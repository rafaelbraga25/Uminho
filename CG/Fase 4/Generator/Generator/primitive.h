/**
 * @file primitive.h
 *
 * @brief M�dulo que representa a classe abstrata Primitive. Uma primitiva pode
 *        ser vista como um conjunto de v�rtices.
 *
 * @author Carlos Pereira - A61887
 * @author Jo�o Barreira  - A73831
 * @author Rafael Braga   - A61799
 *
 * @version 02-05-2017
 */


#ifndef primitive_h
#define primitive_h

#include <vector>
#include "tripleFloat.h"

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
	 * @param vertices  Conjunto de v�rtices de uma primitiva.
	 * @param normals   Conjunto de normais de uma primitiva.
	 * @param texCoords Conjunto de coordenadas de uma textura. 
	 * @param indexes   Conjunto de �ndices associados ao vetor de v�rtices.
	 */
	Primitive(std::vector<TripleFloat> vertices,
		      std::vector<TripleFloat> normals,
		      std::vector<TripleFloat> texCoords,
		      std::vector<size_t> indexes);


	/**
	 * Construtor de c�pia.
	 *
	 * @param p Objeto da classe Primitive a ser copiado.
	 */
	Primitive(const Primitive& p);
	

	/**
	 * Devolve o conjunto de v�rtices que definem uma primitiva.
	 */
	std::vector<TripleFloat> getVertices(void);


	/**
	 * Devolve o conjunto de normais que definem uma primitiva.
	 */
	std::vector<TripleFloat> getNormals(void);


	/**
	 * Devolve o conjunto coordenadas de uma textura.
	 */
	std::vector<TripleFloat> getTexCoords(void);


	/**
	 * Devolve o conjunto de �ndices associados ao vetor de v�rtices.
	 */
	std::vector<size_t> getIndexes(void);


	/**
	 * Adiciona um v�rtice ao conjunto de v�rtices de uma primitiva.
	 *
	 * @param v V�rtice a adicionar.
	 */
	void addVertex(TripleFloat v);


	/**
	 * Adiciona uma normal ao conjunto de normais de uma primitiva.
	 *
	 * @param n Normal a adicionar.
	 */
	void addNormal(TripleFloat n);


	/**
	 * Adiciona uma coordenada de uma textura ao conjunto de 
	 * coordenadas.
	 *
	 * @param t Coordenada de uma textura a adicionar.
	 */
	void addTexCoord(TripleFloat t);


	/**
	 * Adiciona um �ndice ao conjunto de �ndices.
	 *
	 * @param index �ndice a adicionar.
	 */
	void addIndex(size_t index);


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

