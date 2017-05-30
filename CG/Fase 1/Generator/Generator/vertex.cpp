/**
 * @file vertex.cpp
 *
 * Definição dos métodos da classe Vertex.
 *
 * @author Carlos Pereira - A61887
 * @author João Barreira  - A73831
 * @author Rafael Braga   - A61799
 */


#include <vector>
#include <sstream>
#include "vertex.h"


class Vertex::VertexImpl {
	float x;  // Coordenada x de um vértice
	float y;  // Coordenada y de um vértice
	float z;  // Coordenada z de um vértice

public:

	/**
	 * Construtor por defeito.
	 */
	VertexImpl(void)
	{
		x = y = z = 0;
	}


	/**
	 * Construtor por parâmetros.
	 *
	 * @param x Coordenada x de um vértice.
	 * @param y Coordenada y de um vértice.
	 * @param z Coordenada z de um vértice.
	 */
	VertexImpl(float x, float y, float z)
	{
		this->x = x;
		this->y = y;
		this->z = z;
	}


	/**
	 * Devolve a coordenada x de um vértice.
	 */
	float getX(void)
	{
		return x;
	}


	/**
	 * Devolve a coordenada y de um vértice.
	 */
	float getY(void)
	{
		return y;
	}


	/**
	 * Devolve a coordenada z de um vértice.
	 */
	float getZ(void)
	{
		return z;
	}


	/**
	 * Altera o valor da coordenada x de um vértice.
	 */
	void setX(float x)
	{
		this->x = x;
	}


	/**
	 * Altera o valor da coordenada y de um vértice.
	 */
	void setY(float y)
	{
		this->y = y;
	}


	/**
	 * Altera o valor da coordenada z de um vértice.
	 */
	void setZ(float z)
	{
		this->z = z;
	}


	/**
	 * Adiciona às coordenadas de um vértice os valores das coordenadas de
	 * outro vértice.
	 *
	 * @param x Coordenada x
	 * @param y Coordenada y
	 * @param z Coordenada z
	 */
	void add(float x, float y, float z)
	{
		this->x += x;
		this->y += y;
		this->z += z;
	}


	/**
	 * Devolve uma representação textual da classe Vertex.
	 */
	std::string toString(void)
	{
		std::stringstream aux;

		aux << x << " " << y << " " << z;

		return aux.str();
	}


	/**
	 * Destrutor por defeito.
	 */
	~VertexImpl(void) = default;
};


/**
 * Construtor por defeito.
 */
Vertex::Vertex(void) : pimpl{ new VertexImpl() } {}


/**
 * Construtor por parâmetros.
 *
 * @param x Coordenada x.
 * @param y Coordenada y.
 * @param z Coordenada z.
 */
Vertex::Vertex(float x, float y, float z)
	: pimpl{ new VertexImpl(x, y, z) } {}


/**
 * Construtor de cópia da classe Vertex.
 *
 * @param v Objeto da classe Vertex a ser copiado.
 */
Vertex::Vertex(const Vertex& v)
{
	pimpl = new VertexImpl(v.pimpl->getX(), v.pimpl->getY(), v.pimpl->getZ());
}


/**
 * Devolve a coordenada x de um vértice.
 */
float Vertex::getX(void)
{
	return pimpl->getX();
}


/**
 * Devolve a coordenada y de um vértice.
 */
float Vertex::getY(void)
{
	return pimpl->getY();
}


/**
 * Devolve a coordenada z de um vértice.
 */
float Vertex::getZ(void)
{
	return pimpl->getZ();
}


/**
 * Altera o valor da coordenada x de um vértice.
 */
void Vertex::setX(float x)
{
	pimpl->setX(x);
}


/**
 * Altera o valor da coordenada y de um vértice.
 */
void Vertex::setY(float y)
{
	pimpl->setY(y);
}


/**
 * Altera o valor da coordenada z de um vértice.
 */
void Vertex::setZ(float z)
{
	pimpl->setZ(z);
}


/**
 * Adiciona às coordenadas de um vértice os valores das coordenadas de
 * outro vértice.
 *
 * @param x Coordenada x.
 * @param y Coordenada y.
 * @param z Coordenada z.
 */
void Vertex::add(float x, float y, float z)
{
	pimpl->add(x, y, z);
}


/**
 * Devolve uma representação textual da classe Vertex.
 */
std::string Vertex::toString(void)
{
	return pimpl->toString();
}


/**
 * Destrutor da classe Vertex.
 * Liberta a memória alocada pelo apontador da parte privada da classe Vertex.
 */
Vertex::~Vertex(void)
{
	if (pimpl != NULL) {
		delete pimpl;
		pimpl = NULL;
	}
}
