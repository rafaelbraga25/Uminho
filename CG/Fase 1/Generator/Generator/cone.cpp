/**
 * @file cone.cpp
 *
 * Defini��o de m�todos para calcular as coordenadas dos pontos de um cone.
 *
 * @author Carlos Pereira - A61887
 * @author Jo�o Barreira  - A73831
 * @author Rafael Braga   - A61799
 */


#include "cone.h"
#include <cmath>

const float pi = 3.1415926f;

class Cone::ConeImpl {
	float radius;		// raio da base
	float height;		// altura do cone
	float alfa;		    // �ngulo ao centro em radianos
	float stackHeight;	// altura de uma stack
	size_t slices;		// n�mero de slices
	size_t stacks;		// n�mero de stacks


public:

	/**
	 * Construtor por defeito.
	 */
	ConeImpl(void)
	{
		radius = height = stackHeight = alfa = 0;
		slices = stacks = 0;
	}


	/**
	 * Construtor por par�metros.
	 *
	 * @param radius Raio da base do cone
	 * @param height Altura do cone
	 * @param slices N�mero de slices a utilizar
	 * @param stacks N�mero de stacks a utilizar
	 */
	ConeImpl(float radius, float height, size_t slices, size_t stacks)
	{
		this->radius = radius;
		this->height = height;
		this->slices = slices;
		this->stacks = stacks;
		
		// C�lculo do �ngulo ao centro
		alfa = (2 * pi) / ((float) slices);		  
		
		// C�lculo da altura de uma stack
		stackHeight = height / ((float) stacks);  
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
	size_t getStacks(void)
	{
		return stacks;
	}

	
	/**
	 * Devolve o n�mero de slices utilizadas.
	 */
	size_t getSlices(void)
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
	void setStacks(size_t stacks)
	{
		this->stacks = stacks;
		stackHeight = height / ((float)stacks);  
	}


	/**
	 * Altera o n�mero de slices.
	 */
	void setSlices(size_t slices)
	{
		this->slices = slices;

		alfa = (2 * pi) / ((float)slices);		  
	}


	/**
	 * Calcula, a partir dos dados recebidos no construtor, as coordenadas de 
	 * todos os pontos que pertencem � base do cone.
	 *
	 * @return Vetor com as coordenadas dos pontos.
	 */
	std::vector<Vertex> generateBase(void)
	{
		std::vector<Vertex> vertices;	// Coordenadas dos pontos a devolver
		float angle = 0;				// �ngulo ao centro
		

	    // Defini��o do primeiro ponto da base que � utilizado como 
		// refer�ncia na contru��o

		float x = 0;					// Coordenada em X
		float y = (-height) / 4;		// Coordenada em Y
		float z = radius;				// Coordenada em Z
		

		// Defini��o do centro da base
		Vertex center(0, y, 0);


		// Para cada slice utilizada calculam-se as coordenadas dos pontos 
		// que a caracterizam. */
		
		for (size_t i = 0; i < slices; i++) {
			// Primeiro ponto do tri�ngulo
			vertices.push_back(Vertex(x, y, z));	
			
			// Segundo ponto do tri�ngulo que � sempre o centro da base 
			vertices.push_back(center);				
			
			// C�lculo do �ngulo ao centro do terceiro ponto
			// que tamb�m � o �ngulo ao centro do primeiro
			// ponto do tri�ngulo da pr�xima slice 
			angle = alfa * (i + 1);					

			// C�lculo das coordenadas do terceiro ponto do tri�ngulo
			x = radius * sin(angle);				
			z = radius * cos(angle);			
			
			// Inser��o do terceiro ponto
			vertices.push_back(Vertex(x, y, z));	
		}

		return vertices;						
	}


	/**
	 * Calcula, a partir dos dados recebidos no construtor, as coordenadas de 
	 * todos os pontos que pertencem � superf�cie lateral do cone.
	 *
	 * @return Vetor com as coordenadas dos pontos.
	 */
	std::vector<Vertex> generateSides(void)
	{
		std::vector<Vertex> vertices;	// Coordenadas dos pontos a devolver
		float angle = 0;				// �ngulo ao centro


		// Coordenadas de refer�ncia
		float lowerR = 0;		// Raio do c�rculo dos 2 pontos inferiores
		float upperR = 0;		// Raio do c�rculo dos 2 pontos superiores
		float lowerH = 0;		// Coordenada em Y dos 2 pontos inferiores
		float upperH = 0;		// Coordenada em Y dos 2 pontos superiores


		// Pontos de refer�ncia para aplicar-se a regra da m�o direita
		float xA, yA, zA;		//Ponto A - canto inferior esquerdo
		float xB, yB, zB;		//Ponto B - canto inferior direito
		float xC, yC, zC;		//Ponto C - canto superior direito
		float xD, yD, zD;		//Ponto D - canto superior esquerdo


		// Para cada stack, calcula-se as alturas em que cada uma
		// est� compreendida e os raios dos c�rculos superior
		// e inferior onde est� inserida
		for (size_t i = 0; i < stacks; i++) {
			lowerH = i * stackHeight;
			upperH = (i + 1) * stackHeight;

			lowerR = radius - radius * lowerH / height;
			upperR = radius - radius * upperH / height;

			// Percorrem-se as slices e calculam-se as coordenadas
			// dos pontos de refer�ncia para a stack e slice atuais
			for (size_t j = 0; j < slices; j++) {
				angle =  alfa * j;

				// C�lculo das novas coordenadas do ponto A
				xA = lowerR * sin(angle);
				yA = lowerH - (height / 4);
				zA = lowerR * cos(angle);


				// C�lculo das novas coordenadas do ponto B
				xB = lowerR * sin(angle + alfa);
				yB = lowerH - (height / 4);
				zB = lowerR * cos(angle + alfa);

				// C�lculo das novas coordenadas do ponto C
				xC = upperR * sin(angle + alfa);
				yC = upperH - (height / 4);
				zC = upperR * cos(angle + alfa);

				// C�lculo das novas coordenadas do ponto D
				xD = upperR * sin(angle);
				yD = upperH - (height / 4);
				zD = upperR * cos(angle);


				// Inser��o dos pontos na estrutura com os resultados
				vertices.push_back(Vertex(xA, yA, zA));
				vertices.push_back(Vertex(xB, yB, zB));		
				vertices.push_back(Vertex(xC, yC, zC));		

				vertices.push_back(Vertex(xA, yA, zA));
				vertices.push_back(Vertex(xC, yC, zC));
				vertices.push_back(Vertex(xD, yD, zD));
			}
		}
	
		return vertices;
	}


	/**
	 * Destrutor por defeito.
	 */
	~ConeImpl(void) = default;
};


/**
 * Construtor por defeito.
 */
Cone::Cone(void) : pimpl{ new ConeImpl() } {}


/**
 * Construtor por par�metros.
 *
 * @param radius Raio da base do cone
 * @param height Altura do cone
 * @param slices N�mero de slices a utilizar
 * @param stacks N�mero de stacks a utilizar
 */
Cone::Cone(float radius, float height, size_t slices, size_t stacks)
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
size_t Cone::getStacks(void)
{
	return pimpl->getStacks();
}


/**
 * Devolve o n�mero de slices.
 */
size_t Cone::getSlices(void)
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
void Cone::setStacks(size_t stacks)
{
	stacks = (stacks < 1) ? 1 : stacks;
	pimpl->setStacks(stacks);
}


/**
 * Altera o n�mero de slices.
 */
void Cone::setSlices(size_t slices)
{
	slices = (slices < 1) ? 1 : slices;
	pimpl->setSlices(slices);
}


/**
 * M�todo que c�lcula todos as coordenadas de todos os pontos de um cone.
 */
void Cone::generateVertices(void)
{
	// Chama o m�todo que c�lcula as coordenadas da base
	std::vector<Vertex> verticesBase = pimpl->generateBase();

	// Chama o m�todo que c�lcula as coordenadas da superf�cie lateral
	std::vector<Vertex> verticesSides = pimpl->generateSides();

	// Adiciona os v�rtices da base ao vetor de v�rtices 
	for (size_t i = 0; i < verticesBase.size(); i++) {
		addVertex(verticesBase.at(i));
	}

	// Adiciona os v�rtices laterais ao vetor de v�rtices 
	for (size_t i = 0; i < verticesSides.size(); i++) {
		addVertex(verticesSides.at(i));
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