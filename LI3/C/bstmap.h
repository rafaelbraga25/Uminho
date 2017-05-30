/**
 *  @file bstmap.h
 *  @brief Protótipos de funções de uma BSTMap (Árvore binária de procura com
 *         chaves).
 *
 *  O tipo de dados implementado corresponde a uma BSTMap (Árvore binária
 *  de procura com chaves). Cada nó desta estrutura de dados contém uma chave
 *  e uma BST (árvore binária de procura do tipo AVL). Cada chave é única.
 *  As chaves servem de mapeamento entre um qualquer tipo de dados key e
 *  um outro qualquer tipo de dados value a ser guardado na BST correspondente
 *  a essa chave.
 *  A inserção de um elemento nesta estrutura de dados funciona da seguinte
 *  forma:
 *  	i)   Começa-se por testar se a chave existe.
 *  	ii)  Se a chave não existir então é criado um novo nó com a nova chave
 *  	     e com uma nova BST correspondente a esta chave incializada com
 *  	     o valor que se pretente adicionar.
 *  	iii) Se a chave já existir apenas é adicionado o valor à BSTree
 *  	     correspondente.
 *
 *  Embora cada nó contenha uma chave e uma BST, a maneira como as chaves
 *  estão organizadas nesta estrutura de dados é também uma BST do tipo AVL.
 *
 *  @author Carlos Pereira - A61887
 *  @author Diogo Silva    - A76407
 *  @author Rafael Braga   - A61799
 *
 *  @bug ?
 *  @version 3.2
 */

#ifndef bstmap_h
	#define bstmap_h

	#include <stdbool.h>
	#include "bstree.h"            /* O módulo da BSTree é necessário. */


	typedef struct bstMap* BSTMap; /* Apontador para uma BSTMap. */


	/**
	 *  @brief Inicia o tipo concreto de dados.
	 *
	 *  Recebe toda a informação necessária para a implementação do tipo concreto
	 *  de dados. Como se trata de uma estrutura genérica, é necessário guardar
	 *  uma função de comparação entre elementos que ajudam as funções de adição,
	 *  remoção e procura de elementos na BSTMap, bem como uma função responsável
	 *  pela impressão de um nó no ecrã. É também necessário saber o tamanho
	 *  em bytes do tipo de elementos que se pretende armazenar.
	 *
	 *  @param key_size    Tamanho que uma chave ocupa (em bytes).
	 *  @param cmpKey      Função de comparação entre duas chaves.
	 *  @param printKey    Função para realizar a impressão de uma chave.
	 *  @param value_size  Tamanho que um elemento ocupa (em bytes).
	 *  @param cmpValue    Função de comparação entre elementos.
	 *  @param printValue  Função para realizar a impressão de um elemento.
	 *  @return  Devolve o apontador para a BSTMap.
	 */
	BSTMap createBSTMap(const unsigned int key_size,
	                    int (*cmpKey)(const void *a, const void *b),
	                    void (*printKey)(const void *key),
	                    const unsigned int value_size,
	                    int (*cmpValue)(const void *a, const void *b),
	                    void (*printValue)(const void *value));


	/**
	*  Liberta toda a memória da BSTMap.
	*
	*  @param bstm  Apontador para a árvore.
	*  @return  Void.
	*/
	void destroyBSTMap(BSTMap bstm);


	/**
	 *  Altera a função para comparar duas chaves da BSTMap.
	 *
	 *  @param bstm  Apontador para a árvore.
	 *  @param cmp   Função fornecida para efetuar uma comparação entre chaves.
	 *  @return  Void. O resultado é guardado em bstm.
	 */
	void setCmpBSTMap(BSTMap bstm, int (*cmp)(const void *a, const void *b));


	/**
	 *  Altera a função para realizar a impressão de uma chave da BSTMap.
	 *
	 *  @param bstm   Apontador para a árvore.
	 *  @param print  Função fornecida para fazer a impressão de uma chave.
	 *  @return  Void. O resultado é guardado em bstm.
	 */
	void setPrintBSTMap(BSTMap bstm, void (*print)(const void *key));


	/**
	 *  Altera a função para apagar uma chave da BSTMap.
	 *
	 *  @param bstm    Apontador para a árvore.
	 *  @param delete  Função fornecida para apagar a chave de um nó.
	 *  @return  Void. O resultado é guardado em bstm.
	 */
	void setDeleteBSTMap(BSTMap bstm, void (*delete)(void*));


	/**
	 *  Altera a função para comparar dois valores de uma BSTree.
	 *
	 *  @param bstm  Apontador para a árvore.
	 *  @param cmp   Função fornecida para efetuar uma comparação entre valores.
	 *  @return  Void. O resultado é guardado em bstm.
	 */
	void setCmpValueBSTMap(BSTMap bstm,
	                       int (*cmp)(const void *a, const void *b));


	/**
	 *  @brief Altera a função para realizar a impressão de um valor da BST.
	 *
	 *  Essa função é guardada na BSTMap para ser utilizada como argumento
	 *  na criação de uma BSTree.
	 *
	 *  @param bstm   Apontador para a árvore.
	 *  @param print  Função fornecida para fazer a impressão de um valor da BST.
	 *  @return  Void. O resultado é guardado em bstm.
	 */
	void setPrintValueBSTMap(BSTMap bstm, void (*print)(const void *key));


	/**
	 *  Altera a função para fazer a libertação de memória de um valor da BST.
	 *
	 *  @param bstm    Apontador para a árvore.
	 *  @param delete  Função fornecida para apagar um valor de uma BST.
	 *  @return  Void. O resultado é guardado em bstm.
	 */
	void setDeleteValueBSTMap(BSTMap bstm, void (*delete)(void*));


	/**
	 *  @brief Adiciona uma chave e um elemento à BSTMap caso esta exista.
	 *
	 *  A BSTMap tem de ser previamente inicializada.
	 *  Em cada nó da BSTMap além de uma chave existe também um apontador
	 *  para uma BST. É utilizada a cmpKey para comparar duas chaves.
	 *  Caso já exista a chave, é adicionado um valor à BST desse nó.
	 *  Caso contrário, é criado um nó com essa chave e uma BST com esse valor.
	 *
	 *  @param bstm   Apontador para a árvore.
	 *  @param key    Chave a adicionar (à BSTMap).
	 *  @param value  Valor a adicionar (à BST).
	 *  @return  Devolve o apontador para a árvore.
	 */
	BSTMap addBSTMap(BSTMap bstm, const void * key, const void *value);


	/**
	 *  @brief Procura por uma chave na árvore.
	 *
	 *  A BSTMap deve ter sido previamente inicializada, caso contrário não se
	 *  faz a procura.
	 *  É utilizada a cmpKey ao percorrer a àrvore.
	 *
	 *  @param bstm  Apontador para a árvore.
	 *  @param key   Chave a procurar.
	 *  @return  false caso a árvore ou a chave não existam.
	 *           true caso contrário.
	 */
	bool containsKeyBSTMap(const BSTMap bstm, const void *key);


	/**
	 *  @brief Procura por um valor nas BST.
	 *
	 *  @param bstm   Apontador para a árvore.
	 *  @param key    Chave correspondente ao elemento a procurar.
	 *  @param value  Valor a procurar.
	 *  @return  false caso a BSTMap ou o elemento não existam.
	 *           true caso contrário.
	 */
	bool containsValueBSTMap(const BSTMap bstm, const void *key,
	                         const void *value);


	/**
	 *  @brief Faz o map de uma função a todas as chaves da BSTMap.
	 *
	 *  @param bstm  Apontador para a árvore.
	 *  @param f     Função a aplicar a todas as chaves.
	 *  @return  Void. O resultado é guardado em bstm.
	 */
	void mapKeyBSTMap(const BSTMap bstm, void (*f)(void *key));


	/**
	 *  @brief Faz o map de uma função a todos os valores das BST de uma chave
	 *         contida na BSTMap.
	 *
	 *  @param bstm  Apontador para a árvore.
	 *  @param key   Chave a procurar na BSTMap.
	 *  @param f     Função a aplicar a todas os valores das BST.
	 *  @return  Void. O resultado é guardado em bstm.
	 */
	void mapValueBSTMap(const BSTMap bstm, const void *key,
	                    void (*f)(void *value));


	/**
	 *  @brief Faz o fold de uma função com acumulador a todos os valores das
	 *         BST.
	 *
	 *  @param bstm  Apontador para a árvore.
	 *  @param acc   Acumulador da função f.
	 *  @param f     Função a aplicar a todas os valores das BST.
	 *  @return  Void. O resultado é guadado em acc.
	 */
	void foldBSTMap(const BSTMap bstm, void *acc,
	                void (*f)(const void *value, void *acc));


	/**
	 *  @brief Faz o fold de uma função com acumulador a todas as chaves da
	 *         BSTMap.
	 *
	 *  @param bstm  Apontador para a árvore.
	 *  @param acc   Acumulador da função f.
	 *  @param f     Função a aplicar a todas as chaves da BSTMap.
	 *  @return  Void. O resultado é guardado em acc.
	 */
	void foldKeyBSTMap(const BSTMap bstm, void *acc,
	                   void (*f)(const void *key, void *acc));


	/**
	 *  Faz o fold de uma função com acumulador a todos os valores de uma
	 *  BST de uma chave contida na BSTMap.
	 *
	 *  @param bstm  Apontador para a árvore.
	 *  @param key   Chave a procurar na BSTMap.
	 *  @param acc   Acumulador da função f.
	 *  @param f     Função a aplicar a todas os valores da BST.
	 *  @return  Void. O resultado é guardado em acc.
	 */
	void foldValueBSTMap(const BSTMap bstm, const void *key, void *acc,
	                     void (*f)(const void *value, void *acc));



	/**
	*  @brief Faz o fold de uma função com acumulador a todos os valores de
	*         de todas as BSTrees de uma BSTMap.
	*
	*  A cada valor é possível realizar-se operações com um predicado e com a
	*  chave a que esse valor corresponde.
	*
	*  @param bstm  Apontador para a árvore.
	*  @param acc   Acumulador da função f.
	*  @param pred  Predicado a aplicar a cada nó de uma BSTree.
	*  @param f     Função a aplicar a todos os valores da BST.
	*  @return  Void. O resultado é guardado em acc.
	*/
	void foldKeyValueWithBSTMap(const BSTMap bstm, void *acc, const void *pred,
	                            void (*f)(const void *key, const void *value,
	                                      const void *pred, void *acc));


	/**
	 *  @brief Faz a impressão da BSTMap caso esta exista.
	 *
	 *  Faz a impressão de uma chave e de seguida de todos os valores da
	 *  BST apontada. O impressão segue uma travessia pré ordem.
	 *  Faz o mesmo procedimento para as chaves restantes.
	 *  A função printKey e printValue decidem a forma como a informação
	 *  deve ser apresentada.
	 *  Para uma BSTMap vazia a função não tem efeito.
	 *
	 *  @param bstm  Apontador para a árvore, contém a função cmpKey e a
	 *               função printKey.
	 *  @return  Void.
	 */
	void preOrderBSTMap(const BSTMap bstm);


	/**
	 *  @brief Faz a impressão da BSTMap caso esta exista. A impressão é feita
	 *         com os elementos por ordem crescente.
	 *
	 *  Faz a impressão da árvore realizando uma travessia em ordem.
	 *  A impressão é feita conforme a função print da BSTMap e BSTree
	 *  recebidas.
	 *  Se a árvore não contiver quaisquer elementos, a função não tem efeito.
	 *
	 *  @param bstm  Apontador para a árvore.
	 *  @return  Void.
	 */
	void inOrderBSTMap(const BSTMap bstm);


	/**
	 *  @brief Faz a impressão da BSTMap caso esta exista. A impressão é feita
	 *         por ordem decrescente.
	 *
	 *  Faz a impressão da árvore, realizando uma travessia pós ordem.
	 *  A impressão é feita conforme as funções recebidas.
	 *  Se a árvore não contiver quaisquer elementos a função não tem efeito.
	 *
	 *  @param bstm  Apontador para a árvore.
	 *  @return  Void.
	 */
	void postOrderBSTMap(const BSTMap bstm);


	/**
	 *  @brief Procura um nó da BSTMap com chave key. Converte para o iterador a
	 *         BST apontada por esse nó.
	 *
	 *  @param bstm  Apontador para a árvore.
	 *  @param key   Chave a procurar nos nós da BSTMap.
	 *  @return  Iterador com os elementos da BST apontada pelo nó (da BSTMap)
	 *           de chave key.
	 */
	Iterator toIteratorValuePosOrderBSTMap(const BSTMap bstm, const void *key);

#endif
