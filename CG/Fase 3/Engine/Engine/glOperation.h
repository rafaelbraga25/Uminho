/**
 * @file glOperation.h
 *
 * Módulo que representa a classe base para uma operação qualquer em
 * OpenGL (translação, rotação, desenho de primitivas, etc).
 *
 * @author Carlos Pereira - A61887
 * @author João Barreira  - A73831
 * @author Rafael Braga   - A61799
 *
 * @version 26-03-2017
 */


#ifndef glOperation_h
#define glOperation_h


#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif


class GLOperation {

public:

	/**
	 * Construtor da classe Operation (por defeito em c++).
	 */
	GLOperation(void) = default;


	/**
	 * Método abstrato de uma qualquer operação em OpenGL.
	 */
	virtual void execute(void) = 0;


	/**
	 * Destrutor da classe Operation (por defeito em c++). Todas as classes
	 * derivadas desta classe implementam as suas versões deste destrutor.
	 */
	virtual ~GLOperation(void) = default;
};


#endif
