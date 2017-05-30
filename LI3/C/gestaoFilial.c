/**
 *  @file gestaoFilial.c
 *
 *  O armazenamento dos informações da filial é feito numa BSTMap.
 *  As funções de criação, remoção, procura e de travessia já foram criadas
 *  no módulo da BSTMap. Este módulo irá servir-se dessas funções para
 *  que possa ser feita a gestão das filiais.
 *
 *  @author Carlos Pereira - A61887
 *  @author Diogo Silva    - A76407
 *  @author Rafael Braga   - A61799
 *
 *  @bug ?
 *  @version 4.1
 */

#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include "bstmap.h"
#include "gestaoFilial.h"


#define DEFAULT_PAGE_SIZE 10  /* Número de códigos impressos por página. */
#define NUM_MODES 2           /* Número de modos (N e P). */
#define DEFAULT_MONTHS 12     /* Valor por defeito de meses. */


/*Tipos de venda para o problema em questão.*/

#define N 'N'
#define P 'P'


/*Tipo de nó de dados a ser armazenado na BSTMap.*/

struct sale {
	char *product;      /* Código de produto. */
	double price;       /* Preço de uma unidade de um produto. */
	unsigned int units; /* Número de unidades compradas de um produto. */
	char type;          /* Tipo de compra de um produto. */
};


/*Estrutura do catálogo das informações relativas à filial.*/

struct branchCtlg {
	BSTMap *sales;                      /* Apontador para uma BSTMap em que a
	                                     * chave é um código de cliente. */
	Iterator mode_it[NUM_MODES];        /* Apontador para iterador onde a
	                                     * impressão tem de distinguir a venda
	                                     * por tipo (N ou P).*/
	unsigned int mode_pages[NUM_MODES]; /* Número de elementos por página do
	                                     * de cada iterador modo N ou P. */


	unsigned int page_size;             /* Número de elementos numa página do
	                                     * iterador de modos. */
	unsigned int page;                  /* Página atual no iterador. */

	unsigned int size;                  /* Número de meses da gestão de
	                                     * filial .*/

	printSaleCode printSC;              /*Função que faz a impressão de um
	                                     * código de produto. */
	printSaleBranch printS;             /* Função que faz a impressão de uma
	                                     * venda. */

	unsigned int client_size;           /* Tamanho de um código de cliente. */
};


/*****************************************************************************
 * BEGIN PRIVATE                                                             *
 *****************************************************************************/

/*****************************************************************************
 * BEGIN PRINT FUNCTIONS                                                     *
 *****************************************************************************/

/**
 *  Faz a impressão de uma página da pesquisa do tipo de venda.
 *
 *  @param catalog  Apontador para o catálogo da filial.
 *  @param mode     Variável que indica o tipo de venda.
 *  @return Void.
 */
static void printModePage(const BranchCtlg catalog, const char mode)
{
	unsigned int i = 0;                       /* Controlo do ciclo for e número
	                                           * de clientes impressos. */
	unsigned int index = (mode == N) ? 0 : 1; /* Atribui a posição no array de
	                                           * iteradores correspondente
	                                           * ao tipo de venda. */

	for (; i < catalog->page_size; i++) {

		/* Faz a impressão do elemento atual do iterador. */

		 printCurrentIterator(catalog->mode_it[index]);

		/* Verifica se o elemento atual da página tem mais um elemento
		 *  a seguir antes que termine a página.*/

		if (hasNextIterator(catalog->mode_it[index]) == true) {

			/*Incrementa o valor do elemento atual do iterador.*/

			nextIterator(catalog->mode_it[index]);
		}
		else {

			/*Não tem mais elementos a imprimir nesta página.*/

			break;
		}
 	}
}

/*****************************************************************************
 * END PRINT FUNCTIONS                                                     *
 *****************************************************************************/

/*****************************************************************************
 * BEGIN DATA STRUCTURES AUXILIARY FUNCTIONS                                 *
 *****************************************************************************/

/**
 *  Função que faz a comparação entre duas chaves da árvore BSTMap.
 *
 *  @param a Chave a comparar.
 *  @param b Chave a comparar.
 *  @return < 0 se a chave a for menor que a chave b
 *          0  se a chaves a e b forem iguais
 *          > 0 se a chave a for maior que a chave b
 */
static int cmpKey(const void *a, const void *b)
{
	return strcmp((char*) a, (char*) b);
}


/**
 *  Função que faz a comparação das unidades de duas vendas. Caso sejam
 *  iguais em unidades, comparam-se os códigos (de produtos ou de vendas).
 *
 *
 *  @param a Chave a comparar.
 *  @param b Chave a comparar.
 *  @return < 0 se a chave a for menor que a chave b
 *          0  se a chaves a e b forem iguais
 *          > 0 se a chave a for maior que a chave b
 */
static int cmpSales(const void *a, const void *b)
{
	/* Como os nós na árvore BST são do tipo void*, primeiro é preciso fazer
	 * o cast para uma estrutura concreta - neste caso é Sale.*/

	Sale s1 = (Sale) a;
	Sale s2 = (Sale) b;
	int r = 0;

	/*Começa-se por comparar as unidades.*/

	if (s1->units > s2->units) {
		r = 1;
	}
	else if (s1->units < s2->units) {
		r = -1;
	}
	else {

		/* Caso as vendas tenham o mesmo número de unidades, comparam-se os
		 * os códigos de produto. */

		r = strcmp(s1->product, s2->product);
	}

	return r;
}


/**
 *  Função que acrescenta a um acumulador as unidades de uma venda.
 *
 *  @param a   Venda com as unidades a somar.
 *  @param acc Acumulador que vai ser somado com as unidades de venda.
 *  @return Void. O resultado é devolvido em acc.
 */
static void sumTotalUnits(const void *a, void *acc)
{
	Sale s = (Sale) a;

	(*(unsigned int*) acc) += s->units;
}



/**
 *  Função para apagar uma estrutura de uma venda.
 *
 *  @param a  Venda a apagar.
 *  @return Void.
 */
static void deleteSale(void *a)
{
	Sale s = (Sale) a;

	if (s != NULL) {
		if (s->product != NULL) {
			free(s->product);
			s->product = NULL;
		}

		free(s);
		s = NULL;
	}
}


/**
 *  Função que acrescenta um cliente ao iterador de modos caso este tenha
 *  comprado um determinado produto.
 *
 *  @param client   Cliente a adicionar.
 *  @param value    Venda efetuada por um cliente.
 *  @param product  Produto a testar.
 *  @param it_mode  Iterador de modos N e P.
 *  @return Void.
 */
static void selectMode(const void *client, const void *value,
                       const void *product, void *it_mode)
{
	char *aux_client = (char*) client;
	char *aux_product = (char*) product;
	Sale s = (Sale) value;

	if (strcmp(s->product, aux_product) == 0) {
		if (s->type == N) {
			addIterator(((Iterator*) it_mode)[0], aux_client);
		}
		else {
			addIterator(((Iterator*) it_mode)[1], aux_client);
		}
	}
}

/*****************************************************************************
 * END DATA STRUCTURES AUXILIARY FUNCTIONS                                   *
 *****************************************************************************/


/*****************************************************************************
 * BEGIN NAVIGATION                                                          *
 *****************************************************************************/

/**
 *  Função que inicializa o iterador de tipos de venda. Caso o iterador
 *  já tenha sido utilizado, a função apaga os dados que já lá estavam.
 *
 *  @param catalog Apontador para o catálogo.
 *  @param i       Variável que informa a função o tipo de venda.
 *
 *  @return Void.
 */
static void initModeIterator(BranchCtlg catalog, const unsigned int i)
{
	if (catalog->mode_it[i] != NULL && catalog->mode_pages != NULL) {
		destroyIterator(catalog->mode_it[i]);
		catalog->mode_pages[i] = 0;
	}
}

/*****************************************************************************
 * END NAVIGATION                                                          *
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
 *  @brief Criação do catálogo de filial.
 *
 *  Recebe toda a informação necessária para a criação do catálogo de filial.
 *  Como já existe o módulo de BSTMap, chama-se a função createBSTMap de
 *  maneira a criar uma BSTMap, passando-lhe os parâmetros necessários.
 *  O processo de criação de BSTMap é feito as vezes que forem enviadas como
 *  parâmetro.
 *
 *  @param printSC  Função para fazer a impressão de um código de cliente.
 *  @param printS   Função para fazer a impressão de uma venda.
 *  @param size     Número elementos do array de BSTMap (número de meses).
 *  @return Devolve o apontador para o catálogo de filial.
 */
BranchCtlg createBranchCtlg(printSaleCode printSC,
                            printSaleBranch printS,
                            const unsigned int size)
{
	unsigned int i = 0;

	/* Alocação de espaço para o apontador para o catálogo da filial. */

	BranchCtlg catalog = malloc(sizeof(struct branchCtlg));

	if (catalog == NULL) {

		/* Caso a alocação não tenha sido bem feita, faz-se um realloc. */

		catalog = realloc(catalog, sizeof(struct branchCtlg));

		/* Caso o realloc falhe, o programa termina e imprime uma mensagem
		 * a informar.*/

		assert(catalog != NULL);
	}

	catalog->size = size;
	catalog->printSC = printSC;
	catalog->printS = printS;

	/* Alocação de espaço para o array de número de meses de árvores BSTMap. As
	 * chaves nas árvores BSTMap deste array estão ordenadas por código de
	 * cliente. */

	catalog->sales = malloc(size * sizeof(BSTMap));

	if(catalog->sales == NULL) {

		/* Caso a alocação não tenha sido bem feita, faz-se um realloc. */

		catalog->sales = realloc(catalog->sales, size * sizeof(BSTMap));

		/* Caso o realloc falhe, o programa termina e imprime uma mensagem
		 * a informar.*/

		assert(catalog->sales != NULL);
	}

	for(; i < size; i++) {

		/* Criação de uma árvore BSTMap em cada elemento do array. */

		catalog->sales[i] = NULL;
	}

	for(i = 0; i < NUM_MODES; i++) {
		catalog->mode_it[i] = NULL;
		catalog->mode_pages[i] = 0;
	}


	/* Os restantes parâmetros e valores por defeitos são acrescentados à
	 * estrutura do catálogo.*/

	catalog->page = 0;
	catalog->page_size = DEFAULT_PAGE_SIZE;
	catalog->client_size = 0;

	return catalog;
}


/**
 *  Construtor por defeito da gestão de uma filial.
 *  Apenas invoca o construtor por parâmetros com o número de meses por
 *  defeito.
 *
 *  @param printSC  Função para imprimir um código de cliente.
 *  @param printS   Função para imprimir uma venda.
 *  @return Devolve o catálogo de vendas.
 */
BranchCtlg defaultCreateBranchCtlg(printSaleCode printSC,
                                   printSaleBranch printS)
{
	return createBranchCtlg(printSC, printS, DEFAULT_MONTHS);
}


/**
 *  @brief Destruição do catálogo de filial.
 *
 *  Liberta a memória ocupada pelo catálogo de filial.
 *
 *  @param catalog Apontador para a estrutura do catálogo de filial.
 *  @return Void
 */
void destroyBranchCtlg(BranchCtlg catalog)
{
	unsigned int i = 0;

	/* Apenas liberta a memória caso o apontador exista. */

	if(catalog != NULL) {

		/* Apenas liberta a memória ocupada pelos arrays caso existam. */

		if (catalog->sales != NULL) {

			/* Em cada posição do array de árvores BSTMap, chama-se a
			 * respectiva função de destruição. */

			for(; i < catalog->size; i++) {
				destroyBSTMap(catalog->sales[i]);
			}

			/* Libertação do apontador para o array em que as chaves são
			 * códigos de cliente.*/

			free(catalog->sales);
			catalog->sales = NULL;
		}

		for(i = 0; i < NUM_MODES; i++) {
			destroyIterator(catalog->mode_it[i]);
		}

		/* Libertação do apontador para o catálogo de filial. */

		free(catalog);
		catalog = NULL;
	}
}

/*****************************************************************************
 * END CONSTRUCTORS AND DESTRUCTORS                                          *
 *****************************************************************************/


/*****************************************************************************
 * BEGIN GETS AND SETS                                                       *
 *****************************************************************************/

/**
 *  Função que devolve o código de produto de uma venda.
 *
 *  @param sale Venda.
 *  @return Código de produto de uma venda.
 */
char* getProduct(const Sale sale)
{
	return sale->product;
}


/**
 *  Função que devolve o preço de uma venda.
 *
 *  @param sale Venda.
 *  @return Preço de uma venda.
 */
double getPrice(const Sale sale)
{
	return sale->price;
}


/**
 *  Função que devolve as unidades de uma venda.
 *
 *  @param sale Venda.
 *  @return Unidades da venda.
 */
unsigned int getUnits(const Sale sale)
{
	return sale->units;
}


/**
 *  Função que devolve o tipo de uma venda.
 *
 *  @param sale Venda.
 *  @return Tipo da venda.
 */
char getType(const Sale sale)
{
	return sale->type;
}


/**
 *  Função que calcula o número total de produtos comprados por
 *  um cliente num dado mês.
 *
 *  @param catalog Apontador para o catálogo de filial.
 *  @param client  Código de um cliente a procurar.
 *  @param month   Mês a procurar.
 *  @return Número total de produtos comprados pelo cliente.
 */
unsigned int getTotalProducts(const BranchCtlg catalog, const char *client,
                              const unsigned int month)
{
	unsigned int acc = 0;

	/* Apenas percorre a árvore caso o apontador para o catálogo exista, o
	 * o valor do mês seja válido e o apontador para o código do cliente
	 * exista. */

	if (catalog != NULL && month >= 1 && month <= catalog->size
	    && client != NULL) {

		/* Chamada da função foldValueBSTMap que vai percorrer a árvore de
		 * BSTMap na posição pretendida, com o acumulador , a chave pretendida
		 * e a função a aplicar. */

		foldValueBSTMap(catalog->sales[month - 1], client, &acc,
		                sumTotalUnits);
	}

	return acc;
}


/**
 *  @brief Devolve o número de páginas da pesquisa de cada tipo
 *         de venda.
 *
 *  Começa por testar se o catálogo foi previamente inicializado, bem como
 *  o iterador de cada tipo de venda. Caso estas condições se verifiquem,
 *  efectuam-se os cálculos para determinar o número de páginas.
 *
 *  @param catalog  Apontador para o catálogo da filial.
 *  @param mode     Variável que indica o tipo de venda.
 *  @return Número de páginas do iterador.
 */
unsigned int getNumModePages(const BranchCtlg catalog, const char mode)
{
	unsigned int num = 0; /* Número total de páginas. */
	double aux = 0;       /* Valor real auxiliar para efetuar o arredondamento
	                       * por excesso do número de páginas. */

	/* Verifica se o apontador para o catálogo da filial e o apontador para os
	 * iteradores de cada tipo de venda são válidos. */

	if (catalog != NULL && catalog->mode_it != NULL) {

		if (mode == N) {

			/* Atribui a aux o número de páginas de vendas do tipo N. */

			aux = ((double) getSizeIterator(catalog->mode_it[0])) /
			      catalog->page_size;
		}
		else {

			/* Atribui a aux o número de páginas de vendas do tipo P. */

			aux = ((double) getSizeIterator(catalog->mode_it[1])) /
			      catalog->page_size;
		}

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
 *  Modifica o número de elementos numa página de códigos de cliente caso
 *  o catálogo tenha sido previamente inicializado.
 *
 *  @param catalog    Apontador para o catálogo da filial.
 *  @param page_size  Novo tamanho de página de códigos de cliente.
 *  @return Void.
 */
void setSalePageSize(const BranchCtlg catalog, const unsigned int page_size)
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
 *  @brief Adiciona uma venda a cada array de árvores BSTMap.
 *
 *  Todos os campos da venda são enviados para a função como parâmatros.
 *  A venda é adicionada através da chamada da função addBSTMap.
 *
 *  @param catalog  Apontador para o catálogo da filial.
 *  @param product  Código do produto a acrescentar.
 *  @param price    Preço da venda a acrescentar.
 *  @param units    Unidades vendidas a acrescentar.
 *  @param type     Tipo de venda a acrescentar.
 *  @param client   Código de cliente a acrescentar.
 *  @param month    Mês da venda a acrescentar.
 *  @return Devolve o apontador para o catálogo.
 */
BranchCtlg addSale(BranchCtlg catalog, char *product, const double price,
                   const unsigned int units, const char type,
                   char *client, const unsigned int month)
{
	struct sale s; /* Estrutura que vai ser adicionada às árvores BSTMap
	                * que estão ordenadas por cliente.*/

	/* A venda só é adicionada se o apontador para o catálogo e o mês
	 * e o mês forem válidos.*/

	if (catalog != NULL && month > 0 && month <= catalog->size) {

		/* A venda só é adicionada se os apontadores para os arrays de
		 * árvores BSTMap existirem.*/

		if (catalog->sales != NULL) {

			/* Alocação de espaço para o apontador para o código de produto. */

			s.product = malloc(sizeof(char*));

			if (s.product == NULL) {

				/* Se o malloc falhar, faz-se um realloc. */

				s.product = realloc(s.product, sizeof(char*));

				/* Caso o realloc falhe, o programa termina. */

				assert(s.product != NULL);
			}

			/* Inicialização dos restantes campos da struct sale. Correspondem ao
			 * value das árvores BST contidas nas árvores BSTMap. */

			strcpy(s.product, product);
			s.price = price;
			s.units = units;
			s.type = type;

			/* Testa se a BSTMap correspondente ao mês é nula. Se assim for
			 * cria uma árvore que suporte os códigos de cliente e de produto. */

			if (catalog->sales[month - 1] == NULL) {
				catalog->sales[month - 1] =
				   createBSTMap(((unsigned int) strlen(product) + 1), cmpKey,
				                catalog->printSC, sizeof(struct sale),
				                cmpSales, catalog->printS);

				/* Altera a função para apagar a estrutura de vendas. */

				setDeleteValueBSTMap(catalog->sales[month - 1], deleteSale);
			}

			addBSTMap(catalog->sales[month - 1], client, &s);

			if (catalog->client_size == 0) {
				catalog->client_size = strlen(client) + 1;
			}
		}
	}

	return catalog;
}


/**
 *  @brief Procura o código de um cliente na filial.
 *
 *  Esta função vai a cada posição do array de árvores BSTMap procurar uma
 *  Chave que seja igual ao código de cliente fornecido. Caso encontre antes de
 *  chegar ao fim do ciclo, o ciclo termina.
 *
 *  @param catalog  Apontador para o catálogo da filial.
 *  @param client   Código de cliente a procurar.
 *  @return false se o cliente não existir na filial.
 *          true caso contrário
 */
bool existClientInBranch(const BranchCtlg catalog, const char *client)
{
	bool b = false;      /* Variável que corresponde à existência do cliente na
	                      * filial.*/
	unsigned int i = 0;  /* Variável de controlo de ciclo*/

	/* Apenas começa a procura se o apontador para o catálogo da filial e o
	 * apontador para o código de cliente existirem. */

	if (catalog != NULL && client != NULL) {

		/* Chama-se a função containsKeyBSTMap. Para cada árvore BSTMap
		 * que existe no array, faz um map que compara o código enviado
		 * e as chaves dos nós dessa árvore.*/

		for(; i < catalog->size && b == false; i++) {
			b = containsKeyBSTMap(catalog->sales[i], client);
		}
	}

	return b;
}

/*****************************************************************************
 * END ADD, SEARCH AND REMOVE                                                *
 *****************************************************************************/

/*****************************************************************************
 * BEGIN TREE TRAVERSALS                                                     *
*****************************************************************************/

/**
 *  @brief Aplica uma função com acumulador a todos os produtos comprados
 *         por um cliente num mês na filial.
 *
 *  A partir dos parâmetros recebidos, a função aplica um fold a todas
 *  os valores na árvore BST a ser apontada por uma chave de um nó da BSTMap
 *  que seja igual ao parâmetro (client) fornecido.
 *
 *  @param catalog  Apontador para o catálogo da filial.
 *  @param client   Código de cliente a procurar.
 *  @param month    Mês a procurar pelo cliente.
 *  @param acc      Acumulador da função a aplicar.
 *  @param f        Função a aplicar.
 *  @return Void
 */
void foldClientProductsInMonth(const BranchCtlg catalog, const char *client,
                               const unsigned int month, void *acc,
                               void (*f)(const void *, void *acc))
{

	/* Apenas começa o fold se os apontadores para o catálogo da filial, para o
	 * código de cliente e para o array de árvores BSTMap forem válidos.*/

	if (catalog != NULL && client != NULL && catalog->sales != NULL) {

		/* Chama a função que vai procurar o cliente e aplicar à sua árvore
		 * do tipo BST a função e o respectivo acumulador.*/
		foldValueBSTMap(catalog->sales[month - 1], client, acc, f);
	}
}


/**
 *  @brief Aplica uma função com acumulador a todos os nós das árvores BST a
 *         serem apontadas por todos os nós das árvores BSTMap de todas as
 *         posições do array ordenado por código de cliente na chave.
 *
 *  A partir da função f determinam-se os códigos de produto mais vendidos.
 *
 *  @param catalog  Apontador para o catálogo da filial.
 *  @param acc      Acumulador da função a aplicar.
 *  @param f        Função a aplicar.
 *  @return Void. O resultado é guardado em acc.
 */
 void mostSoldProducts(const BranchCtlg catalog, void *acc,
                       void (*f)(const void *, void *acc))
 {
	unsigned int i = 0;

	/* Apenas começa o fold se os apontadores para o catálogo da filial e para
	 * o array de árvores BSTMap forem válidos.*/

	if (catalog != NULL && catalog->sales != NULL) {

		/* Em cada posição do array é aplicado o fold à árvore BSTMap. */

		for (; i < catalog->size; i++) {
			foldBSTMap(catalog->sales[i], acc, f);
		}
	}
 }


/**
 *  @brief Aplica uma função com acumulador a todos os nós das árvores BST a
 *         serem apontadas por todos os nós das árvores BSTMap de todas as
 *         posições do array ordenado por código de cliente na chave.
 *
 *  A partir da função f determinam-se os códigos de produto em
 *  que o cliente mais gastou.
 *
 *  @param catalog  Apontador para o catálogo da filial.
 *  @param acc      Acumulador da função a aplicar.
 *  @param f        Função a aplicar.
 *  @return Void
 */
void mostSpentByClient(const BranchCtlg catalog, const char *client, void *acc,
                       void (*f)(const void *, void *acc))
{
	unsigned int i = 0;

	if (catalog != NULL && catalog->sales != NULL && client != NULL) {
		for (; i < catalog->size; i++) {
			foldValueBSTMap(catalog->sales[i], client, acc, f);
		}
	}
 }

/*****************************************************************************
 * END TREE TRAVERSALS                                                       *
 *****************************************************************************/


/*****************************************************************************
 * BEGIN NAVIGATION                                                          *
 *****************************************************************************/

/**
 *  @brief Calcula o número clientes que compraram um dado produto.
 *
 *  Para cada tipo de venda é calculado o número de clientes que compraram um
 *  dado produto nessas condições.
 *  Percorrendo cada nó do array de árvores BSTMap ordenadas por produto,
 *  faz-se uma procura do produto passado como parâmetro. Quando se encontrar
 *  um nó que tenha o mesmo código, é aplicado um fold que tem uma função e
 *  um acumulador. A função fornecida verifica o tipo de venda, acrescentando
 *  o código do cliente ao tipo de iterador correspondente.
 *  No fim verifica-se o número de elementos em cada iterador, resultando no
 *  número de clientes que compraram o produto dado em cada tipo de venda.
 *
 *  @param catalog  Apontador para o catálogo da filial.
 *  @param product  Código de produto a procurar.
 *  @param total_N  Número total de vendas N.
 *  @param total_P  Número total de vendas P.
 *  @return Void. O resultado é guardado em total_N e total_P.
 */
void clientsThatBought(const BranchCtlg catalog, const char *product,
                       unsigned int *total_N, unsigned int *total_P)
{
	unsigned int i = 0;

	/* Verifica se o apontador para o catálogo e o apontador para o código de
	 * produto são válidos.*/

	if (catalog != NULL && product != NULL) {

		/* Cada iterador por tipo de venda é inicializado e criado. */

		for (i = 0; i < NUM_MODES; i++) {
			initModeIterator(catalog, i);
			catalog->mode_it[i] = createIterator(catalog->client_size,
			                                     catalog->printSC);
		}

		/* Para cada árvore BSTMap ordenada por código de produto, faz-se
		 * um fold que procura o produto dado e aplica a função o acumulador. */

		for (i = 0; i < catalog->size; i++) {
			foldKeyValueWithBSTMap(catalog->sales[i], catalog->mode_it,
			                       product, selectMode);

		}


		/* O número de elementos no iterador de vendas normais corresponderá
		 * ao número de clientes que compraram o produto em venda normal. */

		*total_N = getSizeIterator(catalog->mode_it[0]);

		/* O número de elementos no iterador de vendas em promoção
		 * corresponderá ao número de clientes que compraram o produto
		 * em promoção.*/

		*total_P = getSizeIterator(catalog->mode_it[1]);
	}
}


/**
 *  Passa para a página seguinte da pesquisa.
 *
 *  @param catalog  Apontador para o catálogo da filial.
 *  @param mode     Variável que indica o tipo de venda.
 *  @return Void.
 */
void nextModePage(const BranchCtlg catalog, const char mode)
{
	unsigned int index = (mode == N) ? 0 : 1; /* Atribui a posição no array de
	                                           * iteradores correspondente
	                                           * ao tipo de venda. */

	/* Verifica se o apontador para o catálogo da filial, o apontador para os
	 * iteradores de cada tipo de venda e o apontador para o array com
	 * o número de páginas por tipo de venda são válidos. */

	if (catalog != NULL && catalog->mode_it != NULL &&
	    catalog->mode_pages != NULL) {

		/* Verifica se já não estamos na última página. */

		if (catalog->mode_pages[index] < getNumModePages(catalog, mode)) {
				printModePage(catalog, mode);

				/* Atualiza a página da pesquisa, incrementando-a em uma unidade. */

				catalog->mode_pages[index]++;
		}
	}
}


/**
 *  Vai diretamente para uma página da pesquisa.
 *
 *  @param catalog  Apontador para o catálogo da filial.
 *  @param mode     Variável que indica o tipo de venda.
 *  @param page     Página da pesquisa a ir.
 *  @return Void.
 */
void goToModePage(const BranchCtlg catalog, const char mode,
                  const unsigned int page)
{
	unsigned int index = (mode == N) ? 0 : 1; /* Atribui a posição no array de
	                                           * iteradores correspondente
	                                           * ao tipo de venda. */

	/* Verifica se o apontador para o catálogo da filial e o apontador para os
	 * iteradores de cada tipo de venda. */

	if (catalog != NULL && catalog->mode_it != NULL) {

		/* Verifica a página a ir é válida, ou seja, se está compreendida entre a
		 * página 1 e a última página. */

		if (page > 0 && page <= getNumModePages(catalog, mode)) {

			/* Vai para a página da pesquisa pretendida.
			 * Invoca a função goToIterator para alterar o seu índice. */
			goToIterator(catalog->mode_it[index],
			             (page - 1) * catalog->page_size);

			/*A página atual é atualizada.*/

			catalog->mode_pages[index] = page - 1;
		}
	}
}

/*****************************************************************************
 * END NAVIGATION                                                            *
 *****************************************************************************/

/*****************************************************************************
 * END PUBLIC                                                                *
 *****************************************************************************/
