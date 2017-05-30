/**
 *  @file faturacao.c
 *  @brief Implementação de um módulo de facturação global de vendas.
 *
 *  Aqui constam todas as funções necessárias ao correto funcionamento deste
 *  módulo assim como estruturas auxiliares.
 *  A estrutura principal deste módulo é a GlobalBilled e é nessa que é
 *  armazenada toda a informação necessária para os cálculos principais e
 *  auxiliares.
 *
 *  @author Carlos Pereira - A61887
 *  @author Diogo Silva    - A76407
 *  @author Rafael Braga   - A61799
 *
 *  @bug ?
 *  @version 3.2
 */
#ifndef faturacaoGlobal_h
	#define faturacaoGlobal_h

	#include <stdbool.h>

	typedef char *ProductBill;
	typedef struct bill *Bill;
	typedef struct productUnitsClients *ProductUnitsClients;
	typedef struct globalBilled *GlobalBilled;

	typedef void (*printPBill)(const void*);
	typedef void (*printPrdctUntClnt)(const void*);
	typedef void (*printGBill)(const void*);

	/**
	 *  @brief Cria a estrutura principal da faturação, esta é do tipo
	 *  GlobalBilled.
	 *
	 *  É necessário fornecer as funções de impressão para as diversas estruturas.
	 *  Os argumentos para a alocação de espaço da matriz b_matrix são recebidos
	 *  nesta função.
	 *
	 *  @param printP       Função de impressão de uma key.
	 *  @param printB       Função de impressão de uma Bill
	 *  @param printPUC     Função de impressão de uma ProductUnitsClients.
	 *  @param months       Número de meses da faturação.
	 *  @param branches     Número de filiais da faturação.
	 *  @param product_size Tamanho de um código de produto.
	 *  @return Uma nova estrutura GlobalBilled.
	 */
	GlobalBilled createGlobalBilled(printPBill printP,
	                                printGBill printB,
	                                printPrdctUntClnt printPUC,
	                                const unsigned int months,
	                                const unsigned int branches,
	                                const unsigned int product_size);

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
	 *
	 */
	GlobalBilled defaultCreateGlobalBilled(printPBill printP,
	                                       printGBill printB,
	                                       printPrdctUntClnt printPUC);


	/**
	 *  @brief Destrói uma estrutura GlobalBilled.
	 *
	 *  O único argumento recebido é a estrutura a libertar, só efectua trabalho
	 *  se esta não for nula.
	 *
	 *  @param g Estrutura a destruir.
	 *  @return Void.
	*/
	void destroyGlobalBilled(GlobalBilled g);


	/**
	 *  @brief Devolve o campo de unidades de uma Bill.
	 *
	 *  Se a estrutura for nula, devolve 0.
	 *
	 *  @param bill Estrutura com os campos da faturação.
	 *  @return Número de unidades.
	 */
	unsigned int getUnitsBill(const Bill b);


	/**
	 *  @brief Devolve o campo de preço de um Bill.
	 *
	 *  Se a estrutura for nula, devolve -1.
	 *
	 *  @param bill Estrutura com os campos da faturação.
	 *  @return Preço unitário.
	 */
	double getPriceBill(const Bill b);


	/**
	 *  @brief Devolve o campo do tipo de um Bill.
	 *
	 *  Se a estrutura for nula, devolve '\0'.
	 *
	 *  @param bill Estrutura com os campos da faturação.
	 *  @return Tipo de venda.
	 */
	char getTypeBill(const Bill b);


	/**
	 *  @brief Devolve o campo produto de um ProductUnitsClients.
	 *
	 *  Se a estrutura for nula, devolve "".
	 *
	 *  @param bill Estrutura ProductUnitsClients.
	 *  @return Produto.
	 */
	char* getProductPUC(const ProductUnitsClients p);


	/**
	 *  @brief Devolve o campo produto de unidades de um ProductUnitsClients.
	 *
	 *  Se a estrutura for nula, devolve 0.
	 *
	 *  @param bill Estrutura ProductUnitsClients.
	 *  @return Unidades.
	 */
	unsigned int getUnitsPUC(const ProductUnitsClients p);


	/**
	 *  @brief Devolve o campo produto de número de clientes de um
	 *         ProductUnitsClients.
	 *
	 *  Se a estrutura for nula, devolve 0.
	 *
	 *  @param bill Estrutura ProductUnitsClients.
	 *  @return Número de clientes.
	 */
	unsigned int getClientsPUC(const ProductUnitsClients p);


	/**
	 *  @brief Devolve a quantidade de páginas para apresentar os produtos não
	 *         vendidos numa determinada filial.
	 *
	 *  Efectuamos um arredondamento por excesso caso existam casas decimais no
	 *  cálculo das páginas.
	 *
	 *  @param g      Estrutura que contém o iterador onde se pretende calcular o
	 *                número de páginas.
	 *  @param branch Filial do iterador correspondente.
	 *  @return Número de páginas.
	 */
	unsigned int getNotSoldInBranchPages(const GlobalBilled g,
	                                     const unsigned int branch);


	/**
	 *  @brief Devolve a quantidade de elementos a apresentar por página do
	 *  iterador not_sold duma estrutura GlobalBilled.
	 *
	 *
	 *  @param g      Estrutura que contém o iterador onde se pretende calcular o
	 *                número de elementos por página.
	 *  @return Número de páginas.
	 */
	unsigned int getNotSoldPageSize(const GlobalBilled g);


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
	unsigned int getNumNotSoldPages(const GlobalBilled g);


	/**
	 *  @brief Apresenta o número de produtos não vendidos em nenhuma das três
	 *         filiais.
	 *
	 *  Utiliza a função já previamente definida no módulo do iterador
	  * devolvendo o número de elementos que este apresenta..
	 *
	 *  @param g Estrutura GlobalBilled que contém o iterador.
	 *  @return Número de produtos não vendidos.
	 */
	unsigned int getNotSold(const GlobalBilled billing);


	/**
	 *  @brief Apresenta o número de produtos não vendidos numa nada filial.
	 *
	 *  Utiliza a função já previamente definida no módulo do iterador devolvendo
	 *  o tamanho deste.
	 *
	 *  @param g Estrutura GlobalBilled que contém o iterador.
	 *  @param branch      Filial onde é preciso saber quantos não foram vendidos.
	 *  @return Número de produtos não vendidos numa filial.
	 */
	unsigned int getNotSoldInBranch(const GlobalBilled g,
	                                const unsigned int branch);


	/**
	 *  @brief Devolve a quantidade de unidades vendidas num determinado mês de uma
	 *  estrutura GlobalBilled.
	 *
	 *  Caso o vetor total_units esteja nulo, não é efectuado trabalho.
	 *
	 *  @param g      Estrutura GlobalBilled.
	 *  @return Número de unidades de produtos vendidas num dado mês.
	 */
	unsigned int getTotalUnits(const GlobalBilled g, const unsigned int month);


	/**
	 *  @brief Devolve total facturado num determinado mês de uma estrutura
	 *  GlobalBilled.
	 *
	 *  Caso o vetor total_billed esteja nulo, não é efectuado trabalho.
	 *
	 *  @param g      Estrutura GlobalBilled.
	 *  @return Total faturado num dado mês.
	 */
	double getTotalBilled(const GlobalBilled g, const unsigned int month);


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
	void getNMostBought(const GlobalBilled g, const unsigned int n);


	/**
 	 *  @brief Adiciona uma nova factura a GlobalBilled fornecendo todos os
 	 *  pârametros necessários para atribuir aos campos de uma estrutura Bill.
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
	GlobalBilled addBill(GlobalBilled g, ProductBill product, const double price,
	                     const unsigned int units, const char type,
	                     const unsigned int month, const unsigned int branch);


	/**
	 *  @brief Adiciona um produto não comprado em nenhuma filial ao iterador
	 *  not_sold.
	 *
	 *  @param g       Estrutura GlobalBilled.
	 *  @param product Produto não comprado em nenhuma filial.
	 *  @return Apontador para a nova estrutura.
	 */
	GlobalBilled addNotSold(GlobalBilled g, ProductBill product);


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
	                                const unsigned int branch);


	/**
	 *  @brief Verifica se um dado produto foi comprado numa determinada filial.
	 *
	 *  @param g       Estrutura GlobalBilled.
	 *  @param product Produto que queremos saber se foi comprado em branch.
	 *  @param branch  Filial a verificar.
	 *  @return bool.
	 */
	bool productSoldInBranch(const GlobalBilled g, const ProductBill product,
	                         const unsigned int branch);



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
	                          const unsigned int month,
	                          const unsigned int branch,
	                          double *price_N, double *price_P,
	                          unsigned int *units_N, unsigned int *units_P);



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
	 *	    num_page não seja válida retorna 0.
	 */
	unsigned int goToNotSoldPage(const GlobalBilled g,
	                             const unsigned int num_page);


	/**
	 *  @brief Altera a posição de pesquisa do iterador para a página num_page
	 *  fornecida se esta for válida num iterador para uma filial fornecida.
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
	                             const unsigned int branch);


	/**
	 *  @brief Mostra a próxima página da última pesquisa no iterador de produtos
	 *  não vendidos de GlobalBilled.
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
	unsigned int nextNotSoldPage(const GlobalBilled g);


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
	void nextNotSoldInBranchPage(const GlobalBilled g, const unsigned int branch);


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
	unsigned int previousNotSoldPage(const GlobalBilled g);


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
	void resetAllSearches(const GlobalBilled g);


	/**
	 *  @brief Altera a posição de pesquisa do iterador de produtos mais comprados
	 *         numa determinada filial para a página num_page fornecida se esta for válida.
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
	                        const unsigned int branch);


	/**
	 *  @brief Mostra a próxima página da última pesquisa no iterador de produtos
	 *         mais comprados numa filial de GlobalBilled.
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
	void nextMostBoughtPage(const GlobalBilled g, const unsigned int branch);

#endif
