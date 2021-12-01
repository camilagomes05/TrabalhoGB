/* Hello Triangle - código adaptado de https://learnopengl.com/#!Getting-started/Hello-Triangle
 *
 * Adaptado por Rossana Baptista Queiroz
 * para a disciplina de Processamento Gráfico - Jogos Digitais - Unisinos
 * Versão inicial: 7/4/2017
 * Última atualização em 09/08/2021
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


// Protótipo da função de callback de teclado
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);

// Protótipos das funções
int loadTexture(string path);
GLuint createSprite();

// Dimensões da janela (pode ser alterado em tempo de execução)
const GLuint WIDTH = 800, HEIGHT = 600;
const int nPoints = 100 + 1 + 1; //+centro +cópia do primeiro
const float pi = 3.14159;
double xpos, ypos, xposx, yposy;


// Função MAIN
int main()
{
	// Inicialização da GLFW
	glfwInit();

	//Muita atenção aqui: alguns ambientes não aceitam essas configurações
	//Você deve adaptar para a versão do OpenGL suportada por sua placa
	//Sugestão: comente essas linhas de código para desobrir a versão e
	//depois atualize (por exemplo: 4.5 com 4 e 5)
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//Essencial para computadores da Apple
#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

	// Criação da janela GLFW
	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Hello PG Framework!", nullptr, nullptr);
	glfwMakeContextCurrent(window);

	// Fazendo o registro da função de callback para a janela GLFW
	glfwSetMouseButtonCallback(window, mouse_button_callback);


	// GLAD: carrega todos os ponteiros d funções da OpenGL
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;

	}

	// Obtendo as informações de versão
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
	string vs[8];
	string fs[8];
	
	int j = 0;
	int k = 2;

	while (j <= 7 || k <= 9) {

		vs[j] = "./shaders/sprite" + to_string(k) + ".vs";
		fs[j] = "./shaders/sprite" + to_string(k) + ".fs";

		shaders[j] = new Shader(vs[j].c_str(), fs[j].c_str());

		j++;
		k++;
	}


	// Background
	GLuint texID = loadTexture("./textures/fundo.jpg");

	Object backgroud;
	backgroud.initialize();
	backgroud.setPosition(glm::vec3(400, 300, 0));
	backgroud.setDimensions(glm::vec3(800, 600, 1.0));
	backgroud.setTexture(texID);
	backgroud.setShader(shader);

	//Pedir imagem
	string nomeImg;
	cout << "Digite o nome/path da imagem: ";
	cin >> nomeImg;

	GLuint texID2 = loadTexture(nomeImg);

	Object foto;
	foto.initialize();
	foto.setPosition(glm::vec3(400, 330, 0));
	foto.setDimensions(glm::vec3(300, 300, 1.0));
	foto.setTexture(texID2);
	foto.setShader(shader);


	//Icones
	vector <Object> objects;

	GLuint img[5];
	Object icon[5];

	int l = 0;
	int posX = 345.0;

	while (l <= 4) {
		img[l] = loadTexture("./textures/" + to_string(l) + ".png");
		icon[l].initialize();
		if (l == 0) {
			icon[0].setPosition(glm::vec3(posX, 510.0, 0.0));
		}
		else {
			icon[l].setPosition(glm::vec3(posX + 45.0, 510.0, 0.0));
			posX = posX + 45.0;
		}
		icon[l].setDimensions(glm::vec3(40.0, 40.0, 1.0));
		icon[l].setTexture(img[l]);
		icon[l].setShader(shader);
		l++;
	}


	// Yoshi

	GLuint texID8 = loadTexture("./textures/yoshi.png");

	Sprite yoshi;
	yoshi.setSpritesheet(texID8, 2, 8);
	yoshi.setPosition(glm::vec3(255, 510, 0.0));
	yoshi.setDimensions(glm::vec3(40, 40, 1.0));
	yoshi.setShader(sprShader);
	yoshi.setAnimation(1);

	GLuint texID9 = loadTexture("./textures/characterRun.png");

	Sprite player;
	player.setSpritesheet(texID9, 1, 6);
	player.setPosition(glm::vec3(300, 510, 0.0));
	player.setDimensions(glm::vec3(40, 40, 1.0));
	player.setShader(sprShader);


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
		filtro[i].setShader(shaders[i]);
		i++;
	}


	// Gerando um buffer simples, com a geometria de um triângulo
	GLuint VAO = createSprite();


	//Ativando o shader que será usado
	shader->Use();

	GLint projLoc = glGetUniformLocation(shader->Program, "projection");
	assert(projLoc > -1);

	glUniform1i(glGetUniformLocation(shader->Program, "tex1"), 0);

	
	int n = 0;
	while (n <= 7) {
		shaders[n]->Use();

		GLint projLoc = glGetUniformLocation(shaders[n]->Program, "projection");
		assert(projLoc > -1);

		glUniform1i(glGetUniformLocation(shaders[n]->Program, "tex1"), 0);

		n++;
	}


	//inicializa com a matriz identidade
	glm::mat4 ortho = glm::mat4(1); 

	glm::mat4 model = glm::mat4(1);

	double xmin = 0.0, xmax = 800.0, ymin = 0.0, ymax = 600.0;

	shader->Use();


	// Loop da aplicação - "game loop"
	while (!glfwWindowShouldClose(window))
	{
		// Checa se houveram eventos de input (key pressed, mouse moved etc.) e chama as funções de callback correspondentes
		glfwPollEvents();

		// Definindo as dimensões da viewport com as mesmas dimensões da janela da aplicação
		int width, height;
		glfwGetFramebufferSize(window, &width, &height);
		glViewport(0, 0, width, height);

		ortho = glm::ortho(xmin, xmax, ymin, ymax, -1.0, 1.0);


		//Enviar a matriz de projeção ortográfica para o shader
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(ortho));


		// Limpa o buffer de cor
		glClearColor(0.3f, 0.3f, 0.3f, 1.0f); //cor de fundo
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		backgroud.update();
		backgroud.draw();

		foto.update();
		foto.draw();

		int q = 0;

		while (q <= 4) {
			icon[q].update();
			icon[q].draw();
			q++;
		}

		int p = 0;

		while (p <= 7) {
			filtro[p].update();
			glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(ortho));
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


		//Mudar filtro
		if (xpos >= 5 && xpos <= 95 && ypos >= 452 && ypos <= 545) {
			foto.setShader(shaders[0]);
		}
		else if (xpos >= 104 && xpos <= 195 && ypos >= 452 && ypos <= 545) {
			foto.setShader(shaders[1]);
		}
		else if (xpos >= 204 && xpos <= 295 && ypos >= 452 && ypos <= 545) {
			foto.setShader(shaders[2]);
		}
		else if (xpos >= 304 && xpos <= 395 && ypos >= 452 && ypos <= 545) {
			foto.setShader(shaders[3]);
		}
		else if (xpos >= 404 && xpos <= 495 && ypos >= 452 && ypos <= 545) {
			foto.setShader(shaders[4]);
		}
		else if (xpos >= 504 && xpos <= 595 && ypos >= 452 && ypos <= 545) {
			foto.setShader(shaders[5]);
		}
		else if (xpos >= 604 && xpos <= 695 && ypos >= 452 && ypos <= 545) {
			foto.setShader(shaders[6]);
		}
		else if (xpos >= 704 && xpos <= 795 && ypos >= 452 && ypos <= 545) {
			foto.setShader(shaders[7]);
		}
		else if (xpos >= 0 && xpos <= 250 && ypos >= 115 && ypos <= 425) {
			foto.setShader(shader);
		}


		//Mexer icon
		glfwGetCursorPos(window, &xposx, &yposy);

		if (xpos >= 235 && xpos <= 275 && ypos >= 50 && ypos <= 110) {
			yoshi.setPosition(glm::vec3(xposx, 600 - yposy, 0.0));
		}
		else if (xpos >= 285 && xpos <= 325 && ypos >= 50 && ypos <= 110) {
			player.setPosition(glm::vec3(xposx, 600 - yposy, 0.0));
		}
		else if (xpos >= 326 && xpos <= 360 && ypos >= 50 && ypos <= 110) {
			icon[0].setPosition(glm::vec3(xposx, 600 - yposy, 0.0));
		}
		else if (xpos >= 367 && xpos <= 410 && ypos >= 50 && ypos <= 110) {
			icon[1].setPosition(glm::vec3(xposx, 600 - yposy, 0.0));
		}
		else if (xpos >= 416 && xpos <= 457 && ypos >= 50 && ypos <= 110) {
			icon[2].setPosition(glm::vec3(xposx, 600 - yposy, 0.0));
		}
		else if (xpos >= 460 && xpos <= 497 && ypos >= 50 && ypos <= 110) {
			icon[3].setPosition(glm::vec3(xposx, 600 - yposy, 0.0));
		}
		else if (xpos >= 504 && xpos <= 546 && ypos >= 50 && ypos <= 110) {
			icon[4].setPosition(glm::vec3(xposx, 600 - yposy, 0.0));
		}
		else if (xpos >= 550 && xpos <= 800 && ypos >= 115 && ypos <= 420) {
			yoshi.setPosition(glm::vec3(255, 510, 0.0));
			player.setPosition(glm::vec3(300, 510, 0.0));

			int z = 0;

			int iconposx = 345;

			while (z <= 4) {
				if (z == 0) {
					icon[0].setPosition(glm::vec3(iconposx, 510.0, 0.0));
				}
				else {
					icon[z].setPosition(glm::vec3(iconposx + 45.0, 510.0, 0.0));
					iconposx = iconposx + 45.0;
				}
				z++;
		    }
		}


		// Troca os buffers da tela
		glfwSwapBuffers(window);
	}
	// Pede pra OpenGL desalocar os buffers
	glDeleteVertexArrays(1, &VAO);
	// Finaliza a execução da GLFW, limpando os recursos alocados por ela
	glfwTerminate();
	return 0;
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
	int state = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT);
	if (state == GLFW_PRESS) {
		glfwGetCursorPos(window, &xpos, &ypos);
		cout << xpos << " " << ypos << endl;
	}

}

int loadTexture(string path)
{
	GLuint texID;

	// Gera o identificador da textura na memória 
	glGenTextures(1, &texID);
	glBindTexture(GL_TEXTURE_2D, texID);

	//Ajusta os parâmetros de wrapping e filtering
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