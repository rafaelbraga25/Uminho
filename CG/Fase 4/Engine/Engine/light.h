/**
 * @file light.h
 * 
 * @brief M�dulo que apresenta m�todos para a defini��o de uma luz em 
 *        OpenGL.
 *
 *
 * @author Carlos Pereira - A61887
 * @author Jo�o Barreira  - A73831
 * @author Rafael Braga   - A61799
 *
 * @version 12-05-2017
 */


#ifndef light_h
#define light_h


#include "glOperation.h"
#include "tripleFloat.h"


class Light : public GLOperation {

	class LightImpl;
	LightImpl* pimpl;

	static int currentLight;

public:

	/**
	 * Construtor por defeito.
	 */
	Light(void);


	/**
	 * Construtor por par�metros.
	 *
	 * @param pos       Posi��o da luz.
	 * @param diff      Cor difusa da luz.
	 * @param spec      Cor especular da luz.
	 * @param ambt      Cor ambiente da luz.
	 * @param constant  Atenua��o constante.
	 * @param linear    Atenua��o linear.
	 * @param quadratic Atenua��o quadratica.
	 */
	Light(TripleFloat pos, TripleFloat diff, TripleFloat spec, TripleFloat ambt,
		  float constant, float linear, float quadratic);


	/**
	 * Construtor de c�pia.
	 *
	 * @param l Objeto da classe Light a copiar.
	 */
	Light(const Light& l);


	/**
	 * Devolve a posi��o da luz.
	 */
	TripleFloat getPos(void);


	/**
	 * Devolve a cor difusa da luz.
	 */
	TripleFloat getDiff(void);


	/**
	 * Devolve a cor especular
	 */
	TripleFloat getSpec(void);


	/**
	 * Devolve a cor ambiente da luz.
	 */
	TripleFloat getAmbt(void);


	/**
	 * Devolve o valor da atenua��o constante.
	 */
	float getConstant(void);


	/**
	 * Devolve o valor da atenua��o linear.
	 */
	float getLinear(void);


	/**
	 * Devolve o valor da atenua��o quadratica.
	 */
	float getQuadratic(void);


	/**
	 * Altera a posi��o da luz.
	 */
	void setPos(TripleFloat);


	/**
	 * Altera a cor difusa da luz.
	 */
	void setDiff(TripleFloat);


	/**
	 * Altera a cor especular da luz.
	 */
	void setSpec(TripleFloat);


	/**
	 * Altera a cor ambiente da luz.
	 */
	void setAmbt(TripleFloat);


	/**
	 * Altera o valor da atenua��o constante.
	 */
	void setConstant(float);


	/**
	 * Altera o valor da atenua��o linear.
	 */
	void setLinear(float);


	/**
	 * Altera o valor da atenua��o quadratica.
	 */
	void setQuadratic(float);


	/**
	 * Destrutor da classe Light.
	 */
	virtual ~Light(void);


protected:

	/**
	 * Devolve o n�mero da luz atual (LIGHT0..LIGHT7).
	 */
	static GLenum getLight(void);


	/**
	 * Atualiza a luz atual.
	 */
	static void updateCurrentLight(void);

};


#endif
