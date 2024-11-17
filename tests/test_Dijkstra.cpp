#include <boost/test/unit_test.hpp>

#include "Archadian.h"
#include "City.h"
#include "Algorithms.h"

// Teste do algoritmo de Dijkstra para calcular a distância mínima
BOOST_AUTO_TEST_CASE(Dijkstra_ShortestPath) {
	City node1(1), node2(2), node3(3), node4(4);

	node1.connect(&node2);
	node2.connect(&node3);
	node3.connect(&node4);
	node1.connect(&node3);
	Archadian Archadian({ node1, node2, node3, node4 });

	auto distances = Algorithms::Dijkstra(&Archadian, node1);

	BOOST_CHECK(distances.find(&node1) == distances.end());
	BOOST_CHECK(distances[&node2].size() == 1);
	BOOST_CHECK(distances[&node3].size() == 1);
	BOOST_CHECK(distances[&node4].size() == 2);
}

// Teste complexo do algoritmo de Dijkstra para calcular a distância mínima
BOOST_AUTO_TEST_CASE(Dijkstra_ComplexShortestPath) {
	City node1(1), node2(2), node3(3), node4(4), node5(5), node6(6);

	node1.connect(&node2);
	node1.connect(&node3);
	node2.connect(&node3);
	node2.connect(&node4);
	node3.connect(&node5);
	node5.connect(&node4);
	node4.connect(&node6);
	node5.connect(&node6);
	node1.connect(&node6);

	Archadian Archadian({ node1, node2, node3, node4, node5, node6 });

	auto distances = Algorithms::Dijkstra(&Archadian, node1);

	BOOST_CHECK(distances.find(&node1) == distances.end());
	BOOST_CHECK(distances[&node2].size() == 1);
	BOOST_CHECK(distances[&node3].size() == 1);
	BOOST_CHECK(distances[&node4].size() == 2);
	BOOST_CHECK(distances[&node5].size() == 2);
	BOOST_CHECK(distances[&node6].size() == 1);
}

// Teste do algoritmo de Dijkstra em um grafo com ciclos
BOOST_AUTO_TEST_CASE(Dijkstra_CycleArchadianTest) {
	City node1(1), node2(2), node3(3), node4(4);

	node1.connect(&node2);
	node2.connect(&node3);
	node3.connect(&node4);
	node4.connect(&node2);
	node3.connect(&node1);

	Archadian Archadian({ node1, node2, node3, node4 });

	auto distances = Algorithms::Dijkstra(&Archadian, node1);

	BOOST_CHECK(distances.find(&node1) == distances.end());
	BOOST_CHECK(distances[&node2].size() == 1);
	BOOST_CHECK(distances[&node3].size() == 2);
	BOOST_CHECK(distances[&node4].size() == 3);
}

// Teste do algoritmo de Dijkstra em um grafo desconexo
BOOST_AUTO_TEST_CASE(Dijkstra_DisconnectedArchadianTest) {
	City node1(1), node2(2), node3(3), node4(4), node5(5);

	node1.connect(&node2);
	node2.connect(&node3);

	node4.connect(&node5);

	Archadian Archadian({ node1, node2, node3, node4, node5 });

	auto distances = Algorithms::Dijkstra(&Archadian, node1);

	BOOST_CHECK(distances.find(&node1) == distances.end());
	BOOST_CHECK(distances[&node2].size() == 1);
	BOOST_CHECK(distances[&node3].size() == 2);

	BOOST_CHECK(distances.find(&node4) == distances.end());
	BOOST_CHECK(distances.find(&node5) == distances.end());
}