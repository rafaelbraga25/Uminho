/**
 *  @file catalogoProdutos.c
 *  @brief Os códigos dos produtos são armazenados num array de BSTree's.
 *
 *  O array tem 26 posições. Cada posição corresponde à diferença entre
 *  o valor da 1ª letra do código de produto e a letra 'A', em ASCII.
 *  Definição de todas as funções pertencentes à interface deste módulo, bem
 *  como todos os seus métodos auxiliares.
 *
 *  @author Carlos Pereira - A61887
 *  @author Diogo Silva    - A76407
 *  @author Rafael Braga   - A61799
 *
 *  @bug ?
 *  @version 3
 */

#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include "bstree.h"
#include "iterator.h"
#include "catalogoProdutos.h"


#define SIZE 26               /* Nº de posições do array.
                               * Cada posição é uma letra do alfabeto. */
#define DEFAULT_PAGE_SIZE 30  /* Número de códigos de produtos impressos por
                               * página. */


/*  Tipo do catálogo de produtos. */

struct productCtlg {
	BSTree *vec;             /* Array de BSTree's que irá conter os códigos
	                          * de produtos.*/

	Iterator it;             /* Iterador sobre o catálogo de produtos. */

	unsigned int page_size;  /* Tamanho de uma página de códigos de produtos. */
	unsigned int page;       /* Página atual. */

	printProd printP;        /* Função de impressão de um código de produto. */
};



/*****************************************************************************
 * BEGIN PRIVATE                                                             *
 *****************************************************************************/

/*****************************************************************************
 * BEGIN GETS AND SETS                                                       *
 *****************************************************************************/

/**
 *  @brief Determina o índice, de um dado código, no array de BSTree's.
 *
 *  Determina a posição correspondente à diferença entre o valor da 1ª letra
 *  do código de produto e a letra 'A', em ASCII.
 *
 *  @param code Código do produto a determinar o índice.
 *  @return Retorna o índice correspondente.
 */
static unsigned int getProductHash(const char code)
{
	unsigned int index = 0;

	index = ((unsigned int) code - 65);

	return index;
}

/*****************************************************************************
 * END GETS AND SETS                                                         *
 *****************************************************************************/


/*****************************************************************************
 * BEGIN PRINT FUNCTIONS                                                     *
 *****************************************************************************/

/**
 *  @brief Faz a impressão de uma página de uma pesquisa neste catálogo.
 *
 *  Esta função admite que tanto como o catálogo de produtos bem como o
 *  iterador deste tenham sido previamente inicializados. Para além disso
 *  admite que a página a ser impressa é válida. O número
 *  de elementos percorridos no iterador é igual ao número de códigos de
 *  impressos por página.
 *  O ciclo termina caso se chegue ao fim do iterador.
 *
 *  @param catalog Apontador para o catálogo.
 *  @return Devolve o número de produtos impressos.
 */
static unsigned int printProductPage(const ProductCtlg catalog)
{
	unsigned int i = 0; /* Controlo do ciclo for e número de produtos
	                     * impressos. */

	for (; i < catalog->page_size; i++) {
		 printCurrentIterator(catalog->it);

		 if (hasNextIterator(catalog->it) == true) {
			 nextIterator(catalog->it);
		 }
		 else {
			 i++;
			 break;
		 }
	 }

	return i;
}

/*****************************************************************************
 * END PRINT FUNCTIONS                                                       *
 *****************************************************************************/


/*****************************************************************************
 * BEGIN DATA STRUCTURES AUXILIARY FUNCTIONS                                 *
 *****************************************************************************/

/**
 *  Função de comparação entre dois elementos de uma BSTree.
 *  Neste caso, como os elementos a serem guardados na BSTree são strings,
 *  usa-se a função strcmp para determinar o resultado.
 *
 *  @param a Primeira string a ser comparada.
 *  @param b Segunda string a ser comparada.
 *  @return 0 se a e b são iguais, 1 se a contém um valor alfabético superior
 *          a b e -1 caso contrário.
 */
static int cmp(const void *a, const void *b)
{
  return (strcmp((char*)a, (char*)b));
}


/**
 *  Função para verificar se um código de produto presente na árvore binária
 *  é iniciado pela sequência de caracteres pred.
 *
 *  @param value Elemento a testar.
 *  @param pred  Predicado da função de teste, esta variável pode ser usada
 *               para efetuar qualquer tipo de comparação. Neste caso,
 *               representa uma sequência de caracteres.
 *  @return true caso value seja inicado pela sequência de caracteres pred ou
 *          false caso contrário.
 */
static bool cond(const void *value, const void *pred)
{
	bool b = false;

	if (strncmp((char*) value, (char*) pred, strlen((char*) pred)) == 0) {
		b = true;
	}

	return b;
}


/**
 *  Limpa o iterador do catálogo, caso este contenha alguns dados.
 *
 *  @param catalog Apontador para o catálogo.
 *  @return Void. O resultado é guardado em catalog.
 */
static void initIterator(const ProductCtlg catalog)
{
	if (catalog->it != NULL) {

		/* Já existem dados no iterador logo este é destruido. */

		catalog->page = 0;
		destroyIterator(catalog->it);
	}
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
 *  @brief Cria e inicializa o catálogo de produtos.
 *
 *  O catálogo de produtos corresponde a um vprintector com 26 posições. Cada
 *  posição corresponde à diferença entre o valor da 1ª letra do código de
 *  produto e a letra 'A', em ASCII. Cada posição deste array contém
 *  uma BSTree de código que começam pela mesma letra do alfabeto.
 *
 *  Aloca espaço para a raiz da árvore binária. Guarda a informação
 *  da função que faz o display de um elemento no ecrã, como também cria
 *  um array com 26 posições.
 *
 *  A árvore armazena os códigos maiores à direita e os menores
 *  à esquerda.
 *
 *  @param print Função para realizar a impressão de um código de produto.
 *  @return Apontador para o catálogo dos produtos.
*/
ProductCtlg createProductCtlg(printProd printP)
{
	unsigned int i = 0;
	ProductCtlg catalog = malloc(sizeof(struct productCtlg));

	if (catalog == NULL) {

		/* Se o malloc do catálogo falhar faz-se o realloc deste. */

		catalog = realloc(catalog, sizeof(struct productCtlg));

		/* Se o realloc falhar então o programa é terminado. */

		assert(catalog != NULL);
	}

	/* Aloca-se espaço para o array de BSTree's. */

	catalog->vec = malloc(SIZE * sizeof(BSTree));

	if (catalog->vec == NULL) {

		/* Se o malloc do array falhar então é feito um realloc deste. */

		catalog->vec = realloc(catalog->vec,
		                               SIZE * sizeof(BSTree));

		/* Se o realloc falhar então o programa é terminado. */

		assert(catalog->vec != NULL);
	}

	/* Cada posição do array é inicializada com uma BSTree. */

	for (; i < SIZE; i++) {
		catalog->vec[i] = NULL;
	}

	catalog->it = NULL;
	catalog->page_size = DEFAULT_PAGE_SIZE;
	catalog->page = 0;
	catalog->printP = printP;

	return catalog;
}


/**
 *  @brief Liberta a memória ocupada pelo catálogo.
 *
 *  Faz o free para cada BSTree do array. No final, liberta a memória
 *  do catálogo de produtos.
 *  Se o catálogo for nulo, a função não tem efeito.
 *
 *  @param catalog Apontador para o catálogo.
 *  @return Void.
 */
void destroyProductCtlg(ProductCtlg catalog)
{
	unsigned int i = 0;

	if (catalog != NULL) {
		if (catalog->vec != NULL) {

			/* Destroi todas as posições do array de BSTree's. */

			for (; i < SIZE; i++) {
				destroyBSTree(catalog->vec[i]);
			}

			/* Apaga o array. */

			free(catalog->vec);
			catalog->vec = NULL;
		}

		/* Destroi o iterador. */

		destroyIterator(catalog->it);

		/* Finalmente apaga a estrutura do catálogo. */

		free(catalog);
		catalog	= NULL;
	}
}

/*****************************************************************************
 * END CONSTRUCTORS AND DESTRUCTORS                                          *
 *****************************************************************************/


/*****************************************************************************
 * BEGIN GETS AND SETS                                                       *
 *****************************************************************************/

/**
 *  Devolve o número total de páginas de códigos de produto.
 *  O número total de páginas é calculado através da divisão da última
 *  posição do iterador com o tamanho pré-definido de uma página de produto.
 *  O valor devolvido é arredondado por excesso.
 *
 *  @param catalog Apontador para o catálogo.
 *  @return Número de páginas de códigos de produto.
 */
unsigned int getNumProductPages(const ProductCtlg catalog)
{
 	unsigned int num = 0; /* Número total de páginas. */
 	double aux = 0;       /* Valor real auxiliar para efetuar o arredondamento
 	                       * do número de páginas por excesso. */

 	if (catalog->it != NULL) {
 		aux = ((double) getSizeIterator(catalog->it)) / catalog->page_size;

 		/* num recebe o valor total de páginas arredondadas por defeito. */

 		num = (unsigned int) aux;

 		/* Se a subtração ao valor total de páginas com o valor de num for
 		   maior que zero é sinal que o número de páginas deve ser
 			 incrementado. */

 		if (aux - num > 0) {
 			num++;
 		}
 	}

 	return num;
}


/**
 *  Devolve o tamanho de página de códigos de produto.
 *
 *  @param catalog Apontador para o catálogo.
 *  @return Devolve catalog->page_size caso este exista ou
 *          DEFAULT_PAGE_SIZE caso contrário.
 */
unsigned int getProductPageSize(const ProductCtlg catalog)
{
	unsigned int page_size = (catalog != NULL)
	                          	? catalog->page_size
	                          	: DEFAULT_PAGE_SIZE;

	return page_size;
}


/**
 *  Modifica o tamanho de uma página de códigos de produto caso
 *  o catálogo tenha sido previamente inicializado.
 *
 *  @param catalog   Apontador para o catálogo.
 *  @param page_size Novo tamanho de página de códigos de produto.
 *  @return Void.
 */
void setProductPageSize(const ProductCtlg catalog,
                        const unsigned int page_size)
{
	if (catalog != NULL) {
			catalog->page_size = page_size;
	}
}

/*****************************************************************************
 * END GETS AND SETS                                                         *
 *****************************************************************************/


/*****************************************************************************
 * BEGIN ADD, SEARCH AND REMOVE                                              *
 *****************************************************************************/

/**
 *  @brief Adiciona um produto ao catálogo de produtos.
 *
 *  Se o catálogo já tiver sido criado e inicializado, adiciona um
 *  código de produto. O produto é adicionado conforme a função de
 *  comparação dada.
 *
 *  @param catalog Apontador para o catálogo de produtos.
 *  @param code    Produto a adicionar.
 *  @return Devolve o apontador para o catálogo.
 */
ProductCtlg addProduct(ProductCtlg catalog, const ProductCode code)
{
	unsigned int index = 0;

	if (catalog != NULL) {
		index = getProductHash(*code);

		if (index < SIZE) {
			if (catalog->vec[index] == NULL) {
				/* Cria a árvore correspondente à primeira letra de code caso esta
				 * não exista. É reservado espeço suficiente para suportar dados
				 * do tipo ProductCode. */

				catalog->vec[index] = createBSTree(((unsigned int) strlen(code) + 1),
				                                   cmp, catalog->printP);
			}
			addBSTree(catalog->vec[index], code);
		}
	}

	return catalog;
}


/**
 *  @brief Verifica se existe um dado produto no catálogo.
 *
 *  Procura por code no catálogo, caso este tenha sido previamente
 *  inicializado. A função de procura segue o critério da função de
 *  comparação fornecida.
 *
 *  @param catalog Apontador para o catálogo.
 *  @param code    Produto a procurar.
 *  @return Retorna true caso o produto exista no catálogo ou false
 *          caso contrário.
 */
bool containsProduct(const ProductCtlg catalog, const char *code)
{
	unsigned int index = 0;
	bool b = false;

	if (catalog != NULL && catalog->vec != NULL) {
		index = getProductHash(*code);

		if (index < SIZE && index >= 0) {
			if (containsBSTree(catalog->vec[index], code) == true) {
				b = true;
			}
		}
	}

	return b;
}

/*****************************************************************************
 * END ADD, SEARCH AND REMOVE                                                *
 *****************************************************************************/


/*****************************************************************************
 * BEGIN NAVIGATION                                                          *
 *****************************************************************************/

/**
 *  @brief Inicia o iterador com uma nova pesquisa no catálogo de produtos.
 *         Devolve o número de elementos guardados no iterator, ou seja,
 *         o número de produtos começados pela cadeia de caracteres x.
 *
 *  Começa-se por testar se o catálogo realizar uma pesquisa
 *  foi previamente inicializado. Caso este exista é criado um iterador com
 *  todos os elementos que satisfazem esta pesquisa.
 *  Se x apenas contém uma letra do alfabeto então todos os códigos
 *  correspondentes a essa letra são filtrados para o iterador.
 *  Se x for uma sequência de caracteres filtra-se para o iterador todos os
 *  elementos que sejam iniciados por essa sequência.
 *
 *  @param catalog Apontador para o catálogo.
 *  @param x       Cadeia de caracteres pelos quais os códigos de produto
 *                 começam.
 *  @return Número de produtos que satisfazem a pesquisa. O resultado da
 *          pesquisa é guardado em catalog->it.
 */
unsigned int productsBeginningWithX(const ProductCtlg catalog,
                                    const ProductCode x)
{
	unsigned int num_elem = 0; /* Número de elementos do iterador, ou seja,
	                            * número de códigos de produto começados por
	                            * x. */

	unsigned int index = 0;

	if (catalog != NULL && catalog->vec != NULL && x != NULL) {

		/* O catálogo existe, logo cria-se o iterador. */

		initIterator(catalog);

		index = getProductHash(*x);

		if (index < SIZE && index >= 0) {

			if (strlen(x) == 1) {

				/* X apenas contém um caráter então seleciona todos os códigos
				 * começados por esse caráter. */

				catalog->it = toIteratorInOrderBSTree(catalog->vec[index]);
			}
			else if (strlen(x) > 1) {

				/* Filtra-se da BSTree correspondente ao primeiro caráter de x
				 * todos os elementos que contenham toda a sequência de caracteres x. */

				catalog->it = filterWithPredBSTree(catalog->vec[index],
				              x, cond);
				}
		}

		/* Número total de elementos que satisfazem a pesquisa. */

		num_elem = getSizeIterator(catalog->it);
	}

	return num_elem;
}


/**
 *  @brief Vai para a página num_page de uma pesquisa realizada no catálogo
 *         de produtos.
 *
 *  A função começa por testar se o catálogo foi previamente inicializado e se
 *  já houve alguma pesquisa neste, ou seja, se o iterador deste catálogo não
 *  é nulo. Caso todas estas condições se verifiquem num_page é convertido para
 *  um índice válido do iterador e são mostradas x posições deste iterador (em
 *  que x = tamanho de página deste catálogo).
 *
 *  @param catalog  Apontador para o catálogo.
 *  @param num_page Número da página a imprimir.
 *  @return Retorna o número de produtos impressos na página num_page, caso
 *          num_page não seja válida retorna 0.
 */
unsigned int goToProductPage(const ProductCtlg catalog,
                            const unsigned int num_page)
{
	unsigned int num_products = 0; /* Número de produtos da página num_page. */

	if (catalog != NULL && catalog->it != NULL) {

		/* Testa se num_page é válida, ou seja, se está compreendida entre a
		 * página 1 e a última página. */

		if (num_page > 0 && num_page <= getNumProductPages(catalog)) {

			/* A página deste catálogo é atualizada para num_page. */

			catalog->page = num_page;

			/* Converte num_page para o índice correspondente do iterador.
			 * Invoca a função goToIterator para alterar o seu índice. */

			goToIterator(catalog->it, (num_page - 1) * catalog->page_size);

			num_products = printProductPage(catalog);
		}
	}

	return num_products;
}


/**
 *  @brief Mostra a próxima página de uma pesquisa no catálogo de produtos.
 *
 *  Começa por testar se o catálogo foi previamente inicializado, bem como
 *  o iterador deste. Caso estas condições se verifiquem é realizado a
 *  impressão da próxima página a não ser que a última página já tenha sido
 *  impressa anteriormente.
 *
 *  @param catalog Apontador para o catálogo.
 *  @return Número de produtos impressos, caso a página não seja válida
 *          retorna 0.
 */
unsigned int nextProductPage(const ProductCtlg catalog)
{
	unsigned int num_products = 0; /* Número de produtos da próxima página. */

	if (catalog != NULL && catalog->it != NULL) {

		/* Testa se a página a imprimir não é a última página. */

		if (catalog->page < getNumProductPages(catalog)) {
			num_products = printProductPage(catalog);

			/* Atualiza a página do catálogo, passando esta a ser incrementada. */

			catalog->page++;
		}
	}

	return num_products;
}


/**
 *  @brief Mostra a página anterior de uma pesquisa no catálogo de produtos.
 *
 *  Começa por testar se o catálogo foi previamente inicializado, bem como
 *  o iterador deste. Caso estas condições se verifiquem é realizada a
 *  impressão da página anterior a não ser que a última página impressa tenha
 *  sido a primeira página da pesquisa.
 *
 *  @param catalog Apontador para o catálogo.
 *  @return Número de produtos impressos, caso a página não seja válida
 *          retorna 0.
 */
unsigned int previousProductPage(const ProductCtlg catalog)
{
	unsigned int num_products = 0; /* Número de produtos da página anterior. */
	unsigned int total_pages = 0;
	unsigned int aux_page = 0;

	if (catalog != NULL && catalog->it != NULL) {

		/* Testa se a página a imprimir não é a primeira página. */

		if (catalog->page > 1) {
			total_pages = getNumProductPages(catalog);

			/* Converte o número da página anterior para um índice válido do
			 * iterador. Supondo que se mostram 20 produtos por página, ao mostrar-se
			 * a página anterior tem que se fazer recuar no iterador os 20 produtos
			 * da página atual mais os 20 produtos da página anterior. */

			if (catalog->page < total_pages) {

				/* Converte o número da página anterior para um índice válido do
				 * iterador. Supondo que se mostram 20 produtos por página, ao
				 * mostrar-se a página anterior tem que se fazer recuar no iterador os
				 * 20 produtos da página atual mais os 20 produtos da página
				 * anterior. */

				goToIterator(catalog->it,
				             getIndexIterator(catalog->it) - (2 * catalog->page_size));
			}
			else {

				/* Neste caso pretende-se navegar da última página para a penúltima.
				 * Como a última página pode não conter tantos códigos quanto o
				 * número de códigos impressos por página, tem que se calcular o
				 * número de códigos impressos na última página.
				 * Começa-se por subtrair ao número de elementos totais do iterador
				 * o tamanho de página vezes o número total de páginas menos um.
				 * Com este resultado obtemos o número de códigos impressos
				 * na última página. */

				aux_page = getSizeIterator(catalog->it) -
				           (catalog->page_size * (total_pages - 1));

				num_products = aux_page;

				/* O índice da última página consite em subtrair ao iterador
				 * a soma do resultado obtido acima com o tamanho de página - 1.
				 */

				aux_page += catalog->page_size - 1;

				goToIterator(catalog->it,
				             getIndexIterator(catalog->it) - (aux_page));

			}

			if (num_products > 0) {
				printProductPage(catalog);
			}
			else {
				num_products = printProductPage(catalog);
			}

			/* Atualiza a página do catálogo sendo esta descrementada uma unidade. */

			catalog->page--;
		}
	}

	return num_products;
}


/*****************************************************************************
 * END NAVIGATION                                                            *
 *****************************************************************************/


/*****************************************************************************
 * BEGIN MAPS                                                                *
*****************************************************************************/

/**
 *  Efetua uma função a cada código de produto presente no catálogo caso o
 *  catálogo exista.
 *
 *  @param catalog Apontador para o catálogo.
 *  @param f       Função a efetuar a cada código de produto.
 *  @return Void. O resultado é guardado em catalog.
 */
void mapProductCtlg(const ProductCtlg catalog, void(*f)(void *product))
{
	unsigned int i = 0;

	if(catalog != NULL) {
		for(; i < SIZE; i++) {
			if(catalog->vec[i] != NULL) {
				mapBSTree(catalog->vec[i], f);
			}
		}
	}
}

/*****************************************************************************
 * END MAPS                                                                  *
 *****************************************************************************/

/*****************************************************************************
 * END PUBLIC                                                                *
 *****************************************************************************/
