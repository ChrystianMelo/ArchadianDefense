#ifndef ALGORITHMS_H
#define ALGORITHMS_H

#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>

#include "Archadian.h"

enum CityColor {
	// N�o foi descobreto.
	UNDISCOVERED,
	// Descoberto mas n�o finalizado.
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
* \brief Visitante de n�s para a identifica��o de componentes fortemente conectadas (SCCs).
*
* Essa classe rastreia as componentes fortemente conectadas (SCCs) enquanto os n�s
* s�o visitados durante uma execu��o de busca em profundidade (DFS).
*/
class SCCNodeVisitor : public NodeVisitor {
public:
	/**
	 * \brief Construtor padr�o.
	 *
	 * Inicializa as estruturas necess�rias para rastrear as SCCs.
	 */
	SCCNodeVisitor()
		: m_sccs(), scc_(), prev_dfs_main_visit(nullptr), prev_node(nullptr) {}

	/**
	 * \brief M�todo chamado para visitar um n�.
	 * \param node Ponteiro para o n� sendo visitado.
	 *
	 * Identifica e constr�i as SCCs � medida que os n�s s�o visitados.
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
	 * Adiciona a �ltima SCC rastreada � lista, se necess�rio.
	 */
	void finalize() {
		if (!scc_.empty()) {
			m_sccs.push_back(scc_);
		}
	}

	/**
	 * \brief Obt�m as SCCs identificadas.
	 * \return Um vetor contendo todas as SCCs rastreadas.
	 */
	std::vector<SCC> getSCCS() { return m_sccs; }

private:
	/**
	 * \brief Lista de componentes fortemente conectadas.
	 */
	std::vector<SCC> m_sccs;

	/**
	 * \brief A SCC atual sendo constru�da.
	 */
	SCC scc_;

	/**
	 * \brief Ponteiro para o n� principal da �ltima visita DFS.
	 */
	City* prev_dfs_main_visit;

	/**
	 * \brief Ponteiro para o �ltimo n� visitado.
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
	 * Este m�todo percorre o grafo come�ando a partir de um n� inicial e visita recursivamente
	 * todos os n�s conectados, registrando informa��es como tempos de descoberta e finaliza��o.
	 *
	 * \param Archadian Um ponteiro para o objeto 'Archadian' que cont�m os n�s e arestas a serem percorridos.
	 *                  Este objeto representa o grafo sobre o qual a DFS ser� executada.
	 * \param nodeVisitor Um ponteiro para uma fun��o ou objeto que ser� chamado em cada n� visitado.
	 *                    Permite a execu��o de a��es espec�ficas durante a visita a cada n�.
	 *
	 * \return Um `DFS_DATA` contendo tr�s mapas:
	 *         - Um mapa que associa cada n� (City) ao seu estado (`CityColor`).
	 *         - Um mapa que associa cada n� ao seu tempo de descoberta (`DiscoveryTime`).
	 *         - Um mapa que associa cada n� ao seu tempo de finaliza��o (`FinishingTime`).
	 *
	 * \note Complexidade: O(V + E), onde V � o n�mero de n�s (v�rtices) e E � o n�mero de arestas do grafo.
	 *       A DFS percorre todos os n�s e arestas uma �nica vez.
	 */
	static DFS_DATA DFS(Archadian* Archadian, NodeVisitor* nodeVisitor);

	/**
	 * \brief Realiza uma busca em profundidade (DFS) em um conjunto de n�s.
	 *
	 * Este m�todo executa a DFS em um subconjunto espec�fico de n�s, utilizando os n�s
	 * fornecidos como ponto de partida. Durante a execu��o, os n�s visitados e suas
	 * respectivas informa��es de descoberta e finaliza��o s�o registrados.
	 *
	 * \param visitingNodes Um vetor contendo as cidades (City) a partir das quais a DFS ser� iniciada.
	 * \param nodeVisitor Um ponteiro para uma fun��o ou objeto que ser� chamado em cada n� visitado.
	 *                    Permite a execu��o de a��es espec�ficas durante a visita a cada n�.
	 *
	 * \return Um `DFS_DATA` contendo tr�s mapas:
	 *         - Um mapa que associa cada n� (City) ao seu estado (`CityColor`).
	 *         - Um mapa que associa cada n� ao seu tempo de descoberta (`DiscoveryTime`).
	 *         - Um mapa que associa cada n� ao seu tempo de finaliza��o (`FinishingTime`).
	 *
	 * \note Complexidade: O(V + E), onde V � o n�mero de n�s visitados e E � o n�mero de arestas conectadas
	 *       aos n�s visitados. A DFS percorre apenas os n�s e arestas acess�veis a partir dos n�s fornecidos.
	 */
	static DFS_DATA DFS(std::vector<City>& visitingNodes, NodeVisitor* nodeVisitor);

	/**
	 * \brief Realiza a transposi��o de um grafo, invertendo a dire��o de todas as arestas.
	 *
	 * Este m�todo inverte as arestas do grafo, tornando o n� de destino de cada aresta o novo n� de origem,
	 * e o n� de origem o novo destino. Essa opera��o � usada em algoritmos como o de Kosaraju para encontrar
	 * componentes fortemente conectadas.
	 *
	 * \param Archadian O grafo a ser transposto.
	 *
	 * \note Complexidade: O(V + E), onde V � o n�mero de n�s e E � o n�mero de arestas do grafo.
	 */
	static void transposeArchadian(Archadian& Archadian);

	/**
	 * \brief Encontra componentes fortemente conectadas em um grafo usando o algoritmo de Kosaraju.
	 *
	 * Este m�todo utiliza uma busca em profundidade (DFS) combinada com uma transposi��o do grafo para identificar
	 * conjuntos de n�s interconectados, onde cada n� do conjunto pode alcan�ar qualquer outro n� do mesmo conjunto.
	 *
	 * \param Archadian Um ponteiro para o objeto 'Archadian' que ser� processado.
	 *
	 * \return Um vetor de componentes fortemente conectadas (SCC), onde cada SCC � um conjunto de n�s.
	 *
	 * \note Complexidade: O(V + E), onde V � o n�mero de n�s e E � o n�mero de arestas do grafo.
	 */
	static std::vector<SCC> Kosaraju(Archadian* Archadian);

	/**
	 * \brief Calcula os caminhos mais curtos de um n� fonte para todos os outros n�s em um grafo usando o algoritmo de Dijkstra.
	 *
	 * Este m�todo encontra os caminhos mais curtos de um n� de origem para todos os outros n�s do grafo, considerando pesos nas arestas.
	 *
	 * \param Archadian Um ponteiro para o objeto 'Archadian' contendo os n�s e arestas.
	 * \param source O n� de origem a partir do qual os caminhos ser�o calculados.
	 *
	 * \return Um mapa que associa cada n� acess�vel a partir da origem com o vetor de cidades que comp�em o caminho mais curto.
	 *
	 * \note Complexidade: O((V + E) * log(V)), onde V � o n�mero de n�s e E � o n�mero de arestas do grafo.
	 */
	static std::unordered_map<City*, std::vector<City*>, CityHash, CityEqual> Dijkstra(Archadian* Archadian, City& source);

	/**
	 * \brief Move o elemento especificado para a primeira posi��o no vetor,
	 * preservando a ordem relativa dos outros elementos.
	 *
	 * \tparam T Tipo dos elementos no vetor.
	 * \param vec Vetor onde o elemento ser� movido.
	 * \param value Valor que ser� movido para a primeira posi��o.
	 *
	 * /note Complexidade:
	 * A complexidade no pior caso � O(n^2), onde n � o tamanho do vetor.
	 * Isso ocorre porque, no pior caso, o elemento est� na �ltima posi��o,
	 * e para cada passo, todos os swaps subsequentes s�o realizados.
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
