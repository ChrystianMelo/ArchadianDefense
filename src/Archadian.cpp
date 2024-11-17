#include "Archadian.h"

#include <cassert>
#include <limits>

#include "Algorithms.h"

namespace {
	class SCCNodeVisitor : public NodeVisitor {
	public:
		SCCNodeVisitor()
			: m_sccs(), scc_(), prev_dfs_main_visit(nullptr), prev_node(nullptr) {}

		void visit(City* node) override {
			assert(dfs_main_visit != nullptr);

			if (prev_dfs_main_visit == nullptr) prev_dfs_main_visit = dfs_main_visit;

			if (prev_dfs_main_visit != dfs_main_visit && !scc_.empty()) {
				m_sccs.push_back(scc_);
				scc_ = SCC();
				prev_dfs_main_visit = dfs_main_visit;
			}

			if (prev_node != nullptr && dfs_recent_visit != nullptr && prev_node != dfs_recent_visit)
				scc_.push_back(*dfs_recent_visit);
			scc_.push_back(*node);
			prev_node = node;
		}

		void finalize() {
			if (!scc_.empty()) {
				m_sccs.push_back(scc_);
			}
		}

		std::vector<SCC> getSCCS() { return m_sccs; };
	private:
		std::vector<SCC> m_sccs;
		SCC scc_;                 // SCC atual sendo construído
		City* prev_dfs_main_visit;
		City* prev_node;     // Último nó visitado
	};
}

Archadian::Archadian() : m_nodes(), m_capital() {}

Archadian::Archadian(const std::vector<City>& nodes) : m_nodes(nodes) {
}

std::vector<City>& Archadian::getNodes() {
	return m_nodes;
}

City Archadian::getCapital() const { return m_capital; }

Battalions Archadian::getBattalions() const { return m_battalions; }

std::vector<Patrolling> Archadian::getPatrolling() const { return m_patrolling; }

bool Archadian::hasBattalions() const { return m_hasBattalions; }

void Archadian::calcCapital() {
	std::unordered_map<City*, int, CityHash, CityEqual> distances;

	for (City& node : m_nodes) {
		auto dijkstra = Algorithms::Dijkstra(this, node);

		// Se não se existir caminho pra todos os nós do grafo esse nó não é candidato a ser capitao.
		if (dijkstra.size() != m_nodes.size() - 1) continue;

		int sum = 0;
		for (const auto& pair : dijkstra)
			sum += pair.second.size();
		distances[&node] = sum;
	}

	int maior = std::numeric_limits<int>::max();
	for (const auto& pair : distances)
		if (pair.second < maior && pair.second > 0) {
			maior = pair.second;
			m_capital = *pair.first;
		}
}

void Archadian::calcBattalionsAndPatrolling() {
	Algorithms::moveToFirst<City>(m_nodes, m_capital);

	auto sccs = Algorithms::Kosaraju(this);

	m_hasBattalions = !(sccs.size() == 1 && sccs[0][0] == m_capital);

	// Remove a scc formada so pelo capitao, se existir.
	for (auto it = sccs.begin(); it != sccs.end();) {
		if (it->size() == 1 && it->front().getIndex() == m_capital.getIndex()) {
			it = sccs.erase(it);
		}
		else {
			++it;
		}
	}

	for (auto scc : sccs)
		// Não existe batalhao começando pela capital
		if (auto battalion = scc[0]; scc[0] != m_capital)
			m_battalions.push_back(scc[0]);

	// Não existe patrulha de um batalhao só.
	for (auto it = sccs.begin(); it != sccs.end();) {
		if (it->size() == 1) {
			it = sccs.erase(it);
		}
		else {
			++it;
		}
	}

	for (auto scc : sccs) {
		SCC patrolling;

		// Percorre o caminho da scc com o caminho original do grafo.
		Archadian archadian2 = Archadian(scc);
		{
			Algorithms::transposeArchadian(archadian2);

			SCCNodeVisitor visitedNodeCollector = SCCNodeVisitor();
			auto dfs_data = Algorithms::DFS(&archadian2, &visitedNodeCollector);
			visitedNodeCollector.finalize();

			auto sccs = visitedNodeCollector.getSCCS();
			assert(sccs.size() == 1);

			patrolling = sccs[0];
		}

		// Adiciona um caminho de volta pro batalhao apos visitar todas as cidades do patrulhamento.
		{
			City first = patrolling[0];
			City last = patrolling[patrolling.size() - 1];

			if (first != last) {
				auto dijkstra = Algorithms::Dijkstra(&archadian2, last);
				auto pathPointer = dijkstra[&first];

				std::vector<City> path;
				for (auto city : pathPointer) {
					path.push_back(*city);
				}
				assert(!path.empty());

				patrolling.insert(patrolling.end(), path.begin(), path.end() - 1);
			}
		}

		m_patrolling.push_back(patrolling);
	}
}