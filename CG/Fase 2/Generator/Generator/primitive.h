/**
 * @file primitive.h
 *
 * @brief M�dulo que representa a classe abstrata Primitive. Uma primitiva pode
 *        ser vista como um conjunto de v�rtices.
 *
 * @author Carlos Pereira - A61887
 * @author Jo�o Barreira  - A73831
 * @author Rafael Braga   - A61799
 */


#ifndef primitive_h
#define primitive_h

#include <vector>
#include "vertex.h"

class Primitive {
	class PrimitiveImpl;
	PrimitiveImpl* pimpl;

public:

	/**
	 * Construtor por defeito.
	 */
	Primitive(void);


	/**
	 * Construtor por par�metros.
	 *
	 * @param vertices Conjunto de v�rtices de uma primitiva.
	 */
	Primitive(std::vector<Vertex> vertices);


	/**
	 * Construtor de c�pia.
	 *
	 * @param p Objeto da classe Primitive a ser copiado.
	 */
	Primitive(const Primitive& p);
	

	/**
	 * Devolve o conjunto de v�rtices que definem uma primitiva.
	 */
	std::vector<Vertex> getVertices(void);


	/**
	 * Adiciona um v�rtice ao conjunto de v�rtices de uma primitiva.
	 *
	 * @param v V�rtice a adicionar.
	 */
	void addVertex(Vertex v);


	/**
	 * M�todo abstrato para gerar os v�rtices de um tipo de primitiva 
	 * qualquer.
	 */
	virtual void generateVertices(void) = 0;


	/**
	 * Destrutor. 
	 */
	virtual ~Primitive(void);
};

#endif 

