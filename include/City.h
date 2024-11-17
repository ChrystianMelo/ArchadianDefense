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
 * \brief Classe base abstrata para visitar nós (Citys) em um grafo.
 *
 * Esta classe define a interface para visitantes de nós em um grafo, permitindo
 * realizar operações específicas durante a travessia (DFS ou outros algoritmos).
 */
class NodeVisitor {
public:
	/**
	 * \brief Destrutor virtual padrão.
	 *
	 * Permite a correta destruição de classes derivadas.
	 */
	virtual ~NodeVisitor() = default;

	/**
	 * \brief Visita um nó (City) durante a travessia do grafo.
	 *
	 * Este método deve ser implementado pelas subclasses para definir o comportamento
	 * durante a visita a um nó específico.
	 *
	 * \param node Ponteiro para o nó a ser visitado.
	 */
	virtual void visit(City* node) = 0;

	/**
	 * \brief Ponteiro para o nó principal visitado durante a execução do DFS.
	 *
	 * Armazena o nó principal sendo processado durante a travessia.
	 */
	City* dfs_main_visit = nullptr;

	/**
	 * \brief Ponteiro para o nó mais recente visitado no DFS.
	 *
	 * Armazena o nó que foi processado mais recentemente.
	 */
	City* dfs_recent_visit = nullptr;
};

/**
 * \class City
 * \brief Representa um nó (vértice) em um grafo.
 *
 * A classe `City` modela um nó em um grafo, que pode estar conectado a outros nós
 * através de arestas (representadas pela classe `Road`). Ela oferece métodos para
 * gerenciar conexões, acessar informações e operar sobre nós.
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
	 * \brief Construtor de City com índice e nome.
	 *
	 * \param index Índice único para identificar a cidade.
	 * \param name Nome opcional para a cidade.
	 *
	 * Este construtor inicializa um nó com um índice específico e, opcionalmente, um nome.
	 */
	City(std::size_t index, std::string name = "");

	/**
	 * \brief Obtém o índice da cidade.
	 * \return O índice único associado à cidade.
	 */
	std::size_t getIndex() const;

	/**
	 * \brief Conecta dois nós (Citys).
	 *
	 * \param node Ponteiro para o nó a ser conectado a este.
	 *
	 * Adiciona uma conexão (Road) entre este nó e o nó fornecido.
	 */
	void connect(City* node);

	/**
	 * \brief Verifica se este nó está conectado a outro nó.
	 *
	 * \param node Ponteiro para o nó a ser verificado.
	 * \return Verdadeiro se os dois nós estão conectados; caso contrário, falso.
	 */
	bool isConnected(City* node);

	/**
	 * \brief Obtém o nome da cidade.
	 * \return Referência para o nome da cidade.
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
	 * \brief Define as arestas conectadas ao nó.
	 *
	 * \param edges Um vetor de arestas (Roads) a serem atribuídas ao nó.
	 */
	void setEdges(std::vector<Road> edges);

	/**
	 * \brief Operador de igualdade para comparação de nós.
	 *
	 * \param other Outro nó a ser comparado.
	 * \return Verdadeiro se os dois nós possuem o mesmo índice.
	 */
	bool operator==(const City& other) const;

	/**
	 * \brief Operador de desigualdade para comparação de nós.
	 *
	 * \param other Outro nó a ser comparado.
	 * \return Verdadeiro se os dois nós possuem índices diferentes.
	 */
	bool operator!=(const City& other) const;

	/**
	 * \brief Operador menor que para comparação de nós.
	 *
	 * \param other Outro nó a ser comparado.
	 * \return Verdadeiro se o índice deste nó for menor que o do outro nó.
	 */
	bool operator<(const City& other) const;

	/**
	 * \struct CityHash
	 * \brief Functor para calcular o hash de um ponteiro para `City`.
	 *
	 * Este functor utiliza o índice da cidade para calcular o hash.
	 */
	struct CityHash {
		std::size_t operator()(const City* k) const {
			return std::hash<std::size_t>()(k->getIndex());
		}
	};

	/**
	 * \struct CityEqual
	 * \brief Functor para verificar a igualdade de dois ponteiros para `City`.
	 *
	 * Este functor utiliza o operador `==` definido na classe `City` para verificar igualdade.
	 */
	struct CityEqual {
		bool operator()(const City* lhs, const City* rhs) const {
			return *lhs == *rhs;
		}
	};

	/**
	 * \brief Cria um mapa personalizado para armazenar dados associados a cidades.
	 *
	 * \tparam T Tipo dos valores armazenados no mapa.
	 * \return Um mapa com chaves do tipo `City*` e valores do tipo `T`.
	 */
	template<typename T>
	static std::unordered_map<City*, T, CityHash, CityEqual> map() {
		return std::unordered_map<City*, T, CityHash, CityEqual>();
	}

private:
	/**
	 * \brief Armazena as arestas conectadas ao nó.
	 *
	 * Um vetor que contém todas as conexões (Roads) que partem deste nó para outros.
	 */
	std::vector<Road> m_edges;

	/**
	 * \brief Índice único da cidade.
	 *
	 * Identifica exclusivamente o nó em um grafo.
	 */
	std::size_t m_index;

	/**
	 * \brief Nome da cidade.
	 *
	 * Nome opcional que pode ser usado para identificar o nó de forma descritiva.
	 */
	std::string m_name;
};

namespace std {
	template <>
	/**
	 * \struct hash<City>
	 * \brief Especialização de `std::hash` para a classe `City`.
	 *
	 * Utiliza o índice da cidade para calcular o hash.
	 */
	struct hash<City> {
		std::size_t operator()(const City node) const {
			return std::hash<std::size_t>()(node.getIndex());
		}
	};
}
#endif // City_H
