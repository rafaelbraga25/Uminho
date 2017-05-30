/**
 * @file trianglesDrawing.cpp
 *
 * Definição de todos os métodos para se representar um conjunto de vértices em
 * OpenGL.
 *
 * @author Carlos Pereira - A61887
 * @author João Barreira  - A73831
 * @author Rafael Braga   - A61799
 *
 * @version 12-05-2017
 */


#include "trianglesDrawing.h"


class TrianglesDrawing::TrianglesDrawingImpl {
	std::vector<GLfloat> vertices;  // Conjunto de vértices a desenhar
	std::vector<GLfloat> normals;   // Conjunto de normais a desenhar
	std::vector<GLfloat> texCoords; // Conjunto de coordenadas de uma textura

	std::vector<size_t> indexes;    // Conjunto de índices associados ao vetor
	                                // de vértices
	float sphereRadius;             // Raio da esfera que cobre a primitiva

	TripleFloat diff;               // Cor difusa
	TripleFloat spec;               // Cor especular
	TripleFloat emis;               // Cor emissiva
	TripleFloat ambt;               // Cor ambiente

	float shininess;                // Brilho do material

	std::string texture;            // Textura

	bool isGenerated;               // Flag que testa se o buffer já foi 
	                                // inicializado ou não

	GLuint buffers[3];              // Buffers utilizados para os VBOs
	unsigned int texID;             // ID de uma textura


	/**
	 * Carrega a textura da primitiva
	 */
	void loadTexture(void) 
	{
		unsigned int t = 0; 
		unsigned int tw = 0; 
		unsigned int th = 0;
		unsigned char *texData;

		ilEnable(IL_ORIGIN_SET);
		ilOriginFunc(IL_ORIGIN_LOWER_LEFT);

		ilGenImages(1, &t);
		ilBindImage(t);
		ilLoadImage((ILstring)texture.c_str());

		tw = ilGetInteger(IL_IMAGE_WIDTH);
		th = ilGetInteger(IL_IMAGE_HEIGHT);

		ilConvertImage(IL_RGBA, IL_UNSIGNED_BYTE);
		texData = ilGetData();

		glGenTextures(1, &texID);

		glBindTexture(GL_TEXTURE_2D, texID);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, tw, th, 0, GL_RGBA, GL_UNSIGNED_BYTE, texData);
		glGenerateMipmap(GL_TEXTURE_2D);

		glBindTexture(GL_TEXTURE_2D, 0);
	}


	/**
	 * Gera os buffers para serem utilizados em VBOs. 
	 * Preenche o buffer com o array de índices.
	 */
	void generate(void)
	{
		// O buffer é apenas inicializado uma vez
		isGenerated = true;

		// Apenas é carregada uma textura se o ficheiro for válido
		if (texture.compare("") != 0) {
			loadTexture();
		}

		glGenBuffers(3, buffers);

		glBindBuffer(GL_ARRAY_BUFFER, buffers[0]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertices.size(), &vertices[0], GL_STATIC_DRAW);

		glBindBuffer(GL_ARRAY_BUFFER, buffers[1]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * normals.size(), &normals[0], GL_STATIC_DRAW);

		if (texture.compare("") != 0) {
			glBindBuffer(GL_ARRAY_BUFFER, buffers[2]);
			glBufferData(GL_ARRAY_BUFFER, sizeof(float) * texCoords.size(), &texCoords[0], GL_STATIC_DRAW);
		}
	}

	/**
	 * Testa se uma cor tem outro valor que não uma cor preta (0, 0, 0).
	 */
	bool hasColor(TripleFloat color)
	{
		return (color.getF1() != 0.0f || color.getF2() != 0.0f || color.getF3() != 0.0f);
	}


public:

	/**
	 * Construtor por defeito.
	 */
	TrianglesDrawingImpl(void) 
	{

		diff.setF1(0.8f);
		diff.setF2(0.8f);
		diff.setF3(0.8f);

		spec.setF1(0.0f);
		spec.setF2(0.0f);
		spec.setF3(0.0f);

		emis.setF1(0.0f);
		emis.setF2(0.0f);
		emis.setF3(0.0f);

		ambt.setF1(0.2f);
		ambt.setF2(0.2f);
		ambt.setF3(0.2f);

		shininess = 0.0f;
		texture = "";
		isGenerated = false;
		texID = 0;
		sphereRadius = 0.0f;
	}


	/**
	 * Construtor por parâmetros.
	 *
	 * @param vertices     Conjunto de vértices a desenhar.
	 * @param normals      Conjunto de vértices a desenhar.
	 * @param texCoords    Conjunto de coordenadas de uma textura.
	 * @param indexes      Conjunto de índices associados ao vetor de vértices.
	 * @param sphereRadius Raio da esfera que cobre a primitiva.
	 * @param diff         Cor difusa.
	 * @param spec         Cor especular.
	 * @param emis         Cor emissiva.
	 * @param ambt         Cor ambiente.
	 * @param shininess    Brilho do material
	 * @param texture      Textura de um modelo.
	 */
	TrianglesDrawingImpl(std::vector<GLfloat> vertices, 
		                 std::vector<GLfloat> normals,
		                 std::vector<GLfloat> texCoords,
		                 std::vector<size_t> indexes,
		                 float sphereRadius,
		                 TripleFloat diff,
		                 TripleFloat spec,
		                 TripleFloat emis,
		                 TripleFloat ambt,
		                 float shininess,
		                 std::string texture)
	{
		this->vertices = vertices;
		this->normals = normals;
		this->texCoords = texCoords;
		this->indexes = indexes;

		this->diff.setF1(diff.getF1()); 
		this->diff.setF2(diff.getF2()); 
		this->diff.setF3(diff.getF3()); 

		this->spec.setF1(spec.getF1());
		this->spec.setF2(spec.getF2());
		this->spec.setF3(spec.getF3());

		this->emis.setF1(emis.getF1());
		this->emis.setF2(emis.getF2());
		this->emis.setF3(emis.getF3());

		this->ambt.setF1(ambt.getF1());
		this->ambt.setF2(ambt.getF2());
		this->ambt.setF3(ambt.getF3());

		this->shininess = shininess;
		this->texture = texture;

		isGenerated = false;
		
		texID = 0;
		this->sphereRadius = sphereRadius;
	}


	/**
	 * Devolve o conjunto de vértices a desenhar.
	 */
	std::vector<GLfloat> getVertices(void)
	{
		return vertices;
	}


	/**
	 * Devolve o conjunto de normais a desenhar.
	 */
	std::vector<GLfloat> getNormals(void)
	{
		return normals;
	}


	/**
	 * Devolve o conjunto de coordenadas de uma textura.
	 */
	std::vector<GLfloat> getTexCoords(void)
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
	 * Devolve o valor do raio da esfera que cobre a primitiva.
	 */
	float getSphereRadius(void)
	{
		return sphereRadius;
	}


	/**
	 * Devolve a cor difusa do modelo.
	 */
	TripleFloat getDiff(void)
	{
		return diff;
	}


	/**
	 * Devolve a cor especular do modelo.
	 */
	TripleFloat getSpec(void)
	{
		return spec;
	}


	/**
	 * Devolve a cor emissiva do modelo.
	 */
	TripleFloat getEmis(void)
	{
		return emis;
	}


	/**
	 * Devolve a cor ambiente do modelo.
	 */
	TripleFloat getAmbt(void)
	{
		return ambt;
	}


	/**
	 * Devolve o valor do brilho do modelo.
	 */
	float getShininess(void)
	{
		return shininess;
	}


	/**
	 * Devolve o nome da textura.
	 */
	std::string getTexture(void)
	{
		return texture;
	}


	/**
	 * Altera o conjunto de vértices a desenhar.
	 */
	void setVertices(std::vector<GLfloat> vertices)
	{
		this->vertices = vertices;
	}


	/**
	 * Altera o conjunto de normais a desenhar.
	 */
	void setNormals(std::vector<GLfloat> normals)
	{
		this->normals = normals;
	}


	/**
	 * Altera o conjunto de coordenadas de uma textura.
	 */
	void setTexCoords(std::vector<GLfloat> texCoords)
	{
		this->texCoords = texCoords;
	}


	/**
	 * Altera o conjunto de índices associados ao vetor de vértices.
	 */
	void setIndexes(std::vector<size_t> indexes)
	{
		this->indexes = indexes;
	}


	/**
	 * Altera a cor difusa do modelo.
	 */
	void setDiff(TripleFloat diff)
	{
		this->diff.setF1(diff.getF1());
		this->diff.setF2(diff.getF2());
		this->diff.setF3(diff.getF3());
	}


	/**
	 * Altera a cor especular do modelo.
	 */
	void setSpec(TripleFloat spec)
	{
		this->spec.setF1(spec.getF1());
		this->spec.setF2(spec.getF2());
		this->spec.setF3(spec.getF3());
	}


	/**
	 * Altera a cor emissiva do modelo.
	 */
	void setEmis(TripleFloat emis)
	{
		this->emis.setF1(emis.getF1());
		this->emis.setF2(emis.getF2());
		this->emis.setF3(emis.getF3());
	}


	/**
	 * Altera a cor ambiente do modelo.
	 */
	void setAmbt(TripleFloat ambt)
	{
		this->ambt.setF1(ambt.getF1());
		this->ambt.setF2(ambt.getF2());
		this->ambt.setF3(ambt.getF3());
	}


	/**
	 * Altera o valor do brilho do modelo.
	 */
	void setShininess(float shininess)
	{
		this->shininess = shininess;
	}


	/**
	 * Altera o nome da textura.
	 */
	void setTexture(std::string texture)
	{
		this->texture = texture;
	}


	/**
	 * Desenha uma primitiva em modo de VBOs com um conjunto de índices.
	 */
	void execute(void)
	{
		float d[4];
		float s[4];
		float e[4] = { emis.getF1(), emis.getF2(), emis.getF3(), 1.0f };
		float a[4];

		if (isGenerated == false) {
			generate();
		}

		// Não deixa que a tela fique em preto
		if (hasColor(diff) == false) {
			diff.setF1(1.0f);
			diff.setF2(1.0f);
			diff.setF3(1.0f);
		}

		d[0] = diff.getF1(); d[1] = diff.getF2(); d[2] = diff.getF3(); d[3] = 1.0f;
		s[0] = spec.getF1(); s[1] = spec.getF2(); s[2] = spec.getF3(); s[3] = 1.0f;
		a[0] = ambt.getF1(); a[1] = ambt.getF2(); a[2] = ambt.getF3(); a[3] = 1.0f;

		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, d);
		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, s);
		glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, e);
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, a);

		glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shininess);

		glBindBuffer(GL_ARRAY_BUFFER, buffers[0]);
		glVertexPointer(3, GL_FLOAT, 0, 0);

		glBindBuffer(GL_ARRAY_BUFFER, buffers[1]);
		glNormalPointer(GL_FLOAT, 0, 0);

		if (texture.compare("") != 0) {
			glEnableClientState(GL_TEXTURE_COORD_ARRAY);

			glBindBuffer(GL_ARRAY_BUFFER, buffers[2]);
			glTexCoordPointer(2, GL_FLOAT, 0, 0);

			glBindTexture(GL_TEXTURE_2D, texID);
		}
		else {
			glDisableClientState(GL_TEXTURE_COORD_ARRAY);
		}

		glDrawElements(GL_TRIANGLES, (GLsizei)indexes.size(), GL_UNSIGNED_INT, &indexes[0]);

		if (texture.compare("") != 0) {
			glBindTexture(GL_TEXTURE_2D, 0);
		}
	}


	/**
	 * Desenha uma primitiva em modo de VBOs com um conjunto de índices.
	 */
	void execute(FrustumCulling* f)
	{
		bool inFrustum = false;
		TripleFloat coord(f->getCoords());

	    inFrustum = f->sphereInFrustum(coord, sphereRadius);

		/**
		 * Só desenha a primitiva se estiver dentro do campo visível.
		 */
		if (inFrustum == true) {
			execute();
		}
	}


	/**
	 * Destrutor da classe TrianglesDrawingImpl (por defeito em c++).
	 */
	~TrianglesDrawingImpl(void) = default;
};


/**
 * Construtor por defeito. Inicializa o apontador para a implementação da
 * classe TrianglesDrawing.
 */
TrianglesDrawing::TrianglesDrawing(void)
{
	pimpl = new TrianglesDrawingImpl();
}


/**
 * Construtor por parâmetros.
 *
 * @param vertices     Conjunto de vértices a desenhar.
 * @param normals      Conjunto de vértices a desenhar.
 * @param texCoords    Conjunto de coordenadas de uma textura.
 * @param indexes      Conjunto de índices associados ao vetor de vértices. 
 * @param sphereRadius Raio da esfera que cobre a primitiva.
 * @param diff         Cor difusa.
 * @param spec         Cor especular.
 * @param emis         Cor emissiva.
 * @param ambt         Cor ambiente.
 * @param shininess    Brilho do material.
 * @param texture      Textura de um modelo.
 */ 
TrianglesDrawing::TrianglesDrawing(std::vector<GLfloat> vertices,
	                               std::vector<GLfloat> normals,
	                               std::vector<GLfloat> texCoords,
	                               std::vector<size_t> indexes,
	                               float sphereRadius,
	                               TripleFloat diff,
	                               TripleFloat spec,
	                               TripleFloat emis,
	                               TripleFloat ambt,
	                               float shininess,
	                               std::string texture)
{
	pimpl = new TrianglesDrawingImpl(vertices, normals, texCoords, indexes, sphereRadius,
		                             diff, spec, emis, ambt,
		                             shininess, texture);
}


/**
 * Construtor de cópia. Inicializa o apontador para a implementação da classe
 * TrianglesDrawing, recorrendo a uma deep copy de um objeto desta classe.
 *
 * @param t Objeto da classe TrianglesDrawing a copiar.
 */
TrianglesDrawing::TrianglesDrawing(const TrianglesDrawing& t)
{
	pimpl = new TrianglesDrawingImpl(t.pimpl->getVertices(),
		                             t.pimpl->getNormals(),
		                             t.pimpl->getTexCoords(),
		                             t.pimpl->getIndexes(),
		                             t.pimpl->getSphereRadius(),
		                             t.pimpl->getDiff(),
		                             t.pimpl->getSpec(),
		                             t.pimpl->getEmis(),
		                             t.pimpl->getAmbt(),
		                             t.pimpl->getShininess(),
		                             t.pimpl->getTexture());
}


/**
 * Devolve o conjunto de vértices a desenhar.
 */
std::vector<GLfloat> TrianglesDrawing::getVertices(void)
{
	return pimpl->getVertices();
}


/**
 * Devolve o conjunto de normais a desenhar.
 */
std::vector<GLfloat> TrianglesDrawing::getNormals(void)
{
	return pimpl->getNormals();
}


/**
 * Devolve o conjunto de coordenadas de uma textura.
 */
std::vector<GLfloat> TrianglesDrawing::getTexCoords(void)
{
	return pimpl->getTexCoords();
}


/**
 * Devolve o conjunto de índices associados ao vetor de vértices.
 */
std::vector<size_t> TrianglesDrawing::getIndexes(void)
{
	return pimpl->getIndexes();
}


/**
 * Devolve a cor difusa do modelo.
 */
TripleFloat TrianglesDrawing::getDiff(void)
{
	return pimpl->getDiff();
}


/**
 * Devolve a cor especular do modelo.
 */
TripleFloat TrianglesDrawing::getSpec(void)
{
	return pimpl->getSpec();
}


/**
 * Devolve a cor emissiva do modelo.
 */
TripleFloat TrianglesDrawing::getEmis(void)
{
	return pimpl->getEmis();
}


/**
 * Devolve a cor ambiente do modelo.
 */
TripleFloat TrianglesDrawing::getAmbt(void)
{
	return pimpl->getAmbt();
}


/**
 * Devolve o valor do brilho do modelo.
 */
float TrianglesDrawing::getShininess(void)
{
	return pimpl->getShininess();
}


/**
 * Devolve o nome da textura.
 */
std::string TrianglesDrawing::getTexture(void)
{
	return pimpl->getTexture();
}


/**
 * Altera o conjunto de vértices a desenhar.
 */
void TrianglesDrawing::setVertices(std::vector<GLfloat> vertices)
{
	pimpl->setVertices(vertices);
}


/**
 * Altera o conjunto de normais a desenhar.
 */
void TrianglesDrawing::setNormals(std::vector<GLfloat> normals)
{
	pimpl->setNormals(normals);
}


/**
 * Altera o conjunto de coordenadas de uma textura.
 */
void TrianglesDrawing::setTexCoords(std::vector<GLfloat> texCoords)
{
	pimpl->setTexCoords(texCoords);
}


/**
 * Altera o conjunto de índices associados ao vetor de vértices.
 */
void TrianglesDrawing::setIndexes(std::vector<size_t> indexes)
{
	pimpl->setIndexes(indexes);
}


/**
 * Altera a cor difusa do modelo.
 */
void TrianglesDrawing::setDiff(TripleFloat diff)
{
	pimpl->setDiff(diff);
}


/**
 * Altera a cor especular do modelo.
 */
void TrianglesDrawing::setSpec(TripleFloat spec)
{
	pimpl->setSpec(spec);
}


/**
 * Altera a cor emissiva do modelo.
 */
void TrianglesDrawing::setEmis(TripleFloat emis)
{
	pimpl->setEmis(emis);
}


/**
 * Altera a cor ambiente do modelo.
 */
void TrianglesDrawing::setAmbt(TripleFloat ambt)
{
	pimpl->setAmbt(ambt);
}


/**
 * Altera o valor do brilho do modelo.
 */
void TrianglesDrawing::setShininess(float shininess)
{
	pimpl->setShininess(shininess);
}


/**
 * Altera o nome da textura.
 */
void TrianglesDrawing::setTexture(std::string texture)
{
	pimpl->setTexture(texture);
}


/**
 * Desenha os vértices correspondentes a uma primitiva em OpenGL.
 */
void TrianglesDrawing::execute(void)
{
	pimpl->execute();
}


/**
 * Desenha os vértices correspondentes a uma primitiva em OpenGL.
 */
void TrianglesDrawing::execute(FrustumCulling* f)
{
	pimpl->execute(f);
}


/**
 * Destrutor da classe TrianglesDrawing. Liberta a memória ocupada pelo 
 * apontador para a implementação da classe TrianglesDrawing.
 */
TrianglesDrawing::~TrianglesDrawing(void)
{
	if (pimpl != NULL) {
		delete pimpl;
		pimpl = NULL;
	}
}