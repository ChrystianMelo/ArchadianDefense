#ifndef Archadian_H
#define Archadian_H

#include <vector>

#include "City.h"

using Battalions = std::vector<City>;
using Patrolling = std::vector<City>;

/**
 * \class Archadian
 * \brief Representa um grafo contendo m�ltiplos n�s (Citys).
 *
 * Esta classe cont�m uma cole��o de n�s (Citys) que representam os v�rtices
 * do grafo. A classe tamb�m oferece m�todos para acessar e gerenciar esses n�s.
 */
class Archadian {
public:
	/**
	 * \brief Construtor padr�o da classe Archadian.
	 *
	 * Inicializa um grafo vazio sem nenhum n�. Este construtor cria uma inst�ncia
	 * de 'Archadian' sem n�s ou arestas, ideal para ser preenchido posteriormente.
	 */
	Archadian();

	/**
	 * \brief Construtor da classe Archadian com um conjunto de n�s.
	 *
	 * \param nodes Vetor contendo os n�s (Citys) que far�o parte do grafo.
	 *
	 * Este construtor inicializa o grafo com um vetor de n�s fornecido. Ele permite
	 * a cria��o de um grafo j� populado com n�s.
	 */
	Archadian(const std::vector<City>& nodes);

	/**
	 * \brief Obt�m os n�s do grafo.
	 * \return Refer�ncia ao vetor de Citys presentes no grafo.
	 *
	 * Este m�todo retorna todos os n�s armazenados no grafo. Pode ser usado para
	 * manipular ou acessar os n�s do grafo.
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
	 * \brief Armazena os n�s (Citys) do grafo.
	 *
	 * Um vetor que cont�m todos os n�s (Citys) presentes no grafo. Cada n�
	 * pode estar conectado a outros n�s atrav�s de arestas (Roads).
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
