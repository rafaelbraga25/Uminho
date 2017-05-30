/**
 *  @file catalogoProdutos.h
 *  @brief Protótipos das funções do catálogo de produtos.
 *
 *  Implementação de um array de árvores binárias de procura para o catálogo
 *  de códigos de produtos. O array tem 26 posições. Cada posição
 *  corresponde à diferença entre o valor da 1ª letra do código de produto e
 *  a letra 'A', em ASCII.
 *  	NOTA: A posição 0 do array apenas conterá códigos de produto começados
 *  	      pela letra 'A'.
 *
 *  Deve ser fornecida uma função que imprima um elemento da árvore, ou seja,
 *  um código de produto.
 *
 *  @author Carlos Pereira - A61887
 *  @author Diogo Silva    - A76407
 *  @author Rafael Braga   - A61799
 *
 *  @bug ?
 *  @version 3.1
 */

#ifndef catalogoProdutos_h
	#define catalogoProdutos_h

	#include <stdbool.h>


	typedef char* ProductCode;               /* Tipo de dados armazenados -
	                                          * Código de um produto. */
	typedef struct productCtlg* ProductCtlg; /* Array de árvores binárias -
	                                          * Catálogo de produtos.*/

	typedef void (*printProd)(const void*);  /* Função para realizar a impressão
	                                          * de um código de produto. */


	/**
	 *  @brief Cria e inicializa o catálogo de produtos.
	 *
	 *  O catálogo de produtos corresponde a vector com 26 posições. Cada posição
	 *  corresponde à diferença entre o valor da 1ª letra do código de
	 *  produto e a letra 'A', em ASCII. Cada posição deste array contém
	 *  uma BSTree de códigos de produto que começam pela mesma letra do
	 *  alfabeto.
	 *  Aloca espaço para a raiz da árvore binária. Guarda a informação
	 *  da função que faz a impressão de um elemento no ecrã, como também cria um
	 *  array com 26 posições.
	 *
	 *  A árvore armazena os códigos alfabéticamente maiores à direita e os
	 *  menores à esquerda.
	 *
	 *  @param print Função para realizar a impressão de um código de produto.
	 *  @return Apontador para o catálogo dos produtos.
	 */
	ProductCtlg createProductCtlg(printProd print);


	/** @brief Liberta a memória ocupada pelo catálogo.
	 *
	 *  Faz o free para cada BSTree do array. No final, liberta a memória
	 *  do catálogo de produtos.
	 *  Se o catálogo for nulo, a função não tem efeito.
	 *
	 *  @param catalog Apontador para o catálogo.
	 *  @return Void.
	 */
	void destroyProductCtlg(ProductCtlg catalog);


	/**
	 *  Devolve o número de páginas a ser impressas.
	 *
	 *  @param catalog Apontador para o catálogo.
	 *  @return Número total de páginas.
	 */
	unsigned int getNumProductPages(const ProductCtlg catalog);


	/**
	 *  Devolve o número de códigos de produto por página.
	 *
	 *  @param catalog Apontador para o catálogo.
	 *  @return Tamanho de uma página de códigos de produto.
	 */
	unsigned int getProductPageSize(const ProductCtlg catalog);


	/**
	 *  Modifica o número de códigos de produto a serem impressos por página.
	 *
	 *  @param catalog   Apontador para o catálogo.
	 *  @param page_size Novo tamanho da página.
	 *  @return Void.
	 */
	void setProductPageSize(const ProductCtlg catalog,
	                        const unsigned int page_size);


	/**
	 *  @brief Adiciona um produto ao catálogo de produtos.
	 *
	 *  Se o catálogo já tiver sido criado e inicializado, adiciona um
	 *  código de produto. O produto é adicionado por ordem alfabética.
	 *
	 *  @param catalog Apontador para o catálogo de produtos.
	 *  @param code    Produto a adicionar.
	 *  @return Devolve o apontador para o catálogo.
	*/
	ProductCtlg addProduct(ProductCtlg catalog, const ProductCode code);


	/**
	 *  @brief Verifica se existe um dado produto no catálogo.
	 *
	 *  Procura por code no catálogo, caso este tenha sido previamente
	 *  inicializado.
	 *
	 *  @param catalog Apontador para o catálogo.
	 *  @param code    Produto a procurar.
	 *  @return Retorna true caso o produto exista no catálogo ou false
	 *          caso contrário.
	 */
	bool containsProduct(const ProductCtlg catalog, const char *code);


	/**
	 *  @brief Devolve o número de códigos de produto iniciados por uma dada
	 *         cadeia de caracteres.
	 *
	 *  Caso o catálogo e o array de BSTree's estejam inicializados, procura
	 *  nesse array por produtos cujo código seja iniciado pela sequência x.
	 *  Esta função cria um iterator com todas as ocorrências de x
	 *  no catálogo de produtos.
	 *
	 *  @param catalog Apontador para o catálogo.
	 *  @param x       Cadeia de caracteres a procurar no catálogo.
	 *  @return Retorna o número de ocorrências de x no catálogo de produtos.
	 *          O iterador é guardado em catalog.
	 */
	unsigned int productsBeginningWithX(const ProductCtlg catalog,
	                                    const ProductCode x);


	/**
	 *  @brief Navega para uma dada página da última pesquisa no catálogo
	 *         de produtos.
	 *
	 *  Vai para uma página x conforme o número de página recebido, isto é, caso
	 *  este não ultrapasse o número total de páginas. Em caso de sucesso toda a
	 *  página é impressa, sendo esta impressão realizada conforme a função print
	 *  recebida.
	 *  O número de códigos de produto impressos por página pode ser alterado
	 *  através da função setProductPageSize. O número padrão de produtos
	 *  impressos por página é 30.
	 *
	 *  @param catalog  Apontador para o catálogo.
	 *  @param num_page Página que se pretentde realizar a impressão.
	 *  @return Devolve o número de códigos de produto impressos nesta página.
	 *          Caso a página não seja válida devolve 0.
	 */
	unsigned int goToProductPage(const ProductCtlg catalog,
	                             const unsigned int num_page);


	/**
	 *  @brief Realiza a impressão da próxima página de códigos de produto
	 *         relativa à última pesquisa realizada neste catálogo.
	 *
	 *  Vai para a próxima página do catálogo caso esta já não seja a última
	 *  página. Em caso de sucesso toda a página é impressa, sendo esta impressão
	 *  realizada conforme a função print recebida.
	 *  O número de códigos de produto impressos por página pode ser alterado
	 *  através da função setProductPageSize. O número padrão de produtos
	 *  impressos por página é 30.
	 *
	 *  @param catalog Apontador para o catálogo.
	 *  @return Devolve o número de códigos de produto impressos nesta página.
	 *          Caso a página não seja válida devolve 0.
	 */
	unsigned int nextProductPage(const ProductCtlg catalog);


	/**
	 *  @brief Realiza a impressão da página anterior de códigos de produto
	 *         relativa à última pesquisa realizada neste catálogo.
	 *
	 *  Vai para a página anterior do catálogo, caso esta já não seja a primeira
	 *  página. Em caso de sucesso toda a página é impressa, sendo esta impressão
	 *  realizada conforme a função print recebida.
	 *  O número de códigos de produto impressos por página pode ser alterado
	 *  através da função setProductPageSize. O número padrão de produtos
	 *  impressos por página é 30.
	 *
	 *  @param catalog Apontador para o catálogo.
	 *  @return Devolve o número de códigos de produto impressos nesta página.
	 *          Caso a página não seja válida devolve 0.
	 */
	unsigned int previousProductPage(const ProductCtlg catalog);


	/**
	 *  @brief Aplica uma função a todos os códigos de produtos presentes no
	 *         catálogo.
	 *
	 *  Recebe uma função f a ser aplicada a todos os códigos de produto.
	 *  A função pode alterar o conteúdo dos códigos presentes no catálogo, mas
	 *  não deve alterar os seus tipos.
	 *
	 *  @param catalof Apontador para o catálogo.
	 *  @param f       Função para realizar uma certa operação sobre um código
	 *                 de produto.
	 *  @return Void. O resultado é guardado em catalog.
	 */
	void mapProductCtlg(const ProductCtlg catalog, void(*f)(void *product));

#endif
