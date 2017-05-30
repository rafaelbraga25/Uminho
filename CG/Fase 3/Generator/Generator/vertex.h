/**
 * @file vertex.h
 *
 * @brief M�dulo que representa as coordenadas x, y e z de um v�rtice.
 *
 * @author Carlos Pereira - A61887
 * @author Jo�o Barreira  - A73831
 * @author Rafael Braga   - A61799
 *
 * @version 4-4-2017
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
	 * Construtor por par�metros.
	 *
	 * @param x Coordenada x de um v�rtice.
	 * @param y Coordenada y de um v�rtice.
	 * @param z Coordenada z de um v�rtice.
	 */
	Vertex(float x, float y, float z);


	/*
	 * Construtor de c�pia.
	 *
	 * @param v Objeto da classe Vertex a ser copiado.
	 */
	Vertex(const Vertex& v);


	/**
	 * Devolve a coordenada x de um v�rtice.
	 */
	float getX(void);
	
	
	/**
	 * Devolve a coordenada y de um v�rtice.
	 */
	float getY(void);
	
	
	/**
	 * Devolve a coordenada z de um v�rtice.
	 */
	float getZ(void);


	/**
	 * Altera o valor da coordenada x de um v�rtice.
	 */
	void setX(float x);
	
	
	/**
	 * Altera o valor da coordenada y de um v�rtice.
	 */
	void setY(float y);
	
	
	/**
	 * Altera o valor da coordenada z de um v�rtice.
	 */
	void setZ(float z);


	/**
	 * Adiciona �s coordenadas de um v�rtice os valores das coordenadas de
	 * outro v�rtice.
	 *
	 * @param x Coordenada x.
	 * @param y Coordenada y.
	 * @param z Coordenada z.
	 */
	void add(float x, float y, float z);


	/**
	 * Devolve uma representa��o textual da classe Vertex.
	 */
	std::string toString();


	/**
	 * Destrutor da classe Vertex.
	 */
	~Vertex(void);
};

#endif 

