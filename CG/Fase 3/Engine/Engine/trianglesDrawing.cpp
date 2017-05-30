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
 * @version 4-4-2017
 */


#include "trianglesDrawing.h"


class TrianglesDrawing::TrianglesDrawingImpl {
	std::vector<GLfloat> vertices;  // Conjunto de v�rtices a desenhar
	std::vector<size_t> indexes;    // Conjunto de �ndices associados ao vetor
	                                // de v�rtices
	float diffR;                    // Valor da difus�o em vermelho
	float diffG;                    // Valor da difus�o em verde
	float diffB;                    // Valor da difus�o em azul

	bool isGenerated;               // Flag que testa se o buffer j� foi 
	                                // inicializado ou n�o

	GLuint indexesBuffer;           // Buffer utilizado para os VBOs


	/**
	 * Gera o buffer para ser utilizado em VBOs. Preenche o buffer com o array
	 * de �ncices.
	 */
	void generate(void)
	{
		// O buffer � apenas inicalizado uma vez
		isGenerated = true;

		glGenBuffers(1, &indexesBuffer);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexesBuffer);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexes.size() * sizeof(size_t),
			         &indexes[0], GL_STATIC_DRAW);
	}


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
	 * @param indexes  Conjunto de �ndices associados ao vetor de v�rtices.
	 * @param diffR    Difus�o em vermelho.
	 * @param diffG    Difus�o em verde.
	 * @param diffB    Difus�o em azul.
	 */
	TrianglesDrawingImpl(std::vector<GLfloat> vertices, 
		                 std::vector<size_t> indexes,
		                 float diffR, float diffG, float diffB)
	{
		this->vertices = vertices;
		this->indexes = indexes;

		this->diffR = diffR;
		this->diffG = diffG;
		this->diffB = diffB;

		isGenerated = false;
	}


	/**
	 * Devolve o conjunto de v�rtices a desenhar.
	 */
	std::vector<GLfloat> getVertices(void)
	{
		return vertices;
	}


	/**
	 * Devolve o conjunto de �ndices associados ao vetor de v�rtices.
	 */
	std::vector<size_t> getIndexes(void)
	{
		return indexes;
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
	void setVertices(std::vector<GLfloat> vertices)
	{
		this->vertices = vertices;
	}


	/**
	 * Altera o conjunto de �ndices associados ao vetor de v�rtices.
	 */
	void setIndexes(std::vector<size_t> indexes)
	{
		this->indexes = indexes;
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
	 * Desenha uma primitiva em modo de VBOs com um conjunto de �ndices.
	 */
	void execute(void)
	{
		if (isGenerated == false) {
			generate();
		}

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexesBuffer);	
		glVertexPointer(3, GL_FLOAT, 0, &vertices[0]);
		glColor3f(diffR, diffG, diffB);


	
		glDrawElements(GL_TRIANGLES, indexes.size(), GL_UNSIGNED_INT, NULL);
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
 * @param indexes  Conjunto de �ndices associados ao vetor de v�rtices.
 * @param diffR    Difus�o em vermelho.
 * @param diffG    Difus�o em verde.
 * @param diffB    Difus�o em azul.
 */
TrianglesDrawing::TrianglesDrawing(std::vector<GLfloat> vertices,
                                   std::vector<size_t> indexes,
	                               float diffR, float diffG, float diffB)
{
	pimpl = new TrianglesDrawingImpl(vertices, indexes,
		                             diffR, diffG, diffB);
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
		                             t.pimpl->getIndexes(),
		                             t.pimpl->getDiffR(),
		                             t.pimpl->getDiffG(),
		                             t.pimpl->getDiffB());
}


/**
 * Devolve o conjunto de v�rtices a desenhar.
 */
std::vector<GLfloat> TrianglesDrawing::getVertices(void)
{
	return pimpl->getVertices();
}


/**
 * Devolve o conjunto de �ndices associados ao vetor de v�rtices.
 */
std::vector<size_t> TrianglesDrawing::getIndexes(void)
{
	return pimpl->getIndexes();
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
void TrianglesDrawing::setVertices(std::vector<GLfloat> vertices)
{
	pimpl->setVertices(vertices);
}


/**
 * Altera o conjunto de �ndices associados ao vetor de v�rtices.
 */
void TrianglesDrawing::setIndexes(std::vector<size_t> indexes)
{
	pimpl->setIndexes(indexes);
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
	pimpl->execute();
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