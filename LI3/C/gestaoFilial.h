/**
 *  @file gestaoFilial.h
 *  @brief Protótipos das funções referentes à gestão de uma filial.
 *
 *  Organiza as vendas de uma filial por mês. Os dados são guardados num
 *  array de 12 (por defeito) posições que correspondem aos meses em que foram
 *  efetuadas vendas. Cada uma destas posições contém uma BSTMap que está
 *  organizada por clientes. Cada valor correspodente à chave cliente contém
 *  o registo de uma compra desse cliente. O registo de compra é constituído
 *  por um código de produto, pelas unidades e pelo preço desse produto.
 *
 *  @author Carlos Pereira - A61887
 *  @author Diogo Silva    - A76407
 *  @author Rafael Braga   - A61799
 *
 *  @bug ?
 *  @version 4.1
 */

#ifndef gestaoFilial_h

	#define gestaoFilial_h

	#include <stdbool.h>

	typedef struct sale* Sale;                    /* Campos de uma venda:
	                                               * 	- Codigo de produto.
	                                               * 	- Unidades.
	                                               * 	- Preço.
	                                               * 	- Tipo de venda. */
	typedef struct branchCtlg* BranchCtlg;        /* Estrutura de um catálogo
	                                               * de vendas de uma filial. */
	typedef void (*printSaleCode)(const void*);   /* Função para a impressão de
	                                               * um código de cliente. */
	typedef void (*printSaleBranch)(const void*); /* Função para a impressão de
	                                               * todos os campos de uma
	                                               * venda. */


	/**
	 *  @brief Criação do catálogo de vendas.
	 *
	 * Recebe toda a informação necessária para a criação do catálogo de vendas.
	 * Como já existe o módulo de BSTMap, chama-se a função createBSTMap de
	 * maneira a criar uma BSTMap, passando-lhe os parâmetros necessários.
	 * O processo de criação de BSTMap é feito as vezes que forem enviadas
	 * como parâmetro.
	 *
	 *  @param printSC  Função para fazer a impressão de um código de cliente.
	 *  @param printS   Função para fazer a impressão de uma venda.
	 *  @param size     Número de meses da gestão de vendas de uma filial.
	 *  @return Devolve o apontador para o catálogo de vendas de uma filial.
	 */
	BranchCtlg createBranchCtlg(printSaleCode printSC,
                              printSaleBranch printS,
	                            const unsigned int size);



	/**
	 *  @brief Construtor por defeito da gestão de uma filial.
	 *
	 *  Inicia todas as estruturas referentes à gestão de uma filial.
	 *  O número de meses da gestão será inicializado a 12.
	 *
	 *  @param printSC  Função para a impressão de um código de cliente.
	 *  @param printS   Função para a impressão de uma venda.
	 *  @return Devolve um apontador para o catálogo de vendas de uma filial.
	 */
	BranchCtlg defaultCreateBranchCtlg(printSaleCode printSC,
	                                   printSaleBranch printS);


	/**
	 *  @brief Destruição do catálogo de vendas.
	 *
	 *  Liberta a memória ocupada pelo catálogo de vendas.
	 *
	 *  @param catalog Apontador para a estrutura do catálogo de vendas.
	 *  @return Void
	 */
	void destroyBranchCtlg(BranchCtlg catalog);


	/**
	 *  Devolve o código produto de uma venda.
	 *
	 *  @param sale Venda.
	 *  @return Código produto de uma venda.
	 */
	char* getProduct(const Sale sale);


	/**
	*  Devolve o preço de uma venda.
	*
	*  @param sale Venda.
	*  @return Preço de uma venda.
	*/
	double getPrice(const Sale sale);


	/**
	 *  Devolve as unidades de uma venda.
	 *
	 *  @param sale Venda.
	 *  @return Unidades da venda.
	 */
	unsigned int getUnits(const Sale sale);


	/**
	 *  Devolve o tipo de uma venda.
	 *
	 *  @param sale Venda.
	 *  @return Tipo da venda.
	 */
	char getType(const Sale sale);


	/**
	 *  Calcula o número total de produtos comprados por um cliente num dado
	 *  mês.
	 *
	 *  @param catalog Apontador para o catálogo de vendas.
	 *  @param client  Código de um cliente a procurar.
	 *  @param month   Mês a procurar.
	 *  @return Número total de produtos comprados pelo cliente.
	 */
	unsigned int getTotalProducts(const BranchCtlg catalog, const char *client,
	                              unsigned int month);


	/**
	 *  @brief Devolve o número de elementos na página de códigos de cliente
	 *         da filial.
	 *
	 *  @param catalog Apontador para o catálogo.
	 *  @return catalog->page_size caso o apontador para o catálogo da filial
	 *          exista DEFAULT_PAGE_SIZE caso contrário.
	 */
	unsigned int getBranchPageSize(const BranchCtlg catalog);


	/**
	 *  @brief Devolve o número de páginas da pesquisa de cada tipo de venda.
	 *
	 *  Começa por testar se o catálogo foi previamente inicializado, bem como
	 *  o iterador de cada tipo de venda. Caso estas condições se verifiquem,
	 *  efectuam-se os cálculos para determinar o número de páginas.
	 *
	 *  @param catalog  Apontador para o catálogo da filial.
	 *  @param mode     Variável que indica o tipo de venda.
	 *  @return Número de páginas do iterador.
	 */
	unsigned int getNumModePages(const BranchCtlg catalog, const char mode);


	/**
	 *  @brief Modifica o número de elementos numa página de códigos de cliente
	 *         caso o catálogo tenha sido previamente inicializado.
	 *
	 *  @param catalog    Apontador para o catálogo da filial.
	 *  @param page_size  Novo tamanho de página de códigos de cliente.
	 *  @return Void.
	 */
	void setSalePageSize(const BranchCtlg catalog, const unsigned int page_size);


	/**
	 *  @brief Adiciona uma venda a cada array de árvores BSTMap.
	 *
	 *  Todos os campos da venda são enviados para a função como parâmetros.
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
	                   const unsigned int units, const char type, char *client,
	                   unsigned int month);


	/**
	 *  @brief Procura por um código de cliente na filial.
	 *
	 *  Esta função vai a cada posição do array de árvores BSTMap procurar uma
	 *  chave que seja igual ao código de cliente fornecido. Caso encontre antes
	 *  de chegar ao fim do ciclo, o ciclo termina.
	 *
	 *  @param catalog  Apontador para o catálogo da filial.
	 *  @param client   Código de cliente a procurar.
	 *  @return false Se o cliente não existir na filial.
	 *          true Caso contrário
	 */
	bool existClientInBranch(const BranchCtlg catalog, const char *client);


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
	 *  @return Void. O resultado é devolvido em acc.
	 */
	void foldClientProductsInMonth(const BranchCtlg catalog, const char *client,
	                               unsigned int month, void *acc,
	                               void (*f)(const void *value, void *acc));


	/**
	 *  @brief Aplica uma função com acumulador a todos os nós das árvores BST a
	 *         serem apontadas por todos os nós das árvores BSTMap de todas as
	 *         posições do array ordenado por código de cliente na chave.
	 *
	 *  A partir da função f determinam-se os códigos de produto mais vendidos.
	 *
	 *  @param catalog  Apontador para o catálogo da filial.
	 *  @param client   Código de cliente a procurar.
	 *  @param acc      Acumulador da função a aplicar.
	 *  @param f        Função a aplicar.
	 *  @return Void. O resultado é guardado em acc.
	 */
	void mostSoldProducts(const BranchCtlg catalog, void *acc,
	                      void (*f)(const void *value, void *acc));


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
	 *  @return Void. O resultado é devolvido em acc.
	 */
	void mostSpentByClient(const BranchCtlg catalog, const char *client,
	                       void *acc, void (*f)(const void *v, void *acc));


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
	 *  @return Void. O resultado é devolvido em total_N e total_P.
	 */
	void clientsThatBought(const BranchCtlg catalog, const char *product,
	                       unsigned int *total_N, unsigned int *total_P);


	/**
	 *  @brief Passa para a página seguinte da pesquisa.
	 *
	 *  @param catalog  Apontador para o catálogo da filial.
	 *  @param mode     Variável que indica o tipo de venda.
	 *  @return Void.
	 */
	void nextModePage(const BranchCtlg catalog, const char mode);


	/**
	 *  @brief Vai diretamente para uma página da pesquisa.
	 *
	 *  @param catalog  Apontador para o catálogo da filial.
	 *  @param mode     Variável que indica o tipo de venda.
	 *  @param page     Página da pesquisa a ir.
	 *  @return Void.
	 */
	void goToModePage(const BranchCtlg catalog, const char mode,
	                  const unsigned int page);

#endif
