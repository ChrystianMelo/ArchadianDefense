#ifndef Road_H
#define Road_H

#include "City.h"

class City;

/**
 * \class Road
 * \brief Representa uma aresta (conexão) entre dois nós (Citys) em um grafo.
 *
 * A classe `Road` modela uma conexão entre dois nós (Citys) em um grafo,
 * estabelecendo uma relação de vizinhança entre eles. Ela também pode incluir
 * um peso associado à conexão, útil para algoritmos de grafos ponderados.
 */
class Road {
public:
	/**
	 * \brief Construtor de Road.
	 * \param source Nó de origem da aresta.
	 * \param target Nó de destino da aresta.
	 *
	 * Cria uma instância de `Road` que conecta o nó de origem ao nó de destino.
	 * Inicializa o peso padrão como 1, caso não seja especificado.
	 */
	Road(City* source, City* target);

	/**
	 * \brief Obtém o nó de origem da aresta.
	 * \return Ponteiro para o nó de origem.
	 *
	 * Retorna o nó de onde a aresta se origina. Este nó é armazenado em `m_source`.
	 */
	City* getSource() const;

	/**
	 * \brief Obtém o nó de destino da aresta.
	 * \return Ponteiro para o nó de destino.
	 *
	 * Retorna o nó para onde a aresta aponta. Este nó é armazenado em `m_target`.
	 */
	City* getTarget() const;

	/**
	 * \brief Obtém o peso da aresta.
	 * \return O peso associado à aresta.
	 *
	 * Retorna o valor do peso (por padrão, inicializado como 1), que pode ser
	 * utilizado em algoritmos de caminhos mínimos, como Dijkstra.
	 */
	int getWeight() const { return m_weight; };

	/**
	 * \brief Operador de igualdade para comparação de arestas.
	 * \param other Outra instância de `Road` para comparar.
	 * \return Verdadeiro se ambas as arestas possuem o mesmo nó de origem,
	 *         nó de destino e peso; caso contrário, retorna falso.
	 */
	bool operator==(const Road& other) const;

private:
	/**
	 * \brief Nó de origem da aresta.
	 *
	 * Este atributo armazena o ponteiro para o nó (City) de onde a aresta se origina.
	 */
	City* m_source;

	/**
	 * \brief Nó de destino da aresta.
	 *
	 * Este atributo armazena o ponteiro para o nó (City) para onde a aresta aponta.
	 */
	City* m_target;

	/**
	 * \brief Peso da aresta.
	 *
	 * Um valor inteiro que representa o custo ou peso associado à aresta.
	 * O peso é inicializado como 1 por padrão.
	 */
	int m_weight = 1;
};

#endif // Road_H
