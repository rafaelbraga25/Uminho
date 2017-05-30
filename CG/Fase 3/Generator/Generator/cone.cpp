/**
 * @file cone.cpp
 *
 * Defini��o de m�todos para calcular as coordenadas dos pontos de um cone.
 *
 * @author Carlos Pereira - A61887
 * @author Jo�o Barreira  - A73831
 * @author Rafael Braga   - A61799
 *
 * @version 30-4-2017
 */


#include "cone.h"
#include <cmath>


const float pi = 3.1415926f;


class Cone::ConeImpl {
	float radius;		// raio da base
	float height;		// altura do cone
	float alfa;		    // �ngulo ao centro em radianos
	float stackHeight;	// altura de uma stack
	int slices;		    // n�mero de slices
	int stacks;		    // n�mero de stacks
	size_t index;       // �ndice atual do conjunto de �ndices

	
	/**
	 * Calcula, a partir dos dados recebidos no construtor, as coordenadas de
	 * todos os pontos que pertencem � base do cone.
	 *
	 * @param vertices Conjunto de v�rtices.
	 * @param indexes  Conjunto de �ndices.
	 * @return O resultado � guardado em vertices e em indexes.
	 */
	void generateBase(std::vector<Vertex>& vertices,
		              std::vector<size_t>& indexes)
	{
		float angle = 0.0f;	// �ngulo ao centro


		// Defini��o do primeiro ponto da base que � utilizado como 
		// refer�ncia na contru��o

		float x = 0.0f;					// Coordenada em X
		float y = (-height) / 4.0f;		// Coordenada em Y
		float z = radius;				// Coordenada em Z
		bool firstIt = true;            // Flag que verifica se � a primeira
		                                // itera��o da gera��o da base

		vertices.push_back(Vertex(x, y, z));

		// Defini��o do centro da base
		vertices.push_back(Vertex(0, y, 0));



		// Para cada slice utilizada calculam-se as coordenadas dos pontos 
		// que a caracterizam. 
		for (size_t i = 0; i < (size_t)slices; i++) {
			
			// Primeiro ponto do tri�ngulo (�ndice da itera��o anterior)
			indexes.push_back(index);

			// Segundo ponto do tri�ngulo que � sempre o centro da base 
			indexes.push_back(1);

			if (firstIt == true) {
				firstIt = false;
				index++;
			}

			// C�lculo do �ngulo ao centro do terceiro ponto
			// que tamb�m � o �ngulo ao centro do primeiro
			// ponto do tri�ngulo da pr�xima slice 
			angle += alfa;

			// C�lculo das coordenadas do terceiro ponto do tri�ngulo
			x = radius * sin(angle);
			z = radius * cos(angle);

			// Inser��o do terceiro ponto
			vertices.push_back(Vertex(x, y, z));
			indexes.push_back(++index);
		}

		// Final dos �ndices da base
		index++;
	}


	/**
	 * Calcula, a partir dos dados recebidos no construtor, as coordenadas de
	 * todos os pontos que pertencem � superf�cie lateral do cone.
	 *
	 * @param vertices Conjunto de v�rtices.
	 * @param indexes  Conjunto de �ndices.
	 * @return O resultado � guardado em vertices e em indexes.
	 */
	void generateSides(std::vector<Vertex>& vertices,
		               std::vector<size_t>& indexes)
	{
		float angle = 0.0f;		// �ngulo ao centro
		float r = 0.0f;
		float x = 0.0f;
		float y = 0.0f;
		float z = 0.0f;

		// Para cada stack, calcula-se o raio do seu c�rculo
		for (size_t i = 0; i <= (size_t)stacks; i++) {
			r = radius - (radius * ((stacks - i) * stackHeight) / height);

			// Percorrem-se as slices e calculam-se as coordenadas
			// dos pontos de refer�ncia para a stack e slice atuais
			for (size_t j = 0; j <= (size_t)slices; j++) {
				angle = alfa * (float)j;

				x = r * sin(angle);
				y = height - (i * stackHeight) - (height / 4.0f);
				z = r * cos(angle);

				vertices.push_back(Vertex(x, y, z));
			}
		}

		for (size_t i = 0; i < (size_t)stacks; i++) {
			for (size_t j = 0; j < (size_t)slices; j++) {
				indexes.push_back(i * (slices + 1) + j + index);
				indexes.push_back((i + 1) * (slices + 1) + j + 1 + index);
				indexes.push_back(i * (slices + 1) + j + 1 + index);

				indexes.push_back(i * (slices + 1) + j + index);
				indexes.push_back((i + 1) * (slices + 1) + j + index);
				indexes.push_back((i + 1) * (slices + 1) + j + 1 + index);
			}
		}
	}


public:

	/**
	 * Construtor por defeito.
	 */
	ConeImpl(void)
	{
		radius = height = stackHeight = alfa = 0;
		slices = stacks = 0;
		index = 0;
	}


	/**
	 * Construtor por par�metros.
	 *
	 * @param radius Raio da base do cone
	 * @param height Altura do cone
	 * @param slices N�mero de slices a utilizar
	 * @param stacks N�mero de stacks a utilizar
	 */
	ConeImpl(float radius, float height, int slices, int stacks)
	{
		this->radius = radius;
		this->height = height;
		this->slices = slices;
		this->stacks = stacks;
		
		// C�lculo do �ngulo ao centro
		alfa = (2 * pi) / ((float) slices);		  
		
		// C�lculo da altura de uma stack
		stackHeight = height / ((float) stacks);  
		
		index = 0;
	}


	/**
	 * Devolve o valor do raio da base.
	 */
	float getRadius(void)
	{
		return radius;
	}

	
	/**
	 * Devolve a altura do cone.
	 */
	float getHeight(void)
	{
		return height;
	}


	/**
	 * Devolve o �ngulo ao centro.
	 */
	float getAlfa(void)
	{
		return alfa;
	}


	/**
	 * Devolve a altura de uma stack.
	 */
	float getStackHeight(void)
	{
		return stackHeight;
	}


	/**
	 * Devolve o n�mero de stacks utilizadas.
	 */
	int getStacks(void)
	{
		return stacks;
	}

	
	/**
	 * Devolve o n�mero de slices utilizadas.
	 */
	int getSlices(void)
	{
		return slices;
	}


	/**
	 * Altera o valor do raio.
	 */
	void setRadius(float radius)
	{
		this->radius = radius;
	}


	/**
	 * Altera o valor da altura.
	 */
	void setHeight(float height)
	{
		this->height = height;
		stackHeight = height / ((float)stacks);  
	}


	/**
	 * Altera o n�mero de stacks.
	 */
	void setStacks(int stacks)
	{
		this->stacks = stacks;
		stackHeight = height / ((float)stacks);  
	}


	/**
	 * Altera o n�mero de slices.
	 */
	void setSlices(int slices)
	{
		this->slices = slices;

		alfa = (2 * pi) / ((float)slices);		  
	}


	/**
	 * Gera o conjunto de v�rtices de um cone, bem como o conjunto de �ndices
	 * associado a este vetor.
	 *
	 * @param vertices Conjunto de v�rtices.
	 * @param indexes  Conjunto de �ndices.
	 * @return O resultado � guardado em vertices e em indexes.
	 */
	void generateCone(std::vector<Vertex>& vertices,
		              std::vector<size_t>& indexes)
	{
		// Gera os v�rtices da base e dos lados do cone
		generateBase(vertices, indexes);
		generateSides(vertices, indexes);
	}


	/**
	 * Destrutor por defeito.
	 */
	~ConeImpl(void) = default;
};


/**
 * Construtor por defeito.
 */
Cone::Cone(void)
{
	pimpl = new ConeImpl();
}


/**
 * Construtor por par�metros.
 *
 * @param radius Raio da base do cone
 * @param height Altura do cone
 * @param slices N�mero de slices a utilizar
 * @param stacks N�mero de stacks a utilizar
 */
Cone::Cone(float radius, float height, int slices, int stacks)
{
	// O valor do raio e da altura t�m que ser positivos
	radius = (radius < 0) ? 0 : radius;
	height = (height < 0) ? 0 : height;

	// Por defeito, o n�mero de slices e de stacks � sempre maior ou igual a 1
	slices = (slices < 1) ? 1 : slices;	
	stacks = (stacks < 1) ? 1 : stacks; 

	pimpl = new ConeImpl(radius, height, slices, stacks);

	generateVertices();
}


/**
 * Construtor de c�pia.
 *
 * @param c Objeto da classe Cone a ser copiado.
 */
Cone::Cone(const Cone& c)
{
	pimpl = new ConeImpl(c.pimpl->getRadius(), c.pimpl->getHeight(),
		                 c.pimpl->getSlices(), c.pimpl->getStacks());
}


/**
 * Devolve o valor do raio da base.
 */
float Cone::getRadius(void)
{
	return pimpl->getRadius();
}


/**
 * Devolve a altura do cone.
 */
float Cone::getHeight(void)
{
	return pimpl->getHeight();
}


/**
 * Devolve o n�mero de stacks.
 */
int Cone::getStacks(void)
{
	return pimpl->getStacks();
}


/**
 * Devolve o n�mero de slices.
 */
int Cone::getSlices(void)
{
	return pimpl->getSlices();
}


/**
 * Altera o valor do raio.
 */
void Cone::setRadius(float radius)
{
	radius = (radius < 0) ? 0 : radius;
	pimpl->setRadius(radius);
}


/**
 * Altera o valor da altura.
 */
void Cone::setHeight(float height)
{
	height = (height < 0) ? 0 : height;
	pimpl->setHeight(height);
}


/**
 * Altera o n�mero de stacks.
 */
void Cone::setStacks(int stacks)
{
	stacks = (stacks < 1) ? 1 : stacks;
	pimpl->setStacks(stacks);
}


/**
 * Altera o n�mero de slices.
 */
void Cone::setSlices(int slices)
{
	slices = (slices < 1) ? 1 : slices;
	pimpl->setSlices(slices);
}


/**
 * M�todo que c�lcula todos as coordenadas de todos os pontos de um cone.
 */
void Cone::generateVertices(void)
{
	std::vector<Vertex> vertices;
	std::vector<size_t> indexes;

	pimpl->generateCone(vertices, indexes);

	for (size_t i = 0; i < vertices.size(); i++) {
		addVertex(vertices.at(i));
	}

	for (size_t i = 0; i < indexes.size(); i++) {
		addIndex(indexes.at(i));
	}
}



/**
 * Destrutor da classe Cone.
 *
 * Liberta a mem�ria ocupada pelo apontador para a parte privada da classe
 * Cone.
 */
Cone::~Cone(void)
{
	if (pimpl != NULL) {
		delete pimpl;
		pimpl = NULL;
	}
}