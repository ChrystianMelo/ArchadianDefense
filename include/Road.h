#ifndef Road_H
#define Road_H

#include "City.h"

class City;

/**
 * \class Road
 * \brief Representa uma aresta (conex�o) entre dois n�s em um grafo.
 *
 * Uma Road conecta dois n�s (Citys) em um grafo, criando uma rela��o
 * de vizinhan�a entre os n�s.
 */
class Road {
public:
	/**
	 * \brief Construtor de Road.
	 * \param source N� de origem da aresta.
	 * \param target N� de destino da aresta.
	 *
	 * Cria uma aresta que conecta o n� de origem ao n� de destino.
	 */
	Road(City* source, City* target);

	/**
	 * \brief Obt�m o n� de origem da aresta.
	 * \return Ponteiro para o n� de origem.
	 *
	 * Retorna o n� de onde a aresta se origina.
	 */
	City* getSource() const;

	/**
	 * \brief Obt�m o n� de destino da aresta.
	 * \return Ponteiro para o n� de destino.
	 *
	 * Retorna o n� para onde a aresta aponta.
	 */
	City* getTarget() const;

	/**
	 *
	 */
	int getWeight() const { return m_weight; };

	/**
	 *
	 */
	bool operator==(const Road& other) const;

private:
	/**
	 * \brief O n� de origem da aresta.
	 *
	 * Armazena o n� de onde a aresta se origina.
	 */
	City* m_source;

	/**
	 * \brief O n� de destino da aresta.
	 *
	 * Armazena o n� para onde a aresta aponta.
	 */
	City* m_target;

	int m_weight = 1;
};

#endif // Road_H
