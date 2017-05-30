/**
 *  @file faturacao.c
 *  @brief Implementação de um módulo de faturação global de vendas.
 *
 *  Aqui constam todas as funções necessárias ao correto funcionamento deste
 *  módulo, assim como estruturas auxiliares.
 *
 *  A estrutura principal deste módulo, GlobalBilled, contém uma matriz
 *  organizada por meses e filiais. Esta matriz é composta por uma BSTMap em que
 *  a key é um código de produto e as BSTrees para o qual aponta tem como
 *  value uma Bill.
 *
 *  @author Carlos Pereira - A61887
 *  @author Diogo Silva    - A76407
 *  @author Rafael Braga   - A61799
 *
 *  @bug ?
 *  @version 3.2
 */

#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include "bstmap.h"
#include "faturacaoGlobal.h"
#include "iterator.h"

#define DEFAULT_PAGE_SIZE 20       /* Quando se está a trabalhar com
                                    * valores globais, utiliza-se este tamanho
                                    * de página. */

#define DEFAULT_BRANCH_PAGE_SIZE 5 /* Quando se está a trabalhar com valores por
                                    * filial, utiliza-se este tamanho de página. */

#define DEFAULT_MONTHS 12          /* Número por defeito de meses. */
#define DEFAULT_BRANCHES 3         /* Número por defeito de filiais. */
#define DEFAULT_PRODUCT_SIZE 8


/* Estrutura de uma faturação */

struct globalBilled {
	BSTMap **b_matrix;            /* Uma matriz de BSTMap composta por 12 linhas
	                               * e 3 colunas, correspondendo, respetivamente,
	                               * a meses e filiais.*/
	Iterator not_sold;            /* Todos os produtos que não foram vendidos
	                               * encontram-se neste iterador. */
	Iterator *not_sold_in_branch; /* Um array de iteradores, onde cada posição
	 		               * corresponde a uma filial */

	/* Estruturas e variáveis auxiliares. */

	unsigned int page;		        /* Página atual do iterador.*/
	unsigned int page_size;		        /* Número de elementos por página a ser apresentada.*/
	unsigned int branch_page_size;          /* Número de elementos por página a ser apresentada,
				                 * quando se faz distinções de resultados por
                                                 * filial.*/
	unsigned int *not_sold_in_branch_pages; /*Número máximo de páginas, por filial, de
					         *cada iterador dos produtos que não foram
					         *vendidos.*/

	unsigned int months;   /* Pode eventualmente ser alterado o valor por defeito
	                        * de meses. Esta variável corresponde ao número de
	                        * meses. */
	unsigned int branches; /* Número de filiais utilizadas no número de colunas
                                * de b_matrix */

	unsigned int product_size; /* Tamanho de um código de produto. */

	unsigned int *total_units; /* Total de unidades por mês. Ao ser inserida nova
	                            * informação à estrutura, estes valores serão
	                            * incrementados */
	double *total_billed;      /* Total faturado por mês. Ao ser inserida nova
			                        *informação à estrutura, é calculado o novo
			                        *valor faturado em cada mês. */

	printPBill printP; /* Função de impressão de um produto. */
	printPBill printB; /* Função de impressão de uma estrutura Bill. */

	BSTree *aux_most_sold; /* BSTree auxiliar de produtos mais vendidos, as
	                        * estruturas em cada nó estão organizadas por ordem
	                        * alfabética do produto. A cada nova inserção de dados
	                        * é recalculado o número de unidades. */

	BSTree *most_sold;     /* BSTree que armazena os produtos mais comprados por
	                        * ordem descendente do mais comprado. */

	Iterator *it_MS;       /* Iterador com os produtos mais vendidos. */

	unsigned int n;        /* Número de produtos que o cliente pretende
	                        * visualizar no iterador it_MS. */

	printPrdctUntClnt printPUC; /* Função de impressão de uma estrutura
	                             * productUnitsClients. */
	unsigned int *it_MS_pages;  /* Número de páginas do iterador it_MS. */
};

/*Estrutura principal que armazena uma fatura de compras. */

struct bill {
	unsigned int units; /* Número de unidades de um produto numa venda. */
	double price;       /* Preço unitário de um produto numa venda. */
	char type;          /* Tipo de venda. */
};

/* Estrutura com o código de produto, o número de unidades vendidas e o número
 * de clientes que compraram esse produto.*/

struct productUnitsClients {
	char *product;        /* Código de um produto. */
	unsigned int units;   /* Número de unidades vendidas de um produto. */
	unsigned int clients; /* Número total de clientes que compraram um determinado
	                       * produto. */
};

/* Estrutura auxiliar para obter facilmente e apenas numa travessia o número
 * de unidades em modo N e o preço em modo P. */

typedef struct auxBill {
	unsigned int units_N; /* Unidades de uma compra Normal. */
	unsigned int units_P; /* Unidades de uma compra Promocional. */
	double price_N;       /* Preço de uma compra Normal. */
	double price_P;       /* Preço de uma compra Promocional. */
} *AuxBill;


/*****************************************************************************
 * BEGIN PRIVATE                                                             *
 *****************************************************************************/

/*****************************************************************************
 * BEGIN PRINT FUNCTIONS                                                     *
 *****************************************************************************/

/**
 *  @brief Imprime uma página de uma pesquisa a partir do iterador not_sold.
 *
 *  Esta função admite que tanto a estrutura da faturação bem como o
 *  iterador desta foram préviamente inicializados. Para além disso admite
 *  que a página a ser impressa é válida. Serão apenas impressos, no máximo,
 *  um número de elementos equivalentes à page_size.
 *
 *  @param g Apontador para a estrutura da faturação.
 *  @return Retorna o número de elementos que imprimiu.
 */
static unsigned int printNotSoldPage(const GlobalBilled g)
{
	/* Controlo do ciclo for e número de produtos impressos.*/

	unsigned int i = 0;

	for (; i < g->page_size; i++) {

		/* Imprime a posição atual do iterador. */

		printCurrentIterator(g->not_sold);

		/* Se existirem ainda elementos no iterador, avança internamente o index. */

		if (hasNextIterator(g->not_sold) == true) {
			nextIterator(g->not_sold);
		}
		else {
			i++;
			break;
		}
	}

	/* Número total de elementos impressos. */

	return i;
}


/**
 *  @brief Imprime uma página de uma pesquisa a partir do iterador not_sold_in_branch.
 *
 *  Esta função admite que tanto a estrutura da faturação bem como o seu iterador
 *  foram préviamente inicializados. Para além disso admite que a página a ser
 *  impressa é válida. Serão apenas impressos, no máximo, um número de elementos
 *  equivalentes a branch_page_size;
 *
 *  @param g      Apontador para a estrutura da faturação global.
 *  @param branch A filial do iterador que pretendemos imprimir.
 *  @return Void.
 */
static void printNotSoldInBranchPage(const GlobalBilled g,
                                     unsigned int branch)
{
	unsigned int i = 0; /* Controlo do ciclo for e número de produtos
	                     * impressos. */

	for (; i < g->branch_page_size; i++) {

		 printCurrentIterator(g->not_sold_in_branch[branch - 1]);

		 if (hasNextIterator(g->not_sold_in_branch[branch - 1]) == true) {
			 nextIterator(g->not_sold_in_branch[branch - 1]);
		 }
		 else {
			 i++;
			 break;
		 }
	 }
}


/**
 *  @brief Imprime uma página de uma pesquisa a partir do iterador it_MS.
 *
 *  Esta função admite que tanto a estrutura da faturação bem como o iterador
 *  desta foram préviamente inicializados. Para além disso admite que a
 *  página a ser impressa é válida. Serão apenas impressos, no máximo, um
 *  número de elementos equivalentes a it_MS_pages;
 *
 *  @param g      Apontador para a estrutura da faturação global.
 *  @param branch A filial do iterador que pretendemos imprimir.
 *  @return Void.
 */
static void printNMostBoughtPage(const GlobalBilled g,
                                 const unsigned int branch)
{
	unsigned int i = 0; /* Controlo do ciclo for e número de produtos
	                     * impressos. */

	for (; i < g->branch_page_size; i++) {
		if (getIndexIterator(g->it_MS[branch - 1]) >= g->n) {
			break;
		}

		/* Imprime a atual posição do iterador. */

		printCurrentIterator(g->it_MS[branch - 1]);

		if (hasNextIterator(g->it_MS[branch - 1]) == true) {
			nextIterator(g->it_MS[branch - 1]);
		}
		else {
			i++;
			break;
		}
	}
}


/*****************************************************************************
 * END PRINT FUNCTIONS                                                       *
 *****************************************************************************/


/*****************************************************************************
 * BEGIN DATA STRUCTURES AUXILIARY FUNCTIONS                                 *
 *****************************************************************************/

/**
 *  @brief Função simples de comparação entre produtos.
 *
 *  Utiliza a strcmp para comparar os dois produtos, faz "cast" para "char *".
 *  Essa devolve 0 caso sejam iguais.
 *
 *  @param a Produto a ser comparado.
 *  @param b Produto a ser comparado.
 *  @return Resultado da comparação.
 *
 */
static int cmpProducts(const void *a, const void *b)
{
	return (strcmp((char*) a, (char*) b));
}


/**
 *  @brief Função de comparação entre estruturas do tipo Bill.
 *
 *  Utiliza o campo das unidades como referência de comparação.
 *  Caso as unidades sejam as mesmas o resultado é 1.
 *
 *  @param a Estrutura a ser comparada.
 * 	@param b Estrutura a ser comparada.
 *  @return Resultado da comparação.
 *
 */
static int cmpBills(const void *a, const void *b)
{
	double aux1 = 0;
	double aux2 = 0;
	int r = 0;

	aux1 = ((double) ((Bill) a)->units);
	aux2 = ((double) ((Bill) b)->units);

	r = (aux1 < aux2) ? - 1 : 1;

	return r;
}


/**
 *  @brief Função de comparação entre estruturas do tipo ProductUnitsClients.
 *
 *  Utiliza o campo dos produtos como referência de comparação.
 *  Usa o resultado de strcmp aplicada aos dois produtos como valor de retorno.
 *
 *  @param a Estrutura a ser comparada.
 * 	@param b Estrutura a ser comparada.
 *  @return Resultado da comparação.
 *
 */
static int cmpP(const void *a, const void *b)
{
	ProductUnitsClients aux1 = (ProductUnitsClients) a;
	ProductUnitsClients aux2 = (ProductUnitsClients) b;

	return strcmp(aux1->product, aux2->product);
}


/**
 *  @brief Função de comparação entre estruturas do tipo ProductUnitsClients.
 *
 *  Utiliza o campo das unidades como referência de comparação.
 *  Retorna 1 caso as unidades da estrutura passada no primeiro argumento
 *  forem superiores às passadas na estrutura como segundo parãmetro.
 *
 *  @param a Estrutura a ser comparada.
 *  @param b Estrutura a ser comparada.
 *  @return Resultado da comparação.
 */
static int cmpU(const void *a, const void *b)
{
	int i = 0;
	ProductUnitsClients aux1 = (ProductUnitsClients) a;
	ProductUnitsClients aux2 = (ProductUnitsClients) b;

	i = (aux1->units > aux2->units) ? -1 : 1;

	return i;
}


/**
 *  @brief Adiciona uma nova estrutura ProductUnitsClients a um acumulador
 *  do tipo BSTree.
 *
 *  É invocada uma função de para efectuar a inserção do módulo BSTree.
 *
 *  @param a   Estrutura a ser inserida.
 *  @param acc Estrutura onde se pretende inserir informação.
 *  @return Void.
 *
 */
static void addToMostSold(const void *a, void *acc)
{
	addBSTree((BSTree) acc, (ProductUnitsClients) a);
}


/**
 *  Soma das unidades de duas estruturas auxliares de produtos, clientes e unidades.
 *
 *  @param acc       Acumulador.
 *  @param new_value Estrutura a adicionar.
 *  @return Void.
 */
static void addPUC(void *acc, const void *new_value)
{
	ProductUnitsClients aux = (ProductUnitsClients) new_value;

	((ProductUnitsClients) acc)->units += aux->units;
	((ProductUnitsClients) acc)->clients++;
}


/**
 *  @brief Função auxiliar utilizada em billOfProductInMonth.
 *
 *  Esta função vai incrementar os campos de acc do tipo auxBill.
 *  É primeiro testado qual o tipo de compra, e só depois o faturado e o
 *  número de unidades são somadas aos campos já inicializados do acc.
 *
 *  @param value Estrutura de origem, essa é inalterável.
 *  @param acc   Estrutura de destino, acumulador, será alterado.
 *  @return Void.
 */
static void sumUnitsPrice(const void *value, void *acc)
{
	Bill source = (Bill) value;
	AuxBill target = (AuxBill) acc;

	if (source->type == 'N') {
		target->units_N += source->units;
		target->price_N += source->price * source->units;
	}
	else {
		target->units_P += source->units;
		target->price_P += source->price * source->units;
	}
}


/**
 *  @brief Função para efectuar libertação de memória de uma estrutura do tipo
 *  ProductUnitsClients.
 *
 *  O campo product é alocado dinâmicamente pelo que é necessário efectuar free
 *  primeiro a este, antes de toda a estrutura.
 *
 *  @param a Estrutura a ser libertada.
 *  @return Void.
 */
static void deleteProductsUnitsClients(void *a)
{
	ProductUnitsClients aux = (ProductUnitsClients) a;

	if (aux != NULL) {
		if (aux->product != NULL) {
			free(aux->product);
			aux->product = NULL;
		}

		free(aux);
		aux = NULL;
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
 *  @brief Cria a estrutura principal da faturação, esta é do tipo GlobalBilled.
 *
 *  É necessário fornecer as funções de impressão para as diversas estruturas.
 *  Os argumentos para a alocação de espaço da matriz b_matrix são recebidos
 *  nesta função.
 *
 *  @param printP        Função de impressão de uma key.
 *  @param printB        Função de impressão de uma Bill
 *  @param printPUC      Função de impressão de uma ProductUnitsClients.
 *  @param months        Meses de uma faturação.
 *  @param branches      Filias.
 *  @param product_size  Tamanho de um código de produto.
 *  @return Uma nova estrutura GlobalBilled.
 *
 */
GlobalBilled createGlobalBilled(printPBill printP, printGBill printB,
                                printPrdctUntClnt printPUC,
                                const unsigned int months,
                                const unsigned int branches,
                                const unsigned int product_size)
{
	unsigned int i = 0;
	unsigned int j = 0;

	GlobalBilled g = malloc(sizeof(struct globalBilled));

  	if (g == NULL)  {
		g = realloc(g, sizeof(struct globalBilled));
		assert(g != NULL);
	}


	g->months = (months > 0) ? months : DEFAULT_MONTHS;
	g->branches = (branches > 0) ? branches : DEFAULT_BRANCHES;
	g->product_size = (product_size > 0) ? product_size : DEFAULT_PRODUCT_SIZE;


	g->b_matrix = malloc(g->months * sizeof(BSTMap));

	if (g->b_matrix == NULL)  {
		g->b_matrix = realloc(g->b_matrix, sizeof(g->months * sizeof(BSTMap)));
		assert(g->b_matrix != NULL);
	}


	for(i = 0; i < g->months; i++) {
		g->b_matrix[i] = malloc(g->branches * sizeof(BSTMap*));

		if (g->b_matrix[i] == NULL) {
			g->b_matrix[i] = realloc(g->b_matrix[i], g->branches * sizeof(BSTMap));
			assert(g->b_matrix[i] != NULL);
		}

		for(j = 0; j < g->branches; j++) {
			g->b_matrix[i][j] = createBSTMap(g->product_size, cmpProducts,
			                                 printP, sizeof(struct bill),
			                                 cmpBills, printB);
		}
	}


	g->not_sold = createIterator(g->product_size, printP);


	g->not_sold_in_branch = malloc(g->branches * sizeof(Iterator));

	if (g->not_sold_in_branch == NULL) {
		g->not_sold_in_branch = realloc(g->not_sold_in_branch,
		                                g->branches * sizeof(Iterator));
	}

	for(i = 0; i < g->branches; i++) {
		g->not_sold_in_branch[i] = createIterator(g->product_size, printP);
	}


	g->not_sold_in_branch_pages = malloc(g->branches * sizeof(unsigned int));

	if (g->not_sold_in_branch_pages == NULL) {
		g->not_sold_in_branch_pages = realloc(g->not_sold_in_branch_pages,
		                                      g->branches * sizeof(unsigned int));
		assert(g->not_sold_in_branch_pages != NULL);
	}

	for(i = 0; i < g->branches; i++) {
		g->not_sold_in_branch_pages[i] = 0;
	}

	g->total_units = malloc(g->months * sizeof(unsigned int));

	if (g->total_units == NULL) {
		g->total_units = realloc(g->total_units, g->months * sizeof(unsigned int));
		assert(g->total_units != NULL);
	}

	for (i = 0; i < g->months; i++) {
		g->total_units[i] = 0;
	}


	g->total_billed = malloc(g->months * sizeof(double));

	if (g->total_billed == NULL) {
		g->total_billed = realloc(g->total_billed, g->months * sizeof(double));
		assert(g->total_billed != NULL);
	}

	for (i = 0; i < g->months; i++) {
		g->total_billed[i] = 0;
	}

	g->aux_most_sold = malloc(g->branches * sizeof(BSTree));

	if (g->aux_most_sold == NULL) {
		g->aux_most_sold = realloc(g->aux_most_sold, g->branches * sizeof(BSTree));
		assert(g->aux_most_sold != NULL);
	}

	for (i = 0; i < g->branches; i++) {
		g->aux_most_sold[i] = createBSTree(sizeof(struct productUnitsClients),
		                                   cmpP, printPUC);
	}




	g->most_sold = malloc(g->branches * sizeof(BSTree));

	if (g->most_sold == NULL) {
		g->most_sold = realloc(g->most_sold, g->branches * sizeof(BSTree));
		assert(g->most_sold != NULL);
	}

	for (i = 0; i < g->branches; i++) {
		g->most_sold[i] = createBSTree(sizeof(struct productUnitsClients),
		                               cmpU, printPUC);
	}



	g->it_MS = malloc(g->branches * sizeof(Iterator));

	if (g->it_MS == NULL) {
		g->it_MS = realloc(g->it_MS, g->branches * sizeof(Iterator));
		assert(g->it_MS != NULL);
	}

	for (i = 0; i < g->branches; i++) {
		g->it_MS[i] = createIterator(sizeof(struct productUnitsClients),
		                             printPUC);
	}


	g->it_MS_pages = malloc(g->branches * sizeof(unsigned int));

	if (g->it_MS_pages == NULL) {
		g->it_MS_pages = realloc(g->it_MS_pages,
		                         g->branches * sizeof(unsigned int));

		assert(g->it_MS_pages != NULL);
	}

	for (i = 0; i <  g->branches; i++) {
		g->it_MS_pages[i] = 0;
	}


	g->page = 0;
	g->page_size = DEFAULT_PAGE_SIZE;
	g->branch_page_size = DEFAULT_BRANCH_PAGE_SIZE;
	g->n = 0;
	g->printPUC = printPUC;

	return g;
}


/**
 *  @brief Cria a estrutura principal da faturação de um modo pré-definido.
 * 
 *  É necessário fornecer as funções de impressão para as diversas estruturas.
 *  Os argumentos para a alocação de espaço da matriz b_matrix não são
 *  recebidos nesta função. Assume-se que meses e filial, equivalem,
 *  respetivamente a 12 e 3. Esta função utiliza o construtor para devolver uma
 *  nova estrutura do tipo GlobalBilled fornecendo os argumentos pré-definidos.
 *
 *  @param printP   Função de impressão de uma key.
 *  @param printB   Função de impressão de uma Bill
 *  @param printPUC Função de impressão de uma ProductUnitsClients.
 *  @return Uma nova estrutura GlobalBilled.
 */
GlobalBilled defaultCreateGlobalBilled(printPBill printP,
	                               printGBill printB,
	                               printPrdctUntClnt printPUC)
{
	return createGlobalBilled(printP, printB, printPUC, DEFAULT_MONTHS, DEFAULT_BRANCHES,
	                          DEFAULT_PRODUCT_SIZE);
}




/**
 *  @brief Destrói uma estrutura Bill.
 *
 *  O único argumento recebido é a estrutura a
 *  libertar, só efectua trabalho se esta não for nula.
 *
 *  @param g Estrutura a destruir.
 *  @return Void.
 */
void destroyGlobalBilled(GlobalBilled g)
{
	unsigned int i = 0;
	unsigned int j = 0;

	if (g != NULL) {
		if (g->b_matrix != NULL) {
			for(i = 0; i < g->months; i++) {
				for(j = 0; j < g->branches; j++) {
					destroyBSTMap(g->b_matrix[i][j]);
				}

				free(g->b_matrix[i]);
				g->b_matrix[i] = NULL;
			}

			free(g->b_matrix);
			g->b_matrix = NULL;
		}

		destroyIterator(g->not_sold);

		if (g->not_sold_in_branch != NULL) {
			for(i = 0; i < g->branches; i++) {
				destroyIterator(g->not_sold_in_branch[i]);
			}

			free(g->not_sold_in_branch);
			g->not_sold_in_branch = NULL;
		}

		if (g->not_sold_in_branch_pages != NULL) {
			free(g->not_sold_in_branch_pages);
			g->not_sold_in_branch_pages = NULL;
		}

		if (g->total_units != NULL) {
			free(g->total_units);
			g->total_units = NULL;
		}

		if (g->total_billed != NULL) {
			free(g->total_billed);
			g->total_billed = NULL;
		}

		if (g->aux_most_sold != NULL) {
			for (i = 0; i < g->branches; i++) {
				destroyBSTree(g->aux_most_sold[i]);
			}

			free(g->aux_most_sold);
			g->aux_most_sold = NULL;
		}

		if (g->most_sold != NULL) {
			for (i = 0; i < g->branches; i++) {
				destroyBSTree(g->most_sold[i]);
			}

			free(g->most_sold);
			g->most_sold = NULL;
		}

		if (g->it_MS != NULL) {
			for (i = 0; i < g->branches; i++) {
				destroyIterator(g->it_MS[i]);
			}

			free(g->it_MS);
			g->it_MS = NULL;
		}

		if (g->it_MS_pages != NULL) {
			free(g->it_MS_pages);
			g->it_MS_pages = 0;
		}

		free(g);
		g = NULL;
	}
}

/*****************************************************************************
 * END CONSTRUCTORS AND DESTRUCTORS                                          *
 *****************************************************************************/


/*****************************************************************************
 * BEGIN GETS AND SETS                                                       *
 *****************************************************************************/

/**
 *  @brief Devolve o campo de unidades de uma Bill.
 *
 *  Se a estrutura for nula, devolve 0.
 *
 *  @param bill Estrutura com os campos da faturação.
 *  @return Número de unidades.
 */
unsigned int getUnitsBill(Bill bill)
{
	unsigned int units = (bill != NULL) ? bill->units : 0;

	return units;
}


/**
 *  @brief Devolve o campo de preço de um Bill.
 *
 *  Se a estrutura for nula, devolve -1.
 *
 *  @param bill Estrutura com os campos da faturação.
 *  @return Preço unitário.
 */
double getPriceBill(Bill bill)
{
	double price = (bill != NULL) ? bill->price : -1;

	return price;
}


/**
 *  @brief Devolve o campo do tipo de um Bill.
 *
 *  Se a estrutura for nula, devolve '\0'.
 *
 *  @param bill Estrutura com os campos da faturação.
 *  @return Tipo de venda.
 */
char getTypeBill(Bill bill)
{
	char type = (bill != NULL) ? bill->type : '\0';

	return type;
}


/**
 *  @brief Devolve o campo produto de um ProductUnitsClients.
 *
 *  Se a estrutura for nula, devolve "".
 *
 *  @param bill Estrutura ProductUnitsClients.
 *  @return Produto.
 */
char *getProductPUC(const ProductUnitsClients p)
{
	char *product = (p != NULL) ? p->product : "";

	return product;
}


/**
 *  @brief Devolve o campo produto de unidades de um ProductUnitsClients.
 *
 *  Se a estrutura for nula, devolve 0.
 *
 *  @param bill Estrutura ProductUnitsClients.
 *  @return Unidades.
 */
unsigned int getUnitsPUC(const ProductUnitsClients p)
{
	unsigned int units = (p != NULL) ? p->units : 0;

	return units;
}


/**
 *  @brief Devolve o campo produto de número de clientes de um
 * ProductUnitsClients.
 *
 *  Se a estrutura for nula, devolve 0.
 *
 *  @param bill Estrutura ProductUnitsClients.
 *  @return Número de clientes.
 */
unsigned int getClientsPUC(const ProductUnitsClients p)
{
	unsigned int clients = (p != NULL) ? p->clients : 0;

	return clients;
}


/**
 *  @brief Devolve a quantidade de páginas para apresentar os produtos não
 *  vendidos numa determinada filial.
 *
 *  Efectuamos um arredondamento por excesso caso existam casas decimais no
 *  cálculo das páginas.
 *
 *  @param g      Estrutura que contém o iterador onde se pretende calcular o
 *                número de páginas.
 *  @param branch Filial do iterador correspondente.
 *  @return Número de páginas.
 */
unsigned int getNotSoldInBranchPages(const GlobalBilled g, unsigned int branch)
{
	unsigned int num = 0; /* Número total de páginas. */
	double aux = 0;       /* Valor real auxiliar para efetuar o arredondamento do
	                       * número de páginas para cima. */

	if (g->not_sold_in_branch[branch - 1] != NULL) {
		aux = ((double) getSizeIterator(g->not_sold_in_branch[branch - 1]))
		                / g->branch_page_size;

		/* num recebe o valor total de páginas arredondadas para baixo. */

		num = (unsigned int) aux;

		/* Se a subtração ao valor total de páginas com o valor de num for
		   maior que zero é sinal que o número de páginas deve ser incrementado. */

		if (aux - num > 0) {
			num++;
		}
	}

	return num;
}


/**
 *  @brief Devolve a quantidade de páginas para apresentar os produtos mais
 *  vendidos no iterador it_MS.
 *
 *  Efectuamos um arredondamento por excesso caso existam casas decimais no
 *  cálculo das páginas.
 *
 *  @param g      Estrutura que contém o iterador onde se pretende calcular o
 *                número de páginas.
 *  @param branch Filial do iterador correspondente.
 *  @return Número de páginas.
 */
unsigned int getMostBoughtPages(const GlobalBilled g, unsigned int branch)
{
	unsigned int num = 0; /* Número total de páginas. */
	double aux = 0;       /* Valor real auxiliar para efetuar o arredondamento do
	                         número de páginas para cima. */
	unsigned int aux_page = 0;

	if (g != NULL && g->it_MS != NULL) {
		if (branch > 0 && branch <= g->branches) {
			if (g->it_MS[branch - 1] != NULL) {
				aux_page = (g->n < getSizeIterator(g->it_MS[branch - 1]))
				            ? g->n
				            : getSizeIterator(g->it_MS[branch - 1]);

				aux = ((double) aux_page / g->branch_page_size);

				/* num recebe o valor total de páginas arredondadas para baixo. */

				num = (unsigned int) aux;

				/* Se a subtração ao valor total de páginas com o valor de num for
				   maior que zero é sinal que o número de páginas deve ser
					 incrementado. */

				if (aux - num > 0) {
					num++;
				}
			}
		}
	}

	return num;
}


/**
 *  @brief Devolve a quantidade de elementos a apresentar por página do
 *  iterador not_sold duma estrutura GlobalBilled.
 *
 *
 *  @param g      Estrutura que contém o iterador onde se pretende calcular o
 *                número de elementos por página.
 *  @return Número de páginas.
 */
unsigned int getNotSoldPageSize(const GlobalBilled g)
{
	unsigned int page_size = (g != NULL) ? g->page_size : DEFAULT_PAGE_SIZE;

	return page_size;
}



/**
 *  @brief Devolve a quantidade de páginas do iterador not_sold duma estrutura
 *  GlobalBilled.
 *
 *  Efectuamos um arredondamento por excesso caso existam casas decimais no
 *  cálculo das páginas.
 *
 *  @param g      Estrutura que contém o iterador onde se pretende calcular o
 *                número de elementos por página.
 *  @return Número de páginas.
 */
unsigned int getNotSoldPages(const GlobalBilled g)
{
	unsigned int num = 0; /* Número total de páginas. */
	double aux = 0;       /* Valor real auxiliar para efetuar o
	                         arredondamento do número de páginas para cima. */

	if (g->not_sold != NULL) {
		aux = ((double) getSizeIterator(g->not_sold)) / g->page_size;

		/* num recebe o valor total de páginas arredondadas para baixo. */

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
 *  @brief Apresenta o número de produtos não vendidos em nenhuma das três
 *  filiais.
 *
 *  Utiliza a função já previamente definida no módulo do iterador
  * devolvendo o número de elementos que este apresenta..
 *
 *  @param g Estrutura GlobalBilled que contém o iterador.
 *  @return Número de produtos não vendidos.
 */
unsigned int getNotSold(GlobalBilled g)
{
	unsigned int size = 0;

	if (g != NULL) {
		size = getSizeIterator(g->not_sold);
	}

	return size;
}

/**
 *  @brief Apresenta o número de produtos não vendidos numa nada filial.
 *
 *  Utiliza a função já previamente definida no módulo do iterador devolvendo
 * o tamanho deste.
 *
 *  @param g Estrutura GlobalBilled que contém o iterador.
 *  @param branch      Filial onde é preciso saber quantos não foram vendidos.
 *  @return Número de produtos não vendidos numa filial.
 */
unsigned int getNotSoldInBranch(GlobalBilled g, const unsigned int branch)
{
	unsigned int size = 0;

	if (g != NULL && branch > 0 && branch <= g->branches) {
		size = getSizeIterator(g->not_sold_in_branch[branch - 1]);
	}

	return size;
}


/**
 *  @brief Devolve a quantidade de unidades vendidas num determinado mês de uma
 *  estrutura GlobalBilled.
 *
 *  Caso o vetor total_units esteja nulo, não é efectuado trabalho.
 *
 *  @param g      Estrutura GlobalBilled.
 *  @return Número de unidades de produtos vendidas num dado mês.
 */
unsigned int getTotalUnits(const GlobalBilled g, const unsigned int month)
{
	unsigned int r = 0;

	if (g != NULL && month > 0 && month <= g->months) {
		if (g->total_units != NULL) {
			r = g->total_units[month - 1];
		}
	}

	return r;
}


/**
 *  @brief Devolve total facturado num determinado mês de uma estrutura
 *  GlobalBilled.
 *
 *  Caso o vetor total_billed esteja nulo, não é efectuado trabalho.
 *
 *  @param g      Estrutura GlobalBilled.
 *  @return Total faturado num dado mês.
 */
double getTotalBilled(const GlobalBilled g, const unsigned int month)
{
	double r = 0;

	if (g != NULL && month > 0 && month <= g->months) {
		if (g->total_billed != NULL) {
			r = g->total_billed[month - 1];
		}
	}

	return r;
}


/**
 *  @brief Calcula o os produtos mais comprados por ordem descendente.
 *
 *  Depois de testar se todas as estruturas envolvidas foram inicializadas,
 *  a função procede com trabalho útil.
 *  Caso já existam elementos na estrutura "resultado", esta é libertada e
 *  inicializada novamente. Ou seja o campo filial de most_sold é inicializado.
 *  De seguida, todos os produtos de aux_most_sold são utilizados para criar uma
 *  nova árvore ordenada agora pelos produtos mais vendidos (olhando para as
 *  respetivas unidades). Essa árvore estará presente em most_sold[filial].
 *  Por fim, estes elementos são enviados para it_MS[filial] após uma travessia
 *  inOrder de most_sold para cada filial.
 *
 *  @param g Uma GlobalBilled.
 *  @param n Número de produtos mais comprados a mostrar.
 *  @return Void.
 */
void getNMostBought(const GlobalBilled g, const unsigned int n)
{
	unsigned int i = 0;

	if (g != NULL && g->n == 0) {

		g->n = n;

		if (g->aux_most_sold != NULL && g->most_sold != NULL && g->it_MS != NULL) {
			for (; i < g->branches; i++) {
				if (getSizeIterator(g->it_MS[i]) == 0) {
					foldBSTree(g->aux_most_sold[i], g->most_sold[i], addToMostSold);

					g->it_MS[i] = toIteratorInOrderBSTree(g->most_sold[i]);
				}
			}
		}
	}
}


/*****************************************************************************
 * END GETS AND SETS                                                         *
 *****************************************************************************/


/*****************************************************************************
 * BEGIN ADD, SEARCH AND REMOVE                                              *
 *****************************************************************************/


/**
 *  @brief Adiciona uma nova factura a GlobalBilled fornecendo todos os
 *         pârametros necessários para atribuir aos campos de uma estrutura Bill.
 *
 *  A estrutura Bill é inicializada nesta função com todos os parâmetros dados.
 *  De seguida utiliza-se uma função que adiciona a já inicializada estrutura
 *  à BSTMap na b_matrix[mês][filial].
 *  Da mesma forma, é criada uma nova estrutura productUnitsClients puc que
 *  é posteriormente adicionada a aux_most_sold[filial]. Caso o produto em
 *  questão já exista na BSTree então apenas o número de clientes que o comprou
 *  é incrementado assim como o número de unidades.
 *  Caso contrário, adiciona-se à árvore, formando um novo nó e não, apenas,
 *  somando valores.
 *
 *  @param g       Estrutura da facturação global.
 *  @param product Produto que queremos adicionar.
 *  @param price   Preço unitário de um dado produto.
 *  @param units   Unidades de um dado produto.
 *  @param type    Tipo de compra de um dado produto.
 *  @param month   Mês da compra um dado produto.
 *  @param branch  Filial da compra um dado produto.
 *  @return Void.
 */
GlobalBilled addBill(GlobalBilled g, const ProductBill product,
                    const double price, const unsigned int units,
                    const char type, const unsigned int month,
                    const unsigned int branch)
{
	struct bill new_struct;
	struct productUnitsClients puc;

	if (g != NULL && month > 0 && month <= g->months && branch > 0 &&
	    branch <= g->branches) {

		if (g->total_units != NULL && g->total_billed != NULL) {
			g->total_units[month - 1] += units;

			/* Cálculo do faturado. */

			g->total_billed[month - 1] += (units * price);
		}

		/* Atribuimos os campos à estrutura. */

		new_struct.price = price;
		new_struct.units = units;
		new_struct.type = type;

		if (g->b_matrix != NULL && g->b_matrix[month - 1][branch - 1] != NULL) {
			/* Adiciona-se a nova estrutura já inicializada à respetiva árvore. */

			addBSTMap(g->b_matrix[month - 1][branch - 1], product, &new_struct);

			/* Caso a estrutura aux_most_sold não seja nula, adiciona-se o novo nó à
		 	* BSTree da filial correspondente com addWithCondBSTree. */
		}

		if (g->aux_most_sold != NULL) {

			puc.product = malloc(strlen(product) + 1);

			strcpy(puc.product, product);

			puc.units = units;
			puc.clients = 1;

			addWithCondBSTree(g->aux_most_sold[branch - 1], &puc, addPUC);
		}
	}

	return g;
}


/**
 *  @brief Adiciona um produto não comprado em nenhuma filial ao iterador
 *         not_sold.
 *
 *  @param g       Estrutura GlobalBilled.
 *  @param product Produto não comprado em nenhuma filial.
 *  @return Apontador para a nova estrutura.
 */
GlobalBilled addNotSold(GlobalBilled g, const ProductBill product)
{
	if (g != NULL) {
		if (g->not_sold != NULL) {
			addIterator(g->not_sold, product);
		}
	}

	return g;
}


/**
 *  @brief Adiciona um produto não comprado numa dada filial ao iterador
 *         not_sold_in_branch.
 *
 *  @param g       Estrutura GlobalBilled.
 *  @param product Produto não comprado em branch.
 *  @param branch  Filial onde o produto a adicionar não foi comprado.
 *  @return Apontador para a nova estrutura.
 */
GlobalBilled addNotSoldInBranch(GlobalBilled g, const ProductBill product,
                                const unsigned int branch)
{
	if (g != NULL && branch > 0 && branch <= g->branches) {
		if (g->not_sold_in_branch[branch - 1] != NULL) {
			
			addIterator(g->not_sold_in_branch[branch - 1], product);
		}
	}

	return g;
}


/**
 *  @brief Verifica se um dado produto foi comprado numa determinada filial.
 *
 *  @param g       Estrutura GlobalBilled.
 *  @param product Produto que queremos saber se foi comprado em branch.
 *  @param branch  Filial a verificar.
 *  @return bool.
 */
bool productSoldInBranch(const GlobalBilled g, ProductBill product,
                         const unsigned int branch)
{
	bool b = false;
	unsigned int i = 0;

	if (g != NULL && branch > 0 && branch <= g->branches) {
		for(; b == false && i < g->months; i++) {
			b = containsKeyBSTMap(g->b_matrix[i][branch - 1], product);
		}
	}

	return b;
}


/**
 *  @brief Determina o número de vendas e o preço de um mês numa dada filial.
 *
 *  Utiliza um acumulador do tipo auxBill para percorrer a estrutura da
 *  b_matrix[mês][filial] assim como uma função auxiliar que irá preencher
 *  o acumulador.
 *  Depois da travessia da estrutura são preenchidos os campos fornecidos
 *  anteriormente na função (price_N, price_P, units_N, units_P).
 *
 *  @param g       Estrutura da faturação.
 *  @param product Produto em questão que queremos pesquisar.
 *  @param month   Mês.
 *  @param branch  Filial.
 *  @param price_N Apontador para um preço do tipo de compra N.
 *  @param price_P Apontador para um preço do tipo de compra P.
 *  @param units_N Apontador para unidades de um produto do tipo de compra N.
 *  @param units_P Apontador para unidades de um produto do tipo de compra P.
 *  @return Void.
 */
void billOfProductInMonth(const GlobalBilled g, const ProductBill product,
                          const unsigned int month, const unsigned int branch,
                          double *price_N, double *price_P,
                          unsigned int *units_N, unsigned int *units_P)
{
	struct auxBill aux;

	if (g != NULL && month > 0 && month <= g->months && branch > 0 &&
	    branch <= g->branches) {

		/* Inicialização das variáveis. */
		aux.price_N = 0;
		aux.price_P = 0;
		aux.units_N = 0;
		aux.units_P = 0;


		foldValueBSTMap(g->b_matrix[month - 1][branch - 1], product,  &aux,
		                sumUnitsPrice);

		*price_N = aux.price_N;
		*price_P = aux.price_P;

		*units_N = aux.units_N;
		*units_P = aux.units_P;
	}
}

/*****************************************************************************
 * END ADD, SEARCH AND REMOVE                                                *
 *****************************************************************************/


/*****************************************************************************
 * BEGIN NAVIGATION                                                          *
 *****************************************************************************/


/**
 *  @brief Altera a posição de pesquisa do iterador para a página num_page
 *         fornecida se esta for válida.
 *
 *  A função começa por testar se o iterador foi previamente inicializado,
 *  ou seja, se o iterador deste catálogo não é nulo. Caso todas estas
 *  condições se verifiquem num_page é convertido para um índice válido do
 *  iterador e são mostradas page_size posições deste.
 *
 *  @param g        Apontador para a estrutura da faturação.
 *  @param num_page Número da página a realizar a impressão de elementos.
 *  @return Retorna o número de elementos impressos na página num_page, caso
 *          num_page não seja válida retorna 0.
 */
unsigned int goToNotSoldPage(const GlobalBilled g,
                             const unsigned int num_page)
 {
	unsigned int num_products = 0; /* Número de produtos da página num_page. */

	if (g != NULL && g->not_sold != NULL) {

		/* Testa se num_page é válida, ou seja, se está compreendida entre a
		   página 1 e a última página. */

		if (num_page > 0 && num_page <= getNotSoldPages(g)) {

			/* A página deste catálogo é atualizada para num_page. */

			g->page = num_page;

			/* Converte num_page para o índice correspondente do iterador.
			 * Invoca a função goToIterator para alterar o seu índice. */

			goToIterator(g->not_sold, (num_page - 1) * g->page_size);

			num_products = printNotSoldPage(g);
		}
	}

	return num_products;
}


/**
 *  @brief Altera a posição de pesquisa do iterador para a página num_page
 *         fornecida se esta for válida num iterador para uma filial fornecida.
 *
 *  A função começa por testar se o iterador dessa filial foi previamente
 *  inicializado. Caso se verifique num_page é convertido para um índice válido
 *  do iterador e são mostradas page_size posições deste.
 *
 *  @param g        Apontador para a estrutura da faturação.
 *  @param num_page Número da página a realizar a impressão de elementos.
 *  @param branch   Filial do iterador correspondente.
 *  @return Void.
 */
void goToNotSoldInBranchPage(const GlobalBilled g,
                             const unsigned int num_page,
                             const unsigned int branch)
 {
	if (g != NULL && g->not_sold_in_branch[branch - 1] != NULL &&
	    g->not_sold_in_branch_pages != NULL) {

		/* Testa se num_page é válida, ou seja, se está compreendida entre a
		   página 1 e a última página. */

		if (num_page > 0 && num_page <= getNotSoldInBranchPages(g, branch)) {

			/* A página deste iterador é atualizada para num_page. */

			/* Converte num_page para o índice correspondente do iterador.
			   Invoca a função goToIterator para alterar o seu índice. */

			goToIterator(g->not_sold_in_branch[branch - 1],
			             (num_page - 1) * g->branch_page_size);

			g->not_sold_in_branch_pages[branch - 1] = num_page - 1;
		}
	}
}


/**
 *  @brief Mostra a próxima página da última pesquisa no iterador de produtos
 *         não vendidos de GlobalBilled.
 *
 *  Começa por testar se GlobalBilled foi previamente inicializado, bem como
 *  o iterador deste. Caso estas condições se verifiquem é realizado é
 *  imprimida a próxima página a não ser que a última página já tenha sido
 *  impressa anteriormente.
 *
 *  @param g Apontador para GlobalBilled.
 *  @return Número de produtos impressos, caso a página não seja válida
 *          retorna 0.
 */
unsigned int nextNotSoldPage(const GlobalBilled g)
{
	unsigned int num_products = 0; /* Número de produtos da próxima página. */

	if (g != NULL && g->not_sold != NULL) {

		/* Testa se já não estamos na última página. */

		if (g->page < getNotSoldPages(g)) {
				num_products = printNotSoldPage(g);

				/* Atualiza a página do catálogo, passando esta a ser incrementada. */

				g->page++;
		}
	}

	return num_products;
 }


/**
 *  @brief Mostra a próxima página da última pesquisa no iterador de produtos
 *  não vendidos numa filial de GlobalBilled.
 *
 *  Começa por testar se GlobalBilled foi previamente inicializado, bem como
 *  o iterador a pesquisar deste. Caso estas condições se verifiquem é
 *  impressa a próxima página a não ser que a última já tenha sido impressa
 *  anteriormente.
 *
 *  @param g      Apontador para GlobalBilled.
 *  @param branch Filial.
 *  @return Número de produtos impressos, caso a página não seja válida
 *          retorna 0.
 */
void nextNotSoldInBranchPage(const GlobalBilled g,
                             const unsigned int branch)
{
	if (g != NULL && g->not_sold_in_branch[branch - 1] != NULL &&
	    g->not_sold_in_branch_pages != NULL) {

		/* Testa se já não estamos na última página. */

		if (g->page < getNotSoldInBranchPages(g, branch)) {
				printNotSoldInBranchPage(g, branch);

				/* Atualiza a página do catálogo, passando esta a ser incrementada. */

				g->not_sold_in_branch_pages[branch - 1]++;
		}
	}
}


/**
 *  @brief Mostra a página anterior da última pesquisa no iterador not_sold.
 *
 *  Começa por testar se GlobalBilled foi previamente inicializado, bem como
 *  o iterador deste. Caso estas condições se verifiquem é impressa a página
 *  anterior a não ser que a última página impressa tenha sido a primeira
 *  página da pesquisa.
 *
 *  @param catalog Apontador para a estrutura da faturação global..
 *  @return Número de produtos impressos, caso a página não seja válida
 *          retorna 0.
 */
unsigned int previousNotSoldPage(const GlobalBilled g)
{
	unsigned int num_products = 0; /* Número de produtos da página anterior. */
	unsigned int aux_page = 0;
	unsigned int total_pages = 0;

	if (g != NULL && g->not_sold != NULL) {

		/* Testa se não estamos na primeira página. */

		if (g->page > 1) {

			total_pages = getNotSoldPages(g);

			if (g->page < total_pages) {

				/* Converte o número da página anterior para um índice válido do
				   iterador. Supondo que se mostram 20 produtos por página, ao mostrar-se
				   a página anterior tem que se fazer recuar no iterador os 20 produtos
				   da página atual mais os 20 produtos da página anterior. */

				goToIterator(g->not_sold,
				             getIndexIterator(g->not_sold) - (2 * g->page_size));
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

				aux_page = getSizeIterator(g->not_sold) -
									 (g->page_size * (total_pages - 1));

				num_products = aux_page;

				/* O índice da última página consite em subtrair ao iterador
				 * a soma do resultado obtido acima com o tamanho de página - 1.
				 */

				aux_page += g->page_size - 1;

				goToIterator(g->not_sold, getIndexIterator(g->not_sold) - (aux_page));
			}


			if (num_products > 0) {
				printNotSoldPage(g);
			}
			else {
				num_products = printNotSoldPage(g);
			}

			/* Atualiza a página do catálogo sendo esta descrementada uma unidade. */
			g->page--;
		}
	}

	return num_products;
 }

/**
 *  @brief Reseta as pesquisas de todos os iteradores de GlobalBilled.
 *
 *  A função começa por testar se GlobalBilled foi previamente inicializado.
 *  Quer para not_sold, quer para todos os iteradores de not_sold_in_branch
 *  são invocadas funções de goToIterator para o index 0 de forma a recomeçar
 *  qualquer pesquisar seguinte.
 *
 *  @param g        Apontador para a estrutura da faturação.
 *  @return Void.
 */
void resetAllSearches(const GlobalBilled g)
{
	unsigned int i = 0;

	if (g != NULL) {
		g->page = 0;
		g->n = 0;

		if (g->not_sold != NULL) {
			goToIterator(g->not_sold, 0);
		}

		if (g->not_sold_in_branch != NULL && g->not_sold_in_branch_pages != NULL &&
		    g->it_MS != NULL) {
			for (; i < g->branches; i++) {
				goToIterator(g->not_sold_in_branch[i], 0);
				g->not_sold_in_branch_pages[i] = 0;

				goToIterator(g->it_MS[i], 0);
				g->it_MS_pages[i] = 0;
			}
		}
	}
}


/**
 *  @brief Altera a posição de pesquisa do iterador de produtos mais comprados
 *  numa determinada filial para a página num_page fornecida se esta for válida.
 *
 *  A função começa por testar se o iterador dessa filial foi previamente
 *  inicializado. Caso se verifique num_page é convertido para um índice válido
 *  do iterador e são mostradas page_size posições deste.
 *
 *  @param g        Apontador para a estrutura da faturação.
 *  @param num_page Número da página a realizar a impressão de elementos.
 *  @param branch   Filial do iterador correspondente.
 *  @return Void.
 */
void goToMostBoughtPage(const GlobalBilled g,
                        const unsigned int num_page,
                        const unsigned int branch)
{
	if (g != NULL && g->it_MS != NULL) {
		if (branch > 0 && branch <= g->branches) {
			if (g->it_MS[branch - 1] != NULL && g->it_MS_pages != NULL) {

				/* Testa se num_page é válida, ou seja, se está compreendida entre a
				   página 1 e a última página. */

				if (num_page > 0 && num_page <= getMostBoughtPages(g, branch)) {

					/* A página deste catálogo é atualizada para num_page. */

					/* Converte num_page para o índice correspondente do iterador.
						 Invoca a função goToIterator para alterar o seu índice. */

					goToIterator(g->it_MS[branch - 1],
			                 (num_page - 1) * g->branch_page_size);

					g->it_MS_pages[branch - 1] = num_page - 1;
				}
			}
		}
	}
}


/**
 *  @brief Mostra a próxima página da última pesquisa no iterador de produtos
 *  mais comprados numa filial de GlobalBilled.
 *
 *  Começa por testar se GlobalBilled foi previamente inicializado, bem como
 *  o iterador a pesquisar deste. Caso estas condições se verifiquem é
 *  impressa a próxima página a não ser que a última já tenha sido impressa
 *  anteriormente.
 *
 *  @param g      Apontador para GlobalBilled.
 *  @param branch Filial de produtos mais comprados.
 *  @return Número de produtos impressos, caso a página não seja válida
 *          retorna 0.
 */
void nextMostBoughtPage(const GlobalBilled g, const unsigned int branch)
{
	if (g != NULL && g->it_MS_pages != NULL) {
		if (branch > 0 && branch <= g->branches) {
			if (g->it_MS[branch - 1] != NULL && g->it_MS_pages != NULL) {

		/* Testa se já não estamos na última página. */

				if (g->page < getMostBoughtPages(g, branch)) {
					printNMostBoughtPage(g, branch);

					/* Atualiza a página do catálogo, passando esta a ser incrementada. */

					g->it_MS_pages[branch - 1]++;
				}
			}
		}
	}
}

/*****************************************************************************
 * END NAVIGATION                                                            *
 *****************************************************************************/

/*****************************************************************************
 * END PUBLIC                                                                *
 *****************************************************************************/