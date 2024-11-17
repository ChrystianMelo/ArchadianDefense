#include "Road.h"

Road::Road(City* source, City* target) : m_source(source), m_target(target) {}

City* Road::getSource() const {
	return m_source;
}

City* Road::getTarget() const {
	return m_target;
}

bool Road::operator==(const Road& other) const {
	return m_source == other.getSource() && m_target == other.getTarget();
}
