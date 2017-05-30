/**
 * @file main.cpp
 *
 * @brief Defini��o de todos m�todos para o funcionamento do programa Engine.
 *
 * @author Carlos Pereira - A61887
 * @author Jo�o Barreira  - A73831
 * @author Rafael Braga   - A61799
 *
 * @version 12-4-2017 
 */


#include <stdlib.h>


#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif


#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include "xmlParser.h"


// Ficheiro xml por defeito
#define XML_FILE "demos/solarsystem.xml" 

#define FRONT_AND_BACK 1  // Desenhar a parte da frente e de tr�s de
                          // uma primitiva

const float PI = 3.14159265358979323846f;  // Valor da constante pi


float xPos = 0.0;    // Posi��o x
float zPos = 0.0;    // Posi��o z
float angleX = 0.0;  // �ngulo em rela��o ao eixo dos xx
float angleY = 0.0;  // �ngulo em rela��o ao eixo dos yy


// Por defeito o modo de desenho � wired
GLenum mode = GL_FILL;

// Por defeito desenham-se ambos os lados de uma primitiva
GLenum drawMode = FRONT_AND_BACK;


float lx = 0.0;                  // Posi��o para onde se est� a olhar no eixo dos
                                 // xx
float px = 0.0;                  // Posi��o da c�mara no eixo dos xx

float ly = 0.0;                  // Posi��o para onde se est� a olhar no eixo dos
                                 // yy
float py = 0.0;                  // Posi��o da c�mara no eixo dos yy

float lz = -1.0;                 // Posi��o para onde se est� a olhar no eixo dos
                                 // zz
float pz = 15.0;                 // Posi��o da c�mara no eixo dos zz

float cameraAngleX = 0.0;        // �ngulo da c�mara no eixo dos xx
float deltaAngleX = 0.0;         // �ngulo para c�lculos auxilares
int xOrigin = -1;                // Posi��o x do rato

float cameraAngleY = 0.0;        // �ngulo da c�mara no eixo dos yy
float deltaAngleY = 0.0;         // �ngulo para c�lculos auxiliares
int yOrigin = -1;                // Posi��o y do rato

const float vCameraX = 0.003;    // Velocidade de rota��o da c�mara em X
const float vCameraY = 0.5;      // Velocidade de rota��o da c�mara em Y


std::vector<GLOperation*> glOperations;  // Vetor de opera��es em OpenGL


/**
 * Fun��o respons�vel pela representa��o de uma cena em OpenGL. Percorre
 * o vetor de opera��es em openGL (transla��es, rota��es, desenho de 
 * tri�ngulos, ...) e executa cada uma destas.
 */
void drawScene(void)
{	
	for (size_t i = 0; i < glOperations.size(); i++) {
		glOperations.at(i)->execute();
	}
}


void changeSize(int w, int h)
{
	// Prevent a divide by zero, when window is too short
	// (you cant make a window with zero width).
	if (h == 0) {
		h = 1;
	}

	// compute window's aspect ratio 
	float ratio = w * 1.0 / h;

	// Set the projection matrix as current
	glMatrixMode(GL_PROJECTION);

	// Load Identity Matrix
	glLoadIdentity();

	// Set the viewport to be the entire window
	glViewport(0, 0, w, h);

	// Set perspective
	gluPerspective(45.0f, ratio, 1.0f, 1000.0f);

	// return to the model view matrix mode
	glMatrixMode(GL_MODELVIEW);
}


void renderScene(void)
{
	// clear buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// set the camera
	glLoadIdentity();
	gluLookAt(px, py, pz,
		      px + lx, py + ly, pz + lz,
		      0.0f, 1.0f, 0.0f);


	glTranslatef(xPos, 0, zPos);
	glRotatef(angleY, 0, 1, 0);
	glRotatef(angleX, 1, 0, 0);

	if (drawMode != FRONT_AND_BACK) {
		glEnable(GL_CULL_FACE);
		glCullFace(drawMode);
	}
	else {
		glDisable(GL_CULL_FACE);
	}

	glPolygonMode(GL_FRONT_AND_BACK, mode);

	// Representa a cena correspondente a um conjunto de opera��es em OpenGL
	drawScene();

	glutSwapBuffers();
}


/**
 * Fun��o que trata dos eventos do teclado, teclas 'w', 's', 'a' e 'd'.
 */
void keyboardEvent(unsigned char key, int x, int y)
{
	if (key == 'w') {

		// Afasta um modelo
		zPos -= 0.3;
	}
	else if (key == 's') {

		// Aproxima um modelo
		zPos += 0.3;
	}
	else if (key == 'a') {

		// Move um modelo para a direita
		xPos -= 0.3;
	}
	else if (key == 'd') {

		// Move um modelo para a esquerda
		xPos += 0.3;
	}
}


/**
 * Fun��o que trata dos eventos respetivos �s arrow keys.
 */
void rotateEvent(int key, int x, int y)
{
	if (key == GLUT_KEY_LEFT) {

		// Roda o modelo em torno do eixo dos yy no sentido dos 
		// ponteiros do rel�gio
		angleY -= 3.0;
	}
	else if (key == GLUT_KEY_RIGHT) {
		
		// Roda o modelo em torno do eixo dos yy no sentido contr�rio ao dos 
		// ponteiros do rel�gio
		angleY += 3.0;
	}
	else if (key == GLUT_KEY_UP) {

		// Roda o modelo em torno do eixo dos yy no sentido dos 
		// ponteiros do rel�gio
		angleX -= 3.0;
	}
	else if (key == GLUT_KEY_DOWN) {

		// Roda o modelo em torno do eixo dos yy no sentido contr�rio ao dos 
		// ponteiros do rel�gio
		angleX += 3.0;
	}
}


/**
 * Fun��o que trata das op��es selecionadas no menu.
 */
void processMenuEvents(int option)
{
	if (option == GL_FILL) {

		// Preenche a primitiva
		mode = GL_FILL;
	}
	else if (option == GL_LINE) {

		// Desenha a primitiva em modo wired
		mode = GL_LINE;
	}
	else if (option == GL_POINT) {

		// Desenha apenas os v�rtices da primitiva
		mode = GL_POINT;
	}
	else if (option == GL_BACK) {
		drawMode = GL_BACK;
	}
	else if (option == GL_FRONT) {
		drawMode = GL_FRONT;
	}
	else if (option == FRONT_AND_BACK) {
		drawMode = FRONT_AND_BACK;
	}
}


/**
 * Handler para o movimento do rato.
 */
void mouseMove(int x, int y) 
{
	// Apenas se roda a c�mara quando o bot�o do lado esquerdo do rato
	// est� a ser pressionado
	if (xOrigin >= 0) {

		// O valor  
		deltaAngleX = (x - xOrigin) * vCameraX;

		// Atualiza-se a dire��o da c�mara
		lx = sin(cameraAngleX + deltaAngleX);
		lz = -cos(cameraAngleX + deltaAngleX);
	}

	if (yOrigin >= 0) {
		deltaAngleY = (y - yOrigin) * vCameraY;

		// Limita-se o �ngulo da c�mara em Y entre -90 e 90 graus
		if (cameraAngleY + deltaAngleY >= 90.0) {
			ly = tan(89.0 * PI / 180.0);
		}
		else if (cameraAngleY + deltaAngleY <= -90.0) {
			ly = tan(-89.0 * PI / 180.0);
		}
		else {
			ly = tan((cameraAngleY + deltaAngleY) * PI / 180.0);
		}
	}
}


/**
 * Handler para os eventos do rato.
 * Atualiza o angulo x e y da c�mara.
 */
void mouseButton(int button, int state, int x, int y) 
{
	// A anima��o come�a apenas quando o bot�o do lado esquerdo do rato �
	// pressionado
	if (button == GLUT_LEFT_BUTTON) {

		// Depois de o bot�o ser libertado atualizam-se os �ngulos da c�mara
		if (state == GLUT_UP) {
			cameraAngleX += deltaAngleX;
			xOrigin = -1;
			
			cameraAngleY += deltaAngleY;

			yOrigin = -1;
		}
		else {
			xOrigin = x;
			yOrigin = y;
		}
	}
}


/**
 * Fun��o que inicializa todos os componentes da glut
 */
void initGlut(int argc, char **argv)
{
	int menu = 0;

	// Cria a janela e centra-a no ecr�
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(glutGet(GLUT_SCREEN_WIDTH) / 4, glutGet(GLUT_SCREEN_HEIGHT) / 4);
	glutInitWindowSize(glutGet(GLUT_SCREEN_WIDTH) / 2, glutGet(GLUT_SCREEN_HEIGHT) / 2);
	glutCreateWindow("Engine");

	glutDisplayFunc(renderScene);
	glutReshapeFunc(changeSize);


	// Registos de fun��es
	glutIdleFunc(renderScene);
	glutKeyboardFunc(keyboardEvent);
	glutSpecialFunc(rotateEvent);
	menu = glutCreateMenu(processMenuEvents);

	// Categorias do menu
	glutAddMenuEntry("GL_FILL", GL_FILL);
	glutAddMenuEntry("GL_LINE", GL_LINE);
	glutAddMenuEntry("GL_POINT", GL_POINT);
	glutAddMenuEntry("DRAW_FRONT", GL_BACK);
	glutAddMenuEntry("DRAW_BACK", GL_FRONT);
	glutAddMenuEntry("DRAW_FRONT_AND_BACK", FRONT_AND_BACK);

	// O menu � acionado sempre que se pressiona o bot�o direito do rato
	glutAttachMenu(GLUT_RIGHT_BUTTON);

	// Fun��es de tratamento dos eventos do rato
	glutMouseFunc(mouseButton);
	glutMotionFunc(mouseMove);


#ifndef __APPLE___
	glewInit();
#endif

	//  OpenGL settings
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnable(GL_DEPTH_TEST);


	// enter GLUT's main cycle
	glutMainLoop();
}


/**
 * Fun��o principal do programa.
 *
 * @param argc N�mero de argumentos recebidos.
 * @param argv Argumentos recebidos.
 */
int main(int argc, char **argv)
{
	XMLParser* parser;

	std::cout << "Processing models..." << std::endl;

	// Se o n�mero de argumentos for maior que 1 ent�o abre o ficheiro
	// correspondente ao segundo argumento
	if (argc > 1) {
		parser = new XMLParser(argv[1]);
	}
	else {
		// Caso contr�rio carrega-se o ficheiro por defeito.
		parser = new XMLParser(XML_FILE);
	}

	glOperations = parser->getGLOperations();

	// Testa-se se o parsing foi efetuado com sucesso
	if (glOperations.size() > 0) {

		// Apenas se inicia a glut se todos os modelos foram processados com
		// sucesso
		if (parser->getFailedModels() < parser->getNumModels()) {
			// Mostra no ecr� eventuais warnings que possam ter ocorrido
			std::cout << parser->getErrorString();
			
			delete parser;
			initGlut(argc, argv);
		}
		else {
			std::cout << "Could not process the models!" << std::endl;
		}
	}
	else {
		std::cout << parser->getErrorString();
	}

	delete parser;

	std::cout << "Press any key to continue..." << std::endl;

	getchar();
	return 1;
}