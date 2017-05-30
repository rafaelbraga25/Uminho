/**
 * @file primitive.cpp
 *
 * Definição dos métodos da classe Primitive.
 *
 * @author Carlos Pereira - A61887
 * @author João Barreira  - A73831
 * @author Rafael Braga   - A61799
 */


#include <iterator>
#include "primitive.h"


class Primitive::PrimitiveImpl {
	std::vector<Vertex> vertices;  // Conjunto de vértices de uma primitiva

public:

	/**
	 * Construtor por defeito.
	 */
	PrimitiveImpl(void) = default;


	/**
	 * Construtor por parâmetros.
	 *
	 * @param vertices Conjunto de vértices de uma primitiva.
	 */
	PrimitiveImpl(std::vector<Vertex> vertices)
	{
		for (size_t i = 0; i < vertices.size(); i++) {
			this->vertices.push_back(vertices.at(i));
		}
	}


	/**
	 * Devolve o conjunto de vértices que definem uma primitiva.
	 */
	std::vector<Vertex> getVertices(void)
	{
		return vertices;
	}

	
	/**
	 * Adiciona um vértice ao conjunto de vértices de uma primitiva.
	 *
	 * @param v Vértice a adicionar.
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
 * Construtor por parâmetros.
 *
 * @param vertices Conjunto de vértices de uma primitiva.
 */
Primitive::Primitive(std::vector<Vertex> vertices)
	: pimpl{ new PrimitiveImpl(vertices) } {}


/**
 * Construtor de cópia.
 *
 * @param p Objeto da classe Primitive a ser copiado.
 */
Primitive::Primitive(const Primitive& p)
	: pimpl{ new PrimitiveImpl(p.pimpl->getVertices()) } {}


/**
 * Devolve o conjunto de vértices que definem uma primitiva.
 */
std::vector<Vertex> Primitive::getVertices(void)
{
	return pimpl->getVertices();
}


/**
 * Adiciona um vértice ao conjunto de vértices de uma primitiva.
 *
 * @param v Vértice a adicionar.
 */
void Primitive::addVertex(Vertex v)
{
	pimpl->addVertex(v);
}


/**
 * Destrutor da classe Primitive.
 *
 * Liberta a memória ocupada pelo apontador para a parte privada da classe
 * Primitive.
 */
Primitive::~Primitive(void)
{
	if (pimpl != NULL) {
		delete pimpl;
		pimpl = NULL;
	}
}