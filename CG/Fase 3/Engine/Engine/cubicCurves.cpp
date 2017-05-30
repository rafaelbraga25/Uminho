/**
 * @file cubicCurves.cpp
 * 
 * Definição de todos os métodos para se efetuarem cálculos entre matrizes e
 * vetores, bem como para o cálculo de pontos que definem curvas de Bezier e de
 * Catmull-Rom.
 *
 * @author Carlos Pereira - A61887
 * @author João Barreira  - A73831
 * @author Rafael Braga   - A61799
 *
 * @version 26-04-2017
 */


#include "cubicCurves.h"
#include <cmath>


#define CC 4 


// Matriz de Catmull-Rom
float catmullMatrix[CC][CC] = { { -0.5f,  1.5f, -1.5f,  0.5f },
	                            { 1.0f, -2.5f,  2.0f, -0.5f },
	                            { -0.5f,  0.0f,  0.5f,  0.0f },
	                            { 0.0f,  1.0f,  0.0f,  0.0f } };

// Matriz de bezier.
float bezierMatrix[CC][CC] = { { -1.0f, 3.0f, -3.0f, 1.0f },
                               { 3.0f, -6.0f, 3.0f, 0.0f },
                               { -3.0f, 3.0f, 0.0f, 0.0f },
                               { 1.0f,  0.0f, 0.0f, 0.0f } };


/**
 * Constroi uma matriz 4x4 à custa dos vetores x, y e z.
 *
 * @return O resultado é devolvido sob a forma de uma matriz na variável m.
 */
void buildRotMatrix(float* x, float* y, float* z, float* m)
{
	m[0] = x[0]; m[1] = x[1]; m[2] = x[2]; m[3] = 0;
	m[4] = y[0]; m[5] = y[1]; m[6] = y[2]; m[7] = 0;
	m[8] = z[0]; m[9] = z[1]; m[10] = z[2]; m[11] = 0;
	m[12] = 0; m[13] = 0; m[14] = 0; m[15] = 1;
}


/**
 * Dados dois vetores, calcula um vetor perpendicular a ambos.
 *
 * @param a   Primeiro vetor.
 * @param b   Segundo vetor.
 * @param res Resultado da operação entre os vetores a e b, ou seja um vetor
 *            perpendicular a ambos.
 */
void cross(float* a, float* b, float* res)
{
	res[0] = a[1] * b[2] - a[2] * b[1];
	res[1] = a[2] * b[0] - a[0] * b[2];
	res[2] = a[0] * b[1] - a[1] * b[0];
}


/**
 * Normaliza um vetor.
 *
 * @param a Vetor a ser normalizado.
 */
void normalize(float* a)
{
	float l = sqrt(a[0] * a[0] + a[1] * a[1] + a[2] * a[2]);

	a[0] = a[0] / l;
	a[1] = a[1] / l;
	a[2] = a[2] / l;
}


/**
 * Calcula a normal de um vetor.
 */
float length(float* v)
{
	float res = sqrt(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);

	return res;
}


/**
 * Efetua uma multiplicação de uma matriz por um vetor.
 *
 * @param m   Matriz a ser multiplicada.
 * @param v   Vetor a ser multiplicado.
 * @param res Resultado da operação de multiplicação.
 */
void multMatrixVector(float* m, float* v, float* res)
{
	for (int j = 0; j < CC; ++j) {
		res[j] = 0;

		for (int k = 0; k < CC; ++k) {
			res[j] += v[k] * m[j * CC + k];
		}
	}
}


/**
 * Calcula um ponto de uma curva de Catmull-Rom, bem como a sua derivada.
 * Os cálculos são efetuados através de quatro pontos (com coordenadas x, y e
 * z) e através de um determinado instante t.
 *
 * @param t     Variável dependente.
 * @param p0    Ponto p0 (com coordenadas x, y e z).
 * @param p0    Ponto p1 (com coordenadas x, y e z).
 * @param p0    Ponto p2 (com coordenadas x, y e z).
 * @param p0    Ponto p3 (com coordenadas x, y e z).
 * @param pos   Posição (x, y e z) pertencente a uma curva de Catmull-Rom a ser
 *              calculada.
 * @param deriv Derivada (x, y e z) pertencente a uma curva de Camull-Rom a ser
 *              calculada.
 */
void getCatmullRomPoint(float t,
	                    float* p0, float* p1, float* p2, float* p3,
	                    float* pos, float* deriv)
{
	// Calcula A = M * P

	float ax[CC];
	float ay[CC];
	float az[CC];

	float px[CC] = { p0[0], p1[0], p2[0], p3[0] };
	float py[CC] = { p0[1], p1[1], p2[1], p3[1] };
	float pz[CC] = { p0[2], p1[2], p2[2], p3[2] };

	float T[CC] = { t * t * t, t * t, t, 1 };
	float TDeriv[CC] = { 3 * (t * t), 2 * t, 1, 0 };

	multMatrixVector((float*)catmullMatrix, px, ax);
	multMatrixVector((float*)catmullMatrix, py, ay);
	multMatrixVector((float*)catmullMatrix, pz, az);

	// Calcula pos = T * A

	pos[0] = (T[0] * ax[0]) + (T[1] * ax[1]) + (T[2] * ax[2]) + (T[3] * ax[3]);
	pos[1] = (T[0] * ay[0]) + (T[1] * ay[1]) + (T[2] * ay[2]) + (T[3] * ay[3]);
	pos[2] = (T[0] * az[0]) + (T[1] * az[1]) + (T[2] * az[2]) + (T[3] * az[3]);

	// Calcula deriv = T' * A

	deriv[0] = (TDeriv[0] * ax[0]) + (TDeriv[1] * ax[1]) + (TDeriv[2] * ax[2]) + (TDeriv[3] * ax[3]);
	deriv[1] = (TDeriv[0] * ay[0]) + (TDeriv[1] * ay[1]) + (TDeriv[2] * ay[2]) + (TDeriv[3] * ay[3]);
	deriv[2] = (TDeriv[0] * az[0]) + (TDeriv[1] * az[1]) + (TDeriv[2] * az[2]) + (TDeriv[3] * az[3]);
}


/**
 * Calcula um ponto de uma curva de Bezier. Os cálculos são efetuados através
 * de três matrizes 4x4 (uma para cada coordenada x, y e z dos dezasseis
 * pontos necessários para o cálculo de uma superfície cúbica de Bezier), bem
 * como o valor da tesselagem em u e em v.
 *
 * @param u         Valor da tesselagem vertical.
 * @param v         Valor da tesselagem horizontal.
 * @param pMatrizX  Matriz com as coordendas x de dezasseis pontos.
 * @param pMatrizY  Matriz com as coordendas y de dezasseis pontos.
 * @param pMatrizZ  Matriz com as coordendas z de dezasseis pontos.
 * @param pos       Posição (x, y e z) pertencente a uma curva de Bezier a ser
 *                  calculada.
 */
void getBezierPoint(float u, float v, 
	                float** pMatrixX, float** pMatrixY, float** pMatrixZ,
	                float* pos)
{

	float uVec[CC] = { u * u * u, u * u, u, 1 };
	float vVec[CC] = { v * v * v, v * v, v, 1 };

	float mvVec[CC];
	float px[CC];
	float py[CC];
	float pz[CC];

	float mx[CC];
	float my[CC];
	float mz[CC];

	// Calcula M (transposta) * V
	multMatrixVector((float*)bezierMatrix, vVec, mvVec);

	// Calcula P * resultado anterior
	multMatrixVector((float*)pMatrixX, mvVec, px);
	multMatrixVector((float*)pMatrixY, mvVec, py);
	multMatrixVector((float*)pMatrixZ, mvVec, pz);

	// Calcula M * resultado anterior
	multMatrixVector((float*)bezierMatrix, px, mx);
	multMatrixVector((float*)bezierMatrix, py, my);
	multMatrixVector((float*)bezierMatrix, pz, mz);

	// Calcula U * resultado anterior
	pos[0] = (uVec[0] * mx[0]) + (uVec[1] * mx[1]) + (uVec[2] * mx[2]) + (uVec[3] * mx[3]);
	pos[1] = (uVec[0] * my[0]) + (uVec[1] * my[1]) + (uVec[2] * my[2]) + (uVec[3] * my[3]);
	pos[2] = (uVec[0] * mz[0]) + (uVec[1] * mz[1]) + (uVec[2] * mz[2]) + (uVec[3] * mz[3]);
}