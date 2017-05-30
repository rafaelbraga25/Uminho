/**
 * @file trianglesDrawing.h
 *
 * @brief Módulo que apresenta métodos para se efetuar um desenho de um
 *        conjunto de triângulos em OpenGL.
 *
 * Uma triângulo é definido como três vértices. Esta classe usa então um
 * array de vértices recorrendo à classe auxiliar Vertex. 
 *
 * @author Carlos Pereira - A61887
 * @author João Barreira  - A73831
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
	class TrianglesDrawingImpl;   // Implementação da classe TrianglesDrawing
	TrianglesDrawingImpl* pimpl;  // Apontador para a implementação da classe 
	                              // TrianglesDrawing


public:

	/**
	 * Construtor por defeito.
	 */
	TrianglesDrawing(void);


	/**
	 * Construtor por parâmetros.
	 *
	 * @param vertices Conjunto de vértices a desenhar.
	 * @param diffR    Valor da difusão em vermelho.
	 * @param diffG    Valor da difusão em verde.
	 * @param diffB    Valor da difusão em azul.
	 */
	TrianglesDrawing(std::vector<GLfloat> vertices, std::vector<size_t> indexes,
		             float diffR, float diffG, float diffB);


	/**
	 * Construtor de cópia.
	 *
	 * @param t Objeto da classe TrianglesDrawing a copiar.
	 */
	TrianglesDrawing(const TrianglesDrawing& t);


	/**
	 * Devolve o conjunto de vértices a desenhar.
	 */
	std::vector<GLfloat> getVertices(void);
	

	/**
	 * Devolve o conjunto de índices associados ao vetor de vértices.
	 */
	std::vector<size_t> getIndexes(void);

	
	/**
	 * Devolve o valor da difusão em vermelho.
	 */
	float getDiffR(void);


	/**
	 * Devolve o valor da difusão em verde.
	 */
	float getDiffG(void);


	/**
	 * Devolve o valor da difusão em azul.
	 */
	float getDiffB(void);


	/**
	 * Altera o conjunto de vértices a desenhar.
	 */
	void setVertices(std::vector<GLfloat>);


	/**
	 * Altera o conjunto de índices associados ao vetor de vértices.
	 */
	void setIndexes(std::vector<size_t>);


	/**
	 * Altera o valor da difusão em vermelho.
	 */
	void setDiffR(float);


	/**
	 * Altera o valor da difusão em verde.
	 */
	void setDiffG(float);


	/**
	 * Altera o valor da difusão em azul.
	 */
	void setDiffB(float);


	/**
	 * Desenha um conjunto de vértices de uma primitiva em OpenGL.
	 */
	void execute(void);


	/**
	 * Destrutor da classe TrianglesDrawing.
	 */
	~TrianglesDrawing(void);
};


#endif
