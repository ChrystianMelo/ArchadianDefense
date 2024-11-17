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
 * Esta classe encapsula um grafo, onde os nós representam cidades (Citys)
 * e as arestas representam conexões entre elas. Também fornece métodos para
 * realizar cálculos relacionados a capital, batalhões e patrulhamento no grafo.
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
	 * \brief Calcula a cidade capital do grafo.
	 *
	 * Este método utiliza o algoritmo de Dijkstra para determinar a cidade capital,
	 * que é definida como o nó mais central ou estratégico do grafo.
	 *
	 * \note Complexidade: O((V + E) * log(V)), onde V é o número de nós (Citys) e E é o número de arestas.
	 */
	void calcCapital();

	/**
	 * \brief Calcula os batalhões e o patrulhamento no grafo.
	 *
	 * Este método executa uma sequência de algoritmos:
	 * 1. Kosaraju para encontrar componentes fortemente conectadas (SCCs).
	 * 2. Para cada componente fortemente conectada (n componentes no total), executa:
	 *    - Uma busca em profundidade (DFS) para analisar conexões internas.
	 *    - O algoritmo de Dijkstra para calcular rotas e custos associados.
	 *
	 * \note Complexidade:
	 * - Kosaraju: O(V + E), onde V é o número de nós e E é o número de arestas.
	 * - DFS e Dijkstra sequenciais: O(n * (V + E) * log(V)), onde n é o número de componentes fortemente conectadas.
	 */
	void calcBattalionsAndPatrolling();

	/**
	 * \brief Obtém os nós do grafo.
	 * \return Referência ao vetor de Citys presentes no grafo.
	 *
	 * Este método retorna todos os nós armazenados no grafo. Pode ser usado para
	 * manipular ou acessar os nós do grafo.
	 */
	std::vector<City>& getNodes();

	/**
	 * \brief Obtém a cidade capital do grafo.
	 * \return A cidade definida como capital.
	 *
	 * Este método retorna a cidade calculada como a capital do grafo, após a
	 * execução de `calcCapital`.
	 */
	City getCapital() const;

	/**
	 * \brief Obtém os batalhões definidos no grafo.
	 * \return Um vetor de cidades representando os batalhões.
	 *
	 * Este método retorna a lista de cidades que foram classificadas como batalhões
	 * após a execução de `calcBattalionsAndPatrolling`.
	 */
	Battalions getBattalions() const;

	/**
	 * \brief Obtém as patrulhas definidas no grafo.
	 * \return Um vetor de vetores de cidades representando as rotas de patrulha.
	 *
	 * Este método retorna as rotas de patrulhamento definidas no grafo, calculadas
	 * após a execução de `calcBattalionsAndPatrolling`.
	 */
	std::vector<Patrolling> getPatrolling() const;

	/**
	 * \brief Verifica se há batalhões definidos no grafo.
	 * \return Verdadeiro se houver batalhões, falso caso contrário.
	 *
	 * Este método retorna um valor booleano indicando se a estrutura de batalhões
	 * foi calculada e está disponível.
	 */
	bool hasBattalions() const;

private:
	/**
	 * \brief Armazena os nós (Citys) do grafo.
	 *
	 * Um vetor que contém todos os nós (Citys) presentes no grafo. Cada nó
	 * pode estar conectado a outros nós através de arestas (Roads).
	 */
	std::vector<City> m_nodes;

	/**
	 * \brief Cidade definida como capital do grafo.
	 *
	 * Após a execução de `calcCapital`, este atributo armazena o nó que foi
	 * determinado como capital.
	 */
	City m_capital;

	/**
	 * \brief Lista de cidades classificadas como batalhões.
	 *
	 * Após a execução de `calcBattalionsAndPatrolling`, este vetor armazena os
	 * batalhões definidos no grafo.
	 */
	Battalions m_battalions;

	/**
	 * \brief Lista de rotas de patrulhamento.
	 *
	 * Após a execução de `calcBattalionsAndPatrolling`, este vetor de vetores armazena
	 * as rotas de patrulha definidas no grafo.
	 */
	std::vector<Patrolling> m_patrolling;

	/**
	 * \brief Indica se batalhões foram definidos no grafo.
	 *
	 * Este valor booleano é verdadeiro se `calcBattalionsAndPatrolling` tiver sido
	 * executado e definido batalhões com sucesso.
	 */
	bool m_hasBattalions = false;
};

#endif // Archadian_H