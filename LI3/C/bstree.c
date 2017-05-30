/**
 *  @file bstree.c
 *  @brief Uma árvore binária de procura do tipo AVL.
 *
 *  Definição de todas as funções pertencentes à interface deste módulo, bem
 *  como todos os métodos auxiliares.
 *
 *  @author Carlos Pereira - A61887
 *  @author Diogo Silva    - A76407
 *  @author Rafael Braga   - A61799
 *
 *  @bug ?
 *  @version 3.1
 */

#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "bstree.h"

/* Tipo de um nodo de dados. */

typedef struct node {
	void *value;          /* Valor a adicionar à arvore. */
	unsigned char height; /* Altura da árvore.
	                       * NOTA: A altura de uma árvore com cerca de 10G de
	                       * elementos é 44, pelo que valores entre 0 e 255
	                       * chegam para armazenar a altura de uma árvore com
	                       * biliões de elementos. Ao armazenar este valor num
	                       * inteiro estaríamos a gastar 4 vezes mais memória
	                       * para este campo, o que é desnecessário. */
	struct node *left;    /* Sub-árvore à esquerda. */
	struct node *right;   /* Sub-árvore à direita. */
} Node;


/* Tipo concreto de BSTree. */

struct bstree {
	Node *root;                           /* Raiz da árvore. */
	unsigned int value_size;              /* Tamanho de cada elemento a
	                                       * adicionar na árvore. */
	unsigned int num_nodes;               /* Número de nós da árvore. */
	int (*cmp)(const void*, const void*); /* Função para efetuar a comparação
	                                       * entre dois elementos. */
	void (*print)(const void*);           /* Função para realizar a impressão de
	                                       * um elemento no ecrã. */
	void (*delete)(void*);                /* Função para apagar um elemento de
	                                       * um nó. Por defeito esta função será
	                                       * a função defaultDestroy que
	                                       * apaga todo o tipo de dados básicos.
	                                       * Para apagar tipos mais complexos,
	                                       * como por exemplo um array de
	                                       * qualquer tipo de dados, deve-se
	                                       * fornecer uma função o apagar. */
};


/*****************************************************************************
 * BEGIN PRIVATE                                                             *
 *****************************************************************************/

/*****************************************************************************
 * BEGIN CONSTRUCTORS AND DESTRUCTORS                                        *
 *****************************************************************************/

/**
 *  @brief Inicia um nó da árvore.
 *
 *  Aloca espaço para um nó. Inicia cada elemento desse nó conforme os
 *  os valores dos argumentos recebidos. Como os dados são guardados em void*
 *  tem que se alocar o tamanho (em bytes) do valor a ser adicionado. A função
 *  memcpy transfere byte a byte o conteúdo de value para root->value.
 *  A função trata de erros a nível de memória caso a alocação desta falhe por
 *  algum motivo.
 *
 *  @param value       Valor a ser adicionado à árvore.
 *  @param value_size  Tamanho que esse valor ocupa (em bytes).
 *  @return  Devolve o novo nó.
 */
static Node* createNode(const void *value, const unsigned int value_size)
{
	Node *root = malloc(sizeof(Node)); /* Aloca espaço para um novo nó da
	                                    * árvore. */

	if (root == NULL) {

		/* Se o malloc falhar tenta-se fazer o realoc. */

		root = realloc(root, sizeof(Node));

		/* Caso root seja NULL após o realloc então o programa é abortado. */

		assert(root != NULL);
	}

	/* Faz o malloc para um valor de um nó. */

	root->value = malloc(value_size);

	if (root->value == NULL) {

		/* Testa se a realocação para um valor de um novo nó tem sucesso.
		 * Em caso de insucesso o programa é terminado. */

		root->value = realloc(root->value, value_size);
		assert(root->value != NULL);
	}

	memcpy(root->value, value, value_size);

	root->height = 1;   /* A altura de um nó sem filhos é 1. */
	root->left = NULL;
	root->right = NULL;

	return root;
}


/**
 *  Liberta a memória de todos os elementos da árvore.
 *
 *  @param bst   Apontador para a árvore.
 *  @param root  Raiz da árvore.
 *  @return  Void.
 */
static void destroyNode(BSTree bst, Node *root)
{

	/* Só remove um nó se este não for vazio. */

	if (root != NULL) {
		destroyNode(bst, root->left);
		destroyNode(bst, root->right);

		/* Liberta o apontador genérico de dados. */

		bst->delete(root->value);
	}

	/* No final remove a estrutura completamente. */

	free(root);
	root = NULL;
}

/*****************************************************************************
 * END CONSTRUCTORS AND DESTRUCTORS                                          *
 *****************************************************************************/


/*****************************************************************************
 * BEGIN GETS AND SETS                                                       *
 *****************************************************************************/

/**
 *  @brief Devolve a altura da árvore.
 *
 *  A altura é guardada previamente em cada nó. Esta função não efetua
 *  qualquer travessia na árvore.
 *
 *  @param root  Nó em que se pretende saber a altura.
 *  @return  Devolve 0 caso o nó recebido não exista ou a sua altura caso
 *           contrário.
 */
static unsigned char getHeightNode(const Node *root)
{
	unsigned char h = (root != NULL) ? root->height : 0;

	return h;
}


/**
 *  Devolve o mínimo da árvore, ou seja, o seu elemento mais à esquerda.
 *
 *  @param root  Raiz da árvore.
 *  @return  Valor mínimo da árvore.
 */
static void* getMinNode(Node *root)
{
	Node *temp = root; /* Nó auxiliar para efetuar a travessia na árvore. */

	while (temp != NULL) {
		if (temp->left == NULL) {
			break;
		}
		temp = temp->left;
	}

	return temp->value;
}


/**
 *  Devolve o máximo da árvore, ou seja, o seu elemento mais à direita.
 *
 *  @param root  Raiz da árvore.
 *  @return  Valor máximo da árvore.
 */
static void* getMaxNode(Node *root)
{
	Node *temp = root; /* Nó auxiliar para efetuar a travessia na árvore. */

	while (temp != NULL) {
		if (temp->right == NULL) {
			break;
		}
		temp = temp->right;
	}

	return temp->value;
}


/**
 *  @brief Devolve o fator de balanceamento da árvore.
 *
 *  O cálculo do fator baseia-se em substrair a altura da sub-árvore da
 *  esquerda à altura da sub-árvore da direita.
 *
 *  @param root  Nó onde se pretende calcular o fator.
 *  @return  Subtração entre as alturas das sub-árvores da direita e da
 *           esquerda.
 */
static int getFactor(const Node *root)
{
	int f = ((int) (getHeightNode(root->right) - getHeightNode(root->left)));

	return f;
}

/*****************************************************************************
 * END GETS AND SETS                                                         *
 *****************************************************************************/


/*****************************************************************************
 * BEGIN BALANCE FUNCTIONS                                                   *
 *****************************************************************************/

/**
 *  @brief Atualiza a altura de um nó da árvore.
 *
 *  Depois de cada rotação é necessário alterar a altura de cada um dos nós
 *  da árvore. Esta função é responsável por esse processo.
 *
 *  @param root  Nó onde se pretende realizar a atualização da sua altura.
 *  @return  Void.
 */
static void recalcHeight(Node *root)
{
	unsigned char hl = getHeightNode(root->left);
	unsigned char hr = getHeightNode(root->right);

	root->height = (unsigned char) (((hl > hr) ? hl : hr) + 1);
}


/**
 *  @brief Faz uma rotação à esquerda.
 *
 *  Sendo A a raiz e x uma sub-árvore.
 *
 *  Caso : A                       B
 *          \                     / \
 *           B      ----->       A   C
 *          / \                  \
 *         x   C                  x
 *
 *  Neste caso mesmo que o nó B contenha uma sub-árvore à sua esquerda,
 *  todos os elmentos dessa sub-árvore são maiores que o nó A.
 *
 *  @param root  Raiz A.
 *  @return  Devolve a nova raiz, neste caso, o nodo B.
 */
static Node* rotateLeft(Node *root)
{
	Node *pivot = root->right; /* Nova raiz. */

	root->right = pivot->left;
	pivot->left = root;

	/* Depois da rotação tem que se atualizar a altura. */

	recalcHeight(root);
	recalcHeight(pivot);

	return pivot;
}


/**
 *  @brief Faz uma rotação à direita.
 *
 *  Sendo A a raiz e x uma sub-árvore.
 *
 *  Caso :   A                   B
 *          /                   / \
 *         B     ------->      B   A
 *        / \                     /
 *       C   x                   x
 *
 *  Neste caso mesmo que o nó B contenha uma sub-árvore à sua direita,
 *  todos os elementos dessa sub-árvore são menores que o nó A.
 *
 *  @param root  Raiz A.
 *  @return  Devolve a nova raiz, neste caso, o nodo B.
 */
static Node* rotateRight(Node *root)
{
	Node *pivot = root->left; /* Nova raiz. */

	root->left = pivot->right;
	pivot->right = root;

	/* Depois da rotação tem que se atualizar a altura. */

	recalcHeight(root);
	recalcHeight(pivot);

	return pivot;
}


/**
 *  @brief Efetua o balanceamento da árvore.
 *
 *  Esta função é chamada após a inserção de um novo elemento na árvore.
 *  Começa-se por calcular a nova altura dos nós das sub-árvores. De seguida,
 *  calcula-se o fator de balanceamento. Um fator compreendido entre -1 e 1
 *  significa que a árvore já se encontra balanceada. Um fator maior que 1
 *  significa que a árvore não é balanceada à sua direita e é aplicada uma
 *  rotação simples, ou dupla, à esquerda conforme o caso. Um fator menor que
 *  -1 significa que a árvore não é balanceada à sua esquerda e é aplicada uma
 *  rotação simples, ou dupla, à direita consoante o caso.
 *
 *  @param root Raiz da árvore.
 *  @return Devolve a nova raiz da árvore, ficando esta balanceada.
 */
static Node* balance(Node *root)
{
	int f = 0;

	recalcHeight(root);

	f = getFactor(root);

	if (f > 1) {
		if (getFactor(root->right) < 0) {

			/*  Rotação dupla à esquerda.
			 *
			 *  Caso:    A            A                   B
			 *            \            \                 / \
			 *             B   --->     B     ---->     A   C
			 *            /              \
			 *           C                C
			 *
			 */

			root->right = rotateRight(root->right);
			root = rotateLeft(root);
		}
		else {
			root = rotateLeft(root);
		}
	}

	if (f < -1) {
		if (getFactor(root->left) > 0) {

			/*  Rotação dupla à direita
			 *
			 *  Caso:      A                A               B
			 *            /                /               / \
			 *           B     ---->      B     ---->     A   C
			 *            \              /
			 *             C            C
			 *
			 */

			root->left = rotateLeft(root->left);
			root = rotateRight(root);
		}
		else {
			root = rotateRight(root);
		}
	}

	return root;
}

/*****************************************************************************
 * END BALANCE FUNCTIONS                                                     *
 *****************************************************************************/


/*****************************************************************************
 * BEGIN ADD, SEARCH AND REMOVE                                              *
 *****************************************************************************/

/**
 *  @brief Adiciona um novo nó à árvore.
 *
 *  A função segue o critério da função de comparação fornecida na criação
 *  da árvore. Caso compare > 0 adiciona o novo elemento à direita. Caso
 *  compare < 0 adiciona o novo elemento à esquerda.
 *
 *  @param bst    Contém a função compare que serve para ordenar a árvore.
 *                Contém tambem o tamanho necessário a alocar em memória para
 *                guardar o novo elemento.
 *  @param root   Raiz da árvore.
 *  @param value  Elemento a adicionar na árvore.
 *  @return Retorna a raiz da árvore.
 */
static Node* addNode(const BSTree bst, Node *root, const void * value)
{

	/* Sendo a raiz nula pode-se adicionar um novo elemento. */

	if (root == NULL) {
		root = createNode(value, bst->value_size);

		/* A árvore recebe mais um elemento, logo o seu tamanho é incrementado. */

		bst->num_nodes++;
	}
	else {
		if (bst->cmp(value, root->value) < 0) {

			/* Adiciona à esquerda. */

			root->left = addNode(bst, root->left, value);
		}
		else if (bst->cmp(value, root->value) > 0) {

			/* Adiciona à direira. */

			root->right = addNode(bst, root->right, value);
		}

		/* Depois de se adicionar o novo elemento tem que se efetuar o
		 * balanceamento da árvore.	*/

		root = balance(root);
	}

	return root;
}



/**
 *  @brief Adiciona um novo nó à árvore. Aplica uma função f caso o nó
 *         já exista.
 *
 *  O método de inserção é muito semelhante à função addNode. A única
 *  diferença ocorre quando o resultado da comparação entre elementos for 0.
 *  Ou seja, na tentativa de inserção de um elemento repetido a função f é
 *  chamada. Nesta função o utilizador pode tratar deste tipo de casos.
 *
 *  @param bst    Contém a função compare que serve para ordenar a árvore.
 *                Contém tambem o tamanho necessário a alocar em memória para
 *                guardar o novo elemento.
 *  @param root   Raiz da árvore.
 *  @param value  Elemento a adicionar na árvore.
 *  @param f      Função para tratar de elementos repetidos.
 *  @return Retorna a raiz da árvore.
 */
static Node* addWithCondNode(const BSTree bst, Node *root, const void *value,
                             void (*f)(void *acc, const void *new_value))
{

	/* Sendo a raiz nula pode-se adicionar um novo elemento. */

	if (root == NULL) {
		root = createNode(value, bst->value_size);

		/* A árvore recebe mais um elemento, logo o seu tamanho é incrementado. */

		bst->num_nodes++;
	}
	else {
		if (bst->cmp(value, root->value) < 0) {

			/* Adiciona à esquerda. */

			root->left = addWithCondNode(bst, root->left, value, f);
		}

		/* Adiciona à direira. */

		else if (bst->cmp(value, root->value) > 0) {

			/* Adiciona à direira. */

			root->right = addWithCondNode(bst, root->right, value, f);
		}
		else {

			/* O elemento já existe, logo a função f que trata estes casos é
			 * invocada. */

			f(root->value, value);
		}

		/* Depois de se adicionar o novo elemento tem que se efetuar o
		 * balanceamento da árvore.	*/

		root = balance(root);
	}

	return root;
}


/**
 *  @brief Verifa se um elemento já existe na árvore.
 *
 *  Efetua a travessia na árvore tendo como critério o resultado da função
 *  compare (comp).
 *
 *  @param bst   Contém informação relativa à função compare.
 *  @param root  Raiz da árvore.
 *  @param value Valor a procurar na árvore.
 *  @return true caso o elemento exista ou false caso contrário.
 */
static bool containsNode(const BSTree bst, const Node *root,
	                       const void *value)
{
	bool b = false; /* Valor é false por defeito, se o elemento for
                     encontrado este é transformado para true. */


	/* Se root for NULL a procura chegou ao fim e o elemento não existe. */

	if (root != NULL) {

	/* Começa-se por testar se o elemento é menor que o valor do nodo.
	 * Se assim for procura-se na sub-árvore à esquerda.	*/

		if (bst->cmp(value, root->value) < 0) {
			b = containsNode(bst, root->left, value);
		}

		/* Se o elemento for maior procura-se na sub-árvore à direira. */

		else if (bst->cmp(value, root->value) > 0) {

			/* Se o elemento for maior procura-se na sub-árvore à direira. */

			b = containsNode(bst, root->right, value);
		}
		else {

			/* O elemento existe na árvore. */

			b = true;
		}
	}

	return b;
}


/**
 *  @brief Verifica se algum elmento da árvore satisfaz uma certa condição.
 *
 *  Percorre toda a árvore e testa a validade de f em cada um dos seus
 *  elementos. Se um elemento verificar f, a função é terminada.
 *
 *  @param root Raiz da árvore.
 *  @param pred Predicado a comparar com um elemento.
 *  @param f    Função para efetuar uma comparação entre um elemento da árvore
 *              e um predicado.
 *  @return true caso algum elemento verificar f ou false caso contrário.
 */
static bool anyValueMatchNode(const Node *root, const void *pred,
                              bool (*f)(const void *value, const void *pred))
{
	bool b = false; /* Valor é false por defeito. */

	if (root != NULL) {

		/* Testa se algum elemento da sub-árvore à esquerda satisfaz f. */

		b = anyValueMatchNode(root->left, pred, f);

		if (b == false) {

			/* Se nenhum elemento da sub-árvore à esquerda verificar então
			 * verifica-se o elemento da raiz. */

			b = f(root->value, pred);

			if (b == false) {

				/* Finalmente, se o elemento da raiz não verificar f é realizado o
				 * teste para os elementos da sub-árvore à direita. */

				b = anyValueMatchNode(root->right, pred, f);
			}
		}
	}

	return b;
}


/**
 *  @brief Apaga um nó da árvore.
 *
 *  A função usa a função compare para realizar a travessia na árvore e
 *  verificar se o elemento que se pretende apagar existe. Caso ele exista,
 *  este é removido da árvore. De seguida reconstroí-se a árvore sem este
 *  elemento.
 *
 *  @param bst   Contém a função compare, bem como o tamanho do elemento.
 *  @param root  Raiz da árvore.
 *  @param value Valor do elemento a ser removido.
 *  @return Devolve a raiz da árvore.
 */
static Node* delNode(const BSTree bst, Node *root, const void *value)
{
	Node *temp = NULL;      /* Nó auxiliar para guardar sub-árvores. */
	void *min_value = NULL; /* Nó mínimo para calcular a nova sub-árvore. */

	/* Procura pelo elementa à esquerda. */

	if (bst->cmp(value, root->value) < 0) {
		root->left = delNode(bst, root->left, value);
	}
	else if (bst->cmp(value, root->value) > 0) {

		/* Procura pelo elemento à direita. */

		root->right = delNode(bst, root->right, value);
	}
	else {
		/* O elemento foi encontrado.
		 * Como um elemento é removido o tamanho da árvore é decrementado. */

		bst->num_nodes--;

		/* Se o elemento não conter nenhuma sub-árvore à esquerda então
		 * a nova raiz é a sua sub-árvore à direita. */

		if (root->left == NULL) {
			temp = root->right;
			free(root->value);
			free(root);
			root = temp;
		}
		else if (root->right == NULL) {

			/* Se o elemento não conter nenhuma sub-árvore à direita então a nova
			 * raiz é a sua sub-árvore à esquerda. */

			temp = root->left;
			free(root->value);
			free(root);
			root = temp;
		}
		else {

			/* Neste caso o elemento a remover contém sub-árvores à esquerda e à
			 * direita. Para a resolução deste caso é necessário calcular a sua nova
			 * raiz. Esta conterá o elemento mínimo da sub-árvore à direita,
			 * pois este é garantidamente maior que todos os elementos da sub-árvore
			 * à esquerda. Efetua-se a cópia desse elemento mínimo para a nova raiz
			 * através da função memcpy e remove-se esse elemento da sub-árvore à
			 * direita. No final é necessário balancear a árvore.	*/

			min_value = getMinNode(root->right);
			memcpy(root->value, min_value, bst->value_size);
			root->right = delNode(bst, root->right, root->value);
			root = balance(root);
		}
	}

	return root;
}

/*****************************************************************************
 * END ADD, SEARCH AND REMOVE                                                *
 *****************************************************************************/




/*****************************************************************************
 * BEGIN TREE TRAVERSALS                                                     *
 *****************************************************************************/

/**
 *  @brief Aplica uma função a todos os elementos da árvore.
 *
 *  Recebe uma função f qualquer e aplica-a a cada elemento da árvore.
 *  A função não deve alterar o tipo de dados guardado nesta árvore.
 *
 *  @param root Raiz da árvore.
 *  @param f    Função a ser aplicada a cada elemento.
 *  @return Void. O valor do novo elemento é retornado em value.
 */
static void mapNode(const Node *root, void (*f)(void *value))
{
	if (root != NULL) {
		mapNode(root->left, f);
		f(root->value);
		mapNode(root->right, f);
	}
}


/**
 *  @brief Devolve uma qualquer estrutura de dados aplicada a todos os elmentos
 *         da árvore.
 *
 *  Recebe uma função f qualquer e aplica-a a cada elemento da árvore. O
 *  resultado da função deve ser devolvido em acc.
 *
 *  @param root Raiz da árvore.
 *  @param acc  Acumulador da nova estrutura de dados.
 *  @param f    Função a ser aplicada a cada elemento para a construção de
 *              uma qualquer estrutura de dados.
 *  @return Void.
 */
static void foldNode(const Node *root, void *acc,
                     void (*f)(const void* value, void *acc))
{
	if (root != NULL) {
		foldNode(root->left, acc, f);
		f(root->value, acc);
		foldNode(root->right, acc, f);
	}
}



/**
 *  @brief Devolve uma qualquer estrutura de dados aplicada a todos os elmentos
 *         da árvore.
 *
 *  Recebe uma função f qualquer e aplica-a a cada elemento da árvore. O
 *  resultado da função deve ser devolvido em acc.
 *
 *  @param root  Raiz da árvore.
 *  @param acc   Acumulador da nova estrutura de dados.
 *  @param data  Valor de dados.
 *  @param pred  Predicado.
 *  @param f     Função a ser aplicada a cada elemento para a construção de
 *               uma qualquer estrutura de dados.
 *  @return Void. O resultado é guardado em acc.
 */
void foldWithNode(const Node *root, void *acc, const void *data,
                  const void *pred,
                  void (*f) (const void *data, const void *value,
                             const void *pred, void *acc))
{
	if (root != NULL) {
		foldWithNode(root->left, acc, data, pred, f);
		f(data, root->value, pred, acc);
		foldWithNode(root->right, acc, data, pred, f);
	}
}


/**
 *  Faz a impressão da árvore.
 *  A impressão é realizado conforme a função print.
 *
 *  @param bst  Contém a função print.
 *  @param root Raiz da árvore.
 *  @return Void.
 */
static void preOrderNode(const BSTree bst, const Node *root)
{
	if (root != NULL) {
		bst->print(root->value);
		preOrderNode(bst, root->left);
		preOrderNode(bst, root->right);
	}
}


/**
 *  Faz a impressão da árvore.
 *  A impressão é realizado conforme a função print.
 *
 *  @param bst Contém a função print.
 *  @param root Raiz da árvore.
 *  @return Void.
 */
static void inOrderNode(const BSTree bst, const Node *root)
{
	if (root != NULL) {
		inOrderNode(bst, root->left);
		bst->print(root->value);
		inOrderNode(bst, root->right);
	}
}


/**
 *  Faz a impressão da árvore.
 *  A impressão é realizado conforme a função print.
 *
 *  @param bst Contém a função print.
 *  @param root Raiz da árvore.
 *  @return Void.
 */
static void postOrderNode(const BSTree bst, const Node *root)
{
	if (root != NULL) {
		postOrderNode(bst, root->left);
		postOrderNode(bst, root->right);
		bst->print(root->value);
	}
}

/*****************************************************************************
 * END TREE TRAVERSALS                                                       *
 *****************************************************************************/



/*****************************************************************************
 * BEGIN DATA STRUCTURES AUXILIARY FUNCTIONS                                 *
 *****************************************************************************/

/**
 *  Devolve um iterador sobre a árvore binária de procura.
 *  A travessia é realizada em ordem.
 *
 *  @param root Raiz da árvore.
 *  @param it   Iterador a ser criado com os elementos da árvore.
 *  @return Void.
 */
static void toIteratorInOrderNode(const Node *root, Iterator it)
{
	if (root != NULL) {
		toIteratorInOrderNode(root->left, it);
		addIterator(it, root->value);
		toIteratorInOrderNode(root->right, it);
	}
}


/**
 *  Devolve um iterador sobre a árvore binária de procura.
 *  A travessia é realizada em pós ordem.
 *
 *  @param root Raiz da árvore.
 *  @param it   Iterador a ser criado com os elementos da árvore.
 *  @return Void.
 */
static void toIteratorPostOrderNode(const Node *root, Iterator it)
{
	if (root != NULL) {
		toIteratorPostOrderNode(root->right, it);
		addIterator(it, root->value);
		toIteratorPostOrderNode(root->left, it);
	}
}


/**
 *  Efetua uma travessia em ordem na árvore. A cada elemento é testado
 *  o valor retornado por f, que tem como parâmtros um elemento da árvore.
 *  Caso f retorne true então o elemento satisfaz uma certa condição,
 *  sendo este adicionado ao iterador.
 *
 *  @param root Raiz da árvore.
 *  @param it   Iterador a ser criado com os elementos filtrados da árvore.
 *  @param f    Função a ser invocada para testar se um elemento x da árvore
 *              satisfaz uma dada condição.
 *  @return Void.
 */
static void filterToIteratorNode(Node *root, Iterator it,
                                 bool (*f)(const void *value))
{
	if (root != NULL) {
		filterToIteratorNode(root->left, it, f);

		if (f(root->value) == true) {

			/* root->value satisfaz uma dada condição logo é adicionado ao
			 * iterador. */

			addIterator(it, root->value);
		}
		filterToIteratorNode(root->right, it, f);
	}
}


/**
 *  Efetua uma travessia em ordem na árvore. A cada elemento é testado
 *  o valor retornado por f, que tem como parâmtros um elemento e um predicado
 *  qualquer recebido. Caso f retorne true então o elemento satisfaz uma certa
 *  condição, sendo este adicionado ao iterador.
 *
 *  @param root Raiz da árvore.
 *  @param it   Iterador a ser criado com os elementos filtrados da árvore.
 *  @param pred Valor a comparar com um dado elemento.
 *  @param f    Função a ser invocada para testar se um elemento x da árvore
 *              satisfaz uma dada condição.
 *  @return Void.
 */
static void filterToIteratorWithPredNode(Node *root, Iterator it,
                                         const void *pred,
                                         bool (*f)(const void *value,
                                                   const void *pred))
{
	if (root != NULL) {
		filterToIteratorWithPredNode(root->left, it, pred, f);

		if (f(root->value, pred) == true) {

			/* root->value satisfaz uma dada condição logo é adicionado ao
			 * iterador. */

			addIterator(it, root->value);
		}

		filterToIteratorWithPredNode(root->right, it, pred, f);
	}
}

/*****************************************************************************
 * END DATA STRUCTURES AUXILIARY FUNCTIONS                                   *
 *****************************************************************************/

/**
 *  Função por defeito para apagar um elemento guardado num nó.
 *
 *  @param value Elemento a apagar.
 *  @return Void.
 */
static void defaultDestroy(void *value)
{
	if (value != NULL) {
		free(value);
		value = NULL;
	}
}

/*****************************************************************************
 * END PRIVATE                                                               *
 *****************************************************************************/



/*****************************************************************************
 * BEGIN PUBLIC                                                              *
 *****************************************************************************/

/*****************************************************************************
 * BEGIN CONSTRUCTORS AND DESTRUCTORS                                          *
 *****************************************************************************/

/**
 *  @brief Inicia o tipo concreto de dados.
 *
 *  Recebe toda a informação necessária para a implementação do tipo concreto
 *  de dados. Como se trata de uma estrutura genérica é necessário guardar
 *  uma função de comparação entre elementos que auxilia funções de adição,
 *  remoção e procura de elementos na árvore, bem como uma função responsável
 *  pela impressão de um elemento no ecrã. É também necessário saber o
 *  tamanho em bytes do tipo de elementos que se pretende armazenar.
 *
 *  @param value_size Tamanho que um elemento ocupa (em bytes).
 *  @param cmp        Função de comparação entre elementos.
 *  @param print      Função para realizar a impressão de um elemento.
 *  @return Retorna o apontador para a árvore.
 */
BSTree createBSTree(const unsigned int value_size,
                    int (*cmp)(const void *a, const void *b),
                    void (*print)(const void *value))
{
	BSTree bst = malloc(sizeof(struct bstree)); /* Aloca espaço para uma
	                                             * árvore. */

	if (bst == NULL) {

		/* Se o malloc falhou tenta-se efetuar o realloc. */

		bst = realloc(bst, sizeof(struct bstree));

		/* Se realloc também falhar então o programa é terminado. */

		assert(bst != NULL);
	}

	bst->root = NULL;
	bst->value_size = value_size;
	bst->cmp = cmp;
	bst->print = print;
	bst->delete = defaultDestroy;

	return bst;
}


/**
 *  Destroi toda a árvore.
 *
 *  @param bst Apontador para a árvore.
 *  @return Void.
 */
void destroyBSTree(BSTree bst)
{

	/* Apenas a destroi caso esta exista. */

	if (bst != NULL && bst->root != NULL) {

		/* Remove toda a árvore. */

		destroyNode(bst, bst->root);

		/* Finalmente remove o apontador para a árvore. */

		free(bst);
		bst = NULL;
	}
}

/*****************************************************************************
 * END CONSTRUCTORS AND DESTRUCTORS                                          *
 *****************************************************************************/


/*****************************************************************************
 * BEGIN GETS AND SETS                                                       *
 *****************************************************************************/

/**
 *  Devolve a altura da árvore caso esta exista.
 *  Como a altura é guardada em cada nó, basta devolver o valor da altura
 *  do raiz.
 *
 *  @param bst Apontador para a árvore.
 *  @return Altura da árvore.
 */
unsigned int getHeightBSTree(const BSTree bst)
{
	unsigned int h = (bst != NULL) ? getHeightNode(bst->root) : 0;

	return h;
}


/**
 * 	Devolve o tamanho da árvore.
 *
 *  @param bst Apontador para a árvore.
 *  @return Número de elementos da árvore ou 0 caso esta não contenha
 *          elementos ou não exista.
 */
unsigned int getSizeBSTree(const BSTree bst)
{
	unsigned int s = 0;

	if (bst != NULL) {
		s = bst->num_nodes;
	}

	return s;
}


/**
 *  Devolve o mínimo da árvore caso esta exista.
 *
 *  @param bst Apontador para a árvore.
 *  @return Valor mínimo.
 */
void* getMinBSTree(const BSTree bst)
{
	void *min = (bst != NULL) ? getMinNode(bst->root) : NULL;

	return min;
}


/**
 *  Devolve o máximo da árvore caso esta exista.
 *
 *  @param bst Apontador para a árvore.
 *  @return Valor máximo.
 */
void* getMaxBSTree(const BSTree bst)
{
	void *max = (bst != NULL) ? getMaxNode(bst->root) : NULL;
	return max;
}


/**
 *  Altera a função para comparar dois elementos da árvore.
 *
 *  @param bst Apontador para a árvore.
 *  @param cmp Função fornecida para efetuar uma comparação entre elementos.
 *  @return Void.
 */
void setCmpBSTree(BSTree bst, int (*cmp)(const void *a, const void *b))
{
	if (bst != NULL) {
		bst->cmp = cmp;
	}
}


/**
 *  Altera a função para realizar a impressão de um elemento.
 *
 *  @param bst   Apontador para a árvore.
 *  @param print Função fornecida para efetuar a impressão de um elemento.
 *  @return Void.
 */
void setPrintBSTree(BSTree bst, void (*print)(const void *value))
{
	if (bst != NULL) {
		bst->print = print;
	}
}


/**
 *  Altera a função para apagar um elemento de um nó.
 *
 *  @param bst    Apontador para a árvore.
 *  @param delete Função fornecida para apagar um elemento de um nó.
 *  @return Void.
 */
void setDeleteBSTree(BSTree bst, void (*delete)(void *value))
{
	if (bst != NULL) {
		bst->delete = delete;
	}
}

/*****************************************************************************
 * END GETS AND SETS                                                         *
 *****************************************************************************/


/*****************************************************************************
 * BEGIN ADD, SEARCH AND REMOVE                                              *
 *****************************************************************************/

/**
 *  Adiciona um elemento à árvore caso esta exista.
 *
 *  @param bst   Apontador para a árvore.
 *  @param value Valor a adicionar.
 *  @return Devolve o apontador para a árvore.
 */
BSTree addBSTree(BSTree bst, const void *value)
{
	if (bst!= NULL) {
		bst->root = addNode(bst, bst->root, value);
	}

	return bst;
}


/**
 *  Adiciona um elemento à árvore caso esta exista. É aplicada uma função
 *  para tratar casos de elemetos repetidos
 *
 *  @param bst   Apontador para a árvore.
 *  @param value Valor a adicionar.
 *  @param f     Função a aplicar para casos de elementos repetidos.
 *  @return Devolve o apontador para a árvore.
 */
BSTree addWithCondBSTree(BSTree bst, const void *new_value,
			     void (*f)(void *acc, const void *new_value))
{
	if (bst!= NULL) {
		bst->root = addWithCondNode(bst, bst->root, new_value, f);
	}

	return bst;
}


/**
 *  Procura por um elemento na árvore caso esta exista.
 *
 *  @param bst   Apontador para a árvore.
 *  @param value Valor a procurar.
 *  @return false caso a árvore ou o elemento não exista. true caso contrário.
 */
bool containsBSTree(const BSTree bst, const void *value)
{
	bool v = (bst != NULL) ? containsNode(bst, bst->root, value) : false;

	return v;
}


/**
 *  Testa se algum elemento da árvore satisfaz f.
 *
 *  @param bst  Apontador para a árvore.
 *  @param pred Predicado a comparar com os elementos da árvore.
 *  @param f    Função para efetuar uma qualquer comparação entre cada elemento
 *              da árvore e o predicado recebido.
 *  @return Void.
 */
bool anyValueMatch(const BSTree bst, const void *pred,
                   bool (*f)(const void *value, const void *pred))
{
	bool b = false;

	if (bst != NULL) {
		b = anyValueMatchNode(bst->root, pred, f);
	}

	return b;
}


/**
 *  Remove um elemento à árvore caso esta exista.
 *
 *  @param bst   Apontador para a árvore.
 *  @param value Valor a remover.
 *  @return Void. O resultado da remoção é guardado em bst.
 */
void delBSTree(BSTree bst, const void * value)
{
	if (bst!= NULL) {
		bst->root = delNode(bst, bst->root, value);
	}
}

/*****************************************************************************
 * END ADD, SEARCH AND REMOVE                                                *
 *****************************************************************************/


/*****************************************************************************
 * BEGIN TREE TRAVERSALS                                                       *
 *****************************************************************************/

/**
 *  Efetua uma função a cada elemento da árvore caso esta exista.
 *
 *  @param bst Apontador para a árvore.
 *  @param f   Função a efetuar a cada elemento.
 *  @return Void.
 */
void mapBSTree(const BSTree bst, void (*f)(void * value))
{
	if (bst != NULL) {
		mapNode(bst->root, f);
	}
}


/**
 *  Cria uma qualquer estrutura de dados caso a árvore exista.
 *
 *  @param bst Apontador para a árvore.
 *  @param acc Acumulador da nova estrutura de dados.
 *  @param f   Função para atualizar acc conforme cada elemento da árvore.
 *  @return Void. O resultado é guardado em acc.
 */
void foldBSTree(const BSTree bst, void *acc,
                void (*f)(const void *value, void *acc))
{
	if (bst != NULL) {
		foldNode(bst->root, acc, f);
	}
}


/**
 *  Cria uma qualquer estrutura de dados caso a árvore exista.
 *
 *  @param bst   Apontador para a árvore.
 *  @param acc   Acumulador da nova estrutura de dados.
 *  @param data  Estrura de dados qualquer para efetuar operações.
 *  @param pred  Predicado.
 *  @param f     Função para atualizar acc conforme cada elemento da árvore.
 *  @return Void. O resultado é guardado em acc.
 */
void foldWithBSTree(const BSTree bst, void *acc, const void *data,
                    const void *pred,
                    void (*f) (const void *data, const void *value,
                               const void *pred, void *acc))
{
	if (bst != NULL) {
		foldWithNode(bst->root, acc, data, pred, f);
	}
}


/**
 *  Faz a impressão da árvore caso esta exista.
 *
 *  @param bst Apontador para a árvore.
 *  @return Void.
 */
void preOrderBSTree(const BSTree bst)
{
	if (bst != NULL) {
		preOrderNode(bst, bst->root);
	}
}


/**
 *  Faz a impressão da árvore caso esta exista.
 *
 *  @param bst Apontador para a árvore.
 *  @return Void.
 */
void inOrderBSTree(const BSTree bst)
{
  if (bst != NULL) {
    inOrderNode(bst, bst->root);
  }
}


/**
 *  Faz a impressão da árvore caso esta exista.
 *
 *  @param bst Apontador para a árvore.
 *  @return Void.
 */
void postOrderBSTree(const BSTree bst)
{
	if (bst != NULL) {
		postOrderNode(bst, bst->root);
	}
}

/*****************************************************************************
 * END TREE TRAVERSALS                                                       *
 *****************************************************************************/

/*****************************************************************************
 * BEGIN DATA STRUCTURES AUXILIARY FUNCTIONS                                 *
 *****************************************************************************/

/**
 *  Devolve um iterador em ordem sobre a árvore caso esta exita.
 *
 *  @param bst Apontador para a árvore.
 *  @return Iterador sobre a árvore binária.
 */
Iterator toIteratorInOrderBSTree(const BSTree bst)
{
	Iterator it = NULL;

	if (bst != NULL) {

		/* Cria o iterador com os dados da árvore:
		 * 	- Tamanho de um elemento da árvore.
		 * 	- Função de impressão de um elemento. */

		it = createIterator(bst->value_size, bst->print);
		toIteratorInOrderNode(bst->root, it);
	}

	return it;
}


/**
 *  Devolve um iterador pós ordem sobre a árvore caso esta exita.
 *
 *  @param bst Apontador para a árvore.
 *  @return Iterador sobre a árvore binária.
 */
Iterator toIteratorPostOrderBSTree(const BSTree bst)
{
	Iterator it = NULL;

	if (bst != NULL) {

		/* Cria o iterador com os dados da árvore:
		 * 	- Tamanho de um elemento da árvore.
		 * 	- Função de impressão de um elemento. */

		it = createIterator(bst->value_size, bst->print);
		toIteratorPostOrderNode(bst->root, it);
	}

	return it;
}


/**
 *  Caso a árvore exista faz uma travessia em ordem nesta, filtrando
 *  apenas para o iterador todos os elementos que verifiquem a função f.
 *
 *  @param bst  Apontador para a árvore.
 *  @param pred Valor para efetuar uma comparação entre um elemento.
 *  @param f    Função de condição de um elemento da árvore.
 *  @return Iterador sobre todos os elementos que satisfaçam f.
 */
Iterator filterBSTree(const BSTree bst, bool (*f)(const void *elem))
{
	Iterator it = NULL;

	if (bst != NULL) {

		/* Cria o iterador com os dados da árvore:
		 * 	- Tamanho de um elemento da árvore.
		 * 	- Função de impressão de um elemento. */

		it = createIterator(bst->value_size, bst->print);
		filterToIteratorNode(bst->root, it, f);
	}

	return it;
}


/**
 *  Caso a árvore exista faz uma travessia em ordem nesta, filtrando
 *  apenas para o iterador todos os elementos que verifiquem a função f.
 *
 *  @param bst  Apontador para a árvore.
 *  @param pred Valor para efetuar uma comparação entre um elemento.
 *  @param f    Função de condição entre um elemento e algo fornecido.
 *  @return Iterador sobre todos os elementos que satisfaçam f.
 */
Iterator filterWithPredBSTree(const BSTree bst, const void *pred,
                              bool (*f)(const void *elem, const void *pred))
{
	Iterator it = NULL;

	if (bst != NULL) {

		/* Cria o iterador com os dados da árvore:
		 * 	- Tamanho de um elemento da árvore.
		 * 	- Função de impressão de um elemento. */

		it = createIterator(bst->value_size, bst->print);
		filterToIteratorWithPredNode(bst->root, it, pred, f);
	}

	return it;
}


/**
 *  Filtra para um iterador já existente todos os elementos da árvore que
 *  satisfaçam f.
 *
 *  @param bst Apontador para a árvore.
 *  @param it  Iterador para se acrescentar todos os elementos que satisfaçam
 *             f.
 *  @param f   Função para testar se um elemento da árvore satisfaz uma certa
 *             condição.
 *  @return Void. O resultado é guardado em it.
 */
void filterToIteratorBSTree(const BSTree bst, Iterator it,
                            bool (*f)(const void *value))
{
	/* Só acrescenta algo ao iterador se este existir e se a árvore existir. */

	if (bst != NULL && it != NULL) {
		filterToIteratorNode(bst->root, it, f);
	}
}

/*****************************************************************************
 * END DATA STRUCTURES AUXILIARY FUNCTIONS                                   *
 *****************************************************************************/

/*****************************************************************************
 * END PUBLIC                                                                *
 *****************************************************************************/
