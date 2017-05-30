/**
 * @file xmlParser.h
 *
 * M�dulo que efetua o parsing de um ficheiro xml usando como recurso
 * o parser tinyXml. O prop�sito deste m�dulo consiste na extra��o de
 * in�meras opera��es em OpenGL do ficheiro xml recebido. O resultado
 * � devolvido num vetor de opera��es em OpenGL. Caso ocorra algum erro 
 * (sintaxe inv�lida de alguma opera��o (duplica��o da tag models num group,
 * translates ou rotates no final de um group), o parsing � terminado e o
 * vetor devolvido ser� um vetor vazio. Pode-se verificar que tipo de erros
 * ocorreram ao se efetuar o parsing atrav�s da invoca��o da fun��o 
 * getErrorString(). A string devolvida apresenta apenas uma representa��o 
 * textual do primeiro erro encontrado. A string errorString poder� tamb�m
 * conter eventuais warings de tentativas e erros de carregamento de um 
 * conjunto de modelos. Podem-se obter os respetivos valores do n�mero total
 * de modelos lidos e do n�mero total de modelos que n�o se conseguiram 
 * processar atrav�s das fun��es getNumModels() e getFailedModels().
 *
 * @author Carlos Pereira - A61887
 * @author Jo�o Barreira  - A73831
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
	class XMLParserImpl;  // Implementa��o da parte privada da classe XMLParser
	XMLParserImpl* pimpl; // Apontador para a parte privada

public:


	/**
	 * Construtor por defeito.
	 */
	XMLParser(void);


	/**
	 * Construtor por par�metros.
	 *
	 * @param fileName Nome do ficheiro xml.
	 */
	XMLParser(std::string fileName);


	/**
	 * Construtor de c�pia.
	 *
	 * @param x Objeto da classe XMLParser a copiar.
	 */
	XMLParser(const XMLParser& x);


	/**
	 * Devolve o n�mero total de modelos lidos do ficheiro xml.
	 */
	size_t getNumModels(void);


	/**
	 * Devolve o n�mero de modelos que n�o se conseguiu processar.
	 */
	size_t getFailedModels(void);


	/**
	 * Devolve um vetor com a lista de opera��es em OpenGL contidas no ficheiro
	 * xml. As opera��es s�o ordenadas conforme a ordem destas no ficheiro.
	 * Em caso de algum erro, o vetor devolvido � vazio.
	 */
	std::vector<GLOperation*> getGLOperations(void);


	/**
	 * Devolve uma representa��o textual de eventuais erros, ou warnings, do
	 * parsing do ficheiro xml, caso estes existam.
	 */
	std::string getErrorString(void);


	/**
	 * Destrutor da classe XMLParser.
	 */
	~XMLParser(void);
};


#endif 

