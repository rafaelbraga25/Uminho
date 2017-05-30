/**
 * @file box.cpp
 *
 * Defini��o de m�todos para calcular as coordenadas dos pontos de uma caixa.
 *
 * @author Carlos Pereira - A61887
 * @author Jo�o Barreira  - A73831
 * @author Rafael Braga   - A61799
 */


#include "box.h"


class Box::BoxImpl {
	float dimX;     // Dimens�o da caixa no eixo dos xx
	float dimY;     // Dimens�o da caixa no eixo dos yy
	float dimZ;     // Dimens�o da caixa no eixo dos zz
	float divX;     // Dimens�o de uma divis�o da caixa no eixo dos xx
	float divY;     // Dimens�o de uma divis�o da caixa no eixo dos yy
	float divZ;     // Dimens�o de uma divis�o da caixa no eixo dos zz
	float centerX;  // Coordenada x do centro da caixa
	float centerY;  // Coordenada y do centro da caixa
	float centerZ;  // Coordenada z do centro da caix
	size_t numDiv;  // N�mero de divis�es da caixa


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
	 * Construtor por par�metros.
	 *
	 * @param dimX Dimens�o da caixa no eixo dos xx.
	 * @param dimY Dimens�o da caixa no eixo dos yy.
	 * @param dimZ Dimens�o da caixa no eixo dos zz.
	 * @param numDiv N�mero de divis�es da caixa.
	 */
	BoxImpl(float dimX, float dimY, float dimZ, size_t numDiv)
	{
		this->dimX = dimX;
		this->dimY = dimY;
		this->dimZ = dimZ;
		this->numDiv = numDiv;

		// Dimens�o de cada divis�o em cada eixo
		divX = dimX / ((float) numDiv);
		divY = dimY / ((float) numDiv);
		divZ = dimZ / ((float) numDiv);

		// Coordenadas x, y e z do centro da caixa
		centerX = dimX / 2;
		centerY = dimY / 2;
		centerZ = dimZ / 2;
	}


	/**
	 * Devolve o valor da dimens�o da caixa no eixo dos xx.
	 */
	float getDimX(void)
	{
		return dimX;
	}
	 

	/**
	 * Devolve o valor da dimens�o da caixa no eixo dos yy.
	 */
	float getDimY(void)
	{
		return dimY;
	}


	/**
	 * Devolve o valor da dimens�o da caixa no eixo dos zz.
	 */
	float getDimZ(void)
	{
		return dimZ;
	}


	/**
	 * Devolve o n�mero de divis�es da caixa.
	 */
	size_t getNumDiv(void)
	{
		return numDiv;
	}


	/**
	 * Altera o valor da dimens�o da caixa no eixo dos xx.
	 */
	void setDimX(float dimX)
	{
		divX = dimX / ((float)numDiv);
		centerX = dimX / 2;
		this->dimX = dimX;
	}


	/**
	 * Altera o valor da dimens�o da caixa no eixo dos yy.
	 */
	void setDimY(float dimY)
	{
		divY = dimY / ((float)numDiv);
		centerY = dimY / 2;
		this->dimY = dimY;
	}


	/**
	 * Altera o valor da dimens�o da caixa no eixo dos zz.
	 */
	void setDimZ(float dimZ)
	{
		divZ = dimZ / ((float)numDiv);
		centerZ = dimZ / 2;
		this->dimZ = dimZ;
	}


	/**
	 * Altera o n�mero de divis�es da caixa.
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
	 * Calcula todos os v�rtices das duas faces parelelas ao plano XY da caixa.
	 * Os v�rtices da face da frente s�o calculados usando a regra da m�o 
	 * direita no sentido contr�rio aos ponteiros do rel�gio. J� os v�rtices 
	 * da face de tr�s s�o calculados segundo a regra da m�o direita no sentido
	 * dos ponteiros do rel�gio. Ambas as faces s�o centradas em rela��o �
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
	 * @param x Coordenada x do v�rtice inicial (v1).
	 * @param y Coordenada y do v�rtice inicial (v1).
	 * @param z Coordenada z do v�rtice inicial (v1).
	 * @return Vetor com as coordenadas dos v�rtices das duas faces paralelas
	 *         ao plano XY da caixa.
	 */
	std::vector<Vertex> generateFacesXY(float x, float y, float z)
	{
		std::vector<Vertex> vertices; 

		// Para cada uma das duas faces, ser�o calculados 2 tri�ngulos por divis�o

		for (float i = x; i < dimX; i += divX) {
			for (float j = y; j < dimY; j += divY) {

				// Face da frente

				// V�rtices v1-v2-v3
				vertices.push_back(Vertex(i - centerX, j - centerY, z - centerZ));
				vertices.push_back(Vertex(i + divX - centerX, j - centerY, z - centerZ));
				vertices.push_back(Vertex(i + divX - centerX, j + divY - centerY, z - centerZ));

				// V�rtices v1-v3-v4
				vertices.push_back(Vertex(i - centerX, j - centerY, z - centerZ));
				vertices.push_back(Vertex(i + divX - centerX, j + divY - centerY, z - centerZ));
				vertices.push_back(Vertex(i - centerX, j + divY - centerY, z - centerZ));


				// Face de tr�s

				// V�rtices v5-v6-v7
				vertices.push_back(Vertex(i - centerX, j - centerY, z - dimZ - centerZ));
				vertices.push_back(Vertex(i + divX - centerX, j + divY - centerY, z - dimZ - centerZ));
				vertices.push_back(Vertex(i + divX - centerX, j - centerY, z - dimZ - centerZ));

				// V�rtices v5-v8-v6
				vertices.push_back(Vertex(i - centerX, j - centerY, z - dimZ - centerZ));
				vertices.push_back(Vertex(i - centerX, j + divY - centerY, z - dimZ - centerZ));
				vertices.push_back(Vertex(i + divX - centerX, j + divY - centerY, z - dimZ - centerZ));
			}
		}

		return vertices;
	}


	/**
	 * Calcula todos os v�rtices das duas faces parelelas ao plano XZ da caixa.
	 * Os v�rtices da face de cima s�o calculados usando a regra da m�o
	 * direita no sentido contr�rio aos ponteiros do rel�gio. J� os v�rtices
	 * da face de baixo s�o calculados segundo a regra da m�o direita no sentido
	 * dos ponteiros do rel�gio. Ambas as faces s�o centradas em rela��o �
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
	 * @param x Coordenada x do v�rtice inicial (v1).
	 * @param y Coordenada y do v�rtice inicial (v1).
	 * @param z Coordenada z do v�rtice inicial (v1).
	 * @return Vetor com as coordenadas dos v�rtices das duas faces paralelas
	 *         ao plano XZ da caixa.
	 */
	std::vector<Vertex> generateFacesXZ(float x, float y, float z)
	{
		std::vector<Vertex> vertices;

		// Para cada uma das duas faces, ser�o calculados 2 tri�ngulos por divis�o

		for (float i = x; i < dimX; i += divX) {
			for (float j = z; j < dimZ; j += divZ) {

				// Face de cima
				
				// V�rtices v1-v2-v3
				vertices.push_back(Vertex(i - centerX, y - centerY, j - centerZ));
				vertices.push_back(Vertex(i - centerX, y - centerY, j + divZ - centerZ));
				vertices.push_back(Vertex(i + divX - centerX, y - centerY, j - centerZ));

				// V�rices v3-v2-v4
				vertices.push_back(Vertex(i + divX - centerX, y - centerY, j - centerZ));
				vertices.push_back(Vertex(i - centerX, y - centerY, j + divZ - centerZ));
				vertices.push_back(Vertex(i + divX - centerX, y - centerY, j + divZ - centerZ));


				// Face de baixo

				// V�rtices v5-v6-v7
				vertices.push_back(Vertex(i - centerX, y - centerY - dimY, j - centerZ));
				vertices.push_back(Vertex(i + divX - centerX, y - centerY - dimY, j - centerZ));
				vertices.push_back(Vertex(i - centerX, y - centerY - dimY, j + divZ - centerZ));
				
				// V�rtices v6-v8-v7
				vertices.push_back(Vertex(i + divX - centerX, y - centerY - dimY, j - centerZ));
				vertices.push_back(Vertex(i + divX - centerX, y - centerY - dimY, j + divZ - centerZ));
				vertices.push_back(Vertex(i - centerX, y - centerY - dimY, j + divZ - centerZ));
			}
		}

		return vertices;
	}


	/**
	 * Calcula todos os v�rtices das duas faces parelelas ao plano YZ da caixa.
	 * Os v�rtices da face da direita s�o calculados usando a regra da m�o
	 * direita no sentido contr�rio aos ponteiros do rel�gio. J� os v�rtices
	 * da face da esquerda s�o calculados segundo a regra da m�o direita no 
	 * sentido dos ponteiros do rel�gio. Ambas as faces s�o centradas em 
	 * rela��o � origem.
	 *
	 *   v7      v2
	 *  /|      /|
	 * v6|     v3|
	 * | |     | |
	 * | |v5   |v1
	 * |/      |/
	 * v8      v4
	 *
	 * @param x Coordenada x do v�rtice inicial (v1).
	 * @param y Coordenada y do v�rtice inicial (v1).
	 * @param z Coordenada z do v�rtice inicial (v1).
	 * @return Vetor com as coordenadas dos v�rtices das duas faces paralelas
	 *         ao plano YZ da caixa.
	 */
	std::vector<Vertex> generateFacesYZ(float x, float y, float z)
	{
		std::vector<Vertex> vertices;

		// Para cada uma das duas faces, ser�o calculados 2 tri�ngulos por divis�o

		for (float i = y; i < dimY; i += divY) {
			for (float j = z; j < dimZ; j += divZ) {

				// Face da direita

				// V�rtices v1-v2-v3
				vertices.push_back(Vertex(x - centerX, i - centerY, j - centerZ));
				vertices.push_back(Vertex(x - centerX, i + divY - centerY, j - centerZ));
				vertices.push_back(Vertex(x - centerX, i + divY - centerY, j + divZ - centerZ));

				// V�rtices v1-v3-v4
				vertices.push_back(Vertex(x - centerX, i - centerY, j - centerZ));
				vertices.push_back(Vertex(x - centerX, i + divY - centerY, j + divZ - centerZ));
				vertices.push_back(Vertex(x - centerX, i - centerY, j + divZ - centerZ));


				// Face da esquerda

				// V�rtices v5-v6-v7
				vertices.push_back(Vertex(x - centerX - dimX, i - centerY, j - centerZ));
				vertices.push_back(Vertex(x - centerX - dimX, i + divY - centerY, j + divZ - centerZ));
				vertices.push_back(Vertex(x - centerX - dimX, i + divY - centerY, j - centerZ));

				// V�rtices v5-v8-v6
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
 * Construtor por par�metros.
 *
 * @param dimX Dimens�o da caixa no eixo dos xx.
 * @param dimY Dimens�o da caixa no eixo dos yy.
 * @param dimZ Dimens�o da caixa no eixo dos zz.
 * @param numDiv N�mero de divis�es da caixa.
 */
Box::Box(float dimX, float dimY, float dimZ, size_t numDiv)
{
	// O n�mero de divis�es da caixa tem que ser superior a 1
	numDiv = (numDiv < 1) ?	1 : numDiv;

	// N�o faz sentido uma dimens�o ter um valor negativo
	dimX = (dimX < 0) ? 0 : dimX;
	dimY = (dimY < 0) ? 0 : dimY;
	dimZ = (dimZ < 0) ? 0 : dimZ;

	pimpl = new BoxImpl(dimX, dimY, dimZ, numDiv);

	generateVertices();
}


/**
 * Construtor de c�pia.
 *
 * @param b Objeto da classe Box a ser copiado.
 */
Box::Box(const Box& b)
{
	pimpl = new BoxImpl(b.pimpl->getDimX(), b.pimpl->getDimY(), 
		                b.pimpl->getDimZ(), b.pimpl->getNumDiv());
}


/**
 * Devolve o valor da dimens�o da caixa no eixo dos xx.
 */
float Box::getDimX(void)
{
	return pimpl->getDimX();
}


/**
 * Devolve o valor da dimens�o da caixa no eixo dos yy.
 */
float Box::getDimY(void)
{
	return pimpl->getDimY();
}


/**
 * Devolve o valor da dimens�o da caixa no eixo dos zz.
 */
float Box::getDimZ(void)
{
	return pimpl->getDimZ();
}


/**
 * Devolve o n�mero de divis�es da caixa.
 */
size_t Box::getNumDiv(void)
{
	return pimpl->getNumDiv();
}


/**
 * Altera o valor da dimens�o da caixa no eixo dos xx.
 */
void Box::setDimX(float dimX)
{
	dimX = (dimX < 0) ? 0 : dimX;
	pimpl->setDimX(dimX);
}


/**
 * Altera o valor da dimens�o da caixa no eixo dos yy.
 */
void Box::setDimY(float dimY)
{
	dimY = (dimY < 0) ? 0 : dimY;
	pimpl->setDimY(dimY);
}


/**
 * Altera o valor da dimens�o da caixa no eixo dos zz.
 */
void Box::setDimZ(float dimZ)
{
	dimZ = (dimZ < 0) ? 0 : dimZ;
	pimpl->setDimZ(dimZ);
}


/**
 * Altera o n�mero de divis�es da caixa.
 */
void Box::setNumDiv(size_t numDiv)
{
	numDiv = (numDiv < 1) ? 1 : numDiv;
	pimpl->setNumDiv(numDiv);
}


/**
 * M�todo que c�lcula todos as coordenadas de todos os pontos de uma caixa.
 */
void Box::generateVertices(void)
{
	// Gera os v�rtices das faces XY, XZ e YZ
	std::vector<Vertex> verticesXY = pimpl->generateFacesXY(0, 0, pimpl->getDimZ());
	std::vector<Vertex> verticesXZ = pimpl->generateFacesXZ(0, pimpl->getDimY(), 0);
	std::vector<Vertex> verticesYZ = pimpl->generateFacesYZ(pimpl->getDimX(), 0, 0);


	// Adiciona os v�rtices pertencentes a cada face ao conjunto total de
	// v�rtices da caixa
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
 * Liberta a mem�ria ocupada pelo apontador para a parte privada da classe
 * Box.
 */
Box::~Box(void)
{
	if (pimpl != NULL) {
		delete pimpl;
		pimpl = NULL;
	}
}