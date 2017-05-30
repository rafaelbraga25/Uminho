/**
 * @file plane.cpp
 *
 * @brief Definição de todos os métodos para a definição de um plano. Um plano
 *        pode ser definido através de um ponto e de uma normal.
 *
 * @author Carlos Pereira - A61887
 * @author João Barreira  - A73831
 * @author Rafael Braga   - A61799
 *
 * @version 12-05-2017
 */


#include "plane.h"


class Plane::PlaneImpl {

	TripleFloat normal;  // Normal do plano
	TripleFloat p;       // Ponto do plano

public:

	/**
	 * Construtor por defeito.
	 */
	PlaneImpl(void) = default;


	/**
	 * Construtor por parâmetros.
	 *
	 * @param normal Normal do plano.
	 * @param p      Ponto do plano.
	 */
	PlaneImpl(TripleFloat normal, TripleFloat p)
	{
		this->normal.setF1(normal.getF1());
		this->normal.setF2(normal.getF2());
		this->normal.setF3(normal.getF3());

		this->p.setF1(p.getF1());
		this->p.setF2(p.getF2());
		this->p.setF3(p.getF3());
	}


	/**
	 * Devolve a normal do plano.
	 */
	TripleFloat getNormal(void)
	{
		return normal;
	}


	/**
	 * Devolve o ponto do plano.
	 */
	TripleFloat getP(void)
	{
		return p;
	}


	/**
	 * Altera a normal do plano.
	 */
	void setNormal(TripleFloat normal)
	{
		this->normal.setF1(normal.getF1());
		this->normal.setF2(normal.getF2());
		this->normal.setF3(normal.getF3());
	}


	/**
	 * Altera o ponto do plano.
	 */
	void setP(TripleFloat p)
	{
		this->p.setF1(p.getF1());
		this->p.setF2(p.getF2());
		this->p.setF3(p.getF3());
	}


	/**
	 * Destrutor.
	 */
	~PlaneImpl(void) = default;
};


/**
 * Construtor por defeito.
 */
Plane::Plane(void)
{
	pimpl = new PlaneImpl();
}


/**
 * Construtor por parâmetros.
 *
 * @param normal Normal do plano.
 * @param p      Ponto do plano.
 */
Plane::Plane(TripleFloat normal, TripleFloat p)
{
	pimpl = new PlaneImpl(normal, p);
}


/**
 * Construtor de cópia.
 *
 * @param p Objeto da classe Plane a copiar.
 */
Plane::Plane(const Plane& p)
{
	pimpl = new PlaneImpl(p.pimpl->getNormal(), p.pimpl->getP());
}


/**
 * Devolve a normal do plano.
 */
TripleFloat Plane::getNormal(void)
{
	return pimpl->getNormal();
}


/**
 * Devolve o ponto do plano.
 */
TripleFloat Plane::getP(void)
{
	return pimpl->getP();
}


/**
 * Altera a normal do plano.
 */
void Plane::setNormal(TripleFloat normal)
{
	pimpl->setNormal(normal);
}


/**
 * Altera o ponto do plano.
 */
void Plane::setP(TripleFloat p)
{
	pimpl->setP(p);
}


/**
 * Altera o ponto e a normal do plano.
 */
void Plane::setNormalAndPoint(TripleFloat normal, TripleFloat p)
{
	pimpl->setNormal(normal);
	pimpl->setP(p);
}


/**
 * Calcula a distância de um ponto ao plano.
 */
float Plane::distanceFromPoint(TripleFloat point)
{
	float d = getNormal().multWithScalar(-1.0f).dotProd(getP());

	return getNormal().dotProd(point) + d;
}


/**
 * Destrutor.
 */
Plane::~Plane(void)
{
	if (pimpl != NULL) {
		delete pimpl;
		pimpl = NULL;
	}
}