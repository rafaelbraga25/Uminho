/**
 * @file sphere.cpp
 *
 * Definição de métodos para calcular as coordenadas dos pontos de uma esfera.
 *
 * @author Carlos Pereira - A61887
 * @author João Barreira  - A73831
 * @author Rafael Braga   - A61799
 * 
 * @version 30-4-2017
 */


#include "sphere.h"
#include <cmath>


const float pi = 3.1415926f;


class Sphere::SphereImpl {
	float radius;	// Raio da esfera
	float alfa;		// Ângulo em relação ao eixo Y no plano XZ em radianos
	float beta;		// Ângulo em relação ao eixo Z no plano XY em radianos
	int slices;	    // Número de slices a utilizar
	int stacks;	    // Número de stacks a utilizar


public:

	/**
	 * Construtor por defeito.
	 */
	SphereImpl(void)
	{
		radius = 0;
		alfa = beta = 0;
		slices = stacks = 0;
	}

	
	/**
	 * Construtor por parâmetros.
	 *
	 * @param radius Raio da esfera
	 * @param slices Número de slices a utilizar
	 * @param stacks Número de stacks a utilizar
	 */
	SphereImpl(float radius, int slices, int stacks)
	{
		this->radius = radius;
		this->slices = slices;
		this->stacks = stacks;
	
		alfa = (2 * pi) / ((float) slices);
		beta = pi / ((float) stacks);
	}

	
	/**
  	 * Devolve o valor do raio.
	 */
	float getRadius(void)
	{
		return radius;
	}


	/**
	 * Devolve o número de slices utilizadas.
	 */
	int getSlices(void)
	{
		return slices;
	}


	/**
	 * Devolve o número de stacks utilizadas.
	 */
	int getStacks(void)
	{
		return stacks;
	}


	/**
	 * Altera o valor do raio.
	 */
	void setRadius(float radius)
	{
		this->radius = radius;
	}


	/**
	 * Altera o número de stacks.
	 */
	void setStacks(int stacks)
	{
		this->stacks = stacks;

		beta = pi / ((float)stacks);
	}


	/**
	 * Altera o número de slices.
	 */
	void setSlices(int slices)
	{
		this->slices = slices;

		alfa = (2 * pi) / ((float)slices);
	}


	/**
	 * Calcula, a partir dos dados recebidos no construtor, as coordenadas de 
	 * todos os vértices que definem a esfera.
	 *
	 * @param vertices Conjunto de vértices.
	 * @param indexes  Conjunto de índices.
	 * @return O resultado é guardado em vertices e em indexes.
	 */
	void generateSphere(std::vector<Vertex>& vertices,
		                std::vector<size_t>& indexes)
	{
		float angleAlfa = 0;	// Ângulo atual no plano XZ
		float angleBeta = 0;	// Ângulo atual no plano XY

		float x = 0.0f;
		float y = 0.0f;
		float z = 0.0f;

		size_t index = 0;       // Índice atual do conjunto de índices

		for (size_t i = 0; i <= (size_t)stacks; i++) {
			
			//Cálculo do ângulo Beta
			angleBeta = ((float) beta * i);			

			for (size_t j = 0; j <= (size_t)slices; j++) {
				
				//Cálculo do ângulo Alfa
				angleAlfa = ((float) alfa * j);

				x = radius * sin(angleBeta) * cos(angleAlfa);
				y = radius * cos(angleBeta);
				z = radius * sin(angleBeta) * sin(angleAlfa);

				vertices.push_back(Vertex(x, y, z));
			}
		}

		for (size_t i = 0; i < (size_t)stacks; i++) {
			for (size_t j = 0; j < (size_t)slices; j++) {
				indexes.push_back(i * (slices + 1) + j);
				indexes.push_back(i * (slices + 1) + j + 1);
				indexes.push_back((i + 1) * (slices + 1) + j + 1);

				indexes.push_back(i * (slices + 1) + j);
				indexes.push_back((i + 1) * (slices + 1) + j + 1);
				indexes.push_back((i + 1) * (slices + 1) + j);
			}
		}
	}


	~SphereImpl(void) = default;
};


/**
 * Construtor por defeito.
 */
Sphere::Sphere(void) {
	pimpl = new SphereImpl();
} 


/**
 * Construtor por parâmetros.
 *
 * @param radius Raio da esfera
 * @param slices Número de slices a utilizar
 * @param stacks Número de stacks a utilizar
 */
Sphere::Sphere(float radius, int slices, int stacks)
{
	// Por defeito, o número de slices e stacks é sempre maior ou igual a 1

	slices = (slices < 1) ? 1 : slices;	
	stacks = (stacks < 1) ? 1 : stacks; 

	// O raio não pode conter um valor negativo

	radius = (radius < 0) ? 0 : radius;

	pimpl = new SphereImpl(radius, slices, stacks);

	generateVertices();
}


/**
 * Construtor de cópia.
 *
 * @param s Objeto de uma Sphere a ser copiado.
 */
Sphere::Sphere(const Sphere& s)
{
	pimpl = new SphereImpl(s.pimpl->getRadius(), s.pimpl->getSlices(), 
		                   s.pimpl->getStacks());
}


/**
 * Devolve o valor do raio da esfera.
 */
float Sphere::getRadius(void)
{
	return pimpl->getRadius();
}


/**
 * Devolve o número de stacks.
 */
int Sphere::getStacks(void)
{
	return pimpl->getStacks();
}


/**
 * Devolve o número de slices.
 */
int Sphere::getSlices(void)
{
	return pimpl->getSlices();
}


/**
 * Altera o valor do raio.
 */
void Sphere::setRadius(float radius)
{
	radius = (radius < 0) ? 0 : radius;
	pimpl->setRadius(radius);
}


/**
 * Altera o número de stacks.
 */
void Sphere::setStacks(int stacks)
{
	stacks = (stacks < 1) ? 1 : stacks;
	pimpl->setStacks(stacks);
}


/**
 * Altera o número de slices.
 */
void Sphere::setSlices(int slices)
{
	slices = (slices < 1) ? 1 : slices;
	pimpl->setSlices(slices);
}


/**
 * Método que cálcula todos as coordenadas de todos os pontos de uma esfera.
 */
void Sphere::generateVertices(void)
{
	std::vector<Vertex> vertices;
	std::vector<size_t> indexes;

	pimpl->generateSphere(vertices, indexes);

	for (size_t i = 0; i < vertices.size(); i++) {
		addVertex(vertices.at(i));
	}

	for (size_t i = 0; i < indexes.size(); i++) {
		addIndex(indexes.at(i));
	}
}


/**
 * Destrutor da classe Sphere.
 *
 * Liberta a memória ocupada pelo apontador para a parte privada da classe
 * Sphere.
 */
Sphere::~Sphere(void)
{
	if (pimpl != NULL) {
		delete pimpl;
		pimpl = NULL;
	}
}