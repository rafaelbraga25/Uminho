/**
 * @file plane.h
 *
 * @brief Módulo que apresenta métodos para calcular as coordenadas dos pontos 
 *        de um plano a partir de triângulos.
 *
 * As coordenadas são calculadas de maneira que, pela regra da mão direita,
 * a superfície do plano fique voltada para cima.
 *
 * @author Carlos Pereira - A61887
 * @author João Barreira  - A73831
 * @author Rafael Braga   - A61799
 *
 * @version 4-4-2017
 */


#ifndef plane_h
#define plane_h


#include "primitive.h"


class Plane : public Primitive {
	class PlaneImpl;
	PlaneImpl* pimpl;

public:

	/**
	 * Construtor por defeito.
	 */
	Plane(void);


	/**
	 * Construtor por parâmetros. Caso algum valor de uma dimensão seja 
	 * negativo, o valor dessa dimensão é convertido para zero.
	 * Os vértices do plano são calculados automaticamente após a 
	 * inicialização dos parâmetros deste.
	 *
	 * @param dimX Dimensão do plano no eixo dos xx.
	 * @param dimZ Dimensão do plano no eixo dos zz.
	 */
	Plane(float dimX, float dimZ);


	/**
	 * Construtor de cópia.
	 *
	 * @param p Objeto da classe Plane a ser copiado.
	 */
	Plane(const Plane& p);
	

	/**
	 * Devolve o valor da dimensão do plano no eixo dos xx.
	 */
	float getDimX(void);


	/**
	 * Devolve o valor da dimensão do plano no eixo dos zz.
	 */
	float getDimZ(void);
	

	/**
	 * Altera o valor da dimensão do plano no eixo dos xx.
	 */
	void setDimX(float);


	/**
	 * Altera o valor da dimensão do plano no eixo dos zz.
	 */
	void setDimZ(float);


	/**
	 * Método que cálcula todos as coordenadas de todos os vértices de um 
	 * plano.
	 */
	void generateVertices(void);


	/**
	 * Destrutor da classe Plane.
	 */
	~Plane(void);
};

#endif
