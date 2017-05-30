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
 * @version 21-04-2017
 */


#ifndef cubicCurves_h
#define cubicCurves_h


void buildRotMatrix(float* x, float* y, float* z, float* m);


void cross(float* a, float* b, float* res);


void normalize(float* a);


float length(float* v);


void multMatrixVector(float* m, float* v, float* res);


void getCatmullRomPoint(float t, float* p0, float* p1, float* p2, float* p3,
	                    float* pos, float* deriv);


void getBezierPoint(float u, float v,
	                float** pMatrixX, float** pMatrixY, float** pMatrixZ,
	                float* pos);


#endif