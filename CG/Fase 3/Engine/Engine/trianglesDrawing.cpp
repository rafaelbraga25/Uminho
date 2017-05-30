/**
 * @file trianglesDrawing.cpp
 *
 * Definição de todos os métodos para se representar um conjunto de vértices em
 * OpenGL.
 *
 * @author Carlos Pereira - A61887
 * @author João Barreira  - A73831
 * @author Rafael Braga   - A61799
 *
 * @version 4-4-2017
 */


#include "trianglesDrawing.h"


class TrianglesDrawing::TrianglesDrawingImpl {
	std::vector<GLfloat> vertices;  // Conjunto de vértices a desenhar
	std::vector<size_t> indexes;    // Conjunto de índices associados ao vetor
	                                // de vértices
	float diffR;                    // Valor da difusão em vermelho
	float diffG;                    // Valor da difusão em verde
	float diffB;                    // Valor da difusão em azul

	bool isGenerated;               // Flag que testa se o buffer já foi 
	                                // inicializado ou não

	GLuint indexesBuffer;           // Buffer utilizado para os VBOs


	/**
	 * Gera o buffer para ser utilizado em VBOs. Preenche o buffer com o array
	 * de íncices.
	 */
	void generate(void)
	{
		// O buffer é apenas inicalizado uma vez
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
	 * Construtor por parâmetros.
	 *
	 * @param vertices Conjunto de vértices a desenhar.
	 * @param indexes  Conjunto de índices associados ao vetor de vértices.
	 * @param diffR    Difusão em vermelho.
	 * @param diffG    Difusão em verde.
	 * @param diffB    Difusão em azul.
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
	 * Devolve o conjunto de vértices a desenhar.
	 */
	std::vector<GLfloat> getVertices(void)
	{
		return vertices;
	}


	/**
	 * Devolve o conjunto de índices associados ao vetor de vértices.
	 */
	std::vector<size_t> getIndexes(void)
	{
		return indexes;
	}


	/**
	 * Devolve o valor da difusão em vermelho.
	 */
	float getDiffR(void)
	{
		return diffR;
	}


	/**
 	 * Devolve o valor da difusão em verde.
	 */
	float getDiffG(void)
	{
		return diffG;
	}


	/**
	 * Devolve o valor da difusão em azul.
	 */
	float getDiffB(void)
	{
		return diffB;
	}


	/**
	 * Altera o conjunto de vértices a desenhar.
	 */
	void setVertices(std::vector<GLfloat> vertices)
	{
		this->vertices = vertices;
	}


	/**
	 * Altera o conjunto de índices associados ao vetor de vértices.
	 */
	void setIndexes(std::vector<size_t> indexes)
	{
		this->indexes = indexes;
	}


	/**
	 * Altera o valor da difusão em vermelho.
	 */
	void setDiffR(float diffR)
	{
		this->diffR = diffR;
	}


	/**
	 * Altera o valor da difusão em verde.
	 */
	void setDiffG(float diffG)
	{
		this->diffG = diffG;
	}


	/**
	 * Altera o valor da difusão em azul.
	 */
	void setDiffB(float diffB)
	{
		this->diffB = diffB;
	}


	/**
	 * Desenha uma primitiva em modo de VBOs com um conjunto de índices.
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
 * Construtor por defeito. Inicializa o apontador para a implementação da
 * classe TrianglesDrawing.
 */
TrianglesDrawing::TrianglesDrawing(void)
{
	pimpl = new TrianglesDrawingImpl();
}


/**
 * Construtor por parâmetros. Inicializa o apontador para a implementação da
 * classe TrianglesDrawing através dos parâmetros recebidos.
 *
 * @param vertices Conjunto de vértices a desenhar.
 * @param indexes  Conjunto de índices associados ao vetor de vértices.
 * @param diffR    Difusão em vermelho.
 * @param diffG    Difusão em verde.
 * @param diffB    Difusão em azul.
 */
TrianglesDrawing::TrianglesDrawing(std::vector<GLfloat> vertices,
                                   std::vector<size_t> indexes,
	                               float diffR, float diffG, float diffB)
{
	pimpl = new TrianglesDrawingImpl(vertices, indexes,
		                             diffR, diffG, diffB);
}


/**
 * Construtor de cópia. Inicializa o apontador para a implementação da classe
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
 * Devolve o conjunto de vértices a desenhar.
 */
std::vector<GLfloat> TrianglesDrawing::getVertices(void)
{
	return pimpl->getVertices();
}


/**
 * Devolve o conjunto de índices associados ao vetor de vértices.
 */
std::vector<size_t> TrianglesDrawing::getIndexes(void)
{
	return pimpl->getIndexes();
}


/**
 * Devolve o valor da difusão em vermelho.
 */
float TrianglesDrawing::getDiffR(void)
{
	return pimpl->getDiffR();
}


/**
 * Devolve o valor da difusão em verde.
 */
float TrianglesDrawing::getDiffG(void)
{
	return pimpl->getDiffG();
}


/**
 * Devolve o valor da difusão em azul.
 */
float TrianglesDrawing::getDiffB(void)
{
	return pimpl->getDiffB();
}


/**
 * Altera o conjunto de vértices a desenhar.
 */
void TrianglesDrawing::setVertices(std::vector<GLfloat> vertices)
{
	pimpl->setVertices(vertices);
}


/**
 * Altera o conjunto de índices associados ao vetor de vértices.
 */
void TrianglesDrawing::setIndexes(std::vector<size_t> indexes)
{
	pimpl->setIndexes(indexes);
}


/**
 * Altera o valor da difusão em vermelho.
 */
void TrianglesDrawing::setDiffR(float diffR)
{
	pimpl->setDiffR(diffR);
}


/**
 * Altera o valor da difusão em verde.
 */
void TrianglesDrawing::setDiffG(float diffG)
{
	pimpl->setDiffG(diffG);
}


/**
 * Altera o valor da difusão em azul.
 */
void TrianglesDrawing::setDiffB(float diffB)
{
	pimpl->setDiffB(diffB);
}


/**
 * Desenha os vértices correspondentes a uma primitiva em OpenGL.
 */
void TrianglesDrawing::execute(void)
{
	pimpl->execute();
}


/**
 * Destrutor da classe TrianglesDrawing. Liberta a memória ocupada pelo 
 * apontador para a implementação da classe TrianglesDrawing.
 */
TrianglesDrawing::~TrianglesDrawing(void)
{
	if (pimpl != NULL) {
		delete pimpl;
		pimpl = NULL;
	}
}