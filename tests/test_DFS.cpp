#include <boost/test/unit_test.hpp>

#include <unordered_set>

#include "Graph.h"
#include "GraphNode.h"
#include "Algorithms.h"

namespace {
	class VisitedNodeCollector : public NodeVisitor {
	public:
		explicit VisitedNodeCollector()
			: visited_() {}

		void visit(GraphNode* node) override {
			visited_.insert(*node);
		}

		std::unordered_set<GraphNode> getVisited() {
			return visited_;
		}
	private:
		std::unordered_set<GraphNode> visited_;
	};
}

// DFS visitas
BOOST_AUTO_TEST_CASE(DFS_VisitsAllVertices) {
	GraphNode node1(1), node2(2), node3(3), node4(4);

	node1.connect(&node2);
	node2.connect(&node3);
	node3.connect(&node4);

	Graph graph({ node1,node2,node3,node4 });

	VisitedNodeCollector visitedNodeCollector = VisitedNodeCollector();
	auto dfs_data = Algorithms::DFS(&graph, &visitedNodeCollector);
	std::unordered_set<GraphNode> visited = visitedNodeCollector.getVisited();

	BOOST_CHECK(visited.find(node1) != visited.end());
	BOOST_CHECK(visited.find(node2) != visited.end());
	BOOST_CHECK(visited.find(node3) != visited.end());
	BOOST_CHECK(visited.find(node4) != visited.end());

	auto [colors, discovery_times, finishing_times] = dfs_data;

	for (auto& node : { &node1, &node2, &node3, &node4 }) {
		BOOST_CHECK(colors[node] == GraphNodeColor::FINISHED);
	}

	std::unordered_map<GraphNode*, std::size_t, GraphNodeHash, GraphNodeEqual> expected_discovery_times = {
		{ &node1, 1 },
		{ &node2, 2 },
		{ &node3, 3 },
		{ &node4, 4 }
	};

	std::unordered_map<GraphNode*, std::size_t, GraphNodeHash, GraphNodeEqual> expected_finishing_times = {
		{ &node1, 8 },
		{ &node2, 7 },
		{ &node3, 6 },
		{ &node4, 5 }
	};

	for (auto& node : { &node1, &node2, &node3, &node4 }) {
		BOOST_CHECK(discovery_times.find(node) != discovery_times.end());
		BOOST_CHECK(finishing_times.find(node) != finishing_times.end());

		DiscoveryTime d_time = discovery_times[node];
		FinishingTime f_time = finishing_times[node];

		BOOST_CHECK(d_time < f_time);

		BOOST_CHECK(d_time == expected_discovery_times[node]);
		BOOST_CHECK(f_time == expected_finishing_times[node]);
	}
}

// Teste DFS com um grafo mais complexo e verificação dos tempos esperados
BOOST_AUTO_TEST_CASE(DFS_ComplexGraphTraversal) {
	GraphNode node1(1), node2(2), node3(3), node4(4), node5(5), node6(6), node7(7);

	node1.connect(&node2);
	node1.connect(&node3);
	node2.connect(&node4);
	node2.connect(&node5);
	node3.connect(&node6);
	node4.connect(&node7);
	node5.connect(&node7);
	node6.connect(&node7);
	node7.connect(&node1);

	Graph graph({ node1, node2, node3, node4, node5, node6, node7 });

	VisitedNodeCollector visitedNodeCollector = VisitedNodeCollector();
	DFS_DATA dfs_data = Algorithms::DFS(&graph, &visitedNodeCollector);
	std::unordered_set<GraphNode> visited = visitedNodeCollector.getVisited();

	BOOST_CHECK(visited.find(node1) != visited.end());
	BOOST_CHECK(visited.find(node2) != visited.end());
	BOOST_CHECK(visited.find(node3) != visited.end());
	BOOST_CHECK(visited.find(node4) != visited.end());
	BOOST_CHECK(visited.find(node5) != visited.end());
	BOOST_CHECK(visited.find(node6) != visited.end());
	BOOST_CHECK(visited.find(node7) != visited.end());

	auto [colors, discovery_times, finishing_times] = dfs_data;

	for (auto& node : { &node1, &node2, &node3, &node4, &node5, &node6, &node7 }) {
		BOOST_CHECK(colors[node] == GraphNodeColor::FINISHED);
	}

	std::unordered_map<GraphNode*, std::size_t, GraphNodeHash, GraphNodeEqual> expected_discovery_times = {
		{ &node1, 1 },
		{ &node2, 2 },
		{ &node3, 10 },
		{ &node4, 3 },
		{ &node5, 7 },
		{ &node6, 11 },
		{ &node7, 4 }
	};

	std::unordered_map<GraphNode*, std::size_t, GraphNodeHash, GraphNodeEqual> expected_finishing_times = {
		{ &node1, 14 },
		{ &node2, 9 },
		{ &node3, 13 },
		{ &node4, 6 },
		{ &node5, 8 },
		{ &node6, 12 },
		{ &node7, 5 }
	};

	for (auto& node : { &node1, &node2, &node3, &node4, &node5, &node6, &node7 }) {
		// Cada nó deve ter tempos de descoberta e término definidos
		BOOST_CHECK(discovery_times.find(node) != discovery_times.end());
		BOOST_CHECK(finishing_times.find(node) != finishing_times.end());

		DiscoveryTime d_time = discovery_times[node];
		FinishingTime f_time = finishing_times[node];

		BOOST_CHECK(d_time < f_time);

		BOOST_CHECK(d_time == expected_discovery_times[node]);
		BOOST_CHECK(f_time == expected_finishing_times[node]);
	}
}

// Teste DFS em um grafo desconexo
BOOST_AUTO_TEST_CASE(DFS_DisconnectedGraphTest) {
	// Criação dos nós para o primeiro componente conectado
	GraphNode node1(1), node2(2), node3(3);

	node1.connect(&node2);
	node2.connect(&node3);

	// Criação dos nós para o segundo componente conectado
	GraphNode node4(4), node5(5);

	node4.connect(&node5);

	// Criação do nó isolado (terceiro componente)
	GraphNode node6(6);

	// Criação do grafo com todos os nós
	Graph graph({ node1, node2, node3, node4, node5, node6 });

	// Execução do DFS e obtenção do retorno
	VisitedNodeCollector visitedNodeCollector = VisitedNodeCollector();
	DFS_DATA dfs_data = Algorithms::DFS(&graph, &visitedNodeCollector);
	std::unordered_set<GraphNode> visited = visitedNodeCollector.getVisited();

	// Verificação se todos os nós foram visitados
	BOOST_CHECK(visited.find(node1) != visited.end());
	BOOST_CHECK(visited.find(node2) != visited.end());
	BOOST_CHECK(visited.find(node3) != visited.end());
	BOOST_CHECK(visited.find(node4) != visited.end());
	BOOST_CHECK(visited.find(node5) != visited.end());
	BOOST_CHECK(visited.find(node6) != visited.end());

	// Extração dos dados retornados pelo DFS
	auto [colors, discovery_times, finishing_times] = dfs_data;

	// Verificação das cores dos nós após o DFS
	for (auto& node : { &node1, &node2, &node3, &node4, &node5, &node6 }) {
		// O nó deve estar marcado como "preto" após a conclusão do DFS
		BOOST_CHECK(colors[node] == GraphNodeColor::FINISHED);
	}

	// Tempos esperados de descoberta e término para cada nó
	// Supondo que o DFS explora os nós na ordem em que são fornecidos na lista de nós do grafo
	std::unordered_map<GraphNode*, std::size_t, GraphNodeHash, GraphNodeEqual> expected_discovery_times = {
		{ &node1, 1 },
		{ &node2, 2 },
		{ &node3, 3 },
		{ &node4, 7 },
		{ &node5, 8 },
		{ &node6, 11 }
	};

	std::unordered_map<GraphNode*, std::size_t, GraphNodeHash, GraphNodeEqual> expected_finishing_times = {
		{ &node1, 6 },
		{ &node2, 5 },
		{ &node3, 4 },
		{ &node4, 10 },
		{ &node5, 9 },
		{ &node6, 12 }
	};

	// Verificação dos tempos de descoberta e término
	for (auto& node : { &node1, &node2, &node3, &node4, &node5, &node6 }) {
		// Cada nó deve ter tempos de descoberta e término definidos
		BOOST_CHECK(discovery_times.find(node) != discovery_times.end());
		BOOST_CHECK(finishing_times.find(node) != finishing_times.end());

		DiscoveryTime d_time = discovery_times[node];
		FinishingTime f_time = finishing_times[node];

		// O tempo de descoberta deve ser menor que o tempo de término
		BOOST_CHECK(d_time < f_time);

		// Os tempos devem corresponder aos tempos esperados
		BOOST_CHECK(d_time == expected_discovery_times[node]);
		BOOST_CHECK(f_time == expected_finishing_times[node]);
	}
}