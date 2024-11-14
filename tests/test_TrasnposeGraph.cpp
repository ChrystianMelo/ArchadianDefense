#include <boost/test/unit_test.hpp>

#include "Graph.h"
#include "GraphNode.h"
#include "Algorithms.h"

// Teste da função transposeGraph para transpor um grafo com 3 nós
BOOST_AUTO_TEST_CASE(TransposeGraphWithThreeNodes) {
	GraphNode node1(1), node2(2), node3(3);

	node1.connect(&node2);
	node2.connect(&node3);

	Graph graph({ node1, node2, node3 });

	Algorithms::transposeGraph(graph);

	auto nodes = graph.getNodes();
	for (GraphNode& node : nodes) {
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

	Algorithms::transposeGraph(graph);

	nodes = graph.getNodes();
	for (GraphNode& node : nodes) {
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

// Teste da função transposeGraph para transpor um grafo com 3 nós
BOOST_AUTO_TEST_CASE(TransposeGraphWithThreeNodes_Simplified) {
	GraphNode node1(1), node2(2), node3(3);

	node1.connect(&node2);
	node2.connect(&node1);

	node3.connect(&node2);

	Graph graph({ node1, node2, node3 });

	Algorithms::transposeGraph(graph);

	auto nodes = graph.getNodes();
	for (GraphNode& node : nodes) {
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

	Algorithms::transposeGraph(graph);

	nodes = graph.getNodes();
	for (GraphNode& node : nodes) {
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
