/**
 * @file plane.cpp
 *
 * Definição de métodos para calcular as coordenadas dos pontos de um plano.
 *
 * @author Carlos Pereira - A61887 
 * @author João Barreira  - A73831
 * @author Rafael Braga   - A61799
 */


#include "plane.h"


class Plane::PlaneImpl {
	float dimX;  // Dimensão do plano no eixo dos xx
	float dimZ;  // Dimensão do plano no eixo dos zz

public:
	
	/**
	 * Construtor por defeito.
	 */
	PlaneImpl(void)
	{
		dimX = dimZ = 0;
	}


	/**
	 * Construtor por parâmetros.
	 *
	 * @param dimX Dimensão do plano no eixo dos xx.
	 * @param dimZ Dimensão do plano no eixo dos zz.
	 */
	PlaneImpl(float dimX, float dimZ)
	{
		this->dimX = dimX;
		this->dimZ = dimZ;
	}


	/**
	 * Devolve o valor da dimensão do plano no eixo dos xx.
	 */
	float getDimX(void)
	{
		return dimX;
	}


	/**
	 * Devolve o valor da dimensão do plano no eixo dos zz.
	 */
	float getDimZ(void)
	{
		return dimZ;
	}


	/**
	 * Altera o valor da dimensão do plano no eixo dos xx.
	 */
	void setDimX(float dimX)
	{
		this->dimX = dimX;
	}


	/**
	 * Altera o valor da dimensão do plano no eixo dos zz.
	 */
	void setDimZ(float dimZ)
	{
		this->dimZ = dimZ;
	}


	/**
	 * Destrutor por defeito.
	 */
	~PlaneImpl(void) = default;
};


/**
 * Construtor por defeito.
 */
Plane::Plane(void) : pimpl{ new PlaneImpl() } {}


/**
 * Construtor por parâmetros. 
 *
 * @param dimX Dimensão do plano no eixo dos xx.
 * @param dimZ Dimensão do plano no eixo dos zz.
 */
Plane::Plane(float dimX, float dimZ)
{
	dimX = (dimX < 0) ? 0 : dimX;
	dimZ = (dimZ < 0) ? 0 : dimZ;

	pimpl = new PlaneImpl(dimX, dimZ);

	generateVertices();
}


/**
 * Construtor de cópia.
 *
 * @param p Objeto da classe Plane a ser copiado.
 */
Plane::Plane(const Plane& p)
{
	pimpl = new PlaneImpl(p.pimpl->getDimX(), p.pimpl->getDimZ());
}


/**
 * Devolve o valor da dimensão do plano no eixo dos xx.
 */
float Plane::getDimX(void)
{
	return pimpl->getDimX();
}


/**
 * Devolve o valor da dimensão do plano no eixo dos zz.
 */
float Plane::getDimZ(void)
{
	return pimpl->getDimZ();
}


/**
 * Altera o valor da dimensão do plano no eixo dos xx.
 */
void Plane::setDimX(float dimX)
{
	dimX = (dimX < 0) ? 0 : dimX;
	pimpl->setDimX(dimX);
}


/**
 * Altera o valor da dimensão do plano no eixo dos zz.
 */
void Plane::setDimZ(float dimZ)
{
	dimZ = (dimZ < 0) ? 0 : dimZ;
	pimpl->setDimZ(dimZ);
}


/**
 * Método que cálcula todos as coordenadas de todos os pontos de um plano.
 *
 * v2------v1
 *  |      |
 *  |      |
 *  |      |
 *  v3-----v4
 */
void Plane::generateVertices(void)
{
	// Centrar o plano na origem
	float x = pimpl->getDimX() / 2; 
	float z = pimpl->getDimZ() / 2;

	// Um plano apenas contém 2 triângulos

	// Vértices v1-v2-v3
	addVertex(Vertex(x, 0, -z));
	addVertex(Vertex(-x, 0, -z));
	addVertex(Vertex(-x, 0, z));


	// Vértives v1-v3-v4
	addVertex(Vertex(x, 0, -z));
	addVertex(Vertex(-x, 0, z));
	addVertex(Vertex(x, 0, z));
}


/**
 * Destrutor da classe Plane.
 *
 * Liberta a memória ocupada pelo apontador para a parte privada da classe
 * Plane.
 */
Plane::~Plane(void)
{
	if (pimpl != NULL) {
		delete pimpl;
		pimpl = NULL;
	}
}







