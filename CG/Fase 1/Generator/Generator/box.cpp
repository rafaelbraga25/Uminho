/**
 * @file box.cpp
 *
 * Definição de métodos para calcular as coordenadas dos pontos de uma caixa.
 *
 * @author Carlos Pereira - A61887
 * @author João Barreira  - A73831
 * @author Rafael Braga   - A61799
 */


#include "box.h"


class Box::BoxImpl {
	float dimX;     // Dimensão da caixa no eixo dos xx
	float dimY;     // Dimensão da caixa no eixo dos yy
	float dimZ;     // Dimensão da caixa no eixo dos zz
	float divX;     // Dimensão de uma divisão da caixa no eixo dos xx
	float divY;     // Dimensão de uma divisão da caixa no eixo dos yy
	float divZ;     // Dimensão de uma divisão da caixa no eixo dos zz
	float centerX;  // Coordenada x do centro da caixa
	float centerY;  // Coordenada y do centro da caixa
	float centerZ;  // Coordenada z do centro da caix
	size_t numDiv;  // Número de divisões da caixa


public:

	/**
	 * Construtor por defeito. 
	 */
	BoxImpl(void)
	{
		dimX = dimY = dimZ = divX = divY = divZ = 0;
		centerX = centerY = centerZ = 0;
		numDiv = 0;
	}


	/**
	 * Construtor por parâmetros.
	 *
	 * @param dimX Dimensão da caixa no eixo dos xx.
	 * @param dimY Dimensão da caixa no eixo dos yy.
	 * @param dimZ Dimensão da caixa no eixo dos zz.
	 * @param numDiv Número de divisões da caixa.
	 */
	BoxImpl(float dimX, float dimY, float dimZ, size_t numDiv)
	{
		this->dimX = dimX;
		this->dimY = dimY;
		this->dimZ = dimZ;
		this->numDiv = numDiv;

		// Dimensão de cada divisão em cada eixo
		divX = dimX / ((float) numDiv);
		divY = dimY / ((float) numDiv);
		divZ = dimZ / ((float) numDiv);

		// Coordenadas x, y e z do centro da caixa
		centerX = dimX / 2;
		centerY = dimY / 2;
		centerZ = dimZ / 2;
	}


	/**
	 * Devolve o valor da dimensão da caixa no eixo dos xx.
	 */
	float getDimX(void)
	{
		return dimX;
	}
	 

	/**
	 * Devolve o valor da dimensão da caixa no eixo dos yy.
	 */
	float getDimY(void)
	{
		return dimY;
	}


	/**
	 * Devolve o valor da dimensão da caixa no eixo dos zz.
	 */
	float getDimZ(void)
	{
		return dimZ;
	}


	/**
	 * Devolve o número de divisões da caixa.
	 */
	size_t getNumDiv(void)
	{
		return numDiv;
	}


	/**
	 * Altera o valor da dimensão da caixa no eixo dos xx.
	 */
	void setDimX(float dimX)
	{
		divX = dimX / ((float)numDiv);
		centerX = dimX / 2;
		this->dimX = dimX;
	}


	/**
	 * Altera o valor da dimensão da caixa no eixo dos yy.
	 */
	void setDimY(float dimY)
	{
		divY = dimY / ((float)numDiv);
		centerY = dimY / 2;
		this->dimY = dimY;
	}


	/**
	 * Altera o valor da dimensão da caixa no eixo dos zz.
	 */
	void setDimZ(float dimZ)
	{
		divZ = dimZ / ((float)numDiv);
		centerZ = dimZ / 2;
		this->dimZ = dimZ;
	}


	/**
	 * Altera o número de divisões da caixa.
	 */
	void setNumDiv(size_t numDiv)
	{
		divX = dimX / ((float)numDiv);
		divY = dimY / ((float)numDiv);
		divZ = dimZ / ((float)numDiv);

		centerX = dimX / 2;
		centerY = dimY / 2;
		centerZ = dimZ / 2;

		this->numDiv = numDiv;
	}


	/**
	 * Calcula todos os vértices das duas faces parelelas ao plano XY da caixa.
	 * Os vértices da face da frente são calculados usando a regra da mão 
	 * direita no sentido contrário aos ponteiros do relógio. Já os vértices 
	 * da face de trás são calculados segundo a regra da mão direita no sentido
	 * dos ponteiros do relógio. Ambas as faces são centradas em relação à
	 * origem.
	 *
	 *   v8----- v6
     *   |       |
     * v4------v3|
     * | |     | |
     * | |v5---|-|v7
     * |       | 
     * v1------v2
	 *
	 * @param x Coordenada x do vértice inicial (v1).
	 * @param y Coordenada y do vértice inicial (v1).
	 * @param z Coordenada z do vértice inicial (v1).
	 * @return Vetor com as coordenadas dos vértices das duas faces paralelas
	 *         ao plano XY da caixa.
	 */
	std::vector<Vertex> generateFacesXY(float x, float y, float z)
	{
		std::vector<Vertex> vertices; 

		// Para cada uma das duas faces, serão calculados 2 triângulos por divisão

		for (float i = x; i < dimX; i += divX) {
			for (float j = y; j < dimY; j += divY) {

				// Face da frente

				// Vértices v1-v2-v3
				vertices.push_back(Vertex(i - centerX, j - centerY, z - centerZ));
				vertices.push_back(Vertex(i + divX - centerX, j - centerY, z - centerZ));
				vertices.push_back(Vertex(i + divX - centerX, j + divY - centerY, z - centerZ));

				// Vértices v1-v3-v4
				vertices.push_back(Vertex(i - centerX, j - centerY, z - centerZ));
				vertices.push_back(Vertex(i + divX - centerX, j + divY - centerY, z - centerZ));
				vertices.push_back(Vertex(i - centerX, j + divY - centerY, z - centerZ));


				// Face de trás

				// Vértices v5-v6-v7
				vertices.push_back(Vertex(i - centerX, j - centerY, z - dimZ - centerZ));
				vertices.push_back(Vertex(i + divX - centerX, j + divY - centerY, z - dimZ - centerZ));
				vertices.push_back(Vertex(i + divX - centerX, j - centerY, z - dimZ - centerZ));

				// Vértices v5-v8-v6
				vertices.push_back(Vertex(i - centerX, j - centerY, z - dimZ - centerZ));
				vertices.push_back(Vertex(i - centerX, j + divY - centerY, z - dimZ - centerZ));
				vertices.push_back(Vertex(i + divX - centerX, j + divY - centerY, z - dimZ - centerZ));
			}
		}

		return vertices;
	}


	/**
	 * Calcula todos os vértices das duas faces parelelas ao plano XZ da caixa.
	 * Os vértices da face de cima são calculados usando a regra da mão
	 * direita no sentido contrário aos ponteiros do relógio. Já os vértices
	 * da face de baixo são calculados segundo a regra da mão direita no sentido
	 * dos ponteiros do relógio. Ambas as faces são centradas em relação à
	 * origem.
	 *
	 *   v1------v3
	 *  /       / 
	 * v2------v4
	 *         
	 *   v5------v6
	 *  /       /
	 * v7------v8
	 *
	 * @param x Coordenada x do vértice inicial (v1).
	 * @param y Coordenada y do vértice inicial (v1).
	 * @param z Coordenada z do vértice inicial (v1).
	 * @return Vetor com as coordenadas dos vértices das duas faces paralelas
	 *         ao plano XZ da caixa.
	 */
	std::vector<Vertex> generateFacesXZ(float x, float y, float z)
	{
		std::vector<Vertex> vertices;

		// Para cada uma das duas faces, serão calculados 2 triângulos por divisão

		for (float i = x; i < dimX; i += divX) {
			for (float j = z; j < dimZ; j += divZ) {

				// Face de cima
				
				// Vértices v1-v2-v3
				vertices.push_back(Vertex(i - centerX, y - centerY, j - centerZ));
				vertices.push_back(Vertex(i - centerX, y - centerY, j + divZ - centerZ));
				vertices.push_back(Vertex(i + divX - centerX, y - centerY, j - centerZ));

				// Vérices v3-v2-v4
				vertices.push_back(Vertex(i + divX - centerX, y - centerY, j - centerZ));
				vertices.push_back(Vertex(i - centerX, y - centerY, j + divZ - centerZ));
				vertices.push_back(Vertex(i + divX - centerX, y - centerY, j + divZ - centerZ));


				// Face de baixo

				// Vértices v5-v6-v7
				vertices.push_back(Vertex(i - centerX, y - centerY - dimY, j - centerZ));
				vertices.push_back(Vertex(i + divX - centerX, y - centerY - dimY, j - centerZ));
				vertices.push_back(Vertex(i - centerX, y - centerY - dimY, j + divZ - centerZ));
				
				// Vértices v6-v8-v7
				vertices.push_back(Vertex(i + divX - centerX, y - centerY - dimY, j - centerZ));
				vertices.push_back(Vertex(i + divX - centerX, y - centerY - dimY, j + divZ - centerZ));
				vertices.push_back(Vertex(i - centerX, y - centerY - dimY, j + divZ - centerZ));
			}
		}

		return vertices;
	}


	/**
	 * Calcula todos os vértices das duas faces parelelas ao plano YZ da caixa.
	 * Os vértices da face da direita são calculados usando a regra da mão
	 * direita no sentido contrário aos ponteiros do relógio. Já os vértices
	 * da face da esquerda são calculados segundo a regra da mão direita no 
	 * sentido dos ponteiros do relógio. Ambas as faces são centradas em 
	 * relação à origem.
	 *
	 *   v7      v2
	 *  /|      /|
	 * v6|     v3|
	 * | |     | |
	 * | |v5   |v1
	 * |/      |/
	 * v8      v4
	 *
	 * @param x Coordenada x do vértice inicial (v1).
	 * @param y Coordenada y do vértice inicial (v1).
	 * @param z Coordenada z do vértice inicial (v1).
	 * @return Vetor com as coordenadas dos vértices das duas faces paralelas
	 *         ao plano YZ da caixa.
	 */
	std::vector<Vertex> generateFacesYZ(float x, float y, float z)
	{
		std::vector<Vertex> vertices;

		// Para cada uma das duas faces, serão calculados 2 triângulos por divisão

		for (float i = y; i < dimY; i += divY) {
			for (float j = z; j < dimZ; j += divZ) {

				// Face da direita

				// Vértices v1-v2-v3
				vertices.push_back(Vertex(x - centerX, i - centerY, j - centerZ));
				vertices.push_back(Vertex(x - centerX, i + divY - centerY, j - centerZ));
				vertices.push_back(Vertex(x - centerX, i + divY - centerY, j + divZ - centerZ));

				// Vértices v1-v3-v4
				vertices.push_back(Vertex(x - centerX, i - centerY, j - centerZ));
				vertices.push_back(Vertex(x - centerX, i + divY - centerY, j + divZ - centerZ));
				vertices.push_back(Vertex(x - centerX, i - centerY, j + divZ - centerZ));


				// Face da esquerda

				// Vértices v5-v6-v7
				vertices.push_back(Vertex(x - centerX - dimX, i - centerY, j - centerZ));
				vertices.push_back(Vertex(x - centerX - dimX, i + divY - centerY, j + divZ - centerZ));
				vertices.push_back(Vertex(x - centerX - dimX, i + divY - centerY, j - centerZ));

				// Vértices v5-v8-v6
				vertices.push_back(Vertex(x - centerX - dimX, i - centerY, j - centerZ));
				vertices.push_back(Vertex(x - centerX - dimX, i - centerY, j + divZ - centerZ));
				vertices.push_back(Vertex(x - centerX - dimX, i + divY - centerY, j + divZ - centerZ));
			}
		}

		return vertices;
	}


	/**
	 * Destrutor por defeito.
	 */
	~BoxImpl(void) = default;
};


/**
 * Construtor por defeito.
 */
Box::Box(void) : pimpl{ new BoxImpl() } {}


/**
 * Construtor por parâmetros.
 *
 * @param dimX Dimensão da caixa no eixo dos xx.
 * @param dimY Dimensão da caixa no eixo dos yy.
 * @param dimZ Dimensão da caixa no eixo dos zz.
 * @param numDiv Número de divisões da caixa.
 */
Box::Box(float dimX, float dimY, float dimZ, size_t numDiv)
{
	// O número de divisões da caixa tem que ser superior a 1
	numDiv = (numDiv < 1) ?	1 : numDiv;

	// Não faz sentido uma dimensão ter um valor negativo
	dimX = (dimX < 0) ? 0 : dimX;
	dimY = (dimY < 0) ? 0 : dimY;
	dimZ = (dimZ < 0) ? 0 : dimZ;

	pimpl = new BoxImpl(dimX, dimY, dimZ, numDiv);

	generateVertices();
}


/**
 * Construtor de cópia.
 *
 * @param b Objeto da classe Box a ser copiado.
 */
Box::Box(const Box& b)
{
	pimpl = new BoxImpl(b.pimpl->getDimX(), b.pimpl->getDimY(), 
		                b.pimpl->getDimZ(), b.pimpl->getNumDiv());
}


/**
 * Devolve o valor da dimensão da caixa no eixo dos xx.
 */
float Box::getDimX(void)
{
	return pimpl->getDimX();
}


/**
 * Devolve o valor da dimensão da caixa no eixo dos yy.
 */
float Box::getDimY(void)
{
	return pimpl->getDimY();
}


/**
 * Devolve o valor da dimensão da caixa no eixo dos zz.
 */
float Box::getDimZ(void)
{
	return pimpl->getDimZ();
}


/**
 * Devolve o número de divisões da caixa.
 */
size_t Box::getNumDiv(void)
{
	return pimpl->getNumDiv();
}


/**
 * Altera o valor da dimensão da caixa no eixo dos xx.
 */
void Box::setDimX(float dimX)
{
	dimX = (dimX < 0) ? 0 : dimX;
	pimpl->setDimX(dimX);
}


/**
 * Altera o valor da dimensão da caixa no eixo dos yy.
 */
void Box::setDimY(float dimY)
{
	dimY = (dimY < 0) ? 0 : dimY;
	pimpl->setDimY(dimY);
}


/**
 * Altera o valor da dimensão da caixa no eixo dos zz.
 */
void Box::setDimZ(float dimZ)
{
	dimZ = (dimZ < 0) ? 0 : dimZ;
	pimpl->setDimZ(dimZ);
}


/**
 * Altera o número de divisões da caixa.
 */
void Box::setNumDiv(size_t numDiv)
{
	numDiv = (numDiv < 1) ? 1 : numDiv;
	pimpl->setNumDiv(numDiv);
}


/**
 * Método que cálcula todos as coordenadas de todos os pontos de uma caixa.
 */
void Box::generateVertices(void)
{
	// Gera os vértices das faces XY, XZ e YZ
	std::vector<Vertex> verticesXY = pimpl->generateFacesXY(0, 0, pimpl->getDimZ());
	std::vector<Vertex> verticesXZ = pimpl->generateFacesXZ(0, pimpl->getDimY(), 0);
	std::vector<Vertex> verticesYZ = pimpl->generateFacesYZ(pimpl->getDimX(), 0, 0);


	// Adiciona os vértices pertencentes a cada face ao conjunto total de
	// vértices da caixa
	for (size_t i = 0; i < verticesXY.size(); i++) {
		addVertex(verticesXY.at(i));
	}

	for (size_t i = 0; i < verticesXZ.size(); i++) {
		addVertex(verticesXZ.at(i));
	}

	for (size_t i = 0; i < verticesYZ.size(); i++) {
		addVertex(verticesYZ.at(i));
	}
}


/**
 * Destrutor da classe Box.
 *
 * Liberta a memória ocupada pelo apontador para a parte privada da classe
 * Box.
 */
Box::~Box(void)
{
	if (pimpl != NULL) {
		delete pimpl;
		pimpl = NULL;
	}
}