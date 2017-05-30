/**
 * @file rotation.cpp
 *
 * Defini��o de todos os m�todos para se representar uma rota��o em OpenGL.
 *
 * @author Carlos Pereira - A61887
 * @author Jo�o Barreira  - A73831
 * @author Rafael Braga   - A61799
 *
 * @version 29-04-2017
 */


#include <cstddef>
#include "rotation.h"


class Rotation::RotationImpl {
	float angle;          // �ngulo de uma rota��o
	float x;              // Valor de uma rota��o em x
	float y;              // Valor de uma rota��o em y
	float z;              // Valor de uma rota��o em z
	float totalTime;      // Tempo total de uma rota��o 
	float timeAcc;        // Acumulado de tempo de uma rota��o
	size_t elapsedTime;   // Tempo total decorrido de uma rota��o


	/*
	 * C�lcula o tempo decorrido desde a �ltima rota��o.
	 *
	 * @return Tempo decorrido desde a �ltima rota��o.
	 */
	size_t getDeltaTime(void)
	{
		// � calculado o tempo total decorrido at� ao ponto atual
		size_t actualTime = glutGet(GLUT_ELAPSED_TIME);

		// O tempo decorrido desde a �ltima rota��o corresponde
		// � subtra��o do tempo atual pelo tempo total decorrido
		size_t deltaTime = actualTime - elapsedTime;

		// O tempo total decorrido passa a corresponder ao tempo
		// total decorrido at� ao ponto atual
		elapsedTime = actualTime;

		return deltaTime;
	}


public:


	/**
	 * Construtor por defeito.
	 */
	RotationImpl(void)
	{
		angle = x = y = z = 0.0f;
		totalTime = timeAcc = 0.0f;
		elapsedTime = 0;
	}


	/**
	 * Construtor por par�metros.
	 *
	 * @param angle �ngulo de uma rota��o
	 * @param x     Valor de uma rota��o em x.
	 * @param y     Valor de uma rota��o em y.
	 * @param z     Valor de uma rota��o em z.
	 */
	RotationImpl(float angle, float x, float y, float z)
	{
		this->angle = angle;
		this->x = x;
		this->y = y;
		this->z = z;
		totalTime = elapsedTime = 0;
		timeAcc = 0.0f;
	}


	/**
	 * Construtor por par�metros.
	 *
	 * @param angle     �ngulo de uma rota��o.
	 * @param totalTime Tempo total de uma rota��o.
	 * @param x         Valor de uma rota��o em x.
	 * @param y         Valor de uma rota��o em y.
	 * @param z         Valor de uma rota��o em z.
	 */
	RotationImpl(float angle, float totalTime, float x, float y, float z)
	{
		this->angle = angle;
		this->totalTime = totalTime;
		this->x = x;
		this->y = y;
		this->z = z;

		timeAcc = 0.0f;
		elapsedTime = 0;
	}


	/**
	 * Devolve o valor do �ngulo de uma rota��o.
	 */
	float getAngle(void)
	{
		return angle;
	}

	/**
	 * Devolve o valor do tempo total de uma rota��o em x.
	 */
	float getTotalTime(void)
	{
		return totalTime;
	}


	/**
	 * Devolve o valor de uma rota��o em x.
	 */
	float getX(void)
	{
		return x;
	}


	/**
	 * Devolve o valor de uma rota��o em y.
	 */
	float getY(void)
	{
		return y;
	}


	/**
	 * Devolve o valor de uma rota��o em z.
	 */
	float getZ(void)
	{
		return z;
	}


	/**
	 * Altera o valor do �ngulo de uma rota��o.
	 */
	void setAngle(float angle)
	{
		this->angle = angle;
	}


	/**
	 * Altera o valor do tempo total de uma rota��o.
	 */
	void setTotalTime(float totalTime)
	{
		this->totalTime = totalTime;
		timeAcc = 0.0f;
		elapsedTime = 0;
	}


	/**
	 * Altera o valor de uma rota��o em x.
	 */
	void setX(float x)
	{
		this->x = x;
	}


	/**
	 * Altera o valor de uma rota��o em y.
	 */
	void setY(float y)
	{
		this->y = y;
	}


	/**
	 * Altera o valor de uma rota��o em z.
	 */
	void setZ(float z)
	{
		this->z = z;
	}


	/**
	 * Efetua uma rota��o com um certo �ngulo em torno dos eixos x, y ou z em
	 * OpenGL.
	 */
	void execute(void)
	{
		// deltaTime corresponde ao tempo decorrido desde a �ltima rota��o
		size_t deltaTime = getDeltaTime();

		// � dividido por 1000 de forma a termos o tempo em segundos
		float auxTime = ((float)deltaTime) / 1000.0f;

		// Soma-se o tempo parcial da rota��o ao tempo acumulado
		timeAcc += auxTime;

		// Assim que o tempo acumulado atingir o tempo total da rota��o,
		// � colocado a zero
		if (timeAcc >= (float)totalTime) {
			timeAcc = 0.0;
		}

		float auxAngle = timeAcc * 360.0f / ((float)totalTime);

		// � efetuada uma rota��o em openGL correspondente cujo �ngulo
		// corresponde � divis�o do acumulado pelo tempo total. A rota��o
		// � efetuada em torno dos eixos definidos anteriormente.
		glRotatef(auxAngle, x, y, z);
	}


	/**
	 * Efetua uma rota��o com um certo �ngulo em torno dos eixos x, y ou z em
	 * OpenGL.
	 */
	void execute(FrustumCulling* f)
	{
		execute();
		f->rotateCoords(x, y, z, timeAcc * 360.0f / ((float)totalTime));
	}


	/**
	 * Destrutor da classe RotationImpl (por defeito em c++).
	 */
	~RotationImpl(void) = default;
};


/**
 * Construtor por defeito. Inicializa o apontador para a implementa��o da
 * classe Rotation.
 */
Rotation::Rotation(void)
{
	pimpl = new RotationImpl();
}


/**
 * Construtor por par�metros. Inicializa o apontador para a implementa��o da
 * classe Rotation atrav�s dos par�metros recebidos.
 *
 * @param angle     �ngulo de uma rota��o.
 * @param totalTime Tempo total de uma rota��o.
 * @param x         Valor de uma rota��o em x.
 * @param y         Valor de uma rota��o em y.
 * @param z         Valor de uma rota��o em z.
 */
Rotation::Rotation(float angle, float totalTime, float x, float y, float z)
{
	pimpl = new RotationImpl(angle, totalTime, x, y, z);
}


/**
 * Construtor de c�pia. Inicializa o apontador para a implementa��o da classe
 * Rotation, recorrendo a uma deep copy de um objeto desta classe.
 *
 * @param r Objeto da classe Rotation a copiar.
 */
Rotation::Rotation(const Rotation& r)
{
	pimpl = new RotationImpl(r.pimpl->getAngle(),
		r.pimpl->getTotalTime(),
		r.pimpl->getX(),
		r.pimpl->getY(),
		r.pimpl->getZ());
}


/**
 * Devolve o valor do �ngulo de uma rota��o.
 */
float Rotation::getAngle(void)
{
	return pimpl->getAngle();
}


/**
 * Devolve o valor do tempo total de uma rota��o.
 */
float Rotation::getTotalTime(void)
{
	return pimpl->getTotalTime();
}


/**
 * Devolve o valor de uma rota��o em x.
 */
float Rotation::getX(void)
{
	return pimpl->getX();
}


/**
 * Devolve o valor de uma rota��o em y.
 */
float Rotation::getY(void)
{
	return pimpl->getY();
}


/**
 * Devolve o valor de uma rota��o em z.
 */
float Rotation::getZ(void)
{
	return pimpl->getZ();
}


/**
 * Altera o valor do �ngulo de uma rota��o.
 */
void Rotation::setAngle(float angle)
{
	pimpl->setAngle(angle);
}


/**
 * Altera o valor do tempo total de uma rota��o.
 */
void Rotation::setTotalTime(float totalTime)
{
	pimpl->setTotalTime(totalTime);
}


/**
 * Altera o valor de uma rota��o em x.
 */
void Rotation::setX(float x)
{
	pimpl->setX(x);
}


/**
 * Altera o valor de uma rota��o em y.
 */
void Rotation::setY(float y)
{
	pimpl->setY(y);
}


/**
 * Altera o valor de uma rota��o em z.
 */
void Rotation::setZ(float z)
{
	pimpl->setZ(z);
}


/**
 * Efetua uma rota��o com um certo �ngulo em torno dos eixos x, y ou z em
 * OpenGL.
 */
void Rotation::execute(void)
{
	if (pimpl->getTotalTime() > 0) {
		pimpl->execute();
	}
	else {
		glRotatef(pimpl->getAngle(), pimpl->getX(), pimpl->getY(), pimpl->getZ());
	}
}


/**
 * Efetua uma rota��o com um certo �ngulo em torno dos eixos x, y ou z em
 * OpenGL.
 */
void Rotation::execute(FrustumCulling* f)
{
	if (pimpl->getTotalTime() > 0) {
		pimpl->execute(f);
	}
	else {
		glRotatef(pimpl->getAngle(), pimpl->getX(), pimpl->getY(), pimpl->getZ());
		f->rotateCoords(pimpl->getX(), pimpl->getY(), pimpl->getZ(), pimpl->getAngle());
	}
}


/**
 * Destrutor da classe Rotation. Liberta a mem�ria ocupada pelo apontador para
 * a implementa��o da classe Rotation.
 */
Rotation::~Rotation(void)
{
	if (pimpl != NULL) {
		delete pimpl;
		pimpl = NULL;
	}
}