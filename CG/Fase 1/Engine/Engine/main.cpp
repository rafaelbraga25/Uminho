/**
* @file main.cpp
*
* @brief Defini��o de todos m�todos para o funcionamento do programa Engine.
*
* @author Carlos Pereira - A61887
* @author Jo�o Barreira  - A73831
* @author Rafael Braga   - A61799
*/


#include <stdlib.h>

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif


#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include "tinyxml.h"
#include "vertex.h"


#define FILE "demos/plane.xml" // Ficheiro xml por defeito

// Tags do ficheiro xml
#define SCENE "scene"
#define MODEL "model"


// Defini��o dos valores para o menu
#define RED 0
#define ORANGE 1 
#define YELLOW 2 
#define GREEN 3
#define CYAN 4
#define BLUE 5
#define PURPLE 6 
#define PINK 7
#define WHITE 8


float xPos = 0;    // Posi��o x
float zPos = 0;    // Posi��o z
float angleX = 0;  // �ngulo em rela��o ao eixo dos xx
float angleY = 0;  // �ngulo em rela��o ao eixo dos yy


// A cor por defeito � branca (red = 1, green = 1, blue = 1)
float red = 1;   
float green = 1;  
float blue = 1;

// Por defeito o modo de desenho � wired
GLenum mode = GL_LINE;

std::vector<Vertex> vertices; // Vetor de v�rtices
TiXmlDocument doc;            // Documento de xml

size_t numModels = 0;         // N�mero total de modelos presentes no 
                              // ficheiro xml
size_t failedModels = 0;      // N�mero total de modelos presentes no ficheiro
                              // xml que n�o conseguiram ser processados por
                              // algum motivo


float lx = 0;                 // Posi��o para onde se est� a olhar no eixo dos
                              // xx
float px = 0;                 // Posi��o da c�mara no eixo dos xx

float ly = 0;                 // Posi��o para onde se est� a olhar no eixo dos
                              // yy
float py = 0;                 // Posi��o da c�mara no eixo dos yy

float lz = -1;                // Posi��o para onde se est� a olhar no eixo dos
                              // zz
float pz = 15;                // Posi��o da c�mara no eixo dos zz

float cameraAngleX = 0;       // �ngulo da c�mara no eixo dos xx
float deltaAngleX = 0;        // �ngulo para c�lculos auxilares
int xOrigin = -1;             // Posi��o x do rato

float cameraAngleY = 0;       // �ngulo da c�mara no eixo dos yy
float deltaAngleY = 0;        // �ngulo para c�lculos auxiliares
int yOrigin = -1;             // Posi��o y do rato

const float vCamera = 0.005f; // Velocidade de rota��o da c�mara


/**
 * Fun��o que desenha todos os v�rtices de uma primitiva � custa de 
 * tri�ngulos.
 */
void drawVertices(void)
{	
	glBegin(GL_TRIANGLES);
	glColor3f(red, green, blue);

	for (size_t i = 0; i < vertices.size(); i++) {
		glVertex3f(vertices.at(i).getX(),
				   vertices.at(i).getY(),
				   vertices.at(i).getZ());
	}

	glEnd();
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

	glPolygonMode(GL_FRONT_AND_BACK, mode);

	drawVertices();

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

	glutPostRedisplay();
}


/**
 * Fun��o que trata dos eventos respetivos �s arrow keys.
 */
void rotateEvent(int key, int x, int y)
{
	if (key == GLUT_KEY_LEFT) {

		// Roda o modelo em torno do eixo dos yy no sentido dos 
		// ponteiros do rel�gio
		angleY -= 3;
	}
	else if (key == GLUT_KEY_RIGHT) {
		
		// Roda o modelo em torno do eixo dos yy no sentido contr�rio ao dos 
		// ponteiros do rel�gio
		angleY += 3;
	}
	else if (key == GLUT_KEY_UP) {

		// Roda o modelo em torno do eixo dos yy no sentido dos 
		// ponteiros do rel�gio
		angleX -= 3;
	}
	else if (key == GLUT_KEY_DOWN) {

		// Roda o modelo em torno do eixo dos yy no sentido contr�rio ao dos 
		// ponteiros do rel�gio
		angleX += 3;
	}

	glutPostRedisplay();
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
	else if (option == RED) {
		red = 1;
		blue = 0;
		green = 0;
	}
	else if (option == ORANGE) {
		red = 1;
		blue = 0;
		green = 0.5;
	}
	else if (option == YELLOW) {
		red = 1;
		blue = 0;
		green = 1;
	}
	else if (option == GREEN) {
		red = 0;
		blue = 0;
		green = 1;
	}
	else if (option == CYAN) {
		red = 0;
		blue = 1;
		green = 1;
	}
	else if (option == BLUE) {
		red = 0;
		blue = 1;
		green = 0;
	}
	else if (option == PURPLE) {
		red = 0.5;
		blue = 1;
		green = 0;
	}
	else if (option == PINK) {
		red = 1;
		blue = 1;
		green = 0;
	}
	else if (option == WHITE) {
		red = 1;
		blue = 1;
		green = 1;
	}

	glutPostRedisplay();
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
		deltaAngleX = (x - xOrigin) * vCamera;

		// Atualiza-se a dire��o da c�mara
		lx = sin(cameraAngleX + deltaAngleX);
		lz = -cos(cameraAngleX + deltaAngleX);
	}

	if (yOrigin >= 0) {
		deltaAngleY = (y - yOrigin) * vCamera;

		ly = sin(cameraAngleY + deltaAngleY);
	}

	glutPostRedisplay();
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
	glutKeyboardFunc(keyboardEvent);
	glutSpecialFunc(rotateEvent);
	menu = glutCreateMenu(processMenuEvents);

	// Categorias do menu
	glutAddMenuEntry("GL_FILL", GL_FILL);
	glutAddMenuEntry("GL_LINE", GL_LINE);
	glutAddMenuEntry("GL_POINT", GL_POINT);
	glutAddMenuEntry("Red", RED);
	glutAddMenuEntry("Orange", ORANGE);
	glutAddMenuEntry("Yellow", YELLOW);
	glutAddMenuEntry("Green", GREEN);
	glutAddMenuEntry("Cyan", CYAN);
	glutAddMenuEntry("Blue", BLUE);
	glutAddMenuEntry("Purple", PURPLE);
	glutAddMenuEntry("Pink", PINK);
	glutAddMenuEntry("White", WHITE);

	// O menu � acionado sempre que se pressiona o bot�o direito do rato
	glutAttachMenu(GLUT_RIGHT_BUTTON);


	// Fun��es de tratamento dos eventos do rato
	glutMouseFunc(mouseButton);
	glutMotionFunc(mouseMove);


	//  OpenGL settings
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

	// enter GLUT's main cycle
	glutMainLoop();
}


/**
 * Abre o ficheiro que cont�m um conjunto de v�rtices de uma primitiva.
 * Este ficheiro � aberto apenas uma vez.
 *
 * @param fileName Nome do ficheiro.
 */
void readVertices(const char* fileName)
{
	std::ifstream file;    // Estrutura para abertura de um ficheiro em modo
	                       // de leitura
	std::string line;      // String auxiliar que ir� corresponder a uma linha
	                       // do ficheiro
	std::stringstream ss;  // String auxiliar para converter texto em valores
	                       // num�ricos

	float x = 0;  // Coordenada x de um v�rtice
	float y = 0;  // Coordenada y de um v�rtice
	float z = 0;  // Coordenada z de um v�rtice

	file.open(fileName);

	// Testa se o ficheiro foi bem aberto e come�a a sua leitura
	if (file.is_open()) {

		// L� linha a linha
		while (getline(file, line)) {
			std::stringstream ss(line);

			// Converte uma linha para as coordenadas x, y e z
			ss >> x >> y >> z;

			// Adiciona as coordenadas ao vetor de v�rtices
			vertices.push_back(Vertex(x, y, z));

			// Limpa a string auxiliar de convers�o
			ss.str("");
		}

		file.close();
	}
	else {
		std::cout << "Could not read file " << fileName << "!" << std::endl;

		// Se n�o se conseguiu abrir bem o ficheiro ent�o o m�dulo atual conta
		// como um m�dulo que teve um problema
		failedModels++;
	}
}


/**
 * Efetua o parsing do documento xml.
 */
void parseDocument(void)
{
	// Estrutura auxiliar para realizar o parsing do documento xml
	TiXmlElement *scene = doc.FirstChildElement();

	std::cout << "Preparing models..." << std::endl;

	// Testa se existe uma tag chamada scene
	if (scene == NULL || strcmp(scene->Value(), SCENE) != 0) {
		std::cout << "Failed to load file. No scene element!" << std::endl;
		doc.Clear();
		failedModels++;
	}
	else {

		// Processa cada um dos modelos
		for (TiXmlElement* elem = scene->FirstChildElement(); elem != NULL; elem = elem->NextSiblingElement()) {
			std::string elemName = elem->Value();

			// Testa se existe uma tag chamada model
			if (elemName.compare(MODEL) != 0) {
				std::cout << "Invalid document!" << std::endl;
				break;
			}

			numModels++;

			// Processa cada um dos atributos associados � tag model
			for (TiXmlAttribute* a = elem->FirstAttribute(); a; a = a->Next()) {
				readVertices(a->Value());
			}
		}
	}
}


/**
 * Abre um ficheiro xml para realizar o seu parsing.
 *
 * @param fileName Nome do ficheiro.
 * @return Devolve verdadeiro caso se consiga abrir o ficheiro com sucesso ou
 *         falso caso contr�rio
 */
bool openXMLFile(const char* fileName)
{
	bool ret = true;

	if (!doc.LoadFile(fileName)) {
		std::cout << doc.ErrorDesc() << std::endl;
		ret = false;
	}

	return ret;
}


/**
 * Fun��o principal do programa.
 *
 * @param argc N�mero de argumentos recebidos.
 * @param argv Argumentos recebidos.
 */
int main(int argc, char **argv)
{
	bool isDocOK = true;

	// Se o n�mero de argumentos for maior que 1 ent�o abre o ficheiro
	// correspondente ao segundo argumento
	if (argc > 1) {
		isDocOK = openXMLFile(argv[1]);
	}
	else {
		// Caso contr�rio carrega-se o ficheiro por defeito.
		isDocOK = openXMLFile(FILE);
	}

	// Apenas se faz o parsing do documento se este foi aberto com sucesso
	if (isDocOK) {
		parseDocument();

		// Apenas se inicia a glut se todos os modelos foram processados com
		// sucesso
		if (failedModels < numModels) {

			// Os ficheiros s�o apenas lidos uma vez
			initGlut(argc, argv);
		}
		else {
			std::cout << "Could not process the models!" << std::endl;
		}
	}
	else {
		std::cout << "Could not open the xml file!" << std::endl;
	}


	std::cout << "Press any key to continue..." << std::endl;

	getchar();
	return 1;
}