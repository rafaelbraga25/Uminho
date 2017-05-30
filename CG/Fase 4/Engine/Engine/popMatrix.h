/**
 * @file popMatrix.h
 *
 * Módulo que representa uma operação de popMatrix em OpenGL.
 *
 * @author Carlos Pereira - A61887
 * @author João Barreira  - A73831
 * @author Rafael Braga   - A61799
 * 
 * @version 26-03-2017
 */


#ifndef popMatrix_h
#define popMatrix_h


#include "glOperation.h"


class PopMatrix : public GLOperation {

public:


	/**
	 * Construtor por defeito.
	 */
	PopMatrix(void) = default;


	/**
	 * Executa uma operação de popMatrix em OpenGL.
	 */
	void execute(void)
	{
		glDisable(GL_LIGHT0);
		glDisable(GL_LIGHT1);
		glDisable(GL_LIGHT2);
		glDisable(GL_LIGHT3);
		glDisable(GL_LIGHT4);
		glDisable(GL_LIGHT5);
		glDisable(GL_LIGHT6);
		glDisable(GL_LIGHT7);
		glPopMatrix();
	}


	/**
	 * Executa uma operação de popMatrix em OpenGL.
	 */
	void execute(FrustumCulling* f)
	{
		execute();
		f->popCoords();
	}


	/**
	 * Destrutor (por defeito em c++).
	 */
	~PopMatrix(void) = default;
};

#endif 

