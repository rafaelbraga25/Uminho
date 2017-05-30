/**
 * @file plane.h
 *
 * @brief M�dulo que apresenta m�todos para calcular as coordenadas dos pontos 
 *        de um plano a partir de tri�ngulos.
 *
 * As coordenadas s�o calculadas de maneira que, pela regra da m�o direita,
 * a superf�cie do plano fique voltada para cima.
 *
 * @author Carlos Pereira - A61887
 * @author Jo�o Barreira  - A73831
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
	 * Construtor por par�metros. Caso algum valor de uma dimens�o seja 
	 * negativo, o valor dessa dimens�o � convertido para zero.
	 * Os v�rtices do plano s�o calculados automaticamente ap�s a 
	 * inicializa��o dos par�metros deste.
	 *
	 * @param dimX Dimens�o do plano no eixo dos xx.
	 * @param dimZ Dimens�o do plano no eixo dos zz.
	 */
	Plane(float dimX, float dimZ);


	/**
	 * Construtor de c�pia.
	 *
	 * @param p Objeto da classe Plane a ser copiado.
	 */
	Plane(const Plane& p);
	

	/**
	 * Devolve o valor da dimens�o do plano no eixo dos xx.
	 */
	float getDimX(void);


	/**
	 * Devolve o valor da dimens�o do plano no eixo dos zz.
	 */
	float getDimZ(void);
	

	/**
	 * Altera o valor da dimens�o do plano no eixo dos xx.
	 */
	void setDimX(float);


	/**
	 * Altera o valor da dimens�o do plano no eixo dos zz.
	 */
	void setDimZ(float);


	/**
	 * M�todo que c�lcula todos as coordenadas de todos os v�rtices de um 
	 * plano.
	 */
	void generateVertices(void);


	/**
	 * Destrutor da classe Plane.
	 */
	~Plane(void);
};

#endif
