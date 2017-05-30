/**
 *  @file catalogoClientes.h
 *  @brief Protótipos das funções do catálogo de clientes.
 *
 *  Implementação de um array de árvores binárias de procura para o catálogo
 *  de códigos de clientes. O array tem 26 posições. Cada posição
 *  corresponde à diferença entre o valor da 1ª letra do código de cliente e
 *  a letra 'A', em ASCII.
 *  	NOTA: A posição 0 do array apenas conterá códigos de cliente começados
 *  	      pela letra 'A'.
 *
 *  Deve ser fornecida uma função que imprima um elemento da árvore, ou seja,
 *  um código de cliente.
 *
 *  @author Carlos Pereira - A61887
 *  @author Diogo Silva    - A76407
 *  @author Rafael Braga   - A61799
 *
 *  @bug ?
 *  @version 3.1
 */

#ifndef catalogoClientes_h
	#define catalogoClientes_h

	#include <stdbool.h>


	typedef char* ClientCode;                 /* Tipo de dados armazenados -
	                                           * Código de um cliente. */
	typedef struct clientCtlg* ClientCtlg;    /* Array de árvores binárias -
	                                           * Catálogo de clientes.*/

	typedef void (*printClient)(const void*); /* Função para realizar a impressão
	                                           * de um código de cliente. */


	/**
	 *  @brief Cria e inicializa o catálogo de clientes.
	 *
	 *  O catálogo de clientes corresponde a um vector com 26 posições.
	 *  Cada posição corresponde à diferença entre o valor da 1ª letra do código
	 *  de cliente e a letra 'A', em ASCII. Cada posição deste array contém
	 *  uma BSTree de códigos de cliente que começam pela mesma letra do
	 *  alfabeto.
	 *  Aloca espaço para a raiz da árvore binária. Guarda a informação
	 *  da função que faz a impressão de um elemento no ecrã, como também cria um
	 *  array com 26 posições.
	 *
	 *  A árvore armazena os códigos alfabéticamente maiores à direita e os
	 *  menores à esquerda.
	 *
	 *  @param print Função para realizar a impressão de um código de cliente.
	 *  @return Apontador para o catálogo dos clientes.
	 */
	ClientCtlg createClientCtlg(printClient print);


	/** @brief Liberta a memória ocupada pelo catálogo.
	 *
	 *  Faz o free para cada BSTree do array. No final, liberta a memória
	 *  do catálogo de clientes.
	 *  Se o catálogo for nulo, a função não tem efeito.
	 *
	 *  @param catalog Apontador para o catálogo.
	 */
	void destroyClientCtlg(ClientCtlg catalog);


	/**
	 *  Devolve o número de páginas a ser impressas.
	 *
	 *  @param catalog Apontador para o catálogo.
	 *  @return Número total de páginas.
	 */
	unsigned int getNumClientPages(const ClientCtlg catalog);


	/**
	 *  Devolve o número de códigos de cliente por página.
	 *
	 *  @param catalog Apontador para o catálogo.
	 *  @return Tamanho de uma página de códigos de cliente.
	 */
	unsigned int getClientPageSize(const ClientCtlg catalog);


	/**
	 *  Modifica o número de códigos de cliente a serem impressos por página.
	 *
	 *  @param catalog   Apontador para o catálogo.
	 *  @param page_size Novo tamanho da página.
	 *  @return Void. O resultado é guardado em catalog.
	 */
	void setClientPageSize(const ClientCtlg catalog,
	                       const unsigned int page_size);


	/**
	 *  @brief Adiciona um cliente ao catálogo de clientes.
	 *
	 *  Se o catálogo já tiver sido criado e inicializado, adiciona um
	 *  código de cliente. O cliente é adicionado por ordem alfabética.
	 *
	 *  @param catalog Apontador para o catálogo de clientes.
	 *  @param code    Cliente a adicionar.
	 *  @return Devolve o apontador para o catálogo.
	*/
	ClientCtlg addClient(ClientCtlg catalog, const ClientCode code);


	/**
	 *  @brief Verifica se existe um dado cliente no catálogo.
	 *
	 *  Procura por code no catálogo, caso este tenha sido previamente
	 *  inicializado.
	 *
	 *  @param catalog Apontador para o catálogo.
	 *  @param code    Cliente a procurar.
	 *  @return Retorna true caso o cliente exista no catálogo ou false
	 *          caso contrário.
	 */
	bool containsClient(const ClientCtlg catalog, const char *code);


	/**
	 *  @brief Devolve o número de códigos de cliente iniciados por uma dada
	 *         cadeia de caracteres.
	 *
	 *  Caso o catálogo e o array de BSTree's estejam inicializados, procura
	 *  nesse array por clientes cujo código seja iniciado pela sequência x.
	 *  Esta função cria um iterator com todas as ocorrências de x
	 *  no catálogo de clientes.
	 *
	 *  @param catalog Apontador para o catálogo.
	 *  @param x       Cadeia de caracteres a procurar no catálogo.
	 *  @return Retorna o número de ocorrências de x no catálogo de clientes.
	 *          O iterador é guardado em catalog.
	 */
	unsigned int clientsBeginningWithX(const ClientCtlg catalog,
	                                   const ClientCode x);


	/**
	 *  @brief Guarda num iterador todos os clientes que satisfaçam f.
	 *
	 *  Aplica uma função boolena a todos os clientes presentes no
	 *  catálogo. Todos os clientes que satisfaçam a função recebida são
	 *  guardados num iterador.
	 *
	 *  @param catalog Apontador para o catálogo.
	 *  @param f       Função que recebe como parâmetro um código de cliente.
	 *                 Se a função retornar true o cliente é adicionado a um
	 *                 um iterador do catálogo.
	 *  @return Retorna o número de clientes adicionados ao iterador.
	 */
	unsigned int filterClients(const ClientCtlg catalog, bool (*f)(const void*));


	/**
	 *  @brief Navega para uma dada página da última pesquisa no catálogo
	 *         de clientes.
	 *
	 *  Vai para uma página x conforme o número de página recebido, isto é, caso
	 *  este não ultrapasse o número total de páginas. Em caso de sucesso toda a
	 *  página é impressa, sendo esta impressão realizada conforme a função de
	 *  print recebida.
	 *  O número de códigos de cliente impressos por página pode ser alterado
	 *  através da função setClientPageSize. O número padrão de clientes
	 *  impressos por página é 30.
	 *
	 *  @param catalog  Apontador para o catálogo.
	 *  @param num_page Página que se pretende imprimir.
	 *  @return Devolve o número de códigos de cliente impressos nesta página.
	 *          Caso a página não seja válida devolve 0.
	 */
	unsigned int goToClientPage(const ClientCtlg catalog,
	                            const unsigned int num_page);


	/**
	 *  @brief Realiza a impressão da próxima página de códigos de cliente
	 *         relativa à última pesquisa realizada neste catálogo.
	 *
	 *  Vai para a próxima página do catálogo caso esta já não seja a última
	 *  página. Em caso de sucesso toda a página é impressa, sendo esta impressão
	 *  realizada conforme a função print recebida.
	 *  O número de códigos de cliente impressos por página pode ser alterado
	 *  através da função setClientPageSize. O número padrão de clientes
	 *  impressos por página é 30.
	 *
	 *  @param catalog Apontador para o catálogo.
	 *  @return Devolve o número de códigos de cliente impressos nesta página.
	 *          Caso a página não seja válida devolve 0.
	 */
	unsigned int nextClientPage(const ClientCtlg catalog);


	/**
	 *  @brief Realiza a impressão da página anterior de códigos de cliente
	 *         relativa à última pesquisa realizada neste catálogo.
	 *
	 *  Vai para a página anterior do catálogo, caso esta já não seja a primeira
	 *  página. Em caso de sucesso toda a página é impressa, sendo esta impressão
	 *  realizada conforme a função print recebida.
	 *  O número de códigos de cliente impressos por página pode ser alterado
	 *  através da função setClientPageSize. O número padrão de clientes
	 *  impressos por página é 30.
	 *
	 *  @param catalog Apontador para o catálogo.
	 *  @return Devolve o número de códigos de cliente impressos nesta página.
	 *          Caso a página não seja válida devolve 0.
	 */
	unsigned int previousClientPage(const ClientCtlg catalog);


	/**
	 *  @brief Constrói uma qualquer estrutura de dados a partir de todos os
	 *         códigos de cliente presentes no catálogo.
	 *
	 *  A função f recebida irá receber como parâmetro um código de cliente e
	 *  um acumulador, podendo acrescentar-se algo a este.
	 *  O acumulador deve ser previamente inicializado.
	 *
	 *  @param catalog Apontador para o catálogo.
	 *  @param acc     Acumulador onde se prentende guardar uma qualquer
	 *                 estrutura de dados.
	 *  @param f       Função que recebe como parâmetros um elemento da árvore e
	 *                 um acumulador, podendo-se acrescentar algo ao mesmo.
	 *  @return Void. O resultado é guardado em acc.
	 */
	void foldClients(const ClientCtlg catalog, void *acc,
	                 void (*f)(const void *value, void *acc));

#endif
