/**
 *  @file bstmap.c
 *  @brief Uma BSTMap é uma AVL em que os nós contêm uma chave e um
 *         apontador para uma outra AVL.
 *
 *  Definição de todas as funções pertencentes à interface deste módulo, bem
 *  como todos os métodos auxiliares.
 *
 *  @author Carlos Pereira - A61887
 *  @author Diogo Silva    - A76407
 *  @author Rafael Braga   - A61799
 *
 *  @bug ?
 *  @version 3.2
 */

#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "bstmap.h"


/* Tipo de um nó de dados da BST. */

typedef struct node {
	BSTree bst;           /* Apontador para uma árvore binária de procura do
	                       * tipo AVL. */
	void *key;            /* Chave da BSTMap. */
	unsigned char height; /* Altura da BSTMap. */
	struct node *left;    /* Apontador para a sub-árvore à esquerda. */
	struct node *right;   /* Apontador para a Sub-árvore à direita. */
} Node;


/* BSTree do tipo BSTMap. */

struct bstMap {
	Node *root;                              /* Apontador para a raiz da
	                                          * bstMap. */
	unsigned int num_nodes;                  /* Número de nós. */
	unsigned int key_size;                   /* Tamanho da chave. */
	int (*cmpKey)(const void*, const void*); /* Função para comparar duas chaves
	                                          * da BSTMap. */
	void (*printKey)(const void*);           /* Função para fazer a impressão de
	                                          * uma chave da BSTMap */
	void (*deleteKey)(void*);                /* Função para apagar um elemento de
	                                          * um nó. Por defeito esta função
	                                          * será defaultDestroyKey que
	                                          * apaga qualquer tipo de dados
	                                          * básicos. */

/* Os próximos elementos serão usados na createBSTree */

	unsigned int value_size;                   /* Tamanho (em bytes) de um
	                                            * elemento a guardar na árvore */
	int (*cmpValue)(const void*, const void*); /* Compara dois valores de um
	                                            * BSTree */
	void (*printValue)(const void*);           /* Efetua a impressão de um valor
	                                            * de uma BST. */
	void (*deleteValue)(void*);                /* Faz free de um ValueBST */
};


/*****************************************************************************
 * BEGIN PRIVATE                                                             *
 *****************************************************************************/

/*****************************************************************************
 * BEGIN CONSTRUCTORS AND DESTRUCTORS                                        *
 *****************************************************************************/

/**
 *  @brief Aloca espaço para um nó da BSTMap.
 *
 *  A chave dada como argumento é copiada através de memcpy para root->key.
 *  Visto que a chave é do tipo void*, é necessário enviar também como
 *  parâmetro o tamanho dos dados. Da mesma forma, como temos em cada nó da
 *  BSTMap uma BSTree, essa é também inicializada utilizando os campos já
 *  previamente armazenados na BSTMap.
 *
 *  @param bstm     Apontador para a BSTMap.
 *  @param key      Chave a ser copiada para o novo nó da árvore.
 *  @param key_size Tamanho da chave. É necessário pois a chave é um dado
 *                  abstrato.
 *  @return Devolve o novo nó já inicializado.
 */
static Node* createNode(BSTMap bstm, const void *key,
                        const unsigned key_size)
{
	Node *root = malloc(sizeof(Node));

	/* Só inicia a raiz da BSTMap se o malloc não falhou. */

	if (root == NULL) {
		root = realloc(root, sizeof(Node));
		assert(root != NULL);
	}

	root->key = malloc(key_size);

	/* Inicia a chave da BSTMap se o malloc desta tiver sucesso. */

	if (root->key == NULL) {
		root->key = realloc(root->key, key_size);
		assert(root->key != NULL);
	}

	memcpy(root->key, key, key_size);

	root->height = 1;

	/* Cria a árvore binária correspondente à chave recebida. */

	root->bst = createBSTree(bstm->value_size, bstm->cmpValue,
	                         bstm->printValue);

	root->left = NULL;
	root->right = NULL;

	return root;
}


/**
 *  @brief Função por defeito para apagar uma chave guardada num nó.
 *
 *  @param key Chave a ser apagada.
 *  @return Void.
 */
static void defaultDestroyKey(void *key)
{
	if (key != NULL) {
		free(key);
		key = NULL;
	}
}


/**
 *  @brief Função por defeito para apagar um valor de um nó.
 *
 *  @param value Valor a ser apagado.
 *  @return Void.
 */
static void defaultDestroyValue(void *value)
{
	if (value != NULL) {
		free(value);
		value = NULL;
	}
}


/**
 *  @brief Liberta a memória de todos os elementos da BSTMap.
 *
 *  @param bstm  Apontador para a árvore.
 *  @param root  Raiz da BSTMap.
 *  @return Void.
 */
static void destroyNode(BSTMap bstm, Node *root)
{
	if (root != NULL) {

		/* Liberta todas as sub-árvores à esquerda e à direita. */

		destroyNode(bstm, root->left);
		destroyNode(bstm, root->right);

		/* Liberta a chave do presente nó. */

		bstm->deleteKey(root->key);

		/* Liberta a BST do presente nó. */

		/* Modifica a função para apagar um nó da BSTree. */

		setDeleteBSTree(root->bst, bstm->deleteValue);
		destroyBSTree(root->bst);
	}

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
 *  @brief Devolve a altura de um nó, guardando-a ao mesmo tempo no campo
 *         height, não sendo necessário efectuar qualquer travessia.
 *
 *  @param root  Nó cuja altura se pretende obter.
 *  @return  Devolve 0 caso o nó recebido não exista ou a sua altura em caso
 *           contrário.
 */
static unsigned char getHeightNode(const Node *root)
{
	unsigned char h = (root != NULL) ? root->height : 0;

	return h;
}


/**
 *  @brief Devolve o factor de balanceamento de uma árvore do tipo BSTMap.
 *
 *  O factor é determinado pela diferença de alturas entre a sub-árvore à
 *  direita e a sub-árvore à esquerda.
 *
 *  @param root  Nó em que se pretende determinar o factor de balanceamento.
 *  @return  Devolve o fator de balanceamento.
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
 *  @brief Atualiza a altura de um nó.
 *
 *  Depois de uma rotação é necessário recalcular a altura de cada um dos
 *  nós da árvore.
 *
 *  @param root  Nó onde se vai atualizar a altura.
 *  @return  Void. O resultado é guardado em root.
 */
static void recalcHeight(Node *root)
{
	unsigned char hl = getHeightNode(root->left);
	unsigned char hr = getHeightNode(root->right);

	root->height = (unsigned char) (((hl > hr) ? hl : hr) + 1);
}


/**
 *  @brief Faz uma rotação à esquerda no nó root.
 *
 *
 *  Sendo A a root e x uma sub-árvore.
 *
 *  Caso : A                       B
 *          \                     / \
 *           B      ----->       A   C
 *          / \                  \
 *         x   C                  x
 *
 *  Pretende-se que a nova root (pivot) seja root->right, para manter o
 *  critério de uma AVL. Coloca-se root->right a apontar para pivot->left.
 *  Salvaguarda-se pivot->left, passando-o no fim a apontar para a antiga root.
 *  No final actualizam-se as alturas dos nós.
 *
 *  @param root  Antiga raiz da árvore.
 *  @return  A nova raiz da árvore.
 */
static Node* rotateLeft(Node *root)
{
	Node *pivot = root->right; /* Nova raiz. */

	root->right = pivot->left;
	pivot->left = root;

	/* Depois da rotação atualizam-se as alturas de cada nó. */

	recalcHeight(root);
	recalcHeight(pivot);

	return pivot;
}


/**
 *  @brief Faz uma rotação à direita no nó root.
 *
 *  Sendo A a root e x uma sub-árvore.
 *
 *  Caso :   A                   B
 *          /                   / \
 *         B     ------->      B   A
 *        / \                     /
 *       C   x                   x
 *
 *  Pretende-se que a nova root (pivot) seja root->left, para manter o critério
 *  de uma AVL. Coloca-se root->left a apontar para pivot->right.
 *  Salvaguarda-se pivot->right, passando-o no e no fim a apontar para a
 *  antiga root. No final actualizam-se as alturas dos nós.
 *
 *  @param root  Antiga raiz da árvore.
 *  @return  A nova raiz da árvore.
 */
static Node* rotateRight(Node *root)
{
	Node *pivot = root->left; /* Nova raiz. */

	root->left = pivot->right;
	pivot->right = root;

	/* Depois da rotação atualizam-se as alturas de cada nó. */

	recalcHeight(root);
	recalcHeight(pivot);

	return pivot;
}


/**
 *  @brief Efetua o balanceamento da BSTMap.
 *
 *  Esta função é chamada após a inserção de um novo nó na BSTMap.
 *  Calcula-se a nova altura dos nós das sub-árvores. De seguida é calculado
 *  o fator de balanceamento.
 *  Um fator compreendido entre -1 e 1 significa que a árvore já está
 *  balanceada. Um fator maior que 1 significa que a árvore não é balanceada
 *  à sua direita e é aplicada uma rotação simples ou dupla à esquerda.
 *  Um fator menor que -1 significa que a árvore não é balanceada à sua
 *  esquerda e é aplicada uma rotação simples ou dupla à direita.
 *
 *  @param root  Raiz da BSTMap.
 *  @return  A nova raiz da BSTMap após ser balanceada.
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
			 *  Caso :   A            A                   B
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
			 *  Caso :     A                A               B
			 *            /                /               / \
			 *           B     ---->      B     ---->     A  C
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
 * BEGIN ADD, SEARCH AND REMOVE                                               *
 *****************************************************************************/

/**
 *  @brief Adiciona um novo nó à BSTMap ou BSTree.
 *
 *  Para cada nó da BSTMap, além de uma chave, temos também um apontador para
 *  uma BSTree. Ao adicionarmos um nó, se já existir essa chave na BSTMap,
 *  adiciona-se um novo nó à BSTree. Caso contrário cria-se um novo nó na
 *  BSTMap com essa chave e também se cria a BST desse nó.
 *
 *  @param bstm  Contém cmpKey necessário para as comparações entre chaves.
 *  @param root  Raiz da BSTMap.
 *  @param key   Chave onde queremos inserir o nó.
 *  @param value Informação para ser guardada no nó da BSTree para uma dada
 *               chave.
 *  @return  A raiz da árvore.
 */
static Node* addNode(const BSTMap bstm, Node *root,
                     const void *key, const void *value)
{

	/* Sendo a raiz nula pode-se adicionar um novo elemento. */

	if (root == NULL) {

		/* Adiciona-se primeiro a chave. */

		root = createNode(bstm, key, bstm->key_size);

		/* De seguida acrescenta-se value à BST. */

		addBSTree(root->bst, value);

		/* A BSTMap recebe mais um elemento, o seu tamanho é incrementado. */

		bstm->num_nodes++;
	}
	else {
		if (bstm->cmpKey(key, root->key) < 0) {

			/* Adiciona à esquerda. */

			root->left = addNode(bstm, root->left, key, value);
		}
		else if (bstm->cmpKey(key, root->key) == 0) {

			/* Neste caso a BSTMap já contém a chave key, logo apenas
			 * é adicionado value à BST correspondente a esta chave, já que
			 * a BSTMap não tem chaves repetidas. */

			addBSTree(root->bst, value);
		}



		else {

			/* Adiciona à direita. */

			root->right = addNode(bstm, root->right, key, value);
		}

		/* Depois de se adicionar o novo elemento tem que se efetuar o
		 * balanceamento da árvore. */

		root = balance(root);
	}

	return root;
}


/**
 *  @brief Verifica se uma chave já se encontra na BSTMap.
 *
 *  Faz uma travessia tendo como critério o resultado da função cmpKey.
 *
 *  @param bstm  Contém cmpKey necessária para efetuar comparações.
 *  @param root  Raiz da BSTMap.
 *  @param key   Chave a encontrar na árvore.
 *  @return true caso a chave exista ou false se contrário.
 */
static bool containsKeyNode(const BSTMap bstm, const Node *root,
                            const void *key)
{
	bool b = false; /* Valor é false por defeito. Se a chave for
	                 * encontrada, então passa a ser true. */

	/* Se root for NULL, a procura chegou ao fim e a chave não existe. */

	if (root != NULL) {

		/* Começa-se por testar se a chave é menor que a chave do nó.
		 * Se assim for procura-se na sub-árvore à esquerda. */

		if (bstm->cmpKey(key, root->key) < 0) {
			b = containsKeyNode(bstm, root->left, key);
		}
		else if (bstm->cmpKey(key, root->key) > 0) {

			/* Se a chave for maior procura-se na sub-árvore à direira. */

			b = containsKeyNode(bstm, root->right, key);
		}
		else {

			/* A chave existe na árvore. */

			b = true;
		}
	}

	return b;
}


/**
 *  @brief Verifica se um elemento já se encontra numa BST de um nó da BSTMap.
 *
 *  A função começa por verificar se a chave correspondente ao elemento que
 *  se prentende procurar existe.
 *  Se a chave existir, procura-se pelo elemento na BST correspondente à chave.
 *  Se a chava não existir, então o elemento da BST a procurar não existe.
 *
 *  @param bstm   Contém a função necessária para efetuar as
 *                comparações entre chaves.
 *  @param root   Raiz da BSTMap.
 *  @param key    Chave correspondente ao elemento a procurar.
 *  @param value  Elememto a procurar na BSTMap.
 *  @return  true caso o elemento exista ou false se contrário.
 */
static bool containsValueNode(const BSTMap bstm, const Node *root,
                              const void *key, const void *value)
{
	bool b = false; /* Valor é false por defeito. Se o elemento for
	                 * encontrado, então passa a ser true. */

	/* Se root for NULL a procura chegou ao fim e a chave não existe. */

	if (root != NULL) {

		/* Começa por testar se a chave é menor que a chave do nó.
		 * Se assim for procura-se na sub-árvore à esquerda. */

		if (bstm->cmpKey(key, root->key) < 0) {
			b = containsValueNode(bstm, root->left, key, value);
		}
		else if (bstm->cmpKey(key, root->key) > 0) {

			/* Se a chave for maior procura-se na sub-árvore à direira. */

			b = containsValueNode(bstm, root->right, key, value);
		}
		else {

			/* A chave existe na BSTMap, logo procura-se pelo elemento na BST
			 * correspondente a esta chave. */

			b = containsBSTree(root->bst, value);
		}
	}

	return b;
}

/*****************************************************************************
 * END ADD SEARCH AND REMOVE                                                 *
 *****************************************************************************/


/*****************************************************************************
 * BEGIN TREE TRAVERSALS                                                     *
 *****************************************************************************/

/**
 *  Faz o map de uma função a todas as chaves da BSTMap.
 *
 *  @param root  Raiz da BSTMap.
 *  @param f  Função a aplicar a todas as chaves da BSTMap.
 *  @return Void
 */
static void mapKeyNode(const Node *root, void (*f)(void *key))
{
	if (root != NULL) {

		/*Faz-se o mapKeyNode da sub-árvore à esquerda de root.*/

		mapKeyNode(root->left, f);

		/*Aplica-se a função f à chave do nó.*/

		f(root->key);

		/*Faz-se o mapKeyNode da sub-árvore à direita de root.*/

		mapKeyNode(root->right, f);
	}
}


/**
 *  Faz o map de uma função na BST de uma dada chave da BSTMap.
 *
 *  @param bstm  Contém a função necessária para efetuar
 *               comparações de chaves.
 *  @param root  Raiz da BSTMap.
 *  @param key   Raiz da BSTMap.
 *  @param f     Função a aplicar a todas as chaves da BSTMap.
 *  @return Void. O resultado é guardado em bstm.
 */
static void mapValueNode(const BSTMap bstm, const Node *root, const void *key,
                         void (*f)(void *value))
{
	if (root != NULL) {

		/* Começa-se por testar se a chave é menor que a chave do nodo.
		 * Se assim for procura-se na sub-árvore à esquerda. */

		if (bstm->cmpKey(key, root->key) < 0) {
			mapValueNode(bstm, root->left, key, f);
		}
		else if (bstm->cmpKey(key, root->key) > 0) {

			/* Se a chave for maior procura-se na sub-árvore à direira. */

			mapValueNode(bstm, root->right, key, f);
		}
		else {

			/* Quando a chave do nó for igual a key, aplica-se o mapBSTree
			 * à BST para o qual o nó está a apontar.*/

			mapBSTree(root->bst, f);
		}
	}
}


/**
 *  Aplica um fold com acumulador aos values nas BST das chaves da BSTMap.
 *
 *  @param root  Raiz da BSTMap.
 *  @param acc   Acumulador da função f.
 *  @param f     Função a aplicar a todas as BST.
 *  @return  Void. O resultado é guardado em acc.
 */
static void foldNode(const Node *root, void *acc,
                     void (*f)(const void *value, void *acc))
{
	if (root != NULL) {

		/* Faz-se o foldNode da sub-árvore à esquerda de root.*/

		foldNode(root->left, acc, f);

		/* Faz-se o foldBSTree da árvore para o qual root->bst está a apontar.*/

		foldBSTree(root->bst, acc, f);

		/* Faz-se o foldNode da sub-árvore à direita de root.*/

		foldNode(root->right, acc, f);
	}
}


/**
 *  Aplica um fold com acumulador às chaves da BSTMap.
 *
 *  @param root  Raiz da BSTMap.
 *  @param acc   Acumulador da função f.
 *  @param f     Função a aplicar a todas as chaves da BSTMap.
 *  @return      void
 */
static void foldKeyNode(const Node *root, void *acc,
                        void (*f)(const void *key, void *acc))
{
	if (root != NULL) {

		/* Faz-se o foldKeyNode da sub-árvore à esquerda de root.*/

		foldKeyNode(root->left, acc, f);

		/* Aplica-se a função f à chave root-key e ao acumulador acc.*/

		f(root->key, acc);

		/* Faz-se o foldKeyNode da sub-árvore à direita de root.*/

		foldKeyNode(root->right, acc, f);
	}
}


/**
 * Aplica um fold com acumulador a uma BST de uma dada chave da BSTMap.
 *
 *  @param bstm  Contém a função necessária para efetuar
 *               comparações de chaves.
 *  @param root  Raiz da BSTMap.
 *  @param acc   Acumulador da função f.
 *  @param key   Chave da BSTMap a procurar.
 *  @param f    Função a aplicar à BST de chave key.
 *  @return  Void. O resultado é guardado em acc.
 */
static void foldValueNode(const BSTMap bstm, const Node *root, const void *key,
                          void *acc,
                          void (*f)(const void *value, void *acc))
{
	if (root != NULL) {

		/* Começa-se por testar se a chave é menor que a chave do nó.
		 * Se assim for procura-se na sub-árvore à esquerda. */

		if (bstm->cmpKey(key, root->key) < 0) {
			foldValueNode(bstm, root->left, key, acc, f);
		}
		else if (bstm->cmpKey(key, root->key) > 0) {

			/* Se a chave for maior procura-se na sub-árvore à direira. */

			foldValueNode(bstm, root->right, key, acc, f);
		}
		else {

			/* Quando se encontrar o nó de chave key, aplica-se
			 * um foldBSTree à BST para o qual este está a apontar.*/

			foldBSTree(root->bst, acc, f);
		}
	}
}


/**
 *  Aplica um fold com predicado todos os valores da BSTMap, levando como
 *  informção a chave de cada um destes.
 *
 *  @param root Raiz da árvore.
 *  @param acc  Acumulador da função f.
 *  @param pred Predicado.
 *  @param f    Função a aplicar a cada valor da BSTree value.
 *              Recebe os seguintes parêmetros:
 *              	- A chave a que correspode value.
 *              	- Um valor de uma BSTree.
 *              	- Um predicado para efetuar uma comparação.
 *              	- Acumulador que irá guardar uma qualquer estrutura de
 *              	  dados.
 *  @return Void. O resultado é devolvido em acc.
 */
void foldKeyValueWithNode(const Node *root, void *acc, const void *pred,
                          void (*f)(const void *key, const void *value,
                                    const void *pred, void *acc))
{
	if (root != NULL) {
		foldKeyValueWithNode(root->left, acc, pred, f);
		foldWithBSTree(root->bst, acc, root->key, pred, f);
		foldKeyValueWithNode(root->right, acc, pred, f);
	}
}


/**
 *  @brief Faz a impressão das chaves (e das suas BST) da BSTMap.
 *         A impressão é realizada conforme a função de impressão.
 *
 *  @param bstm  Contém a função de impressão.
 *  @param root  Nó da BSTMap. Aponta também para a raiz de uma BST.
 *  @return Void.
 */
static void preOrderNode(const BSTMap bstm, const Node *root)
{
	if (root != NULL) {

		/* Primeiro faz a impressão da chave da BSTMap. */

		bstm->printKey(root->key);

		/* Faz a impressão da BST correspondente à chave do nó actual. */

		preOrderBSTree(root->bst);

		/* Faz a impressão das sub-árvores à esquerda e à direita
		 * do nó actual. */

		preOrderNode(bstm, root->left);
		preOrderNode(bstm, root->right);
	}
}


/**
 *  @brief Faz a impressão das chaves (e das suas BST) da BSTMap.
 *         O impressão é realizada por ordem crescente.
 *
 *  @param bstm  Contém a função de impressão.
 *  @param root  Nó da BSTMap. Aponta também para a raiz de uma BST.
 *  @return Void.
 */
static void inOrderNode(const BSTMap bstm, const Node *root)
{
	if (root != NULL) {
		/* Faz a impressão da sub-árvore à esquerda. Ou seja, dos nós cujas chaves
		 * são de menor valor do que a do nó actual.*/

		inOrderNode(bstm, root->left);

		/*Quando as chaves de menor valor forem todas impressas, imprime-se
		 * a chave actual e a BST correspondente.*/

		bstm->printKey(root->key);
		inOrderBSTree(root->bst);

		/* Faz a impressão da sub-árvore à direita. Ou seja, dos nós cujas chaves
		 * são de maior valor do que a do nó actual.*/

		inOrderNode(bstm, root->right);
	}
}


/**
 *  @brief Faz a impressão das chaves (e das suas BST) da BSTMap.
 *         A impressão é realizada por ordem decrescente.
 *
 *  @param bstm  Contém a função de impressão.
 *  @param root  Nó da BSTMap. Aponta também para a raiz de uma BST.
 *  @return Void.
 */
static void postOrderNode(const BSTMap bstm, const Node *root)
{
	if (root != NULL) {
		postOrderNode(bstm, root->right);

		/* Imprime a chave actual, seguindo-se a impressão da BST
		 * correspondente.*/

		bstm->printKey(root->key);
		postOrderBSTree(root->bst);

		postOrderNode(bstm, root->left);
	}
}

/*****************************************************************************
 * END TREE TRAVERSALS                                                       *
 *****************************************************************************/


/*****************************************************************************
 * BEGIN DATA STRUCTURES AUXILIARY FUNCTIONS                                 *
 *****************************************************************************/

/**
 *  @brief Procura o nó da BSTMap para fazer a conversão da sua BST
 *         num iterador.
 *
 *  @param bstm  Contém a função de comparação.
 *  @param root  Nó da BSTMap. Aponta também para a raiz de uma BST.
 *  @param key   Chave a ser procurada na BSTMap.
 *  @return  Iterador.
 */
static Iterator toIteratorValuePostOrderNode(const BSTMap bstm,
                                             const Node *root, const void *key)
{
	Iterator it = NULL;

	if (root != NULL) {

		/* Começa-se por testar se a chave é menor que a chave do nodo.
		 * Se assim for procura-se na sub-árvore à esquerda. */

		if (bstm->cmpKey(key, root->key) < 0) {
			it = toIteratorValuePostOrderNode(bstm, root->left, key);
		}
		else if (bstm->cmpKey(key, root->key) > 0) {

			/* Caso a chave a procurar seja maior que a chave actual, faz-se
			 * a conversão da sub-árvore à direita.*/

			it = toIteratorValuePostOrderNode(bstm, root->right, key);
		}
		else {

			/* Quando encontrar a chave procurada, segue-se a conversão
			 * da BST contida no nó.*/

			it = toIteratorPostOrderBSTree(root->bst);
		}
	}

	/*No final devolve-se o iterador.*/

	return it;
}

/*****************************************************************************
 * END DATA STRUCTURES AUXILIARY FUNCTIONS                                   *
 *****************************************************************************/

/*****************************************************************************
 * END PRIVATE                                                               *
 *****************************************************************************/



/*****************************************************************************
 * BEGIN PUBLIC                                                              *
 *****************************************************************************/

/*****************************************************************************
 * BEGIN CONSTRUCTORS AND DESTRUCTORS                                        *
 *****************************************************************************/

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
 *  @param printKey    Função para realizar o display de uma chave.
 *  @param value_size  Tamanho que um elemento ocupa (em bytes).
 *  @param cmpValue    Função de comparação entre elementos.
 *  @param printValue  Função para realizar o display de um elemento.
 *  @return            Devolve o apontador para a BSTMap.
 */
BSTMap createBSTMap(const unsigned int key_size,
                    int (*cmpKey)(const void *a, const void *b),
                    void (*printKey)(const void *key),
                    unsigned int value_size,
                    int (*cmpValue)(const void *a, const void *b),
                    void (*printValue)(const void *value))
{
	BSTMap bstm = malloc(sizeof(struct bstMap));

	/* Caso o malloc não seja bem sucedido, faz-se um realloc. Caso este falhe,
	 * o programa termina.*/

	if (bstm == NULL) {
		bstm = realloc(bstm, sizeof(struct bstMap));
		assert(bstm != NULL);
	}

	/* Só inicia a BSTMap se o malloc (ou realloc) for bem sucedido. */

	bstm->root = NULL;
	bstm->key_size = key_size;
	bstm->cmpKey = cmpKey;
	bstm->printKey = printKey;
	bstm->deleteKey = defaultDestroyKey;
	bstm->value_size = value_size;
	bstm->cmpValue = cmpValue;
	bstm->printValue = printValue;
	bstm->deleteValue = defaultDestroyValue;

	return bstm;
}


/**
 *  Liberta toda a memória da BSTMap.
 *
 *  @param bstm  Contém um apontador para a árvore.
 *  @return Void.
 */
void destroyBSTMap(BSTMap bstm)
{
	/* Apenas a liberta a memória da BSTMap caso esta exista. */

	if (bstm != NULL && bstm->root != NULL) {

		/* Remove toda a árvore. */

		destroyNode(bstm, bstm->root);

		/* No fim remove o apontador para a árvore. */

		free(bstm);
		bstm = NULL;
	}
}

/*****************************************************************************
 * END CONSTRUCTORS AND DESTRUCTORS                                          *
 *****************************************************************************/


/*****************************************************************************
 * BEGIN GETS AND SETS                                                       *
 *****************************************************************************/

/**
 *  Altera a função para comparar duas chaves da BSTMap.
 *
 *  @param bstm  Apontador da árvore.
 *  @param cmp   Função fornecida para efetuar uma comparação entre chaves.
 *  @return  Void.
 */
void setCmpBSTMap(BSTMap bstm, int (*cmp)(const void *a, const void *b))
{

	/* Apenas altera a função de comparação da BSTMap caso esta exista. */

	if (bstm != NULL) {
		bstm->cmpKey = cmp;
	}
}


/**
 *  Altera a função para realizar a impressão de uma chave da BSTMap.
 *
 *  @param bstm   Apontador para uma árvore.
 *  @param print  Função fornecida para fazer a impressão de uma chave.
 *  @return  Void.
 */
void setPrintBSTMap(BSTMap bstm, void (*print)(const void *key))
{
	/* Apenas altera a função de impressão da BSTMap caso esta exista. */

	if (bstm != NULL) {
		bstm->printKey = print;
	}
}


/**
 *  Altera a função para apagar uma chave da BSTMap.
 *
 *  @param bstm    Estrutura da BSTMap.
 *  @param delete  Função fornecida para apagar a chave de um nó.
 *  @return  Void.
 */
void setDeleteBSTMap(BSTMap bstm, void (*delete)(void *key))
{
	/* Apenas altera a função de eliminação da BSTMap caso esta exista. */

	if (bstm != NULL) {
		bstm->deleteKey = delete;
	}
}


/**
 *  Altera a função para comparar dois valores da BSTree.
 *
 *  @param bstm  Estrutura da BSTMap.
 *  @param cmp   Função fornecida para efetuar uma comparação entre valores.
 *  @return  Void.
 */
void setCmpValueBSTMap(BSTMap bstm, int (*cmp)(const void *a, const void *b))
{
	/* Apenas altera a função de comparação da BST caso a BSTMap exista. */

	if (bstm != NULL) {
		bstm->cmpValue = cmp;
	}
}


/**
 *  @brief Altera a função para realizar a impressão de um valor da BST.
 *
 *  Essa função é guardada na BSTMap para ser utilizada como argumento
 *  na criação de uma BSTree.
 *
 *  @param bstm   Estrutura da BSTMap.
 *  @param print  Função fornecida para fazer a impressão de um valor da BST.
 *  @return  Void
 */
void setPrintValueBSTMap(BSTMap bstm, void (*print)(const void *value))
{
	/* Apenas altera a função de impressão da BST caso a BSTMap exista. */

	if (bstm != NULL) {
		bstm->printValue = print;
	}
}

/**
 *  Altera a função para fazer a realocação da memória de um valor da BST.
 *
 *  @param bstm    Estrutura da BSTMap.
 *  @param delete  Função fornecida para apagar o valor de uma BST.
 *  @return        void
 */
void setDeleteValueBSTMap(BSTMap bstm, void (*delete)(void*))
{
	/* Apenas altera a função de impressão da BST caso a BSTMap exista. */

	if (bstm != NULL) {
		bstm->deleteValue = delete;
	}
}

/*****************************************************************************
 * END GETS AND SETS                                                         *
 *****************************************************************************/


/*****************************************************************************
 * BEGIN ADD, SEARCH AND REMOVE                                              *
 *****************************************************************************/

/**
 *  Adiciona uma chave e um elemento à árvore caso esta exista.
 *
 *  @param bstm   Estrutura da BSTMap. Contém um apontador para a árvore.
 *  @param key    Chave a adicionar (à BSTMap).
 *  @param value  Valor a adicionar (à BST).
 *  @return  Devolve o apontador para a árvore.
 */
BSTMap addBSTMap(BSTMap bstm, const void *key, const void *value)
{
	if (bstm != NULL) {
		bstm->root = addNode(bstm, bstm->root, key, value);
	}

	return bstm;
}


/**
 *  Procura por uma chave na árvore.
 *
 *  @param bstm  Estrutura da BSTMap. Contém um apontador para a árvore.
 *  @param key   Chave a procurar.
 *  @return  false caso a árvore ou a chave não existam.
 *           true caso contrário.
 */
bool containsKeyBSTMap(const BSTMap bstm, const void *key)
{
	bool b = (bstm != NULL) ? containsKeyNode(bstm, bstm->root, key) : false;

	return b;
}


/**
 *  Procura por um valor nas BST.
 *
 *  @param bstm   Apontador para a árvore.
 *  @param key    Chave correspondente ao elemento a procurar.
 *  @param value  Valor a procurar.
 *  @return  false caso a BSTMap ou o elemento não existam.
 *           true caso contrário.
 */
bool containsValueBSTMap(const BSTMap bstm, const void *key,
                         const void *value)
{
	bool b = (bstm != NULL)
	          	? containsValueNode(bstm, bstm->root, key, value)
	          	: false;

	return b;
}

/*****************************************************************************
 * END ADD, SEARCH AND REMOVE                                                *
 *****************************************************************************/


/*****************************************************************************
 * BEGIN TREE TRAVERSALS                                                     *
 *****************************************************************************/

/**
 *  Faz o map de uma função a todas as chaves da BSTMap.
 *
 *  @param bstm  Contém o apontador para a árvore.
 *  @param f     Função a aplicar a todas as chaves.
 *  @return  Void.
 */
void mapKeyBSTMap(const BSTMap bstm, void (*f)(void *key))
{
	if (bstm != NULL) {
		mapKeyNode(bstm->root, f);
	}
}


/**
 *  @brief Faz o map de uma função a todos os valores das BST de uma chave
 *         contida na BSTMap.
 *
 *  @param bstm  Contém o apontador para a árvore.
 *  @param key   Chave a procurar na BSTMap.
 *  @param f     Função a aplicar a todas os valores das BST.
 *  @return      void
 */
void mapValueBSTMap(const BSTMap bstm, const void *key,
                    void (*f)(void *value))
{
	if (bstm != NULL) {
		mapValueNode(bstm, bstm->root, key, f);
	}
}


/**
 *  Faz o fold de uma função com acumulador a todos os valores das BST.
 *
 *  @param bstm  Contém o apontador para a árvore.
 *  @param acc   Acumulador da função f.
 *  @param f     Função a aplicar a todas os valores das BST.
 *  @return  Void.
 */
void foldBSTMap(const BSTMap bstm, void *acc,
                void (*f)(const void *value, void *acc))
{
	if (bstm != NULL) {
		foldNode(bstm->root, acc, f);
	}
}


/**
 *  Faz o fold de uma função com acumulador a todas as chaves da BSTMap.
 *
 *  @param bstm  Contém o apontador para a árvore.
 *  @param acc   Acumulador da função f.
 *  @param f     Função a aplicar a todas as chaves da BSTMap.
 *  @return  Void.
 */
void foldKeyBSTMap(const BSTMap bstm, void *acc,
                   void (*f)(const void *key, void *acc))
{
	if (bstm != NULL) {
		foldKeyNode(bstm->root, acc, f);
	}
}


/**
 *  Faz o fold de uma função com acumulador a todos os valores de uma BST
 *  de uma chave contida na BSTMap.
 *
 *  @param bstm  Contém o apontador para a árvore.
 *  @param key   Chave a procurar na BSTMap.
 *  @param acc   Acumulador da função f.
 *  @param f     Função a aplicar a todas os valores da BST.
 *  @return  Void.
 */
void foldValueBSTMap(const BSTMap bstm, const void *key, void *acc,
                     void (*f)(const void *value, void *acc))
{
	if (bstm != NULL) {
		foldValueNode(bstm, bstm->root, key, acc, f);
	}
}


/**
 *  Faz o fold de uma função com acumulador a todos os valores da BSTMap.
 *
 *  @param bstm  Contém o apontador para a árvore.
 *  @param acc   Acumulador da função f.
 *  @param pred  Predicado a aplicar a cada valor de uma BSTree.
 *  @param f     Função a aplicar a todas os valores da BSTMap.
 *  @return  Void.
 */
void foldKeyValueWithBSTMap(const BSTMap bstm, void *acc, const void *pred,
                        void (*f)(const void *key, const void *value,
                        const void *pred, void *acc))
{
	if (bstm != NULL) {
		foldKeyValueWithNode(bstm->root, acc, pred, f);
	}
}


/**
 *  Faz a impressão da árvore caso esta exista.
 *
 *  @param bstm  Apontador para a árvore.
 *  @return Void.
 */
void preOrderBSTMap(const BSTMap bstm)
{
	if (bstm != NULL) {
		preOrderNode(bstm, bstm->root);
	}
}


/**
 *  Faz a impressão da árvore caso esta exista.
 *
 *  @param bstm  Apontador para a árvore.
 *  @return Void.
 */
void inOrderBSTMap(const BSTMap bstm)
{
	if(bstm != NULL) {
		inOrderNode(bstm, bstm->root);
	}
}


/**
 *  Faz a impressão da árvore caso esta exista.
 *
 *  @param bstm  Apontador para a árvore.
 *  @return Void.
 */
void postOrderBSTMap(const BSTMap bstm) {
	if(bstm != NULL) {
		postOrderNode(bstm, bstm->root);
	}
}

/*****************************************************************************
 * END TREE TRAVERSALS                                                       *
 *****************************************************************************/


/*****************************************************************************
 * BEGIN DATA STRUCTURES AUXILIARY FUNCTIONS                                 *
 *****************************************************************************/

/**
 *  Procura um nó da BSTMap com chave key. Converte para o iterador a
 *  BST apontada por esse nó.
 *
 *  @param bstm  Contém o apontador para a árvore.
 *  @param key   Chave a procurar nos nós da BSTMap.
 *  @return  Iterador com os elementos da BST apontada pelo nó (da BSTMap)
 *           de chave key.
 */
Iterator toIteratorValuePostOrderBSTMap(const BSTMap bstm, const void *key)
{
	Iterator it = NULL;

	/*Apenas procura o nó caso a árvore da BSTMap exista.*/

	if (bstm != NULL) {
		it = toIteratorValuePostOrderNode(bstm, bstm->root, key);
	}

	return it;
}

/*****************************************************************************
 * END DATA STRUCTURES AUXILIARY FUNCTIONS                                   *
 *****************************************************************************/

/*****************************************************************************
 * END PUBLIC                                                                *
 *****************************************************************************/
