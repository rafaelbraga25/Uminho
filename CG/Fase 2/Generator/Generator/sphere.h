/**
 * @file sphere.h
 *
 * @brief Módulo que apresenta métodos para calcular as coordenadas dos pontos 
 *        de uma esfera a partir de triângulos.
 *
 *  As coordenadas são calculadas de maneira que, pela regra da mão direita,
 *  a superfície da esfera fique para fora.
 *
 *  @author Carlos Pereira - A61887
 *  @author João Barreira  - A73831
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
	 * Construtor por parâmetros. O número mínimo de slices e stacks é um.
	 * O valor do raio não pode ser negativo. 
	 * Os vértices da esfera são calculados automaticamente após a 
	 * inicialização dos parâmetros desta.
	 *
	 * @param radius Raio da esfera
	 * @param slices Número de slices a utilizar
	 * @param stacks Número de stacks a utilizar
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
	 * Devolve o número de stacks.
	 */
	size_t getStacks(void);


	/**
	 * Devolve o número de slices.
	 */
	size_t getSlices(void);


	/**
	 * Altera o valor do raio.
	 */
	void setRadius(float);


	/**
	 * Altera o número de stacks.
	 */
	void setStacks(size_t);


	/**
	 * Altera o número se slices.
	 */
	void setSlices(size_t);


	/**
	 * Método que cálcula todos as coordenadas de todos os vértices de uma 
	 * esfera.
	 */
	void generateVertices(void);


	/**
	 * Destrutor da classe Sphere.
	 */
	~Sphere(void);
};

#endif