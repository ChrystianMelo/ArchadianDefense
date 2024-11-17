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
 * Esta classe encapsula um grafo, onde os n�s representam cidades (Citys)
 * e as arestas representam conex�es entre elas. Tamb�m fornece m�todos para
 * realizar c�lculos relacionados a capital, batalh�es e patrulhamento no grafo.
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
	 * \brief Calcula a cidade capital do grafo.
	 *
	 * Este m�todo utiliza o algoritmo de Dijkstra para determinar a cidade capital,
	 * que � definida como o n� mais central ou estrat�gico do grafo.
	 *
	 * \note Complexidade: O((V + E) * log(V)), onde V � o n�mero de n�s (Citys) e E � o n�mero de arestas.
	 */
	void calcCapital();

	/**
	 * \brief Calcula os batalh�es e o patrulhamento no grafo.
	 *
	 * Este m�todo executa uma sequ�ncia de algoritmos:
	 * 1. Kosaraju para encontrar componentes fortemente conectadas (SCCs).
	 * 2. Para cada componente fortemente conectada (n componentes no total), executa:
	 *    - Uma busca em profundidade (DFS) para analisar conex�es internas.
	 *    - O algoritmo de Dijkstra para calcular rotas e custos associados.
	 *
	 * \note Complexidade:
	 * - Kosaraju: O(V + E), onde V � o n�mero de n�s e E � o n�mero de arestas.
	 * - DFS e Dijkstra sequenciais: O(n * (V + E) * log(V)), onde n � o n�mero de componentes fortemente conectadas.
	 */
	void calcBattalionsAndPatrolling();

	/**
	 * \brief Obt�m os n�s do grafo.
	 * \return Refer�ncia ao vetor de Citys presentes no grafo.
	 *
	 * Este m�todo retorna todos os n�s armazenados no grafo. Pode ser usado para
	 * manipular ou acessar os n�s do grafo.
	 */
	std::vector<City>& getNodes();

	/**
	 * \brief Obt�m a cidade capital do grafo.
	 * \return A cidade definida como capital.
	 *
	 * Este m�todo retorna a cidade calculada como a capital do grafo, ap�s a
	 * execu��o de `calcCapital`.
	 */
	City getCapital() const;

	/**
	 * \brief Obt�m os batalh�es definidos no grafo.
	 * \return Um vetor de cidades representando os batalh�es.
	 *
	 * Este m�todo retorna a lista de cidades que foram classificadas como batalh�es
	 * ap�s a execu��o de `calcBattalionsAndPatrolling`.
	 */
	Battalions getBattalions() const;

	/**
	 * \brief Obt�m as patrulhas definidas no grafo.
	 * \return Um vetor de vetores de cidades representando as rotas de patrulha.
	 *
	 * Este m�todo retorna as rotas de patrulhamento definidas no grafo, calculadas
	 * ap�s a execu��o de `calcBattalionsAndPatrolling`.
	 */
	std::vector<Patrolling> getPatrolling() const;

	/**
	 * \brief Verifica se h� batalh�es definidos no grafo.
	 * \return Verdadeiro se houver batalh�es, falso caso contr�rio.
	 *
	 * Este m�todo retorna um valor booleano indicando se a estrutura de batalh�es
	 * foi calculada e est� dispon�vel.
	 */
	bool hasBattalions() const;

private:
	/**
	 * \brief Armazena os n�s (Citys) do grafo.
	 *
	 * Um vetor que cont�m todos os n�s (Citys) presentes no grafo. Cada n�
	 * pode estar conectado a outros n�s atrav�s de arestas (Roads).
	 */
	std::vector<City> m_nodes;

	/**
	 * \brief Cidade definida como capital do grafo.
	 *
	 * Ap�s a execu��o de `calcCapital`, este atributo armazena o n� que foi
	 * determinado como capital.
	 */
	City m_capital;

	/**
	 * \brief Lista de cidades classificadas como batalh�es.
	 *
	 * Ap�s a execu��o de `calcBattalionsAndPatrolling`, este vetor armazena os
	 * batalh�es definidos no grafo.
	 */
	Battalions m_battalions;

	/**
	 * \brief Lista de rotas de patrulhamento.
	 *
	 * Ap�s a execu��o de `calcBattalionsAndPatrolling`, este vetor de vetores armazena
	 * as rotas de patrulha definidas no grafo.
	 */
	std::vector<Patrolling> m_patrolling;

	/**
	 * \brief Indica se batalh�es foram definidos no grafo.
	 *
	 * Este valor booleano � verdadeiro se `calcBattalionsAndPatrolling` tiver sido
	 * executado e definido batalh�es com sucesso.
	 */
	bool m_hasBattalions = false;
};

#endif // Archadian_H