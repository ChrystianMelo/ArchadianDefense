#include "Archadian.h"

#include <cassert>
#include <limits>

#include "Algorithms.h"

Archadian::Archadian() : m_nodes(), m_capital(nullptr) {}

Archadian::Archadian(const std::vector<City>& nodes) : m_nodes(nodes) {
	calcCapital();
	calcBattalionsAndPatrolling();
}

std::vector<City>& Archadian::getNodes() {
	return m_nodes;
}

void Archadian::calcCapital() {
	std::unordered_map<City*, int, CityHash, CityEqual> distances;

	for (City& node : getNodes()) {
		auto data = Algorithms::Dijkstra(this, node);

		int sum = 0;
		for (const auto& pair : data)
			sum += pair.second;
		distances[&node] = sum;
	}

	int maior = std::numeric_limits<int>::max();
	for (const auto& pair : distances)
		if (pair.second < maior && pair.second > 0) {
			maior = pair.second;
			m_capital = pair.first;
		}
	assert(m_capital != nullptr);
}

void Archadian::calcBattalionsAndPatrolling() {
	m_patrolling = Algorithms::Kosaraju(this);

	// Remove o capitao.
	for (auto it = m_patrolling.begin(); it != m_patrolling.end();) {
		if (m_capital && it->size() == 1 && it->front().getIndex() == m_capital->getIndex()) {
			it = m_patrolling.erase(it);
		}
		else {
			++it;
		}
	}

	for (auto patrolling : m_patrolling)
		m_battalions.push_back(patrolling[0]);

	// Nenhuma patrulha é possível, pois ao sair de qualquer batalhão
	for (auto it = m_patrolling.begin(); it != m_patrolling.end();) {
		if (it->size() == 1) {
			it = m_patrolling.erase(it);
		}
		else {
			++it;
		}
	}
}