/**
 * @file trianglesDrawing.cpp
 *
 * Defini��o de todos os m�todos para se representar um conjunto de v�rtices em
 * OpenGL.
 *
 * @author Carlos Pereira - A61887
 * @author Jo�o Barreira  - A73831
 * @author Rafael Braga   - A61799
 *
 * @version 26-03-2017
 */


#include "trianglesDrawing.h"


class TrianglesDrawing::TrianglesDrawingImpl {
	std::vector<Vertex> vertices;  // Conjunto de v�rtices a desenhar
	float diffR;                   // Valor da difus�o em vermelho
	float diffG;                   // Valor da difus�o em verde
	float diffB;                   // Valor da difus�o em azul


public:

	/**
	 * Construtor por defeito.
	 */
	TrianglesDrawingImpl(void)
	{
		diffR = diffG = diffB = 0;
	}


	/**
	 * Construtor por par�metros.
	 *
	 * @param vertices Conjunto de v�rtices a desenhar.
	 */
	TrianglesDrawingImpl(std::vector<Vertex> vertices,
		                 float diffR, float diffG, float diffB)
	{
		for (size_t i = 0; i < vertices.size(); i++) {
			this->vertices.push_back(vertices.at(i));
		}

		this->diffR = diffR;
		this->diffG = diffG;
		this->diffB = diffB;
	}


	/**
	 * Devolve o conjunto de v�rtices a desenhar.
	 */
	std::vector<Vertex> getVertices(void)
	{
		return vertices;
	}


	/**
	 * Devolve o valor da difus�o em vermelho.
	 */
	float getDiffR(void)
	{
		return diffR;
	}


	/**
 	 * Devolve o valor da difus�o em verde.
	 */
	float getDiffG(void)
	{
		return diffG;
	}


	/**
	 * Devolve o valor da difus�o em azul.
	 */
	float getDiffB(void)
	{
		return diffB;
	}


	/**
	 * Altera o conjunto de v�rtices a desenhar.
	 */
	void setVertices(std::vector<Vertex> vertices)
	{
		for (size_t i = 0; i < vertices.size(); i++) {
			this->vertices.push_back(vertices.at(i));
		}
	}


	/**
	 * Altera o valor da difus�o em vermelho.
	 */
	void setDiffR(float diffR)
	{
		this->diffR = diffR;
	}


	/**
	 * Altera o valor da difus�o em verde.
	 */
	void setDiffG(float diffG)
	{
		this->diffG = diffG;
	}


	/**
	 * Altera o valor da difus�o em azul.
	 */
	void setDiffB(float diffB)
	{
		this->diffB = diffB;
	}


	/**
	 * Destrutor da classe TrianglesDrawingImpl (por defeito em c++).
	 */
	~TrianglesDrawingImpl(void) = default;
};


/**
 * Construtor por defeito. Inicializa o apontador para a implementa��o da
 * classe TrianglesDrawing.
 */
TrianglesDrawing::TrianglesDrawing(void)
{
	pimpl = new TrianglesDrawingImpl();
}


/**
 * Construtor por par�metros. Inicializa o apontador para a implementa��o da
 * classe TrianglesDrawing atrav�s dos par�metros recebidos.
 *
 * @param vertices Conjunto de v�rtices a desenhar.
 */
TrianglesDrawing::TrianglesDrawing(std::vector<Vertex> vertices,
	                               float diffR, float diffG, float diffB)
{
	pimpl = new TrianglesDrawingImpl(vertices, diffR, diffG, diffB);
}


/**
 * Construtor de c�pia. Inicializa o apontador para a implementa��o da classe
 * TrianglesDrawing, recorrendo a uma deep copy de um objeto desta classe.
 *
 * @param t Objeto da classe TrianglesDrawing a copiar.
 */
TrianglesDrawing::TrianglesDrawing(const TrianglesDrawing& t)
{
	pimpl = new TrianglesDrawingImpl(t.pimpl->getVertices(),
		                             t.pimpl->getDiffR(),
		                             t.pimpl->getDiffG(),
		                             t.pimpl->getDiffB());
}


/**
 * Devolve o conjunto de v�rtices a desenhar.
 */
std::vector<Vertex> TrianglesDrawing::getVertices(void)
{
	return pimpl->getVertices();
}


/**
 * Devolve o valor da difus�o em vermelho.
 */
float TrianglesDrawing::getDiffR(void)
{
	return pimpl->getDiffR();
}


/**
 * Devolve o valor da difus�o em verde.
 */
float TrianglesDrawing::getDiffG(void)
{
	return pimpl->getDiffG();
}


/**
 * Devolve o valor da difus�o em azul.
 */
float TrianglesDrawing::getDiffB(void)
{
	return pimpl->getDiffB();
}


/**
 * Altera o conjunto de v�rtices a desenhar.
 */
void TrianglesDrawing::setVertices(std::vector<Vertex> vertices)
{
	pimpl->setVertices(vertices);
}


/**
 * Altera o valor da difus�o em vermelho.
 */
void TrianglesDrawing::setDiffR(float diffR)
{
	pimpl->setDiffR(diffR);
}


/**
 * Altera o valor da difus�o em verde.
 */
void TrianglesDrawing::setDiffG(float diffG)
{
	pimpl->setDiffG(diffG);
}


/**
 * Altera o valor da difus�o em azul.
 */
void TrianglesDrawing::setDiffB(float diffB)
{
	pimpl->setDiffB(diffB);
}


/**
 * Desenha os v�rtices correspondentes a uma primitiva em OpenGL.
 */
void TrianglesDrawing::execute(void)
{
	std::vector<Vertex> vertices = pimpl->getVertices();

	glBegin(GL_TRIANGLES);
	glColor3f(pimpl->getDiffR(), pimpl->getDiffG(), pimpl->getDiffB());

	for (size_t i = 0; i < vertices.size(); i++) {
		glVertex3f(vertices.at(i).getX(),
			       vertices.at(i).getY(),
			       vertices.at(i).getZ());
	}

	glEnd();
}


/**
 * Destrutor da classe TrianglesDrawing. Liberta a mem�ria ocupada pelo 
 * apontador para a implementa��o da classe TrianglesDrawing.
 */
TrianglesDrawing::~TrianglesDrawing(void)
{
	if (pimpl != NULL) {
		delete pimpl;
		pimpl = NULL;
	}
}