/**
 * @file primitive.cpp
 *
 * Definição dos métodos da classe Primitive.
 *
 * @author Carlos Pereira - A61887
 * @author João Barreira  - A73831
 * @author Rafael Braga   - A61799
 *
 * @version 04-04-2017
 */


#include "primitive.h"


class Primitive::PrimitiveImpl {
	std::vector<Vertex> vertices;  // Conjunto de vértices de uma primitiva
	std::vector<size_t> indexes;   // Conjunto de índices do vetor de vértices

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
	PrimitiveImpl(std::vector<Vertex> vertices, std::vector<size_t> indexes)
	{
		this->vertices = vertices;
		this->indexes = indexes;
	}


	/**
	 * Devolve o conjunto de vértices que definem uma primitiva.
	 */
	std::vector<Vertex> getVertices(void)
	{
		return vertices;
	}


	/**
	 * Devolve o conjunto de índices associados ao vetor de vértices.
	 */
	std::vector<size_t> getIndexes(void)
	{
		return indexes;
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
	 * Adiciona um índice ao conjunto de índices.
	 *
	 * @param index Índice a adicionar.
	 */
	void addIndex(size_t index)
	{
		indexes.push_back(index);
	}

	
	/**
	 * Destrutor por defeito.
	 */
	~PrimitiveImpl(void) = default;
};


/**
 * Construtor por defeito.
 */
Primitive::Primitive(void)
{
	pimpl = new PrimitiveImpl();
} 


/**
 * Construtor por parâmetros.
 *
 * @param vertices Conjunto de vértices de uma primitiva.
 * @param indexes  Conjunto de índices associados ao vetor de vértices.
 */
Primitive::Primitive(std::vector<Vertex> vertices, std::vector<size_t> indexes)
{
	pimpl = new PrimitiveImpl(vertices, indexes);
}


/**
 * Construtor de cópia.
 *
 * @param p Objeto da classe Primitive a ser copiado.
 */
Primitive::Primitive(const Primitive& p) 
{
	pimpl = new PrimitiveImpl(p.pimpl->getVertices(), p.pimpl->getIndexes());
}


/**
 * Devolve o conjunto de vértices que definem uma primitiva.
 */
std::vector<Vertex> Primitive::getVertices(void)
{
	return pimpl->getVertices();
}


/**
 * Devolve o conjunto de índices associados ao vetor de vértices.
 */
std::vector<size_t> Primitive::getIndexes(void)
{
	return pimpl->getIndexes();
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
 * Adiciona um índice ao conjunto de índices.
 *
 * @param index Índice a adicionar.
 */
void Primitive::addIndex(size_t index)
{
	pimpl->addIndex(index);
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