/**
 * @file vertex.h
 *
 * @brief Módulo que representa as coordenadas x, y e z de um vértice.
 *
 * @author Carlos Pereira - A61887
 * @author João Barreira  - A73831
 * @author Rafael Braga   - A61799
 */


#ifndef vertex_h
#define vertex_h

#include <string>


class Vertex {
	class VertexImpl;
	VertexImpl* pimpl;

public:

	/*
	 * Construtor por defeito.
	 */
	Vertex(void);


	/**
	 * Construtor por parâmetros.
	 *
	 * @param x Coordenada x de um vértice.
	 * @param y Coordenada y de um vértice.
	 * @param z Coordenada z de um vértice.
	 */
	Vertex(float x, float y, float z);


	/*
	 * Construtor de cópia.
	 *
	 * @param v Objeto da classe Vertex a ser copiado.
	 */
	Vertex(const Vertex& v);


	/**
	 * Devolve a coordenada x de um vértice.
	 */
	float getX(void);
	
	
	/**
	 * Devolve a coordenada y de um vértice.
	 */
	float getY(void);
	
	
	/**
	 * Devolve a coordenada z de um vértice.
	 */
	float getZ(void);


	/**
	 * Altera o valor da coordenada x de um vértice.
	 */
	void setX(float x);
	
	
	/**
	 * Altera o valor da coordenada y de um vértice.
	 */
	void setY(float y);
	
	
	/**
	 * Altera o valor da coordenada z de um vértice.
	 */
	void setZ(float z);


	/**
	 * Adiciona às coordenadas de um vértice os valores das coordenadas de
	 * outro vértice.
	 *
	 * @param x Coordenada x.
	 * @param y Coordenada y.
	 * @param z Coordenada z.
	 */
	void add(float x, float y, float z);


	/**
	 * Devolve uma representação textual da classe Vertex.
	 */
	std::string toString();


	/**
	 * Destrutor da classe Vertex.
	 */
	~Vertex(void);
};

#endif 

