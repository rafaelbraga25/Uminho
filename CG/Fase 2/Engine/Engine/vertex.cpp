/**
 * @file vertex.cpp
 *
 * Defini��o dos m�todos da classe Vertex.
 *
 * @author Carlos Pereira - A61887
 * @author Jo�o Barreira  - A73831
 * @author Rafael Braga   - A61799
 */


#include <vector>
#include <sstream>
#include "vertex.h"


class Vertex::VertexImpl {
	float x;  // Coordenada x de um v�rtice
	float y;  // Coordenada y de um v�rtice
	float z;  // Coordenada z de um v�rtice

public:

	/**
	 * Construtor por defeito.
	 */
	VertexImpl(void)
	{
		x = y = z = 0;
	}


	/**
	 * Construtor por par�metros.
	 *
	 * @param x Coordenada x de um v�rtice.
	 * @param y Coordenada y de um v�rtice.
	 * @param z Coordenada z de um v�rtice.
	 */
	VertexImpl(float x, float y, float z)
	{
		this->x = x;
		this->y = y;
		this->z = z;
	}


	/**
	 * Devolve a coordenada x de um v�rtice.
	 */
	float getX(void)
	{
		return x;
	}


	/**
	 * Devolve a coordenada y de um v�rtice.
	 */
	float getY(void)
	{
		return y;
	}


	/**
	 * Devolve a coordenada z de um v�rtice.
	 */
	float getZ(void)
	{
		return z;
	}


	/**
	 * Altera o valor da coordenada x de um v�rtice.
	 */
	void setX(float x)
	{
		this->x = x;
	}


	/**
	 * Altera o valor da coordenada y de um v�rtice.
	 */
	void setY(float y)
	{
		this->y = y;
	}


	/**
	 * Altera o valor da coordenada z de um v�rtice.
	 */
	void setZ(float z)
	{
		this->z = z;
	}


	/**
	 * Adiciona �s coordenadas de um v�rtice os valores das coordenadas de
	 * outro v�rtice.
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
	 * Devolve uma representa��o textual da classe Vertex.
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
 * Construtor por par�metros.
 *
 * @param x Coordenada x.
 * @param y Coordenada y.
 * @param z Coordenada z.
 */
Vertex::Vertex(float x, float y, float z)
	: pimpl{ new VertexImpl(x, y, z) } {}


/**
 * Construtor de c�pia da classe Vertex.
 *
 * @param v Objeto da classe Vertex a ser copiado.
 */
Vertex::Vertex(const Vertex& v)
{
	pimpl = new VertexImpl(v.pimpl->getX(), v.pimpl->getY(), v.pimpl->getZ());
}


/**
 * Devolve a coordenada x de um v�rtice.
 */
float Vertex::getX(void)
{
	return pimpl->getX();
}


/**
 * Devolve a coordenada y de um v�rtice.
 */
float Vertex::getY(void)
{
	return pimpl->getY();
}


/**
 * Devolve a coordenada z de um v�rtice.
 */
float Vertex::getZ(void)
{
	return pimpl->getZ();
}


/**
 * Altera o valor da coordenada x de um v�rtice.
 */
void Vertex::setX(float x)
{
	pimpl->setX(x);
}


/**
 * Altera o valor da coordenada y de um v�rtice.
 */
void Vertex::setY(float y)
{
	pimpl->setY(y);
}


/**
 * Altera o valor da coordenada z de um v�rtice.
 */
void Vertex::setZ(float z)
{
	pimpl->setZ(z);
}


/**
 * Adiciona �s coordenadas de um v�rtice os valores das coordenadas de
 * outro v�rtice.
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
 * Devolve uma representa��o textual da classe Vertex.
 */
std::string Vertex::toString(void)
{
	return pimpl->toString();
}


/**
 * Destrutor da classe Vertex.
 * Liberta a mem�ria alocada pelo apontador da parte privada da classe Vertex.
 */
Vertex::~Vertex(void)
{
	if (pimpl != NULL) {
		delete pimpl;
		pimpl = NULL;
	}
}
