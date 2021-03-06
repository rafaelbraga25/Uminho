/**
 *  @file bstree.h
 *  @brief Protótipos das funções da árvore binária de procura do tipo AVL.
 *
 *  A árvore está preparada para armazenar qualquer tipo de dados. Deve ser
 *  fornecida uma função que permite determinar se um elemento é maior ou menor
 *  que outro, bem como o tamanho dos elementos a guardar e uma função de
 *  impressão de um elemento da árvore.
 *
 *  @author Carlos Pereira - A61887
 *  @author Diogo Silva    - A76407
 *  @author Rafael Braga   - A61799
 *
 *  @bug ?
 *  @version 3.1
 */

#ifndef bstree_h
	#define bstree_h

	#include <stdbool.h>
	#include "iterator.h"


	typedef struct bstree* BSTree; /* Apontador para uma árvore binária. */

	/**
	 *  @brief Inicializa a BSTree.
	 *
	 *  Aloca espaço para a raiz da árvore binária. Guarda a informação do
	 *  tamanho (em bytes) dos dados a serem guardados na árvore, da função que
	 *  compara dois elementos desta árvore e da função que faz a impressão de um
	 *  elemento no ecrã.
	 *  A função de comparação deverá ser do género:
	 *  	i) se (a > b) devolve 1,
	 *  	ii) senão se (b < a) devolve -1,
	 *  	iii) senão devolve 0.
	 *
	 *  A árvore armazena os valores maiores à direita e os menores à esquerda.
	 *
	 *  @param value_size Tamanho dos elementos a serem armazenados.
	 *  @param cmp        Função de comparação entre dois dados da árvore.
	 *  @param print      Função para realizar a impressão de um dado da árvore.
	 *  @return Apontador para a árvore.
	 */
	BSTree createBSTree(const unsigned int value_size,
	                    int (*cmp)(const void *a, const void *b),
	                    void (*print)(const void *value));


	/**
	 *  Faz o free de cada valor armazenado na árvore, assim como a estrutura
	 *  deste. Se a árvore for nula a função não tem efeito.
	 *
	 *  @param bst Apontador para a árvore.
	 *  @return Void.
	 */
	void destroyBSTree(BSTree bst);


	/**
	 *  Faz o free de cada valor armazenado na árvore, assim como a estrutura
	 *  deste. Se a árvore for nula a função não tem efeito.
	 *
	 *  @param bst Apontador para a árvore.
	 *  @return Altura da árvore ou 0 caso a árvore não contenha elementos.
	*/
	unsigned int getHeightBSTree(const BSTree bst);


	/**
	 *  Devolve o número de nós da árvore.
	 *
	 *  @param bst Apontador para a árvore.
	 *  @return Retorna o número de nós da árvore ou zero caso esta não
	 *          exista ou não contenha nenhum nó.
	 */
	unsigned int getSizeBSTree(const BSTree bst);


	/**
	 *  Devolve o elemento mais à esquerda da árvore, ou seja, o seu
	 *  mínimo.
	 *
	 *  @param bst Apontador para a árvore.
	 *  @return Retorna NULL caso a árvore não tenha sido criada e
	 *          o elemento caso contrário.
	 */
	void* getMinBSTree(const BSTree bst);


	/**
	 *  Devolve o elemento mais à direita da árvore, ou seja, o seu máximo.
	 *
	 *  @param bst Apontador para a árvore.
	 *  @return Retorna NULL caso a árvore não tenha sido criada e o elemento
	 *          caso contrário.
	 */
	void* getMaxBSTree(const BSTree bst);


	/**
	 *  Altera a função de comparação entre dois elementos da árvore.
	 *
	 *  @param bst Apontador para a árvore.
	 *  @param cmp Função para comparar dois valores da árvore.
	 *  @return Void.
	 */
	void setCmpBSTree(BSTree bst, int (*cmp)(const void *a, const void *b));


	/**
	 *  Altera a função para realizar a impressão de um elemento.
	 *
	 *  @param bst   Apontador para a árvore.
	 *  @param print Função para realizar a impressão de um elemento.
	 *  @return Void.
	 */
	void setPrintBSTree(BSTree bt, void (*print)(const void *value));


	/**
	 *  @brief Altera a função para apagar um elemento de um nó.
	 *
	 *  Só é necessário realizar esta operação caso os elementos a guardar sejam
	 *  estruturas complexas de dados.
	 *  Ex: Uma estrutura em que um dos seus campos é um array dinâmico.
	 *
	 *  @param bst    Apontador para a árvore.
	 *  @param delete Função para apagar um elemento.
	 *  @return Void.
	 */
	void setDeleteBSTree(BSTree bst, void (*delete)(void *value));


	/**
	 *  @brief Adiciona um elemento à árvore.
	 *
	 *  Se a árvore foi previamente inicializada adiciona um elemento a esta.
	 *  Este é adicionado conforme a função de comparação presente.
	 *
	 *  @param bst Apontador para a árvore.
	 *  @param value Valor a adicionar.
	 *  @return Devolve o apontador para a árvore.
	 */
	BSTree addBSTree(BSTree bst, const void *value);


	/**
	 *  @brief Adiciona um elemento à árvore com uma condição.
	 *
	 *  Adiciona um elemento à árvore caso esta exista. Se o elemento a
	 *  adicionar não existir na árvore é adicionado normalmente.
	 *  Senão é chamada uma função para tratar de elementos repetidos.
	 *
	 *  @param bst       Apontador para a árvore.
	 *  @param new_value Valor a adicionar.
	 *  @param f         Função para tratar de elementos repetidos. Recebe como
	 *                   primeiro parâmetro o elemento já existente e como
	 *                   segundo parâmetro o elemento a adicionar. A função
	 *                   pode modificar o elemento já existente na árvore.
	 *  @return Devolve o apontador para a árvore.
	 */
	BSTree addWithCondBSTree(BSTree bst, const void *new_value,
	                         void (*f)(void *acc, const void *new_value));


	/**
	 *  @brief Verifica se a existe um determinado elemento na árvore.
	 *
	 *  Procura por value na árvore caso esta tenha sido previamente
	 *  inicializada. A função de procura segue o critério da função de
	 *  comparação fornecida anteriormente.
	 *
	 *  @param bst   Apontador para a árvore.
	 *  @param value Valor a procurar na árvore.
	 *  @return Retorna true caso o elemento exista na árvore ou false
	 *          caso contrário.
	 */
	bool containsBSTree(const BSTree bst, const void *value);


	/**
	 *  @brief Verifica se um elemento satisfaz uma dada condição.
	 *
	 *  Percorre a árvore e invoca a função f para testar se um elemento
	 *  satisfaz uma certa condição. A função termina assim que qualquer
	 *  elemento satisfaça a condição recebida.
	 *
	 *  @param bst  Apontador para a árvore.
	 *  @param pred Predicado para comparar com os elementos da árvore.
	 *  @param f    Função que recebe uma certa condição a testar. Recebe como
	 *              primeiro parâmetro um elemento da árvore e como segundo
	 *              parâmetro um predicado para se efetuar uma comparação
	 *              com o elemento.
	 *  @return true caso algum elemento satisfaça f ou false caso contrário.
	 */
	bool anyValueMatch(const BSTree bst, const void *pred,
	                   bool (*f)(const void *value, const void *pred));


	/**
	 *  @brief Remove um elemento da árvore.
	 *
	 *  Remove um elemento da árvore caso este exista e caso a árvore
	 *  tenha sido inicializada. A procura pelo elemento segue o critério da
	 *  função de comparação fornecida.
	 *
	 *  @param bst   Apontador para a árvore.
	 *  @param value Valor a ser removido da árvore.
	 *  @return Void.
	 */
	void delBSTree(BSTree bst, const void *value);


	/**
	 *  @brief Aplica uma função a todos os elementos da árvore.
	 *
	 *  Recebe uma função f a ser aplicada a todos os elementos.
	 *  A função pode alterar o conteúdo dos elementos da árvore, mas não deve
	 *  alterar os seus tipos.
	 *
	 *  @param bst Apontador para a árvore.
	 *  @param f   Função para realizar uma certa operação sobre um elemento.
	 *  @return Void.
	 */
	void mapBSTree(const BSTree bst, void (*f)(void *value));


	/**
	 *  @brief Constrói uma qualquer estrutura de dados a partir de todos os
	 *         elementos da árvore binária.
	 *
	 *  Faz uma travessia em ordem e aplica uma função f a cada elemento desta
	 *  árvore.
	 *  A função f recebida irá receber como parâmetro um elemento da árvore e
	 *  um acumulador, podendo acrescentar-se algo a este.
	 *  O acumulador deve ser previamente inicializado.
	 *
	 *  @param bst Apontador para a árvore.
	 *  @param acc Acumulador onde se prentende guardar uma qualquer estrutura
	 *             de dados.
	 *  @param f   Função que recebe como parâmetros um elemento da árvore e
	 *             um acumulador, podendo-se acrescentar algo ao mesmo.
	 *  @return Void. O resultado é guardado em acc.
	 */
	void foldBSTree(const BSTree bst, void *acc,
	                void (*f)(const void *value, void *acc));



	/**
	 *  @brief Constrói uma qualquer estrutura de dados a partir de todos os
	 *         elementos da árvore binária.
	 *
	 *  Faz uma travessia em ordem e aplica uma função f a cada elemento desta
	 *  árvore.
	 *  A função f recebida irá receber como parâmetro um elemento da árvore e
	 *  um acumulador, podendo acrescentar-se algo a este.
	 *  Recebe também como parêmtros um valor de dados qualquer, bem como um
	 *  predicado para efetuar operações de comparação.
	 *  O acumulador deve ser previamente inicializado.
	 *
	 *  @param bst   Apontador para a árvore.
	 *  @param acc   Acumulador onde se prentende guardar uma qualquer estrutura
	 *               de dados.
	 *  @param data  Valor de dados.
	 *  @param pred  Predicado.
	 *  @param f     Função a aplicar a cada nó da árvore.
	 *  @return Void. O resultado é guardado em acc.
	 */
	void foldWithBSTree(const BSTree bst, void *acc, const void *data,
	                    const void *pred,
	                    void (*f) (const void *data, const void *value,
	                               const void *pred, void *acc));

	/**
	 *  @brief Faz a impressão da árvore.
	 *
	 *  Faz a impressão da árvore realizando uma travessia pré ordem.
	 *  A impressão é realizado conforme a função print recebida.
	 *  Se a árvore não contiver quaisquer elementos, a função não tem efeito.
	 *
	 *  @param bst Apontador para a árvore.
	 *  @return Void.
	 */
	void preOrderBSTree(const BSTree bst);


	/**
	 *  @brief Faz a impressão da árvore.
	 *
	 *  Faz a impressão da árvore realizando uma travessia em ordem.
	 *  A impressão é realizado conforme a função print recebida.
	 *  Se a árvore não contiver quaisquer elementos, a função não tem efeito.
	 *
	 *  @param bst Apontador para a árvore.
	 *  @return Void.
	 */
	void inOrderBSTree(const BSTree bst);


	/**
	 *  @brief Faz a impressão da árvore.
	 *
	 *  Faz a impressão da árvore realizando uma travessia pós ordem.
	 *  A impressão é realizado conforme a função print recebida.
	 *  Se a árvore não contiver quaisquer elementos, a função não tem
	 *  efeito.
	 *
	 *  @param bst Apontador para a árvore.
	 *  @return Void.
	 */
	void postOrderBSTree(const BSTree bst);


	/**
	 *  Devolve um iterador sobre a árvore binária de procura.
	 *  A ordem dos elementos guardados no iterador corresponde a uma
	 *  travessia em ordem sobre a árvore.
	 *
	 *  @param bst Apontador para a árvore.
	 *  @return Retorna um iterator sobre todos os elementos da árvore binária.
	 */
	Iterator toIteratorInOrderBSTree(const BSTree bst);


	/**
	 *  Devolve um iterador sobre a árvore binária de procura.
	 *  A ordem dos elementos guardados no iterador corresponde a uma
	 *  travessia pós ordem sobre a árvore.
	 *
	 *  @param bst Apontador para a árvore.
	 *  @return Retorna um iterator sobre todos os elementos da árvore binária.
	 */
	Iterator toIteratorPostOrderBSTree(const BSTree bst);


	/**
	 *  @brief Devolve um iterador com todos os elementos da árvore que
	 *         satisfaçam a função f recebida.
	 *
	 *  Percorre a árvore numa travessia em ordem e filtra desta para o iterador
	 *  todos os elementos que satisfaçam a função f.
	 *  A função f deve ser do género:
	 *  	Se (value <condição>) == true
	 *  		então retorna verdadeiro
	 *  		senão retorna falso.
	 *
	 *  @param bst  Apontador para a árvore.
	 *  @param f    Função que irá testar se um elemento satisfaz uma determinada
	 *              condição.
	 *  @return Um iterador com todos os elementos que satisfaçam f.
	 */
	Iterator filterBSTree(const BSTree bst, bool (*f)(const void *value));


	/**
	 *  @brief Devolve um iterador com todos os elementos da árvore que
	 *         satisfaçam a função f recebida.
	 *
	 *  Percorre a árvore numa travessia em ordem e filtra desta para o iterador
	 *  todos os elementos que satisfaçam a função f.
	 *  A função f deve ser do género:
	 *  	Se (value <condição> pred) == true
	 *  		então retorna verdadeiro
	 *  		senão retorna falso.
	 *
	 *  @param bst  Apontador para a árvore.
	 *  @param pred Valor que pode servir para efetuar uma comparação entre um
	 *              qualquer elemento da árvore.
	 *  @param f    Função que irá testar se um elemento satisfaz uma determinada
	 *              condição. Recebe como primeiro parâmetro um elemento da
	 *              árvore e como segundo parâmetro um predicado.
	 *  @return Um iterador com todos os elementos que satisfaçam f.
	 */
	Iterator filterWithPredBSTree(const BSTree bst, const void *pred,
	                              bool (*f)(const void *value,
	                                        const void *pred));


	/**
	 *  @brief Adiciona a um iterador já existente todos os elementos da árvore
	 *         que satisfaçam a função f recebida.
	 *
	 *  Percorre a árvore numa travessia em ordem e filtra desta para o iterador
	 *  recebido todos os elementos que satisfaçam a função f.
	 *
	 *  A função f deve ser do género:
	 *  	Se (value <condição> pred) == true
	 *  		então retorna verdadeiro
	 *  		senão retorna falso.
	 *
	 *  @param bst  Apontador para a árvore.
	 *  @param it   Iterador que irá conter todos os elementos que satisfaçam f.
	 *              Os novos elementos serão adicionados aos elementos de it.
	 *  @param f    Função que irá testar se um elemento satisfaz uma determinada
	 *              condição. Recebe como primeiro parâmetro um elemento da
	 *              árvore e como segundo parâmetro um predicado.
	 *  @return Void. Os elementos que satisfaçam f são guardados em it.
	 */
	void filterToIteratorBSTree(const BSTree bst, Iterator it,
	                            bool (*f)(const void *value));

#endif
