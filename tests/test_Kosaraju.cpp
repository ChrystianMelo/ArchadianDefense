#include <boost/test/unit_test.hpp>

#include <unordered_set>

#include "Archadian.h"
#include "City.h"
#include "Algorithms.h"

// Teste simplificado da função Kosaraju para encontrar componentes fortemente conectadas
BOOST_AUTO_TEST_CASE(Kosaraju_Simplified) {
	City node1(1), node2(2), node3(3);

	node1.connect(&node2);
	node2.connect(&node1);

	node3.connect(&node2);

	Archadian Archadian({ node1, node2, node3 });

	std::vector<SCC> sccs = Algorithms::Kosaraju(&Archadian);

	std::vector<std::unordered_set<std::size_t>> foundSCCs;
	for (const auto& scc : sccs) {
		std::unordered_set<std::size_t> scc_indices;
		for (const auto& node : scc) {
			scc_indices.insert(node.getIndex());
		}
		foundSCCs.push_back(scc_indices);
	}

	std::vector<std::unordered_set<std::size_t>> expectedSCCs = {
		{3},       		{1, 2} };

	BOOST_CHECK(foundSCCs.size() == expectedSCCs.size());

	for (const auto& expected_scc : expectedSCCs) {
		bool scc_found = false;
		for (const auto& found_scc : foundSCCs) {
			if (found_scc == expected_scc) {
				scc_found = true;
				break;
			}
		}
		BOOST_CHECK(scc_found);
	}
}

// Teste da função Kosaraju para encontrar componentes fortemente conectadas
BOOST_AUTO_TEST_CASE(Kosaraju) {
	City node1(1), node2(2), node3(3), node4(4), node5(5);

	node1.connect(&node2);
	node2.connect(&node3);
	node3.connect(&node1);

	node2.connect(&node4);

	node4.connect(&node5);
	node5.connect(&node4);

	Archadian Archadian({ node1, node2, node3, node4, node5 });

	std::vector<SCC> sccs = Algorithms::Kosaraju(&Archadian);

	std::vector<std::unordered_set<std::size_t>> foundSCCs;
	for (const auto& scc : sccs) {
		std::unordered_set<std::size_t> scc_indices;
		for (const auto& node : scc) {
			scc_indices.insert(node.getIndex());
		}
		foundSCCs.push_back(scc_indices);
	}

	std::vector<std::unordered_set<std::size_t>> expectedSCCs = {
		{1, 3,2},       		{4, 5} };

	BOOST_CHECK(foundSCCs.size() == expectedSCCs.size());

	for (const auto& expected_scc : expectedSCCs) {
		bool scc_found = false;
		for (const auto& found_scc : foundSCCs) {
			if (found_scc == expected_scc) {
				scc_found = true;
				break;
			}
		}
		BOOST_CHECK(scc_found);
	}
}

// Teste 1: Nós Isolados
BOOST_AUTO_TEST_CASE(Kosaraju_IsolatedNodesTest) {
	City node1(1), node2(2), node3(3);

	City node4(4), node5(5);
	node4.connect(&node5);
	node5.connect(&node4);

	Archadian Archadian({ node1, node2, node3, node4, node5 });

	std::vector<SCC> sccs = Algorithms::Kosaraju(&Archadian);

	std::vector<std::unordered_set<std::size_t>> foundSCCs;
	for (const auto& scc : sccs) {
		std::unordered_set<std::size_t> scc_indices;
		for (const auto& node : scc) {
			scc_indices.insert(node.getIndex());
		}
		foundSCCs.push_back(scc_indices);
	}

	std::vector<std::unordered_set<std::size_t>> expectedSCCs = {
		{1},       		{2},       		{3},       		{4, 5} };

	BOOST_CHECK(foundSCCs.size() == expectedSCCs.size());

	for (const auto& expected_scc : expectedSCCs) {
		bool scc_found = false;
		for (const auto& found_scc : foundSCCs) {
			if (found_scc == expected_scc) {
				scc_found = true;
				break;
			}
		}
		BOOST_CHECK(scc_found);
	}
}

// Teste 2: Grafo Totalmente Conectado
BOOST_AUTO_TEST_CASE(Kosaraju_FullyConnectedArchadianTest) {
	City node1(1), node2(2), node3(3), node4(4);

	node1.connect(&node2);
	node1.connect(&node3);
	node1.connect(&node4);

	node2.connect(&node1);
	node2.connect(&node3);
	node2.connect(&node4);

	node3.connect(&node1);
	node3.connect(&node2);
	node3.connect(&node4);

	node4.connect(&node1);
	node4.connect(&node2);
	node4.connect(&node3);

	Archadian Archadian({ node1, node2, node3, node4 });

	std::vector<SCC> sccs = Algorithms::Kosaraju(&Archadian);

	std::unordered_set<std::size_t> foundSCC;
	for (const auto& scc : sccs) {
		for (const auto& node : scc) {
			foundSCC.insert(node.getIndex());
		}
	}

	std::unordered_set<std::size_t> expectedSCC = { 1, 2, 3, 4 };

	BOOST_CHECK(sccs.size() == 1);

	BOOST_CHECK(foundSCC == expectedSCC);
}

// Teste 3: Grafo com Várias SCCs Individuais
BOOST_AUTO_TEST_CASE(Kosaraju_MultipleSingleNodeSCCsTest) {
	City node1(1), node2(2), node3(3), node4(4);

	Archadian Archadian({ node1, node2, node3, node4 });

	std::vector<SCC> sccs = Algorithms::Kosaraju(&Archadian);

	std::vector<std::unordered_set<std::size_t>> foundSCCs;
	for (const auto& scc : sccs) {
		std::unordered_set<std::size_t> scc_indices;
		for (const auto& node : scc) {
			scc_indices.insert(node.getIndex());
		}
		foundSCCs.push_back(scc_indices);
	}

	std::vector<std::unordered_set<std::size_t>> expectedSCCs = {
		{1},
		{2},
		{3},
		{4}
	};

	BOOST_CHECK(foundSCCs.size() == expectedSCCs.size());

	for (const auto& expected_scc : expectedSCCs) {
		bool scc_found = false;
		for (const auto& found_scc : foundSCCs) {
			if (found_scc == expected_scc) {
				scc_found = true;
				break;
			}
		}
		BOOST_CHECK(scc_found);
	}
}
