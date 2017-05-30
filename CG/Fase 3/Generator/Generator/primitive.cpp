/**
 * @file primitive.cpp
 *
 * Defini��o dos m�todos da classe Primitive.
 *
 * @author Carlos Pereira - A61887
 * @author Jo�o Barreira  - A73831
 * @author Rafael Braga   - A61799
 *
 * @version 04-04-2017
 */


#include "primitive.h"


class Primitive::PrimitiveImpl {
	std::vector<Vertex> vertices;  // Conjunto de v�rtices de uma primitiva
	std::vector<size_t> indexes;   // Conjunto de �ndices do vetor de v�rtices

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
	PrimitiveImpl(std::vector<Vertex> vertices, std::vector<size_t> indexes)
	{
		this->vertices = vertices;
		this->indexes = indexes;
	}


	/**
	 * Devolve o conjunto de v�rtices que definem uma primitiva.
	 */
	std::vector<Vertex> getVertices(void)
	{
		return vertices;
	}


	/**
	 * Devolve o conjunto de �ndices associados ao vetor de v�rtices.
	 */
	std::vector<size_t> getIndexes(void)
	{
		return indexes;
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
	 * Adiciona um �ndice ao conjunto de �ndices.
	 *
	 * @param index �ndice a adicionar.
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
 * Construtor por par�metros.
 *
 * @param vertices Conjunto de v�rtices de uma primitiva.
 * @param indexes  Conjunto de �ndices associados ao vetor de v�rtices.
 */
Primitive::Primitive(std::vector<Vertex> vertices, std::vector<size_t> indexes)
{
	pimpl = new PrimitiveImpl(vertices, indexes);
}


/**
 * Construtor de c�pia.
 *
 * @param p Objeto da classe Primitive a ser copiado.
 */
Primitive::Primitive(const Primitive& p) 
{
	pimpl = new PrimitiveImpl(p.pimpl->getVertices(), p.pimpl->getIndexes());
}


/**
 * Devolve o conjunto de v�rtices que definem uma primitiva.
 */
std::vector<Vertex> Primitive::getVertices(void)
{
	return pimpl->getVertices();
}


/**
 * Devolve o conjunto de �ndices associados ao vetor de v�rtices.
 */
std::vector<size_t> Primitive::getIndexes(void)
{
	return pimpl->getIndexes();
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
 * Adiciona um �ndice ao conjunto de �ndices.
 *
 * @param index �ndice a adicionar.
 */
void Primitive::addIndex(size_t index)
{
	pimpl->addIndex(index);
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