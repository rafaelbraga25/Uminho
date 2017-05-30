/**
 * @file box.h
 *
 * @brief M�dulo que apresenta m�todos para calcular as coordenadas dos pontos 
 *        de uma caixa (cubo ou paralelip�pedo) a partir de tri�ngulos.
 *
 * As coordenadas s�o calculadas de maneira que, pela regra da m�o direita,
 * as faces da caixa fiquem voltadas para fora.
 *
 * @author Carlos Pereira - A61887
 * @author Jo�o Barreira  - A73831
 * @author Rafael Braga   - A61799
 *
 * @version 8-4-2017
 */


#ifndef box_h
#define box_h


#include "primitive.h"


class Box : public Primitive {
	class BoxImpl;
	BoxImpl* pimpl;

public:

	/**
	 * Construtor por defeito.
	 */
	Box(void);


	/**
	 * Construtor por par�metros. O n�mero de divis�es � uma por defeito caso
	 * o construtor n�o receba nenhum valor de numDiv. Se o valor de numDiv
	 * recebido for nulo ou negativo, o valor deste � convertido para uma
	 * divis�o. Os valores das dimens�es n�o podem ser negativos.
	 * Os v�rtices da caixa s�o calculados automaticamente ap�s a
	 * inicializa��o dos par�metros desta.
	 *
	 * @param dimX   Dimens�o do plano no eixo dos xx
	 * @param dimY   Dimens�o do plano no eixo dos yy
	 * @param dimZ   Dimens�o do plano no eixo dos zz
	 * @param numDiv N�mero de divis�es da caixa
	 */
	Box(float dimX, float dimY, float dimZ, int numDiv = 1);


	/**
	 * Construtor de c�pia.
	 *
	 * @param b Objeto da classe Box a ser copiado. 
	 */
	Box(const Box& b);


	/**
	 * Devolve o valor da dimens�o da caixa no eixo dos xx.
	 */
	float getDimX(void);


	/**
	 * Devolve o valor da dimens�o da caixa no eixo dos yy.
	 */
	float getDimY(void);


	/**
	 * Devolve o valor da dimens�o da caixa no eixo dos zz.
	 */
	float getDimZ(void);


	/**
	 * Devolve o n�mero de divis�es da caixa.
	 */
	int getNumDiv(void);


	/**
	 * Altera o valor da dimens�o da caixa no eixo dos xx.
	 */
	void setDimX(float);


	/**
	 * Altera o valor da dimens�o da caixa no eixo dos yy.
	 */
	void setDimY(float);


	/**
	 * Altera o valor da dimens�o da caixa no eixo dos zz.
	 */
	void setDimZ(float);


	/**
	 * Altera o n�mero de divis�es da caixa.
	 */
	void setNumDiv(int);


	/**
	 * M�todo que c�lcula todos as coordenadas de todos os v�rtices de uma 
	 * caixa.
	 */
	void generateVertices(void);


	/**
	 * Destrutor da classe Box.
	 */
	~Box(void);
};

#endif
