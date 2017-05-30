/**
 * @file xmlParser.h
 *
 * Módulo que efetua o parsing de um ficheiro xml usando como recurso
 * o parser tinyXml. O propósito deste módulo consiste na extração de
 * inúmeras operações em OpenGL do ficheiro xml recebido. O resultado
 * é devolvido num vetor de operações em OpenGL. Caso ocorra algum erro 
 * (sintaxe inválida de alguma operação (duplicação da tag models num group,
 * translates ou rotates no final de um group), o parsing é terminado e o
 * vetor devolvido será um vetor vazio. Pode-se verificar que tipo de erros
 * ocorreram ao se efetuar o parsing através da invocação da função 
 * getErrorString(). A string devolvida apresenta apenas uma representação 
 * textual do primeiro erro encontrado. A string errorString poderá também
 * conter eventuais warings de tentativas e erros de carregamento de um 
 * conjunto de modelos. Podem-se obter os respetivos valores do número total
 * de modelos lidos e do número total de modelos que não se conseguiram 
 * processar através das funções getNumModels() e getFailedModels().
 *
 * @author Carlos Pereira - A61887
 * @author João Barreira  - A73831
 * @author Rafael Braga   - A61799
 *
 * @version 12-04-2017
 */


#ifndef xmlParser_h
#define xmlParser_h


#include <string>
#include <vector>
#include "glOperation.h"


class XMLParser {
	class XMLParserImpl;  // Implementação da parte privada da classe XMLParser
	XMLParserImpl* pimpl; // Apontador para a parte privada

public:


	/**
	 * Construtor por defeito.
	 */
	XMLParser(void);


	/**
	 * Construtor por parâmetros.
	 *
	 * @param fileName Nome do ficheiro xml.
	 */
	XMLParser(std::string fileName);


	/**
	 * Construtor de cópia.
	 *
	 * @param x Objeto da classe XMLParser a copiar.
	 */
	XMLParser(const XMLParser& x);


	/**
	 * Devolve o número total de modelos lidos do ficheiro xml.
	 */
	size_t getNumModels(void);


	/**
	 * Devolve o número de modelos que não se conseguiu processar.
	 */
	size_t getFailedModels(void);


	/**
	 * Devolve um vetor com a lista de operações em OpenGL contidas no ficheiro
	 * xml. As operações são ordenadas conforme a ordem destas no ficheiro.
	 * Em caso de algum erro, o vetor devolvido é vazio.
	 */
	std::vector<GLOperation*> getGLOperations(void);


	/**
	 * Devolve uma representação textual de eventuais erros, ou warnings, do
	 * parsing do ficheiro xml, caso estes existam.
	 */
	std::string getErrorString(void);


	/**
	 * Destrutor da classe XMLParser.
	 */
	~XMLParser(void);
};


#endif 

