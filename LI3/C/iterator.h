/**
 *  @file iterator.h
 *  @brief Protótipos das funções de um iterador implementado com um array.
 *
 *  Implementação de um iterador que pode armazenar qualquer tipo de dados.
 *  O iterador é implementado tendo por base um array, facilitando, deste modo,
 *  a navegação deste. O índice da última posição consultada no iterador é
 *  guardado, sendo bastante eficiente consultar a posição seguinte ou a
 *  posição anterior.
 *  Ex: Suponhamos que nos encontramos na posição 4 do iterador.
 *      Se fizermos printCurrentIterator então é efetuado a impressão da
 *      posição 4.
 *      Ao se recuar ou avançar no iterador este índice é decrementado ou
 *      incrementado.
 *      Se fizermos goToIterator(10) então o índice passa a ser 10 e todo o
 *      processo é o mesmo que o para o índice 4.
 *
 *  @author Carlos Pereira - A61887
 *  @author Diogo Silva    - A76407
 *  @author Rafael Braga   - A61799
 *
 *  @bug ?
 *  @version 2.2
 */

#ifndef iterator_h
	#define iterator_h

	#include <stdbool.h>


	typedef struct iterator* Iterator; /* Iterador. */


	/**
	 *  @brief Inicializa o iterador.
	 *
	 *  Aloca espaço para o iterador. Guarda a informação do tamanho de um
	 *  elemento a guadar no iterador (em bytes), bem como a função para realizar
	 *  a impressão de um elemento do iterador.
	 *  O iterador é alocado com uma capacidade inicial suficiente para armazenar
	 *  vários elementos sem ter que se voltar a alocar mais espaço.
	 *
	 *  @param size  Tamanho (em bytes) de um elemento a armazenar no iterador.
	 *  @param print Função para realizar a impressão de um elemento do iterador.
	 *  @return Retorna um novo iterador com capacidade para armazenar vários
	 *          elementos. Todas as suas posição são inicializadas a NULL.
	 */
	Iterator createIterator(const unsigned int value_size,
	                        void (*print)(const void*));


	/**
	 *  Liberta a memória de todo o iterador, bem como cada um dos seus
	 *  elementos. Se o iterador for nulo a função não tem efeito.
	 *
	 *  @param it Apontador para o iterador.
	 *  @return Void.
	 */
	void destroyIterator(Iterator it);


	/**
	 *  Devolve o tamanho do iterador. O tamanho pode não corresponder à
	 *  capacidade total do iterador, mas sim ao número total de elementos
	 *  existem neste.
	 *
	 *  @param it Apontador para o iterador.
	 *  @return Número de elementos do iterador.
	 */
	unsigned int getSizeIterator(Iterator it);


	/**
	 *  Devolve o índice correspondente à última consulta no iterador.
	 *
	 *  @param it Apontador para o iterador.
	 *  @return Índice atual do iterador.
	 */
	unsigned int getIndexIterator(Iterator it);


	/**
	 *  Devolve a próxima posição do iterador caso esta exista.
	 *  A posição é guardada em it.
	 *
	 *  @param it Apontador para o iterador.
	 *  @return void.
	 */
	void nextIterator(Iterator it);


	/**
	 *  Devolve a posição anterior do iterador caso esta exista.
	 *  A posição é guardada em it.
	 *
	 *  @param it Apontador para o iterador.
	 *  @return void.
	 */
	void prevIterator(Iterator it);


	/**
	 *  Navega para uma dada posição do iterador, caso esta seja válida.
	 *  A posição é guardada em it.
	 *
	 *  @param it    Apontador para o iterador.
	 *  @param index Índice pretendido do iterador.
	 *  @return Void.
	 */
	void goToIterator(Iterator it, const unsigned int index);


	/**
	 *  Altera a função para apagar um elemento do iterador. Esta função só é
	 *  necessária caso os elementos a guardar no iterador sejam estruturas de
	 *  dados complexas. Para tipos básicos o iterador fornece uma função por
	 *  defeito que resolve o problema.
	 *
	 *  @param it     Apontador para o iterador.
	 *  @param delete Função para apagar um elemento do iterador.
	 *  @return Void.
	 */
	void setDeleteIterator(Iterator it, void (*delete)(void *value));


	/**
	 *  @brief Adiciona um elemento ao iterador.
	 *
	 *  Adiciona um elemento ao iterador. Caso o iterador tenha atingido a
	 *  capacidade máxima a sua cacidade é duplicada.
	 *
	 *  @param it    Apontador para o iterador.
	 *  @param value Valor a adicionar ao iterador.
	 *  @return Devolve o iterador.
	 */
	Iterator addIterator(Iterator it, const void *value);


	/**
	 *  @brief Adiciona um iterador a outro iterador.
	 *
	 *  Adiciona todo o conteudo do iterador source ao iterador dest.
	 *  Se dest já contiver elementos os elementos são adicionados no fim deste
	 *  iterador. Se dest não contiver elementos então dest é inicializado como
	 *  sendo do mesmo tipo de source. Os elementos a serem armazenados em dest
	 *  são cópias dos elementos de source.
	 *
	 *  @param dest   Apontador para o iterador onde se pretende adicionar
	 *                outro iterador.
	 *  @param source Iterador a acrescentar.
	 *  @return Void. O resultador da adição é guardado em it.
	 */
	Iterator addCollectionIterator(Iterator dest, Iterator source);


	/**
	 *  Testa se o iterador tem algum elemento seguinte relativamente ao
	 *  último elemento consultado neste.
	 *
	 *  @param it Apontador para o iterador.
	 *  @return true caso exista algum elemento seguinte ou false caso contrário.
	 */
	bool hasNextIterator(const Iterator it);


	/**
	 *  Testa se o iterador tem algum elemento anterior relativamente ao
	 *  último elemento consultado neste.
	 *
	 *  @param it Apontador para o iterador.
	 *  @return true caso exista algum elemento anterior ou false caso contrário.
	 */
	bool hasPrevIterator(const Iterator it);


	/**
	 *  @brief Constrói uma qualquer estrutura de dados a partir de todos os
	 *         elementos do iterador.
	 *
	 *  Aplica uma função f a cada elemento deste iterador.
	 *  A função f recebida irá receber como parâmetro um elemento da iterador e
	 *  um acumulador, podendo acrescentar-se algo a este.
	 *  O acumulador deve ser previamente inicializado.
	 *
	 *  @param it  Apontador para a árvore.
	 *  @param acc Acumulador onde se prentende guardar uma qualquer estrutura
	 *             de dados.
	 *  @param f   Função que recebe como parâmetros um elemento do iterador e
	 *             um acumulador, podendo-se acrescentar algo ao mesmo.
	 *  @return Void. O resultado é guardado em acc.
	 */
	void foldIterator(const Iterator it, void *acc,
	                  void (*f)(const void *value, void *acc));


	/**
	 *  Faz a impressão do elemento relativamente à última consulta no iterador.
	 *
	 *  @param it Apontador para o iterador.
	 *  @return Void.
	 */
	void printCurrentIterator(const Iterator it);


	/**
	 *  Faz a impressão de todos os elementos do iterador.
	 *
	 *  @param it Apontador para o iterador.
	 *  @return Void.
	 */
	void printAllIterator(const Iterator it);


	/**
	 *  Faz a impressão de uma determinada posição do iterador.
	 *
	 *  @param it    Apontador para o iterador.
	 *  @param index Posição do iterador que se pretende realizar a impressão.
	 *  @return Void.
	 */
	void printAtIterator(const Iterator it, const unsigned int index);

#endif
