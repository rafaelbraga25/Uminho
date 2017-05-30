/**
 * @file spotLight.h
 *
 * @brief M�dulo que apresenta m�todos para a defini��o de uma luz do tipo
 *        spot em OpenGL.
 *
 *
 * @author Carlos Pereira - A61887
 * @author Jo�o Barreira  - A73831
 * @author Rafael Braga   - A61799
 *
 * @version 12-05-2017
 */


#ifndef spotLight_h
#define spotLight_h


#include "light.h"


class SpotLight : public Light {

	class SpotLightImpl;
	SpotLightImpl* pimpl;


public:

	/**
	 * Construtor por defeito.
	 */
	SpotLight(void);


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
	 * @param spotDir   Dire��o do spot.
	 * @param cutoff    �ngulo do spot.
	 * @param exponent  Expoente do spot.
	 */
	SpotLight(TripleFloat pos, TripleFloat diff, TripleFloat spec, TripleFloat ambt,
		      float constant, float linear, float quadratic,
		      TripleFloat spotDir, float cutoff, float exponent);


	/**
	 * Construtor de c�pia.
	 *
	 * @param s Objeto da classe SpotLight a copiar.
	 */
	SpotLight(const SpotLight& s);


	/**
	 * Devolve a dire��o do spot.
	 */
	TripleFloat getSpotDir(void);


	/**
	 * Devolve o �ngulo do spot.
	 */
	float getCutoff(void);


	/**
	 * Devolve o expoente do spot.
	 */
	float getExponent(void);


	/**
	 * Altera a dire��o do spot.
	 */
	void setSpotDir(TripleFloat);


	/**
	 * Altera o �ngulo do spot.
	 */
	void setCutoff(float);


	/**
	 * Altera o expoente do spot.
	 */
	void setExponent(float);


	/**
	 * Apresenta uma luz do tipo spot em OpenGL.
	 */
	void execute(void);


	/**
	 * Apresenta uma luz do tipo spot em OpenGL.
	 */
	void execute(FrustumCulling*);


	/**
	 * Destrutor da classe SpotLight.
	 */
	~SpotLight(void);
};


#endif 


