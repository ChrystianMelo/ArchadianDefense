#include <boost/test/unit_test.hpp>

#include "Graph.h"
#include "GraphNode.h"
#include "Algorithms.h"

// Teste do algoritmo de Dijkstra para calcular a distância mínima
BOOST_AUTO_TEST_CASE(Dijkstra_ShortestPath) {
	GraphNode node1(1), node2(2), node3(3), node4(4);

	node1.connect(&node2);
	node2.connect(&node3);
	node3.connect(&node4);
	node1.connect(&node3);
	Graph graph({ node1, node2, node3, node4 });

	auto distances = Algorithms::Dijkstra(&graph, node1);

	assert(distances[&node1] == 0);
	assert(distances[&node2] == 1);
	assert(distances[&node3] == 1);
	assert(distances[&node4] == 2);
}

// Teste complexo do algoritmo de Dijkstra para calcular a distância mínima
BOOST_AUTO_TEST_CASE( Dijkstra_ComplexShortestPath) {
	GraphNode node1(1), node2(2), node3(3), node4(4), node5(5), node6(6);

	node1.connect(&node2);
	node1.connect(&node3);
	node2.connect(&node3);
	node2.connect(&node4);
	node3.connect(&node5);
	node5.connect(&node4);
	node4.connect(&node6);
	node5.connect(&node6);
	node1.connect(&node6);

	Graph graph({ node1, node2, node3, node4, node5, node6 });

	auto distances = Algorithms::Dijkstra(&graph, node1);

	assert(distances[&node1] == 0);
	assert(distances[&node2] == 1);
	assert(distances[&node3] == 1);
	assert(distances[&node4] == 2);
	assert(distances[&node5] == 2);
	assert(distances[&node6] == 1);
}

// Teste do algoritmo de Dijkstra em um grafo com ciclos
BOOST_AUTO_TEST_CASE(Dijkstra_CycleGraphTest) {
	GraphNode node1(1), node2(2), node3(3), node4(4);

	node1.connect(&node2);
	node2.connect(&node3);
	node3.connect(&node4);
	node4.connect(&node2);
	node3.connect(&node1);

	Graph graph({ node1, node2, node3, node4 });

	auto distances = Algorithms::Dijkstra(&graph, node1);

	assert(distances[&node1] == 0);
	assert(distances[&node2] == 1);
	assert(distances[&node3] == 2);
	assert(distances[&node4] == 3);
}

// Teste do algoritmo de Dijkstra em um grafo desconexo
BOOST_AUTO_TEST_CASE(Dijkstra_DisconnectedGraphTest) {
	GraphNode node1(1), node2(2), node3(3), node4(4), node5(5);

	node1.connect(&node2);
	node2.connect(&node3);

	node4.connect(&node5);

	Graph graph({ node1, node2, node3, node4, node5 });

	auto distances = Algorithms::Dijkstra(&graph, node1);

	assert(distances[&node1] == 0);
	assert(distances[&node2] == 1);
	assert(distances[&node3] == 2);

	assert(distances[&node4] == std::numeric_limits<int>::max());
	assert(distances[&node5] == std::numeric_limits<int>::max());
}
