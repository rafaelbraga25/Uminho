/**
 * @file sphere.h
 *
 * @brief M�dulo que apresenta m�todos para calcular as coordenadas dos pontos 
 *        de uma esfera a partir de tri�ngulos.
 *
 *  As coordenadas s�o calculadas de maneira que, pela regra da m�o direita,
 *  a superf�cie da esfera fique para fora.
 *
 *  @author Carlos Pereira - A61887
 *  @author Jo�o Barreira  - A73831
 *  @author Rafael Braga   - A61799
 */


#ifndef sphere_h
#define sphere_h


#include "primitive.h"


class Sphere : public Primitive {
	class SphereImpl;
	SphereImpl* pimpl;

public:

	/**
	 * Construtor por defeito.
	 */
	Sphere(void);


	/**
	 * Construtor por par�metros. O n�mero m�nimo de slices e stacks � um.
	 * O valor do raio n�o pode ser negativo. 
	 * Os v�rtices da esfera s�o calculados automaticamente ap�s a 
	 * inicializa��o dos par�metros desta.
	 *
	 * @param radius Raio da esfera
	 * @param slices N�mero de slices a utilizar
	 * @param stacks N�mero de stacks a utilizar
	 */
	Sphere(float radius, size_t slices, size_t stacks);


	/**
	 * Construtor a partir de outro objecto Sphere.
	 *
	 * @param s Objeto da classe Sphere a ser copiado.
	 */
	Sphere(const Sphere& s);


	/**
	 * Devolve o valor do raio da esfera.
	 */
	float getRadius(void);
	
	
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
	 * Altera o n�mero de stacks.
	 */
	void setStacks(size_t);


	/**
	 * Altera o n�mero se slices.
	 */
	void setSlices(size_t);


	/**
	 * M�todo que c�lcula todos as coordenadas de todos os v�rtices de uma 
	 * esfera.
	 */
	void generateVertices(void);


	/**
	 * Destrutor da classe Sphere.
	 */
	~Sphere(void);
};

#endif