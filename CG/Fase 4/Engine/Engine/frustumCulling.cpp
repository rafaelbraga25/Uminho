/**
 * @file frustumCulling.cpp
 *
 * Defini��o de todos os m�todos para a representa��o do campo vis�vel.
 *
 * @author Carlos Pereira - A61887
 * @author Jo�o Barreira  - A73831
 * @author Rafael Braga   - A61799
 *
 * @version 12-05-2017
 */


#include <vector>
#include <stack>
#include "frustumCulling.h"
#include "plane.h"


#define RAD 0.01745329f // Valor de 1 grau em radianos
#define PI 3.14159265f


/** 
 * �ndices dos seis planos para a defini��o do campo vis�vel
 * (plano de cima, baixo, esquerda, direita, near e far).
 */
enum {
	TOP = 0, BOTTOM, LEFT, RIGHT, NEARP, FARP
};


class FrustumCulling::FrustumCullingImpl {

	float angle;                              // Fovy
	float ratio;                              // R�cio da janela
	float near;                               // Posi��o do plano near
	float far;                                // Posi��o do plano far
	float tang;                               // Tangente para o c�lculo das
	                                          // dimens�es de near e far
	float nw;                                 // Largura de near
	float nh;                                 // Altura de near
	float fw;                                 // Largura de far
	float fh;                                 // Altura de far
	std::vector<Plane> pl;                    // Planos do campo vis�vel
	std::stack<TripleFloat> coords;           // Coordenadas do centro
	                                          // onde s�o desenhadas as 
	                                          // primitivas
	std::stack<std::vector<float>> rotStack;  // Matrizes de rota��o
	std::vector<float> id;                    // Matriz identidade
	std::vector<float> rotMatrix;             // Matriz de rota��o auxiliar


	/**
	 * Efetua uma rota��o no eixo dos xx.
	 */
	void getXMatrix(float x, float angle)
	{
		rotMatrix.at(0) = 1.0f; rotMatrix.at(1) = 0.0f; rotMatrix.at(2) = 0.0f; 
		rotMatrix.at(3) = 0.0f; rotMatrix.at(4) = x * cos(angle); rotMatrix.at(5) = x * (-sin(angle)); 
		rotMatrix.at(6) = 0.0f; rotMatrix.at(7) = x * sin(angle); rotMatrix.at(8) = x * cos(angle); 
	}


	/**
	 * Efetua uma rota��o no eixo dos yy.
	 */
	void getYMatrix(float y, float angle)
	{
		rotMatrix.at(0) = y * cos(angle); rotMatrix.at(1) = 0.0f; rotMatrix.at(2) = y * sin(angle);
		rotMatrix.at(3) = 0.0f; rotMatrix.at(4) = 1.0f; rotMatrix.at(5) = 0.0f;
		rotMatrix.at(6) = y * (-sin(angle)); rotMatrix.at(7) = 0.0f; rotMatrix.at(8) = y * cos(angle);
	}


	/**
	 * Efetua uma rota��o no eixo dos zz.
	 */
	void getZMatrix(float z, float angle)
	{
		rotMatrix.at(0) = z * cos(angle); rotMatrix.at(1) = z * (-sin(angle)); rotMatrix.at(2) = 0.0f;
		rotMatrix.at(3) = z * sin(angle); rotMatrix.at(4) = z * cos(angle); rotMatrix.at(5) = 0.0f;
		rotMatrix.at(6) = 0.0f; rotMatrix.at(7) = 0.0f; rotMatrix.at(8) = 1.0f;
	}


	/**
	 * Multiplica uma matriz m pelo vetor v.
	 */
	TripleFloat multMatrixVector(std::vector<float> m, float* v)
	{
		size_t line = 3;
		float res[3];

		for (size_t j = 0; j < 3; j++) {
			res[j] = 0.0f;

			for (size_t k = 0; k < 3; k++) {
				res[j] += v[k] * m.at(j * line + k);
			}
		}

		return TripleFloat(res[0], res[1], res[2]);
	}


public:

	/**
	 * Construtor por defeito.
	 */
	FrustumCullingImpl(void)
	{
		angle = ratio = near = far = tang = nw = nh = fw = fh = 0.0f;

		// Inicializa-se o vetor com os seis planos
		for (size_t i = 0; i < 6; i++) {
			pl.push_back(Plane());
		}

		// No in�cio n�o foram efetuadas transla��es nem rota��es, por isso
		// a matriz de rota��o � igual � identidade
		for (size_t i = 0; i < 3; i++) {
			for (size_t j = 0; j < 3; j++) {
				if (i == j) {
					id.push_back(1.0f);
					rotMatrix.push_back(1.0f);
				}
				else {
					id.push_back(0.0f);
					rotMatrix.push_back(0.0f);
				}
			}
		}
	}


	/**
	 * Altera a perpectiva do campo vis�vel de acordo com os crit�rios
	 * recebidos. Esta fun��o deve ser invocada sempre que se invoca a
	 * fun��o gluPerspective.
	 *
	 * @param angle Fovy.
	 * @param ratio R�cio da janela.
	 * @param near  Posi��o do plano near no eixo dos zz.
	 * @param far   Posi��o do plano far no eixo dos zz.
	 */
	void setPerspective(float angle, float ratio, float near, float far)
	{
		this->angle = angle;
		this->ratio = ratio;
		this->near = near;
		this->far = far;

		// C�lculo das dimens�es dos planos near e far
		tang = tan(RAD * angle * 0.5f);
		nh = near * tang;
		nw = nh * ratio;
		fh = far * tang;
		fw = fh * ratio;
	}


	/**
	 * Altera as defini��es da camera. Esta fun��o deve ser invocada sempre
	 * que se invoca a fun��o gluLookAt. S�o calculadas as normais dos seis 
	 * planos de maneira a que estas estejam direcionadas para dentro do campo.
	 *
	 * @param pos  Posi��o da camera.
	 * @param look Posi��o para onde a camera est� apontada.
	 * @param up   Normal da camera.
	 */
	void setCam(TripleFloat pos, TripleFloat look, TripleFloat up)
	{
		TripleFloat aux;    // Vetor auxiliar nos c�lculos
		TripleFloat normal; // Vetor auxiliar que representa a normal de um plano
		TripleFloat nc;     // Centro do plano near
		TripleFloat fc;     // Centro do plano far
		TripleFloat X;      // Eixo x da camera
		TripleFloat Y;      // Eixo y da camera
		TripleFloat Z;      // Eixo z da camera

		// Calcula-se o eixo Z da camera. Este deve apontar na dire��o contr�ria
		// do vetor look
		Z = pos - look;
		Z.normalize();

		// Calcula-se o eixo X da camera
		X = up * Z;
		X.normalize();

		// Representa o c�lculo do vetor up "real"
		Y = Z * X;

		// C�lculo dos centros dos planos near e far
		nc = pos - Z.multWithScalar(near);
		fc = pos - Z.multWithScalar(far);

		// C�lculo das normais dos planos
		pl.at(NEARP).setNormalAndPoint(Z.multWithScalar(-1.0f), nc);
		pl.at(FARP).setNormalAndPoint(Z, fc);

		aux = (nc + Y.multWithScalar(nh)) - pos;
		aux.normalize();
		normal = aux * X;
		pl.at(TOP).setNormalAndPoint(normal, nc + Y.multWithScalar(nh));

		aux = (nc - Y.multWithScalar(nh)) - pos;
		aux.normalize();
		normal = X * aux;
		pl.at(BOTTOM).setNormalAndPoint(normal, nc - Y.multWithScalar(nh));

		aux = (nc - X.multWithScalar(nw)) - pos;
		aux.normalize();
		normal = aux * Y;
		pl.at(LEFT).setNormalAndPoint(normal, nc - X.multWithScalar(nw));

		aux = (nc + X.multWithScalar(nw)) - pos;
		aux.normalize();
		normal = Y * aux;
		pl.at(RIGHT).setNormalAndPoint(normal, nc + X.multWithScalar(nw));
	}


	/**
	 * Testa se um ponto est� dentro do campo vis�vel.
	 * Um ponto est� dentro do campo vis�vel se a sua dist�ncia a cada um dos
	 * seis p
lanos for maior ou igual a zero. Caso a dist�ncia seja negativa
	 * significa que o ponto se situa do lado contr�rio � normal de um plano, 
	 * ou seja, fora do campo vis�vel.
	 *
	 * @param point Ponto a testar.
	 */
	bool pointInFrustum(TripleFloat point)
	{
		bool res = true;

		for (size_t i = 0; i < 6 && res == true; i++) {
			if (pl.at(i).distanceFromPoint(point) < 0.0f) {
				res = false;
			}
		}

		return res;
	}


	/**
	 * Testa se um ponto est� dentro do campo vis�vel.
	 * Uma esfera est� dentro do campo vis�vel se a sua dist�ncia a cada um dos
	 * seis planos for maior ou igual a zero. Caso a dist�ncia seja negativa
	 * significa que a esfera se situa do lado contr�rio � normal de um plano,
	 * ou seja, fora do campo vis�vel.
	 *
	 * @param point  Centro da esfera.
	 * @param radius Raio da esfera.
	 */
	bool sphereInFrustum(TripleFloat point, float radius) {

		float distance = 0.0f;
		bool res = true;

		for (size_t i = 0; i < 6 && res == true; i++) {
			distance = pl.at(i).distanceFromPoint(point);

			if (distance < -radius) {
				res = false;
			}
		}

		return res;
	}

 
	/**
	 * Devolve as coordenadas atualizadas ap�s a �ltima transla��o.
	 */
	TripleFloat getCoords(void)
	{
		TripleFloat ret;

		if (coords.empty() == false) {
			ret = coords.top();
		}

		return ret;
	}


	/**
	 * Atualiza o centro onde as primitivas s�o desenhadas conforme as suas
	 * transla��es e rota��es. Deve ser invocada sempre que ocorre uma
	 * pushMatrix.
	 */
	void pushCoords(void)
	{
		// N�o houve transla��es, o centro � (0, 0, 0)
		if (coords.empty() == true) {
			coords.push(TripleFloat(0.0f, 0.0f, 0.0f));
		}
		else {
			TripleFloat aux(coords.top());

			coords.push(aux);
		}
		
		// N�o houve rota��es, a matriz de rota��o � igual � identiadade
		if (rotStack.empty() == true) {
			rotStack.push(id);
		}
		else {
			std::vector<float> aux = rotStack.top();
			rotStack.push(aux);
		}
	}


	/**
	 * Remove da stack as �ltimas coordenadas respetivas a transla��es e
	 * rota��es. Deve ser invocada sempre que ocorre uma popMatrix.
	 */
	void popCoords(void) 
	{
		if (coords.empty() == false) {
			coords.pop();
		}

		if (rotStack.empty() == false) {
			rotStack.pop();
		}
	}


	/**
	 * Translada o centro onde ser�o desenhadas as primitivas. Deve ser
	 * invocada sempre que ocorre uma glTranslate.
	 */
	void translateCoords(float x, float y, float z)
	{
		float aux[3] = { x, y, z };
		TripleFloat res;

		res = multMatrixVector(rotStack.top(), aux);
	
		TripleFloat oldCoord(coords.top());
		TripleFloat newCoord = oldCoord + res; 

		coords.pop();
		coords.push(newCoord);
	}


	/**
	 * Efetua uma rota��o sobre o centro onde ser�o desenhadas as primitivas.
	 * Deve ser invocada sempre que ocorre uma glRotate.
	 */
	void rotateCoords(float axisX, float axisY, float axisZ, float angle)
	{
		angle = angle * PI / 180.0f;

		if (axisX != 0.0f) {
			getXMatrix(axisX, angle);
		}
		else if (axisY != 0.0f) {
			getYMatrix(axisY, angle);
		}
		else if (axisZ != 0.0f) {
			getZMatrix(axisZ, angle);
		}

		rotStack.pop();
		rotStack.push(rotMatrix);
	}


	/**
	 * Destrutor.
	 */
	~FrustumCullingImpl(void) = default;

};


/**
 * Construtor por defeito.
 */
FrustumCulling::FrustumCulling(void)
{
	pimpl = new FrustumCullingImpl();
}


/**
 * Construtor de c�pia.
 *
 * @param f Objeto da classe FrustumCulling a copiar.
 */
FrustumCulling::FrustumCulling(const FrustumCulling& f)
{
	pimpl = new FrustumCullingImpl();
}


/**
 * Altera a perpectiva do campo vis�vel de acordo com os crit�rios
 * recebidos. Esta fun��o deve ser invocada sempre que se invoca a
 * fun��o gluPerspective.
 *
 * @param angle Fovy.
 * @param ratio R�cio da janela.
 * @param near  Posi��o do plano near no eixo dos zz.
 * @param far   Posi��o do plano far no eixo dos zz.
 */
void FrustumCulling::setPerspective(float angle, float ratio, float near, float far)
{
	pimpl->setPerspective(angle, ratio, near, far);
}


/**
 * Altera as defini��es da camera. Esta fun��o deve ser invocada sempre
 * que se invoca a fun��o gluLookAt.
 *
 * @param pos  Posi��o da camera.
 * @param look Posi��o para onde a camera est� apontada.
 * @param up   Normal da camera.
 */
void FrustumCulling::setCam(TripleFloat pos, TripleFloat look, TripleFloat up)
{
	pimpl->setCam(pos, look, up);
}


/**
 * Testa se um ponto se situa no campo vis�vel.
 *
 * @param point Ponto a testar.
 */
bool FrustumCulling::pointInFrustum(TripleFloat point)
{
	return pimpl->pointInFrustum(point);
}


/**
 * Testa se uma esfera se situa no campo vis�vel.
 *
 * @param point  Origem da esfera.
 * @param radius Raio da esfera.
 */
bool FrustumCulling::sphereInFrustum(TripleFloat point, float radius)
{
	return pimpl->sphereInFrustum(point, radius);
}


/**
 * Devolve as coordenadas atualizadas ap�s a �ltima transla��o.
 */
TripleFloat FrustumCulling::getCoords(void)
{
	return pimpl->getCoords();
}


/**
 * Atualiza o centro onde as primitivas s�o desenhadas conforme as suas
 * transla��es e rota��es. Deve ser invocada sempre que ocorre uma
 * pushMatrix.
 */
void FrustumCulling::pushCoords(void)
{
	pimpl->pushCoords();
}


/**
 * Remove da stack as �ltimas coordenadas respetivas a transla��es e
 * rota��es. Deve ser invocada sempre que ocorre uma popMatrix.
 */
void FrustumCulling::popCoords(void)
{
	pimpl->popCoords();
}


/**
 * Translada o centro onde ser�o desenhadas as primitivas. Deve ser
 * invocada sempre que ocorre uma glTranslate.
 */
void FrustumCulling::translateCoords(float x, float y, float z)
{
	pimpl->translateCoords(x, y, z);
}


/**
 * Efetua uma rota��o sobre o centro onde ser�o desenhadas as primitivas.
 * Deve ser invocada sempre que ocorre uma glRotate.
 */
void FrustumCulling::rotateCoords(float axisX, float axisY, float axisZ, float angle)
{
	pimpl->rotateCoords(axisX, axisY, axisZ, angle);
}


/**
 * Destrutor.
 */
FrustumCulling::~FrustumCulling(void)
{
	if (pimpl != NULL) {
		delete pimpl;
		pimpl = NULL;
	}
}