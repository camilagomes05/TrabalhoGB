/* Hello Triangle - c�digo adaptado de https://learnopengl.com/#!Getting-started/Hello-Triangle
 *
 * Adaptado por Rossana Baptista Queiroz
 * para a disciplina de Processamento Gr�fico - Jogos Digitais - Unisinos
 * Vers�o inicial: 7/4/2017
 * �ltima atualiza��o em 09/08/2021
 *
 */

#include <iostream>
#include <string>
#include <assert.h>
#include <cmath>


using namespace std;

// GLAD
#include <glad/glad.h>

// GLFW
#include <GLFW/glfw3.h>

#include <glm/glm.hpp> 
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "stb_image.h"

#include "Shader.h"

#include "Object.h"
#include "Sprite.h"

#include <vector>

using namespace std;

// Prot�tipo da fun��o de callback de teclado
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);

// Prot�tipos das fun��es
int setupGeometry();
int loadTexture(string path);
GLuint createSprite();

// Dimens�es da janela (pode ser alterado em tempo de execu��o)
const GLuint WIDTH = 800, HEIGHT = 600;
const int nPoints = 100 + 1 + 1; //+centro +c�pia do primeiro
const float pi = 3.14159;


// Fun��o MAIN
int main()
{
	// Inicializa��o da GLFW
	glfwInit();

	//Muita aten��o aqui: alguns ambientes n�o aceitam essas configura��es
	//Voc� deve adaptar para a vers�o do OpenGL suportada por sua placa
	//Sugest�o: comente essas linhas de c�digo para desobrir a vers�o e
	//depois atualize (por exemplo: 4.5 com 4 e 5)
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//Essencial para computadores da Apple
#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

	// Cria��o da janela GLFW
	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Hello PG Framework!", nullptr, nullptr);
	glfwMakeContextCurrent(window);

	// Fazendo o registro da fun��o de callback para a janela GLFW
	glfwSetKeyCallback(window, key_callback);

	// GLAD: carrega todos os ponteiros d fun��es da OpenGL
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;

	}

	// Obtendo as informa��es de vers�o
	const GLubyte* renderer = glGetString(GL_RENDERER); /* get renderer string */
	const GLubyte* version = glGetString(GL_VERSION); /* version as a string */
	cout << "Renderer: " << renderer << endl;
	cout << "OpenGL version supported " << version << endl;

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_ALWAYS);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// Compilando e buildando o programa de shader

	Shader* shader = new Shader("./shaders/sprite.vs", "./shaders/sprite.fs");
	Shader* sprShader = new Shader("./shaders/animatedsprites.vs", "./shaders/animatedsprites.fs");

	Shader* shaders[8];
	
	int j = 0;

	while (j <= 1) {

		//shaders[i] = new Shader("./textures/sh" + to_string(j) + ".png", "./shaders/sprite2.fs");
		shaders[0] = new Shader("./shaders/sprite2.vs", "./shaders/sprite2.fs");
		shaders[1] = new Shader("./shaders/sprite3.vs", "./shaders/sprite3.fs");
		shaders[2] = new Shader("./shaders/sprite4.vs", "./shaders/sprite4.fs");
		shaders[3] = new Shader("./shaders/sprite5.vs", "./shaders/sprite5.fs");
		shaders[4] = new Shader("./shaders/sprite6.vs", "./shaders/sprite6.fs");
		shaders[5] = new Shader("./shaders/sprite7.vs", "./shaders/sprite7.fs");
		shaders[6] = new Shader("./shaders/sprite8.vs", "./shaders/sprite8.fs");
		shaders[7] = new Shader("./shaders/sprite9.vs", "./shaders/sprite9.fs");

		j++;
	}

	// Background

	GLuint texID = loadTexture("./textures/fundo.jpg");

	Object backgroud;
	backgroud.initialize();
	backgroud.setPosition(glm::vec3(400, 300, 0));
	backgroud.setDimensions(glm::vec3(800, 600, 1.0));
	backgroud.setTexture(texID);
	backgroud.setShader(shader);


	// imagem

	GLuint texID2 = loadTexture("./textures/lena.png");

	Object foto;
	foto.initialize();
	foto.setPosition(glm::vec3(400, 330, 0));
	foto.setDimensions(glm::vec3(300, 300, 1.0));
	foto.setTexture(texID2);
	foto.setShader(shader);


	//Icones

	vector <Object> objects;


	//Retornando erro :/
	/*GLuint img[5];
	Object icon[5];

	int k = 0;
	int posX = 345.0;

	while (k <= 6) {
		img[k] = loadTexture("./textures/sh" + to_string(k) + ".png");
		icon[k].initialize();
		if (k == 0) {
			icon[0].setPosition(glm::vec3(posX, 500.0, 0.0));
		}
		else {
			icon[k].setPosition(glm::vec3(posX + 45.0, 500.0, 0.0));
			posX = posX + 45.0;
		}
		icon[k].setDimensions(glm::vec3(40.0, 40.0, 1.0));
		icon[k].setTexture(img[k]);
		icon[k].setShader(shader);
		k++;
	}*/

	GLuint texID3 = loadTexture("./textures/0.png");

	Object chapeu;
	chapeu.initialize();
	chapeu.setPosition(glm::vec3(345, 500, 0.0));
	chapeu.setDimensions(glm::vec3(35, 35, 1.0));
	chapeu.setTexture(texID3);
	chapeu.setShader(shader);

	GLuint texID4 = loadTexture("./textures/1.png");

	Object core;
	core.initialize();
	core.setPosition(glm::vec3(390, 500, 0.0));
	core.setDimensions(glm::vec3(35, 35, 1.0));
	core.setTexture(texID4);
	core.setShader(shader);

	GLuint texID5 = loadTexture("./textures/2.png");

	Object core2;
	core2.initialize();
	core2.setPosition(glm::vec3(435, 500, 0.0));
	core2.setDimensions(glm::vec3(40, 40, 1.0));
	core2.setTexture(texID5);
	core2.setShader(shader);

	GLuint texID6 = loadTexture("./textures/3.png");

	Object sol;
	sol.initialize();
	sol.setPosition(glm::vec3(480, 500, 0.0));
	sol.setDimensions(glm::vec3(40, 40, 1.0));
	sol.setTexture(texID6);
	sol.setShader(shader);

	GLuint texID7 = loadTexture("./textures/4.png");

	Object like;
	like.initialize();
	like.setPosition(glm::vec3(525, 500, 0.0));
	like.setDimensions(glm::vec3(30, 30, 1.0));
	like.setTexture(texID7);
	like.setShader(shader);

	// Filtros

	Object filtro[8];
	GLuint lena[8];

	int i = 0;
	int positionX = 50.0;

	while (i <= 7) {

		lena[i] = loadTexture("./textures/lena.png");
		filtro[i].initialize();
		if (i == 0) {
			filtro[i].setPosition(glm::vec3(positionX, 100.0, 0.0));
		}
		else {
			filtro[i].setPosition(glm::vec3(positionX + 100.0, 100.0, 0.0));
			positionX = positionX + 100.0;
		}
		filtro[i].setDimensions(glm::vec3(90.0, 90.0, 1.0));
		filtro[i].setTexture(lena[i]);
		filtro[i].setShader(shaders[0]);
		i++;
	}

	// Yoshi

	GLuint texID8 = loadTexture("./textures/yoshi.png");

	Sprite yoshi;
	yoshi.setSpritesheet(texID8, 2, 8);
	yoshi.setPosition(glm::vec3(255, 500, 0.0));
	yoshi.setDimensions(glm::vec3(35, 35, 1.0));
	yoshi.setShader(sprShader);
	yoshi.setAnimation(1);

	GLuint texID9 = loadTexture("./textures/characterRun.png");

	Sprite player;
	player.setSpritesheet(texID9, 1, 6);
	player.setPosition(glm::vec3(300, 500, 0.0));
	player.setDimensions(glm::vec3(35, 35, 1.0));
	player.setShader(sprShader);

	// Gerando um buffer simples, com a geometria de um tri�ngulo
	//GLuint VAO = setupGeometry();
	GLuint VAO = createSprite();

	//Ativando o shader que ser� usado
	shader->Use();

	// Enviando a cor desejada (vec4) para o fragment shader
	// Utilizamos a vari�veis do tipo uniform em GLSL para armazenar esse tipo de info
	// que n�o est� nos buffers

	GLint projLoc = glGetUniformLocation(shader->Program, "projection");
	assert(projLoc > -1);

	/*GLint modelLoc = glGetUniformLocation(shader->Program, "model");
	assert(modelLoc > -1);*/

	glUniform1i(glGetUniformLocation(shader->Program, "tex1"), 0);

	glm::mat4 ortho = glm::mat4(1); //inicializa com a matriz identidade

	glm::mat4 model = glm::mat4(1);

	double xmin = 0.0, xmax = 800.0, ymin = 0.0, ymax = 600.0;

	shader->Use();
	shader->setVec4("corColorizadora", 1.0, 1.0, 0.0, 1.0);

	// Loop da aplica��o - "game loop"
	while (!glfwWindowShouldClose(window))
	{
		// Checa se houveram eventos de input (key pressed, mouse moved etc.) e chama as fun��es de callback correspondentes
		glfwPollEvents();

		// Definindo as dimens�es da viewport com as mesmas dimens�es da janela da aplica��o
		int width, height;
		glfwGetFramebufferSize(window, &width, &height);
		glViewport(0, 0, width, height);

		ortho = glm::ortho(xmin, xmax, ymin, ymax, -1.0, 1.0);


		//Enviar a matriz de proje��o ortogr�fica para o shader
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(ortho));


		// Limpa o buffer de cor
		glClearColor(0.3f, 0.3f, 0.3f, 1.0f); //cor de fundo
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		backgroud.update();
		backgroud.draw();

		foto.update();
		foto.draw();

		chapeu.update();
		chapeu.draw();

		core.update();
		core.draw();

		core2.update();
		core2.draw();

		sol.update();
		sol.draw();

		like.update();
		like.draw();

		/*int q = 0;

		while (q <= 6) {
			icon[q].update();
			icon[q].draw();
			q++;
		}*/

		int p = 0;

		while (p <= 7) {
			filtro[p].update();
			filtro[p].draw();
			p++;
		}

		sprShader->Use();
		sprShader->setMat4("projection", glm::value_ptr(ortho));


		// Para caminhar lentamente
		Sleep(200);

		player.update();
		player.draw();

		yoshi.update();
		yoshi.draw();

		// Troca os buffers da tela
		glfwSwapBuffers(window);
	}
	// Pede pra OpenGL desalocar os buffers
	glDeleteVertexArrays(1, &VAO);
	// Finaliza a execu��o da GLFW, limpando os recursos alocados por ela
	glfwTerminate();
	return 0;
}

// Fun��o de callback de teclado - s� pode ter uma inst�ncia (deve ser est�tica se
// estiver dentro de uma classe) - � chamada sempre que uma tecla for pressionada
// ou solta via GLFW
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
}

int loadTexture(string path)
{
	GLuint texID;

	// Gera o identificador da textura na mem�ria 
	glGenTextures(1, &texID);
	glBindTexture(GL_TEXTURE_2D, texID);

	//Ajusta os par�metros de wrapping e filtering
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	//Carregamento da imagem
	int width, height, nrChannels;
	unsigned char* data = stbi_load(path.c_str(), &width, &height, &nrChannels, 0);

	if (data)
	{
		if (nrChannels == 3) //jpg, bmp
		{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		}
		else //png
		{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		}
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}

	stbi_image_free(data);

	glBindTexture(GL_TEXTURE_2D, 0);

	return texID;
}

GLuint createSprite()
{
	GLuint VAO;
	GLuint VBO, EBO;

	glGenVertexArrays(1, &VAO);

	return VAO;
}