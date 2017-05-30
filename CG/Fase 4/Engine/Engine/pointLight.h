/**
 * @file pointLight.h
 * 
 * @brief M�dulo que apresenta m�todos para a defini��o de uma luz do tipo
 *        point em OpenGL.
 *
 *
 * @author Carlos Pereira - A61887
 * @author Jo�o Barreira  - A73831
 * @author Rafael Braga   - A61799
 *
 * @version 12-05-2017
 */


#ifndef pointLight_h
#define pointLight_h


#include "light.h"


class PointLight : public Light {

public:

	/**
	 * Construtor por defeito.
	 */
	PointLight(void);


	/**
	 * Construtor por par�metros.
	 *
	 * @param pos       Posi��o da luz.
	 * @param diff      Cor difusa da luz.
	 * @param spec      Cor especular da luz.
	 * @param ambt      Cor ambiente da luz.
	 * @param constant  Atenua��o constante.
	 * @param linear    Atenua��o linear.
	 * @param quadratic Atenua��o quadr�tica.
	 */
	PointLight(TripleFloat pos, TripleFloat diff, TripleFloat spec, TripleFloat ambt,
		       float constant, float linear, float quadratic);


	/**
	 * Construtor de c�pia.
	 *
	 * @param p Objeto da classe PointLight a copiar.
	 */
	PointLight(const PointLight& p);


	/**
	 * Apresenta uma luz do tipo point em OpenGL.
	 */
	void execute(void);


	/**
	 * Apresenta uma luz do tipo point em OpenGL.
	 */
	void execute(FrustumCulling*);


	/**
	 * Destrutor da classe PointLight.
	 */
	~PointLight(void);
};


#endif 

