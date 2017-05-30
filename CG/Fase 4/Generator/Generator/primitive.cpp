/**
 * @file primitive.cpp
 *
 * Definição dos métodos da classe Primitive.
 *
 * @author Carlos Pereira - A61887
 * @author João Barreira  - A73831
 * @author Rafael Braga   - A61799
 *
 * @version 12-05-2017
 */


#include "primitive.h"


class Primitive::PrimitiveImpl {
	std::vector<TripleFloat> vertices;  // Conjunto de vértices de uma primitiva
	std::vector<TripleFloat> normals;   // Conjunto de normais de uma primitiva
	std::vector<TripleFloat> texCoords; // Conjunto de coordenadas de uma textura
	std::vector<size_t> indexes;        // Conjunto de índices do vetor de vértices

public:

	/**
	 * Construtor por defeito.
	 */
	PrimitiveImpl(void) = default;


	/**
	 * Construtor por parâmetros.
	 *
	 * @param vertices  Conjunto de vértices de uma primitiva.
	 * @param normals   Conjunto de normais de uma primitiva.
	 * @param texCoords Conjunto de coordenadas de uma textura.
	 * @param indexes   Conjunto de índices associados ao vetor de vértices.
	 */
	PrimitiveImpl(std::vector<TripleFloat> vertices, 
		          std::vector<TripleFloat> normals,
		          std::vector<TripleFloat> texCoords,
		          std::vector<size_t> indexes)
	{
		this->vertices = vertices;
		this->normals = normals;
		this->texCoords = texCoords;
		this->indexes = indexes;
	}


	/**
	 * Devolve o conjunto de vértices que definem uma primitiva.
	 */
	std::vector<TripleFloat> getVertices(void)
	{
		return vertices;
	}


	/**
	 * Devolve o conjunto de normais de uma primitiva.
	 */
	std::vector<TripleFloat> getNormals(void)
	{
		return normals;
	}


	/**
	 * Devolve o conjunto coordenadas de uma textura.
	 */
	std::vector<TripleFloat> getTexCoords(void)
	{
		return texCoords;
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
	void addVertex(TripleFloat v)
	{
		vertices.push_back(v);
	}
	

	/**
	 * Adiciona um normal ao conjunto de normais de uma primitiva.
	 *
	 * @param n Normal a adicionar.
	 */
	void addNormal(TripleFloat n)
	{
		normals.push_back(n);
	}


	/**
	 * Adiciona uma coordenada de uma textura ao conjunto de
	 * coordenadas.
	 *
	 * @param t Coordenada de uma textura a adicionar.
	 */
	void addTexCoord(TripleFloat t)
	{
		texCoords.push_back(t);
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
 * @param normals  Conjunto de normais de uma primitiva.
 * @param texCoords Conjunto de coordenadas de uma textura.
 * @param indexes  Conjunto de índices associados ao vetor de vértices.
 */
Primitive::Primitive(std::vector<TripleFloat> vertices, 
	                 std::vector<TripleFloat> normals,
	                 std::vector<TripleFloat> texCoords,
	                 std::vector<size_t> indexes)
{
	pimpl = new PrimitiveImpl(vertices, normals, texCoords, indexes);
}


/**
 * Construtor de cópia.
 *
 * @param p Objeto da classe Primitive a ser copiado.
 */
Primitive::Primitive(const Primitive& p) 
{
	pimpl = new PrimitiveImpl(p.pimpl->getVertices(), 
		                      p.pimpl->getNormals(),
		                      p.pimpl->getTexCoords(),
		                      p.pimpl->getIndexes());
}


/**
 * Devolve o conjunto de vértices que definem uma primitiva.
 */
std::vector<TripleFloat> Primitive::getVertices(void)
{
	return pimpl->getVertices();
}


/**
 * Devolve o conjunto de normais que definem uma primitiva.
 */
std::vector<TripleFloat> Primitive::getNormals(void)
{
	return pimpl->getNormals();
}


/**
 * Devolve o conjunto coordenadas de uma textura.
 */
std::vector<TripleFloat> Primitive::getTexCoords(void)
{
	return pimpl->getTexCoords();
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
void Primitive::addVertex(TripleFloat v)
{
	pimpl->addVertex(v);
}


/**
 * Adiciona uma normal ao conjunto de normais de uma primitiva.
 *
 * @param n Normal a adicionar.
 */
void Primitive::addNormal(TripleFloat n)
{
	pimpl->addNormal(n);
}


/**
 * Adiciona uma coordenada de uma textura ao conjunto de
 * coordenadas.
 *
 * @param t Coordenada de uma textura a adicionar.
 */
void Primitive::addTexCoord(TripleFloat t)
{
	pimpl->addTexCoord(t);
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