/**
 * @file box.cpp
 *
 * Definição de métodos para calcular as coordenadas dos pontos de uma caixa.
 *
 * @author Carlos Pereira - A61887
 * @author João Barreira  - A73831
 * @author Rafael Braga   - A61799
 * 
 * @version 12-05-2017
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
	float centerZ;  // Coordenada z do centro da caixa
	int numDiv;     // Número de divisões da caixa
	size_t index;   // Índice atual do conjunto de índices


	/**
	 * Gera os índices necessários das duas faces de um plano de uma box.
	 *
	 * @param indexes Vetor de índices.
	 */
	void generateIndexes(std::vector<size_t>& indexes)
	{
		int a = 0;
		int b = 0;
		size_t aux = index;

		// Ponteiros do relógio
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

		// Contrário aos ponteiros do relógio
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
	 * @param x         Coordenada x do vértice inicial (v1).
	 * @param y         Coordenada y do vértice inicial (v1).
	 * @param z         Coordenada z do vértice inicial (v1).
	 * @param vertices  Conjunto de vértices.
	 * @param normals   Conjunto de normais.
	 * @param texCoords Conjunto de coordenadas para uma textura.
	 * @param indexes   Conjunto de índices.
	 */
	void generateFacesXY(float x, float y, float z,
		                 std::vector<TripleFloat>& vertices,
	                     std::vector<TripleFloat>& normals,
		                 std::vector<TripleFloat>& texCoords,
		                 std::vector<size_t>& indexes)
	{
		int a = 0;
		int b = 0;
		float i = x;
		float j = y;

		// Para cada uma das duas faces, serão calculados 2 triângulos por divisão

		// Face da frente
		for (a = 0; a <= numDiv; a++, i += divX) {
			for (b = 0; b <= numDiv; b++, j += divY) {
				vertices.push_back(TripleFloat(i, j, z));
				normals.push_back(TripleFloat(0.0f, 0.0f, 1.0f));
				texCoords.push_back(TripleFloat((float)a / numDiv, (float)b / numDiv, 0.0f));
			}

			j = y;
		}

		i = x;
		j = y;

		// Face de trás
		for (a = 0; a <= numDiv; a++, i += divX) {
			for (b = 0; b <= numDiv; b++, j += divY) {
				vertices.push_back(TripleFloat(i, j, z - dimZ));
				normals.push_back(TripleFloat(0.0f, 0.0f, -1.0f));
				texCoords.push_back(TripleFloat((float)a / numDiv, (float)b / numDiv, 0.0f));
			}

			j = y;
		}
		
		generateIndexes(indexes);
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
	 * @param x         Coordenada x do vértice inicial (v1).
	 * @param y         Coordenada y do vértice inicial (v1).
	 * @param z         Coordenada z do vértice inicial (v1).
	 * @param vertices  Conjunto de vértices.
	 * @param normals   Conjunto de normais.
	 * @param texCoords Conjunto de coordenadas para uma textura.
	 * @param indexes   Conjunto de índices.
	 */
	void generateFacesXZ(float x, float y, float z,
		                 std::vector<TripleFloat>& vertices,
		                 std::vector<TripleFloat>& normals,
		                 std::vector<TripleFloat>& texCoords,
		                 std::vector<size_t>& indexes)
	{
		int a = 0;
		int b = 0;
		float i = x;
		float j = z;

		// Para cada uma das duas faces, serão calculados 2 triângulos por 
		// divisão

		// Face de baixo
		for (a = 0; a <= numDiv; a++, i += divX) {
			for (b = 0; b <= numDiv; b++, j += divZ) {
				vertices.push_back(TripleFloat(i, y - dimY, j));
				normals.push_back(TripleFloat(0.0f, -1.0f, 0.0f));
				texCoords.push_back(TripleFloat((float)b / numDiv, (float)a / numDiv, 0.0f));
			}

			j = z;
		}

		i = x;
		j = z;

		// Face de cima
		for (a = 0; a <= numDiv; a++, i += divX) {
			for (b = 0; b <= numDiv; b++, j += divZ) {
				vertices.push_back(TripleFloat(i, y, j));
				normals.push_back(TripleFloat(0.0f, 1.0f, 0.0f));
				texCoords.push_back(TripleFloat((float)b / numDiv, (float)a / numDiv, 0.0f));
			}

			j = z;
		}

		generateIndexes(indexes);
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
	 * @param x         Coordenada x do vértice inicial (v1).
	 * @param y         Coordenada y do vértice inicial (v1).
	 * @param z         Coordenada z do vértice inicial (v1).
	 * @param vertices  Conjunto de vértices.
	 * @param normals   Conjunto de normais.
	 * @param texCoords Conjunto de coordenadas para uma textura.
	 * @param indexes   Conjunto de índices.
	 */
	void generateFacesYZ(float x, float y, float z,
		                 std::vector<TripleFloat>& vertices,
		                 std::vector<TripleFloat>& normals,
		                 std::vector<TripleFloat>& texCoords,
		                 std::vector<size_t>& indexes)
	{
		int a = 0;
		int b = 0;
		float i = y;
		float j = z;

		// Para cada uma das duas faces, serão calculados 2 triângulos por 
		// divisão

		// Face da direita
		for (a = 0; a <= numDiv; a++, i += divY) {
			for (b = 0; b <= numDiv; b++, j += divZ) {
				vertices.push_back(TripleFloat(x, i, j));
				normals.push_back(TripleFloat(1.0f, 0.0f, 0.0f));
				texCoords.push_back(TripleFloat((float)b / numDiv, (float)a / numDiv, 0.0f));
			}

			j = z;
		}

		i = y;
		j = z;

		// Face da esquerda
		for (a = 0; a <= numDiv; a++, i += divY) {
			for (b = 0; b <= numDiv; b++, j += divZ) {
				vertices.push_back(TripleFloat(x - dimX, i, j));
				normals.push_back(TripleFloat(-1.0f, 0.0f, 0.0f));
				texCoords.push_back(TripleFloat((float)b / numDiv, (float)a / numDiv, 0.0f));
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
		dimX = dimY = dimZ = divX = divY = divZ = 0.0f;
		centerX = centerY = centerZ = 0.0f;
		numDiv = 0;
		index = 0;
	}


	/**
	 * Construtor por parâmetros.
	 *
	 * @param dimX Dimensão da caixa no eixo dos xx.
	 * @param dimY Dimensão da caixa no eixo dos yy.
	 * @param dimZ Dimensão da caixa no eixo dos zz.
	 * @param numDiv Número de divisões da caixa.
	 */
	BoxImpl(float dimX, float dimY, float dimZ, int numDiv)
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
		centerX = dimX / 2.0f;
		centerY = dimY / 2.0f;
		centerZ = dimZ / 2.0f;

		index = 0;
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
	int getNumDiv(void)
	{
		return numDiv;
	}


	/**
	 * Altera o valor da dimensão da caixa no eixo dos xx.
	 */
	void setDimX(float dimX)
	{
		divX = dimX / ((float)numDiv);
		centerX = dimX / 2.0f;
		this->dimX = dimX;
	}


	/**
	 * Altera o valor da dimensão da caixa no eixo dos yy.
	 */
	void setDimY(float dimY)
	{
		divY = dimY / ((float)numDiv);
		centerY = dimY / 2.0f;
		this->dimY = dimY;
	}


	/**
	 * Altera o valor da dimensão da caixa no eixo dos zz.
	 */
	void setDimZ(float dimZ)
	{
		divZ = dimZ / ((float)numDiv);
		centerZ = dimZ / 2.0f;
		this->dimZ = dimZ;
	}


	/**
	 * Altera o número de divisões da caixa.
	 */
	void setNumDiv(int numDiv)
	{
		divX = dimX / ((float)numDiv);
		divY = dimY / ((float)numDiv);
		divZ = dimZ / ((float)numDiv);

		centerX = dimX / 2.0f;
		centerY = dimY / 2.0f;
		centerZ = dimZ / 2.0f;

		this->numDiv = numDiv;
	}


	/**
	 * Gera o conjunto de vértices de uma box, bem como o conjunto de índices
	 * associado a este vetor.
	 *
	 * @param vertices  Conjunto de vértices.
	 * @param normals   Conjunto de normais.
	 * @param texCoords Conjunto de coordenadas para uma textura.
	 * @param indexes   Conjunto de índices.
	 */
	void generateBox(std::vector<TripleFloat>& vertices,
		             std::vector<TripleFloat>& normals,
		             std::vector<TripleFloat>& texCoords,
		             std::vector<size_t>& indexes)
	{
		generateFacesXY(-centerX, -centerY, dimZ - centerZ, vertices, normals, texCoords, indexes);
		generateFacesXZ(-centerX, dimY - centerY, -centerZ, vertices, normals, texCoords, indexes);
	    generateFacesYZ(dimX - centerX, -centerY, -centerZ, vertices, normals, texCoords, indexes);
	}


	/**
	 * Destrutor por defeito.
	 */
	~BoxImpl(void) = default;
};


/**
 * Construtor por defeito.
 */
Box::Box(void) 
{
	pimpl = new BoxImpl();
} 


/**
 * Construtor por parâmetros.
 *
 * @param dimX Dimensão da caixa no eixo dos xx.
 * @param dimY Dimensão da caixa no eixo dos yy.
 * @param dimZ Dimensão da caixa no eixo dos zz.
 * @param numDiv Número de divisões da caixa.
 */
Box::Box(float dimX, float dimY, float dimZ, int numDiv)
{
	// O número de divisões da caixa tem que ser superior a 1
	numDiv = (numDiv < 1) ?	1 : numDiv;

	// Não faz sentido uma dimensão ter um valor negativo
	dimX = (dimX < 0.0f) ? 0.0f: dimX;
	dimY = (dimY < 0.0f) ? 0.0f : dimY;
	dimZ = (dimZ < 0.0f) ? 0.0f : dimZ;

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
int Box::getNumDiv(void)
{
	return pimpl->getNumDiv();
}


/**
 * Altera o valor da dimensão da caixa no eixo dos xx.
 */
void Box::setDimX(float dimX)
{
	dimX = (dimX < 0.0f) ? 0.0f : dimX;
	pimpl->setDimX(dimX);
}


/**
 * Altera o valor da dimensão da caixa no eixo dos yy.
 */
void Box::setDimY(float dimY)
{
	dimY = (dimY < 0.0f) ? 0.0f : dimY;
	pimpl->setDimY(dimY);
}


/**
 * Altera o valor da dimensão da caixa no eixo dos zz.
 */
void Box::setDimZ(float dimZ)
{
	dimZ = (dimZ < 0.0f) ? 0.0f : dimZ;
	pimpl->setDimZ(dimZ);
}


/**
 * Altera o número de divisões da caixa.
 */
void Box::setNumDiv(int numDiv)
{
	numDiv = (numDiv < 1) ? 1 : numDiv;
	pimpl->setNumDiv(numDiv);
}


/**
 * Método que cálcula todos as coordenadas de todos os pontos de uma caixa.
 */
void Box::generateVertices(void)
{
	std::vector<TripleFloat> vertices;
	std::vector<TripleFloat> normals;
	std::vector<TripleFloat> texCoords;
	std::vector<size_t> indexes;

	pimpl->generateBox(vertices, normals, texCoords, indexes);

	for (size_t i = 0; i < vertices.size(); i++) {
		addVertex(vertices.at(i));
		addNormal(normals.at(i));
		addTexCoord(texCoords.at(i));
	}

	for (size_t i = 0; i < indexes.size(); i++) {
		addIndex(indexes.at(i));
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