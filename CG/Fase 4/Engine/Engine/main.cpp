/**
 * @file main.cpp
 *
 * @brief Definição de todos métodos para o funcionamento do programa Engine.
 *
 * @author Carlos Pereira - A61887
 * @author João Barreira  - A73831
 * @author Rafael Braga   - A61799
 *
 * @version 12-05-2017 
 */


#include <cstdlib>

#include <IL/il.h>

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
#include "frustumCulling.h"


// Ficheiro xml por defeito
#define XML_FILE   "demos/solarsystem.xml" 

// Ficheiro xml da camera por defeito
#define CAMERA_ENTITY "demos/tiefighter.xml"

// Background por defeito
#define BACKGROUND "demos/univ.jpg"


#define FRONT_AND_BACK 1  // Desenhar a parte da frente e de trás de
                          // uma primitiva

const float PI = 3.14159265358979323846f;  // Valor da constante pi


float xPos = 0.0f;    // Posição x
float zPos = 0.0f;    // Posição z
float angleX = 0.0f;  // Ângulo em relação ao eixo dos xx
float angleY = 0.0f;  // Ângulo em relação ao eixo dos yy


float lx = 0.0f;               // Posição para onde se está a olhar no eixo dos
                               // xx
float px = 0.0f;               // Posição da câmara no eixo dos xx

float ly = 0.0f;               // Posição para onde se está a olhar no eixo dos
                               // yy
float py = 0.0f;               // Posição da câmara no eixo dos yy

float lz = 1.0f;               // Posição para onde se está a olhar no eixo dos
                               // zz
float pz = 0.0f;               // Posição da câmara no eixo dos zz

float deltaAngleX = 0.0f;      // Ângulo para cálculos auxilares
int xOrigin = -1;              // Posição x do rato

float deltaAngleY = 0.0f;      // Ângulo para cálculos auxiliares
int yOrigin = -1;              // Posição y do rato

const float vCameraX = 0.5f;   // Velocidade de rotação da câmara em X
const float vCameraY = 0.5f;   // Velocidade de rotação da câmara em Y

float camAngle = 0.0f;         // Ângulo da camera em x e em z
float camAngleY = 0.0f;        // Ângulo da camera em y

std::vector<GLOperation*> glOperations;  // Vetor de operações em OpenGL
std::vector<GLOperation*> cameraEntity;  // Vetor de operações em OpenGl
                                         // Respetivos à entidade da camera

float entityZAngle = 0.0f;               // Ângulo da entidade da camera

float epx = 0.0f;                        // Posição da entidade da camera no
                                         // eixo dos xx
float epz = 0.0f;                        // Posição da entidade da camera no
                                         // eixo dos zz

GLuint texID;                            // Textura do background
std::string background;                  // Nome da textura do background

FrustumCulling* fCulling = new FrustumCulling(); // Campo visível
size_t elapsedTime = 0;                          // Tempo total decorrido
size_t dTime = 0;                             
bool stabilizing = false;                       // Informa se a camera já
                                                 // estabilizou

int timebase = 0;
int frame = 0;

/**
 * Função responsável pela representação de uma cena em OpenGL. Percorre
 * o vetor de operações em openGL (translações, rotações, desenho de 
 * triângulos, ...) e executa cada uma destas.
 */
void drawScene(void)
{	
	for (size_t i = 0; i < glOperations.size(); i++) {
		glOperations.at(i)->execute(fCulling);
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

	fCulling->setPerspective(45.0f, ratio, 1.0f, 1000.0f);

	// return to the model view matrix mode
	glMatrixMode(GL_MODELVIEW);
}


/**
 * Desenha um background estático no fundo da janela.
 */
void drawBackground(void)
{
	float w = 0.0f;  // Largura da janela
	float h = 0.0f;  // Altura da janela

	// Pretende-se que o background não seja sujeito a transformações e que
	// permaneça no fundo da janela
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_LIGHTING);

	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();

	// Calculam-se a altura e a largura da janela
	w = (float)glutGet(GLUT_WINDOW_WIDTH);
	h = (float)glutGet(GLUT_WINDOW_HEIGHT);

	gluOrtho2D(0.0, (GLdouble)w, (GLdouble)h, 0.0);

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();

	glBindTexture(GL_TEXTURE_2D, texID);

	// Desenha-se um plano com as dimensões da janela e aplica-se a textura
	// com o background
	glBegin(GL_QUADS);

	glColor3f(1.0f, 1.0f, 1.0f);

	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);

	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(0.0f, h, 0.0f);

	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(w, h, 0.0f);

	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(w, 0.0f, 0.0f);

	glEnd();


	// Retorna-se às configurações iniciais
	glPopMatrix(); 
	glMatrixMode(GL_PROJECTION);
	glPopMatrix(); 
	glMatrixMode(GL_MODELVIEW);

	glBindTexture(GL_TEXTURE_2D, 0);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
}


/**
 * Atualiza uma posição dos vetores pos e look da câmara
 */
void updateCam(float* p, float* l, float k, float d)
{
	*p = *p + k * d;
	*l = *l + k * d;
}


/**
 * Estabiliza a camera.
 */
void stabilize(void)
{
	float dx = lx - px;
	float dy = ly - py;
	float dz = lz - pz;

	float rx = -dz;
	float rz = dx;

	float k = vCameraX * 0.2;

	if (epz < 0.0f) {
		epz += 0.05f;

		updateCam(&px, &lx, k, dx);
		updateCam(&py, &ly, k, dy);
		updateCam(&pz, &lz, k, dz);

		if (epz >= 0.0f) {
			epz = 0.0f;
			stabilizing = false;
		}
	}
	else if (epz > 0.0f) {
		epz -= 0.05f;

		updateCam(&px, &lx, -k, dx);
		updateCam(&py, &ly, -k, dy);
		updateCam(&pz, &lz, -k, dz);

		if (epz <= 0.0f) {
			epz = 0.0f;
			stabilizing = false;
		}
	}


	if (epx > 0.0f) {
		epx -= 0.05f;
		entityZAngle += 2.25f;

		updateCam(&px, &lx, k, rx);
		updateCam(&pz, &lz, k, rz);

		if (epx <= 0.0f) {
			epx = 0.0f;
			entityZAngle = 0.0f;
			stabilizing = false;
		}
	}
	else if (epx < 0.0f) {
		epx += 0.05f;
		entityZAngle -= 2.25f;

		updateCam(&px, &lx, -k, rx);
		updateCam(&pz, &lz, -k, rz);

		if (epx >= 0.0f) {
			epx = 0.0f;
			entityZAngle = 0.0f;
			stabilizing = false;
		}
	}
}


/**
 * Devolve o tempo decorrido desde a última medição.
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


/**
 * Desenha a cena.
 */
void renderScene(void)
{
	TripleFloat pos(px, py, pz);
	TripleFloat look(lx, ly, lz);
	TripleFloat up(0.0f, 1.0f, 0.0f);
	size_t i = 0;
	float fps = 0.0f;
	int time = 0;
	char s[64];

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	drawBackground();

	// Efetua uma medição de tempo
	dTime += getDeltaTime();

	// Se a entidade da câmera não foi movida então estabiliza-se a camera
	if (dTime > 300 && stabilizing == false) {
		stabilizing = true;
	}

	if (stabilizing == true) {
		stabilize();
	}

	// set the camera
	glLoadIdentity();

	glPushMatrix();

	// Desenha a entidade da camera
	glTranslatef(epx, 0.0f, epz);
	glRotatef(entityZAngle, 0.0f, 0.0f, 1.0f);

	for (; i < cameraEntity.size(); i++) {
		cameraEntity.at(i)->execute();
	}

	glPopMatrix();

	gluLookAt(px, py, pz, lx, ly, lz, 0.0f, 1.0f, 0.0f);

	fCulling->setCam(pos, look, up);

	glPushMatrix();

	// Representa a cena correspondente a um conjunto de operações em OpenGL
	drawScene();

	glPopMatrix();


	frame++;
	time = glutGet(GLUT_ELAPSED_TIME);
	
	if (time - timebase > 1000) {
		fps = frame*1000.0 / (time - timebase);
		timebase = time;
		frame = 0;
		sprintf_s(s, "FPS: %f6.2", fps);
		glutSetWindowTitle(s);
	}

	glutSwapBuffers();
}


/**
 * Função que trata dos eventos do teclado, teclas 'w', 's', 'a' e 'd'.
 * Move a identidade da camera (a partir de uma certa "força", a camera acompanha
 * a identidade).
 */
void keyboardEvent(unsigned char key, int x, int y)
{
	float dx = (lx - px);
	float dy = (ly - py);
	float dz = (lz - pz);

	float k = vCameraX;

	float rx = -dz;
	float rz = dx;

	if (key == 'w' || key == 'W') {
		if (epz > -1.0f) {
			epz -= 0.1f;
		}
		else {
			updateCam(&px, &lx, k, dx);
			updateCam(&pz, &lz, k, dz);
		}

		updateCam(&py, &ly, k, dy);
	}
	else if (key == 'a' || key == 'A') {
		if (epx > -1.0f) {
			epx -= 0.1f;
		}
		else {
			updateCam(&px, &lx, -k, rx);
			updateCam(&pz, &lz, -k, rz);
		}

		if (entityZAngle < 45.0f) {
			entityZAngle += 4.5f;
		}
	}
	else if (key == 's' || key == 'S') {
		if (epz < 1.0f) {
			epz += 0.1f;
		}
		else {
			updateCam(&px, &lx, -k, dx);
			updateCam(&pz, &lz, -k, dz);
		}

		updateCam(&py, &ly, -k, dy);
	}
	else if (key == 'd' || key == 'D') {
		if (epx < 1.0f) {
			epx += 0.1f;
		}
		else {
			updateCam(&px, &lx, k, rx);
			updateCam(&pz, &lz, k, rz);
		}

		if (entityZAngle > -45.0f) {
			entityZAngle -= 4.5f;
		}
	}

	getDeltaTime();
	dTime = 0;
}


/**
 * Função que trata dos eventos respetivos às arrow keys.
 * Roda a camera.
 */
void rotateEvent(int key, int x, int y)
{
	if (key == GLUT_KEY_LEFT) {
		camAngle += 5.0f;
	}
	else if (key == GLUT_KEY_RIGHT) {
		camAngle -= 5.0f;
	}
	else if (key == GLUT_KEY_UP) {
		camAngleY -= 5.0f;

		if (camAngleY < -90.0f) {
			camAngleY = -90.0f;
		}
	}
	else if (key == GLUT_KEY_DOWN) {
		camAngleY += 5.0f;

		if (camAngleY > 90.0f) {
			camAngleY = 90.0f;
		}
	}

	lx = px + sin(camAngle * PI / 180.0f);
	ly = py + sin(camAngleY * PI / 180.0f);
	lz = pz + cos(camAngle * PI / 180.0f);
}


/**
 * Handler para o movimento do rato.
 */
void mouseMove(int x, int y) 
{
	// Apenas se roda a câmara quando o botão do lado esquerdo do rato
	// está a ser pressionado
	if (xOrigin >= 0) {

		// O valor  
		deltaAngleX = (x - xOrigin) * vCameraX;

		// Atualiza-se a direção da câmara
		lx = px + sin((camAngle + deltaAngleX) * PI / 180.0f);
		lz = pz + cos((camAngle + deltaAngleX) * PI / 180.0f);
	}

	if (yOrigin >= 0) {
		deltaAngleY = (y - yOrigin) * vCameraY;

		// Limita-se o ângulo da câmara em Y entre -90 e 90 graus
		if (camAngleY + deltaAngleY >= 90.0f) {
			ly = py + sin(90.0f * PI / 180.0f);
		}
		else if (camAngleY + deltaAngleY <= -90.0f) {
			ly = py + sin(-90.0f * PI / 180.0f);
		}
		else {
			ly = py + sin((camAngleY + deltaAngleY) * PI / 180.0f);
		}
	}
}


/**
 * Handler para os eventos do rato.
 * Atualiza o angulo x e y da câmara.
 */
void mouseButton(int button, int state, int x, int y) 
{
	// A animação começa apenas quando o botão do lado esquerdo do rato é
	// pressionado
	if (button == GLUT_LEFT_BUTTON) {

		// Depois de o botão ser libertado atualizam-se os ângulos da câmara
		if (state == GLUT_UP) {
			camAngle += deltaAngleX;
			xOrigin = -1;
			
			camAngleY += deltaAngleY;

			yOrigin = -1;
		}
		else {
			xOrigin = x;
			yOrigin = y;
		}
	}
}


/**
 * Carrega a textura do background.
 */
void loadBackground(void)
{
	unsigned int t = 0;
	unsigned int tw = 0;
	unsigned int th = 0;
	unsigned char *texData;

	ilEnable(IL_ORIGIN_SET);
	ilOriginFunc(IL_ORIGIN_LOWER_LEFT);

	ilGenImages(1, &t);
	ilBindImage(t);
	ilLoadImage((ILstring)background.c_str());

	tw = ilGetInteger(IL_IMAGE_WIDTH);
	th = ilGetInteger(IL_IMAGE_HEIGHT);

	ilConvertImage(IL_RGBA, IL_UNSIGNED_BYTE);
	texData = ilGetData();

	glGenTextures(1, &texID);

	glBindTexture(GL_TEXTURE_2D, texID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, tw, th, 0, GL_RGBA, GL_UNSIGNED_BYTE, texData);
	glGenerateMipmap(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, 0);
}


/**
 * Função que inicializa todos os componentes da glut
 */
void initGlut(int argc, char **argv)
{
	int menu = 0;

	// Cria a janela e centra-a no ecrã
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(glutGet(GLUT_SCREEN_WIDTH) / 4, glutGet(GLUT_SCREEN_HEIGHT) / 4);
	glutInitWindowSize(glutGet(GLUT_SCREEN_WIDTH) / 2, glutGet(GLUT_SCREEN_HEIGHT) / 2);
	glutCreateWindow("Engine");

	glutDisplayFunc(renderScene);
	glutReshapeFunc(changeSize);

	// Registos de funções
	glutIdleFunc(renderScene);
	glutKeyboardFunc(keyboardEvent);
	glutSpecialFunc(rotateEvent);


	// Funções de tratamento dos eventos do rato
	glutMouseFunc(mouseButton);
	glutMotionFunc(mouseMove);


#ifndef __APPLE___
	glewInit();
#endif

	ilInit();

	//  OpenGL settings
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_DEPTH_TEST);
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glEnable(GL_SMOOTH);
	glEnable(GL_RESCALE_NORMAL);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	
	loadBackground();

	// enter GLUT's main cycle
	glutMainLoop();
}


/**
 * Função principal do programa.
 *
 * @param argc Número de argumentos recebidos.
 * @param argv Argumentos recebidos.
 */
int main(int argc, char **argv)
{
	XMLParser* parser;
	XMLParser* cameraParser;

	std::cout << "Processing models..." << std::endl;

	// Se o número de argumentos for maior que 1 então abre o ficheiro
	// correspondente ao segundo argumento
	if (argc > 1) {
		parser = new XMLParser(argv[1]);
	}
	else {
		// Caso contrário carrega-se o ficheiro por defeito.
		parser = new XMLParser(XML_FILE);
	}

	// Se possuir mais que dois argumentos então o segundo argumento
	// corresponde à entidade da camera

	if (argc > 2) {
		cameraParser = new XMLParser(argv[2]);
	}
	else {
		cameraParser = new XMLParser(CAMERA_ENTITY);
	}

	// Se possuir mais que três argumentos então o terceiro argumento
	// corresponde à textura do background
	if (argc > 3) {
		background = argv[2];
	}
	else {

		// Caso contrário é carregada a textura por defeito
		background = BACKGROUND;
	}

	glOperations = parser->getGLOperations();
	cameraEntity = cameraParser->getGLOperations();

	// Testa-se se o parsing foi efetuado com sucesso
	if (glOperations.size() > 0) {

		// Apenas se inicia a glut se todos os modelos foram processados com
		// sucesso
		if (parser->getFailedModels() < parser->getNumModels() &&
			cameraParser->getFailedModels() < cameraParser->getNumModels()) {
			// Mostra no ecrã eventuais warnings que possam ter ocorrido
			std::cout << parser->getErrorString();
			std::cout << cameraParser->getErrorString();

			delete cameraParser;
			delete parser;
			initGlut(argc, argv);
		}
		else {
			std::cout << "Could not process the models!" << std::endl;
		}
	}
	else {
		std::cout << parser->getErrorString();
		std::cout << cameraParser->getErrorString();
	}

	delete parser;
	delete cameraParser;

	std::cout << "Press any key to continue..." << std::endl;

	getchar();
	return 1;
}