/**
 * @file xmlParser.cpp
 *
 * Definição de todos os métodos para se efetuar o parsing de um ficheiro xml
 * que contenha múltiplas instruções a ser executadas em OpenGL.
 *
 * @author Carlos Pereira - A61887
 * @author João Barreira  - A73831
 * @author Rafael Braga   - A61799
 *
 * @version 12-04-2017
 */


#include <stack>
#include <algorithm>
#include <map>
#include <stdexcept>
#include <sstream>
#include <fstream>
#include <ctime>
#include "xmlParser.h"
#include "tinyxml.h"
#include "popMatrix.h"
#include "pushMatrix.h"
#include "rotation.h"
#include "scale.h"
#include "translation.h"
#include "trianglesDrawing.h"


/* Definição de constantes e atributos que caracterizam operações em OpenGL */
#define SCENE  "scene"
#define GROUP  "group"
#define MODELS "models"

/* Tag de model e atributos */
#define MODEL  "model"
#define FILE   "file"
#define DIFFR  "diffr"
#define DIFFG  "diffg"
#define DIFFB  "diffb"
#define RAND   "rand"
#define XZMINR "xzminr"
#define XZMAXR "xzmaxr"
#define YMINR  "yminr"
#define YMAXR  "ymaxr"


/* Tag de rotate e atributos */
#define ROTATE "rotate"
#define ANGLE  "angle"
#define AXISX  "axisx"
#define AXISY  "axisy"
#define AXISZ  "axisz"

/* Tags de scale e translate e respetivos atributos */
#define SCALE     "scale"
#define TRANSLATE "translate"
#define POINT     "point"
#define X         "x"
#define Y         "y"
#define Z         "z"
#define TIME      "time"


const float PI = 3.14159265358979323846f;  // Valor da constante pi


class XMLParser::XMLParserImpl {
	TiXmlDocument doc;    // Documento tinyXML 
	bool invalidDoc;      // Variável para detetar se ocorreu algum erro de 
	                      // parsing
	size_t numModels;     // Número total de modelos lidos
	size_t failedModels;  // Número total de modelos que não se conseguiram 
	                      // processar

	std::stack<bool> rotatesInContainer;    // Stack para guardar a informação
	                                        // acerca de um container possuir
	                                        // ou não uma rotação
	std::stack<bool> scalesInContainer;     // Stack para guardar a informação
	                                        // acerca de um container possuir
	                                        // ou não uma escala
	std::stack<bool> translatesInContainer;	// Stack para guardar a informação
	                                        // acerca de um container possuir
	                                        // ou não uma translação
	std::stack<bool> somethingInContainer;  // Stack para guardar a informação
	                                        // acerca de um container possuir
	                                        // ou não uma qualquer tag
	std::stack<bool> modelsInContainer;     // Stack para guardar a informação
	                                        // acerca de um container possuir
	                                        // ou não uma tag models

	std::vector<GLOperation*> glOperations;   // Vetor de operações em OpenGL
	std::string errorString;                  // Representação textual de
	                                          // eventuais erros, ou warnings,
	                                          // que possam ocorrer
	std::string fileName;                     // Nome do ficheiro xml

	// Map que associa o nome de um ficheiro a um conjunto de vértices
	std::map<std::string, std::vector<GLfloat>> mapFileVertices;

	// Map que associa o nome de um ficheiro a um conjunto de índices
	std::map<std::string, std::vector<size_t>> mapFileIndexes;


	/**
	 * Limpa o conteúdo do vetor de operações em OpenGL.
	 */
	void clearGLOperations(void)
	{
		for (size_t i = 0; i < glOperations.size(); i++) {
			delete glOperations.at(i);
		}

		glOperations.clear();
	}


	/**
	 * Converte todos os carateres de uma string para minúsculas.
	 *
	 * @param str String a ser convertida.
	 * @return Devolve uma string que contenha apenas minúsculas.
	 */
	std::string toLower(const char* str)
	{
		std::string aux(str);

		std::transform(aux.begin(), aux.end(), aux.begin(), ::tolower);

		return aux;
	}


	/**
	 * Inicializa as stacks de um container. Sempre que se inicia o parsing
	 * de um container todas as stacks recebem o valor falso.
	 */
	void pushContainerStacks(void)
	{
		somethingInContainer.push(false);
		rotatesInContainer.push(false);
		scalesInContainer.push(false);
		translatesInContainer.push(false);
		modelsInContainer.push(false);
	}


	/**
	 * Gera um valor real aleatório entre 0 e 1;
	 */
	float getRandom(void)
	{
		float r = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);

		return r;
	}


	/**
	 * Gera uma posição (x, y, z) aleatória dentro da área da gama de valores
	 * recebidos.
	 * 
	 * @param xzMinR Raio xz mínimo da área a serem geradas as coordenadas x 
	 *               e z.
	 * @param xzMaxR Raio xz máximo da área a serem geradas as coordenadas x e
	 *               e z.
	 * @param yMinR  Raio y mínimo da área a ser gerada uma coordenada y.
	 * @param yMax   Raio y máximo da área a ser gerada uma coordenada y.
	 */
	void generateRandomPos(float xzMinR, float xzMaxR, 
		                   float yMinR, float yMaxR)
	{
		float x = 0;
		float y = 0;
		float z = 0;
		
		float xzArea = xzMaxR - xzMinR;
		float yArea = yMaxR - yMinR;

		float xzAngle = getRandom() * 360.0;
		float xzR = (getRandom() * xzArea) + xzMinR;

		float yAngle = getRandom() * 360.0 - 180.0;
		float yR = (getRandom() * yArea) + yMinR;

		x = xzR * sin(xzAngle * PI / 180.0);
		y = yR * cos(yAngle * PI / 180.0);
		z = xzR * cos(xzAngle * PI / 180.0);

		glOperations.push_back(new Translation(x, y, z));
	}


	/**
	 * Testa se os valores recebidos para a geração de posições (x, y, z) 
	 * aleatórias são válidos.
	 *
	 * @param existsXZ Indica se foi fornecida a área máxima em x e z.
	 * @param existsY  Indica se foi fornecida a área mínima em y.
	 * @param minXZ    Área mínima em x e z.
	 * @param maxXZ    Áream máxima em x e z.
	 * @param minY     Área mínima em y.
	 * @param maxY     Áream máxima em y.
	 */
	bool randPosError(bool existsXZ, bool existsY, float minXZ, float maxXZ,
		              float minY, float maxY)
	{
		if (existsXZ == false && existsY == false) {
			errorString.append("Error: No area values!\n");
			invalidDoc = true;
		}
		else if (minXZ != 0 && existsXZ == false) {
			errorString.append("Error: MaxXZ area is required!\n");
			invalidDoc = true;
		}
		else if (minY != 0 && existsY == false) {
			errorString.append("Error: MaxY area is required!\n");
			invalidDoc = true;
		}
		else if (minXZ >= maxXZ && existsXZ == true) {
			errorString.append("Error: MaxXZ area must be greater than MinXZ area!\n");
			invalidDoc = true;
		}
		else if (minY >= maxY && existsY == true) {
			errorString.append("Error: MaxY area must be greater than MinY area!\n");
			invalidDoc = true;
		}
		else if (minXZ < 0 || maxXZ < 0 || minY < 0 || maxY < 0) {
			errorString.append("Error: Area values must be positive!\n");
			invalidDoc = true;
		}

		return invalidDoc;
	}


	/**
	 * Remove-se a informação relativa a um container das stacks auxiliares.
	 */
	void popContainerStacks(void)
	{
		somethingInContainer.pop();
		rotatesInContainer.pop();
		scalesInContainer.pop();
		translatesInContainer.pop();
		modelsInContainer.pop();
	}


	/**
	 * Abre o ficheiro que contém um conjunto de vértices de uma primitiva.
	 * Este ficheiro é aberto apenas uma vez.
	 *
	 * @param fileName Nome do ficheiro.
	 * @param vertices Conjunto de vértices de uma primitiva.
	 * @param indexes  Conjunto de índices associados ao vetor de vértices.
	 * @return O resultado é devolvido em vertices e em indexes.
	 */
	void readModel(const char* file, std::vector<GLfloat>& vertices,
		           std::vector<size_t>& indexes)
	{
		std::fstream fp;       // Estrutura para abertura de um ficheiro em
		                       // modo de leitura
		std::string line;      // String auxiliar que irá corresponder a uma 
		                       // linha do ficheiro
		std::stringstream ss;  // String auxiliar para converter texto em 
		                       // valores numéricos

		float x = 0.0;  // Coordenada x de um vértice
		float y = 0.0;  // Coordenada y de um vértice
		float z = 0.0;  // Coordenada z de um vértice

		size_t index = 0;

		bool indexesMode = false;

		// Extrai dos mapas, os vértices e os índices associados
		// à string file, caso estes existam
		try {
			vertices = mapFileVertices.at(file);
			indexes = mapFileIndexes.at(file);
		}
		catch (std::out_of_range) {
			// Caso os maps não possua esse ficheiro deve-se proceder à 
			// abertura do ficheiro e respetiva leitura dos vértices e dos
			// índices

			fp.open(file);

			// Testa se o ficheiro foi bem aberto e inicia a sua leitura
			if (fp.is_open()) {

				// Lê linha a linha
				while (getline(fp, line)) {
					std::stringstream ss(line);

					// Entra em modo de leitura de índices caso encontre uma
					// linha vazia
					if (line.compare("") == 0) {
						indexesMode = true;
						continue;
					}

					if (indexesMode == true) {
						ss >> index;

						indexes.push_back(index);
					}
					else {

						// Converte uma linha para as coordenadas x, y e z
						ss >> x >> y >> z;

						// Adiciona as coordenadas ao vetor de vértices
						vertices.push_back(x); 
						vertices.push_back(y); 
						vertices.push_back(z);
					}
				}

				fp.close();

				std::string aux(file);   // String auxliar para a conversão

				// O ficheiro lido e conjunto de vértices e índices são 
				// adicionados aos mapas. Assim, não será necessário 
				// proceder-se à leitura deste ficheiro novamente
				mapFileVertices.insert(std::pair<std::string, 
					                   std::vector<GLfloat>>(file, vertices));

				mapFileIndexes.insert(std::pair < std::string,
					                  std::vector < size_t >> (file, indexes));
			}
			else {
				errorString.append("Warning: Could not read file ");
				errorString.append(file);
				errorString.append("!\n");

				// Se não se conseguiu abrir bem o ficheiro então o modelo atual 
				// conta como um modelo que não pode ser processado
				failedModels++;
			}
		}
	}


	/**
	 * Efetua o parsing de um modelo.
	 *
	 * @param model Tag model.
	 */
	void parseModel(TiXmlElement* model)
	{
		std::vector<GLfloat> vertices;  // Vetor de vértices de um modelo
		std::vector<size_t> indexes;    // Conjunto de índices associados ao
		                                // vetor de vértices
		size_t numFiles = 0;            // Número de ficheiros associados à tag
		                                // model

		float diffR = 0.0;  // Valor da difusão em vermelho 
		float diffG = 0.0;  // Valor da difusão em verde 
		float diffB = 0.0;  // Valor da difusão em azul 
		
		size_t rand = 0;          // Quantidade de modelos a serem gerados 
		                          // em posições aleatórias
		bool existsXZMax = false; // Determina se foi fornecida a área máxima
		                          // para a geração das coordenas x e z 
		                          // aleatórias
		bool existsYMax = false;  // Determina se foi fornecida a área máxima
		                          // para a geração da coordenada y aleatória
		float xzMinR = 0.0;       // Área mínima para a geração das coodenadas
		                          // aleatórias x e z
		float xzMaxR = 0.0;       // Área máxima para a geração das coodenadas
		                          // aleatórias x e z
		float yMinR = 0.0;        // Área mínima para a geração da coodenada
		                          // aleatória y
		float yMaxR = 0.0;        // Área máxima para a geração da coodenada
		                          // aleatória y

		size_t numColors = 0;  // Número de atributos relativamente a cores

		numModels++;

		for (TiXmlAttribute* a = model->FirstAttribute(); 
		     a != NULL && invalidDoc == false; a = a->Next()) {
			
			std::string attName(toLower(a->Name()));

			if (attName.compare(FILE) == 0) {
				if (numFiles > 0) {

					// Um modelo apenas pode conter um ficheiro
					invalidDoc = true;
				}
				else {
					readModel(a->Value(), vertices, indexes);
					numFiles++;
				}
			}
			else if (attName.compare(DIFFR) == 0) {
				std::stringstream ss(a->Value());
				ss >> diffR;
				numColors++;
			}
			else if (attName.compare(DIFFG) == 0) {
				std::stringstream ss(a->Value());
				ss >> diffG;
				numColors++;
			}
			else if (attName.compare(DIFFB) == 0) {
				std::stringstream ss(a->Value());
				ss >> diffB;
				numColors++;
			}
			else if(attName.compare(RAND) == 0) {
				std::stringstream ss(a->Value());
				ss >> rand;
			}
			else if (attName.compare(XZMINR) == 0) {
				std::stringstream ss(a->Value());
				ss >> xzMinR;
			}
			else if (attName.compare(XZMAXR) == 0) {
				std::stringstream ss(a->Value());
				ss >> xzMaxR;
				existsXZMax = true;
			}
			else if (attName.compare(YMINR) == 0) {
				std::stringstream ss(a->Value());
				ss >> yMinR;
				existsYMax = true;
			}
			else if (attName.compare(YMAXR) == 0) {
				std::stringstream ss(a->Value());
				ss >> yMaxR;
			}
			else {
				errorString.append("Error: Invalid model attribute!\n");
				invalidDoc = true;
			}
		}

		// A cor de um modelo é branca por defeito
		if (numColors == 0) {
			diffR = diffG = diffB = 1.0;
		}

		if (rand > 0 && invalidDoc == false) {
			if (randPosError(existsXZMax, existsYMax, xzMinR, 
				             xzMaxR, yMinR, yMaxR) == false) {

				for (size_t i = 0; i < rand; i++) {
					glOperations.push_back(new PushMatrix());
					generateRandomPos(xzMinR, xzMaxR, yMinR, yMaxR);
					
					glOperations.push_back(new TrianglesDrawing(vertices, 
						                                        indexes,
						                                        diffR, 
						                                        diffG, 
						                                        diffB));
					
					glOperations.push_back(new PopMatrix());
				}
			}
		}
		else {
			glOperations.push_back(new TrianglesDrawing(vertices, indexes,
				                                        diffR, diffG, diffB));
		}
	}


	/**
	 * Efetua o parsing dos atributos associados à tag models.
	 *
	 * @param models Tag models.
	 */
	void parseModels(TiXmlElement* models)
	{
		for (TiXmlElement* model = models->FirstChildElement(); 
		     model != NULL && invalidDoc == false; 
		     model = model->NextSiblingElement()) {
			
			std::string modelName(toLower(model->Value()));

			if (modelName.compare(MODEL) == 0) {
				parseModel(model);
			}
			else {

				// Uma tag models apenas pode ter a si associada filhos do tipo
				// model
				errorString.append("Error: Invalid models tag!\n");
				invalidDoc = true;
			}
		}
	}


	/**
	 * Efetua o parsing de um group.
	 *
	 * Sempre que se inicia um group é efetuada uma pushMatrix. No final do 
	 * tratamento de todos os elementos de um group é efetuada uma popMatrix.
	 *
	 * @param group Tag group.
	 */
	void parseGroup(TiXmlElement* group)
	{
		glOperations.push_back(new PushMatrix());

		pushContainerStacks();

		for (TiXmlElement* tag = group->FirstChildElement(); 
		     tag != NULL && invalidDoc == false; 
		     tag = tag->NextSiblingElement()) {
			
			parseTag(tag);
		}

		// Como já se processaram os elementos de um group então remove-se
		// a informação deste nas stacks auxiliares
		popContainerStacks();

		glOperations.push_back(new PopMatrix());
	}


	Vertex parsePoint(TiXmlElement* point)
	{
		float x = 0.0;
		float y = 0.0;
		float z = 0.0;

		std::string pointName = toLower(point->Value());

		if (pointName.compare(POINT) == 0) {
			for (TiXmlAttribute* a = point->FirstAttribute();
			     a != NULL && invalidDoc == false; a = a->Next()) {

				std::string attName(toLower(a->Name()));
				std::stringstream ss(a->Value());

				if (attName.compare(X) == 0) {
					ss >> x;
				}
				else if (attName.compare(Y) == 0) {
					ss >> y;
				}
				else if (attName.compare(Z) == 0) {
					ss >> z;
				}
				else {
					errorString.append("Error: Invalid translate attribute!\n");
					invalidDoc = true;
				}
			}
		}
		else {
			errorString.append("Error: ");
			errorString.append(pointName);
			errorString.append(" is not a valid tag!\n");
			invalidDoc = true;
		}

		return Vertex(x, y, z);
	}


	/**
	 * Efetua o parsing de uma translate.
	 *
     * @param translate Tag translate.
	 */
	void parseTranslate(TiXmlElement* translate)
	{
		float x = 0.0;
		float y = 0.0;
		float z = 0.0;
		float time = 0.0;
		std::vector<Vertex> catmullPoints;

		for (TiXmlAttribute* a = translate->FirstAttribute(); 
		     a != NULL && invalidDoc == false; a = a->Next()) {
			
			std::string attName(toLower(a->Name()));
			std::stringstream ss(a->Value());

			if (attName.compare(X) == 0) {
				ss >> x;
			}
			else if (attName.compare(Y) == 0) {
				ss >> y;
			}
			else if (attName.compare(Z) == 0) {
				ss >> z;
			}
			else if (attName.compare(TIME) == 0) {
				ss >> time;

				if (time > 0.0) {
					for (TiXmlElement* point = translate->FirstChildElement();
					     point != NULL && invalidDoc == false;
						 point = point->NextSiblingElement()) {

						catmullPoints.push_back(parsePoint(point));
					}
				}
				else {
					errorString.append("Error: Invalid time value!\n");
					invalidDoc = true;
				}
			}
			else {
				errorString.append("Error: Invalid translate attribute!\n");
				invalidDoc = true;
			}
		}

		if (time > 0.0 && catmullPoints.size() < 4) {
			errorString.append("Error: The number of Catmull-Rom points must be at least 4!\n");
		}

		glOperations.push_back(new Translation(x, y, z, catmullPoints, time));
	}


	/**
	 * Efetua o parsing de uma rotate.
	 *
	 * @param rotate Tag rotate.
	 */
	void parseRotate(TiXmlElement* rotate)
	{
		float angle = 0.0;
		float axisX = 0.0;
		float axisY = 0.0;
		float axisZ = 0.0;
		float time = 0.0;

		for (TiXmlAttribute* a = rotate->FirstAttribute(); 
		     a != NULL && invalidDoc == false; a = a->Next()) {
			
			std::string attName(toLower(a->Name()));
			std::stringstream ss(a->Value());

			if (attName.compare(ANGLE) == 0) {
				ss >> angle;
			}
			else if (attName.compare(AXISX) == 0) {
				ss >> axisX;
			}
			else if (attName.compare(AXISY) == 0) {
				ss >> axisY;
			}
			else if (attName.compare(AXISZ) == 0) {
				ss >> axisZ;
			}
			else if (attName.compare(TIME) == 0) {
				ss >> time;

				if (time < 0.0) {
					errorString.append("Error: Invalid time value!\n");
					invalidDoc = true;
				}
			}
			else {
				errorString.append("Error: Invalid rotate attribute!\n");
				invalidDoc = true;
			}
		}
		
		glOperations.push_back(new Rotation(angle, time, axisX, axisY, axisZ));
	}


	/**
	 * Efetua o parsing de uma scale.
	 *
	 * @param scale Tag scale.
	 */
	void parseScale(TiXmlElement* scale)
	{
		float x = 0.0;
		float y = 0.0;
		float z = 0.0;

		for (TiXmlAttribute* a = scale->FirstAttribute(); 
		     a != NULL && invalidDoc == false; a = a->Next()) {
			
			std::string attName(toLower(a->Name()));
			std::stringstream ss(a->Value());

			if (attName.compare(X) == 0) {
				ss >> x;
			}
			else if (attName.compare(Y) == 0) {
				ss >> y;
			}
			else if (attName.compare(Z) == 0) {
				ss >> z;
			}
			else {
				errorString.append("Error: Invalid scale attribute!\n");
				invalidDoc = true;
			}
		}

		glOperations.push_back(new Scale(x, y, z));
	}


	/**
	 * Testa a que tipo pertence uma tag e para cada tipo efetua o seu 
	 * respetivo parsing.
	 *
	 * @param tag Tag recebida.
	 */
	void parseTag(TiXmlElement* tag)
	{
		std::string tagName = toLower(tag->Value());

		// Testa se existe uma tag chamada model
		if (tagName.compare(MODELS) == 0) {
			if (somethingInContainer.top() == false) {
				somethingInContainer.pop();
				somethingInContainer.push(true);
			}

			// Se o número de models tags for igual ou superior a 1 então o
			// parsing termina
			if (modelsInContainer.top() == true) {
				errorString.append("Error: Duplicated models tag in group!\n");
				invalidDoc = true;
			}
			else {

				// O container passa a possuir uma models tag
				modelsInContainer.pop();
				modelsInContainer.push(true);
				parseModels(tag);
			}
		}
		else if (tagName.compare(GROUP) == 0) {
			if (somethingInContainer.top() == false) {
				somethingInContainer.pop();
				somethingInContainer.push(true);
			}

			parseGroup(tag);
		}
		else if (tagName.compare(TRANSLATE) == 0) {

			// Caso já haja uma translate num group ou caso a translate ocorra
			// depois de uma tag models ou group o parsing termina
			if (somethingInContainer.top() == true || 
				translatesInContainer.top() == true) {
				errorString.append("Error: Misplaced translate tag!\n");
				invalidDoc = true;
			}
			else {
				translatesInContainer.pop();
				translatesInContainer.push(true);

				parseTranslate(tag);
			}
		}
		else if (tagName.compare(ROTATE) == 0) {

			// Caso já haja uma rotate num group ou caso a rotate ocorra
			// depois de uma tag models ou group o parsing termina
			if (somethingInContainer.top() == true ||
				rotatesInContainer.top() == true) {
				errorString.append("Error: Misplaced rotate tag!\n");

				invalidDoc = true;
			}
			else {
				rotatesInContainer.pop();
				rotatesInContainer.push(true);

				parseRotate(tag);
			}
		}
		else if (tagName.compare(SCALE) == 0) {

			// Caso já haja uma scale num group ou caso a scale ocorra
			// depois de uma tag models ou group o parsing termina
			if (somethingInContainer.top() == true || 
				scalesInContainer.top() == true) {
				errorString.append("Error: Misplaced scale tag!\n");
				invalidDoc = true;
			}
			else {
				scalesInContainer.pop();
				scalesInContainer.push(true);

				parseScale(tag);
			}
		}

		// Apenas são admitidas tags dos tipos mencionados acima
		else {
			errorString.append("Error: ");
			errorString.append(tagName);
			errorString.append(" is not a valid tag!\n");
			invalidDoc = true;
		}
	}


	/**
	 * Efetua o parsing de um documento xml.
	 */
	void parseDocument(void)
	{
		// Estrutura auxiliar para realizar o parsing do documento xml
		TiXmlElement* scene = doc.FirstChildElement();

		// Testa se existe uma tag chamada scene
		if (scene == NULL || toLower(scene->Value()).compare(SCENE) != 0) {
			invalidDoc = true;
			errorString.append("Failed to load file. No scene element!\n");
			failedModels++;
		}
		else {
			pushContainerStacks();

			glOperations.push_back(new PushMatrix());

			// Processa cada um dos modelos
			for (TiXmlElement* tag = scene->FirstChildElement(); 
			     tag != NULL && invalidDoc == false; 
			     tag = tag->NextSiblingElement()) {
				
				parseTag(tag);
			}

			popContainerStacks();

			glOperations.push_back(new PopMatrix());
		}
	}


	/**
	 * Abre um documento xml para ser efetuado o seu parsing.
	 * 
	 * @return Devolve true caso o ficheiro tenha sido aberto com sucesso ou 
	 *         false caso contrário.
	 */
	bool openXMLFile(void)
	{
		bool ret = true;

		if (!doc.LoadFile(fileName.c_str())) {
			errorString.append("Could not read file ");
			errorString.append(fileName);
			errorString.append("...\n");
			ret = false;
		}

		return ret;
	}


public:


	/**
	 * Construtor por defeito.
	 */
	XMLParserImpl(void)
	{
		invalidDoc = false;
		numModels = failedModels = 0;
		errorString = "";
		fileName = "";
		srand(time(NULL));
	}


	/**
	 * Construtor por parâmetros.
	 *
	 * @param fileName Nome do ficheiro.
	 */
	XMLParserImpl(std::string fileName) 
	{
		invalidDoc = false;
		numModels = failedModels = 0;
		errorString = "";
		this->fileName = fileName;
		srand(time(NULL));

		// Abre o ficheiro com o nome fileName para ser efetuado o seu parsing
		if (openXMLFile() == true) {
			parseDocument();
		}
	}


	/**
	 * Devolve o número total de modelos lidos do ficheiro xml.
	 */
	size_t getNumModels(void)
	{
		return numModels;
	}


	/**
	 * Devolve o número de modelos que não se conseguiu processar.
	 */
	size_t getFailedModels(void)
	{
		return failedModels;
	}


	/**
	 * Devolve o vetor com o conjunto de operações em OpenGL.
 	 */
	std::vector<GLOperation*> getGLOperations(void)
	{
		if (invalidDoc == true) {

			// Se houve algum erro são limpas eventuais operações que já
			// tenham sido armazendas no vetor
			clearGLOperations();
		}

		return glOperations;
	}


	/**
	 * Devolve uma representação textual de eventuais erros, ou warnings, do
	 * parsing do ficheiro xml, caso estes existam.
	 */
	std::string getErrorString(void)
	{
		return errorString;
	}


	/**
	 * Devolve o nome do ficheiro xml que se efetuou o parsing.
	 */
	std::string getFileName(void)
	{
		return fileName;
	}


	/**
	 * Destrutor (por defeito em c++).
	 */
	~XMLParserImpl(void) = default;
};


/**
 * Construtor por defeito.
 */
XMLParser::XMLParser(void)
{
	pimpl = new XMLParserImpl();
}


/**
 * Construtor por parâmetros.
 *
 * @param fileName Nome do ficheiro.
 */
XMLParser::XMLParser(std::string fileName)
{
	pimpl = new XMLParserImpl(fileName);
}


/**
 * Construtor de cópia.
 *
 * @param x Objeto da classe XMLParser a copiar.
 */
XMLParser::XMLParser(const XMLParser& x)
{
	pimpl = new XMLParserImpl(x.pimpl->getFileName());
}


/**
 * Devolve o número total de modelos lidos do ficheiro xml.
 */
size_t XMLParser::getNumModels(void) 
{
	return pimpl->getNumModels();
}


/**
 * Devolve o número de modelos que não se conseguiu processar.
 */
size_t XMLParser::getFailedModels(void)
{
	return pimpl->getFailedModels();
}


/**
 * Devolve o vetor com o conjunto de operações em OpenGL.
 */
std::vector<GLOperation*> XMLParser::getGLOperations(void)
{
	return pimpl->getGLOperations();
}


/**
 * Devolve uma representação textual de eventuais erros, ou warnings, do
 * parsing do ficheiro xml, caso estes existam.
 */
std::string XMLParser::getErrorString(void)
{
	return pimpl->getErrorString();
}


/**
 * Destrutor da classe XMLParser. Liberta a memória ocupada pelo apontador para
 * implementação da classe XMLParser.
 */
XMLParser::~XMLParser(void)
{
	if (pimpl != NULL) {
		delete pimpl;
		pimpl = NULL;
	}
}