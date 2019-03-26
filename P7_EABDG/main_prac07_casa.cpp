/*---------------------------------------------------------*/
/* ----------------   Práctica 7 --------------------------*/
/*-----------------    2019-2   ---------------------------*/
/*------------- Alumno: Díaz Gutiérrez Elvira Angela Belem ---------------*/
/*------------------ Visual Studio Versión 2017 --------------------*/
/*Instrucciones de uso:
Para poder observar, mover y rotar la imagen se debe tienen las siguientes teclas con sus respectivas acciones:
	D					Mueve el modelo atomico a la izquierda
	A					Mueve el modelo atomico a la derecha
	AvPág				Mueve el modelo atomico hacia abajo
	RePág				Mueve el modelo atomico hacia arriba
	W					Acerca el modelo atomico
	S					Aleja el modelo atomico
	Flecha abajo		Rota el modelo atomico hacia enfrente
	Flecha arriba		Rota el modelo atomico hacia atras
	L					Cambia la ubicacion de la fuente de luz,inicialmente esta abajo a la derecha y al presionar L
						se coloca arriba a la izquierda y al presionarse de nuevo regresa a su lugar inicial.
*/

#include "esfera.h"
#include "camera.h"

Esfera my_sphere(1.0);

void resize(GLFWwindow* window, int width, int height);
void my_input(GLFWwindow *window);
void mouse_callback(GLFWwindow *window, double xpos, double ypos);
void scroll_callback(GLFWwindow *window, double xoffset, double yoffset);

// settings
// Window size
int SCR_WIDTH = 3800;
int SCR_HEIGHT = 7600;

GLFWmonitor *monitors;
GLuint VBO, VAO, lightVAO;

//Camera
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
double	lastX = 0.0f,
		lastY = 0.0f;
bool firstMouse = true;

//Timing
double	deltaTime = 0.0f,
		lastFrame = 0.0f;

//Lighting
float luzX = 3.0f;
float luzY = -3.0f;
glm::vec3 lightPos(luzX, luzY, 2.0f);

void myData(void);
void display(void);
void getResolution(void);
void animate(void);

//For Keyboard
float	movX = 0.0f,
		movY = 0.0f,
		movZ = -5.0f;
float	angX = 0.0f;
float	angY = 0.0f;

float	nucleo = 0.0f;
float	electron1 = 0.0f,
electron2 = 0.0f,
electron3 = 0.0f,
electron4 = 0.0f,
electron5 = 0.0f,
electron6 = 0.0f;

int Presionado = 0;

void getResolution()
{
	const GLFWvidmode * mode = glfwGetVideoMode(glfwGetPrimaryMonitor());

	SCR_WIDTH = mode->width;
	SCR_HEIGHT = (mode->height) - 80;

	lastX = SCR_WIDTH / 2.0f;
	lastY = SCR_HEIGHT / 2.0f;

}

void myData()
{	
		GLfloat vertices[] = {
		//Position				//Normals
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,//
		 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		 0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,

		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

		 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
	};

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &VBO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// Normal attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);


	//To configure Second Objecto to represet Light
	glGenVertexArrays(1, &lightVAO);
	glBindVertexArray(lightVAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

}

void animate(void)
{
	nucleo += 0.5f;
	electron1 += 0.9f;
	electron2 += 0.8f;
	electron3 += 0.7f;
	electron4 += 0.6f;
	electron5 += 0.5f;
	electron6 += 0.4f;

}

void display(void)
{
	//Shader myShader("shaders/shader.vs", "shaders/shader.fs");
	//Shader projectionShader("shaders/shader_projection.vs", "shaders/shader_projection.fs");
	Shader projectionShader("shaders/shader_light.vs", "shaders/shader_light.fs");
	//Shader projectionShader("shaders/shader_light_Gouraud.vs", "shaders/shader_light_Gouraud.fs");
	Shader lampShader("shaders/shader_lamp.vs", "shaders/shader_lamp.fs");

	//To Use Lighting
	projectionShader.use();
	//projectionShader.setVec3("lightColor", 1.0f, 1.0f, 1.0f);
	//projectionShader.setVec3("lightPos", lightPos);
	projectionShader.setVec3("lightColor", 1.0f, 1.0f, 1.0f);
	projectionShader.setVec3("lightPos", glm::vec3(luzX, luzY, 2.0f));


	// create transformations and Projection
	glm::mat4 model = glm::mat4(1.0f);		// initialize Matrix, Use this matrix for individual models
	glm::mat4 view = glm::mat4(1.0f);		//Use this matrix for ALL models
	glm::mat4 projection = glm::mat4(1.0f);	//This matrix is for Projection

	//Use "projection" to inlcude Camera
	projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
	//view = camera.GetViewMatrix();
	view = glm::translate(view, glm::vec3(movX, movY, movZ));
	view = glm::rotate(view, glm::radians(angX), glm::vec3(0, 1, 0));//Hace la rotacion
	view = glm::rotate(view, glm::radians(angY), glm::vec3(1, 0, 0));

	// pass them to the shaders}
	projectionShader.setVec3("viewPos", camera.Position);
	projectionShader.setMat4("model", model);
	projectionShader.setMat4("view", view);
	// note: currently we set the projection matrix each frame, but since the projection matrix rarely changes it's often best practice to set it outside the main loop only once.
	projectionShader.setMat4("projection", projection);


	glBindVertexArray(VAO);
	//nucleo Amarillo
	model = glm::rotate(model, glm::radians(nucleo), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::scale(model, glm::vec3(2.0f, 2.0f, 2.0f));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("ambientColor", 0.0f, 0.0f, 1.0f);
	projectionShader.setVec3("diffuseColor", 1.0f, 1.0f, 0.0f);
	projectionShader.setVec3("specularColor", 1.0f, 0.0f, 0.0f);
	my_sphere.render();

	//electron1  Cafe
	model = glm::mat4(1.0f);
	model = glm::rotate(model, glm::radians(electron1), glm::vec3(1.0f, 0.0f, 0.0f));
	model = glm::translate(model, glm::vec3(0, 4, 0));
	model = glm::rotate(model, glm::radians(electron1), glm::vec3(1.0f, 0.0f, 0.0f));
	model = glm::scale(model, glm::vec3(0.4f, 0.4f, 0.4f));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("ambientColor", 0.0f, 0.0f, 1.0f);
	projectionShader.setVec3("diffuseColor", 0.4f, 0.2f, 0.0f);
	projectionShader.setVec3("specularColor", 0.729f, 0.4f, 0.070f);
	my_sphere.render();

	//electron2 naranja
	model = glm::mat4(1.0f);
	model = glm::rotate(model, glm::radians(electron2), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::translate(model, glm::vec3(4, 0, 0));
	model = glm::rotate(model, glm::radians(electron2), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::scale(model, glm::vec3(0.4f, 0.4f, 0.4f));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("ambientColor", 0.0f, 0.0f, 1.0f);
	projectionShader.setVec3("diffuseColor", 1.0f, 0.5f, 0.0f);
	projectionShader.setVec3("specularColor", 0.976f, 0.701f, 0.423f);
	my_sphere.render();

	//electron3 Azul Verdoso
	model = glm::mat4(1.0f);
	model = glm::rotate(model, glm::radians(electron3), glm::vec3(1.0f, 1.0f, 0.0f));
	model = glm::translate(model, glm::vec3(-4, 4, 0));
	model = glm::rotate(model, glm::radians(electron3), glm::vec3(1.0f, 1.0f, 0.0f));
	model = glm::scale(model, glm::vec3(0.4f, 0.4f, 0.4f));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("ambientColor", 0.0f, 0.0f, 1.0f);
	projectionShader.setVec3("diffuseColor", 0.0f, 1.0f, 0.537f);
	projectionShader.setVec3("specularColor", 0.549f, 0.890f, 0.733f);
	my_sphere.render();

	//electron4 Rojo
	model = glm::mat4(1.0f);
	model = glm::rotate(model, glm::radians(electron4), glm::vec3(-1.0f, 1.0f, 0.0f));
	model = glm::translate(model, glm::vec3(4, 4, 0));
	model = glm::rotate(model, glm::radians(electron4), glm::vec3(-1.0f, 1.0f, 0.0f));
	model = glm::scale(model, glm::vec3(0.4f, 0.4f, 0.4f));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("ambientColor", 0.0f, 0.0f, 1.0f);
	projectionShader.setVec3("diffuseColor", 1.0f, 0.0f, 0.0f);
	projectionShader.setVec3("specularColor", 0.984f, 0.513f, 0.513f);
	my_sphere.render();

	//electron5 Café grisaseo
	model = glm::mat4(1.0f);
	model = glm::rotate(model, glm::radians(electron5), glm::vec3(0.5f, 1.0f, 0.0f));
	model = glm::translate(model, glm::vec3(-4, 2, 0));
	model = glm::rotate(model, glm::radians(electron5), glm::vec3(0.5f, 1.0f, 0.0f));
	model = glm::scale(model, glm::vec3(0.4f, 0.4f, 0.4f));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("ambientColor", 0.0f, 0.0f, 1.0f);
	projectionShader.setVec3("diffuseColor", 0.580f, 0.494f, 0.478f);
	projectionShader.setVec3("specularColor", 0.756f, 0.658f, 0.643f);
	my_sphere.render();

	//electron6 Azul
	model = glm::mat4(1.0f);
	model = glm::rotate(model, glm::radians(electron6), glm::vec3(-0.5f, 1.0f, 0.0f));
	model = glm::translate(model, glm::vec3(-4, -2, 0));
	model = glm::rotate(model, glm::radians(electron6), glm::vec3(-0.5f, 1.0f, 0.0f));
	model = glm::scale(model, glm::vec3(0.4f, 0.4f, 0.4f));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("ambientColor", 0.0f, 0.0f, 1.0f);
	projectionShader.setVec3("diffuseColor", 0.0f, 0.0f, 1.0f);
	projectionShader.setVec3("specularColor", 0.349f, 0.349f, 0.909f);
	my_sphere.render();

	//luz
	projectionShader.setVec3("lightColor", 1.0f, 1.0f, 1.0f);
	projectionShader.setVec3("lightPos", glm::vec3(luzX, luzY, 2.0f));
	lampShader.use();
	lampShader.setMat4("projection", projection);
	lampShader.setMat4("view", view);
	//model = glm::mat4(1.0f);
	model = glm::translate(model,glm::vec3( luzX, luzY, 2.0f));
	model = glm::scale(model, glm::vec3(1.0f));
	lampShader.setMat4("model", model);

	glBindVertexArray(lightVAO);
	//glDrawArrays(GL_TRIANGLES, 0, 36);	//Light


	//glBindVertexArray(0);

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

    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Practica 7", NULL, NULL);
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
	glDeleteVertexArrays(1, &lightVAO);
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

	

	if ( (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS) && (Presionado == 0) ) 
	{
		luzX = -luzX;
		luzY = -luzY;
		Presionado = 1;
	}

	if ( glfwGetKey(window, GLFW_KEY_L) == GLFW_RELEASE )
	{
		Presionado = 0;
	}
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

	camera.ProcessMouseMovement(xoffset, yoffset);
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	camera.ProcessMouseScroll(yoffset);
}