#ifndef ALGORITHMS_H
#define ALGORITHMS_H

#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>

#include "Graph.h"

enum GraphNodeColor {
	// N�o foi descobreto.
	UNDISCOVERED,
	// Descoberto mas n�o finalizado.
	DISCOVERED,
	// Finalizado.
	FINISHED
};


using GraphNodeHash = GraphNode::GraphNodeHash;
using GraphNodeEqual = GraphNode::GraphNodeEqual;
using DiscoveryTime = std::size_t;
using FinishingTime = std::size_t;
using DFS_DATA = std::tuple<
	std::unordered_map<GraphNode*, GraphNodeColor, GraphNodeHash, GraphNodeEqual>,
	std::unordered_map<GraphNode*, DiscoveryTime, GraphNodeHash, GraphNodeEqual>,
	std::unordered_map<GraphNode*, FinishingTime, GraphNodeHash, GraphNodeEqual>>;
using SCC = std::vector<GraphNode>;

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
	 * Este m�todo percorre o grafo come�ando de um n� e visita todos os n�s conectados a ele de maneira recursiva,
	 * utilizando o algoritmo de busca em profundidade (Depth-First Search, DFS).
	 *
	 * \param graph Um ponteiro para o objeto 'Graph' que cont�m os n�s e arestas a serem percorridos.
	 * \param visitedNode Um 'std::function' que ser� executado em cada n� visitado durante a busca.
	 *                    A fun��o aceita um ponteiro para 'GraphNode' como argumento, permitindo que o comportamento
	 *                    durante a visita a cada n� seja personalizado.
	 *
	 * \return *escrever aqui*
	 *
	 * \note Complexidade: O(V + E), onde V � o n�mero de v�rtices (n�s) e E � o n�mero de arestas do grafo.
	 */
	static DFS_DATA DFS(Graph* graph, NodeVisitor* nodeVisitor);

	/**
	 * \brief Realiza uma busca em profundidade (DFS) em um grafo.
	 *
	 * Este m�todo percorre o grafo come�ando de um n� e visita todos os n�s conectados a ele de maneira recursiva,
	 * utilizando o algoritmo de busca em profundidade (Depth-First Search, DFS).
	 *
	 * \param graph Um ponteiro para o objeto 'Graph' que cont�m os n�s e arestas a serem percorridos.
	 * \param visitingNodes
	 * \param nodeVisitor a fun��o aceita um ponteiro para 'GraphNode' como argumento, permitindo que o comportamento
	 *                    durante a visita a cada n� seja personalizado.
	 *
	 * \return *escrever aqui*
	 *
	 * \note Complexidade: O(V + E), onde V � o n�mero de v�rtices (n�s) e E � o n�mero de arestas do grafo.
	 */
	static DFS_DATA DFS(std::vector<GraphNode>& visitingNodes, NodeVisitor* nodeVisitor);

	/**
	 * \brief Realiza a transposi��o de um grafo, invertendo a dire��o de todas as arestas.
	 *
	 * Este m�todo inverte as arestas do grafo, tornando o n� de destino de cada aresta o novo n� de origem,
	 * e o n� de origem o novo destino. Essa opera��o � usada em algoritmos como o de Kosaraju para encontrar
	 * componentes fortemente conectadas.
	 *
	 * \param graph O grafo a ser transposto.
	 *
	 * \note Complexidade: O(V + E), onde V � o n�mero de n�s e E � o n�mero de arestas do grafo.
	 */
	static void transposeGraph(Graph& graph);

	/**
	 * \brief Encontra componentes fortemente conectadas em um grafo usando o algoritmo de Kosaraju.
	 *
	 * Este m�todo utiliza uma busca em profundidade (DFS) combinada com uma transposi��o do grafo para identificar
	 * conjuntos de n�s interconectados, onde cada n� do conjunto pode alcan�ar qualquer outro n� do mesmo conjunto.
	 *
	 * \param graph Um ponteiro para o objeto 'Graph' que ser� processado.
	 *
	 * \return Um vetor de componentes fortemente conectadas (SCC), onde cada SCC � um conjunto de n�s.
	 *
	 * \note Complexidade: O(V + E), onde V � o n�mero de n�s e E � o n�mero de arestas do grafo.
	 */
	static std::vector<SCC> Kosaraju(Graph* graph);

	/**
	 * \brief Calcula as menores dist�ncias de um n� fonte para todos os outros n�s em um grafo usando o algoritmo de Dijkstra.
	 *
	 * Este m�todo encontra o caminho mais curto de um n� de origem para todos os outros n�s do grafo, considerando pesos nas arestas.
	 *
	 * \param graph Um ponteiro para o objeto 'Graph' contendo os n�s e arestas.
	 * \param source O n� de origem a partir do qual as dist�ncias ser�o calculadas.
	 *
	 * \return Um mapa que associa cada n� acess�vel a partir da origem com sua menor dist�ncia.
	 *
	 * \note Complexidade: O((V + E) * log(V)), onde V � o n�mero de n�s e E � o n�mero de arestas do grafo.
	 */
	static std::unordered_map<GraphNode*, int, GraphNodeHash, GraphNodeEqual> Dijkstra(Graph* graph, GraphNode& source);

};

#endif // ALGORITHMS_H
