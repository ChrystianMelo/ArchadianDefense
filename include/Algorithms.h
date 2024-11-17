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
 * \class Algorithms
 *
 * \brief Algotimos aprendidos a partir do livro Algorithm Design de Jon Kleinberg
 */
class Algorithms {
public:
	/**
	 * \brief Realiza uma busca em profundidade (DFS) em um grafo.
	 *
	 * Este método percorre o grafo começando de um nó e visita todos os nós conectados a ele de maneira recursiva,
	 * utilizando o algoritmo de busca em profundidade (Depth-First Search, DFS).
	 *
	 * \param Archadian Um ponteiro para o objeto 'Archadian' que contém os nós e arestas a serem percorridos.
	 * \param visitedNode Um 'std::function' que será executado em cada nó visitado durante a busca.
	 *                    A função aceita um ponteiro para 'City' como argumento, permitindo que o comportamento
	 *                    durante a visita a cada nó seja personalizado.
	 *
	 * \return *escrever aqui*
	 *
	 * \note Complexidade: O(V + E), onde V é o número de vértices (nós) e E é o número de arestas do grafo.
	 */
	static DFS_DATA DFS(Archadian* Archadian, NodeVisitor* nodeVisitor);

	/**
	 * \brief Realiza uma busca em profundidade (DFS) em um grafo.
	 *
	 * Este método percorre o grafo começando de um nó e visita todos os nós conectados a ele de maneira recursiva,
	 * utilizando o algoritmo de busca em profundidade (Depth-First Search, DFS).
	 *
	 * \param Archadian Um ponteiro para o objeto 'Archadian' que contém os nós e arestas a serem percorridos.
	 * \param visitingNodes
	 * \param nodeVisitor a função aceita um ponteiro para 'City' como argumento, permitindo que o comportamento
	 *                    durante a visita a cada nó seja personalizado.
	 *
	 * \return *escrever aqui*
	 *
	 * \note Complexidade: O(V + E), onde V é o número de vértices (nós) e E é o número de arestas do grafo.
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
	 * \brief Calcula as menores distâncias de um nó fonte para todos os outros nós em um grafo usando o algoritmo de Dijkstra.
	 *
	 * Este método encontra o caminho mais curto de um nó de origem para todos os outros nós do grafo, considerando pesos nas arestas.
	 *
	 * \param Archadian Um ponteiro para o objeto 'Archadian' contendo os nós e arestas.
	 * \param source O nó de origem a partir do qual as distâncias serão calculadas.
	 *
	 * \return Um mapa que associa cada nó acessível a partir da origem com sua menor distância.
	 *
	 * \note Complexidade: O((V + E) * log(V)), onde V é o número de nós e E é o número de arestas do grafo.
	 */
	static std::unordered_map<City*, int, CityHash, CityEqual> Dijkstra(Archadian* Archadian, City& source);

	/**
	 * \brief
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
