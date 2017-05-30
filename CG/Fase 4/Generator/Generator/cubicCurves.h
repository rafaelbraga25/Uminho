/**
 * @file cubicCurves.h
 *
 * @brief Módulo que apresenta métodos para se efetuar uma translação em OpenGL.
 *
 * Uma translação pode ser definida à custa dos valores de x, y e z.
 *
 * @author Carlos Pereira - A61887
 * @author João Barreira  - A73831
 * @author Rafael Braga   - A61799
 * 
 * @version 02-05-2017
 */


#ifndef cubicCurves_h
#define cubicCurves_h


 /**
  * Constroi uma matriz 4x4 à custa dos vetores x, y e z.
  *
  * @return O resultado é devolvido sob a forma de uma matriz na variável m.
  */
void buildRotMatrix(float* x, float* y, float* z, float* m);


/**
 * Dados dois vetores, calcula um vetor perpendicular a ambos.
 *
 * @param a   Primeiro vetor.
 * @param b   Segundo vetor.
 * @param res Resultado da operação entre os vetores a e b, ou seja um vetor
 *            perpendicular a ambos.
 */
void cross(float* a, float* b, float* res);


/**
 * Normaliza um vetor.
 *
 * @param a Vetor a ser normalizado.
 */
void normalize(float* a);


/**
 * Calcula a normal de um vetor.
 */
float length(float* v);


/**
 * Efetua uma multiplicação de uma matriz por um vetor.
 *
 * @param m   Matriz a ser multiplicada.
 * @param v   Vetor a ser multiplicado.
 * @param res Resultado da operação de multiplicação.
 */
void multMatrixVector(float* m, float* v, float* res);


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
void getCatmullRomPoint(float t, float* p0, float* p1, float* p2, float* p3,
	                    float* pos, float* deriv);


/**
 * Calcula um ponto de uma curva de Bezier. Os cálculos são efetuados através
 * de três matrizes 4x4 (uma para cada coordenada x, y e z dos dezasseis
 * pontos necessários para o cálculo de uma superfície cúbica de Bezier), bem
 * como o valor da tesselagem em u e em v. São também calculdas as derivadas 
 * em u e em v.
 *
 * @param u         Valor da tesselagem vertical.
 * @param v         Valor da tesselagem horizontal.
 * @param pMatrizX  Matriz com as coordendas x de dezasseis pontos.
 * @param pMatrizY  Matriz com as coordendas y de dezasseis pontos.
 * @param pMatrizZ  Matriz com as coordendas z de dezasseis pontos.
 * @param pos       Posição (x, y e z) pertencente a uma curva de Bezier a ser
 *                  calculada.
 * @param derivU    Derivada em u.
 * @param derivV    Derivada em v.
 */
void getBezierPoint(float u, float v,
	                float** pMatrixX, float** pMatrixY, float** pMatrixZ,
	                float* pos, float* derivU, float* derivV);


#endif