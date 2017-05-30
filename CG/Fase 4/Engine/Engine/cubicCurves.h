/**
 * @file cubicCurves.h
 *
 * @brief M�dulo que apresenta m�todos para a gera��o de pontos de superf�cies
 *        c�bicas de Bezier e de Catmull-Rom, bem como opera��es entre vetores
 *        e matrizes.
 *
 * @author Carlos Pereira - A61887
 * @author Jo�o Barreira  - A73831
 * @author Rafael Braga   - A61799
 * 
 * @version 12-05-2017
 */


#ifndef cubicCurves_h
#define cubicCurves_h


/**
 * Constroi uma matriz 4x4 � custa dos vetores x, y e z.
 *
 * @return O resultado � devolvido sob a forma de uma matriz na vari�vel m.
 */
void buildRotMatrix(float* x, float* y, float* z, float* m);


/**
 * Dados dois vetores, calcula um vetor perpendicular a ambos.
 *
 * @param a   Primeiro vetor.
 * @param b   Segundo vetor.
 * @param res Resultado da opera��o entre os vetores a e b, ou seja um vetor
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
 * Efetua uma multiplica��o de uma matriz por um vetor.
 *
 * @param m   Matriz a ser multiplicada.
 * @param v   Vetor a ser multiplicado.
 * @param res Resultado da opera��o de multiplica��o.
 */
void multMatrixVector(float* m, float* v, float* res);


/**
 * Calcula um ponto de uma curva de Catmull-Rom, bem como a sua derivada.
 * Os c�lculos s�o efetuados atrav�s de quatro pontos (com coordenadas x, y e 
 * z) e atrav�s de um determinado instante t.
 *
 * @param t     Vari�vel dependente.
 * @param p0    Ponto p0 (com coordenadas x, y e z).
 * @param p0    Ponto p1 (com coordenadas x, y e z).
 * @param p0    Ponto p2 (com coordenadas x, y e z).
 * @param p0    Ponto p3 (com coordenadas x, y e z).
 * @param pos   Posi��o (x, y e z) pertencente a uma curva de Catmull-Rom a ser
 *              calculada.
 * @param deriv Derivada (x, y e z) pertencente a uma curva de Camull-Rom a ser
 *              calculada.
 */
void getCatmullRomPoint(float t, float* p0, float* p1, float* p2, float* p3,
	                    float* pos, float* deriv);


/**
 * Calcula um ponto de uma curva de Bezier. Os c�lculos s�o efetuados atrav�s
 * de tr�s matrizes 4x4 (uma para cada coordenada x, y e z dos dezasseis
 * pontos necess�rios para o c�lculo de uma superf�cie c�bica de Bezier), bem
 * como o valor da tesselagem em u e em v. S�o tamb�m calculdas as derivadas
 * em u e em v.
 *
 * @param u         Valor da tesselagem vertical.
 * @param v         Valor da tesselagem horizontal.
 * @param pMatrizX  Matriz com as coordendas x de dezasseis pontos.
 * @param pMatrizY  Matriz com as coordendas y de dezasseis pontos.
 * @param pMatrizZ  Matriz com as coordendas z de dezasseis pontos. 
 * @param pos       Posi��o (x, y e z) pertencente a uma curva de Bezier a ser
 *                  calculada.
 * @param derivU    Derivada em u.
 * @param derivV    Derivada em v.
 */
void getBezierPoint(float u, float v,
	                float** pMatrixX, float** pMatrixY, float** pMatrixZ,
	                float* pos, float* derivU, float* derivV);


#endif