/**
 * @file trianglesDrawing.h
 *
 * @brief M�dulo que apresenta m�todos para se efetuar um desenho de um
 *        conjunto de tri�ngulos em OpenGL.
 *
 * Uma tri�ngulo � definido como tr�s v�rtices. Esta classe usa ent�o um
 * array de v�rtices recorrendo � classe auxiliar Vertex. 
 *
 * @author Carlos Pereira - A61887
 * @author Jo�o Barreira  - A73831
 * @author Rafael Braga   - A61799
 *
 * @version 4-04-2017
 */


#ifndef trianglesDrawing_h
#define trianglesDrawing_h


#include <vector>
#include "glOperation.h"
#include "vertex.h"


class TrianglesDrawing : public GLOperation {
	class TrianglesDrawingImpl;   // Implementa��o da classe TrianglesDrawing
	TrianglesDrawingImpl* pimpl;  // Apontador para a implementa��o da classe 
	                              // TrianglesDrawing


public:

	/**
	 * Construtor por defeito.
	 */
	TrianglesDrawing(void);


	/**
	 * Construtor por par�metros.
	 *
	 * @param vertices Conjunto de v�rtices a desenhar.
	 * @param diffR    Valor da difus�o em vermelho.
	 * @param diffG    Valor da difus�o em verde.
	 * @param diffB    Valor da difus�o em azul.
	 */
	TrianglesDrawing(std::vector<GLfloat> vertices, std::vector<size_t> indexes,
		             float diffR, float diffG, float diffB);


	/**
	 * Construtor de c�pia.
	 *
	 * @param t Objeto da classe TrianglesDrawing a copiar.
	 */
	TrianglesDrawing(const TrianglesDrawing& t);


	/**
	 * Devolve o conjunto de v�rtices a desenhar.
	 */
	std::vector<GLfloat> getVertices(void);
	

	/**
	 * Devolve o conjunto de �ndices associados ao vetor de v�rtices.
	 */
	std::vector<size_t> getIndexes(void);

	
	/**
	 * Devolve o valor da difus�o em vermelho.
	 */
	float getDiffR(void);


	/**
	 * Devolve o valor da difus�o em verde.
	 */
	float getDiffG(void);


	/**
	 * Devolve o valor da difus�o em azul.
	 */
	float getDiffB(void);


	/**
	 * Altera o conjunto de v�rtices a desenhar.
	 */
	void setVertices(std::vector<GLfloat>);


	/**
	 * Altera o conjunto de �ndices associados ao vetor de v�rtices.
	 */
	void setIndexes(std::vector<size_t>);


	/**
	 * Altera o valor da difus�o em vermelho.
	 */
	void setDiffR(float);


	/**
	 * Altera o valor da difus�o em verde.
	 */
	void setDiffG(float);


	/**
	 * Altera o valor da difus�o em azul.
	 */
	void setDiffB(float);


	/**
	 * Desenha um conjunto de v�rtices de uma primitiva em OpenGL.
	 */
	void execute(void);


	/**
	 * Destrutor da classe TrianglesDrawing.
	 */
	~TrianglesDrawing(void);
};


#endif
