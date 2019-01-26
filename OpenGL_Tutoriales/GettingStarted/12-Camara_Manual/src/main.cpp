#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb_image.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <cmath>
#include <iostream>

#include "Shader.hpp"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);           //Movimiento con el raton
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);    //Scroll con la rueda del raton
void processInput(GLFWwindow *window);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

//Posiciones de la camara, inicializadas
glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);     //Posicion de la camara en el mundo 3D
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);  //Objetivo donde apunta la camara, en este caso al origen
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);      //Up Axis

//Inicializacion de datos del raton, (yaw,pitch = Angulos de euler)
bool firstMouse = true;           // para asegurar datos la primera vez
float yaw   = -90.0f;	          // yaw (inclinacion de derecha a izquierda) se inicializa a -90.0 grados ya que un guiñada de 0.0 resulta en un vector de dirección apuntando hacia la derecha, por lo que inicialmente giramos un poco hacia la izquierda.
float pitch =  0.0f;              // pich (inclinacion de arriba a abajo) inicializado a 0
float lastX =  SCR_WIDTH / 2.0;   // Centro del primer frame (normalmente centro de la ventana)
float lastY =  SCR_HEIGHT / 2.0;
float fov   =  45.0f;             // campo de vision o fov

float deltaTime = 0.0f;	// Tiempo entre el actual frame y el ultimo
float lastFrame = 0.0f; // Tiempo del ultimo frame

int main()
{
    //*********** INICIALIZAR ***********
    // Inicializar GLFW
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); //Solo para OS X

    //Creamos una ventana
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);                 //Iniciar mouse
    glfwSetScrollCallback(window, scroll_callback);                   //Iniciar scroll
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED); //Le dice a GLFW que capture el raton, de esta manera no se saldra de pantalla, ademas de esconder el cursor

    //Inicializar GLAD (administra los punteros de OpenGL)
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    //*********** APLICAR PROFUNDIDAD Z-BUFFER ***********
    glEnable(GL_DEPTH_TEST);

    //*********** SHADERS ***********
    Shader *ourShader = new Shader("shaders/shader.vs", "shaders/shader.fs");

    //***********RECTANGULO***********
    float vertices[] = {
         // positions      //Coordenadas de la textura (ejes s,t)
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
    };
    //posicion de 10 cubos en el mundo
    glm::vec3 cubePositions[] = {
      glm::vec3( 0.0f,  0.0f,  0.0f),
      glm::vec3( 2.0f,  5.0f, -15.0f),
      glm::vec3(-1.5f, -2.2f, -2.5f),
      glm::vec3(-3.8f, -2.0f, -12.3f),
      glm::vec3( 2.4f, -0.4f, -3.5f),
      glm::vec3(-1.7f,  3.0f, -7.5f),
      glm::vec3( 1.3f, -2.0f, -2.5f),
      glm::vec3( 1.5f,  2.0f, -2.5f),
      glm::vec3( 1.5f,  0.2f, -1.5f),
      glm::vec3(-1.3f,  1.0f, -1.5f)
    };

    //Vertex Buffer Object && Vertex Array Object
    unsigned int VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    //**********VERTICES***********
    // Atributo posicion
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // Atributo textura
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    //*********** TEXTURAS ***********
    //TEXTURA 1
    //Crear textura
    unsigned int texture1;
    glGenTextures(1, &texture1);

    //Enlazar textura
    glBindTexture(GL_TEXTURE_2D, texture1);

    //Parametros de la textura
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);

    //Filtrado y escalado de texturas (GL_NEAREST:mas pixelado, mejor para minimizar/ GL_LINEAR:mas suave y borroso, mejor para aumentar)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    //Cargar y generar textura
    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(true);  // le dices a stb_image.h que gire la textura cargada en el y-axis
    unsigned char *data = stbi_load("resources/container.jpg", &width, &height, &nrChannels, 0);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);

    //TEXTURA 2
    //Crear textura
    unsigned int texture2;
    glGenTextures(1, &texture2);

    //Enlazar textura
    glBindTexture(GL_TEXTURE_2D, texture2);

    //Parametros de la textura
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    //Filtrado y escalado de texturas
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    //Cargar y generar textura
    data = stbi_load("resources/awesomeface.png", &width, &height, &nrChannels, 0);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data); //Liberar imagen memoria

    //Pasar textura al shader
    ourShader->use(); //activar shader
    // Aplicar uniform manualmente o usando funcion
    ourShader->setInt("texture1", 0);
    ourShader->setInt("texture2", 1);

    //Bucle de render
    while(!glfwWindowShouldClose(window))
    {
        //Tiempo por frame
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        //Input
        processInput(window);

        //Comandos de render
        //borrar pantalla
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        //Aplicar Textura1
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture1);
        //Aplicar Textura2
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, texture2);

        //USAR SHADERS
        ourShader->use();

        //CAMARA
        //Aplicar proyeccion en la escena
        glm::mat4 projection = glm::mat4(1.0f);
        projection = glm::perspective(glm::radians(fov), (float)SCR_WIDTH/(float)SCR_HEIGHT, 0.1f, 100.0f);   //agregamos el fov
        ourShader->setMat4("projection",projection);
        //Funcion lookAt, calculo de la matriz final
        glm::mat4 view;
        view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);    //con la suma nos aseguramos que al movernos siempre mirara al objetivo
        ourShader->setMat4("view", view);

        //DIBUJAR ARRAY DE CUBOS
        glBindVertexArray(VAO);
        for(unsigned int i = 0; i < 10; i++)
        {
          glm::mat4 model = glm::mat4(1.0f);
          model = glm::translate(model, cubePositions[i]);
          float angle = 20.0f * i;
          model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
          ourShader->setMat4("model", model);

          glDrawArrays(GL_TRIANGLES, 0, 36);
        }

        //Comprobar y llamar eventos, cambiar buffers
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glfwTerminate();
    return 0;
}

//Procesa todos los Input
void processInput(GLFWwindow *window)
{
    float cameraSpeed = 2.5 * deltaTime;

    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)  //Si pulsas Escape
        glfwSetWindowShouldClose(window, true);            //Cerrar GLFW

    if(glfwGetKey(window, GLFW_KEY_G) == GLFW_PRESS)    //Si pulsas G
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);      //vista de wireframe.

    if(glfwGetKey(window, GLFW_KEY_H) == GLFW_PRESS)    //Si pulsas H
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);      //vista poligonos normal

    //Movimiento de la camara
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        cameraPos += cameraSpeed * cameraFront;

    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        cameraPos -= cameraSpeed * cameraFront;

    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;

    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
}

//Funcion cambio del viewport
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

//glfw:Cada vez que el ratón se mueve, esta funcion se llama
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    if(firstMouse) //Si es la primera vez, actualizar al centro del frame actual
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    //Calculo del movimiento de desplazamiento entre el ultimo y el frame actual
    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // Invertido, ya que las coordenadas Y van de abajo hacia arriba.
    lastX = xpos;
    lastY = ypos;

    //sensibilidad del raton
    float sensitivity = 0.1f; // cambiar este valor a tu gusto
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    //actualizar las inclinaciones
    yaw += xoffset;
    pitch += yoffset;

    //asegurarse de que cuando el raton está fuera de los límites, la pantalla no se de la vuelta
    if (pitch > 89.0f)
        pitch = 89.0f;
    if (pitch < -89.0f)
        pitch = -89.0f;

    //Calculo del vector de direccion, cambiando el objetivo (cameraFrom)
    glm::vec3 front;
    front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    front.y = sin(glm::radians(pitch));
    front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    cameraFront = glm::normalize(front);
}

//glfw: Cada vez que haces scroll con el raton, esta funcion se llama
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    //Cambiar el fov entre 1 y 90
    if (fov >= 1.0f && fov <= 90.0f)
        fov -= yoffset;
    if (fov <= 1.0f)
        fov = 1.0f;
    if (fov >= 90.0f)
        fov = 90.0f;
}

