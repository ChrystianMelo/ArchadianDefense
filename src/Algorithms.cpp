#include <cassert>
#include <unordered_set>
#include <limits>

#include "Algorithms.h"

namespace {
	/**
	 * \class NullNodeVisitor
	 * \brief Um visitante de nó nulo que não realiza nenhuma operação.
	 *
	 * Essa classe é uma implementação padrão de `NodeVisitor` que não realiza
	 * nenhuma ação nos nós visitados. Útil como implementação de fallback ou
	 * quando nenhuma operação é necessária.
	 */
	class NullNodeVisitor : public NodeVisitor {
	public:
		/**
		 * \brief Método chamado para visitar um nó.
		 * \param node Ponteiro para o nó sendo visitado.
		 *
		 * Esta implementação não realiza nenhuma ação.
		 */
		void visit([[maybe_unused]] City* node) override {}
	};

	/**
	 * \brief Executa uma visita em profundidade (DFS) a partir de um nó.
	 *
	 * \param node O nó inicial para a DFS.
	 * \param time Ponteiro para o contador de tempo.
	 * \param coloring Mapa de cores para rastrear o estado dos nós.
	 * \param start Mapa de tempos de descoberta dos nós.
	 * \param finish Mapa de tempos de finalização dos nós.
	 * \param nodeVisitor Objeto visitante a ser aplicado em cada nó visitado.
	 *
	 * Essa função realiza uma busca em profundidade (DFS) em um grafo, registrando
	 * tempos de descoberta e finalização, enquanto utiliza o `NodeVisitor` fornecido
	 * para executar ações específicas durante a travessia.
	 *
	 * \note Complexidade: O(V + E), onde V é o número de nós e E o número de arestas.
	 */
	static void dfs_visit(City* node, std::size_t* time,
		std::unordered_map<City*, CityColor, CityHash, CityEqual>* coloring,
		std::unordered_map<City*, DiscoveryTime, CityHash, CityEqual>* start,
		std::unordered_map<City*, FinishingTime, CityHash, CityEqual>* finish,
		NodeVisitor* nodeVisitor) {
		(*time)++;
		(*start)[node] = *time;
		(*coloring)[node] = CityColor::DISCOVERED;

		nodeVisitor->visit(node);

		for (Road& edge : node->getEdges())
			if (City* target = edge.getTarget(); (*coloring)[target] == CityColor::UNDISCOVERED) {
				nodeVisitor->dfs_recent_visit = node;
				dfs_visit(target, time, coloring, start, finish, nodeVisitor);
			}

		(*coloring)[node] = CityColor::FINISHED;
		(*time)++;
		(*finish)[node] = *time;
	}

	/**
	 * \brief Ordena nós por seus tempos de finalização em ordem decrescente.
	 *
	 * \param nodes Vetor de nós a serem ordenados.
	 * \param finishingTime Mapa contendo os tempos de finalização de cada nó.
	 * \return Um vetor de nós ordenados por tempo de finalização em ordem decrescente.
	 *
	 * Essa função utiliza um algoritmo de ordenação Bubble Sort para reordenar os nós.
	 *
	 * \note Complexidade: O(n^2), onde n é o número de nós.
	 */
	std::vector<City> sortNodesByFinishingTime(
		std::vector<City>& nodes,
		std::unordered_map<City*, FinishingTime, CityHash, CityEqual>& finishingTime) {
		std::vector<City*> nodePointers;
		for (auto& node : nodes) {
			nodePointers.push_back(&node);
		}

		std::size_t n = nodePointers.size();
		for (std::size_t i = 0; i < n - 1; ++i) {
			for (std::size_t j = 0; j < n - i - 1; ++j) {
				if (finishingTime[nodePointers[j]] < finishingTime[nodePointers[j + 1]]) {
					std::swap(nodePointers[j], nodePointers[j + 1]);
				}
			}
		}

		std::vector<City> nodes2;
		for (auto node : nodePointers) {
			nodes2.push_back(*node);
		}

		return nodes2;
	}
}

DFS_DATA Algorithms::DFS(Archadian* Archadian, NodeVisitor* nodeVisitor) {
	return Algorithms::DFS(Archadian->getNodes(), nodeVisitor);
}

DFS_DATA Algorithms::DFS(std::vector<City>& visitingNodes, NodeVisitor* nodeVisitor) {
	std::unordered_map<City*, CityColor, CityHash, CityEqual> coloring;
	std::unordered_map<City*, DiscoveryTime, CityHash, CityEqual> start;
	std::unordered_map<City*, FinishingTime, CityHash, CityEqual> finish;

	for (City& node : visitingNodes) {
		coloring[&node] = CityColor::UNDISCOVERED;
		start[&node] = 0;
		finish[&node] = 0;
	}

	std::size_t time = 0;

	for (City& node : visitingNodes)
		if (coloring[&node] == CityColor::UNDISCOVERED) {
			nodeVisitor->dfs_recent_visit = nullptr;
			nodeVisitor->dfs_main_visit = &node;
			dfs_visit(&node, &time, &coloring, &start, &finish, nodeVisitor);
		}

	return std::make_tuple(coloring, start, finish);;
}

void Algorithms::transposeArchadian(Archadian& Archadian) {
	std::unordered_map<std::size_t, std::vector<City*>> invertedEdges;

	for (auto& node : Archadian.getNodes()) {
		for (const auto& edge : node.getEdges()) {
			invertedEdges[edge.getTarget()->getIndex()].push_back(&node);
		}
	}

	for (auto& node : Archadian.getNodes()) {
		node.setEdges({});
	}

	for (auto& node : Archadian.getNodes()) {
		for (City* sourceNode : invertedEdges[node.getIndex()]) {
			node.connect(sourceNode);
		}
	}
}


std::vector<SCC> Algorithms::Kosaraju(Archadian* archadian) {
	NullNodeVisitor nullNodeVisitor = NullNodeVisitor();
	DFS_DATA data = Algorithms::DFS(archadian, &nullNodeVisitor);
	auto& finishingTime = std::get<2>(data);

	Algorithms::transposeArchadian(*archadian);

	std::vector<City> nodes2 = sortNodesByFinishingTime(archadian->getNodes(), finishingTime);

	SCCNodeVisitor visitor = SCCNodeVisitor();
	Algorithms::DFS(nodes2, &visitor);
	visitor.finalize();

	Algorithms::transposeArchadian(*archadian);

	return visitor.getSCCS();
}

std::unordered_map<City*, std::vector<City*>, CityHash, CityEqual> Algorithms::Dijkstra(Archadian* Archadian, City& source) {
	std::unordered_map<City*, int, CityHash, CityEqual> distances;
	std::unordered_map<City*, City*, CityHash, CityEqual> predecessors;

	for (City& node : Archadian->getNodes()) {
		distances[&node] = std::numeric_limits<int>::max();
		predecessors[&node] = nullptr;
	}
	distances[&source] = 0;

	using NodeDistPair = std::pair<int, City*>;
	std::priority_queue<NodeDistPair, std::vector<NodeDistPair>, std::greater<NodeDistPair>> queue;
	queue.push({ 0, &source });

	while (!queue.empty()) {
		int distance = queue.top().first;
		City* current = queue.top().second;
		queue.pop();

		int currentDistance = distances[current];
		if (distance > currentDistance) continue;

		for (const Road& edge : current->getEdges()) {
			City* neighbor = edge.getTarget();
			int newDist = distances[current] + edge.getWeight();

			if (newDist < distances[neighbor]) {
				distances[neighbor] = newDist;
				predecessors[neighbor] = current;
				queue.push({ newDist, neighbor });
			}
		}
	}

	std::unordered_map<City*, std::vector<City*>, CityHash, CityEqual> result;
	for (const auto& pair : distances) {
		City* node = pair.first;

		if (*node == source) continue;

		int distance = pair.second;

		if (distance == std::numeric_limits<int>::max()) continue;

		std::vector<City*> path;
		for (City* at = node; at != nullptr; at = predecessors[at]) {
			if (*at == source) continue;
			path.push_back(at);
		}

		std::size_t n = path.size();
		for (std::size_t i = 0; i < n / 2; ++i) {
			City* temp = path[i];
			path[i] = path[n - i - 1];
			path[n - i - 1] = temp;
		}

		result[node] = path;
	}

	return result;
}