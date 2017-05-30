/**
 * @file directionalLight.h
 *
 * @brief Módulo que apresenta métodos para a definição de uma luz direcional
 *        em OpenGL.
 *
 *
 * @author Carlos Pereira - A61887
 * @author João Barreira  - A73831
 * @author Rafael Braga   - A61799
 *
 * @version 12-05-2017
 */


#ifndef directionalLight_h
#define directionalLight_h


#include "light.h"


class DirectionalLight : public Light {

public:

	/**
	 * Construtor por defeito.
	 */
	DirectionalLight(void);


	/**
	 * Construtor por parâmetros.
	 *
	 * @param pos       Posição da luz.
	 * @param diff      Cor difusa da luz.
	 * @param spec      Cor especular da luz.
	 * @param ambt      Cor ambiente da luz.
	 * @param constant  Atenuação constante.
	 * @param linear    Atenuação linear.
	 * @param quadratic Atenuação quadrática.
	 */
	DirectionalLight(TripleFloat pos, TripleFloat diff, TripleFloat spec, TripleFloat ambt,
		             float constant, float linear, float quadratic);


	/**
	 * Construtor de cópia.
	 *
	 * @param d Objeto da classe DirectionalLight a copiar.
	 */
	DirectionalLight(const DirectionalLight& d);


	/**
	 * Apresenta uma luz direcional em OpenGL.
	 */
	void execute(void);


	/**
	 * Apresenta uma luz direcional em OpenGL.
	 */
	void execute(FrustumCulling*);


	/**
	 * Destrutor da classe DirectionalLight.
	 */
	~DirectionalLight(void);
};


#endif 

