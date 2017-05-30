/**
 * @file translation.cpp
 *
 * Definição de todos os métodos para se representar uma translação em OpenGL.
 *
 * @author Carlos Pereira - A61887
 * @author João Barreira  - A73831
 * @author Rafael Braga   - A61799
 *
 * @version 29-04-2017
 */


#include <cstddef>
#include "translation.h"
#include "cubicCurves.h"


class Translation::TranslationImpl {
	float x;                            // Valor de uma translação em x
	float y;                            // Valor de uma translação em y
	float z;                            // Valor de uma translação em z
	std::vector<Vertex> catmullPoints;  // Lista de pontos para uma curva do
	                                    // tipo Catmull-Rom
	size_t elapsedTime;                 // Tempo decorrido desde o ínicio da
	                                    // contagem de tempo
	float totalTime;                    // Tempo total da animação
	float timeAcc;                      // Tempo decorrido da animação
	float up[3];                        // Normal de um modelo


	/**
	 * Devolve o intervalo de tempo decorrido deste a última medida de tempo
	 * efetuada.
	 *
	 * @return Intervalo de tempo decorrido desde a última medida
	 */
	size_t getDeltaTime(void)
	{
		size_t actualTime = glutGet(GLUT_ELAPSED_TIME);
		size_t deltaTime = actualTime - elapsedTime;

		elapsedTime = actualTime;

		return deltaTime;
	}


	/**
	 * Para um instante de tempo, devolve as coordenadas globais de um ponto
	 * da curva Catmull-Rom.
	 *
	 * @param gt	Tempo global
	 * @param pos	Vetor com as coordenadas a serem retornadas
	 * @param deriv	Vetor da tangente às coordenadas calculadas
	 */
	void getGlobalCatmullRomPoint(float gt, float *pos, float *deriv) 
	{
		size_t numPoints = catmullPoints.size();
		int indexes[4];

		float t = gt * numPoints;
		int index = floor(t);
		
		// coordenadas que definem a curva Catmull-Rom
		// para depois calcular o ponto intermédio
		float p[12];	

		t = t - index;

		indexes[0] = (index + numPoints - 1) % numPoints;
		indexes[1] = (indexes[0] + 1) % numPoints;
		indexes[2] = (indexes[1] + 1) % numPoints;
		indexes[3] = (indexes[2] + 1) % numPoints;
		 
		for (size_t i = 0; i < 4; i++) {

			// cálculo das coordanas da curva
			p[i * 3] = catmullPoints.at(indexes[i]).getX();
			p[i * 3 + 1] = catmullPoints.at(indexes[i]).getY();
			p[i * 3 + 2] = catmullPoints.at(indexes[i]).getZ();
		}

		getCatmullRomPoint(t, p, p + 3, p + 6, p + 9, pos, deriv);
	}


public:

	/**
	 * Construtor por defeito.
	 */
	TranslationImpl(void)
	{
		x = y = z = 0.0;
		totalTime = timeAcc = 0.0;
		elapsedTime = 0;
		up[0] = 0.0;
		up[1] = 1.0;
		up[2] = 0.0;
	}


	/**
	 * Construtor por parâmetros.
	 *
	 * @param x Valor de uma translação em x.
	 * @param y Valor de uma translação em y.
 	 * @param z Valor de uma translação em z.
	 */
	TranslationImpl(float x, float y, float z)
	{
		this->x = x;
		this->y = y;
		this->z = z;

		totalTime = timeAcc = 0.0;
		elapsedTime = 0;

		up[0] = 0.0;
		up[1] = 1.0;
		up[2] = 0.0;
	}


	/**
	 * Construtor por parâmetros.
	 *
	 * @param x				Valor de uma translação em x.
	 * @param y				Valor de uma translação em y.
	 * @param z				Valor de uma translação em z.
	 * @param catmullPoints	Coordenadas dos pontos da curva Catmull-Rom.
	 * @param totalTime		Tempo total de translação.
	 */
	TranslationImpl(float x, float y, float z,
		            std::vector<Vertex> catmullPoints, float totalTime)
	{
		this->x = x;
		this->y = y;
		this->z = z;
		this->catmullPoints = catmullPoints;
		this->totalTime = totalTime;

		elapsedTime = 0;
		timeAcc = 0.0;

		up[0] = 0.0;
		up[1] = 1.0;
		up[2] = 0.0;
	}


	/**
	 * Devolve o valor de uma translação em x.
	 */
	float getX(void)
	{
		return x;
	}


	/**
	 * Devolve o valor de uma translação em y.
	 */
	float getY(void)
	{
		return y;
	}


	/**
	 * Devolve o valor de uma translação em z.
	 */
	float getZ(void)
	{
		return z;
	}


	/**
	 * Devolve um vector com as coordenadas dos pontos da curva.
	 */
	std::vector<Vertex> getCatmullPoints(void)
	{
		return catmullPoints;
	}


	/**
	 * Devolve o tempo total de translação na curva.
	 */
	float getTotalTime(void)
	{
		return totalTime;
	}


	/**
	 * Altera o valor de uma translação em x.
	 *
	 * @param x	Novo valor de x.
	 */
	void setX(float x)
	{
		this->x = x;
	}


	/**
	 * Altera o valor de uma translação em y.
	 *
	 * @param y	Novo valor de y.
	 */
	void setY(float y)
	{
		this->y = y;
	}


	/**
	 * Altera o valor de uma translação em z.
	 *
	 * @param z	Novo valor de z.
	 */
	void setZ(float z)
	{
		this->z = z;
	}


	/**
	 * Altera o vector com as coordenadas dos pontos da curva.
	 *
	 * @param catmullPoints	Novo vector com os pontos da curva.
	 */
	void setCatmullPoints(std::vector<Vertex> catmullPoints)
	{
		this->catmullPoints = catmullPoints;
		timeAcc = 0.0;
		elapsedTime = 0;
	}


	/**
	 * Altera o tempo total de translação.
	 *
	 * @param totalTime	Novo tempo total de translação.
	 */
	void setTotalTime(float totalTime)
	{
		this->totalTime = totalTime;
		timeAcc = 0.0;
		elapsedTime = 0;
	}


	/**
	 * Executa uma translação em x, y ou z em OpenGL.
	 */
	void execute(void)
	{
		float pos[3];
		float deriv[3];
		float z[3];

		// tempo decorrido desde a última medição de tempo
		size_t deltaTime = getDeltaTime();			

		// conversão de deltaTime em segundos
		float auxTime = ((float)deltaTime) / 1000.0;	

		// é somado ao acumulador de instantes de
		// tempo uma fatia de tempo proporcional
		// ao tempo total de translação
		timeAcc += (auxTime / (float)totalTime);	

		// Caso o acumulador seja superior a 1.0, já se passou o tempo
		// total de translação, logo inicia-se de novo o acumulador para
		// uma nova volta
		if (timeAcc >= 1.0) {	
			timeAcc = 0.0;
		}

		getGlobalCatmullRomPoint(timeAcc, pos, deriv);
		glTranslatef(pos[0], pos[1], pos[2]);
		
		// z é o vetor perpendicular aos vetores deriv e up
		cross(deriv, up, z);	
		normalize(z);

		// up é o vetor perpendicular aos vetores z e deriv
		cross(z, deriv, up);	
		normalize(up);

		normalize(deriv);

		float m[4][4] = {
			{ deriv[0], up[0], z[0], pos[0] },
			{ deriv[1], up[1], z[1], pos[1] },
			{ deriv[2], up[2], z[2], pos[2] },
			{ 0.0, 0.0, 0.0, 1.0 }
		};

		buildRotMatrix(deriv, up, z, (float*)m);
		glMultMatrixf((float*)m);
	}


	/**
	 * Destrutor da classe TranslationImpl (por defeito em c++).
	 */
	~TranslationImpl(void) = default;
};


/**
 * Construtor por defeito. Inicializa o apontador para a implementação da
 * classe Translation.
 */
Translation::Translation(void)
{
	pimpl = new TranslationImpl();
}


/**
 * Construtor por parâmetros. Inicializa o apontador para a implementação da
 * classe Translation através dos parâmetros recebidos.
 *
 * @param x Valor de uma translação em x.
 * @param y Valor de uma translação em y.
 * @param z Valor de uma translação em z.
 */
Translation::Translation(float x, float y, float z)
{
	pimpl = new TranslationImpl(x, y, z);
}


/**
 * Construtor por parâmetros. Inicializa o apontador para a implementação da
 * classe Translation através dos parâmetros recebidos.
 *
 * @param x					Valor de uma translação em x.
 * @param y					Valor de uma translação em y.
 * @param z					Valor de uma translação em z.
 * @param catmullPoints		Coordenadas dos pontos da curva Catmull-Rom.
 * @param totalTime			Tempo total de translação.
 */
Translation::Translation(float x, float y, float z, 
	                     std::vector<Vertex> catmullPoints, float totalTime)
{
	pimpl = new TranslationImpl(x, y, z, catmullPoints, totalTime);
}


/**
 * Construtor de cópia. Inicializa o apontador para a implementação da classe
 * Translation, recorrendo a uma deep copy de um objeto desta classe.
 *
 * @param t Objeto da classe Translation a copiar.
 */
Translation::Translation(const Translation& t)
{
	pimpl = new TranslationImpl(t.pimpl->getX(),
		                        t.pimpl->getY(), t.pimpl->getZ(),
		                        t.pimpl->getCatmullPoints(),
		                        t.pimpl->getTotalTime());
}


/**
 * Devolve o valor de uma translação em x.
 */
float Translation::getX(void)
{
	return pimpl->getX();
}


/**
 * Devolve o valor de uma translação em y.
 */
float Translation::getY(void)
{
	return pimpl->getY();
}


/**
 * Devolve o valor de uma translação em z.
 */
float Translation::getZ(void)
{
	return pimpl->getZ();
}


/**
 * Devolve um vector com as coordenadas dos pontos da curva.
 */
std::vector<Vertex> Translation::getCatmullPoints(void)
{
	return pimpl->getCatmullPoints();
}


/**
 * Devolve o tempo total de translação na curva.
 */
float Translation::getTotalTime(void)
{
	return pimpl->getTotalTime();
}


/**
 * Altera o valor de uma translação em x.
 */
void Translation::setX(float x)
{
	pimpl->setX(x);
}


/**
 * Altera o valor de uma translação em y.
 */
void Translation::setY(float y)
{
	pimpl->setY(y);
}


/**
 * Altera o valor de uma translação em z.
 */
void Translation::setZ(float z)
{
	pimpl->setZ(z);
}


/**
 * Altera o vector com as coordenadas dos pontos da curva.
 */
void Translation::setCatmullPoints(std::vector<Vertex> catmullPoints)
{
	pimpl->setCatmullPoints(catmullPoints);
}


/**
 * Altera o tempo total de translação.
 */
void Translation::setTotalTime(float totalTime)
{
	pimpl->setTotalTime(totalTime);
}


/**
 * Executa uma translação em x, y ou z em OpenGL.
 */
void Translation::execute(void)
{
	if (pimpl->getCatmullPoints().size() < 4) {
		glTranslatef(pimpl->getX(), pimpl->getY(), pimpl->getZ());
	}
	else {
		pimpl->execute();
	}
}


/**
 * Destrutor da classe Translation. Liberta a memória ocupada pelo apontador 
 * para a implementação da classe Translation.
 */
Translation::~Translation(void)
{
	if (pimpl != NULL) {
		delete pimpl;
		pimpl = NULL;
	}
}