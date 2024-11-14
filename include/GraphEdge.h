#ifndef GRAPHEDGE_H
#define GRAPHEDGE_H

#include "GraphNode.h"

class GraphNode;

/**
 * \class GraphEdge
 * \brief Representa uma aresta (conexão) entre dois nós em um grafo.
 *
 * Uma GraphEdge conecta dois nós (GraphNodes) em um grafo, criando uma relação
 * de vizinhança entre os nós.
 */
class GraphEdge {
public:
	/**
	 * \brief Construtor de GraphEdge.
	 * \param source Nó de origem da aresta.
	 * \param target Nó de destino da aresta.
	 *
	 * Cria uma aresta que conecta o nó de origem ao nó de destino.
	 */
	GraphEdge(GraphNode* source, GraphNode* target);

	/**
	 * \brief Obtém o nó de origem da aresta.
	 * \return Ponteiro para o nó de origem.
	 *
	 * Retorna o nó de onde a aresta se origina.
	 */
	GraphNode* getSource() const;

	/**
	 * \brief Obtém o nó de destino da aresta.
	 * \return Ponteiro para o nó de destino.
	 *
	 * Retorna o nó para onde a aresta aponta.
	 */
	GraphNode* getTarget() const;

	/**
	 *
	 */
	int getWeight() const { return m_weight; };

	/**
	 *
	 */
	bool operator==(const GraphEdge& other) const;

private:
	/**
	 * \brief O nó de origem da aresta.
	 *
	 * Armazena o nó de onde a aresta se origina.
	 */
	GraphNode* m_source;

	/**
	 * \brief O nó de destino da aresta.
	 *
	 * Armazena o nó para onde a aresta aponta.
	 */
	GraphNode* m_target;

	int m_weight = 1;
};

#endif // GRAPHEDGE_H
