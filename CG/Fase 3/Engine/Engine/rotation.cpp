/**
 * @file rotation.cpp
 *
 * Definição de todos os métodos para se representar uma rotação em OpenGL.
 *
 * @author Carlos Pereira - A61887
 * @author João Barreira  - A73831
 * @author Rafael Braga   - A61799
 *
 * @version 29-04-2017
 */


#include <cstddef>
#include "rotation.h"


class Rotation::RotationImpl {
	float angle;          // Ângulo de uma rotação
	float x;              // Valor de uma rotação em x
	float y;              // Valor de uma rotação em y
	float z;              // Valor de uma rotação em z
	float totalTime;      // Tempo total de uma rotação 
	float timeAcc;        // Acumulado de tempo de uma rotação
	size_t elapsedTime;   // Tempo total decorrido de uma rotação


	/*
	 * Cálcula o tempo decorrido desde a última rotação.
	 *
	 * @return Tempo decorrido desde a última rotação.
	 */
	size_t getDeltaTime(void)
	{
		// É calculado o tempo total decorrido até ao ponto atual
		size_t actualTime = glutGet(GLUT_ELAPSED_TIME);

		// O tempo decorrido desde a última rotação corresponde
		// à subtração do tempo atual pelo tempo total decorrido
		size_t deltaTime = actualTime - elapsedTime;

		// O tempo total decorrido passa a corresponder ao tempo
		// total decorrido até ao ponto atual
		elapsedTime = actualTime;

		return deltaTime;
	}


public:


	/**
	 * Construtor por defeito.
	 */
	RotationImpl(void)
	{
		angle = x = y = z = 0.0;
		totalTime = timeAcc = 0.0;
		elapsedTime = 0;
	}


	/**
	 * Construtor por parâmetros.
	 *
	 * @param angle Ângulo de uma rotação
	 * @param x     Valor de uma rotação em x.
	 * @param y     Valor de uma rotação em y.
	 * @param z     Valor de uma rotação em z.
	 */
	RotationImpl(float angle, float x, float y, float z)
	{
		this->angle = angle;
		this->x = x;
		this->y = y;
		this->z = z;
		totalTime = elapsedTime = 0;
		timeAcc = 0;
	}


	/**
	 * Construtor por parâmetros.
	 *
	 * @param angle     Ângulo de uma rotação.
	 * @param totalTime Tempo total de uma rotação.
	 * @param x         Valor de uma rotação em x.
	 * @param y         Valor de uma rotação em y.
	 * @param z         Valor de uma rotação em z.
	 */
	RotationImpl(float angle, float totalTime, float x, float y, float z)
	{
		this->angle = angle;
		this->totalTime = totalTime;
		this->x = x;
		this->y = y;
		this->z = z;

		timeAcc = 0.0;
		elapsedTime = 0;
	}


	/**
	 * Devolve o valor do ângulo de uma rotação.
	 */
	float getAngle(void)
	{
		return angle;
	}

	/**
	 * Devolve o valor do tempo total de uma rotação em x.
	 */
	float getTotalTime(void)
	{
		return totalTime;
	}


	/**
	 * Devolve o valor de uma rotação em x.
	 */
	float getX(void)
	{
		return x;
	}


	/**
	 * Devolve o valor de uma rotação em y.
	 */
	float getY(void)
	{
		return y;
	}


	/**
	 * Devolve o valor de uma rotação em z.
	 */
	float getZ(void)
	{
		return z;
	}


	/**
	 * Altera o valor do ângulo de uma rotação.
	 */
	void setAngle(float angle)
	{
		this->angle = angle;
	}


	/**
	 * Altera o valor do tempo total de uma rotação.
	 */
	void setTotalTime(float totalTime)
	{
		this->totalTime = totalTime;
		timeAcc = 0.0;
		elapsedTime = 0;
	}


	/**
	 * Altera o valor de uma rotação em x.
	 */
	void setX(float x)
	{
		this->x = x;
	}


	/**
	 * Altera o valor de uma rotação em y.
	 */
	void setY(float y)
	{
		this->y = y;
	}


	/**
	 * Altera o valor de uma rotação em z.
	 */
	void setZ(float z)
	{
		this->z = z;
	}


	/**
	 * Efetua uma rotação com um certo ângulo em torno dos eixos x, y ou z em
	 * OpenGL.
	 */
	void execute(void)
	{
		// deltaTime corresponde ao tempo decorrido desde a última rotação
		size_t deltaTime = getDeltaTime();

		// É dividido por 1000 de forma a termos o tempo em segundos
		float auxTime = ((float)deltaTime) / 1000.0;

		// Soma-se o tempo parcial da rotação ao tempo acumulado
		timeAcc += auxTime;

		// Assim que o tempo acumulado atingir o tempo total da rotação,
		// é colocado a zero
		if (timeAcc >= (float)totalTime) {
			timeAcc = 0.0;
		}

		// É efetuada uma rotação em openGL correspondente cujo ângulo
		// corresponde à divisão do acumulado pelo tempo total. A rotação
		// é efetuada em torno dos eixos definidos anteriormente.
		glRotatef(timeAcc * 360.0 / ((float)totalTime), x, y, z);
	}


	/**
	 * Destrutor da classe RotationImpl (por defeito em c++).
	 */
	~RotationImpl(void) = default;
};


/**
 * Construtor por defeito. Inicializa o apontador para a implementação da
 * classe Rotation.
 */
Rotation::Rotation(void)
{
	pimpl = new RotationImpl();
}


/**
 * Construtor por parâmetros. Inicializa o apontador para a implementação da
 * classe Rotation através dos parâmetros recebidos.
 *
 * @param angle     Ângulo de uma rotação.
 * @param totalTime Tempo total de uma rotação.
 * @param x         Valor de uma rotação em x.
 * @param y         Valor de uma rotação em y.
 * @param z         Valor de uma rotação em z.
 */
Rotation::Rotation(float angle, float totalTime, float x, float y, float z)
{
	pimpl = new RotationImpl(angle, totalTime, x, y, z);
}


/**
 * Construtor de cópia. Inicializa o apontador para a implementação da classe
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
 * Devolve o valor do ângulo de uma rotação.
 */
float Rotation::getAngle(void)
{
	return pimpl->getAngle();
}


/**
 * Devolve o valor do tempo total de uma rotação.
 */
float Rotation::getTotalTime(void)
{
	return pimpl->getTotalTime();
}


/**
 * Devolve o valor de uma rotação em x.
 */
float Rotation::getX(void)
{
	return pimpl->getX();
}


/**
 * Devolve o valor de uma rotação em y.
 */
float Rotation::getY(void)
{
	return pimpl->getY();
}


/**
 * Devolve o valor de uma rotação em z.
 */
float Rotation::getZ(void)
{
	return pimpl->getZ();
}


/**
 * Altera o valor do ângulo de uma rotação.
 */
void Rotation::setAngle(float angle)
{
	pimpl->setAngle(angle);
}


/**
 * Altera o valor do tempo total de uma rotação.
 */
void Rotation::setTotalTime(float totalTime)
{
	pimpl->setTotalTime(totalTime);
}


/**
 * Altera o valor de uma rotação em x.
 */
void Rotation::setX(float x)
{
	pimpl->setX(x);
}


/**
 * Altera o valor de uma rotação em y.
 */
void Rotation::setY(float y)
{
	pimpl->setY(y);
}


/**
 * Altera o valor de uma rotação em z.
 */
void Rotation::setZ(float z)
{
	pimpl->setZ(z);
}


/**
 * Efetua uma rotação com um certo ângulo em torno dos eixos x, y ou z em
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
 * Destrutor da classe Rotation. Liberta a memória ocupada pelo apontador para
 * a implementação da classe Rotation.
 */
Rotation::~Rotation(void)
{
	if (pimpl != NULL) {
		delete pimpl;
		pimpl = NULL;
	}
}