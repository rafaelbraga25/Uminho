/**
 * @file box.h
 *
 * @brief Módulo que apresenta métodos para calcular as coordenadas dos pontos 
 *        de uma caixa (cubo ou paralelipípedo) a partir de triângulos.
 *
 * As coordenadas são calculadas de maneira que, pela regra da mão direita,
 * as faces da caixa fiquem voltadas para fora.
 *
 * @author Carlos Pereira - A61887
 * @author João Barreira  - A73831
 * @author Rafael Braga   - A61799
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
	 * Construtor por parâmetros. O número de divisões é uma por defeito caso
	 * o construtor não receba nenhum valor de numDiv. Se o valor de numDiv
	 * recebido for nulo ou negativo, o valor deste é convertido para uma
	 * divisão. Os valores das dimensões não podem ser negativos.
	 * Os vértices da caixa são calculados automaticamente após a
	 * inicialização dos parâmetros desta.
	 *
	 * @param dimX   Dimensão do plano no eixo dos xx
	 * @param dimY   Dimensão do plano no eixo dos yy
	 * @param dimZ   Dimensão do plano no eixo dos zz
	 * @param numDiv Número de divisões da caixa
	 */
	Box(float dimX, float dimY, float dimZ, size_t numDiv = 1);


	/**
	 * Construtor de cópia.
	 *
	 * @param b Objeto da classe Box a ser copiado. 
	 */
	Box(const Box& b);


	/**
	 * Devolve o valor da dimensão da caixa no eixo dos xx.
	 */
	float getDimX(void);


	/**
	 * Devolve o valor da dimensão da caixa no eixo dos yy.
	 */
	float getDimY(void);


	/**
	 * Devolve o valor da dimensão da caixa no eixo dos zz.
	 */
	float getDimZ(void);


	/**
	 * Devolve o número de divisões da caixa.
	 */
	size_t getNumDiv(void);


	/**
	 * Altera o valor da dimensão da caixa no eixo dos xx.
	 */
	void setDimX(float);


	/**
	 * Altera o valor da dimensão da caixa no eixo dos yy.
	 */
	void setDimY(float);


	/**
	 * Altera o valor da dimensão da caixa no eixo dos zz.
	 */
	void setDimZ(float);


	/**
	 * Altera o número de divisões da caixa.
	 */
	void setNumDiv(size_t);


	/**
	 * Método que cálcula todos as coordenadas de todos os vértices de uma 
	 * caixa.
	 */
	void generateVertices(void);


	/**
	 * Destrutor da classe Box.
	 */
	~Box(void);
};

#endif
