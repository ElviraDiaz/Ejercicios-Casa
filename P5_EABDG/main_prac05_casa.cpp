/*---------------------------------------------------------*/
/* ----------------   Práctica 5 --------------------------*/
/*-----------------    2019-2   ---------------------------*/
/*------------- Computación gráfica e interacción humano computadora  ---------------*/
/*--------------Díaz Gutiérrez Elvira Angela Belem---------------------*/
/*------------------ Visual Studio Versión 2017 --------------------*/
/* Instrucciones de uso:
Para poder observar, mover y rotar la imagen se debe tienen las siguientes teclas con sus respectivas acciones:
	D					Mueve la figura a la derecha
	A					Mueve la figura a la izquierda
	AvPág				Mueve la figura hacia abajo
	RePág				Mueve la figura hacia arriba
	W					Aleja la figura
	S					Acerca la figura
	Flecha abajo		Rota la figura hacia enfrente
	Flecha arriba		Rota la figura hacia atras
	Flecha izquierda	Rota la figura hacia la izquierda
	Flecha derecha		Rota la figura hacia la derecha

	Teclas que controlan el BRAZO DERECHO
	T				Rota el HOMBRO  hacia abajo y si se aprieta con shift derecho rota hacia arriba 
	Y				Rota el ANTEBRAZO hacia enfrente y si se aprieta con shift derecho rota hacia atras 
	U				Rota la MANO hacia enfrente	y si se aprieta con shift derecho rota hacia atras 
	I				Rota el PULGAR hacia enfrente y si se aprieta con shift derecho rota hacia atras 
	O				Rota el INDICE hacia enfrente y si se aprieta con shift derecho rota hacia atras 
	P				Rota el MEDIO hacia enfrente y si se aprieta con shift derecho rota hacia atras 
	L				Rota el ANULAR hacia enfrente y si se aprieta con shift derecho rota hacia atras 
	K				Rota el MEÑIQUE hacia enfrente y si se aprieta con shift derecho rota hacia atras 

	Teclas que controlan el BRAZO IZQUIERDO
	Z				Rota el HOMBRO hacia abajo y si se aprieta con shift derecho rota hacia arriba 
	X				Rota el ANTEBRAZO hacia enfrente y si se aprieta con shift derecho rota hacia atras  
	C				Rota la MANO hacia enfrente	y si se aprieta con shift derecho rota hacia atras 
	V				Rota el PULGAR hacia enfrente y si se aprieta con shift derecho rota hacia atras 
	B				Rota el INDICE hacia enfrente y si se aprieta con shift derecho rota hacia atras 
	N				Rota el MEDIO hacia enfrente y si se aprieta con shift derecho rota hacia atras  
	M				Rota el ANULAR hacia enfrente y si se aprieta con shift derecho rota hacia atras 
	J				Rota el MEÑIQUE hacia enfrente y si se aprieta con shift derecho rota hacia atras 
	
*/

#include <glew.h>
#include <glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <shader_m.h>

#include <iostream>

void resize(GLFWwindow* window, int width, int height);
void my_input(GLFWwindow *window);

// settings
// Window size
int SCR_WIDTH = 3800;
int SCR_HEIGHT = 7600;

GLFWmonitor *monitors;
GLuint VBO, VAO, EBO;

void myData(void);
void display(void);
void getResolution(void);

//For Keyboard

float	movX = 0.0f,		//Variable de traslación en X
		movY = 0.0f,		//Variable de traslación en Y
		movZ = -5.0f,		//Variable de traslación en Z
		angX = 0.0f,		//Ángulo de rotación en X
		angY = 0.0f;		//Ángulo de rotación en Y
float angHomIzq = 0.0f,		//Ángulo de rotación del hombro izquiero
angAntIzq = 0.0f,			//Ángulo de rotación del antebrazo (codo) izquierdo
angManoIzq = 0.0f,			//Ángulo de rotación de la mano (muñeca) izquierda
angPuIzq = 0.0f,			//Ángulo de rotación del pulgar izquierdo
angInIzq = 0.0f,			//Ángulo de rotación del indice izquierdo
angMedIzq = 0.0f,			//Ángulo de rotación del medio izquierdo
angAnIzq = 0.0f,			//Ángulo de rotación del anular izquierdo
angMeIzq = 0.0f,			//Ángulo de rotación del meñique izquierdo
angHomDer = 0.0f,			//Ángulo de rotación del hombro derecho
angAntDer = 0.0f,			//Ángulo de rotación del antebrazo (codo) derecho
angManoDer = 0.0f,			//Ángulo de rotación de la mano (muñeca) derecha
angPuDer = 0.0f,			//Ángulo de rotación del pulgar derecho
angInDer = 0.0f,			//Ángulo de rotación del indice derecho
angMedDer = 0.0f,			//Ángulo de rotación del medio derecho
angAnDer = 0.0f,			//Ángulo de rotación del anular derecho
angMeDer = 0.0f				//Ángulo de rotación del meñique derecho
;

void getResolution()
{
	const GLFWvidmode * mode = glfwGetVideoMode(glfwGetPrimaryMonitor());

	SCR_WIDTH = mode->width;
	SCR_HEIGHT = (mode->height) - 80;
}

void myData()
{	
		GLfloat vertices[] = {
		//Position				//Color
		-0.5f, -0.5f, 0.5f,		1.0f, 0.0f, 0.0f,	//V0 - Frontal
		0.5f, -0.5f, 0.5f,		1.0f, 0.0f, 0.0f,	//V1
		0.5f, 0.5f, 0.5f,		1.0f, 0.0f, 0.0f,	//V5
		-0.5f, 0.5f, 0.5f,		1.0f, 0.0f, 0.0f,	//V4

		0.5f, -0.5f, -0.5f,		1.0f, 1.0f, 0.0f,	//V2 - Trasera
		-0.5f, -0.5f, -0.5f,	1.0f, 1.0f, 0.0f,	//V3
		-0.5f, 0.5f, -0.5f,		1.0f, 1.0f, 0.0f,	//V7
		0.5f, 0.5f, -0.5f,		1.0f, 1.0f, 0.0f,	//V6

		-0.5f, 0.5f, 0.5f,		0.0f, 0.0f, 1.0f,	//V4 - Izq
		-0.5f, 0.5f, -0.5f,		0.0f, 0.0f, 1.0f,	//V7
		-0.5f, -0.5f, -0.5f,	0.0f, 0.0f, 1.0f,	//V3
		-0.5f, -0.5f, 0.5f,		0.0f, 0.0f, 1.0f,	//V0

		0.5f, 0.5f, 0.5f,		0.0f, 1.0f, 0.0f,	//V5 - Der
		0.5f, -0.5f, 0.5f,		0.0f, 1.0f, 0.0f,	//V1
		0.5f, -0.5f, -0.5f,		0.0f, 1.0f, 0.0f,	//V2
		0.5f, 0.5f, -0.5f,		0.0f, 1.0f, 0.0f,	//V6

		-0.5f, 0.5f, 0.5f,		1.0f, 0.0f, 1.0f,	//V4 - Sup
		0.5f, 0.5f, 0.5f,		1.0f, 0.0f, 1.0f,	//V5
		0.5f, 0.5f, -0.5f,		1.0f, 0.0f, 1.0f,	//V6
		-0.5f, 0.5f, -0.5f,		1.0f, 0.0f, 1.0f,	//V7

		-0.5f, -0.5f, 0.5f,		1.0f, 1.0f, 1.0f,	//V0 - Inf
		-0.5f, -0.5f, -0.5f,	1.0f, 1.0f, 1.0f,	//V3
		0.5f, -0.5f, -0.5f,		1.0f, 1.0f, 1.0f,	//V2
		0.5f, -0.5f, 0.5f,		1.0f, 1.0f, 1.0f,	//V1
	};

	unsigned int indices[] =	//I am not using index for this session
	{
		0
	};

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &VBO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// color attribute
	//glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	//glEnableVertexAttribArray(1);

	//Para trabajar con indices (Element Buffer Object)
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);

}

void display(void)
{
	//Shader myShader("shaders/shader.vs", "shaders/shader.fs");
	Shader projectionShader("shaders/shader_projection.vs", "shaders/shader_projection.fs");

	projectionShader.use();

	// create transformations and Projection
	glm::mat4 modelTemp = glm::mat4(1.0f); //Temp
	glm::mat4 modelTemp2 = glm::mat4(1.0f); //Temp
	glm::mat4 model = glm::mat4(1.0f);		// initialize Matrix, Use this matrix for individual models
	glm::mat4 view = glm::mat4(1.0f);		//Use this matrix for ALL models
	glm::mat4 projection = glm::mat4(1.0f);	//This matrix is for Projection

	
	//Use "projection" in order to change how we see the information
	projection = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
	//projection = glm::ortho(-5.0f, 5.0f, -3.0f, 3.0f, 0.1f, 10.0f);

	//Use "view" in order to affect all models
	view = glm::translate(view, glm::vec3(movX, movY, movZ));
	view = glm::rotate(view,glm::radians(angX),glm::vec3(0,1,0));//Hace la rotacion
	view = glm::rotate(view, glm::radians(angY), glm::vec3(1, 0, 0));
	// pass them to the shaders
	projectionShader.setMat4("model", model);
	projectionShader.setMat4("view", view);
	// note: currently we set the projection matrix each frame, but since the projection matrix rarely changes it's often best practice to set it outside the main loop only once.
	projectionShader.setMat4("projection", projection);


	glBindVertexArray(VAO);
	//Tronco
	projectionShader.setVec3("aColor", glm::vec3(0.0f, 0.0f, 1.0f));
	model = glm::scale(model, glm::vec3(4, 5, 1));
	projectionShader.setMat4("model",model);
	glDrawArrays(GL_QUADS, 0, 24); 
	//Cinturon
	model = glm::translate(model = glm::mat4(1.0f), glm::vec3(0,-3.5, 0));
	model = glm::scale(model, glm::vec3(4, 2, 1));
	projectionShader.setVec3("aColor", glm::vec3(1.0f, 1.0f, 0.0f));
	projectionShader.setMat4("model", model);
	glDrawArrays(GL_QUADS, 0, 24);
	//Pierna izquierda
	model = glm::translate(model = glm::mat4(1.0f), glm::vec3(-1.5, -6.0, 0));
	model = glm::scale(model, glm::vec3(1, 3, 1));
	projectionShader.setVec3("aColor", glm::vec3(1.0f, 1.0f, 1.0f));
	projectionShader.setMat4("model", model);
	glDrawArrays(GL_QUADS, 0, 24);
	//Pie izquierdo
	model = glm::translate(model = glm::mat4(1.0f), glm::vec3(-3.0, -8.0, 0));
	model = glm::scale(model, glm::vec3(4, 1, 1));
	projectionShader.setVec3("aColor", glm::vec3(0.6f, 0.3f, 0.0f));
	projectionShader.setMat4("model", model);
	glDrawArrays(GL_QUADS, 0, 24);
	//Pierna derecha
	model = glm::translate(model = glm::mat4(1.0f), glm::vec3(1.5, -6.0, 0));
	model = glm::scale(model, glm::vec3(1, 3, 1));
	projectionShader.setVec3("aColor", glm::vec3(1.0f, 1.0f, 1.0f));
	projectionShader.setMat4("model", model);
	glDrawArrays(GL_QUADS, 0, 24);
	//Pie derecho
	model = glm::translate(model = glm::mat4(1.0f), glm::vec3(3.0, -8.0, 0));
	model = glm::scale(model, glm::vec3(4, 1, 1));
	projectionShader.setVec3("aColor", glm::vec3(0.6f, 0.3f, 0.0f));
	projectionShader.setMat4("model", model);
	glDrawArrays(GL_QUADS, 0, 24);

	//Hombro izquierdo
	model = glm::translate(model = glm::mat4(1.0f), glm::vec3(-2.5, 2.0, 0));
	modelTemp = model;
	model = glm::rotate(model, glm::radians(-angHomIzq), glm::vec3(0, 0, 1));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(1, 1, 0));
	glDrawArrays(GL_QUADS, 0, 24);
	//Bicep izquierdo
	model = glm::translate(model, glm::vec3(-1.5, 0, 0));
	modelTemp = model;
	model = glm::scale(model, glm::vec3(2, 1, 0.7));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(0.0f, 0.0f, 1.0f));
	glDrawArrays(GL_QUADS, 0, 24);
	model = modelTemp;
	//Antebrazo izquierdo
	model = glm::translate(model, glm::vec3(-1, 0, 0));
	model = glm::rotate(model, glm::radians(-angAntIzq), glm::vec3(0, 1, 0));
	model = glm::translate(model, glm::vec3(-1.5, 0, 0));
	modelTemp = model;
	projectionShader.setMat4("model", model);
	model = glm::scale(model, glm::vec3(3, 1, 0.7));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(1.0f, 0.0f, 0.0f));
	glDrawArrays(GL_QUADS, 0, 24);
	model = modelTemp;
	//Mano izquierda
	model = glm::translate(model, glm::vec3(-1.5, 0, 0));
	model = glm::rotate(model, glm::radians(-angManoIzq), glm::vec3(0, 1, 0));
	model = glm::translate(model, glm::vec3(-0.5, 0, 0));
	modelTemp = model;
	modelTemp2 = model;
	projectionShader.setMat4("model", model);
	model = glm::scale(model, glm::vec3(1, 1, 0.3));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(0.0f, 1.0f, 0.0f));
	glDrawArrays(GL_QUADS, 0, 24);
	//Pulgar Inferior izquierdo
	model = glm::translate(model, glm::vec3(0.35, 0.5, 0));
	model = glm::rotate(model, glm::radians(angPuIzq), glm::vec3(1, 0, 0));
	model = glm::translate(model, glm::vec3(0, 0.15, 0));
	modelTemp = model;
	projectionShader.setMat4("model", model);
	model = glm::scale(model, glm::vec3(0.3, 0.3, 0.3));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(0.5f, 0.0f, 0.5f));
	glDrawArrays(GL_QUADS, 0, 24);
	model = modelTemp;
	//Pulgar Superior izquierdo
	model = glm::translate(model, glm::vec3(0, 0.15, 0));
	model = glm::rotate(model, glm::radians(angPuIzq*0.7f), glm::vec3(1, 0, 0));
	model = glm::translate(model, glm::vec3(0, 0.15, 0));
	modelTemp = model;
	projectionShader.setMat4("model", model);
	model = glm::scale(model, glm::vec3(0.3, 0.3, 0.3));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(1.0f, 0.0f, 0.5f));
	glDrawArrays(GL_QUADS, 0, 24);
	//Indice inferior izquierdo
	model = modelTemp2;
	model = glm::translate(model, glm::vec3(-0.5, 0.38, 0));
	modelTemp2 = model;//contiene inicio de falange
	model = glm::rotate(model, glm::radians(-angInIzq), glm::vec3(0, 1, 0));
	model = glm::translate(model, glm::vec3(-0.15, 0, 0));
	modelTemp = model;
	projectionShader.setMat4("model", model);
	model = glm::scale(model, glm::vec3(0.3, 0.25, 0.3));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(0.168f, 0.564f, 0.933f));
	glDrawArrays(GL_QUADS, 0, 24);
	//Indice medio izquierdo
	model = modelTemp;
	model = glm::translate(model, glm::vec3(-0.15, 0, 0));
	model = glm::rotate(model, glm::radians(-angInIzq*0.5f), glm::vec3(0, 1, 0));
	model = glm::translate(model, glm::vec3(-0.15, 0, 0));
	modelTemp = model;
	projectionShader.setMat4("model", model);
	model = glm::scale(model, glm::vec3(0.3, 0.25, 0.3));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(0.117f, 0.835f, 0.921f));
	glDrawArrays(GL_QUADS, 0, 24);
	//Indice Superior izquierdo
	model = modelTemp;
	model = glm::translate(model, glm::vec3(-0.15, 0, 0));
	model = glm::rotate(model, glm::radians(-angInIzq* 0.9f), glm::vec3(0, 1, 0));
	model = glm::translate(model, glm::vec3(-0.15, 0, 0));
	modelTemp = model;
	projectionShader.setMat4("model", model);
	model = glm::scale(model, glm::vec3(0.3, 0.25, 0.3));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(0.094f, 0.968f, 0.843f));
	glDrawArrays(GL_QUADS, 0, 24);
	//Medio inferior izquierdo
	model = modelTemp2;
	model = glm::translate(model, glm::vec3(0, -0.25, 0));
	model = glm::rotate(model, glm::radians(-angMedIzq), glm::vec3(0, 1, 0));
	model = glm::translate(model, glm::vec3(-0.2, 0, 0));
	modelTemp = model;
	projectionShader.setMat4("model", model);
	model = glm::scale(model, glm::vec3(0.4, 0.25, 0.3));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(0.968f, 0.2f, 0.094f));
	glDrawArrays(GL_QUADS, 0, 24);
	//Medio medio izquierdo
	model = modelTemp;
	model = glm::translate(model, glm::vec3(-0.2, 0, 0));
	model = glm::rotate(model, glm::radians(-angMedIzq*0.5f), glm::vec3(0, 1, 0));
	model = glm::translate(model, glm::vec3(-0.2, 0, 0));
	modelTemp = model;
	projectionShader.setMat4("model", model);
	model = glm::scale(model, glm::vec3(0.4, 0.25, 0.3));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(0.968f, 0.407f, 0.094f));
	glDrawArrays(GL_QUADS, 0, 24);
	//Medio Superior izquierdo
	model = modelTemp;
	model = glm::translate(model, glm::vec3(-0.2, 0, 0));
	model = glm::rotate(model, glm::radians(-angMedIzq* 0.9f), glm::vec3(0, 1, 0));
	model = glm::translate(model, glm::vec3(-0.2, 0, 0));
	modelTemp = model;
	projectionShader.setMat4("model", model);
	model = glm::scale(model, glm::vec3(0.4, 0.25, 0.3));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(0.968f, 0.580f, 0.094f));
	glDrawArrays(GL_QUADS, 0, 24);
	//Anular inferior izquierdo
	model = modelTemp2;
	model = glm::translate(model, glm::vec3(0, -0.5, 0));
	model = glm::rotate(model, glm::radians(-angAnIzq), glm::vec3(0, 1, 0));
	model = glm::translate(model, glm::vec3(-0.15, 0, 0));
	modelTemp = model;
	projectionShader.setMat4("model", model);
	model = glm::scale(model, glm::vec3(0.3, 0.25, 0.3));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(1.0f, 0.8f, 0.1f));
	glDrawArrays(GL_QUADS, 0, 24);
	//Anular medio izquierdo
	model = modelTemp;
	model = glm::translate(model, glm::vec3(-0.15, 0, 0));
	model = glm::rotate(model, glm::radians(-angAnIzq*0.5f), glm::vec3(0, 1, 0));
	model = glm::translate(model, glm::vec3(-0.15, 0, 0));
	modelTemp = model;
	projectionShader.setMat4("model", model);
	model = glm::scale(model, glm::vec3(0.3, 0.25, 0.3));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(1.0f, 1.0f, 0.0f));
	glDrawArrays(GL_QUADS, 0, 24);
	//Anular Superior izquierdo
	model = modelTemp;
	model = glm::translate(model, glm::vec3(-0.15, 0, 0));
	model = glm::rotate(model, glm::radians(-angAnIzq* 0.9f), glm::vec3(0, 1, 0));
	model = glm::translate(model, glm::vec3(-0.15, 0, 0));
	modelTemp = model;
	projectionShader.setMat4("model", model);
	model = glm::scale(model, glm::vec3(0.3, 0.25, 0.3));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(0.980f, 0.984f, 0.615f));
	glDrawArrays(GL_QUADS, 0, 24);
	//Meñique inferior izquierdo
	model = modelTemp2;
	model = glm::translate(model, glm::vec3(0, -0.75, 0));
	model = glm::rotate(model, glm::radians(-angMeIzq), glm::vec3(0, 1, 0));
	model = glm::translate(model, glm::vec3(-0.1, 0, 0));
	modelTemp = model;
	projectionShader.setMat4("model", model);
	model = glm::scale(model, glm::vec3(0.2, 0.25, 0.3));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(0.58824f, 0.0f, 0.80392f));
	glDrawArrays(GL_QUADS, 0, 24);
	//Meñique medio izquierdo
	model = modelTemp;
	model = glm::translate(model, glm::vec3(-0.1, 0, 0));
	model = glm::rotate(model, glm::radians(-angMeIzq*0.5f), glm::vec3(0, 1, 0));
	model = glm::translate(model, glm::vec3(-0.1, 0, 0));
	modelTemp = model;
	projectionShader.setMat4("model", model);
	model = glm::scale(model, glm::vec3(0.2, 0.25, 0.3));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(0.72549f, 0.29804f, 0.88235f));
	glDrawArrays(GL_QUADS, 0, 24);
	//Meñique Superior izquierdo
	model = modelTemp;
	model = glm::translate(model, glm::vec3(-0.1, 0, 0));
	model = glm::rotate(model, glm::radians(-angMeIzq* 0.9f), glm::vec3(0, 1, 0));
	model = glm::translate(model, glm::vec3(-0.1, 0, 0));
	modelTemp = model;
	projectionShader.setMat4("model", model);
	model = glm::scale(model, glm::vec3(0.2, 0.25, 0.3));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(0.913f, 0.627f, 0.972f));
	glDrawArrays(GL_QUADS, 0, 24);
		   	 
	//Hombro derecho
	model = glm::translate(model = glm::mat4(1.0f), glm::vec3(2.5, 2.0, 0));
	modelTemp = model;
	model = glm::rotate(model, glm::radians(angHomDer), glm::vec3(0, 0, 1));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(1, 1, 0));
	glDrawArrays(GL_QUADS, 0, 24);
	//Bicep derecho
	model = glm::translate(model, glm::vec3(1.5, 0, 0));
	modelTemp = model;
	model = glm::scale(model, glm::vec3(2, 1, 0.7));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(0.0f, 0.0f, 1.0f));
	glDrawArrays(GL_QUADS, 0, 24);
	model = modelTemp;
	//Antebrazo derecho
	model = glm::translate(model, glm::vec3(1, 0, 0));
	model = glm::rotate(model, glm::radians(angAntDer), glm::vec3(0, 1, 0));
	model = glm::translate(model, glm::vec3(1.5, 0, 0));
	modelTemp = model;
	projectionShader.setMat4("model", model);
	model = glm::scale(model, glm::vec3(3, 1, 0.7));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(1.0f, 0.0f, 0.0f));
	glDrawArrays(GL_QUADS, 0, 24);
	model = modelTemp;
	//Mano derecha
	model = glm::translate(model, glm::vec3(1.5, 0, 0));
	model = glm::rotate(model, glm::radians(angManoDer), glm::vec3(0, 1, 0));
	model = glm::translate(model, glm::vec3(0.5, 0, 0));
	modelTemp = model;
	modelTemp2 = model;
	projectionShader.setMat4("model", model);
	model = glm::scale(model, glm::vec3(1, 1, 0.3));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(0.0f, 1.0f, 0.0f));
	glDrawArrays(GL_QUADS, 0, 24);
	//Pulgar Inferior derecho
	model = glm::translate(model, glm::vec3(-0.35, 0.5, 0));
	model = glm::rotate(model, glm::radians(angPuDer), glm::vec3(1, 0, 0));
	model = glm::translate(model, glm::vec3(0, 0.15, 0));
	modelTemp = model;
	projectionShader.setMat4("model", model);
	model = glm::scale(model, glm::vec3(0.3, 0.3, 0.3));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(0.5f, 0.0f, 0.5f));
	glDrawArrays(GL_QUADS, 0, 24);
	model = modelTemp;
	//Pulgar Superior derecho
	model = glm::translate(model, glm::vec3(0, 0.15, 0));
	model = glm::rotate(model, glm::radians(angPuDer*0.7f), glm::vec3(1, 0, 0));
	model = glm::translate(model, glm::vec3(0, 0.15, 0));
	modelTemp = model;
	projectionShader.setMat4("model", model);
	model = glm::scale(model, glm::vec3(0.3, 0.3, 0.3));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(1.0f, 0.0f, 0.5f));
	glDrawArrays(GL_QUADS, 0, 24);
	//Indice inferior derecho
	model = modelTemp2;
	model = glm::translate(model, glm::vec3(0.5, 0.38, 0));
	modelTemp2 = model;//contiene inicio de falange
	model = glm::rotate(model, glm::radians(angInDer), glm::vec3(0, 1, 0));
	model = glm::translate(model, glm::vec3(0.15, 0, 0));
	modelTemp = model;
	projectionShader.setMat4("model", model);
	model = glm::scale(model, glm::vec3(0.3, 0.25, 0.3));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(0.168f, 0.564f, 0.933f));
	glDrawArrays(GL_QUADS, 0, 24);
	//Indice medio derecho
	model = modelTemp;
	model = glm::translate(model, glm::vec3(0.15, 0, 0));
	model = glm::rotate(model, glm::radians(angInDer*0.5f), glm::vec3(0, 1, 0));
	model = glm::translate(model, glm::vec3(0.15, 0, 0));
	modelTemp = model;
	projectionShader.setMat4("model", model);
	model = glm::scale(model, glm::vec3(0.3, 0.25, 0.3));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(0.117f, 0.835f, 0.921f));
	glDrawArrays(GL_QUADS, 0, 24);
	//Indice Superior derecho
	model = modelTemp;
	model = glm::translate(model, glm::vec3(0.15, 0, 0));
	model = glm::rotate(model, glm::radians(angInDer* 0.9f), glm::vec3(0, 1, 0));
	model = glm::translate(model, glm::vec3(0.15, 0, 0));
	modelTemp = model;
	projectionShader.setMat4("model", model);
	model = glm::scale(model, glm::vec3(0.3, 0.25, 0.3));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(0.094f, 0.968f, 0.843f));
	glDrawArrays(GL_QUADS, 0, 24);
	//Medio inferior derecho
	model = modelTemp2;
	model = glm::translate(model, glm::vec3(0, -0.25, 0));
	model = glm::rotate(model, glm::radians(angMedDer), glm::vec3(0, 1, 0));
	model = glm::translate(model, glm::vec3(0.2, 0, 0));
	modelTemp = model;
	projectionShader.setMat4("model", model);
	model = glm::scale(model, glm::vec3(0.4, 0.25, 0.3));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(0.968f, 0.2f, 0.094f));
	glDrawArrays(GL_QUADS, 0, 24);
	//Medio medio derecho
	model = modelTemp;
	model = glm::translate(model, glm::vec3(0.2, 0, 0));
	model = glm::rotate(model, glm::radians(angMedDer*0.5f), glm::vec3(0, 1, 0));
	model = glm::translate(model, glm::vec3(0.2, 0, 0));
	modelTemp = model;
	projectionShader.setMat4("model", model);
	model = glm::scale(model, glm::vec3(0.4, 0.25, 0.3));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(0.968f, 0.407f, 0.094f));
	glDrawArrays(GL_QUADS, 0, 24);
	//Medio Superior derecho
	model = modelTemp;
	model = glm::translate(model, glm::vec3(0.2, 0, 0));
	model = glm::rotate(model, glm::radians(angMedDer* 0.9f), glm::vec3(0, 1, 0));
	model = glm::translate(model, glm::vec3(0.2, 0, 0));
	modelTemp = model;
	projectionShader.setMat4("model", model);
	model = glm::scale(model, glm::vec3(0.4, 0.25, 0.3));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(0.968f, 0.580f, 0.094f));
	glDrawArrays(GL_QUADS, 0, 24);
	//Anular inferior derecho
	model = modelTemp2;
	model = glm::translate(model, glm::vec3(0, -0.5, 0));
	model = glm::rotate(model, glm::radians(angAnDer), glm::vec3(0, 1, 0));
	model = glm::translate(model, glm::vec3(0.15, 0, 0));
	modelTemp = model;
	projectionShader.setMat4("model", model);
	model = glm::scale(model, glm::vec3(0.3, 0.25, 0.3));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(1.0f, 0.8f, 0.1f));
	glDrawArrays(GL_QUADS, 0, 24);
	//Anular medio derecho
	model = modelTemp;
	model = glm::translate(model, glm::vec3(0.15, 0, 0));
	model = glm::rotate(model, glm::radians(angAnDer*0.5f), glm::vec3(0, 1, 0));
	model = glm::translate(model, glm::vec3(0.15, 0, 0));
	modelTemp = model;
	projectionShader.setMat4("model", model);
	model = glm::scale(model, glm::vec3(0.3, 0.25, 0.3));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(1.0f, 1.0f, 0.0f));
	glDrawArrays(GL_QUADS, 0, 24);
	//Anular Superior derecho
	model = modelTemp;
	model = glm::translate(model, glm::vec3(0.15, 0, 0));
	model = glm::rotate(model, glm::radians(angAnDer* 0.9f), glm::vec3(0, 1, 0));
	model = glm::translate(model, glm::vec3(0.15, 0, 0));
	modelTemp = model;
	projectionShader.setMat4("model", model);
	model = glm::scale(model, glm::vec3(0.3, 0.25, 0.3));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(0.980f, 0.984f, 0.615f));
	glDrawArrays(GL_QUADS, 0, 24);
	//Meñique inferior derecho
	model = modelTemp2;
	model = glm::translate(model, glm::vec3(0, -0.75, 0));
	model = glm::rotate(model, glm::radians(angMeDer), glm::vec3(0, 1, 0));
	model = glm::translate(model, glm::vec3(0.1, 0, 0));
	modelTemp = model;
	projectionShader.setMat4("model", model);
	model = glm::scale(model, glm::vec3(0.2, 0.25, 0.3));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(0.58824f, 0.0f, 0.80392f));
	glDrawArrays(GL_QUADS, 0, 24);
	//Meñique medio derecho
	model = modelTemp;
	model = glm::translate(model, glm::vec3(0.1, 0, 0));
	model = glm::rotate(model, glm::radians(angMeDer*0.5f), glm::vec3(0, 1, 0));
	model = glm::translate(model, glm::vec3(0.1, 0, 0));
	modelTemp = model;
	projectionShader.setMat4("model", model);
	model = glm::scale(model, glm::vec3(0.2, 0.25, 0.3));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(0.72549f, 0.29804f, 0.88235f));
	glDrawArrays(GL_QUADS, 0, 24);
	//Meñique Superior derecho
	model = modelTemp;
	model = glm::translate(model, glm::vec3(0.1, 0, 0));
	model = glm::rotate(model, glm::radians(angMeDer* 0.9f), glm::vec3(0, 1, 0));
	model = glm::translate(model, glm::vec3(0.1, 0, 0));
	modelTemp = model;
	projectionShader.setMat4("model", model);
	model = glm::scale(model, glm::vec3(0.2, 0.25, 0.3));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("aColor", glm::vec3(0.913f, 0.627f, 0.972f));
	glDrawArrays(GL_QUADS, 0, 24);
	//Cuello
	model = glm::translate(model = glm::mat4(1.0f), glm::vec3(0, 2.75, 0));
	model = glm::scale(model, glm::vec3(0.5, 0.5, 1));
	projectionShader.setVec3("aColor", glm::vec3(1.0f, 0.2f, 0.7f));
	projectionShader.setMat4("model", model);
	glDrawArrays(GL_QUADS, 0, 24);
	//Cabeza
	model = glm::translate(model = glm::mat4(1.0f), glm::vec3(0, 4.25, 0));//cabeza
	model = glm::scale(model, glm::vec3(1.5, 2.5, 1));
	projectionShader.setVec3("aColor", glm::vec3(1.0f, 0.0f, 0.0f));
	projectionShader.setMat4("model", model);
	glDrawArrays(GL_QUADS, 0, 24);

	glBindVertexArray(0);
}

int main()
{
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    /*glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);*/

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // uncomment this statement to fix compilation on OS X
#endif

    // glfw window creation
    // --------------------
	monitors = glfwGetPrimaryMonitor();
	getResolution();

    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Practica 4", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
	glfwSetWindowPos(window, 0, 30);
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, resize);

	glewInit();


	//Mis funciones
	//Datos a utilizar
	myData();
	glEnable(GL_DEPTH_TEST);

    // render loop
    // While the windows is not closed
    while (!glfwWindowShouldClose(window))
    {
        // input
        // -----
        my_input(window);

        // render
        // Backgound color
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//Mi función de dibujo
		display();

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void my_input(GLFWwindow *window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)  //GLFW_RELEASE
        glfwSetWindowShouldClose(window, true);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		movX += 0.08f;
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		movX -= 0.08f;
	if (glfwGetKey(window, GLFW_KEY_PAGE_UP) == GLFW_PRESS)
		movY += 0.08f;
	if (glfwGetKey(window, GLFW_KEY_PAGE_DOWN) == GLFW_PRESS)
		movY -= 0.08f;
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		movZ -= 0.08f;
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		movZ += 0.08f;
	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
		angX -= 1.2f;
	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
		angX += 1.2f;
	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
		angY -= 1.2f;
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
		angY += 1.2f;
	if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS) {
		if (glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT) == GLFW_PRESS) {
			if (angHomIzq < 90)
				angHomIzq += 0.8f;
		}
		else {
			if (angHomIzq > -90)
				angHomIzq -= 0.8f;
		}
	}
	if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS) {
		if (glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT) == GLFW_PRESS) {
			if (angAntIzq < 0)
				angAntIzq += 0.8f;
		}
		else {
			if (angAntIzq > -140)
				angAntIzq -= 0.8f;
		}
	}
	if (glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS) {
		if (glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT) == GLFW_PRESS) {
			if (angManoIzq < 20)
				angManoIzq += 0.8f;
		}
		else {
			if (angManoIzq > -40)
				angManoIzq -= 0.8f;
		}
	}
	if (glfwGetKey(window, GLFW_KEY_V) == GLFW_PRESS) {
		if (glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT) == GLFW_PRESS) {
			if (angPuIzq > 0)
				angPuIzq -= 0.8f;
		}
		else {
			if (angPuIzq < 80)
				angPuIzq += 0.8f;
		}
	}
	if (glfwGetKey(window, GLFW_KEY_B) == GLFW_PRESS) {
		if (glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT) == GLFW_PRESS) {
			if (angInIzq < 0)
				angInIzq += 0.8f;
		}
		else {
			if (angInIzq > -80)
				angInIzq -= 0.8f;
		}
	}
	if (glfwGetKey(window, GLFW_KEY_N) == GLFW_PRESS) {
		if (glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT) == GLFW_PRESS) {
			if (angMedIzq < 0)
				angMedIzq += 0.8f;
		}
		else {
			if (angMedIzq > -80)
				angMedIzq -= 0.8f;
		}
	}
	if (glfwGetKey(window, GLFW_KEY_M) == GLFW_PRESS) {
		if (glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT) == GLFW_PRESS) {
			if (angAnIzq < 0)
				angAnIzq += 0.8f;
		}
		else {
			if (angAnIzq > -80)
				angAnIzq -= 0.8f;
		}
	}
	if (glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS) {
		if (glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT) == GLFW_PRESS) {
			if (angMeIzq < 0)
				angMeIzq += 0.8f;
		}
		else {
			if (angMeIzq > -80)
				angMeIzq -= 0.8f;
		}
	}
	if (glfwGetKey(window, GLFW_KEY_T) == GLFW_PRESS) {
		if (glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT) == GLFW_PRESS) {
			if (angHomDer < 90)
				angHomDer += 0.8f;
		}
		else {
			if (angHomDer > -90)
				angHomDer -= 0.8f;
		}
	}
	if (glfwGetKey(window, GLFW_KEY_Y) == GLFW_PRESS) {
		if (glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT) == GLFW_PRESS) {
			if (angAntDer < 0)
				angAntDer += 0.8f;
		}
		else {
			if (angAntDer > -140)
				angAntDer -= 0.8f;
		}
	}
	if (glfwGetKey(window, GLFW_KEY_U) == GLFW_PRESS) {
		if (glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT) == GLFW_PRESS) {
			if (angManoDer < 20)
				angManoDer += 0.8f;
		}
		else {
			if (angManoDer > -40)
				angManoDer -= 0.8f;
		}
	}
	if (glfwGetKey(window, GLFW_KEY_I) == GLFW_PRESS) {
		if (glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT) == GLFW_PRESS) {
			if (angPuDer > 0)
				angPuDer -= 0.8f;
		}
		else {
			if (angPuDer < 80)
				angPuDer += 0.8f;
		}
	}
	if (glfwGetKey(window, GLFW_KEY_O) == GLFW_PRESS) {
		if (glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT) == GLFW_PRESS) {
			if (angInDer < 0)
				angInDer += 0.8f;
		}
		else {
			if (angInDer > -80)
				angInDer -= 0.8f;
		}
	}
	if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS) {
		if (glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT) == GLFW_PRESS) {
			if (angMedDer < 0)
				angMedDer += 0.8f;
		}
		else {
			if (angMedDer > -80)
				angMedDer -= 0.8f;
		}
	}
	if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS) {
		if (glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT) == GLFW_PRESS) {
			if (angAnDer < 0)
				angAnDer += 0.8f;
		}
		else {
			if (angAnDer > -80)
				angAnDer -= 0.8f;
		}
	}
	if (glfwGetKey(window, GLFW_KEY_K) == GLFW_PRESS) {
		if (glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT) == GLFW_PRESS) {
			if (angMeDer < 0)
				angMeDer += 0.8f;
		}
		else {
			if (angMeDer > -80)
				angMeDer -= 0.8f;
		}
	}
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void resize(GLFWwindow* window, int width, int height)
{
    // Set the Viewport to the size of the created window
    glViewport(0, 0, width, height);
}