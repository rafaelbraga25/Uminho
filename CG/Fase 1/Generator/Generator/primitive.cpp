/**
 * @file primitive.cpp
 *
 * Defini��o dos m�todos da classe Primitive.
 *
 * @author Carlos Pereira - A61887
 * @author Jo�o Barreira  - A73831
 * @author Rafael Braga   - A61799
 */


#include <iterator>
#include "primitive.h"


class Primitive::PrimitiveImpl {
	std::vector<Vertex> vertices;  // Conjunto de v�rtices de uma primitiva

public:

	/**
	 * Construtor por defeito.
	 */
	PrimitiveImpl(void) = default;


	/**
	 * Construtor por par�metros.
	 *
	 * @param vertices Conjunto de v�rtices de uma primitiva.
	 */
	PrimitiveImpl(std::vector<Vertex> vertices)
	{
		for (size_t i = 0; i < vertices.size(); i++) {
			this->vertices.push_back(vertices.at(i));
		}
	}


	/**
	 * Devolve o conjunto de v�rtices que definem uma primitiva.
	 */
	std::vector<Vertex> getVertices(void)
	{
		return vertices;
	}

	
	/**
	 * Adiciona um v�rtice ao conjunto de v�rtices de uma primitiva.
	 *
	 * @param v V�rtice a adicionar.
	 */
	void addVertex(Vertex v)
	{
		vertices.push_back(v);
	}
	
	
	/**
	 * Destrutor por defeito.
	 */
	~PrimitiveImpl(void) = default;
};


/**
 * Construtor por defeito.
 */
Primitive::Primitive(void) : pimpl{ new PrimitiveImpl() } {}


/**
 * Construtor por par�metros.
 *
 * @param vertices Conjunto de v�rtices de uma primitiva.
 */
Primitive::Primitive(std::vector<Vertex> vertices)
	: pimpl{ new PrimitiveImpl(vertices) } {}


/**
 * Construtor de c�pia.
 *
 * @param p Objeto da classe Primitive a ser copiado.
 */
Primitive::Primitive(const Primitive& p)
	: pimpl{ new PrimitiveImpl(p.pimpl->getVertices()) } {}


/**
 * Devolve o conjunto de v�rtices que definem uma primitiva.
 */
std::vector<Vertex> Primitive::getVertices(void)
{
	return pimpl->getVertices();
}


/**
 * Adiciona um v�rtice ao conjunto de v�rtices de uma primitiva.
 *
 * @param v V�rtice a adicionar.
 */
void Primitive::addVertex(Vertex v)
{
	pimpl->addVertex(v);
}


/**
 * Destrutor da classe Primitive.
 *
 * Liberta a mem�ria ocupada pelo apontador para a parte privada da classe
 * Primitive.
 */
Primitive::~Primitive(void)
{
	if (pimpl != NULL) {
		delete pimpl;
		pimpl = NULL;
	}
}