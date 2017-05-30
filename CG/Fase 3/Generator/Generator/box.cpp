/**
 * @file box.cpp
 *
 * Defini��o de m�todos para calcular as coordenadas dos pontos de uma caixa.
 *
 * @author Carlos Pereira - A61887
 * @author Jo�o Barreira  - A73831
 * @author Rafael Braga   - A61799
 * 
 * @version 30-4-2017
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
	float centerZ;  // Coordenada z do centro da caixa
	int numDiv;     // N�mero de divis�es da caixa
	size_t index;   // �ndice atual do conjunto de �ndices


	/**
	 * Gera os �ndices necess�rios das duas faces de um plano de uma box.
	 *
	 * @param indexes Vetor de �ndices.
	 */
	void generateIndexes(std::vector<size_t>& indexes)
	{
		int a = 0;
		int b = 0;
		size_t aux = index;

		// Ponteiros do rel�gio
		for (a = 0; a < numDiv; a++) {
			for (b = 0; b < numDiv; b++) {
				indexes.push_back(a * (numDiv + 1) + b + aux);
				indexes.push_back((a + 1) * (numDiv + 1) + b + aux);
				indexes.push_back(a * (numDiv + 1) + b + 1 + aux);

				indexes.push_back((a + 1) * (numDiv + 1) + b + aux);
				indexes.push_back((a + 1) * (numDiv + 1) + b + 1 + aux);
				indexes.push_back(a * (numDiv + 1) + b + 1 + aux);
			}
		}

		index += ((numDiv + 1) * (numDiv + 1));
		aux = index;

		// Contr�rio aos ponteiros do rel�gio
		for (a = 0; a < numDiv; a++) {
			for (b = 0; b < numDiv; b++) {
				indexes.push_back(a * (numDiv + 1) + b + aux);
				indexes.push_back(a * (numDiv + 1) + b + 1 + aux);
				indexes.push_back((a + 1) * (numDiv + 1) + b + aux);

				indexes.push_back((a + 1) * (numDiv + 1) + b + aux);
				indexes.push_back(a * (numDiv + 1) + b + 1 + aux);
				indexes.push_back((a + 1) * (numDiv + 1) + b + 1 + aux);
			}
		}

		index += ((numDiv + 1) * (numDiv + 1));
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
	 * @param x        Coordenada x do v�rtice inicial (v1).
	 * @param y        Coordenada y do v�rtice inicial (v1).
	 * @param z        Coordenada z do v�rtice inicial (v1).
	 * @param vertices Conjunto de v�rtices.
	 * @param indexes  Conjunto de �ndices.
	 * @return O resultado � guardado em vertices e em indexes.
	 */
	void generateFacesXY(float x, float y, float z,
		                 std::vector<Vertex>& vertices,
		                 std::vector<size_t>& indexes)
	{
		int a = 0;
		int b = 0;
		float i = x;
		float j = y;

		// Para cada uma das duas faces, ser�o calculados 2 tri�ngulos por divis�o

		// Face da frente
		for (a = 0; a <= numDiv; a++, i += divX) {
			for (b = 0; b <= numDiv; b++, j += divY) {
				vertices.push_back(Vertex(i, j, z));
			}

			j = y;
		}

		i = x;
		j = y;

		// Face de tr�s
		for (a = 0; a <= numDiv; a++, i += divX) {
			for (b = 0; b <= numDiv; b++, j += divY) {
				vertices.push_back(Vertex(i, j, z - dimZ));
			}

			j = y;
		}
		
		generateIndexes(indexes);
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
	 * @param x        Coordenada x do v�rtice inicial (v1).
	 * @param y        Coordenada y do v�rtice inicial (v1).
	 * @param z        Coordenada z do v�rtice inicial (v1).
	 * @param vertices Conjunto de v�rtices.
	 * @param indexes  Conjunto de �ndices.
	 * @return O resultado � guardado em vertices e em indexes.
	 */
	void generateFacesXZ(float x, float y, float z,
		                 std::vector<Vertex>& vertices,
		                 std::vector<size_t>& indexes)
	{
		int a = 0;
		int b = 0;
		float i = x;
		float j = z;

		// Para cada uma das duas faces, ser�o calculados 2 tri�ngulos por divis�o

		// Face da frente
		for (a = 0; a <= numDiv; a++, i += divX) {
			for (b = 0; b <= numDiv; b++, j += divZ) {
				vertices.push_back(Vertex(i, y - dimY, j));
			}

			j = z;
		}

		i = x;
		j = z;

		// Face de tr�s
		for (a = 0; a <= numDiv; a++, i += divX) {
			for (b = 0; b <= numDiv; b++, j += divZ) {
				vertices.push_back(Vertex(i, y, j));
			}

			j = z;
		}

		generateIndexes(indexes);
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
	 * @param x        Coordenada x do v�rtice inicial (v1).
	 * @param y        Coordenada y do v�rtice inicial (v1).
	 * @param z        Coordenada z do v�rtice inicial (v1).
	 * @param vertices Conjunto de v�rtices.
	 * @param indexes  Conjunto de �ndices.
	 * @return O resultado � guardado em vertices e em indexes.
	 */
	void generateFacesYZ(float x, float y, float z,
		                 std::vector<Vertex>& vertices,
		                 std::vector<size_t>& indexes)
	{
		int a = 0;
		int b = 0;
		float i = y;
		float j = z;

		// Para cada uma das duas faces, ser�o calculados 2 tri�ngulos por divis�o

		// Face da frente
		for (a = 0; a <= numDiv; a++, i += divY) {
			for (b = 0; b <= numDiv; b++, j += divZ) {
				vertices.push_back(Vertex(x, i, j));
			}

			j = z;
		}

		i = y;
		j = z;

		// Face de tr�s
		for (a = 0; a <= numDiv; a++, i += divY) {
			for (b = 0; b <= numDiv; b++, j += divZ) {
				vertices.push_back(Vertex(x - dimX, i, j));
			}

			j = z;
		}

		generateIndexes(indexes);
	}


public:

	/**
	 * Construtor por defeito. 
	 */
	BoxImpl(void)
	{
		dimX = dimY = dimZ = divX = divY = divZ = 0;
		centerX = centerY = centerZ = 0;
		numDiv = 0;
		index = 0;
	}


	/**
	 * Construtor por par�metros.
	 *
	 * @param dimX Dimens�o da caixa no eixo dos xx.
	 * @param dimY Dimens�o da caixa no eixo dos yy.
	 * @param dimZ Dimens�o da caixa no eixo dos zz.
	 * @param numDiv N�mero de divis�es da caixa.
	 */
	BoxImpl(float dimX, float dimY, float dimZ, int numDiv)
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

		index = 0;
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
	int getNumDiv(void)
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
	void setNumDiv(int numDiv)
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
	 * Gera o conjunto de v�rtices de uma box, bem como o conjunto de �ndices
	 * associado a este vetor.
	 *
	 * @param vertices Conjunto de v�rtices.
	 * @param indexes  Conjunto de �ndices.
	 * @return O resultado � guardado em vertices e em indexes.
	 */
	void generateBox(std::vector<Vertex>& vertices,
		             std::vector<size_t>& indexes)
	{
		// Gera os v�rtices das faces XY, XZ e YZ
		generateFacesXY(-centerX, -centerY, dimZ - centerZ, vertices, indexes);
		generateFacesXZ(-centerX, dimY - centerY, -centerZ, vertices, indexes);
	    generateFacesYZ(dimX - centerX, -centerY, -centerZ, vertices, indexes);
	}


	/**
	 * Destrutor por defeito.
	 */
	~BoxImpl(void) = default;
};


/**
 * Construtor por defeito.
 */
Box::Box(void) {
	pimpl = new BoxImpl();
} 


/**
 * Construtor por par�metros.
 *
 * @param dimX Dimens�o da caixa no eixo dos xx.
 * @param dimY Dimens�o da caixa no eixo dos yy.
 * @param dimZ Dimens�o da caixa no eixo dos zz.
 * @param numDiv N�mero de divis�es da caixa.
 */
Box::Box(float dimX, float dimY, float dimZ, int numDiv)
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
int Box::getNumDiv(void)
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
void Box::setNumDiv(int numDiv)
{
	numDiv = (numDiv < 1) ? 1 : numDiv;
	pimpl->setNumDiv(numDiv);
}


/**
 * M�todo que c�lcula todos as coordenadas de todos os pontos de uma caixa.
 */
void Box::generateVertices(void)
{
	std::vector<Vertex> vertices;
	std::vector<size_t> indexes;

	pimpl->generateBox(vertices, indexes);

	for (size_t i = 0; i < vertices.size(); i++) {
		addVertex(vertices.at(i));
	}

	for (size_t i = 0; i < indexes.size(); i++) {
		addIndex(indexes.at(i));
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