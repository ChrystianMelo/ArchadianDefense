#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include "GraphNode.h"

/**
 * \class Graph
 * \brief Representa um grafo contendo múltiplos nós (GraphNodes).
 *
 * Esta classe contém uma coleção de nós (GraphNodes) que representam os vértices
 * do grafo. A classe também oferece métodos para acessar e gerenciar esses nós.
 */
class Graph {
public:
	/**
	 * \brief Construtor padrão da classe Graph.
	 *
	 * Inicializa um grafo vazio sem nenhum nó. Este construtor cria uma instância
	 * de 'Graph' sem nós ou arestas, ideal para ser preenchido posteriormente.
	 */
	Graph() {}

	/**
	 * \brief Construtor da classe Graph com um conjunto de nós.
	 *
	 * \param nodes Vetor contendo os nós (GraphNodes) que farão parte do grafo.
	 *
	 * Este construtor inicializa o grafo com um vetor de nós fornecido. Ele permite
	 * a criação de um grafo já populado com nós.
	 */
	Graph(const std::vector<GraphNode>& nodes) : m_nodes(nodes) {}

	/**
	 * \brief Obtém os nós do grafo.
	 * \return Referência ao vetor de GraphNodes presentes no grafo.
	 *
	 * Este método retorna todos os nós armazenados no grafo. Pode ser usado para
	 * manipular ou acessar os nós do grafo.
	 */
	std::vector<GraphNode>& getNodes();

protected:
	/**
	 * \brief Armazena os nós (GraphNodes) do grafo.
	 *
	 * Um vetor que contém todos os nós (GraphNodes) presentes no grafo. Cada nó
	 * pode estar conectado a outros nós através de arestas (GraphEdges).
	 */
	std::vector<GraphNode> m_nodes;
};

#endif // GRAPH_H
