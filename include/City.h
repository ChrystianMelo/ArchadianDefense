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
 * \brief Representa um n� (v�rtice) em um grafo.
 *
 * Um n� em um grafo pode estar conectado a outros n�s atrav�s de arestas
 * (Roads). Esta classe fornece funcionalidades para acessar as arestas
 * conectadas ao n�.
 */
class City {
public:
	/**
	 * \brief Construtor padr�o de City.
	 *
	 * Cria uma inst�ncia de City sem arestas conectadas inicialmente.
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
	 * \brief Obt�m as arestas conectadas ao n�.
	 * \return Um vetor de ponteiros para Roads conectadas a este n�.
	 *
	 * Retorna todas as arestas que est�o conectadas ao n� atual, permitindo que
	 * o chamador interaja com as conex�es do n�.
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
	 * \brief Armazena as arestas conectadas ao n�.
	 *
	 * Um vetor que cont�m ponteiros para as arestas (Roads) que conectam este n�
	 * a outros n�s. Cada aresta aponta para outro n� no grafo.
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
