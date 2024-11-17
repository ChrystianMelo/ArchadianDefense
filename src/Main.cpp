#include <iostream>

#include <cassert>
#include <unordered_set>
#include <string>
#include <limits>

#include "Algorithms.h"

class VisitedNodeCollector : public NodeVisitor {
public:
	explicit VisitedNodeCollector()
		: visited_() {}

	void visit(City* node) override {
		visited_.insert(*node);
	}

	std::unordered_set<City> getVisited() {
		return visited_;
	}
private:
	std::unordered_set<City> visited_;
};

bool isSubset(const std::vector<City>& subset, const std::vector<City>& superset) {
	std::unordered_set<City> supersetSet(superset.begin(), superset.end());

	for (const City& elem : subset) {
		bool found = false;
		for (const City& elem2 : subset)
			if (elem.getIndex() == elem2.getIndex())
				found = true;

		if (!found)
			return false;
	}
	return true;
}

int main() {
	std::size_t v, e;
	std::cin >> v >> e;
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

	std::size_t index = 1;
	std::unordered_map<std::string, City> map;
	std::vector<std::string> insertion_order;

	for (std::size_t i = 0; i < e; i++) {
		std::string s1, s2;

		std::cin >> s1 >> s2;

		City* c1 = nullptr;
		if (auto it = map.find(s1); it == map.end()) {
			map.insert({ s1, City(index++, s1) });
			c1 = &map[s1];
			insertion_order.push_back(s1);
		}
		else {
			c1 = &it->second;
		}

		City* c2 = nullptr;
		if (auto it2 = map.find(s2); it2 == map.end()) {
			map.insert({ s2, City(index++, s2) });
			c2 = &map[s2];
			insertion_order.push_back(s2);
		}
		else {
			c2 = &it2->second;
		}

		c1->connect(c2);
	}

	assert(map.size() == v);

	std::vector<City> cities;
	for (const auto& name : insertion_order) {
		cities.push_back(map[name]);
	}

	Archadian archadian = Archadian(cities);

	auto capital = archadian.getCapital();
	std::cout << capital->getName() << std::endl;

	auto battalions = archadian.getBattalions();
	auto patrollings = archadian.getPatrolling();

	// Batalhao
	if (patrollings.size() == 1 && patrollings[0][0].isConnected(capital)) {
		std::cout << "0" << std::endl;
	}
	else {
		std::cout << battalions.size() << std::endl;
		for (auto city : battalions) {
			std::cout << city.getName() << std::endl;
		}
	}

	// Patrulhamento
	std::cout << patrollings.size() << std::endl;
	for (auto patrolling : patrollings) {
		for (auto city : patrolling)
			std::cout << city.getName() << " ";
		std::cout << std::endl;
	}
}