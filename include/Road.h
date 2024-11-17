#ifndef Road_H
#define Road_H

#include "City.h"

class City;

/**
 * \class Road
 * \brief Representa uma aresta (conexão) entre dois nós em um grafo.
 *
 * Uma Road conecta dois nós (Citys) em um grafo, criando uma relação
 * de vizinhança entre os nós.
 */
class Road {
public:
	/**
	 * \brief Construtor de Road.
	 * \param source Nó de origem da aresta.
	 * \param target Nó de destino da aresta.
	 *
	 * Cria uma aresta que conecta o nó de origem ao nó de destino.
	 */
	Road(City* source, City* target);

	/**
	 * \brief Obtém o nó de origem da aresta.
	 * \return Ponteiro para o nó de origem.
	 *
	 * Retorna o nó de onde a aresta se origina.
	 */
	City* getSource() const;

	/**
	 * \brief Obtém o nó de destino da aresta.
	 * \return Ponteiro para o nó de destino.
	 *
	 * Retorna o nó para onde a aresta aponta.
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
	 * \brief O nó de origem da aresta.
	 *
	 * Armazena o nó de onde a aresta se origina.
	 */
	City* m_source;

	/**
	 * \brief O nó de destino da aresta.
	 *
	 * Armazena o nó para onde a aresta aponta.
	 */
	City* m_target;

	int m_weight = 1;
};

#endif // Road_H
