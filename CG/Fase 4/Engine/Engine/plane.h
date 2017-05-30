/**
 * @file plane.h
 *
 * @brief M�dulo que apresenta m�todos para a defini��o de um plano. Um plano
 *        pode ser definido atrav�s de um ponto e de uma normal.
 *
 * @author Carlos Pereira - A61887
 * @author Jo�o Barreira  - A73831
 * @author Rafael Braga   - A61799
 * 
 * @version 12-05-2017
 */


#ifndef plane_h
#define plane_h


#include "tripleFloat.h"


class Plane {

	class PlaneImpl;
	PlaneImpl* pimpl;

public:

	/**
	 * Construtor por defeito.
	 */
	Plane(void);


	/**
	 * Construtor por par�metros.
	 * 
	 * @param normal Normal do plano.
	 * @param p      Ponto do plano.
	 */
	Plane(TripleFloat normal, TripleFloat p);


	/**
	 * Construtor de c�pia.
	 *
	 * @param p Objeto da classe Plane a copiar.
	 */
	Plane(const Plane& p);


	/**
	 * Devolve a normal do plano.
	 */
	TripleFloat getNormal(void);


	/**
	 * Devolve o ponto do plano.
	 */
	TripleFloat getP(void);


	/**
	 * Altera a normal do plano.
	 */
	void setNormal(TripleFloat);


	/**
	 * Altera o ponto do plano.
	 */
	void setP(TripleFloat);


	/**
	 * Altera o ponto e a normal do plano.
	 */
	void setNormalAndPoint(TripleFloat normal, TripleFloat p);


	/**
	 * Calcula a dist�ncia de um ponto ao plano.
	 */
	float distanceFromPoint(TripleFloat point);


	/**
	 * Destrutor.
	 */
	~Plane(void);
};


#endif
