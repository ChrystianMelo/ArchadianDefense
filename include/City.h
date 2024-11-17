#ifndef City_H
#define City_H

#include <vector>
#include <string>
#include <unordered_map>

#include "Road.h"

class Road;
class City;

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
	virtual void visit(City* node) = 0;

	/**
	 * \brief
	 */
	City* dfs_main_visit = nullptr;

	/**
	 * \brief
	 */
	City* dfs_recent_visit = nullptr;
};

/**
 * \class City
 * \brief Representa um nó (vértice) em um grafo.
 *
 * Um nó em um grafo pode estar conectado a outros nós através de arestas
 * (Roads). Esta classe fornece funcionalidades para acessar as arestas
 * conectadas ao nó.
 */
class City {
public:
	/**
	 * \brief Construtor padrão de City.
	 *
	 * Cria uma instância de City sem arestas conectadas inicialmente.
	 */
	City();

	/**
	 *
	 */
	City(std::size_t index, std::string name = "");

	/**
	 *
	 */
	std::size_t getIndex() const;

	/**
	 * \brief Conecta dois Citys.
	 */
	void connect(City* node);

	/**
	 *
	 */
	bool isConnected(City* node);

	/**
	 *
	 */
	std::string& getName();

	/**
	 * \brief Obtém as arestas conectadas ao nó.
	 * \return Um vetor de ponteiros para Roads conectadas a este nó.
	 *
	 * Retorna todas as arestas que estão conectadas ao nó atual, permitindo que
	 * o chamador interaja com as conexões do nó.
	 */
	std::vector<Road>& getEdges();

	/**
	 *
	 */
	void setEdges(std::vector<Road> edges);

	/**
	 *
	 */
	bool operator==(const City& other) const;

	/**
	 *
	 */
	bool operator!=(const City& other) const;

	/**
	 *
	 */
	bool operator<(const City& other) const;

	/**
	 *
	 */
	struct CityHash {
		std::size_t operator()(const City* k) const {
			return std::hash<std::size_t>()(k->getIndex());
		}
	};

	/**
	 *
	 */
	struct CityEqual {
		bool operator()(const City* lhs, const City* rhs) const {
			return *lhs == *rhs;
		}
	};

	/**
	 *
	 */
	template<typename T>
	static std::unordered_map<City*, T, CityHash, CityEqual> map() {
		return std::unordered_map<City*, T, CityHash, CityEqual>();
	}
private:
	/**
	 * \brief Armazena as arestas conectadas ao nó.
	 *
	 * Um vetor que contém ponteiros para as arestas (Roads) que conectam este nó
	 * a outros nós. Cada aresta aponta para outro nó no grafo.
	 */
	std::vector<Road> m_edges;

	/**
	 *
	 */
	std::size_t m_index;

	/**
	 *
	 */
	std::string m_name;
};


namespace std {
	template <>

	/**
	 *
	 */
	struct hash<City> {
		std::size_t operator()(const City node) const {
			return std::hash<std::size_t>()(node.getIndex());
		}
	};
}
#endif // City_H
