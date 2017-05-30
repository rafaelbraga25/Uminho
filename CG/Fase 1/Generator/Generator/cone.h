/**
 * @file cone.h
 *
 * @brief M�dulo que apresenta m�todos para calcular as coordenadas dos pontos 
 *        de um cone a partir de tri�ngulos.
 *  
 * As coordenadas s�o calculadas de maneira que, pela regra da m�o direita,
 * todas as superf�cies (lateral e base) fiquem para fora.
 *
 * @author Carlos Pereira - A61887
 * @author Jo�o Barreira  - A73831
 * @author Rafael Braga   - A61799
 */


#ifndef cone_h
#define cone_h


#include "primitive.h"


class Cone : public Primitive {
	class ConeImpl;
	ConeImpl* pimpl;

public:

	/**
	 * Construtor por defeito.
	 */
	Cone(void);


	/**
	 * Construtor por par�metros.
	 *
	 * N�o s�o permitidos valores negativos para o raio e a altura. O n�mero
	 * m�nimo de slices e stacks � 1.
	 * Os v�rtices do cone s�o calculados automaticamente ap�s a 
	 * inicializa��o dos par�metros deste.
	 *
	 * @param radius Raio da base do cone
	 * @param height Altura do cone
	 * @param slices N�mero de slices a utilizar
	 * @param stacks N�mero de stacks a utilizar
	 */
	Cone(float radius, float height, size_t slices, size_t stacks);
	

	/**
	 * Construtor de c�pia.
	 *
	 * @param c Objeto da classe Cone a ser copiado.
	 */
	Cone(const Cone& c);


	/**
	 * Devolve o valor do raio da base.
	 */
	float getRadius(void);
	
	
	/**
	 * Devolve a altura do cone.
	 */
	float getHeight(void);


	/**
	 * Devolve o n�mero de stacks.
	 */
	size_t getStacks(void);


	/**
	 * Devolve o n�mero de slices.
	 */
	size_t getSlices(void);


	/**
	 * Altera o valor do raio.
	 */
	void setRadius(float);


	/**
	 * Altera o valor da altura.
	 */
	void setHeight(float);


	/**
	 * Altera o n�mero de stacks.
	 */
	void setStacks(size_t);


	/**
	 * Altera o n�mero se slices.
	 */
	void setSlices(size_t);


	/**
	 * M�todo que c�lcula todos as coordenadas de todos os pontos de um cone.
	 */
	void generateVertices(void);


	/**
	 * Destrutor da classe Cone.
	 */
	~Cone(void);
};

#endif