#ifndef ALGORITHMS_H
#define ALGORITHMS_H

#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>

#include "Archadian.h"

enum CityColor {
	// Não foi descobreto.
	UNDISCOVERED,
	// Descoberto mas não finalizado.
	DISCOVERED,
	// Finalizado.
	FINISHED
};


using CityHash = City::CityHash;
using CityEqual = City::CityEqual;
using DiscoveryTime = std::size_t;
using FinishingTime = std::size_t;
using DFS_DATA = std::tuple<
	std::unordered_map<City*, CityColor, CityHash, CityEqual>,
	std::unordered_map<City*, DiscoveryTime, CityHash, CityEqual>,
	std::unordered_map<City*, FinishingTime, CityHash, CityEqual>>;
using SCC = std::vector<City>;

/**
* \class SCCNodeVisitor
* \brief Visitante de nós para a identificação de componentes fortemente conectadas (SCCs).
*
* Essa classe rastreia as componentes fortemente conectadas (SCCs) enquanto os nós
* são visitados durante uma execução de busca em profundidade (DFS).
*/
class SCCNodeVisitor : public NodeVisitor {
public:
	/**
	 * \brief Construtor padrão.
	 *
	 * Inicializa as estruturas necessárias para rastrear as SCCs.
	 */
	SCCNodeVisitor()
		: m_sccs(), scc_(), prev_dfs_main_visit(nullptr), prev_node(nullptr) {}

	/**
	 * \brief Método chamado para visitar um nó.
	 * \param node Ponteiro para o nó sendo visitado.
	 *
	 * Identifica e constrói as SCCs à medida que os nós são visitados.
	 */
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

	/**
	 * \brief Finaliza o rastreamento das SCCs.
	 *
	 * Adiciona a última SCC rastreada à lista, se necessário.
	 */
	void finalize() {
		if (!scc_.empty()) {
			m_sccs.push_back(scc_);
		}
	}

	/**
	 * \brief Obtém as SCCs identificadas.
	 * \return Um vetor contendo todas as SCCs rastreadas.
	 */
	std::vector<SCC> getSCCS() { return m_sccs; }

private:
	/**
	 * \brief Lista de componentes fortemente conectadas.
	 */
	std::vector<SCC> m_sccs;

	/**
	 * \brief A SCC atual sendo construída.
	 */
	SCC scc_;

	/**
	 * \brief Ponteiro para o nó principal da última visita DFS.
	 */
	City* prev_dfs_main_visit;

	/**
	 * \brief Ponteiro para o último nó visitado.
	 */
	City* prev_node;
};

/**
 * \class Algorithms
 *
 * \brief Algotimos aprendidos a partir do livro Algorithm Design de Jon Kleinberg
 */
class Algorithms {
public:
	/**
	 * \brief Realiza uma busca em profundidade (DFS) em um grafo.
	 *
	 * Este método percorre o grafo começando a partir de um nó inicial e visita recursivamente
	 * todos os nós conectados, registrando informações como tempos de descoberta e finalização.
	 *
	 * \param Archadian Um ponteiro para o objeto 'Archadian' que contém os nós e arestas a serem percorridos.
	 *                  Este objeto representa o grafo sobre o qual a DFS será executada.
	 * \param nodeVisitor Um ponteiro para uma função ou objeto que será chamado em cada nó visitado.
	 *                    Permite a execução de ações específicas durante a visita a cada nó.
	 *
	 * \return Um `DFS_DATA` contendo três mapas:
	 *         - Um mapa que associa cada nó (City) ao seu estado (`CityColor`).
	 *         - Um mapa que associa cada nó ao seu tempo de descoberta (`DiscoveryTime`).
	 *         - Um mapa que associa cada nó ao seu tempo de finalização (`FinishingTime`).
	 *
	 * \note Complexidade: O(V + E), onde V é o número de nós (vértices) e E é o número de arestas do grafo.
	 *       A DFS percorre todos os nós e arestas uma única vez.
	 */
	static DFS_DATA DFS(Archadian* Archadian, NodeVisitor* nodeVisitor);

	/**
	 * \brief Realiza uma busca em profundidade (DFS) em um conjunto de nós.
	 *
	 * Este método executa a DFS em um subconjunto específico de nós, utilizando os nós
	 * fornecidos como ponto de partida. Durante a execução, os nós visitados e suas
	 * respectivas informações de descoberta e finalização são registrados.
	 *
	 * \param visitingNodes Um vetor contendo as cidades (City) a partir das quais a DFS será iniciada.
	 * \param nodeVisitor Um ponteiro para uma função ou objeto que será chamado em cada nó visitado.
	 *                    Permite a execução de ações específicas durante a visita a cada nó.
	 *
	 * \return Um `DFS_DATA` contendo três mapas:
	 *         - Um mapa que associa cada nó (City) ao seu estado (`CityColor`).
	 *         - Um mapa que associa cada nó ao seu tempo de descoberta (`DiscoveryTime`).
	 *         - Um mapa que associa cada nó ao seu tempo de finalização (`FinishingTime`).
	 *
	 * \note Complexidade: O(V + E), onde V é o número de nós visitados e E é o número de arestas conectadas
	 *       aos nós visitados. A DFS percorre apenas os nós e arestas acessíveis a partir dos nós fornecidos.
	 */
	static DFS_DATA DFS(std::vector<City>& visitingNodes, NodeVisitor* nodeVisitor);

	/**
	 * \brief Realiza a transposição de um grafo, invertendo a direção de todas as arestas.
	 *
	 * Este método inverte as arestas do grafo, tornando o nó de destino de cada aresta o novo nó de origem,
	 * e o nó de origem o novo destino. Essa operação é usada em algoritmos como o de Kosaraju para encontrar
	 * componentes fortemente conectadas.
	 *
	 * \param Archadian O grafo a ser transposto.
	 *
	 * \note Complexidade: O(V + E), onde V é o número de nós e E é o número de arestas do grafo.
	 */
	static void transposeArchadian(Archadian& Archadian);

	/**
	 * \brief Encontra componentes fortemente conectadas em um grafo usando o algoritmo de Kosaraju.
	 *
	 * Este método utiliza uma busca em profundidade (DFS) combinada com uma transposição do grafo para identificar
	 * conjuntos de nós interconectados, onde cada nó do conjunto pode alcançar qualquer outro nó do mesmo conjunto.
	 *
	 * \param Archadian Um ponteiro para o objeto 'Archadian' que será processado.
	 *
	 * \return Um vetor de componentes fortemente conectadas (SCC), onde cada SCC é um conjunto de nós.
	 *
	 * \note Complexidade: O(V + E), onde V é o número de nós e E é o número de arestas do grafo.
	 */
	static std::vector<SCC> Kosaraju(Archadian* Archadian);

	/**
	 * \brief Calcula os caminhos mais curtos de um nó fonte para todos os outros nós em um grafo usando o algoritmo de Dijkstra.
	 *
	 * Este método encontra os caminhos mais curtos de um nó de origem para todos os outros nós do grafo, considerando pesos nas arestas.
	 *
	 * \param Archadian Um ponteiro para o objeto 'Archadian' contendo os nós e arestas.
	 * \param source O nó de origem a partir do qual os caminhos serão calculados.
	 *
	 * \return Um mapa que associa cada nó acessível a partir da origem com o vetor de cidades que compõem o caminho mais curto.
	 *
	 * \note Complexidade: O((V + E) * log(V)), onde V é o número de nós e E é o número de arestas do grafo.
	 */
	static std::unordered_map<City*, std::vector<City*>, CityHash, CityEqual> Dijkstra(Archadian* Archadian, City& source);

	/**
	 * \brief Move o elemento especificado para a primeira posição no vetor,
	 * preservando a ordem relativa dos outros elementos.
	 *
	 * \tparam T Tipo dos elementos no vetor.
	 * \param vec Vetor onde o elemento será movido.
	 * \param value Valor que será movido para a primeira posição.
	 *
	 * /note Complexidade:
	 * A complexidade no pior caso é O(n^2), onde n é o tamanho do vetor.
	 * Isso ocorre porque, no pior caso, o elemento está na última posição,
	 * e para cada passo, todos os swaps subsequentes são realizados.
	 */
	template <typename T>
	static void moveToFirst(std::vector<T>& vec, const T& value) {
		for (size_t i = 0; i < vec.size(); ++i) {
			if (vec[i] == value) {
				for (size_t j = i; j > 0; --j)
					std::swap(vec[j], vec[j - 1]);
				return;
			}
		}
	}
};

#endif // ALGORITHMS_H
