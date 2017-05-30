/**
 * @file trianglesDrawing.h
 *
 * @brief M�dulo que apresenta m�todos para se efetuar um desenho de um
 *        conjunto de tri�ngulos em OpenGL.
 *
 * Uma tri�ngulo � definido como tr�s v�rtices. Esta classe usa ent�o um
 * array de v�rtices recorrendo � classe auxiliar Vertex. 
 *
 * @author Carlos Pereira - A61887
 * @author Jo�o Barreira  - A73831
 * @author Rafael Braga   - A61799
 *
 * @version 06-05-2017
 */


#ifndef trianglesDrawing_h
#define trianglesDrawing_h


#include <vector>
#include "glOperation.h"
#include "tripleFloat.h"


class TrianglesDrawing : public GLOperation {
	class TrianglesDrawingImpl;   // Implementa��o da classe TrianglesDrawing
	TrianglesDrawingImpl* pimpl;  // Apontador para a implementa��o da classe 
	                              // TrianglesDrawing


public:

	/**
	 * Construtor por defeito.
	 */
	TrianglesDrawing(void);


	/**
	 * Construtor por par�metros.
	 *
	 * @param vertices     Conjunto de v�rtices a desenhar.
	 * @param normals      Conjunto de v�rtices a desenhar.
	 * @param texCoords    Conjunto de coordenadas de uma textura.
	 * @param indexes      Conjunto de �ndices associados ao vetor de v�rtices.
	 * @param sphereRadius Raio da esfera que cobre a primitiva.
	 * @param diff         Cor difusa.
	 * @param spec         Cor especular.
	 * @param emis         Cor emissiva.
	 * @param ambt         Cor ambiente.
	 * @param shininess    Brilho do modelo.
	 * @param textura      Textura de um modelo.
	 */
	TrianglesDrawing(std::vector<GLfloat> vertices,
		             std::vector<GLfloat> normals,
		             std::vector<GLfloat> texCoords,
		             std::vector<size_t> indexes,
		             float sphereRadius,
		             TripleFloat diff,
		             TripleFloat spec,
		             TripleFloat emis,
		             TripleFloat ambt,
		             float shininess = 0.0f,
		             std::string texture = "");


	/**
	 * Construtor de c�pia.
	 *
	 * @param t Objeto da classe TrianglesDrawing a copiar.
	 */
	TrianglesDrawing(const TrianglesDrawing& t);


	/**
	 * Devolve o conjunto de v�rtices a desenhar.
	 */
	std::vector<GLfloat> getVertices(void);
	

	/**
	 * Devolve o conjunto de normais.
	 */
	std::vector<GLfloat> getNormals(void);


	/**
	 * Devolve o conjunto de coordenadas de uma textura.
	 */
	std::vector<GLfloat> getTexCoords(void);


	/**
	 * Devolve o conjunto de �ndices associados ao vetor de v�rtices.
	 */
	std::vector<size_t> getIndexes(void);

	
	/**
	 * Devolve a cor difusa do modelo.
	 */
	TripleFloat getDiff(void);


	/**
	 * Devolve a cor especular do modelo.
	 */
	TripleFloat getSpec(void);


	/**
	 * Devolve a cor emissiva do modelo.
	 */
	TripleFloat getEmis(void);


	/**
	 * Devolve a cor ambiente do modelo.
	 */
	TripleFloat getAmbt(void);


	/**
	 * Devolve o valor do brilho do modelo.
	 */
	float TrianglesDrawing::getShininess(void);


	/**
	 * Devolve o nome da textura.
	 */
	std::string getTexture(void);


	/**
	 * Altera o conjunto de v�rtices a desenhar.
	 */
	void setVertices(std::vector<GLfloat>);


	/**
	 * Altera o conjunto de normais.
	 */
	void setNormals(std::vector<GLfloat>);


	/**
	 * Altera o conjunto de coordenadas de uma textura.
	 */
	void setTexCoords(std::vector<GLfloat>);


	/**
	 * Altera o conjunto de �ndices associados ao vetor de v�rtices.
	 */
	void setIndexes(std::vector<size_t>);


	/**
	 * Altera a cor difusa do modelo.
	 */
	void setDiff(TripleFloat);


	/**
	 * Altera a cor especular do modelo.
	 */
	void setSpec(TripleFloat);


	/**
	 * Altera a cor emissiva do modelo.
	 */
	void setEmis(TripleFloat);


	/**
	 * Altera a cor ambiente do modelo.
	 */
	void setAmbt(TripleFloat);


	/**
	 * Altera o valor do brilho do modelo.
	 */
	void TrianglesDrawing::setShininess(float);


	/**
	 * Altera o nome da textura.
	 */
	void setTexture(std::string texture);


	/**
	 * Desenha um conjunto de v�rtices de uma primitiva em OpenGL.
	 */
	void execute(void);


	/**
	 * Desenha um conjunto de v�rtices de uma primitiva em OpenGL.
	 */
	void execute(FrustumCulling*);


	/**
	 * Destrutor da classe TrianglesDrawing.
	 */
	~TrianglesDrawing(void);
};


#endif
