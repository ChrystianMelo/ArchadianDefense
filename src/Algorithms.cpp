#include <cassert>
#include <limits> 

#include "Algorithms.h"

namespace {
	/**
	 * \brief
	 */
	class NullNodeVisitor : public NodeVisitor {
	public:
		void visit(City* node) override {
		}
	};

	/**
	 * \brief
	 */
	class SCCNodeVisitor : public NodeVisitor {
	public:
		SCCNodeVisitor()
			: m_sccs(), scc_(), prev_dfs_main_visit(nullptr), prev_node(nullptr) {}

		void visit(City* node) override {
			assert(dfs_main_visit != nullptr);

			if (prev_dfs_main_visit == nullptr) prev_dfs_main_visit = dfs_main_visit;

			if (prev_dfs_main_visit != dfs_main_visit && !scc_.empty()) {
				m_sccs.push_back(scc_);
				scc_ = SCC();
				prev_dfs_main_visit = dfs_main_visit;
			}
		
			if(prev_node != nullptr  && dfs_recent_visit != nullptr && prev_node != dfs_recent_visit)
				scc_.push_back(*dfs_recent_visit);

			scc_.push_back(*node);
			prev_node = node;
		}

		void finalize() {
			if (!scc_.empty()) {
				m_sccs.push_back(scc_);
			}
		}

		std::vector<SCC> getSCCS() { return m_sccs; };
	private:
		std::vector<SCC> m_sccs;
		SCC scc_;                 // SCC atual sendo construído
		City* prev_dfs_main_visit;     
		City* prev_node;     // Último nó visitado
	};


	/**
	 * \brief Metodo auxiliar
	 *
	 * \see Algorithms::dfs()
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
	* \brief
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


std::vector<SCC> Algorithms::Kosaraju(Archadian* Archadian) {
	NullNodeVisitor nullVisitor = NullNodeVisitor();
	DFS_DATA data = Algorithms::DFS(Archadian, &nullVisitor);
	auto& finishingTime = std::get<2>(data);

	Algorithms::transposeArchadian(*Archadian);

	std::vector<City> nodes2 = sortNodesByFinishingTime(Archadian->getNodes(), finishingTime);

	SCCNodeVisitor visitor = SCCNodeVisitor();
	Algorithms::DFS(nodes2, &visitor);
	visitor.finalize();

	Algorithms::transposeArchadian(*Archadian);

	return visitor.getSCCS();
}

std::unordered_map<City*, int, CityHash, CityEqual> Algorithms::Dijkstra(Archadian* Archadian, City& source) {
	// Define a distância inicial como infinito
	std::unordered_map<City*, int, CityHash, CityEqual> distances;
	for (City& node : Archadian->getNodes()) {
		distances[&node] = 999;//std::numeric_limits<int>::max();
	}
	distances[&source] = 0;

	// Fila de prioridade para selecionar o nodo com a menor distância
	using NodeDistPair = std::pair<int, City*>;
	std::priority_queue<NodeDistPair, std::vector<NodeDistPair>, std::greater<NodeDistPair>> queue;
	queue.push({ 0, &source });

	while (!queue.empty()) {
		int distance = queue.top().first;
		City* current = queue.top().second;
		queue.pop();

		// Ignorar se a distância é maior do que a registrada
		int curretDistance = distances[current];
		if (distance > curretDistance) continue;

		// Verificar vizinhos
		for (const Road& edge : current->getEdges()) {
			City* neighbor = edge.getTarget();
			int newDist = distances[current] + edge.getWeight();

			// Atualizar a distância se o caminho atual é mais curto
			if (newDist < distances[neighbor]) {
				distances[neighbor] = newDist;
				queue.push({ newDist, neighbor });
			}
		}
	}

	return distances;
}
