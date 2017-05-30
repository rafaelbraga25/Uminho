/**
 * @file cone.h
 *
 * @brief Módulo que apresenta métodos para calcular as coordenadas dos pontos 
 *        de um cone a partir de triângulos.
 *  
 * As coordenadas são calculadas de maneira que, pela regra da mão direita,
 * todas as superfícies (lateral e base) fiquem para fora.
 *
 * @author Carlos Pereira - A61887
 * @author João Barreira  - A73831
 * @author Rafael Braga   - A61799
 *
 * @version 8-4-4017
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
	 * Construtor por parâmetros.
	 *
	 * Não são permitidos valores negativos para o raio e a altura. O número
	 * mínimo de slices e stacks é 1.
	 * Os vértices do cone são calculados automaticamente após a 
	 * inicialização dos parâmetros deste.
	 *
	 * @param radius Raio da base do cone
	 * @param height Altura do cone
	 * @param slices Número de slices a utilizar
	 * @param stacks Número de stacks a utilizar
	 */
	Cone(float radius, float height, int slices, int stacks);
	

	/**
	 * Construtor de cópia.
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
	 * Devolve o número de stacks.
	 */
	int getStacks(void);


	/**
	 * Devolve o número de slices.
	 */
	int getSlices(void);


	/**
	 * Altera o valor do raio.
	 */
	void setRadius(float);


	/**
	 * Altera o valor da altura.
	 */
	void setHeight(float);


	/**
	 * Altera o número de stacks.
	 */
	void setStacks(int);


	/**
	 * Altera o número se slices.
	 */
	void setSlices(int);


	/**
	 * Método que cálcula todos as coordenadas de todos os pontos de um cone.
	 */
	void generateVertices(void);


	/**
	 * Destrutor da classe Cone.
	 */
	~Cone(void);
};

#endif