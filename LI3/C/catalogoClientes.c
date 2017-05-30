/**
 *  @file catalogoClientes.c
 *  @brief Os códigos dos clientes são armazenados num array de BSTree's.
 *
 *  O array tem 26 posições. Cada posição corresponde à diferença entre
 *  o valor da 1ª letra do código de cliente e a letra 'A', em ASCII.
 *  Definição de todas as funções pertencentes à interface deste módulo, bem
 *  como todos os seus métodos auxiliares.
 *
 *  @author Carlos Pereira - A61887
 *  @author Diogo Silva    - A76407
 *  @author Rafael Braga   - A61799
 *
 *  @bug ?
 *  @version 3.1
 */

#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include "bstree.h"
#include "iterator.h"
#include "catalogoClientes.h"


#define SIZE 26               /* Nº de posições do array.
                               *  Cada posição é uma letra do alfabeto. */
#define DEFAULT_PAGE_SIZE 20  /* Número de códigos de clientes impressos por
                               * página. */


/*  Tipo do catálogo de clientes. */

struct clientCtlg {
	BSTree *vec;            /* Array de BSTree's que irá conter os códigos
	                         * de clientes.*/

	Iterator it;            /* Iterador sobre o catálogo de clientes. */

	unsigned int page_size; /* Tamanho de uma página de códigos de clientes. */
	unsigned int page;      /* Página atual. */
	printClient print;      /* Função de impressão de um cliente. */
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
 *  do código de cliente e a letra 'A', em ASCII.
 *
 *  @param code Código do cliente a determinar o índice.
 *  @return Devolve o índice correspondente.
 */
static unsigned int getClientHash(const char code)
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
 *  Esta função admite que o catálogo de clientes e o seu
 *  iterador tenham sido já inicializados. Também
 *  admite que a página a ser impressa é válida. O número
 *  de elementos percorridos no iterador é igual ao número de códigos
 *  impressos por página.
 *  O ciclo termina caso se chegue ao fim do iterador.
 *
 *  @param catalog Apontador para o catálogo.
 *  @return Devolve o número de clientes impressos.
 */
static unsigned int printClientPage(const ClientCtlg catalog)
{
	unsigned int i = 0; /* Controlo do ciclo for e número de clientes
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
 *  Função para verificar se um código de cliente presente na árvore binária
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
static void initIterator(const ClientCtlg catalog)
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
 *  @brief Cria e inicializa o catálogo de clientes.
 *
 *  O catálogo de clientes corresponde a um vector com 26 posições. Cada
 *  posição corresponde à diferença entre o valor da 1ª letra do código de
 *  cliente e a letra 'A', em ASCII. Cada posição deste array contém
 *  uma BSTree de códigos que começam pela mesma letra do alfabeto.
 *
 *  Aloca espaço para a raiz da árvore binária. Guarda a informação
 *  da função que faz a impressão de um elemento no ecrã, como também cria
 *  um array com 26 posições.
 *
 *  A árvore armazena os códigos maiores à direita e os menores
 *  à esquerda.
 *
 *  @param print Função para realizar a impressão de um código de cliente.
 *  @return Apontador para o catálogo dos clientes.
 */
ClientCtlg createClientCtlg(printClient print)
{
	unsigned int i = 0;
	ClientCtlg catalog = malloc(sizeof(struct clientCtlg));

	if (catalog == NULL) {

		/* Se o malloc do catálogo falhar tenta-se fazer o realloc deste. */

		catalog = realloc(catalog, sizeof(struct clientCtlg));

		/* Se o realloc do catálogo falhar o programa termina. */

		assert(catalog != NULL);
	}

	/* Aloca-se espaço para o array de BSTree's. */

	catalog->vec = malloc(SIZE * sizeof(BSTree));

	if (catalog->vec == NULL) {

		/* Se o malloc falhar é realizado o realloc. */

		catalog->vec = realloc(catalog->vec, SIZE * sizeof(BSTree));

		/* Se o realloc falhar então o programa é terminado. */

		assert(catalog->vec != NULL);
	}

	/* A cada posição do array de BSTree's é inicializada a sua correspondente
	 * árvore binária. */

	for (; i < SIZE; i++) {
		catalog->vec[i] = NULL;
	}

	catalog->it = NULL;
	catalog->page_size = DEFAULT_PAGE_SIZE;
	catalog->page = 0;
	catalog->print = print;

	return catalog;
}


/**
 *  @brief Liberta a memória ocupada pelo catálogo.
 *
 *  Faz o free para cada BSTree do array. No final, liberta a memória
 *  do catálogo de clientes.
 *  Se o catálogo for nulo, a função não tem efeito.
 *
 *  @param catalog Apontador para o catálogo.
 *  @return Void.
 */
void destroyClientCtlg(ClientCtlg catalog)
{
	unsigned int i = 0;

	if (catalog != NULL) {
		if (catalog->vec != NULL) {

			/* Destroi todas as posições do array de BSTree's. */

			for (; i < SIZE; i++) {
				destroyBSTree(catalog->vec[i]);
			}

			/* Destroi o array. */

			free(catalog->vec);
			catalog->vec = NULL;
		}

		/* Destroi o iterador. */

		destroyIterator(catalog->it);

		/* Finalmente destroi a estrutura do catálogo. */

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
 *  Devolve o número total de páginas de códigos de cliente.
 *  O número total de páginas é calculado através da divisão da última
 *  posição do iterador com o tamanho pré-definido de uma página de cliente.
 *  O valor devolvido é arredondado por excesso.
 *
 *  @param catalog Apontador para o catálogo.
 *  @return Número de páginas de códigos de cliente.
 */
unsigned int getNumClientPages(const ClientCtlg catalog)
{
	unsigned int num = 0; /* Número total de páginas. */
	double aux = 0;       /* Valor real auxiliar para efetuar o arredondamento
	                       * do número de páginas por excesso. */

	if (catalog->it != NULL) {
		aux = ((double) getSizeIterator(catalog->it)) / catalog->page_size;

		/* num recebe o valor total de páginas arredondadas por defeito. */

		num = (unsigned int) aux;

		/* Se a subtração ao valor total de páginas com o valor de num for
		 * maior que zero é sinal que o número de páginas deve ser
		 * incrementado. */

		if (aux - num > 0) {
			num++;
		}
	}

	return num;
}


/**
 *  Devolve o tamanho de página de códigos de cliente.
 *
 *  @param catalog Apontador para o catálogo.
 *  @return Devolve catalog->page_size caso este exista ou
 *          DEFAULT_PAGE_SIZE caso contrário.
 */
unsigned int getClientPageSize(const ClientCtlg catalog)
{
	unsigned int page_size = (catalog != NULL)
	                          	? catalog->page_size
	                          	: DEFAULT_PAGE_SIZE;

  return page_size;
}


/**
 *  Modifica o tamanho de uma página de códigos de cliente caso
 *  o catálogo tenha sido previamente inicializado.
 *
 *  @param catalog   Apontador para o catálogo.
 *  @param page_size Novo tamanho de página de códigos de cliente.
 *  @return Void. O resultado é guardado em catalog.
 */
void setClientPageSize(const ClientCtlg catalog, const unsigned int page_size)
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
 *  @brief Adiciona um cliente ao catálogo de clientes.
 *
 *  Se o catálogo já tiver sido criado e inicializado, adiciona um
 *  código de cliente. O cliente é adicionado conforme a função de
 *  comparação dada.
 *
 *  @param catalog Apontador para o catálogo de clientes.
 *  @param code    Cliente a adicionar.
 *  @return Devolve o apontado para o catálogo.
 */
ClientCtlg addClient(ClientCtlg catalog, const ClientCode code)
{
	unsigned int index = 0;

	if (catalog != NULL) {
		index = getClientHash(*code);

		if (index < SIZE) {
			if (catalog->vec[index] == NULL) {

				/* Se a árvore correspondente ao índice da primeira letra de code
				 * for nula cria-a. É reservado tamanho suficiente na árvore para
				 * que consiga suportar dados do tipo ClientCode. */

				catalog->vec[index] = createBSTree(((unsigned int)strlen(code) + 1),
				                                   cmp, catalog->print);
			}

			addBSTree(catalog->vec[index], code);
		}
	}

	return catalog;
}


/**
 *  @brief Verifica se existe um dado cliente no catálogo.
 *
 *  Procura por code no catálogo, caso este tenha sido previamente
 *  inicializado. A função de procura segue o critério da função de
 *  comparação fornecida.
 *
 *  @param catalog Apontador para o catálogo.
 *  @param code    Cliente a procurar.
 *  @return Devolve true caso o cliente exista no catálogo ou false
 *          caso contrário.
 */
bool containsClient(const ClientCtlg catalog, const char *code)
{
	unsigned int index = 0;
	bool b = false;

	if (catalog != NULL && catalog->vec != NULL) {
		index = getClientHash(*code);

		if (index < SIZE) {
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
 *  @brief Inicia o iterador com uma nova pesquisa no catálogo de clientes.
 *         Devolve o número de elementos guardados no iterator, ou seja,
 *         o número de clientes começados pela cadeia de caracteres x.
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
 *  @param x       Cadeia de caracteres pelos quais os códigos de cliente
 *                 começam.
 *  @return Número de clientes que satisfazem a pesquisa. O resultado da
 *          pesquisa é guardado em catalog->it.
 */
unsigned int clientsBeginningWithX(const ClientCtlg catalog,
                                   const ClientCode x)
{
	unsigned int num_elem = 0; /* Número de elementos do iterador, ou seja,
	                            * número de códigos de cliente começados por
	                            * x. */

	unsigned int index = 0;

	if (catalog != NULL && catalog->vec != NULL && x != NULL) {

		/* O catálogo existe, logo cria-se o iterador. */

		initIterator(catalog);

		index = getClientHash(*x);

		if (index < SIZE) {

			if (strlen(x) == 1) {

				/* X apenas contém um caráter então seleciona todos os códigos
				 * começados por esse caráter. */

				catalog->it = toIteratorInOrderBSTree(catalog->vec[index]);
			}
			else if (strlen(x) > 1) {

				/* Filtra-se da BSTree correspondente ao primeiro caráter de x
				 * todos os elementos que contenham toda a sequência de
				 * caracteres x. */

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
 *  Filtra para o iterador do catálogo todos os clientes que satisfizerem f.
 *
 *  @param catalog Apontador para o catálogo.
 *  @param f       Função que recebe como parâmetro um código de cliente.
 *                 Se o resultado desta função for true o cliente é
 *                 adicionado ao iterador do catálogo.
 *  @return Número de códigos de cliente que foram adicionados ao iterador
 *          do catálogo.
 */
unsigned int filterClients(const ClientCtlg catalog, bool (*f)(const void*))
{
	unsigned int num_elem = 0;
	unsigned int i = 0;

	if (catalog != NULL && catalog->vec != NULL) {

		/* Destroi o iterador do catálogo caso este já contenha dados relativos
		 * a uma pesquisa qualquer. */

		initIterator(catalog);

		/* Cria um iterador sobre o catálogo. */

		catalog->it = createIterator(sizeof(ClientCode), catalog->print);

		for (; i < SIZE; i++) {

			/* Adiciona ao iterador todos os códigos de cliente que verifiquem f. */

			filterToIteratorBSTree(catalog->vec[i], catalog->it, f);
		}

		num_elem = getSizeIterator(catalog->it);
	}

	return num_elem;
}


/**
 *  @brief Vai para a página num_page de uma pesquisa realizada no catálogo
 *         de clientes.
 *
 *  A função começa por testar se o catálogo foi previamente inicializado e se
 *  já houve alguma pesquisa neste, ou seja, se o iterador deste catálogo não
 *  é nulo. Caso todas estas condições se verifiquem num_page é convertido para
 *  um índice válido do iterador e são mostradas x posições deste iterador (em
 *  que x = tamanho de página deste catálogo).
 *
 *  @param catalog  Apontador para o catálogo.
 *  @param num_page Número da página a imprimir.
 *  @return Retorna o número de clientes impressos na página num_page, caso
 *          num_page não seja válida retorna 0.
 */
unsigned int goToClientPage(const ClientCtlg catalog,
                            const unsigned int num_page)
{
	unsigned int num_clients = 0; /* Número de clientes da página num_page. */

	if (catalog != NULL && catalog->it != NULL) {

		/* Testa se num_page é válida, ou seja, se está compreendida entre a
		 * página 1 e a última página. */

		if (num_page > 0 && num_page <= getNumClientPages(catalog)) {

			/* A página deste catálogo é atualizada para num_page. */

			catalog->page = num_page;

			/* Converte num_page para o índice correspondente do iterador.
			 * Invoca a função goToIterator para alterar o seu índice. */

			goToIterator(catalog->it, (num_page - 1) * catalog->page_size);

			num_clients = printClientPage(catalog);
		}
	}

	return num_clients;
}


/**
 *  @brief Mostra a próxima página de uma pesquisa no catálogo de clientes.
 *
 *  Começa por testar se o catálogo foi previamente inicializado, bem como
 *  o iterador deste. Caso estas condições se verifiquem é realizado a
 *  impressão da próxima página a não ser que a última página já tenha sido
 *  impressa anteriormente.
 *
 *  @param catalog Apontador para o catálogo.
 *  @return Número de clientes impressos, caso a página não seja válida
 *          retorna 0.
 */
unsigned int nextClientPage(const ClientCtlg catalog)
{
	unsigned int num_clients = 0; /* Número de clientes da próxima página. */

	if (catalog != NULL && catalog->it != NULL) {

		/* Testa se a página a imprimir não é a última página. */

		if (catalog->page < getNumClientPages(catalog)) {
			num_clients = printClientPage(catalog);

			/* Atualiza a página do catálogo, passando esta a ser incrementada. */

			catalog->page++;
		}
	}

	return num_clients;
}


/**
 *  @brief Mostra a página anterior da última pesquisa no catálogo de clientes.
 *
 *  Começa por testar se o catálogo foi previamente inicializado, bem como
 *  o iterador deste. Caso estas condições se verifiquem é realizada a
 *  impressão da página anterior a não ser que a última página impressa tenha
 *  sido a primeira página da pesquisa.
 *
 *  @param catalog Apontador para o catálogo.
 *  @return Número de clientes impressos, caso a página não seja válida
 *          retorna 0.
 */
unsigned int previousClientPage(const ClientCtlg catalog)
{
	unsigned int num_clients = 0; /* Número de clientes da página anterior. */
	unsigned int total_pages = 0;
	unsigned int aux_page = 0;

	if (catalog != NULL && catalog->it != NULL) {

		/* Testa a página a imprimir não é a primeira página. */

		if (catalog->page > 1) {
			total_pages = getNumClientPages(catalog);

			/* Converte o número da página anterior para um índice válido do
			 * iterador. Supondo que se mostram 20 clientes por página, ao mostrar-se
			 * a página anterior tem que se fazer recuar no iterador os 20 clientes
			 * da página atual mais os 20 clientes da página anterior. */

			if (catalog->page < total_pages) {

				/* Converte o número da página anterior para um índice válido do
				 * iterador. Supondo que se mostram 20 clientes por página, ao
				 * mostrar-se a página anterior tem que se fazer recuar no iterador os
				 * 20 clientes da página atual mais os 20 clientes da página
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

				num_clients = aux_page;

				/* O índice da última página consite em subtrair ao iterador
				 * a soma do resultado obtido acima com o tamanho de página - 1.
				 */

				aux_page += catalog->page_size - 1;

				goToIterator(catalog->it,
				             getIndexIterator(catalog->it) - (aux_page));

			}

			if (num_clients > 0) {
				printClientPage(catalog);
			}
			else {
				num_clients = printClientPage(catalog);
			}

			/* Atualiza a página do catálogo sendo esta descrementada uma unidade. */

			catalog->page--;
		}
	}

	return num_clients;
}



/*****************************************************************************
 * END NAVIGATION                                                            *
 *****************************************************************************/


/*****************************************************************************
 * BEGIN FOLDS                                                               *
 *****************************************************************************/

/**
 *  Cria uma qualquer estrutura de dados caso o catálogo exista.
 *
 *  @param catalog Apontador para o catálogo.
 *  @param acc     Acumulador da nova estrutura de dados.
 *  @param f       Função para atualizar acc conforme cada código de cliente.
 *  @return Void. O resultado é guardado em acc.
 */
void foldClients(const ClientCtlg catalog, void *acc,
                 void (*f)(const void *value, void *acc))
{
	unsigned int i = 0;

	if (catalog != NULL) {
		for(; i < SIZE; i++) {
			foldBSTree(catalog->vec[i], acc, f);
		}
	}
}

/*****************************************************************************
 * END FOLDS                                                                 *
 *****************************************************************************/

/*****************************************************************************
 * END PUBLIC                                                                *
 *****************************************************************************/
