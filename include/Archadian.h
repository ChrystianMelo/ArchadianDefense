#ifndef Archadian_H
#define Archadian_H

#include <vector>

#include "City.h"

using Battalions = std::vector<City>;
using Patrolling = std::vector<City>;

/**
 * \class Archadian
 * \brief Representa um grafo contendo múltiplos nós (Citys).
 *
 * Esta classe contém uma coleção de nós (Citys) que representam os vértices
 * do grafo. A classe também oferece métodos para acessar e gerenciar esses nós.
 */
class Archadian {
public:
	/**
	 * \brief Construtor padrão da classe Archadian.
	 *
	 * Inicializa um grafo vazio sem nenhum nó. Este construtor cria uma instância
	 * de 'Archadian' sem nós ou arestas, ideal para ser preenchido posteriormente.
	 */
	Archadian();

	/**
	 * \brief Construtor da classe Archadian com um conjunto de nós.
	 *
	 * \param nodes Vetor contendo os nós (Citys) que farão parte do grafo.
	 *
	 * Este construtor inicializa o grafo com um vetor de nós fornecido. Ele permite
	 * a criação de um grafo já populado com nós.
	 */
	Archadian(const std::vector<City>& nodes);

	/**
	 * \brief Obtém os nós do grafo.
	 * \return Referência ao vetor de Citys presentes no grafo.
	 *
	 * Este método retorna todos os nós armazenados no grafo. Pode ser usado para
	 * manipular ou acessar os nós do grafo.
	 */
	std::vector<City>& getNodes();

	/**
	 *
	 */
	City* getCapital() const;

	/**
	 *
	 */
	Battalions getBattalions() const;

	/**
	 *
	 */
	std::vector<Patrolling> getPatrolling() const;

private:
	/**
	 *
	 */
	void calcCapital();

	/**
	 *
	 */
	void calcBattalionsAndPatrolling();

	/**
	 * \brief Armazena os nós (Citys) do grafo.
	 *
	 * Um vetor que contém todos os nós (Citys) presentes no grafo. Cada nó
	 * pode estar conectado a outros nós através de arestas (Roads).
	 */
	std::vector<City> m_nodes;

	/**
	 *
	 */
	City* m_capital;

	/**
	 *
	 */
	Battalions m_battalions;

	/**
	 *
	 */
	std::vector<Patrolling> m_patrolling;
};

#endif // Archadian_H
