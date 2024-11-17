#include "City.h"

City::City() : m_index(0) {}

City::City(std::size_t index, std::string name) : m_index(index), m_name(name) {}

void City::connect(City* node) {
	m_edges.push_back(Road(this, node));
}

void City::disconnect(City* node) {
	m_edges.erase(std::remove(m_edges.begin(), m_edges.end(), Road(this, node)), m_edges.end());
}

bool City::isConnected(City* node) {
	for (Road& e : m_edges)
		if (*e.getTarget() == *node)
			return true;
	return false;
}

std::string& City::getName() { return m_name; }

std::vector<Road>& City::getEdges() {
	return m_edges;
}

void City::setEdges(std::vector<Road> edges) { m_edges = edges; }

bool City::operator==(const City& other) const {
	if (m_index != other.getIndex())
		return false;

	if (m_edges.size() != other.m_edges.size())
		return false;

	for (std::size_t i = 0; i < m_edges.size(); i++)
		if (m_edges[i] != other.m_edges[i])
			return false;

	return true;

}

bool City::operator<(const City& other) const {
	return this->m_index < other.getIndex();
}

std::size_t City::getIndex() const { return m_index; }