/*---------------------------------------------------------*/
/* ----------------   Práctica 9 --------------------------*/
/*-----------------    2019-2   ---------------------------*/
/*------------- Alumno: Díaz Gutiérrez Elvira Angela Belem ---------------*/
/*---------------------------- Visual Studio Versión 2017 --------------------------*/
/*----------------------------------------------------------------------------------*/
/*---------------------------------- Instructivo: ----------------------------------*/
/*
Con las siguientes teclas se puede mover toda la biblioteca:
	D: Mueve el modelo a la izquierda
	A: Mueve el modelo a la derecha
	W: Acerca el modelo
	S: Aleja el modelo
	Flecha abajo: Lo rota hacia enfrente
	Flecha arriba: Lo rota hacia atras
	Flecha derecha: Lo rota hacia la derecha
	Flecha izquierda:Lo rota hacia la izquierda
	AvPág: Lo mueve hacia abajo
	RePág: Lo mueve hacia arriba

	Además la cámara desde la cual se observa se puede mover con el Mouse,al mover el mouse hacia:
		la derecha, la cámara gira a la derecha
		la izquierda, la cámara gira a la izquierda
		arriba, la cámara gira hacia arriba
		abajo, la cámara gira hacia abajo

Con las siguientes teclas se modifica la intensidad de la luz:
	O: Disminuye la instensidad
	I: Aumenta la instensidad

Con las siguientes teclas se modifica el color de la luz:
	R: La luz se vuelve Roja
	T: La luz se vuelve Azul
	Y: La luz se vuelve Verde
	U: La luz se vuelve Amarillo
	F: La luz se vuelve Rosa
	G: La luz se vuelve Naranja
	H: La luz se vuelve Morado
	J: La luz se vuelve Negra
	K: La luz se vuelve Blanca

Con las siguientes teclas se cambia el tipo de iluminación
	V:	Directional
	B:	Positional
	N:	Spotlight
*/

#define STB_IMAGE_IMPLEMENTATION
#include "esfera.h"
#include "camera.h"
#include "stb_image.h"
#include <string.h>
using namespace std;

Esfera my_sphere(1.0f);

void resize(GLFWwindow* window, int width, int height);
void my_input(GLFWwindow *window);
void mouse_callback(GLFWwindow *window, double xpos, double ypos);
void scroll_callback(GLFWwindow *window, double xoffset, double yoffset);

// settings
// Window size
int SCR_WIDTH = 3800;
int SCR_HEIGHT = 7600;

GLFWmonitor *monitors;
GLuint VBO, VAO, EBO;

//Camera
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
double	lastX = 0.0f,
lastY = 0.0f;
bool firstMouse = true;

//Timing
double	deltaTime = 0.0f,
lastFrame = 0.0f;

//Lighting                                    //Reflector
glm::vec3 lightPosition(0.0f, 3.0f, 0.0f);    //Posición de la Luz
glm::vec3 lightDirection(0.0f, 0.0f, -3.0f);  //Dirección de la Luz

void myData(void);
void display(void);
void getResolution(void);
void animate(void);
void LoadTextures(void);
unsigned int generateTextures(char*, bool);

//For Keyboard
float	movX = 0.0f,
movY = 0.0f,
movZ = -5.0f,
rotX = 0.0f,
rotY = 0.0f;

// Para controlar el color de la luz

glm::vec3 Rojo = glm::vec3(1.0f, 0.0f, 0.0f);
glm::vec3 Azul = glm::vec3(0.0f, 0.0f, 1.0f);
glm::vec3 Verde = glm::vec3(0.0f, 1.0f, 0.0f);
glm::vec3 Amarillo = glm::vec3(1.0f, 1.0f, 0.0f);
glm::vec3 Rosa = glm::vec3(1.0f, 0.5f, 0.7f);
glm::vec3 Naranja = glm::vec3(1.0f, 0.7f, 0.3f);
glm::vec3 Morado = glm::vec3(0.9f, 0.5f, 1.0f);
glm::vec3 Negra = glm::vec3(0.0f, 0.0f, 0.0f);
glm::vec3 Blanca = glm::vec3(1.0f, 1.0f, 1.0f);
glm::vec3 ColorLuz = Blanca;

//R red	T blue Y verde U Amarillo I pink F orange G morado H negra J Blanco


char Light_VertxShader[100] = "shaders/shader_texture_light_dir.vs";
char Light_FragShader[100] = "shaders/shader_texture_light_dir.fs";

glm::vec3 Light_Position = camera.Position;
glm::vec3 Light_Direction = camera.Front;
float Light_CutOff = glm::cos(glm::radians(13.0f));


//-------- Texturas --------

//Difusas
unsigned int t_Frente,
			 t_Frente_Specular,
			 t_Derecha,
		     t_Derecha_Specular,
			 t_Izquierda,
			 t_Izquierda_Specular,
			 t_Atras,
			 t_Atras_Specular,
			 t_cubito_Frente,
			 t_cubito_Frente_Specular,
			 t_cubito_Derecha,
			 t_cubito_Derecha_Specular,
			 t_cubito_Izquierda,
		  	 t_cubito_Izquierda_Specular,
			 t_cubito_Atras,
			 t_cubito_Atras_Specular,
			 t_negro;

// ------- Propiedades de la Luz --------
float opaco = 32.0f;
int Spotlight_ON = 0;  

unsigned int generateTextures(const char* filename, bool alfa)
{
	unsigned int textureID;
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);
	// set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// load image, create texture and generate mipmaps
	int width, height, nrChannels;
	stbi_set_flip_vertically_on_load(true); // tell stb_image.h to flip loaded texture's on the y-axis.

	unsigned char *data = stbi_load(filename, &width, &height, &nrChannels, 0);
	if (data)
	{
		if (alfa)
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		else
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
		return textureID;
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
		return 100;
	}

	stbi_image_free(data);
}

void getResolution()
{
	const GLFWvidmode * mode = glfwGetVideoMode(glfwGetPrimaryMonitor());

	SCR_WIDTH = mode->width;
	SCR_HEIGHT = (mode->height) - 80;

	lastX = SCR_WIDTH / 2.0f;
	lastY = SCR_HEIGHT / 2.0f;

}


void LoadTextures()
{
	t_Frente = generateTextures("Texturas/MuroEnfrente.png", 1);
	t_Frente_Specular = generateTextures("Texturas/MuroEnfrente_Especular.png", 1);
	t_Derecha = generateTextures("Texturas/MuroDerecha.png", 1);
	t_Derecha_Specular = generateTextures("Texturas/MuroDerecha_Especular.png", 1);
	t_Izquierda = generateTextures("Texturas/MuroIzquierda.png", 1);
	t_Izquierda_Specular = generateTextures("Texturas/MuroIzquierda_Especular.png", 1);
	t_Atras = generateTextures("Texturas/MuroAtras.png", 1);
	t_Atras_Specular = generateTextures("Texturas/MuroAtras_Especular.png", 1);

	t_cubito_Frente = generateTextures("Texturas/CubitoFrente.png", 1);
	t_cubito_Frente_Specular = generateTextures("Texturas/CubitoFrente_Especular", 1);
	t_cubito_Derecha = generateTextures("Texturas/CubitoLateralDerecho.png", 1);
	t_cubito_Derecha_Specular = generateTextures("Texturas/CubitoLateralDerecho_Especular.png", 1);
	t_cubito_Izquierda = generateTextures("Texturas/CubitoLateralIzquierdo.png", 1);
	t_cubito_Izquierda_Specular = generateTextures("Texturas/CubitoLateralIzquierdo_Especular.png", 1);
	t_cubito_Atras = generateTextures("Texturas/CubitoAtras.png", 1);
	t_cubito_Atras_Specular = generateTextures("Texturas/CubitoAtras_Especular.png", 1);
	t_negro = generateTextures("Texturas/gris.jpg", 0);

	// bind textures on corresponding texture units
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, 0);

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, t_Frente);
	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, t_Frente_Specular);
	glActiveTexture(GL_TEXTURE3);
	glBindTexture(GL_TEXTURE_2D, t_Derecha);
	glActiveTexture(GL_TEXTURE4);
	glBindTexture(GL_TEXTURE_2D, t_Derecha_Specular);
	glActiveTexture(GL_TEXTURE5);
	glBindTexture(GL_TEXTURE_2D, t_Izquierda);
	glActiveTexture(GL_TEXTURE6);
	glBindTexture(GL_TEXTURE_2D, t_Izquierda_Specular);
	glActiveTexture(GL_TEXTURE7);
	glBindTexture(GL_TEXTURE_2D, t_Atras);	
	glActiveTexture(GL_TEXTURE8);
	glBindTexture(GL_TEXTURE_2D, t_Atras_Specular);

	glActiveTexture(GL_TEXTURE9);
	glBindTexture(GL_TEXTURE_2D, t_cubito_Frente);
	glActiveTexture(GL_TEXTURE10);
	glBindTexture(GL_TEXTURE_2D, t_cubito_Frente_Specular);
	glActiveTexture(GL_TEXTURE11);
	glBindTexture(GL_TEXTURE_2D, t_cubito_Derecha);
	glActiveTexture(GL_TEXTURE12);
	glBindTexture(GL_TEXTURE_2D, t_cubito_Derecha_Specular);
	glActiveTexture(GL_TEXTURE13);
	glBindTexture(GL_TEXTURE_2D, t_cubito_Izquierda);
	glActiveTexture(GL_TEXTURE14);
	glBindTexture(GL_TEXTURE_2D, t_cubito_Izquierda_Specular);
	glActiveTexture(GL_TEXTURE15);
	glBindTexture(GL_TEXTURE_2D, t_cubito_Atras);
	glActiveTexture(GL_TEXTURE16);
	glBindTexture(GL_TEXTURE_2D, t_cubito_Atras_Specular);
	glActiveTexture(GL_TEXTURE17);
	glBindTexture(GL_TEXTURE_2D, t_negro);


}

void myData()
{
	float vertices[] = {

		// positions          // normals           // texture coords
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,
		 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  0.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  1.0f,

		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,
		 0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  1.0f,

		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
		-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
		-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  0.0f,

		 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
		 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
		 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  1.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  0.0f,

		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  1.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  0.0f,

	
		//Segunda caja
		//Cara de enfrente
		 0.5f,  0.5f, 0.5f,    0.0f, 0.0f, 1.0f,    1.0f, 1.0f,    // top right
		 0.5f, -0.5f, 0.5f,    0.0f, 0.0f, 1.0f,    1.0f, 0.0f,    // bottom right
		-0.5f, -0.5f, 0.5f,    0.0f, 0.0f, 1.0f,    0.0f, 0.0f,    // bottom left
		-0.5f,  0.5f, 0.5f,    0.0f, 0.0f, 1.0f,    0.0f, 1.0f,    // top left 

		//Cara de atrás
		-0.5f,  0.5f, -0.5f,   0.0f, 0.0f, -1.0f,   1.0f, 1.0f,    // top right
		-0.5f, -0.5f, -0.5f,   0.0f, 0.0f, -1.0f,   1.0f, 0.0f,    // bottom right
		 0.5f, -0.5f, -0.5f,   0.0f, 0.0f, -1.0f,   0.0f, 0.0f,    // bottom left
		 0.5f,  0.5f, -0.5f,   0.0f, 0.0f, -1.0f,   0.0f, 1.0f,    // top left 

		//Cara de arriba
		 0.5f,  0.5f, -0.5f,   0.0f,  1.0f, 0.0f,   1.0f, 1.0f,    // top right
		 0.5f,  0.5f,  0.5f,   0.0f,  1.0f, 0.0f,   1.0f, 0.0f,    // bottom right
		-0.5f,  0.5f,  0.5f,   0.0f,  1.0f, 0.0f,   0.0f, 0.0f,    // bottom left
		-0.5f,  0.5f, -0.5f,   0.0f,  1.0f, 0.0f,   0.0f, 1.0f,    // top left 

		//Cara de abajo
		 0.5f, -0.5f,  0.5f,   0.0f, -1.0f, 0.0f,   1.0f, 1.0f,    // top right
		 0.5f, -0.5f, -0.5f,   0.0f, -1.0f, 0.0f,   1.0f, 0.0f,    // bottom right
		-0.5f, -0.5f, -0.5f,   0.0f, -1.0f, 0.0f,   0.0f, 0.0f,    // bottom left
		-0.5f, -0.5f,  0.5f,   0.0f, -1.0f, 0.0f,   0.0f, 1.0f,    // top left 

		//Cara de la derecha
		 0.5f,  0.5f, -0.5f,   1.0f, 0.0f, 0.0f,    1.0f, 1.0f,    // top right
		 0.5f, -0.5f, -0.5f,   1.0f, 0.0f, 0.0f,    1.0f, 0.0f,    // bottom right
		 0.5f, -0.5f,  0.5f,   1.0f, 0.0f, 0.0f,    0.0f, 0.0f,    // bottom left
		 0.5f,  0.5f,  0.5f,   1.0f, 0.0f, 0.0f,    0.0f, 1.0f,    // top left 

		 //Cara de la izquierda
		-0.5f,  0.5f,  0.5f,  -1.0f, 0.0f, 0.0f,    1.0f, 1.0f,    // top right
		-0.5f, -0.5f,  0.5f,  -1.0f, 0.0f, 0.0f,    1.0f, 0.0f,    // bottom right
		-0.5f, -0.5f, -0.5f,  -1.0f, 0.0f, 0.0f,    0.0f, 0.0f,    // bottom left
		-0.5f,  0.5f, -0.5f,  -1.0f, 0.0f, 0.0f,    0.0f, 1.0f,    // top left 
	};

	unsigned int indices[] = {
		0, 1, 3, // first triangle
		1, 2, 3  // second triangle
	};

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// normal attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	// texture coord attribute
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

}

void animate(void)
{
}

void display(void)
{
	//Shader projectionShader("shaders/shader_light.vs", "shaders/shader_light.fs");
	//Shader projectionShader("shaders/shader_texture_color.vs", "shaders/shader_texture_color.fs");

	// ------ Aquí se selecciona el tipo de luz a utilizar, descomentar la línea que se va a ocupar -----

	//Shader lightingShader("shaders/shader_texture_light_dir.vs", "shaders/shader_texture_light_dir.fs");    //Directional
	//Shader lightingShader("shaders/shader_texture_light_pos.vs", "shaders/shader_texture_light_pos.fs");    //Positional
	//Shader lightingShader("shaders/shader_texture_light_spot.vs", "shaders/shader_texture_light_spot.fs");  //Spotlight

	Shader lightingShader(Light_VertxShader, Light_FragShader);
	Shader lampShader("shaders/shader_lamp.vs", "shaders/shader_lamp.fs");

	//To Use Lighting
	lightingShader.use();


	lightingShader.setVec3("light.position", Light_Position);
	lightingShader.setVec3("light.direction", Light_Direction);
	lightingShader.setFloat("light.cutOff", Light_CutOff);

	lightingShader.setVec3("viewPos", camera.Position);

	// Propiedades de la luz 
	lightingShader.setVec3("light.ambient", 0.2f, 0.2f, 0.2f);
	lightingShader.setVec3("light.diffuse", ColorLuz);
	lightingShader.setVec3("light.specular", ColorLuz);

	//Para la Luz Posicional y de Reflector
	lightingShader.setFloat("light.constant", 1.0f);
	lightingShader.setFloat("light.linear", 0.09f);
	lightingShader.setFloat("light.quadratic", 0.032f);

	// Brillo del material
	lightingShader.setFloat("material_shininess", opaco);

	//Matriz de modelo, vista t proyección
	glm::mat4 temp = glm::mat4(1.0f); 
	glm::mat4 model = glm::mat4(1.0f);		//Initialize Matrix, Use this matrix for individual models
	glm::mat4 view = glm::mat4(1.0f);		//Use this matrix for ALL models
	glm::mat4 projection = glm::mat4(1.0f);	//This matrix is for Projection

	//Use "projection" to include Camera
	projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
	view = camera.GetViewMatrix();
	view = glm::translate(view, glm::vec3(movX, movY, movZ));
	view = glm::rotate(view, glm::radians(rotX), glm::vec3(1.0f, 0.0f, 0.0f));
	view = glm::rotate(view, glm::radians(rotY), glm::vec3(0.0f, 1.0f, 0.0f));

	// pass them to the shaders
	//lightingShader.setVec3("viewPos", camera.Position);
	lightingShader.setMat4("model", model);
	lightingShader.setMat4("view", view);
	// note: currently we set the projection matrix each frame, but since the projection matrix rarely changes it's often best practice to set it outside the main loop only once.
	lightingShader.setMat4("projection", projection);

	// Si el tipo de luz es Spotlight
	if (Spotlight_ON == 1)
	{
		Light_Position = camera.Position;
		Light_Direction = camera.Front;
		Light_CutOff = glm::cos(glm::radians(13.0f));
	}

	// ------------------------- Zona de Dibujo -------------------------

	glBindVertexArray(VAO);

	// ------------ Muros  ------------

	// Cara de enfrente
	model = glm::translate(model = glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	model = glm::scale(model, glm::vec3(3.2f, 2.0f, 1.0f));
	lightingShader.setMat4("model", model);
	lightingShader.setInt("material_diffuse", t_Frente);
	lightingShader.setInt("material_specular", t_Frente_Specular);
	glDrawArrays(GL_QUADS, 24, 4);

	// Cara de atrás
	model = glm::translate(model = glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	model = glm::scale(model, glm::vec3(3.2f, 2.0f, 1.0f));
	lightingShader.setMat4("model", model);
	lightingShader.setInt("material_diffuse", t_Atras);
	lightingShader.setInt("material_specular", t_Atras_Specular);
	glDrawArrays(GL_QUADS, 28, 4);

	// Cara de arriba
	model = glm::translate(model = glm::mat4(1.0f), glm::vec3(0.0f, 0.375f, 0.0f));
	model = glm::scale(model, glm::vec3(3.2f, 1.25f, 1.0f));
	lightingShader.setMat4("model", model);
	lightingShader.setInt("material_diffuse", t_negro);
	lightingShader.setInt("material_specular", t_negro);
	glDrawArrays(GL_QUADS, 32, 4);

	// Cara de abajo
	model = glm::translate(model = glm::mat4(1.0f), glm::vec3(0.0f, -0.375f, 0.0f));
	model = glm::scale(model, glm::vec3(3.2f, 1.25f, 1.0f));
	lightingShader.setMat4("model", model);
	lightingShader.setInt("material_diffuse", t_negro);
	lightingShader.setInt("material_specular", t_negro);
	glDrawArrays(GL_QUADS, 36, 4);

	// Cara de la derecha
	model = glm::translate(model = glm::mat4(1.0f), glm::vec3(0.975f, 0.0f, 0.0f));
	model = glm::scale(model, glm::vec3(1.25f, 2.0f, 1.0f));
	lightingShader.setMat4("model", model);
	lightingShader.setInt("material_diffuse", t_Derecha);
	lightingShader.setInt("material_specular", t_Derecha_Specular);
	glDrawArrays(GL_QUADS, 40, 4);

	// Cara de la izquierda
	model = glm::translate(model = glm::mat4(1.0f), glm::vec3(-0.975f, 0.0f, 0.0f));
	model = glm::scale(model, glm::vec3(1.25f, 2.0f, 1.0f));
	lightingShader.setMat4("model", model);
	lightingShader.setInt("material_diffuse", t_Izquierda);
	lightingShader.setInt("material_specular", t_Izquierda_Specular);
	glDrawArrays(GL_QUADS, 44, 4);

	// Cubito superior

	// Cara de enfrente
	model = glm::translate(model = glm::mat4(1.0f), glm::vec3(0.0f, 1.17f, 0.0f));
	temp = model;
	model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
	model = glm::scale(model, glm::vec3(1.02f, 0.34f, 1.0f));
	lightingShader.setMat4("model", model);
	lightingShader.setInt("material_diffuse", t_cubito_Frente);
	lightingShader.setInt("material_specular", t_cubito_Frente_Specular);
	glDrawArrays(GL_QUADS, 24, 4);
	
	// Cara de atrás
	model = temp;
	model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.66f));
	model = glm::scale(model, glm::vec3(1.02f, 0.34f, 1.0f));
	lightingShader.setMat4("model", model);
	lightingShader.setInt("material_diffuse", t_cubito_Atras);
	lightingShader.setInt("material_specular", t_cubito_Atras_Specular);
	glDrawArrays(GL_QUADS, 28, 4);
	
	// Cara de arriba
	model = temp;
	model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.33f));
	model = glm::scale(model, glm::vec3(1.02f, 0.34f, 0.34f));
	lightingShader.setMat4("model", model);
	lightingShader.setInt("material_diffuse", t_negro);
	lightingShader.setInt("material_specular", t_negro);
	glDrawArrays(GL_QUADS, 32, 4);
	
	// Cara de la derecha
	model = temp;
	model = glm::translate(model, glm::vec3(0.34f, 0.0f, 0.33));
	model = glm::scale(model, glm::vec3(0.34f, 0.34f, 0.34f));
	lightingShader.setMat4("model", model);
	lightingShader.setInt("material_diffuse", t_cubito_Derecha);
	lightingShader.setInt("material_specular", t_cubito_Derecha_Specular);
	glDrawArrays(GL_QUADS, 40, 4);

	// Cara de la izquierda
	model = temp;
	model = glm::translate(model, glm::vec3(-0.34f, 0.0f, 0.33));
	model = glm::scale(model, glm::vec3(0.34f, 0.34f, 0.34f));
	lightingShader.setMat4("model", model);
	lightingShader.setInt("material_diffuse", t_cubito_Izquierda);
	lightingShader.setInt("material_specular", t_cubito_Izquierda_Specular);
	glDrawArrays(GL_QUADS, 44, 4);


	
	// ------------- Luz ---------------
	lampShader.use();
	lampShader.setMat4("projection", projection);
	lampShader.setMat4("view", view);
	model = glm::mat4(1.0f);
	model = glm::translate(model, lightPosition);
	model = glm::scale(model, glm::vec3(0.25f));
	lampShader.setMat4("model", model);

	//glBindVertexArray(lightVAO);
	glDrawArrays(GL_QUADS, 0, 24);	//Light

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

	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Practica 9", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwSetWindowPos(window, 0, 30);
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, resize);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);

	//To Enable capture of our mouse
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

	glewInit();


	//Mis funciones
	//Datos a utilizar
	LoadTextures();
	myData();
	my_sphere.init();
	glEnable(GL_DEPTH_TEST);

	// render loop
	// While the windows is not closed
	while (!glfwWindowShouldClose(window))
	{
		// per-frame time logic
		// --------------------
		double currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
		// input
		// -----
		my_input(window);
		animate();

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
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);

	glfwTerminate();
	return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void my_input(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camera.ProcessKeyboard(FORWARD, (float)deltaTime);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera.ProcessKeyboard(BACKWARD, (float)deltaTime);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera.ProcessKeyboard(LEFT, (float)deltaTime);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera.ProcessKeyboard(RIGHT, (float)deltaTime);
	if (glfwGetKey(window, GLFW_KEY_PAGE_UP) == GLFW_PRESS)
		movY += 0.08f;
	if (glfwGetKey(window, GLFW_KEY_PAGE_DOWN) == GLFW_PRESS)
		movY -= 0.08f;
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
		rotX += 1.2f;
	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
		rotX -= 1.2f;
	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
		rotY -= 1.2f;
	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
		rotY += 1.2f;
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		movX -= 0.08f;
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		movX += 0.08f;
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		movZ += 0.08f;
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		movZ -= 0.08f;
	// --------------- Tipo de Iluminación

	// Luz Direccional
	if (glfwGetKey(window, GLFW_KEY_V) == GLFW_PRESS)
	{
		strcpy_s(Light_VertxShader, "shaders/shader_texture_light_dir.vs");
		strcpy_s(Light_FragShader, "shaders/shader_texture_light_dir.fs");
		Light_Direction = lightDirection;

		Spotlight_ON = 0;   
	}

	// Luz Posicional
	if (glfwGetKey(window, GLFW_KEY_B) == GLFW_PRESS)
	{
		strcpy_s(Light_VertxShader, "shaders/shader_texture_light_pos.vs");
		strcpy_s(Light_FragShader, "shaders/shader_texture_light_pos.fs");

		Light_Position = lightPosition;

		Spotlight_ON = 0;  
	}

	// Luz de Reflector
	if (glfwGetKey(window, GLFW_KEY_N) == GLFW_PRESS)
	{
		strcpy_s(Light_VertxShader, "shaders/shader_texture_light_spot.vs");
		strcpy_s(Light_FragShader, "shaders/shader_texture_light_spot.fs");

		Light_Position = camera.Position;
		Light_Direction = camera.Front;
		Light_CutOff = glm::cos(glm::radians(13.0f));

		Spotlight_ON = 1;  //La luz es de tipo reflector
	}


	// --------------- Intensidad de la luz

	// Aumenta Iluminación
	if ((glfwGetKey(window, GLFW_KEY_I) == GLFW_PRESS))
			opaco -= 2;
	// Disminuye Iluminación
	if ((glfwGetKey(window, GLFW_KEY_O) == GLFW_PRESS))
		opaco += 2;


	// ------- Color de la luz
	//R red	T blue Y verde U Amarillo F pink G orange H morado J negra K Blanco
	if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS)
		ColorLuz = Rojo;
	if (glfwGetKey(window, GLFW_KEY_T) == GLFW_PRESS)
		ColorLuz = Azul;
	if (glfwGetKey(window, GLFW_KEY_Y) == GLFW_PRESS)
		ColorLuz = Verde;
	if (glfwGetKey(window, GLFW_KEY_U) == GLFW_PRESS)
		ColorLuz = Amarillo;
	if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS)
		ColorLuz = Rosa;
	if (glfwGetKey(window, GLFW_KEY_G) == GLFW_PRESS)
		ColorLuz = Naranja;
	if (glfwGetKey(window, GLFW_KEY_H) == GLFW_PRESS)
		ColorLuz = Morado;
	if (glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS)
		ColorLuz = Negra;
	if (glfwGetKey(window, GLFW_KEY_K) == GLFW_PRESS)
		ColorLuz = Blanca;
	
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void resize(GLFWwindow* window, int width, int height)
{
	// Set the Viewport to the size of the created window
	glViewport(0, 0, width, height);
}

// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{

	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	double xoffset = xpos - lastX;
	double yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

	lastX = xpos;
	lastY = ypos;

	camera.ProcessMouseMovement(xoffset * 3, yoffset * 3);
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	camera.ProcessMouseScroll(yoffset);
}