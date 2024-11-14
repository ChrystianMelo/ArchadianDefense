#include "GraphEdge.h"

GraphEdge::GraphEdge(GraphNode* source, GraphNode* target) : m_source(source), m_target(target) {}

GraphNode* GraphEdge::getSource() const {
	return m_source;
}

GraphNode* GraphEdge::getTarget() const {
	return m_target;
}

bool GraphEdge::operator==(const GraphEdge& other) const {
	return m_source == other.getSource() && m_target == other.getTarget();
}
