#include <boost/test/unit_test.hpp>

#include "Archadian.h"
#include "City.h"
#include "Algorithms.h"

// Teste da função transposeArchadian para transpor um grafo com 3 nós
BOOST_AUTO_TEST_CASE(TransposeArchadianWithThreeNodes) {
	City node1(1), node2(2), node3(3);

	node1.connect(&node2);
	node2.connect(&node3);

	Archadian Archadian({ node1, node2, node3 });

	Algorithms::transposeArchadian(Archadian);

	auto nodes = Archadian.getNodes();
	for (City& node : nodes) {
		if (node == nodes[0])
			BOOST_CHECK(node.getEdges().size() == 0);
		if (node == nodes[1]) {
			BOOST_CHECK(node.getEdges().size() == 1);
			BOOST_CHECK(node.isConnected(&nodes[0]));
		}
		if (node == nodes[2]) {
			BOOST_CHECK(node.getEdges().size() == 1);
			BOOST_CHECK(node.isConnected(&nodes[1]));
		}

	}

	Algorithms::transposeArchadian(Archadian);

	nodes = Archadian.getNodes();
	for (City& node : nodes) {
		if (node == nodes[0]) {
			BOOST_CHECK(node.getEdges().size() == 1);
			BOOST_CHECK(node.isConnected(&nodes[1]));
		}
		if (node == nodes[1]) {
			BOOST_CHECK(node.getEdges().size() == 1);
			BOOST_CHECK(node.isConnected(&nodes[2]));
		}
		if (node == nodes[2]) {
			BOOST_CHECK(node.getEdges().size() == 0);
		}
	}
}

// Teste da função transposeArchadian para transpor um grafo com 3 nós
BOOST_AUTO_TEST_CASE(TransposeArchadianWithThreeNodes_Simplified) {
	City node1(1), node2(2), node3(3);

	node1.connect(&node2);
	node2.connect(&node1);

	node3.connect(&node2);

	Archadian Archadian({ node1, node2, node3 });

	Algorithms::transposeArchadian(Archadian);

	auto nodes = Archadian.getNodes();
	for (City& node : nodes) {
		if (node == nodes[0]) {
			BOOST_CHECK(node.getEdges().size() == 1);
			BOOST_CHECK(node.isConnected(&nodes[1]));
		}
		if (node == nodes[1]) {
			BOOST_CHECK(node.getEdges().size() == 2);
			BOOST_CHECK(node.isConnected(&nodes[0]));
			BOOST_CHECK(node.isConnected(&nodes[2]));
		}
		if (node == nodes[2]) {
			BOOST_CHECK(node.getEdges().size() == 0);
		}
	}

	Algorithms::transposeArchadian(Archadian);

	nodes = Archadian.getNodes();
	for (City& node : nodes) {
		if (node == nodes[0]) {
			BOOST_CHECK(node.getEdges().size() == 1);
			BOOST_CHECK(node.isConnected(&nodes[1]));
		}
		if (node == nodes[1]) {
			BOOST_CHECK(node.getEdges().size() == 1);
			BOOST_CHECK(node.isConnected(&nodes[0]));
		}
		if (node == nodes[2]) {
			BOOST_CHECK(node.getEdges().size() == 1);
			BOOST_CHECK(node.isConnected(&nodes[1]));
		}
	}
}
