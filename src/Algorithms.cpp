#include <cassert>
#include <limits> 

#include "Algorithms.h"

namespace {
	/**
	 * \brief
	 */
	class NullNodeVisitor : public NodeVisitor {
	public:
		void visit(GraphNode* node) override {
		}
	};

	/**
	 * \brief
	 */
	class SCCNodeVisitor : public NodeVisitor {
	public:
		SCCNodeVisitor()
			: m_sccs(), scc_(), prevNode_(nullptr) {}

		void visit(GraphNode* node) override {
			if (prevNode_ != nullptr && !prevNode_->isConnected(node)) {
				m_sccs.push_back(scc_);
				scc_ = SCC();
			}
			scc_.push_back(*node);
			prevNode_ = node;
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
		GraphNode* prevNode_;     // Último nó visitado
	};


	/**
	 * \brief Metodo auxiliar
	 *
	 * \see Algorithms::dfs()
	 */
	static void dfs_visit(GraphNode* node, std::size_t* time,
		std::unordered_map<GraphNode*, GraphNodeColor, GraphNodeHash, GraphNodeEqual>* coloring,
		std::unordered_map<GraphNode*, DiscoveryTime, GraphNodeHash, GraphNodeEqual>* start,
		std::unordered_map<GraphNode*, FinishingTime, GraphNodeHash, GraphNodeEqual>* finish,
		NodeVisitor* nodeVisitor) {
		(*time)++;
		(*start)[node] = *time;
		(*coloring)[node] = GraphNodeColor::DISCOVERED;

		nodeVisitor->visit(node);

		for (GraphEdge& edge : node->getEdges())
			if (GraphNode* target = edge.getTarget(); (*coloring)[target] == GraphNodeColor::UNDISCOVERED)
				dfs_visit(target, time, coloring, start, finish, nodeVisitor);

		(*coloring)[node] = GraphNodeColor::FINISHED;
		(*time)++;
		(*finish)[node] = *time;
	}

	/**
	* \brief
	*/
	std::vector<GraphNode> sortNodesByFinishingTime(
		std::vector<GraphNode>& nodes,
		std::unordered_map<GraphNode*, FinishingTime, GraphNodeHash, GraphNodeEqual>& finishingTime) {
		std::vector<GraphNode*> nodePointers;
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

		std::vector<GraphNode> nodes2;
		for (auto node : nodePointers) {
			nodes2.push_back(*node);
		}

		return nodes2;
	}
}

DFS_DATA Algorithms::DFS(Graph* graph, NodeVisitor* nodeVisitor) {
	return Algorithms::DFS(graph->getNodes(), nodeVisitor);
}

DFS_DATA Algorithms::DFS(std::vector<GraphNode>& visitingNodes, NodeVisitor* nodeVisitor) {
	std::unordered_map<GraphNode*, GraphNodeColor, GraphNodeHash, GraphNodeEqual> coloring;
	std::unordered_map<GraphNode*, DiscoveryTime, GraphNodeHash, GraphNodeEqual> start;
	std::unordered_map<GraphNode*, FinishingTime, GraphNodeHash, GraphNodeEqual> finish;

	for (GraphNode& node : visitingNodes) {
		coloring[&node] = GraphNodeColor::UNDISCOVERED;
		start[&node] = 0;
		finish[&node] = 0;
	}

	std::size_t time = 0;

	for (GraphNode& node : visitingNodes)
		if (coloring[&node] == GraphNodeColor::UNDISCOVERED)
			dfs_visit(&node, &time, &coloring, &start, &finish, nodeVisitor);

	return std::make_tuple(coloring, start, finish);;
}

void Algorithms::transposeGraph(Graph& graph) {
	std::unordered_map<std::size_t, std::vector<GraphNode*>> invertedEdges;

	for (auto& node : graph.getNodes()) {
		for (const auto& edge : node.getEdges()) {
			invertedEdges[edge.getTarget()->getIndex()].push_back(&node);
		}
	}

	for (auto& node : graph.getNodes()) {
		node.setEdges({});
	}

	for (auto& node : graph.getNodes()) {
		for (GraphNode* sourceNode : invertedEdges[node.getIndex()]) {
			node.connect(sourceNode);
		}
	}
}


std::vector<SCC> Algorithms::Kosaraju(Graph* graph) {
	NullNodeVisitor nullVisitor = NullNodeVisitor();
	DFS_DATA data = Algorithms::DFS(graph, &nullVisitor);
	auto& finishingTime = std::get<2>(data);

	Algorithms::transposeGraph(*graph);

	std::vector<GraphNode> nodes2 = sortNodesByFinishingTime(graph->getNodes(), finishingTime);

	SCCNodeVisitor visitor = SCCNodeVisitor();
	Algorithms::DFS(nodes2, &visitor);
	visitor.finalize();

	Algorithms::transposeGraph(*graph);

	return visitor.getSCCS();
}

std::unordered_map<GraphNode*, int, GraphNodeHash, GraphNodeEqual> Algorithms::Dijkstra(Graph* graph, GraphNode& source) {
	// Define a distância inicial como infinito
	std::unordered_map<GraphNode*, int, GraphNodeHash, GraphNodeEqual> distances;
	for (GraphNode& node : graph->getNodes()) {
		distances[&node] = std::numeric_limits<int>::max();
	}
	distances[&source] = 0;

	// Fila de prioridade para selecionar o nodo com a menor distância
	using NodeDistPair = std::pair<int, GraphNode*>;
	std::priority_queue<NodeDistPair, std::vector<NodeDistPair>, std::greater<NodeDistPair>> queue;
	queue.push({ 0, &source });

	while (!queue.empty()) {
		int distance = queue.top().first;
		GraphNode* current = queue.top().second;
		queue.pop();

		// Ignorar se a distância é maior do que a registrada
		int curretDistance = distances[current];
		if (distance > curretDistance) continue;

		// Verificar vizinhos
		for (const GraphEdge& edge : current->getEdges()) {
			GraphNode* neighbor = edge.getTarget();
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
