#ifndef GRAPHNODE_H
#define GRAPHNODE_H

#include <vector>
#include <unordered_map>
#include "GraphEdge.h"

class GraphEdge;
class GraphNode;

/**
 * \class NodeVisitor
 * \brief
 */
class NodeVisitor {
public:
	/**
	 * \brief
	 */
	virtual ~NodeVisitor() = default;

	/**
	 * \brief
	 */
	virtual void visit(GraphNode* node) = 0;
};

/**
 * \class GraphNode
 * \brief Representa um nó (vértice) em um grafo.
 *
 * Um nó em um grafo pode estar conectado a outros nós através de arestas
 * (GraphEdges). Esta classe fornece funcionalidades para acessar as arestas
 * conectadas ao nó.
 */
class GraphNode {
public:
	/**
	 * \brief Construtor padrão de GraphNode.
	 *
	 * Cria uma instância de GraphNode sem arestas conectadas inicialmente.
	 */
	GraphNode();

	/**
	 *
	 */
	GraphNode(std::size_t index);

	/**
	 *
	 */
	std::size_t getIndex() const;

	/**
	 * \brief Conecta dois GraphNodes.
	 */
	void connect(GraphNode* node);

	/**
	 *
	 */
	void disconnect(GraphNode* node);

	/**
	 *
	 */
	bool isConnected(GraphNode* node);

	/**
	 * \brief Obtém as arestas conectadas ao nó.
	 * \return Um vetor de ponteiros para GraphEdges conectadas a este nó.
	 *
	 * Retorna todas as arestas que estão conectadas ao nó atual, permitindo que
	 * o chamador interaja com as conexões do nó.
	 */
	std::vector<GraphEdge>& getEdges();

	/**
	 *
	 */
	void setEdges(std::vector<GraphEdge> edges);

	/**
	 *
	 */
	bool operator==(const GraphNode& other) const;

	/**
	 *
	 */
	bool operator<(const GraphNode& other) const;

	/**
	 *
	 */
	struct GraphNodeHash {
		std::size_t operator()(const GraphNode* k) const {
			return std::hash<std::size_t>()(k->getIndex());
		}
	};

	/**
	 *
	 */
	struct GraphNodeEqual {
		bool operator()(const GraphNode* lhs, const GraphNode* rhs) const {
			return *lhs == *rhs;
		}
	};

	/**
	 *
	 */
	template<typename T>
	static std::unordered_map<GraphNode*, T, GraphNodeHash, GraphNodeEqual> map() {
		return std::unordered_map<GraphNode*, T, GraphNodeHash, GraphNodeEqual>();
	}
private:
	/**
	 * \brief Armazena as arestas conectadas ao nó.
	 *
	 * Um vetor que contém ponteiros para as arestas (GraphEdges) que conectam este nó
	 * a outros nós. Cada aresta aponta para outro nó no grafo.
	 */
	std::vector<GraphEdge> m_edges;

	/**
	 *
	 */
	std::size_t m_index;
};


namespace std {
	template <>

	/**
	 *
	 */
	struct hash<GraphNode> {
		std::size_t operator()(const GraphNode node) const {
			return std::hash<std::size_t>()(node.getIndex());
		}
	};
}
#endif // GRAPHNODE_H
