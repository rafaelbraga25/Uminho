/**
 *  @file main.c
 *  @brief O cliente principal deste projecto que utilizará as funcionalidades
 *  dos módulos.
 *
 *  Definição de todos os recursos necessários para o correcto funcionamento
 *  dos módulos assim como todas as estruturas e funções auxiliares.
 *
 *  @author Carlos Pereira - A61887
 *  @author Diogo Silva    - A76407
 *  @author Rafael Braga   - A61799
 *
 *  @bug ?
 *  @version 1.0
 */

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include "bstree.h"
#include "iterator.h"
#include "catalogoClientes.h"
#include "catalogoProdutos.h"
#include "gestaoFilial.h"
#include "faturacaoGlobal.h"


/*Definição do comando que limpa o terminal.*/

#ifdef _WIN32
	#define CLEAR_COMMAND "cls"   /* Caso seja o sistema operativo Windows. */
#else
	#define CLEAR_COMMAND "clear" /* Caso seja um sistema operativo Unix. */
#endif


#define SIZE 64       	/* Tamanho para um buffer com larga margem de espaço. */
#define MONTHS 12	/* Número de meses esperado.*/
#define BRANCHES 3	/* Número de filiais esperado.*/
#define CODE_SIZE 8	/* Tamanho (em caracteres) do buffer nas estruturas de
                         * armazenamento de caracteres.*/


/* Estrutura com os campos de uma linha de venda válida.*/

typedef struct sale_struct {
	char product[CODE_SIZE]; 	/* Código do produto.*/
	double price; 			/* Preço de venda do produto.*/
	unsigned int units; 		/* Unidades de produto vendidas.*/
	char type; 			/* Tipo de venda.*/
	char client[CODE_SIZE];	        /* Cdigo do cliente.*/
	unsigned int month;		/* Mês da venda.*/
	unsigned int branch;		/* Filial da venda.*/
	} sale_line;


/*Estrutura auxiliar para as queries 9 e 11.*/

struct aux_queries {
	char *product;		/* Código do produto.*/
	unsigned int units;	/* Unidades de produto*/
	unsigned int clients;	/* Número de clientes que compraram o produto
				 * product.*/
	double spent;		/* Valor gasto na compra do produto product.*/
};

static ClientCtlg clients;		/* Apontador para o catálogo de clientes.*/
static ProductCtlg products;		/* Apontador para o catálogo de produtos.*/
static GlobalBilled billing;		/* Apontador para a faturação global.*/
static BranchCtlg branch_vec[BRANCHES];	/* Vetor de apontadores para o catálogo de
				 	 * filial.*/


static double totalFact;


static char *buffer; /* Buffer geral do teclado. */


/**
 *  Leitura de uma linha do teclado
 */
static void my_getline(void)
{
	unsigned int i = 0;
	size_t n_bytes = SIZE;

	i = getline(&buffer, &n_bytes, stdin);

	if (buffer[i - 1] == '\n') {
		buffer[i - 1] = '\0';
	}
}



/*****************************************************************************
 * BEGIN PRINT FUNCTIONS                                                     *
 *****************************************************************************/

 /**
  *  Imprime uma string no ecrã.
  *
  *  Função utilizada na impressão simples de um código de cliente ou produto.
  *  É usado o caractere '>' para uma maior facilidade de leitura.
  *
  *  @param str String a imprimir.
  *  @return Void.
  */
static void print(const void *str)
{
	printf("   > %s\n", (char*)str);
}


/**
 *  @brief Imprime os campos da estrutura do tipo Sale no ecrã.
 *
 *  Para imprimir uma Sale, mantendo o encapsulamento, temos de invocar métodos
 *  definidos no módulo da BranchCtlg. Caso contrário estaríamos a provocar
 *  "dereferencing" de dados mantidos noutro módulo.
 *
 *  @param x Sale a imprimir.
 *  @return Void.
 */
static void printSale(const void *x)
{
	Sale s = (Sale) x;

	printf("\t%s\n\t%.2f\n\t%d\n\t%c\n\n", getProduct(s), getPrice(s),
	                                       getUnits(s), getType(s));
}


/**
 *  @brief Imprime um código de produto no ecrã.
 *
 *  @param product Código de produto a imprimir.
 *  @return Void.
 */
static void printProduct(const void *product)
{
	printf("%s\n", (char*) product);
}


/**
 *  @brief Imprime os campos da estrutura do tipo Bill no ecrã.
 *
 *  Para imprimir uma Bill, mantendo o encapsulamento, temos de invocar métodos
 *  definidos no módulo do GlobalBilled. Caso contrário estaríamos a provocar
 *  "dereferencing" de dados mantidos noutro módulo.
 *
 *  @param x Bill a imprimir.
 *  @return Void.
 */
static void printBill(const void *x)
{
	Bill bill = (Bill) x;

	printf("\tType %c Price %.2f Units %d\n", getTypeBill(bill),
	                                          getPriceBill(bill),
	                                          getUnitsBill(bill));
}


static void printPUC(const void *x)
{
	ProductUnitsClients p = (ProductUnitsClients) x;

	printf("\t%s | %d | %d\n", getProductPUC(p), getUnitsPUC(p),
	                           getClientsPUC(p));
 }




/*****************************************************************************
 * END PRINT FUNCTIONS                                                       *
 *****************************************************************************/


/*****************************************************************************
 * BEGIN VALIDATION FUNCTIONS                                                *
 *****************************************************************************/

 /**
  *  Verifica se o valor x (int) está compreendido entre min e max.
  *
  *  @param x   Valor a testar.
  *  @param min Valor mínimo do intervalo.
  *  @param max Valor máximo do intervalo.
  *  @return true caso o valor x pertença ao intervalo
  *		false caso contrário.
  */
static bool testIntInterval(const unsigned int x, const unsigned int min,
                            const unsigned int max)
{
	bool b = false;

	if (x >= min && x <= max) {
		b = true;
	}

	return b;
}


/**
 *  Verifica se o valor x (double) está compreendido entre min e max.
 *
 *  @param x   Valor a testar.
 *  @param min Valor mínimo do intervalo.
 *  @param max Valor máximo do intervalo.
 *  @return true caso o valor x pertença ao intervalo
 *          false caso contrário.
 */
static bool testDoubleInterval(const double x, const double min,
                               const double max)
{
	bool b = false;

	if (x >= min && x <= max) {
		b = true;
	}

	return b;
}


/**
 *  Verifica se o tipo da venda é válido, ou seja, se é N (normal) ou
 *  P (promoção).
 *
 *  @param x   Tipo de venda a testar.
 *  @param s_a String constante tipicamente com o valor "N".
 *  @param s_b String constante tipicamente com o valor "P".
 *  @return true caso str seja válida
 *		false caso contrário.
 */
static bool testType(const char x, const char x_a, const char x_b)
{
	bool b = false;

	if (x == x_a || x == x_b) {
		b = true;
	}

	return b;
}


/**
 *  Verifica se um código de cliente existe no catálogo dos Clientes.
 *  Procura o cliente no catálogo utilizando a variável global (do tipo
 *  ClientCtlg) clients.
 *
 *  @param str Código do cliente a procurar.
 *  @return true caso str exista em ClientCtlg
 *		false caso contrário.
 */
static bool auxExistClient(const char *str)
{
	return containsClient(clients, str);
}


/**
 *  Verifica se um código de produto existe no catálogo dos Produtos.
 *  Procura o produto no catálogo utilizando a variável global (do tipo
 *  ProductCtlg) products.
 *
 *  @param str Código do produto a procurar.
 *  @return true caso str exista em ProductCtlg
 *		false caso contrário.
 */
static bool auxExistProduct(const char *str)
{
	return containsProduct(products, str);
}


/**
 *  @brief Testa se uma venda é válida.
 *
 *  Uma venda contém os seguintes campos:
 *  	- Código do produto.
 *  	- Preço do produto.
 *  	- Número de unidades do produto.
 *  	- Tipo de compra.
 *  	- Código do cliente.
 *  	- Mẽs da compra.
 *  	- Filial.
 *
 *  Uma venda é válida se forem cumpridas as seguintes condições.
 *  	- O código do produto encontra-se no catálogo de produtos
 *  	  (a função existProduct deve encarrega-se de realizar este teste).
 *  	- O código do cliente encontra-se no catálogo de clientes
 *  	  (a função existClient deve encarrega-se de realizar este teste).
 *  	- O valor do preço deve está compreendido entre 0.0 e 999.99.
 *  	- O número de unidades está compreendido entre 1 e 200.
 *  	- O tipo de compra é "N" ou "P".
 *  	- O Mês deve está compreendido entre 1 e 12.
 *  	- A filial é 1, 2 ou 3.
 *
 *  @param product Produto a testar.
 *  @param price   Preço a testar.
 *  @param units   Unidades a testar.
 *  @param type    Tipo a testar.
 *  @param client  Cliente a testar.
 *  @param month   Mês a testar.
 *  @param branch  Filial a testar.
 *  @return true caso todas as codições sejam verdadeiras
 *		false caso contrário.
 */
static bool isSaleOK(const char *product, const double price,
                     const unsigned int units, const char type,
                     const char *client, const unsigned int month,
                     const unsigned int branch)

{
	bool b = false; /* Uma venda é inválida por defeito. */

	/* As condições de teste para uma venda são realizadas num único "if".
	 * Estas são testadas seguindo a ordem apresentada acima. Como todas
	 * as condições têm que ser verdadeiras para uma venda ser válida,
	 * ao haver uma falha em qualquer condição as restantes não são testadas. */

	if (auxExistClient(client) == true &&
	    auxExistProduct(product) == true &&
	    testDoubleInterval(price, 0.0, 999.99) == true &&
	    testIntInterval(units, 1, 200) &&
	    testType(type, 'N', 'P') == true &&
	    testIntInterval(month, 1, 12) == true &&
	    testIntInterval(branch, 1, 3)) {


		/* A venda satisfaz todas as condições, sendo válida. */

		b = true;
	}

	return b;
}

/*****************************************************************************
 * END VALIDATION FUNCTIONS                                                  *
 *****************************************************************************/


/*****************************************************************************
 * BEGIN MENUS                                                               *
 *****************************************************************************/

 /**
  *  @brief Menu de navegação invocado em várias queries.
  *
  *  Este menu apenas apresenta os comandos permitidos para navegar os
  *  resultados. Esta função é comum a várias queries.
  *
  *  @param num_pages Número de páginas máximo da query que invocou esta função.
  *  @param buf       Buffer para armazenar o comando de navegação.
  *  @param s         Tamanho (em bytes) do buffer.
  *  @param show_menu Inteiro de controlo. Caso 1 a opção anterior foi válida.
  *                   Caso contrário, não foi válida.
  *  @return Void.
  *
  */
static void navigationMenu(unsigned int num_pages, char buf[], unsigned int s,
                           const unsigned int show_menu)
{
	unsigned int aux = 0;

	if (show_menu == 1) { /*Apenas apresenta as opções de navegação caso o
				     * comando anterior tenha sido válido.*/
		printf("\n\n> n - Pag. Seguinte\n");
		printf("> p - Pag. Anterior\n");
		printf("> 1..%d - Ir Para\n", num_pages);
		printf("> q - Sair\n\n");
	}
	else {
		printf("Opção inválida!\n");
	}

	printf("Opção: > ");

	while(1) {
		my_getline();

		strcpy(buf, buffer);
		/* Conversão dos carateres do comando num inteiro, supondo
		 * é o comando de ir para página.*/

		if (buf[0] != 'q' && buf[0] != 'n' && buf[0] != 'p') {

			aux = (unsigned) atoi(buffer);

			/* Verifica se o número da página a ir é válido: entre 1 e
		 	* a página máxima.*/

			if (aux >= 1 && aux <= num_pages) {
				break;
			}
			else {

				/* Se nenhuma dos testes se verificou, é porque o
			 	 * comando introduzido não é válido.*/

				printf("Opção inválida!\n");
			}
		}
		else {
			break;
		}
	}
}

/*****************************************************************************
 * END MENUS                                                                 *
 *****************************************************************************/

/*****************************************************************************
 * BEGIN CONSTRUCTORS AND DESTRUCTORS                                        *
 *****************************************************************************/

/**
 *  @brief Inicializa todas as estruturas de armazenamento de dados criadas
 *  na main.
 *
 *  Ao fazer a inicialização destas estruturas, é obrigatório chamar
 *  posteriormente, a função que destrói as estruturas - destroyComponents.
 *
 *  @param void Não necessita de parâmetros porque as variáveis são globais.
 *  @return Void.
 */
static void initComponents(void)
{
	unsigned int i = 0;

	clients = createClientCtlg(print);
 	products = createProductCtlg(print);
 	billing = createGlobalBilled(printProduct, printBill, printPUC,
	                             MONTHS, BRANCHES, CODE_SIZE);

 	for (; i < BRANCHES; i++) {
 		branch_vec[i] = createBranchCtlg(print, printSale, MONTHS);
 	}
}


/**
 *  @brief Destrói todas as estruturas de armazenamento de dados criadas
 *  na main.
 *
 * Esta função liberta a memória ocupada por estas estruturas e, caso tenha, os
 * dados delas.
 *
 *  @param void Não necessita de parâmetros porque as variáveis são globais.
 *  @return Void.
 */
static void destroyComponents(void)
{
	unsigned int i = 0;

	destroyClientCtlg(clients);
	destroyProductCtlg(products);
	destroyGlobalBilled(billing);

	for (; i < BRANCHES; i++) {
		destroyBranchCtlg(branch_vec[i]);
	}
 }

 /*****************************************************************************
  * END CONSTRUCTORS AND DESTRUCTORS                                          *
  *****************************************************************************/


/*****************************************************************************
 * BEGIN QUERIES FUNCTIONS                                                   *
 *****************************************************************************/

/*****************************************************************************
 * BEGIN QUERY 1                                                             *
 *****************************************************************************/


/**
 *  @brief Função que conta as linhas lidas e as linha válidas do ficheiro
 *         dos clientes. Quando for preciso, chama a função que adiciona um
 *	      elemento ao catálgo de clientes.
 *
 *  @param str Linha do ficheiro lida.
 *  @param lines_read Contador das linhas lidas.
 *  @param lines_ok Contador das linhas válidas.
 *  @return Void.
 */
static void auxAddClient(char *str, unsigned int *lines_read,
                         unsigned int *lines_ok)
{
	(*lines_read)++; /*Incrementa o contador quando lê uma linha.*/


	(*lines_ok)++; /*Incrementa o contador quando uma linha é válida.*/

	addClient(clients, str); 	/* Acrescenta o código de cliente ao
							* respectivo catálogo.*/

}


/**
 *  @brief Função que conta as linhas lidas e as linha válidas do ficheiro
 *         dos produtos. Quando for preciso, chama a função que adiciona um
 *	     elemento ao catálgo de produtos.
 *
 *  @param str Linha do ficheiro lida.
 *  @param lines_read Contador das linhas lidas.
 *  @param lines_ok Contador das linhas válidas.
 *  @return Void.
 */
static void auxAddProduct(char *str, unsigned int *lines_read,
                          unsigned int *lines_ok)
{
	(*lines_read)++;  /*Incrementa o contador quando lê uma linha.*/


	(*lines_ok)++;  /*Incrementa o contador quando uma linha é válida.*/

	addProduct(products, str); /* Acrescenta o código de produto ao
							* respectivo catálogo.*/
}


/**
 *  @brief Função que conta as linhas lidas e as linha válidas do ficheiro
 *         das vendas. Quando for preciso, as funções que adicionam uma venda
 *         ao catálogo das filiais e ao módulo da faturação.
 *
 *  @param str Linha do ficheiro lida.
 *  @param lines_read Contador das linhas lidas.
 *  @param lines_ok Contador das linhas válidas.
 *  @return Void.
 */
static void auxAddSale(char *str, unsigned int *lines_read, unsigned int *lines_ok)
{
	sale_line s; /* Cria uma estrutura de dados que irá guardar os
				 * campos da venda.*/

	(*lines_read)++;  /*Incrementa o contador quando lê uma linha.*/

	memcpy(s.product, strtok(str, " "), CODE_SIZE);
	s.price = atof(strtok(NULL, " "));
	s.units = (unsigned) atoi(strtok(NULL, " "));
	s.type = *(strtok(NULL, " "));
	memcpy(s.client, strtok(NULL, " "), CODE_SIZE);
	s.month = (unsigned) atoi(strtok(NULL, " "));
	s.branch = (unsigned) atoi(strtok(NULL, "\r\n"));


	/* Chama a função que verifica se a linha lida é uma venda válida.*/

	totalFact += (s.price * s.units);

	if (isSaleOK(s.product, s.price, s.units, s.type,
	             s.client, s.month, s.branch) == true) {
		(*lines_ok)++; /*Incrementa o contador quando uma linha é válida.*/


		/*Adiciona a venda ao módulo da respetiva filial.*/

		addSale(branch_vec[s.branch - 1], s.product, s.price, s.units,
		        s.type, s.client, s.month);

	 /*Adiciona a venda ao módulo da faturação.*/

		addBill(billing, s.product, s.price, s.units, s.type, s.month, s.branch);
	}
}


/**
 *  @brief Verificar se um produto foi vendido em cada uma das filiais. Se não
 *	   foi vendido, adiciona o seu código ao iterador de produtos não
 *	   vendidos da respetiva filial. Caso não tenha sido vendido em nenhuma
 *	   das filiais, também adiciona o seu código ao iterador dos produtos
 *	   que não foram vendidos em nenhuma filial.
 *
 *  @param product Produto a procurar.
 *  @return Void.
 */
void addIteratorsInBilling(void *product)
{
	bool b = false;         /* Resultado, por defeito, do produto ter sido comprado
			         * na filial.*/
	unsigned int i = 0;     /* Número da filial atual.*/
	unsigned int count = 0; /* Contador das filiais em que o produto
				 * não foi vendido.*/

	for(i = 1; i <= BRANCHES; i++) {

		/* Procura em cada posição do vetor do catálogo das filiais o código
		 * do produto. Guarda o resultado em b.*/

		b = productSoldInBranch(billing, product, i);


		/* Caso não tenha encontrado o produto na filial, adiciona o
		 * código ao iterador dos produtos não vendidos naquela filial.
		 * Também incrementa o contador das filiais em que o produto não
		 * foi vendido.*/


		if (b == false) {
			count++;
			addNotSoldInBranch(billing, product, i);
		}
	}

	/* Verifica se o número das filiais em que naõ foi vendido é igual ao
	 * número total de filiais.*/

	if (count == BRANCHES) {

		/*Sendo verdado, é adicionado ao iterador dos produtos que nunca
		 *foram comprados.*/

		addNotSold(billing, product);
	}
}


/**
 *  @brief Função auxiliar que recebe um nome de um ficheiro, lê cada uma das
 *	   suas linhas e adiciona o campo lido à estrutura adequada, validando-a
 *	   previamente.
 *
 *  @param file       Nome do ficheiro a ler.
 *  @param lines_read Contador das linhas lidas do ficheiro.
 *  @param lines_ok   Contador das linhas válidas do ficheiro.
 *  @param add	    Função que adiciona a linha atual às respetivas
 *			    estruturas de dados.
 *  @return Void.
 */
static void auxReadFile(const char* file, unsigned int *lines_read, unsigned int *lines_ok,
			void (*add)(char*, unsigned int*, unsigned int*))
{
	FILE *fp = fopen(file, "r"); /*Apontador para o ficheiro lido.*/
	char str[SIZE] = ""; /*buffer para guardar o conteúdo da linha lida*/


	/*Verifica se o apontador é diferente de nulo.
	 *Caso isso se verifique, o programa termina aqui.*/

	assert(fp != NULL);

	while (fgets(str, SIZE, fp) != NULL) {

		/*Enquanto não se chegar ao fim do ficheiro, é lida uma linha.
		 *Em conjunto com a função add, o campo é adicionado à respetiva
		 *estrutura.*/

		add(strtok(str, "\n\r"), lines_read, lines_ok);
	}

	/*O apontador para o ficheiro é fechado.*/

	fclose(fp);
}


/**
 *  @brief Função para a leitura de ficheiros.
 *	     Envia os parâmetros para a função auxiliar que lê e adiciona as linhas
 *	     dos ficheiros. No fim apresenta no ecrã  o nome do ficheiro, as
 *	     linhas lidas e as linhas válidas.
 *
 *  @param file Nome do ficheiro a ler.
 *  @param add  Função que adiciona a linha atual às respetivas
 *		estruturas de dados.
 *  @return Void.
 */
static void readFile(const char *file,
                     void (*add)(char*, unsigned int*, unsigned int*))
{
	int lines_read = 0; /*Contador de linhas lidas.*/
	int lines_ok = 0;   /*Contador de linhas válidas.*/

	/*Chamada da função que faz a leitura dos ficheiros.*/

	auxReadFile(file, &lines_read, &lines_ok, add);

	/*Impressão das informações do ficheiro lido.*/

	printf("Ficheiro %s\n", file);
	printf("\tLinhas lidas %d | Linhas válidas %d\n", lines_read, lines_ok);
}

/**
 *  @ Query 1.
 *	     Função que lê os 3 ficheiros de entrada. Recebe do utilizador a
 *  opção de ser ele a introduzir o nome dos ficheiros ou se a leitura dos
 *  ficheiros é feita com os nomes existentes por defeito.
 *  	     Se a leitura for válida, apresenta no ecrã o nome dos ficheiros lidos
 *  e para cada um deles o número total de linhas lidas e o número total de
 *  linhas válidas. À medida que vai lendo e validando as linhas, manda-as
 *  para as respetivas estruturas de dados.
 *
 *  @param option Opção de leitura de ficheiros.
 *			1 - O utilizador introduz os nomes dos ficheiros
 *			2 - O programa deve lêr os nomes existentes por defeito.
 *  @return Void.
 */
static void query_1(const int option)
{

	/*Declaração e inicialização dos buffer para os nomes dos ficheiros, caso
	 *seja o utilizador a fazer a introdução destes.*/

	char buf_clients[SIZE] = "";
	char buf_products[SIZE] = "";
	char buf_sales[SIZE] = "";


	/*Declaração e inicialização das variáveis para contagem de tempo passado.*/

	double diff = 0;
	clock_t begin = 0;
	clock_t end = 0;


	/*Chamada das funções que libertação em memória das estruturas de dados.
	 *Sempre que se chama esta query, faz-se a libertação em memória das
	 *estrutura de dados.
	 *As funções de libertação estão preparadas para o caso de ser a 1ª vez
	 *que esta query é chamada.*/

	destroyComponents();


	/*Inicialização das estruturas de dados.*/
	initComponents();



	if(option == 1) {

		/*Caso seja o utilizador a introduzir os nomes dos ficheiros.*/

		printf("Nome do ficheiro dos clientes: ");
		my_getline();
		strcpy(buf_clients, buffer);
		printf("Nome do ficheiro dos produtos: ");
		my_getline();
		strcpy(buf_products, buffer);
		printf("Nome do ficheiro das vendas: ");
		my_getline();
		strcpy(buf_sales, buffer);
	}
	else {

		/*Caso a leitura seja com os nomes por defeito.*/

		strcpy(buf_clients, "Clientes.txt");
		strcpy(buf_products, "Produtos.txt");
		strcpy(buf_sales, "Vendas_1M.txt");
	}


	/*Inicialização do relógio.*/

	begin = clock();


	/*Chamada da função que trata da leitura de cada um dos ficheiros.*/

	readFile(buf_clients, auxAddClient);
	readFile(buf_products, auxAddProduct);
	readFile(buf_sales, auxAddSale);


	/*Map que coloca os códigos dos produtos que nunca foram comprados
	 *no respetivo iterador. Também coloca no respetivos iteradores os códigos
	 *de produto que não foram comprados em cada uma das filiais.
	 *
	 *Estes iteradores poderão ser necessários mais tarde.
	 */

	mapProductCtlg(products, addIteratorsInBilling);


	/*Finalização do relógio. Cálcula do tempo que passou desde o início e
	 *apresentação do valor no ecrã.*/

	end = clock();
	diff = ((double) (end - begin)) / CLOCKS_PER_SEC;

	printf("Tempo passado: %.5f s\n", diff);
}

/*****************************************************************************
 * END QUERY 1                                                               *
 *****************************************************************************/


/*****************************************************************************
 * BEGIN QUERY 2                                                             *
 *****************************************************************************/

 /**
  *  Função que, ao ser impressos os resultados da query 2, apresenta
  *  o número da página atual e o número de páginas totais.
  *
  *  @param page        Número da página atual.
  *  @param total_pages Número total de páginas.
  *  @return Void.
  */
static void infoPrintPage(const unsigned int page, const unsigned int total_pages)
{
	system(CLEAR_COMMAND);
	printf("Pag. %d de %d\n", page, total_pages);
}


/**
 *  Função que apresenta os clientes que começam pelo parâmetro fornecido.
 *
 *
 *  @param str Valor pelo qual os clientes devem começar.
 *  @return Variável que indica a outra função que o utilizador vai deixar de
 *          ver as opções de navegação de resultados, apresentando no ecrã o
 *		menu principal.
 */
static unsigned int query_2_Clients(char *str)
{
	/*Declaração e inicialização do buffer que recebe as opções de navegação
	 *da visualização dos resultados.*/

	char option[SIZE] = "";

	unsigned int i = 1;             /* Número da página atual.*/
	unsigned int total_clients = 0; /* Número total de clientes encontrados.*/
	unsigned int read_clients = 0;  /* Número do último cliente apresentado
				         * na página atual.
						   */
	unsigned int total_pages = 0;	/*Número total de páginas a apresentar.*/


	/* Variável auxiliar que indica a outra função que o utilizador vai deixar de
         * ver as opções de navegação de resultados, apresentando no ecrã o menu
	 * principal.
	 */

	unsigned int aux = 0;


	/* Variável que indica se o programa deve apresentar o menu com as opções
	 * de navegação. Só não apresenta este menu quando tem 1 página de
	 * resultados, não tem nenhuma página, está na última página e recebe o
	 * comando de ir para a seguinte ou está na primeira página e recebe o
	 * comando de ir para a anterior.
	 */

	unsigned int show_menu = 1;


	/* Invocação da função no módulo dos clientes que coloca no iterador desse
	 * módulo os códigos de clientes que comecem por str. Devolve o número
	 * total de clientes colocados nesse iterador.
	 */

	total_clients = clientsBeginningWithX(clients, str);


	/* Caso o número total de clientes seja maior que 0, há resultados
	 * a apresentar.
	 */

	if (total_clients > 0) {


		/* Caso o número total de clientes a apresentar seja menor que o
		 * número de elementos que existem, por defeito, em cada página
		 * do iterador.
		 */

		if (total_clients <= getClientPageSize(clients)) {

			/* Apenas há uma página de resultados a apresentar.*/

			system(CLEAR_COMMAND); /*Chamada para limpar o ecrã.*/


			/* Escrita do número de clientes que começam por str.*/

			printf("Clientes encontrados: %d\n", total_clients);


			/* Apresentação no ecrã a página atual de resultados.*/

			nextClientPage(clients);


			/* Como é apenas um página, não há opções de navegação. Como
			 * não há opções de navegação, é apresentado ao utilizador
			 * o menu principal.
			 */
			aux = 1;
		}
		else {

			/* Como o número total de clientes é superior aos elementos por
			 * página do iterador, determina-se o número total de páginas.
			 */
			total_pages = getNumClientPages(clients);


			/* Faz-se a impressão das informações das páginas dos resultados.*/
			infoPrintPage(i, total_pages);


			/* Apresenta todos os elementos da página atual do iterador.
			 * É devolvido o número de clientes apresentados na página.
			 * Soma-se este valor ao número do último cliente anterior.
			 *
			 * read_clientes tem o número do último cliente apresentado
			 * na página atual.
			 */

			read_clients += nextClientPage(clients);


			/* É apresentado o número do último cliente na página atual
			 * e o número total de resultados.
			 */

			printf("Clientes %d de %d\n", read_clients, total_clients);


			/* Enquanto a opção introduzida não for de sair da navegação.*/

			while(option[0] != 'q') {


				/* Chamada a função de apresentação do menu de navegação.
				 * Apenas apresenta o menu se o comando anterior tenha
				 * sido válido.
				 * Poderá não apresentar o menu quando a opção
				 * não existe ou quando está na última página e recebe
				 * o comando de ir para a seguinte.
				 */
				navigationMenu(total_pages, option, SIZE, show_menu);


				/* Supõe que o comando a introduzir é válido. Caso se
				 * se verifique o contrário, esta variável é alterada.*/

				show_menu = 1;


				/* Caso o comando introduzido seja de ir para a página
				 * de resultados seguinte.
				 */

				if (option[0] == 'n') {


					/* Caso o número da página atual seja inferior
					 * ao número de páginas totais.*/

					if (i < total_pages) {


						/*O número da página atual é incrementado.*/

						i++;

						/*São apresentadas as informações das páginas
						 *dos resultados.
						 */

						infoPrintPage(i, total_pages);


						/*O número de total de clientes apresentados
						 *é incrementado e é apresentada a página
						 *de resultados atual.
						 */

						read_clients += nextClientPage(clients);


						/*É apresentado o número total de clientes
						 *que foram escritos e o número de clientes
						 *ao todo.*/

						printf("Clientes %d de %d\n", read_clients, total_clients);
					}
					else {


						/*Caso o comando seja de ir para a página
						 *de resultados seguinte e a página atual
						 *é a última, significa que o comando não
						 *é válido. Logo, não se irá apresentar o
						 *menu de navegação.
						 */

						show_menu = 0;
					}
				}

				     /*Caso o comando introduzido seja de ir para a página
				      *de resultados anterior.
				      */

				else if (option[0] == 'p') {


					/*Caso o número da página atual seja superior
					 *a 1.*/

					if (i > 1) {


						/*O número da página atual é decrementado.*/

						i--;


						/*São apresentadas as informações das páginas
						 *dos resultados.
						 */

						infoPrintPage(i, total_pages);


						/* O número de total de clientes apresentados
						 * é decrementado e é apresentada a página
						 * de resultados atual.
						 */

						read_clients -= previousClientPage(clients);


						/* É apresentado o número total de clientes
						 * que foram escritos e o número de clientes
						 * ao todo.*/

						printf("Clientes %d de %d\n", read_clients, total_clients);
					}
					else {


						/* Caso o comando seja de ir para a página
						 * de resultados anterior e a página atual
						 * é a primeira, significa que o comando não
						 * é válido. Logo, não se irá apresentar o
						 * menu de navegação.
						 */

						show_menu = 0;
					}
				}


				       /* Caso o comando a introduzir não seja nenhum dos
				        * anterior e não seja de sair do menu, supõe-se
					* que o utilizador pretenda ir diretamente para
					* uma página.
					*/

				else if (option[0] != 'q') {


					/* Faz-se a conversão para inteiro o número da página
					 * de destino.
					 */

					i = (unsigned) atoi(option);


					/* Apresentam-se as informações da página a ir.*/

					infoPrintPage(i, total_pages);


					/* Apresenta-se a página de destino. É devolvido
					 * o número de clientes lidos até essa página.*/

					read_clients = goToClientPage(clients, i);


					/* Ao número de clientes lidos até à página atual,
					 * é somado o número de clientes a apresentar na
					 * página atual.
					 */
					read_clients += getClientPageSize(clients) * (i - 1);


					/* Apresentam-se os clientes lidos e os clientes
					 * totais.
					 */

					printf("Clientes %d of %d\n", read_clients, total_clients);
				}
			}
		}
	}
	else {
		/* Caso contrário, não existem resultados a apresentar.*/

		printf("Não foram encontrados resultados para a sua pesquisa...\n");


		/* A variável que indica que o utilizador vai deixar de ver os
		 * resultados passa a ser verdadeira.*/
		aux = 1;
	}

	return aux;
}



/**
 *  Função que apresenta os produtos que começam pelo parâmetro fornecido.
 *
 *
 *  @param str Valor pelo qual os produtos devem começar.
 *  @return Variável que indica a outra função que o utilizador vai deixar de
 *          ver as opções de navegação de resultados, apresentando no ecrã o
 *		menu principal.
 */

static unsigned int query_2_Products(char *str)
{

	/*Declaração e inicialização do buffer que recebe as opções de navegação
	 *da visualização dos resultados.*/

	char option[SIZE] = "";

	unsigned int i = 1;             /*Número da página atual.*/
	unsigned int total_products = 0; /*Número total de produtos encontrados.*/
	unsigned int read_products = 0;  /*Número do último produto apresentado
						   *na página atual.
						   */
	unsigned int total_pages = 0;	  /*Número total de páginas a apresentar.*/


	/*Variável auxiliar que indica a outra função que o utilizador vai deixar de
         *ver as opções de navegação de resultados, apresentando no ecrã o menu
	 *principal.
	 */

	unsigned int aux = 0;


	/* Variável que indica se o programa deve apresentar o menu com as opções
	 * de navegação. Só não apresenta este menu quando tem 1 página de
	 * resultados, não tem nenhuma página, está na última página e recebe o
	 * comando de ir para a seguinte ou está na primeira página e recebe o
	 * comando de ir para a anterior.
	 */

	unsigned int show_menu = 1;


	/* Invocação da função no módulo dos produtos que coloca no iterador desse
	 * módulo os códigos de produtos que comecem por str. Devolve o número
	 * total de produtos colocados nesse iterador.
	 */

	total_products = productsBeginningWithX(products, str);



	/* Caso o número total de produtos seja maior que 0, há resultados
	 * a apresentar.
	 */

	if (total_products > 0) {

		/*Caso o número total de produtos a apresentar seja menor que o
		 *número de elementos que existem, por defeito, em cada página
		 *do iterador.
		 */

		if (total_products <= getProductPageSize(products)) {


			/*Apenas há uma página de resultados a apresentar.*/

			system(CLEAR_COMMAND);	/*Chamada para limpar o ecrã.*/


			/*Escrita do número de produto que começam por str.*/

			printf("Produtos encontrados: %d\n", total_products);


			/*Apresentação no ecrã a página atual de resultados.*/

			nextProductPage(products);


			/*Como é apenas um página, não há opções de navegação. Como
			 *não há opções de navegação, é apresentado ao utilizador
			 *o menu principal.
			 */

			aux = 1;
		}
		else {
			/*Como o número total de produtos é superior aos elementos por
			 *página do iterador, determina-se o número total de páginas.
			 */
			total_pages = getNumProductPages(products);


			/*Faz-se a impressão das informações das páginas dos resultados.*/
			infoPrintPage(i, total_pages);


			/*Apresenta todos os elementos da página atual do iterador.
			 *É devolvido o número de produtos apresentados na página.
			 *Soma-se este valor ao número do último cliente anterior.
			 *
			 *read_clientes tem o número do último produto apresentado
			 *na página atual.
			 */

			read_products += nextProductPage(products);


			/*É apresentado o número do último produto na página atual
			 *e o número total de resultados.
			 */

			printf("Produtos %d de %d\n", read_products, total_products);


			/*Enquanto a opção introduzida não for de sair da navegação.*/

			while(option[0] != 'q') {


				/*Chamada a função de apresentação do menu de navegação.
				 *Apenas apresenta o menu se o comando anterior tenha
				 *sido válido.
				 *Poderá não apresentar o menu quando a opção
				 *não existe ou quando está na última página e recebe
				 *o comando de ir para a seguinte.
				 */

				navigationMenu(total_pages, option, SIZE, show_menu);


				/*Supõe que o comando a introduzir é válido. Caso se
				 *se verifique o contrário, esta variável é alterada.*/

				show_menu = 1;


				/*Caso o comando introduzido seja de ir para a página
				 *de resultados seguinte.
				 */

				if (option[0] == 'n') {


					/*Caso o número da página atual seja inferior
					 *ao número de páginas totais.*/

					if (i < total_pages) {


						/*O número da página atual é incrementado.*/

						i++;


						/*São apresentadas as informações das páginas
						 *dos resultados.
						 */

						infoPrintPage(i, total_pages);


						/*O número de total de produtos apresentados
						 *é incrementado e é apresentada a página
						 *de resultados atual.
						 */

						read_products += nextProductPage(products);


						/*É apresentado o número total de produtos
						 *que foram escritos e o número de produtos
						 *ao todo.*/

						printf("Produtos %d de %d\n", read_products,
							 total_products);
					}
					else {


						/*Caso o comando seja de ir para a página
						 *de resultados seguinte e a página atual
						 *é a última, significa que o comando não
						 *é válido. Logo, não se irá apresentar o
						 *menu de navegação.
						 */

						show_menu = 0;
					}
				}


				     /*Caso o comando introduzido seja de ir para a página
				      *de resultados anterior.
				      */

				else if (option[0] == 'p') {


					/*Caso o número da página atual seja superior
					 *a 1.*/

					if (i > 1) {


						/*O número da página atual é decrementado.*/

						i--;


						/*São apresentadas as informações das páginas
						 *dos resultados.
						 */

						infoPrintPage(i, total_pages);


						/*O número de total de produtos apresentados
						 *é decrementado e é apresentada a página
						 *de resultados atual.
						 */

						read_products -= previousProductPage(products);


						/*É apresentado o número total de produtos
						 *que foram escritos e o número de produtos
						 *ao todo.*/

						printf("Produtos %d de %d\n", read_products, total_products);
					}
					else {


						/*Caso o comando seja de ir para a página
						 *de resultados anterior e a página atual
						 *é a primeira, significa que o comando não
						 *é válido. Logo, não se irá apresentar o
						 *menu de navegação.
						 */

						show_menu = 0;
					}
				}


				     /*Caso o comando a introduzir não seja nenhum dos
				      *anterior e não seja de sair do menu, supõe-se
				      *que o utilizador pretenda ir diretamente para
				      *uma página.
				      */

				else if (option[0] != 'q') {


					/*Faz-se a conversão para inteiro o número da página
					 *de destino.
					 */

					i = (unsigned) atoi(option);


					/*Apresentam-se as informações da página a ir.*/

					infoPrintPage(i, total_pages);


					/*Apresenta-se a página de destino. É devolvido
					 *o número de produtos lidos até essa página.*/

					read_products = goToProductPage(products, i);


					/*Ao número de produtos lidos até à página atual,
					 *é somado o número de produtos a apresentar na
					 *página atual.
					 */

					read_products += getProductPageSize(products) * (i - 1);


					/*Apresentam-se os produtos lidos e os produtos
					 *totais.
					 */

					printf("Produtos %d of %d\n", read_products, total_products);
				}
			}
		}
	}
	else {

		/*Caso contrário, não existem resultados a apresentar.*/

		printf("Não foram encontrados resultados para a sua pesquisa...\n");


		/*A variável que indica que o utilizador vai deixar de ver os
		 *resultados passa a ser verdadeira.*/

		aux = 1;
	}

	return aux;
}


/*
 *  Função que ao utilizador o valores que para os quais pretende que os
 *  clientes/produtos a apresentar comecem.
 *
 *  @param field Valores pelos quais os clientes/produtos deverão começar. São
 *	   escritos neste buffer durante a execução desta função.
 *  @param size Tamanho do buffer.
 *  @return Void
 */
static void getField(char *field, const unsigned int size)
{
	printf("Campo a procurar: ");

	my_getline();

	strcpy(field, buffer);
}


/*
 *  @ Query 2.
 *	Função principal da query 2.
 *
 * 	Esta query apresentar no ecrã os produtos ou clientes que comecem por uma
 *	letra que o utilizador deverá introduzir. O utilizador é que escolhe
 *	que códigos deverão aparecer.
 *	Também existe a possibilidade do utilizador navegear pelos resultados, caso
 *	sejam demasiados.
 *  @return Void
 */

static void query_2(void)
{
	/*Declaração e inicialização do buffer da opção do utilizador na escolha
	 *de ser apresentado no ecrã os clientes ou produtos ou até mesmo sair
	 *da query.
	 */

	char input[SIZE] = "";



	/*Declaração e inicialização do buffer que guarda a letra pelo qual os
	 *clientes ou produtos a apresentam deverão começar.
	 */
	char field[SIZE] = "";


	/*Variável que guarda a opção número do utilizador.*/

	int option = 0;


	/*Variável auxiliar que indica que o utilizador vai deixar de
         *ver as opções de navegação de resultados, limpando o ecrã no fim da
	 *função.
	 *O ecrã só não é limpo quando o número de resultados é inferior ao número
	 *de elementos por página, não havendo necessidade da navegação.
	 */

	unsigned int aux = 0;

	system(CLEAR_COMMAND); /*Chamada para limpar o ecrã.*/


	/*Apresentação do menu dos resultados a apresentar.*/

	printf("Procurar por:\n");
	printf("1- Clientes\n");
	printf("2- Produtos\n");
	printf("q- Sair\n");


	while(1) {

		/*Introdução, pelo utilizador, dos resultados a apresentar.*/

		my_getline();

		option = atoi(buffer); /*Converte-se a opção para um inteiro.*/

		if (option == 1) {

			/*Caso o utilizador pretenda visuzalizar clientes, é chamada
			 *a função para que ele introduza os valores pelos quais estes
			 *devem começar.
			 */

			getField(field, SIZE);

			/*Chamada da função que vai procurar os clientes.*/

			aux = query_2_Clients(field);
			break;
		}
		else if (option == 2) {

			/*Caso o utilizador pretenda visuzalizar produtos, é chamada
			 *a função para que ele introduza os valores pelos quais estes
			 *devem começar.
			 */

			getField(field, SIZE);

			/*Chamada da função que vai procurar os produtos.*/

			aux = query_2_Products(field);
			break;
		}
		else if (strcmp(buffer, "q") == 0){

				/*Caso a opção seja de sair deste menu.*/

				break;
			} else {

				/*Caso a opção introduzida não seja válida.*/

				printf("Opção inválida!\n");
		}
	}

	if (aux == 0) {
		/*Quando existe navegação, limpa o ecrã antes de sair da query 2.*/
		system(CLEAR_COMMAND);
	}
}

/*****************************************************************************
 * END QUERY 2                                                               *
 *****************************************************************************/


/*****************************************************************************
 * BEGIN QUERY 3                                                             *
 *****************************************************************************/


/**
 * Menu a apresentar quando o utilizador for a introduzir os dados da pesquisa.
 * A função recebe os apontadores e durante a execução vai preenchê-los.
 *
 * @param product Nomde do produto a procurar.
 * @param month Mês a procurar.
 * @param mode Método de apresentação dos resultados: global ou filial a filial.
 * @return Void.
 */

static void query_3_subMenu(char *product, unsigned int *month,
                           unsigned int *mode)
{
	system(CLEAR_COMMAND);

	/*Indicação ao utilizador para introduzir o código do produto a procurar.*/

	printf("Introduza um produto: ");

	my_getline();

	strcpy(product, buffer);

	/*Indicação ao utilizador para introduzir o mês a procurar.*/

	printf("Introduza um mês: ");

	while (1) {

		/*Enquanto o valor introduzido não respeitar o intervalo válido
		 *dos meses, é pedido ao utilizador que introduza o mês.
		 */

		my_getline();

		*month = (unsigned) atoi(buffer);

		if (*month >= 1 && *month <= MONTHS) {
			break;
		}
		else {
			printf("Mês inválido!\n");
			printf("Introduza um mês: ");
		}
	}

	/*Indicação ao utilizador para indicar modo como os resultados da pesquisa
	 *deverão ser apresentados.
	 */

	printf("1 - Resultados filial a filial\n2 - Resultados globais\n");

	while (1) {

		/*Enquanto o valor introduzido não respeitar o intervalo válido
		 *das opções, é pedido ao utilizador que introduza uma opção.
		 */

		my_getline();

		*mode = (unsigned) atoi(buffer);

		if (*mode >= 1 && *mode <= 2) {
			break;
		}
		else {
			printf("Modo inválido!\n");
			printf("1 - Resultados filial a filial\n2 - Resultados globais\n");
		}
	}
}


/*
 *  @ Query 3.
 *	Função principal da query 3.
 *
 * 	Esta query pede ao utilizador um mês e um código de produto.
 *  Será depois apresentado no ecrã o número de total de vendas e o total
 *  faturado, para cada tipo de venda, com esse produto no mês introduzido.
 *  O utilizador também introduz a opção dos resultados serem globais ou
 *  filial a filial.
 *
 *  @return Void
 */
static void query_3(void)
{
	/*
	 * Declaração e inicialização da matriz que irá armazenar os preços do
	 * produto em cada uma das filiais e para cada tipo de venda - N ou P.
	 */

	double price[BRANCHES][2];


	/*
	 * Variáveis que vão guardar os valores globais faturado em vendas tipo
	 * N e tipo P.
	 */

	double total_Price_N = 0;
	double total_Price_P = 0;


	/*
	 *Declaração e inicialização da matriz que irá armazenar as unidades
	 *vendidas do produto em cada uma das filiais e para cada tipo de
	 *venda - N ou P.
	 */

	unsigned int units[BRANCHES][2];


	/*
	 *Variáveis que vão guardar os valores globais das unidades vendidas
	 *das vendas tipo N e tipo P.
	 */

	unsigned int total_Units_N = 0;
	unsigned int total_Units_P = 0;

	unsigned int i = 0;
	unsigned int j = 0;


	/*Mês a procurar.*/

	unsigned int month = 0;


	/*Método de apresentação dos resultados.*/

	unsigned int mode = 0;


	/*Buffer que vai guardar o código do produto a procurar.*/

	char product[SIZE] = "";


	/*Invocação do menu para introdução dos parâmetros de procura da query 3.*/

	query_3_subMenu(product, &month, &mode);


	/*Para cada filial e para cada tipo de venda, é acumulado as unidades
	 *vendidas e guardado o preço praticados em cada tipo de venda - N ou P.
	 */

	for(i = 0; i < BRANCHES; i++) {
		for(j = 0; j < 2; j++){
		billOfProductInMonth(billing, product, month, i + 1, &price[i][0],
		                     &price[i][1], &units[i][0], &units[i][1]);
		}
	}


	/*Caso o utilizador queira que os resultados sejam apresentados filial
	 *a filial
	 */

	if (mode == 1) {
		printf("Faturação de %s na:\n", product);

		for(i = 0; i < BRANCHES; i++) {
			printf("Filial %d\n", i + 1);

			for(j = 0; j < 2; j++) {
				printf("\tTipo %c\n\t Unidades : %d\n\t Faturado: %.2f\n",
				       j == 0 ? 'N' : 'P', units[i][j], price[i][j]);
			}
		}
	}


	/*Caso o utilizador queira que os valores a apresentar sem globais.*/

	else if (mode == 2) {
		printf("Faturação Global de %s:\n", product);

		for(i = 0; i < BRANCHES; i++) {
			total_Price_N += price[i][0];
			total_Units_N += units[i][0];
		}

		for(i = 0; i < BRANCHES; i++) {
			total_Price_P += price[i][1];
			total_Units_P += units[i][1];
		}


		/*Apresentação dos resultados.*/

		printf("Total em N\n\tUnidades : %d\n\tFaturado: %.2f\n", total_Units_N,
		                                                          total_Price_N);

		printf("Total em P\n\tUnidades : %d\n\tFaturado: %.2f\n", total_Units_P,
		                                                          total_Price_P);
	}
}

/*****************************************************************************
 * END QUERY 3                                                               *
 *****************************************************************************/


/*****************************************************************************
 * BEGIN QUERY 4                                                             *
 *****************************************************************************/


static void quer_4_subMenu(unsigned int *mode)
{
	printf("1 - Resultados filial a filial\n");
	printf("2 - Resultados globais\n");

	while (1) {
		my_getline();

		*mode = (unsigned) atoi(buffer);

		if (*mode >= 1 && *mode <= 2) {
			break;
		}
		else {
			printf("Opção inválida!\n");
		}
	}
}


/**
 *  Função que apresenta a lista ordenada dos códigos dos produtos que não
 *  foram comprados por filial.
 *
 *  Esta função é chamada pela função principal de query 4.
 *
 *  @return Void
 */

static void query_4_Mode_1(void)
{
	unsigned int i = 0;

	/*
	 *Variável que conta quantas filiais têm resultados a apresentar ao
	 *utilizador.
	 */

	unsigned int counter = 0;


	/*Variável que guarda o número de páginas máximo das 3 filiais.*/

	unsigned int max_page = 0;


	/*Array que guarda em cada posição o número de página a apresentar da
	 *respetiva filial.
	 */

	unsigned int max_pages[BRANCHES];


	/*Array que guarda em cada posição o número de produtos a apresentar da
	 *respetiva filial.
	 */

	unsigned int total_products[BRANCHES];


	/*
	 *Variável que guarda o número da página atual.
	 */

	unsigned int curr_page = 1;


	/*
	 *Buffer que guarda as opções de navegação dos resultados.
	 */

	char option[SIZE] = "";


	/*
	 *Para cada filial é calculado o número de produtos a apresentar, o número
	 *de páginas de produto a apresentar e também o máximo destas páginas até
	 *ao momento da sua execução.
	 *Caso a filial tenha resultados a apresentar, incrementa o contador de
	 *filiais com resultados.
	 */

	for (; i < BRANCHES; i++) {
		total_products[i] = getNotSoldInBranch(billing, i + 1);
		max_pages[i] = getNotSoldInBranchPages(billing, i + 1);

		max_page = (max_pages[i] > max_page) ? max_pages[i] : max_page;

		if (total_products[i] > 0) {
			counter++;
		}
	}



	/*Caso haja pelo menos uma filial com resultados a apresentar.*/

	if (counter > 0) {

		while(1) {
			system(CLEAR_COMMAND);


			/*
			 *É apresentado ao utilizador a página atual e a página
			 *máxima.
			 */

			printf("\nPag. %d de %d\n", curr_page, max_page);


			/*
			 *Para cada uma das filiais, caso a página atual não seja
			 *superior ao máximo da sua página e tenha resultados a
			 *apresentar, é escrito no ecrã a página atual do iterador.
			 */

			for(i = 0; i < BRANCHES; i++) {
				if(curr_page <= max_pages[i] && total_products[i] > 0) {
					printf("\nFilial %d | Total = %d\n", i + 1, total_products[i]);
					nextNotSoldInBranchPage(billing, i + 1);
				}
			}


			/*
			 *É apresentado ao utilizador o menu de navegação.
			 */

			navigationMenu(max_page, option, SIZE, 1);


			/*
			 *Caso a opção seja de sair dos resultados da querie.
			 */

			if (option[0] == 'q') {
				system(CLEAR_COMMAND);
				break;
			}


			/*
			 *Caso a opção seja de ir para a página seguinte dos
			 *resultados.
			 */

			else if (option[0] == 'n') {

				/*
				 *Caso a página atual não seja a última, é possível
				 *avançar e incrementa-se o valor da página atual.
				 */

				if (curr_page < max_page) {
					curr_page++;
				}
				else {
					for (i = 0; i < BRANCHES; i++) {
						goToNotSoldInBranchPage(billing, curr_page, i + 1);
					}
				}
			}


			/*
			 *Caso a opção seja de ir para a página anterior dos
			 *resultados.
			 */

			else if (option[0] == 'p') {


				/*
				 *Caso a página atual não seja a primeira, é possível
				 *voltar atráse decrementa-se o valor da página atual.
				 */

				if (curr_page > 1) {
					curr_page--;
				}


				/*
				 *Atualiza-se o valor da página atual em cada posição do
				 *vetor de iteradores para as filiais.
				 */

				for (i = 0; i < BRANCHES; i++) {
					goToNotSoldInBranchPage(billing, curr_page, i + 1);
				}
			}
			else {


				/*
				 *Caso não seja nenhuma das anterior, o utilizador pretende
				 *avançar (ou retroceder) diretamente para uma página.
				 *Convertem-se os carates introduzidos em interios e
				 *altera-se o valor da página atual na variável desta
				 *função e o valor da página atual em cada posição do
				 *vetor de iteradores para as filiais
				 */

				curr_page = (unsigned) atoi(option);

				for (i = 0; i < BRANCHES; i++) {
					goToNotSoldInBranchPage(billing, curr_page, i + 1);
				}
			}
		}

		system(CLEAR_COMMAND);
	}
	else {

		/*
		 *Mensagem apresentada quando não existem resultados a apresentar.
		 */
		printf("Todos os produtos foram comprados!\n");
	}
}


/*
 *	Função que apresenta a lista ordenada dos códigos dos produtos que não
 *  foram comprados em nenhuma filial.
 *
 *	Esta função é chamada pela função principal de query 4.
 *
 *  @return Void
 */

static void query_4_Mode_2(void)
{
	unsigned int i = 1;              /*Número de página. */
	unsigned int total_products = 0; /*Número total de produtos encontrados.*/
	unsigned int read_products = 0;  /*Número de produtos escritos por página.*/
	unsigned int total_pages = 0;    /*Número total de páginas a apresentar.*/


	/*Variável que indica se o programa deve apresentar o menu com as opções
	 *de navegação. Só não apresenta este menu quando tem 1 página de
	 *resultados, não tem nenhuma página, está na última página e recebe o
	 *comando de ir para a seguinte ou está na primeira página e recebe o
	 *comando de ir para a anterior.
	 */

	unsigned int show_menu = 1;


	/*Declaração e inicialização do buffer que recebe as opções de navegação
	 *da visualização dos resultados.*/

	char option[SIZE] = "";

	/*
	 *Calcula-se o número total de produtos que não foram comprados em
	 *nenhuma filial.
	 */

	total_products = getNotSold(billing);


	/*
	 *Caso hajam resultados para apresentar.
	 */

	if (total_products > 0) {

		/*
		 *Caso o número total de produtos a apresentar é menor que o número
		 *de elementos por página de resultado.
		 */

		if(total_products <= getNotSoldPageSize(billing)) {
			system(CLEAR_COMMAND);

			/*Escrita do número de produtos que ninguém comprou.*/

			printf("Produtos que ninguém comprou: %d\n", total_products);


			/*Apresentação no ecrã a página atual de resultados.*/

			nextNotSoldPage(billing);

		}
		else {

			/*Como o número total de clientes é superior aos elementos por
			 *página do iterador, determina-se o número total de páginas.
			 */

			total_pages = getNotSoldPages(billing);


			/*Faz-se a impressão das informações das páginas dos resultados.*/

			infoPrintPage(i, total_pages);


			/*Apresenta todos os elementos da página atual do iterador.
			 *É devolvido o número de produtos apresentados na página.
			 *Soma-se este valor ao número do último produto anterior.
			 *
			 *read_products tem o número do últimoproduto apresentado
			 *na página atual.
			 */

			read_products += nextNotSoldPage(billing);


			/*É apresentado o número do último produto na página atual
			 *e o número total de resultados.
			 */

			printf("Produtos %d de %d\n", read_products, total_products);


			/*Enquanto a opção introduzida não for de sair da navegação.*/

			while(option[0] != 'q') {


				/*Chamada a função de apresentação do menu de navegação.
				 *Apenas apresenta o menu se o comando anterior tenha
				 *sido válido.
				 *Poderá não apresentar o menu quando a opção
				 *não existe ou quando está na última página e recebe
				 *o comando de ir para a seguinte.
				 */

				navigationMenu(total_pages, option, SIZE, show_menu);


				/*Supõe que o comando a introduzir é válido. Caso se
				 *se verifique o contrário, esta variável é alterada.
				 */

				show_menu = 1;


				/*Caso o comando introduzido seja de ir para a página
				 *de resultados seguinte.
				 */

				if (option[0] == 'n') {


					/*Caso o número da página atual seja inferior
					 *ao número de páginas totais.
					 */

					if (i < total_pages) {


						/*O número da página atual é incrementado.*/

						i++;


						/*São apresentadas as informações das páginas
						 *dos resultados.
						 */

						infoPrintPage(i, total_pages);


						/*O número de total de produtos apresentados
						 *é incrementado e é apresentada a página
						 *de resultados atual.
						 */

						read_products += nextNotSoldPage(billing);


						/*É apresentado o número total de produtos
						 *que foram escritos e o número de produtos
						 *ao todo.*/

						printf("Produtos %d de %d\n", read_products, total_products);
					}
					else {


						/*Caso o comando seja de ir para a página
						 *de resultados seguinte e a página atual
						 *é a última, significa que o comando não
						 *é válido. Logo, não se irá apresentar o
						 *menu de navegação.
						 */

						show_menu = 0;
					}
				}


				     /*Caso o comando introduzido seja de ir para a página
				     *de resultados anterior.
				      */

				else if (option[0] == 'p') {


					/*Caso o número da página atual seja superior
					 *a 1.*/

					if (i > 1) {

						/*O número da página atual é decrementado.*/

						i--;


						/*São apresentadas as informações das páginas
						 *dos resultados.
						 */

						infoPrintPage(i, total_pages);


						/*O número de total de produtos apresentados
						 *é decrementado e é apresentada a página
						 *de resultados atual.
						 */

						read_products -= previousNotSoldPage(billing);


						/*É apresentado o número total de produtos
						 *que foram escritos e o número de produtos
						 *ao todo.*/

						printf("Produtos %d de %d\n", read_products,
							 total_products);
					}
					else {


						/*Caso o comando seja de ir para a página
						 *de resultados anterior e a página atual
						 *é a primeira, significa que o comando não
						 *é válido. Logo, não se irá apresentar o
						 *menu de navegação.
						 */

						show_menu = 0;
					}
				}


					/*Caso o comando a introduzir não seja nenhum dos
				      *anterior e não seja de sair do menu, supõe-se
					*que o utilizador pretenda ir diretamente para
					*uma página.
					*/

				else if (option[0] != 'q') {


					/*Faz-se a conversão para inteiro o número da página
					 *de destino.
					 */

					i = (unsigned) atoi(option);


					/*Apresentam-se as informações da página a ir.*/

					infoPrintPage(i, total_pages);


					/*Apresenta-se a página de destino. É devolvido
					 *o número de clientes lidos até essa página.*/

					read_products = goToNotSoldPage(billing, i);


					/*Ao número de clientes lidos até à página atual,
					 *é somado o número de produtos a apresentar na
					 *página atual.
					 */

					read_products += getNotSoldPageSize(billing) * (i - 1);


					/*Apresentam-se os clientes lidos e os produtos
					 *totais.
					 */

					printf("Produtos %d of %d\n", read_products, total_products);
				}
			}
		}

		system(CLEAR_COMMAND);
	}
	else {

		/*Caso contrário, não existem resultados a apresentar.*/

		printf("Não existem produtos que não foram comprados em nenhuma filial.\n");
	}
}


/**
 * @ Query 4
 *
 * Função principal da query 4.
 * Esta função apresenta ao utilizador os códigos de produtos que não foram
 * comprados. Dá-lhe a escolha dos resultados serem apresentados filial a filial
 * ou globais.
 *
 * @return Void.
 */
static void query_4(void)
{
	unsigned int mode = 0; /*Variável que guarda a opção de apresentação. */

	/*
	 *Chamada da função que dá a escolher ao utilizador o mode de apresentação.
	 *O resultado é guardado em mode.
	 */

	quer_4_subMenu(&mode);

	if (mode == 1) {

		/*
		 * Caso o utilizador queira ver os produtos que não foram comprados
		 * filial a filial.
		 */

		query_4_Mode_1();
	}
	else {

		/*
		 * Caso o utilizador queira ver os produtos que nunca foram comprados.
		 */

		query_4_Mode_2();
	}


	/*
	 * Quando se faz a navegação, nos iteradores do catálogo da faturação para
	 * esta query, é alterado o campo com a página atual sempre que se apresenta
	 * uma nova página.
	 * Antes que se termine esta função é necessário colocar o valor da página
	 * atual a 1, para quando se chamar de nova esta query (para a mesma execução),
	 * seja apresentada a primeira página.
	 * Se isto não fosse feito, a página apresentada seria a última visualizada
	 * pelo utilizador.
	 */

	resetAllSearches(billing);
}


/*****************************************************************************
 * END QUERY 4                                                               *
 *****************************************************************************/




/*****************************************************************************
 * BEGIN QUERY 5                                                             *
 *****************************************************************************/

/**
  * @ Query 5
  *
  * Função principal da query 5.
  * Esta função pede um código de cliente e apresenta ao utilizador uma tabela
  * com o número total de produtos comprados, mês a mês, filial a filial.
  *
  * @return Void.
  */
static void query_5(void)
{
	unsigned int i = 1; /*Variável de controlo de meses*/
	unsigned int j = 1; /*Variável de controlo de filiais*/
	unsigned int total = 0; /*Número total de unidades que o cliente comprou.*/


	/*Array que guarda em cada posição o número de unidades compradas de
	 *produtos que o cliente introduzido comprou.*/

	unsigned int t_units[BRANCHES];


	/*Buffer que vai guarda o código do cliente a procurar.*/

	char client[SIZE] = "";

	system(CLEAR_COMMAND);


	/*A query pede um código de cliente.*/

	printf("Introduza um cliente: ");
	my_getline();
	strcpy(client, buffer);

	system(CLEAR_COMMAND);


	/*É apresentado no ecrã o código do cliente.*/

	printf("Número Total de Compras do Cliente %s.\n\n", client);


	/*Apresentam-se os nomes das filiais.*/

	printf("\t%10s", "FILIAL 1");

	for (; j < BRANCHES; j++) {
		printf("%13s %d", "FILIAL", j + 1);
	}

	printf("\n");

	/*Para cada mês e cada filial chama-se a função getTotalProducts.
	 *Esta função recebe um código de cliente, o catálogo de uma filial,
	 *e um mês. Com isto, devolve o número de unidades de produtos compradas
	 *pelo cliente naquela filial e naquele mês.
	 */

	for (; i <= MONTHS; i++) {
		for (j = 0; j < BRANCHES; j++) {
			t_units[j] = getTotalProducts(branch_vec[j], client, i);

			/*
			 *Soma-se ao valor total das unidades o valor calculado.
			 */

			total += t_units[j];
		}


		/*
		 *Para o mês atual, apresentam-se as unidades compradas de produto
		 *em cada filial pelo cliente.
		 */

		printf("Mês %2d%10d", i, t_units[0]);

		for (j = 1; j < BRANCHES; j++) {
			printf("%15d", t_units[j]);
		}

		printf("\n");
	}


	/*
	 *No fim, apresenta-se o número total de unidades.
	 */
	printf("\nNúmero Total de Unidades Compradas: %d.\n\n", total);
}

/*****************************************************************************
 * END QUERY 5                                                               *
 *****************************************************************************/


/*****************************************************************************
 * BEGIN QUERY 6                                                             *
 *****************************************************************************/

/**
 *
 * Função que chama o menu que pede ao utilizador para introduzir o
 * intervalo de meses que pretende nos resultados.
 * A função principal da query 6 passa como argumento apontadores que vão
 * guardar o intervalos de meses.
 *
 * @param left Limite inferior do intervalo.
 * @param right Limite superior do intervalo. Esta função apenas termina
 *		      o valor deste é maior ou igual ao valor inferior do intervalo.
 * @return Void.
 */
static void query_6_subMenu(unsigned int *left, unsigned int *right)
{
	system(CLEAR_COMMAND);

	/*
	 *Limite inferior do intervalo
	 */

	printf("Introduza o primeiro mês > ");

	while (1) {

		/*
		 * Enquanto o valor introduzido não seja um mês válido, a função
		 * pede um mês.
		 */

		my_getline();

		*left = (unsigned) atoi(buffer);

		if (*left > 0 && *left <= MONTHS) {
			break;
		}
		else {
			printf("Mês inválido!\n");
		}
	}

	/*
	 *Limite superior do intervalo
	 */


	printf("Introduza o segundo mês > ");

	while (1) {

		/*
		 * Enquanto o valor introduzido não seja um mês válido, e pelo maior
		 * ou igual ao limite inferior, a função pede um mês.
		 */

		my_getline();

		*right = (unsigned) atoi(buffer);

		if (*right > 0 && *right <= MONTHS && *right >= *left) {
			break;
		}
		else {
			printf("Mês inválido!\n");
		}
	}
}


/*
 * @ Query 6
 *
 * Função principal da query 6.
 * Esta função, a partir de um intervalo fechado de meses, determina e apresenta
 * ao utilizador o número de vendas registadas e o total faturado nesse período.
 *
 * @return Void.
 */
static void query_6(void)
{
	unsigned int i = 0;
	unsigned int left = 0; /*Limite inferior do intervalo.*/
	unsigned int right = 0; /*Limite superior do intervalo.*/
	unsigned int global_units = 0; /*Total de unidades.*/
	double global_billed = 0; /*Total faturado.*/

	query_6_subMenu(&left, &right);

	for(i = left; i <= right; i++) {

		/*
		 *A função getTotalBilled, a partir do mês e do catálogo da faturação,
		 *devolve o total faturado naquele mês.
		 */

		global_billed += getTotalBilled(billing, i);


		/*
		 *A função getTotalUnits, a partir do mês e do catálogo da faturação,
		 *devolve o total de unidades vendidas naquele mês.
		 */

		global_units += getTotalUnits(billing, i);
	}


	/*
	 *Apresentação de resultados.
	 */

	printf("Entre os meses %d e %d\nUnidades Vendidas: %d\n",
		      left, right, global_units);

	printf("Total Faturado: %E\n", global_billed);
}

/*****************************************************************************
 * END QUERY 6                                                               *
 *****************************************************************************/


/*****************************************************************************
 * BEGIN QUERY 7                                                             *
 *****************************************************************************/


 /**
  *  Função que é enviada como parâmetro na filterClientes.
  *  Recebe um código de cliente e vai a cada uma das filiais verifica se o
  *  cliente comprou em todas.
  *
  *  @param cliente Código do cliente a procurar.
  *  @return bool true caso o cliente tenha comprado em todas as filiais
  *	     false caso não tenha comprado em pelo menos uma.
  */
static bool isAllBranchClient(const void *client)
{
	bool b = false; /*Valor a devolver. Por defeito é false.*/
	unsigned int i = 0;


	/*Variável que conta em quantas filiais o cliente realizou compras.*/

	unsigned int counter = 0;


	/*Em cada uma das filiais, é aplicada a função existClientInBranch.
	 *Esta função vai às BSTMap da filial e vai comparando o código do
	 *cliente com os nós da árvore da BSTMap. Se não encontrar nenhuma
	 *chave igual, devolve false. */

	for (; i < BRANCHES; i++) {
		if (existClientInBranch(branch_vec[i], (char*) client) == true) {
			/*Se o cliente fez compras na filial atual, o contador de
			 *numero de filiais em que comprou incrementa.
			 */
			counter++;
		} else {
			break;
		}
	}

	if (counter == BRANCHES) {
		/*Se o número de filiais e o número de filiais em que ele comprou
		 * forem iguas, então o valor a retornar é true.*/
		b = true;
	}

	return b;
}


/**
 * @ Query 7
 *
 * Função principal da query 7.
 * Esta função apresenta ao utilizador os cliente que fizeram compras em todas
 * as filiais.
 *
 * @return Void.
 */
static void query_7(void)
{
	char option[SIZE] = "";
	unsigned int i = 1;              /* Número de página. */
	unsigned int total_clients = 0;  /* Número total de clientes encontrados. */
	unsigned int read_clients = 0;   /* Número de clientes escritos por página. */
	unsigned int total_pages = 0;    /* Número total de páginas.*/
  unsigned int show_menu = 1;      /* Mostra o menu se tiver mais que uma página. */

	/*
	 *filterClients percorre a estruta que contém todos os códigos de clientes
	 *e a cada um deles aplica a função isAllBranchClient.
	 *Caso a função aplicada devolva true, o código do cliente lido é
	 *enviado para o iterador que irá apresentar os códigos no ecrã.
	 *Esta função devolve também o número de elementos no iterador.
	 */

	total_clients = filterClients(clients, isAllBranchClient);


	/*
	 *Caso hajam clientes para apresentar
	 */

	if (total_clients > 0) {

		/*Caso o número total de clientes a apresentar seja menor que o
		 *número de elementos que existem, por defeito, em cada página
		 *do iterador.
		 */

		if (total_clients <= getClientPageSize(clients)) {
			/*Apenas há uma página de resultados a apresentar.*/

			system(CLEAR_COMMAND);


			/*Escrita do número de clientes que começam por str.*/

			printf("Clientes encontrados: %d\n", total_clients);


			nextClientPage(clients);/*Apresentação no ecrã a página atual de resultados.*/
		}
		else {

			/*Como o número total de clientes é superior aos elementos por
			 *página do iterador, determina-se o número total de páginas.
			 */

			total_pages = getNumClientPages(clients);


			/*Faz-se a impressão das informações das páginas dos resultados.*/

			infoPrintPage(i, total_pages);

			/*O número de total de clientes apresentados
			 *é incrementado e é apresentada a página
			 *de resultados atual.
			 */

			read_clients += nextClientPage(clients);


			/*Apresenta todos os elementos da página atual do iterador.
			 *É devolvido o número de clientes apresentados na página.
			 *Soma-se este valor ao número do último cliente anterior.
			 *
			 *read_clientes tem o número do último cliente apresentado
			 *na página atual.
			 */

			printf("Clientes %d de %d\n", read_clients, total_clients);


			/*Enquanto a opção introduzida não for de sair da navegação.*/

			while(option[0] != 'q') {

				/*Chamada a função de apresentação do menu de navegação.
				 *Apenas apresenta o menu se o comando anterior tenha
				 *sido válido.
				 *Poderá não apresentar o menu quando a opção
				 *não existe ou quando está na última página e recebe
				 *o comando de ir para a seguinte.
				 */

				navigationMenu(total_pages, option, SIZE, show_menu);


				/*Supõe que o comando a introduzir é válido. Caso se
				 *se verifique o contrário, esta variável é alterada.*/

				show_menu = 1;


				/*Caso o comando introduzido seja de ir para a página
				 *de resultados seguinte.
				 */

				 if (option[0] == 'n') {


 					/*Caso o número da página atual seja inferior
 					 *ao número de páginas totais.*/

 					if (i < total_pages) {


 						/*O número da página atual é incrementado.*/

 						i++;

 						/*São apresentadas as informações das páginas
 						 *dos resultados.
 						 */

 						infoPrintPage(i, total_pages);


 						/*O número de total de clientes apresentados
 						 *é incrementado e é apresentada a página
 						 *de resultados atual.
 						 */

 						read_clients += nextClientPage(clients);


 						/*É apresentado o número total de clientes
 						 *que foram escritos e o número de clientes
 						 *ao todo.*/

 						printf("Clientes %d de %d\n", read_clients, total_clients);
 					}
 					else {


 						/*Caso o comando seja de ir para a página
 						 *de resultados seguinte e a página atual
 						 *é a última, significa que o comando não
 						 *é válido. Logo, não se irá apresentar o
 						 *menu de navegação.
 						 */

 						show_menu = 0;
 					}
				}


					/*Caso o comando introduzido seja de ir para a página
				      *de resultados anterior.
				      */
				else if (option[0] == 'p') {
					/*Caso o número da página atual seja superior
					 *a 1.*/

					if (i > 1) {


						/*O número da página atual é decrementado.*/

						i--;


						/*São apresentadas as informações das páginas
						 *dos resultados.
						 */

						infoPrintPage(i, total_pages);


						/*O número de total de clientes apresentados
						 *é decrementado e é apresentada a página
						 *de resultados atual.
						 */

						read_clients -= previousClientPage(clients);


						/*É apresentado o número total de clientes
						 *que foram escritos e o número de clientes
						 *ao todo.*/

						printf("Clientes %d de %d\n", read_clients, total_clients);
					}
					else {

						/*Caso o comando seja de ir para a página
						 *de resultados anterior e a página atual
						 *é a primeira, significa que o comando não
						 *é válido. Logo, não se irá apresentar o
						 *menu de navegação.
						 */
						show_menu = 0;
					}
				}


					/*Caso o comando a introduzir não seja nenhum dos
				      *anterior e não seja de sair do menu, supõe-se
					*que o utilizador pretenda ir diretamente para
					*uma página.
					*/

				else if (option[0] != 'q') {


					/*Faz-se a conversão para inteiro o número da página
					 *de destino.
					 */

					i = (unsigned) atoi(option);


					/*Apresentam-se as informações da página a ir.*/

					infoPrintPage(i, total_pages);


					/*Apresenta-se a página de destino. É devolvido
					 *o número de clientes lidos até essa página.*/

					read_clients = goToClientPage(clients, i);


					/*Ao número de clientes lidos até à página atual,
					 *é somado o número de clientes a apresentar na
					 *página atual.
					 */
					read_clients += getClientPageSize(clients) * (i - 1);


					/*Apresentam-se os clientes lidos e os clientes
					 *totais.
					 */

					printf("Clientes %d of %d\n", read_clients, total_clients);
					}
				}

				system(CLEAR_COMMAND);
			}
	}
	else {
		printf("Nenhum cliente comprou em todas as filiais!\n");
	}
}

/*****************************************************************************
 * END QUERY 7                                                               *
 *****************************************************************************/


/*****************************************************************************
 * BEGIN QUERY 8                                                             *
 *****************************************************************************/

 /**
  *  Menu a apresentar quando o utilizador for a introduzir os dados da pesquisa.
  *  A função recebe os apontadores e durante a execução vai preenchê-los.
  *
  *  @param product Nome do produto a procurar.
  *  @param branch  Filial a procurar.
  *  @return Void.
  */
static void query_8_subMenu(char *product, unsigned int *branch)
{

	system(CLEAR_COMMAND);


	/*Indicação ao utilizador para introduzir o código do produto a procurar.*/

	printf("Introduza um produto: ");

	my_getline();
	strcpy(product, buffer);



	/*Indicação ao utilizador para introduzir a filial a procurar.*/

	printf("Introduza uma filial: ");

	while (1) {

		/*Enquanto o valor introduzido não respeitar o intervalo válido
		 *das filiais, é pedido ao utilizador que introduza uma filial.
		 */

		my_getline();

		*branch = (unsigned) atoi(buffer);

		if (*branch >= 1 && *branch <= BRANCHES) {
			break;
		}
		else {
			printf("Filial inválida!\n");
			printf("Introduza uma filial: ");
		}
	}

	system(CLEAR_COMMAND);
}


/**
 *  @ Query 8.
 *  Função principal da query 8.
 *
 *  Esta query pede ao utilizador um produto e uma filial.
 *  Apresenta no ecrã os códigos e o número total de clientes que compraram
 *  o produto naquela filial.
 *
 *  @return Void
 */
static void query_8(void)
{

	/*
	 *Total de unidades compradas nos modos N e P.
	 */

	unsigned int total_N = 0;
	unsigned int total_P = 0;


	/*
	 *Variável que guarda o número da página atual.
	 */

	unsigned int curr_page = 1;


	/*
	 *Número de páginas máximo a apresentar nos modos N e P.
	 */

	unsigned int max_page_N = 0;
	unsigned int max_page_P = 0;


	/*
	 *Número máximo de páginas a apresentar.
	 */

	unsigned int max_page = 0;


	/*
	 *Número da filial a procurar.
	 */

	unsigned int branch = 0;


	/*
	 *Código do produto a procurar.
	 */

	char product[SIZE] = "";


	/*
	 *Buffer que guarda as opções de navegação dos resultados.
	 */

	char option[SIZE] = "";

	/*
	 *Variável que guarda a diferença de tempo desde o início até ao fim da
	 *execução da query.
	 */

	double diff = 0;
	clock_t begin = 0;
	clock_t end = 0;


	/*
	 *Chamada do menu que pede os parâmetros de procura.
	 */

	query_8_subMenu(product, &branch);


	/*
	 *Início do relógio.
	 */

	begin = clock();


	/*
	 *  A função clientsThatBought recebe uma filial, o código de um produto
	 *  e os contadores para as unidades.
	 *  Esta função inicializa, para cada tipo, o iterador que vai guarda
	 *  os códigos dos clientes que compraram o produto.
	 *  Depois, aplica um fold a todos os nós das BSTree apontadas pelos nós da
	 *  árvore da BSTMap. Este fold compara os nós da BSTree (que têm códigos
	 *  de produto) até que encontre um que seja igual ao produto que lhe é
	 *  enviado como parâmetro. Quando isso acontece, verifica o tipo de venda e
	 *  manda para o respetivo iterador para ser apresentado posteriormente.
	 */

	clientsThatBought(branch_vec[branch - 1], product, &total_N, &total_P);


	/*
	 *Fim do relógio, cálculo da diferença de tempo e escrita no ecrã do tempo..
	 */

	end = clock();
	diff = ((double) (end - begin)) / CLOCKS_PER_SEC;

	printf("Resultado obtido em: %.5f s\n\n", diff);


	/*Caso hajam resultados a apresentar.*/

	if (total_N > 0 || total_P > 0) {

		/*Calcula-se o número máximo de páginas a apresentar, por tipo. */

		max_page_N = getNumModePages(branch_vec[branch - 1], 'N');
		max_page_P = getNumModePages(branch_vec[branch - 1], 'P');

		/*Também se calcula o número máximo de páginas global.*/

		max_page = (max_page_N > max_page_P) ? max_page_N : max_page_P;

		while(1) {

			/*Caso a página atual seja inferior ao máximo de páginas
			 * no modo N. */

			if (total_N > 0 && curr_page <= max_page_N) {
				printf("Modo N\tTotal = %d\n", total_N);

				/*Imprime-se a página atual.*/

				nextModePage(branch_vec[branch - 1], 'N');
			}


			/*Caso a página atual seja inferior ao máximo de páginas
			 * no modo P.*/

			if (total_P > 0 && curr_page <= max_page_P) {
				printf("\nModo P\tTotal = %d\n", total_P);

				/*Imprime-se a página atual.*/

				nextModePage(branch_vec[branch - 1], 'P');
			}


			/*Caso existam mais do que 1 página, apresenta-se o menu de
			 *navegação.*/

			if (max_page > 1) {
				printf("\nPag. %d de %d\n", curr_page, max_page);

				navigationMenu(max_page, option, SIZE, 1);
			}
			else {

				/*Caso contrário, apresentam-se os resultados e o menu
				 *principal.*/

				break;
			}

			if (strcmp(option, "q") == 0) {

				/*Caso o utilizador queira sair da query.*/

				break;
			}

			     /*Caso o utilizador queira ir para a página seguinte.*/

			else if (strcmp(option, "n") == 0) {

				/*Se a página atual não for a última, incrementa-se a variável
				 *da função responsável pela página atual.*/

				if (curr_page < max_page) {
					curr_page++;
				}
				else {

					/*Caso contrário, está na última página e volta a
					 *imprimir a página atual.*/

					goToModePage(branch_vec[branch - 1], 'N', curr_page);
					goToModePage(branch_vec[branch - 1], 'P', curr_page);
				}
			}

			/*Caso o utilizador queira ir para a página anterior.*/

			else if (strcmp(option, "p") == 0) {

				/*Se a página atual não for a primeira, decrementa-se a variável
				 *da função responsável pela página atual.*/

				if (curr_page > 1) {
					curr_page--;
				}

				/*Imprime-se a página atual para cada tipo de venda.*/

				goToModePage(branch_vec[branch - 1], 'N', curr_page);
				goToModePage(branch_vec[branch - 1], 'P', curr_page);
			}
			else {

				/*Se não for nenhuma das anterior, o utilizador pretende
				 *ir direto para uma página. Converte-se para inteiro
				 *os carateres introduzidos.*/

				curr_page = (unsigned) atoi(option);

				/*
				 *A goToModePage imprime a página introduzida dos resultados
				 *obtidos, sendo ela também quem valida se a página introduzida
				 *existe para nos resultados obtidos.
				 */

				goToModePage(branch_vec[branch - 1], 'N', curr_page);
				goToModePage(branch_vec[branch - 1], 'P', curr_page);
			}
		}
	}
	else {
		printf("O Produto %s não foi Comprado na Filial %d!\n", product, branch);
	}
}

/*****************************************************************************
 * END QUERY 8                                                               *
 *****************************************************************************/




/*****************************************************************************
 * BEGIN QUERY 9                                                             *
 *****************************************************************************/


 /**
  *  Função que compara 2 struct aux_queries em função dos códigos de produtos-
  *  Esta função é uma função auxiliar e é chamada pela função principal da
  *  query 9 que utiliza-a para construir uma BSTree em que os nós estão ordenados
  *  pelos códigos de produto.
  *
  *  @param a Estrutura a comparar.
  *  @param b Estrutura a comparar.
  *  @return Resultado da comparação.
  */
static int cmpProduct(const void *a, const void *b)
{
	/*Como os parâmetros introduzidos são do tipo void*, é preciso convertê-los
	 *primeiro para struct aux_queries.*/

	struct aux_queries *aux1 = (struct aux_queries*) a;
	struct aux_queries *aux2 = (struct aux_queries*) b;

	return strcmp(aux1->product, aux2->product);
}


/**
 *  Função que compara 2 struct aux_queries em função dos códigos de produtos-
 *  Esta função é uma função auxiliar e é chamada pela função principal da
 *  query 9 que utiliza-a para construir uma BSTree em que os nós estão ordenados
 *  pelos unidades de produto vendidas.
 *
 *  @param a Estrutura a comparar.
 *  @param b Estrutura a comparar.
 *  @return Resultado da comparação.
 */
static int cmpUnits(const void *a, const void *b)
{
	int i = 0;

	/*Como os parâmetros introduzidos são do tipo void*, é preciso convertê-los
	 *primeiro para struct aux_queries.*/

	struct aux_queries *aux1 = (struct aux_queries*) a;
	struct aux_queries *aux2 = (struct aux_queries*) b;

	i = (aux1->units > aux2->units) ? -1 : 1;

	return i;
}


/**
 *  Função que recebe uma struct aux_queries e imprime os seus campos.
 *  Esta função é uma função auxiliar e é chamada pela função principal da
 *  query 9 que utiliza-a para construir uma BSTree..
 *
 *  @param a Estrutura a imprimir.
 *  @return Void.
 */
static void printQ9(const void *a)
{
	struct aux_queries *aux = (struct aux_queries*) a;

	printf("%s %d\n", aux->product, aux->units);
}


/**
 *  Função que recebe um acumulador e um valor a somar a este.
 *  Esta função é uma função auxiliar que vai somar a uma struct aux_queries
 *  as unidades de outra struct aux_queries.
 *
 *  @param acc       Acumulador.
 *  @param new_value Valor a acrescentar ao acumulador.
 *  @return Void.
 */
static void addUnits(void *acc, const void *new_value)
{
	struct aux_queries *aux = (struct aux_queries*) new_value;

	((struct aux_queries*) acc)->units += aux->units;
}


/**
 *  A partir de uma estrura Sale, copia de lá o código de produto e as unidades
 * da venda para uma struct aux_queries.
 *  Depois, chama a função addWithCondBSTree. Esta função percorre todos os nós
 * de uma BSTree e, quando o nó e a chave que tem como parâmetro forem iguais
 * (segundo a função de comparação fornecida na criação da árvore), aplica a estes
 * a função addUnits que soma as unidades da venda.
 *
 *  @param acc       Acumulador.
 *  @param new_value Valor a acrescentar ao acumulador.
 *  @return Void.
 */
static void addProductBSTree(const void *a, void *acc)
{
	Sale s = (Sale) a;
	struct aux_queries aux;

	aux.product = getProduct(s);
	aux.units = getUnits(s);

	addWithCondBSTree((BSTree) acc, &aux, addUnits);
}


/**
 * Esta é uma função auxiliar que acrescenta a uma árvore BSTree o nó de outra
 * árvore BSTree.
 *
 * @param a   Nó que vai ser acrescentado.
 * @param acc Árvore BSTree que vai receber o novo nó.
 * @return VOid.
 */
static void addToFieldBSTree(const void *a, void *acc)
{
	addBSTree((BSTree) acc, (struct aux_queries*) a);
}


/**
 * Função que chama o menu que pede ao utilizador para introduzir o
 * código de cliente e o mês a procurar.
 * A função principal da query 9 passa como argumento apontadores que vão
 * guardar estes dados.
 *
 * @param client Código de cliente a procurar.
 * @param month  Mês a procurar.
 * @return Void.
 */
static void query_9_subMenu(char *client, unsigned int *month)
{
	system(CLEAR_COMMAND);


	/*Indicação ao utilizador para introduzir o código do cliente a procurar.*/

	printf("Introduza um cliente: ");

	my_getline();
	strcpy(client, buffer);

	/*Indicação ao utilizador para introduzir o mês a procurar.*/

	printf("Introduza um mês: ");

	while (1) {


		/*Enquanto o valor introduzido não respeitar o intervalo dos meses,
		 *é pedido ao utilizador que introduza um mês.
		 */

		my_getline();

		*month = (unsigned) atoi(buffer);

		if (*month >= 1 && *month <= MONTHS) {
			break;
		}
		else {
			printf("Mês inválido!\n");
			printf("Introduza um mês: ");
		}
	}

	system(CLEAR_COMMAND);
}


/**
 *  @ Query 9.
 *	Função principal da query 9.
 *
 * 	Esta query pede ao utilizador um cliente e um mês.
 *	Apresenta no ecrã os produtos que o cliente mais comprou por quantidade, por
 * ordem descendente.
 *
 *  @return Void
 */
static void query_9(void)
{
	unsigned int i = 0;

	unsigned int month = 0; /*Mês a procurar.*/
	char client[SIZE] = ""; /*Cliente a procurar.*/

	double diff = 0; /*Diferença de tempo desde o início até ao fim da execução
			      * da query.*/
	clock_t begin = 0;
	clock_t end = 0;

	unsigned int page = 0; /*Página atual.*/
	unsigned int total_pages = 0; /*Número total de páginas.*/


	/*Criação de árvores BSTree auxiliares.
	 *A aux_product está ordenada por código de produto.
	 *A aux_field está ordenada por unidades de produto compradas.
	 */

	BSTree aux_product = createBSTree(sizeof(struct aux_queries), cmpProduct,
	                                  printQ9);

	BSTree aux_field = createBSTree(sizeof(struct aux_queries), cmpUnits,
	                                printQ9);


	/*Iterador que vai apresentar os resultados. */

	Iterator aux_iterator = NULL;


	/*Chamada da função que pede ao utilizador os valores de procura.*/

	query_9_subMenu(client, &month);


	/*Início do relógio.*/

	begin = clock();


	/*Para cada uma das filiais, procura-se pela árvore BSTMap (que está ordenada
	 *por códigos de clientes).
	 *Quando se encontrar o nó com o cliente pretendido, vai-se à BSTree apontada
	 *por esse nó e a cada uma das vendas que lá existe, aplica-se a addProductBSTree,
	 *que vai adicionar à aux_product os produtos com as unidades das vendas.
	 *Se por acaso se quiser adicionar a esta BSTree um produto que lá exista,
	 *é aplicada a função addUnits que soma a esse nó da aux_product as unidades
	 *da outra venda.
	 *No fim tem-se em aux_product uma BSTree com todas as unidades de cada produto,
	 *contudo ordenado por código de produto.
	 */

	for(; i < BRANCHES; i++) {
		foldClientProductsInMonth(branch_vec[i], client, month, aux_product,
		                          addProductBSTree);
	}


	/*Como aux_product está ordenado por código de produto, aplica-se-lhe um
	 *foldBSTree em que a função é addToFieldBSTree. Esta função passa todos os
	 *nós de uma árvore (aux_product) para outra árvore (aux_field), sendo que
	 *esta última faz a ordenadação por unidades de produto vendidas.
	 */

	foldBSTree(aux_product, aux_field, addToFieldBSTree);


	/*
	 *toIteratorInOrderBSTree converte a BSTree aux_field num iterador, devolvendo
	 *no final o número de elemntos no iterador.
	 *Os elementos estão por ordem decrescente.
	 */

	aux_iterator = toIteratorInOrderBSTree(aux_field);


	/*
	 *O relógio termina antes da apresentação dos resultados, mas antes é
	 *escrito no ecrã o tempo decorrido desde o início da query.
	 */

	end = clock();
	diff = ((double) (end - begin)) / CLOCKS_PER_SEC;

	printf("Resultado obtido em: %.5f s\n\n", diff);


	/*Apresentam-se os resultados.*/

	printf("Cliente %s | Mes %d\n", client, month);
	printAllIterator(aux_iterator);

	destroyBSTree(aux_product);
	destroyBSTree(aux_field);
	destroyIterator(aux_iterator);
}

/*****************************************************************************
 * END QUERY 9                                                               *
 *****************************************************************************/



/*****************************************************************************
 * BEGIN QUERY 10                                                            *
 *****************************************************************************/

/**
 *  @brief Sub menu da query 10.
 *
 *  Pede ao utilizador a quantidade dos produtos mais vendidos a ser
 *  mostrada no ecrã. A quantidade não pode ser negativa nem zero.
 *  Se, por ventura, o utilizador introduzir um número superior ao número
 *  total de produtos, todos os produtos são apresentados no ecrã.
 *
 *  @param n  Apontador que irá guardar a quantidade de produtos pretendida.
 *  @return Void.
 */
static void query_10_subMenu(unsigned int *n)
{
	/* Limpa o ecrã. */

	system(CLEAR_COMMAND);

	printf("Introduza um valor de N: ");

	while (1) {
		my_getline();

		*n = (unsigned) atoi(buffer);

		if (*n > 0) {

			/* Apenas considera válido se o número introduzido é superior a zero. */

			break;
		}
		else {
			printf("N inválido!\n");
			printf("Introduza um valor de N: ");
		}
	}

	/* Limpa o ecrã. */

	system(CLEAR_COMMAND);
}


/**
 *  @Query 10
 *  Função principal da Query 10.
 *
 *  Começa por pedir ao utilizador para introduzir um número válido de
 *  produtos mais vendidos a mostrar no ecrã.
 *  Solução:
 *  	No final da leitura dos dados o módulo da faturação guarda uma
 *  	BSTree que contém uma estrutura com os seguintes campos:
 *  		Código de produto.
 *  		Total de unidades compradas dess produto.
 *  		Número total de clientes que compraram esse produto.
 *  	Seguindo este calculo auxiliar, a árvore tem que ser convertida para
 *  	outra árvore que ordena os produtos por ordem decrescente de unidades
 *  	compradas. No final, basta passar esta árvore para um iterador.
 *
 *  @return Void.
 */
static void query_10(void)
{
	unsigned int i = 0;               /* Variável de controlo do ciclo for. */
	unsigned int max_page = 0;        /* Guarda o valor máximo das páginas
	                                   * dos códigos de produtos. */
	unsigned int max_pages[BRANCHES]; /* Guarda o número máximo de páginas de
	                                   * códigos de produto para todas as
	                                   * filiais. */
	unsigned int curr_page = 1;       /* Última página impressa. */
	unsigned int n = 0;               /* Quantidade de produtos a mostrar. */
	unsigned int is_one_page = 0;     /* Testa se o número de produtos a
	                                   * imprimir cabe numa página. */
	char option[SIZE] = "";           /* Guarda o valor das opções de
	                                   * navegação. */
	double diff = 0;                  /* Mostra o tempo total da obtenção de
	                                   * resultados para esta query. */
	clock_t begin = 0;                /* Contagem inicial do tempo. */
	clock_t end = 0;                  /* Contagem final do tempo de resposta
	                                   * da query. */


	/* Pede ao utilizador a quantidade de produtos pretendida. */

	query_10_subMenu(&n);

	/* Inicia a contagem do tempo de resposta da query. */

	begin = clock();

	/* Cria os iteradores que contêm os produtos mais vendidos filial a
	 * filial. */

	getNMostBought(billing, n);


	/* Termina a contagem e mostra o tempo de resposta da query. */

	end = clock();
	diff = ((double) (end - begin)) / CLOCKS_PER_SEC;
	printf("Resultado obtido em: %.5f s\n", diff);


	/* Obtém o número de páginas para cada filial. */

	for (; i < BRANCHES; i++) {
		max_pages[i] = getMostBoughtPages(billing, i + 1);

		/* Calcula qual das 3 filiais tem o maior número de páginas. */

		max_page = (max_pages[i] > max_page) ? max_pages[i] : max_page;
	}

	is_one_page = (max_page == 1) ? 1 : 0;

	while(1) {

		/* Se os códigos de produtos cabem numa página não é necessário haver
		 * paginação. */

		if (is_one_page == 0) {
			printf("\nPág. %d de %d\n", curr_page, max_page);
		}

		/* Mostra o conteúdo de uma página para cada filial. */

		for(i = 0; i < BRANCHES; i++) {
			if(curr_page <= max_pages[i]) {
				printf("\nFilial %d\n", i + 1);
				nextMostBoughtPage(billing, i + 1);
			}
		}

		/* Se os códigos de produto cabem numa página não é necessário invocar
		 * o menu de navegação. A query termina. */

		if (is_one_page == 1) {
			break;
		}

		/* Chama o menu para o utilizador introduzir uma opção de navegação. */

		navigationMenu(max_page, option, SIZE, 1);

		if (option[0] == 'q') {

			/* O utilizador pretende sair, a query é terminada e o ecrã limpo. */

			system(CLEAR_COMMAND);
			break;
		}
		else if (option[0] == 'n') {

			/* O utilizador pretende navegar para a página seguinte.
			 * curr_page é incrementado em uma unidade. */

			if (curr_page < max_page) {
				curr_page++;
			}

			for (i = 0; i < BRANCHES; i++) {

				/* O iterador de cada filial vai para a página seguinte. */

				goToMostBoughtPage(billing, curr_page, i + 1);
			}
		}
		else if (option[0] == 'p') {

			/* O utilizador pretende navegar para a página anterior.
			 * curr_page é decrementado em uma unidade. */

			if (curr_page > 1) {
				curr_page--;
			}

			for (i = 0; i < BRANCHES; i++) {

				/* O iterador de cada filial vai para a página anterior. */

				goToMostBoughtPage(billing, curr_page, i + 1);
			}
		}
		else {

			/* O utilizador pretente ir para um índice válido de página. */
			/* curr_page toma o valor de índice. */

			curr_page = (unsigned) atoi(option);

			for (i = 0; i < BRANCHES; i++) {

				/* Navega no iterador de cada filial para a página pretendida do
				 * utilizador. */

				goToMostBoughtPage(billing, curr_page, i + 1);
			}
		}

		/* Limpa o ecrâ. */

		system(CLEAR_COMMAND);
	}

	/* Reinicia as pesquisas realizadas. */

	resetAllSearches(billing);
}

/*****************************************************************************
 * END QUERY 10                                                              *
 *****************************************************************************/


/*****************************************************************************
 * BEGIN QUERY 11                                                            *
 *****************************************************************************/

/**
 *  Compara duas estrututas auxiliares das queries.
 *
 *  @param a Estrutura a comparar.
 *  @param b Estrutura a comparar.
 *  @return -1 caso a estrutura a tenha um valor gasto superior a b ou
 *          1 caso contrário.
 */
static int cmpSpent(const void *a, const void *b)
{
	struct aux_queries *aux1 = (struct aux_queries*) a;
	struct aux_queries *aux2 = (struct aux_queries*) b;
	int i = 0;

	i = (aux1->spent > aux2->spent) ? -1 : 1;

	return i;
}


/**
 *  Função para realizar a impressão de um código de produto e o total
 *  gasto.
 *
 *  @param a Estrutura que contém os campos de código de produto e o
 *           total gasto.
 *  @return Void.
 */
static void printQ11(const void *a)
{
	struct aux_queries *aux = (struct aux_queries*) a;

	printf("%s %.2f\n", aux->product, aux->spent);
}


/**
 *  Função que recebe duas estruturas auxiliares e faz a soma dos campos das
 *  suas unidades e total gasto.
 *
 *  @param acc        Acumulador que irá conter o sumatório das unidades e do
 *                    total gasto num produto.
 *  @param new_value  Estrutura auxiliar a acumular.
 *  @return Void.
 */
static void addUnitsAndClients(void *acc, const void *new_value)
{
	struct aux_queries *aux = (struct aux_queries*) new_value;

	((struct aux_queries*) acc)->units += aux->units;
	((struct aux_queries*) acc)->clients++;
	((struct aux_queries*) acc)->spent += aux->spent;
}


/**
 *  Recebe uma venda e adiona o produto e as unidades desta à estrutura
 *  auxiliar das queries.
 *  Adiciona a estrutura auxiliar das queries a uma árvores auxiliar para
 *  efetuar a sua ordenação.
 *
 *  @param a   Estrutura de uma venda.
 *  @param acc Acumulador que ira guardar os campos da venda.
 *  @return Void.
 */
static void addMostSold(const void *a, void *acc)
{
	Sale s = (Sale) a;
	struct aux_queries aux;

	aux.product = getProduct(s);
	aux.units = getUnits(s);
	aux.clients = 1;

	addWithCondBSTree((BSTree) acc, &aux, addUnitsAndClients);
}


/**
 *  Adiciona a uma estrutura auxiliar das queries o total gasto num produto.
 *
 *  @param a   Estrutura de uma venda.
 *  @param acc Estrutura auxliar das queries que irá somar o total gasto.
 *  @return Void.
 */
static void addMostSpent(const void *a, void *acc)
{
	Sale s = (Sale) a;
	struct aux_queries aux;

	aux.product = getProduct(s);
	aux.spent = getUnits(s) * getPrice(s);

	addWithCondBSTree((BSTree) acc, &aux, addUnitsAndClients);
}


/**
 *  Sub menu da query 11.
 *  Pede ao utilizador um código de cliente.
 *
 *  @param client Guarda o valor do cliente.
 *  @return void.
 */
static void query_11_subMenu(char *client)
{
	system(CLEAR_COMMAND);

	printf("Introduza um cliente: ");

	my_getline();
	strcpy(client, buffer);
}


/**
 *  @Query 11
 *  Função principal de Query 11.
 *  A partir de um código de cliente, apresenta ao utilizador os 3 códigos de
 *  produto em que este gastou mais dinheiro.
 *
 * @return Void.
 */
static void query_11(void)
{
	unsigned int i = 0;

	char client[SIZE] = ""; 	/*Buffer que vai guarda o código do cliente a procurar.*/

	/*
	 *Variável que guarda a diferença de tempo desde o início até ao fim da
	 *execução da query.
	 */
	double diff = 0;
	clock_t begin = 0;
	clock_t end = 0;


	/*Declaração de árvores BSTree auxiliares.
	 *A aux_product está ordenada por código de produto.
	 *A aux_field está ordenada por unidades de produto compradas.
	 */

	BSTree aux_product = NULL;
	BSTree aux_field = NULL;


	Iterator aux_iterator = NULL; 	/*Iterador que vai apresentar os resultados.*/

	/*Criação de árvores BSTree auxiliares.*/

	aux_product = createBSTree(sizeof(struct aux_queries), cmpProduct,
	                           printQ11);

	aux_field = createBSTree(sizeof(struct aux_queries), cmpSpent,
	                         printQ11);

	/*Chamada da função que pede ao utilizador o parâmetro de procura.*/

	query_11_subMenu(client);

	begin = clock(); /*Início do relógio.*/

	/* Para cada filial, chama a função mostSpentByClient.
 	 * Procura pela árvore BSTMap o nó em que o resultado da comparação desse com
 	 * o cliente introduzido, dê igual.
	 * Quando encontrar esse nó, percorre a BSTree apontada por esse nó e a cada
	 * uma das vendas que lá existe, aplica-se a addMostSpent que somaesse nó da aux_product as unidades
	 * da outra venda.
	 * No fim tem-se em aux_product uma BSTree com todas as unidades de cada produto,
	 * contudo ordenado por código de produto.
	 */



	 /* Para cada uma das filiais, procura-se pela árvore BSTMap (que está ordenada
 	  * por códigos de clientes).
 	  * Quando se encontrar o nó com o cliente pretendido, vai-se à BSTree apontada
 	  * por esse nó e a cada uma das vendas que lá existe, aplica-se a addProductBSTree,
 	  * que vai adicionar à aux_product os produtos com o total faturado com esse produto.
 	  * Se por acaso se quiser adicionar a esta BSTree um produto que lá exista,
 	  * é aplicada a função addUnitsAndClients que soma a esse nó da aux_product os totais
	  * faturado.
 	  * No fim tem-se em aux_product uma BSTree com o total faturado de cada produto,
 	  * contudo ordenado por código de produto.
 	  */
	for(; i < BRANCHES; i++) {
		mostSpentByClient(branch_vec[i], client, aux_product, addMostSpent);
	}


	/* Como aux_product está ordenado por código de produto, aplica-se-lhe um
 	 *foldBSTree em que a função é addToFieldBSTree. Esta função passa todos os
 	 * nós de uma árvore (aux_product) para outra árvore (aux_field), sendo que
 	 * esta última faz a ordenadação por total faturado.
 	 */

	foldBSTree(aux_product, aux_field, addToFieldBSTree);


	/*
	 * toIteratorInOrderBSTree converte a BSTree aux_field num iterador, devolvendo
	 * no final o número de elemntos no iterador.
	 * Os elementos estão por ordem decrescente.
	 */

	aux_iterator = toIteratorInOrderBSTree(aux_field);


	/*
	 * O relógio termina antes da apresentação dos resultados, mas antes é
	 * escrito no ecrã o tempo decorrido desde o início da query.
	 */


	end = clock();
	diff = ((double) (end - begin)) / CLOCKS_PER_SEC;
	printf("Resultado obtido em: %.5f s\n", diff);

	/*Apresentam-se os resultados.*/

	if (aux_iterator != NULL && getSizeIterator(aux_iterator) != 0) {

		for (i = 0; i < BRANCHES; i++) {
			printCurrentIterator(aux_iterator);

			if (hasNextIterator(aux_iterator) == true) {
				nextIterator(aux_iterator);
			}
			else {
				break;
			}
		}
	}
	else {
		/*Caso o cliente não tenha feito nenhuma compra.*/
		printf("O cliente %s não comprou!\n", client);
	}

	/*No fim liberta-se a memória ocupada pelas BST auxiliares e pelo iterador auxiliar.*/

	destroyBSTree(aux_product);
	destroyBSTree(aux_field);
	destroyIterator(aux_iterator);
}

/*****************************************************************************
 * END QUERY 11                                                              *
 *****************************************************************************/

/*****************************************************************************
 * BEGIN QUERY 12                                                            *
 *****************************************************************************/


/* Função auxiliar da query 12.
 * Esta função é enviada como parâmetro do foldClients.
 * Recebe um código de cliente e vai a cada módulo de filial verificar se ele
 * realizou alguma compra durante o ano naquela filial.
 * Caso não tenha feito compras, incrementa o contador das filiais em que esse
 * cliente não fez compras.
 * No fim, se este número de filiais for igual ao número total de filiais,
 * o contador de clientes que não fizeram compras (que foi passado como parâmetro),
 * é incrementado.
 *
 * @param client Código do cliente a procurar.
 * @param acc Acumulador dos clientes que não fizeram compras.
 * @return Void.
 */
static void clientNotBuying(const void *client, void *acc)
{
	unsigned int i = 0;
	unsigned int counter = 0;

	for (;i < BRANCHES; i++) {
		if(existClientInBranch(branch_vec[i], (char*) client) == false) {
			counter++;
		}
	}

	if (counter == BRANCHES) {
		(*(unsigned int*) acc) += 1;
	}
}


/*
 *  @ Query 12
 *	Função principal da query 12.
 *
 * 	Apresenta no ecrã o número de produtos que não foram comprados e o número
 *  de clientes que não fizeram compras.
 *
 *  @return Void
 */
static void query_12(void)
{
	unsigned int counter = 0; /*Número de clientes que não fizeram compras.*/
	double diff = 0;          /*Variável que conta o tempo que a query demorou a ser
				   *executada.*/
	clock_t begin = 0;
	clock_t end = 0;

	system(CLEAR_COMMAND);

	begin = clock(); /*Inicialização do relógio.*/


	/*Aplica um fold a todos os clientes no módulo dos clientes.
	 *A função recebe um acumulador para o número de clientes e aplica uma função
	 *(clientNotBuying) a todos os nós da BSTree dos clientes.
	 *A função clientNotBuying conta em quantas filiais o cliente não comprou.
	 *Se o número de filiais em que não comprou for igual ao número das filiais,
	 *então o contador dos clientes que não fizeram compras, que é passado como
	 *acumulador do foldClients, é incrementado.
	 */

	foldClients(clients, &counter, clientNotBuying);


	/*Fim do relógio e apresentação dos resultados.*/

	end = clock();
	diff = ((double) (end - begin)) / CLOCKS_PER_SEC;

	printf("Resultado obtido em: %.5f s\n\n", diff);
	printf("Produtos que não foram comprados %d\n", getNotSold(billing));
	printf("Clientes que nunca compraram %d\n", counter);
}

/*****************************************************************************
 * END QUERY 12                                                              *
 *****************************************************************************/


/*****************************************************************************
 * BEGIN INIT FUNCTIONS                                                      *
 *****************************************************************************/

/**
 *  Faz a impressão do menu principal no ecrã.
 *
 *  @return Void.
 */
static void printMenu(void)
{
	printf("*******************************************************************************\n\n");
	printf("> 1  - Ler ficheiros!\n");
	printf("> 2  - Listar Produtos/Códigos iniciados por uma dada sequência.\n");
	printf("> 3  - Determinar número de Vendas e total Faturado de um Produto num dado Mês.\n");
	printf("> 4  - Listar Produtos que não foram comprados.\n");
	printf("> 5  - Apresentar número total de Produtos comprados por um Cliente Mês a Mês.\n");
	printf("> 6  - Apresentar Vendas registadas entre um intervalo de Meses.\n");
	printf("> 7  - Listar Clientes que compraram em todas as Filiais.\n");
	printf("> 8  - Listar Clientes que compraram um dado Produto numa Filial.\n");
	printf("> 9  - Listar Produtos mais comprados por um Cliente num dado Mês.\n");
	printf("> 10 - Listar os N Produtos mais Vendidos num Ano!\n");
	printf("> 11 - Apresentar os 3 Produtos que um Cliente mais gastou.\n");
	printf("> 12 - Apresentar o número de Clientes que não compraram e Produtos não comprados.\n");
	printf("> q  - Sair.\n");
}


/**
 *  Pede ao utilizador como tratar dos ficheiros de clientes, produtos
 *  e de vendas. O utilizador pode introduzir cada um destes manualmente
 *  ou os ficheiros podem ser carregados com os valores por defeito.
 *  Os ficheiros por defeito são os seguintes:
 *  	- Clientes.txt
 *  	- Produtos.txt
 *  	- Vendas_1M.txt
 *
 *  @return Devolve 0 se houve leitura de ficheiros ou 1 se o utilizador
 *          não pretendeu ler ficheiros.
 */
static unsigned int init_program(void)
{
	int option = 0;
	unsigned int begin = 0;

	/* Limpa o ecrã. */

	system(CLEAR_COMMAND);

	printf("******** Leitura de ficheiros *******\n");
	printf("Pretende:\n");
	printf("1 - Introduzir os nomes dos ficheiros.\n");
	printf("2 - Assumir por omissão.\n");
	printf("q - Sair.\n");
	printf("Opção > ");

	while(1) {

		/* Lê uma linha do teclado. */

		my_getline();

		/* Guarda o valor dessa linha como um inteiro. */

		option = atoi(buffer);

		if(option == 1 || option == 2) {

			/* Se for um valor inteiro compreendido entre 1 e 2 chama a
			 * query_1 que trata da leitura dos ficheiros. */

			query_1(option);
			printf("%E\n", totalFact);
			break;
		}
		else if (strcmp(buffer, "q") == 0) {

			/* Sai do menu de leitura de ficheiros. */

			begin = 1;
			break;
		}
		else {
			printf("Opção inválida!\n");
			printf("Opção > ");
		}
	}

	return begin;
}


/**
 *  Menu principal de gereVendas. Mostra todas as opções de geraVendas
 *  ao utilizador e pede ao mesmo para introduzir uma opção válida.
 *
 *  @param i  Flag que é responsável por limpar o ecrã.
 *  @return Void.
 */
static void menu(const unsigned int i)
{
	int option = 0;         /* Valor da opção. */

	if(i == 0) {

		/* Limpa o ecrã. */

		system(CLEAR_COMMAND);
	}


	/* Mostra as opções do menu principal. */

	printMenu();

	while(1) {

		/* Pede ao utilizador uma opção.
		 * Valores entre 1 e 12 selecionam as queries 1 a 12 respetivamente.
		 * O valor q termina o programa. */

		printf("Opção > ");
		my_getline();

		if(strcmp(buffer, "q") == 0) {
			printf("A sair do programa.\n");
			destroyComponents();
			break;
		}
		else {
			option = atoi(buffer);

			switch(option) {
				case 1 :
					init_program();
					printMenu();
					break;
				case 2 :
					query_2();
					printMenu();
					break;
				case 3 :
					query_3();
					printMenu();
					break;
				case 4 :
					query_4();
					printMenu();
					break;
				case 5 :
					query_5();
					printMenu();
					break;
				case 6 :
					query_6();
					printMenu();
					break;
				case 7 :
					query_7();
					printMenu();
					break;
				case 8 :
					query_8();
					printMenu();
					break;
				case 9 :
					query_9();
					printMenu();
					break;
				case 10 :
					query_10();
					printMenu();
					break;
				case 11 :
					query_11();
					printMenu();
					break;
				case 12 :
					query_12();
					printMenu();
					break;
				default :
					printf("Opção inválida!\n");
					printf("Opção > ");
			}
		}
	}
}

/*****************************************************************************
 * END INIT FUNCTIONS                                                        *
 *****************************************************************************/


/*****************************************************************************
 * MAIN                                                                      *
 *****************************************************************************/

/**
 *  Main do programa.
 */
int main(void)
{

	/* Inicia o buffer para a leitura do teclado. */
	unsigned int begin = 0;
	totalFact = 0;
	buffer = malloc(SIZE + 1);

	/* Cria as estruturas para guardar os dados do programa.
	 * Faz a leitura dos ficheiros. */

	begin = init_program();

	/* Chama o menu principal do program .*/

	if (begin == 0) {
		menu(1);
	}

	/* Liberta o buffer para a leitura do teclado. */

	free(buffer);
	buffer = NULL;

  return 0;
}
