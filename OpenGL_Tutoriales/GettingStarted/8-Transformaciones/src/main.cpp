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
void processInput(GLFWwindow *window);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

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

    //Inicializar GLAD (administra los punteros de OpenGL)
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    //*********** SHADERS ***********
    Shader *ourShader = new Shader("shaders/shader.vs", "shaders/shader.fs");

    //***********RECTANGULO***********
    //Vertices de un RECTANGULO
    float vertices[] = {
        // positions          // colors           //Coordenadas de la textura (ejes s,t)
         0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // top right
         0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // bottom right
        -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // bottom left
        -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // top left
    };
    unsigned int indices[] = {
        0, 1, 3, // first triangle
        1, 2, 3  // second triangle
    };
    //Vertex Buffer Object && Vertex Array Object
    unsigned int VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    //**********VERTICES***********
    // Atributo posicion
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // Atributo color
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3* sizeof(float)));
    glEnableVertexAttribArray(1);
    // Atributo textura
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    //*********** TEXTURAS ***********
    //TEXTURA 1
    //Crear textura
    unsigned int texture1;
    glGenTextures(1, &texture1); //primer parametro el numero de texturas

    //Enlazar textura
    glBindTexture(GL_TEXTURE_2D, texture1);

    //Parametros de la textura
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);

    //Si elegimos la opcion GL_CLAMP_TO_BORDER, especificariamos el color del borde
    // float borderColor[] = { 1.0f, 1.0f, 0.0f, 1.0f };
    // glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);

    //Filtrado y escalado de texturas (GL_NEAREST:mas pixelado, mejor para minimizar/ GL_LINEAR:mas suave y borroso, mejor para aumentar)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    //MipMaps (diferentes texturas para diferentes tamanyos), usar SOLO al minimizar
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

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
    stbi_image_free(data); //Liberar imagen memoria

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
    glUniform1i(glGetUniformLocation(ourShader->ID, "texture1"), 0);
    ourShader->setInt("texture2", 1);

    //Bucle de render
    while(!glfwWindowShouldClose(window))
    {
        //Input
        processInput(window);

        //Comandos de render
        //borrar pantalla
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        //Aplicar Textura1
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture1);
        //Aplicar Textura2
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, texture2);

        //TRANSFORMACION EN TIEMPO REAL
        glm::mat4 trans = glm::mat4(1.0f);                                             //inicializar matriz de transformacion (si no la inicializas seria matriz nula)
        trans = glm::rotate(trans, (float)glfwGetTime(), glm::vec3(0.0, 0.0, 1.0));    //Rotar (glfwGetTime: angulo con el tiempo) grados en z
        trans = glm::scale(trans, glm::vec3(0.5, 0.5, 0.5));                           //Escalamos 0.5 en cada eje

        //USAR SHADERS
        ourShader->use();
        unsigned int transformLoc = glGetUniformLocation(ourShader->ID, "transform");  //Ubicacion de la variable uniforme transform
        glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));          //glUniformMatrix4fv(variable_uniform,numero_de_matrizes_a_enviar,¿transponer_matriz?,matriz_transformacion_en_GLM)

        //DIBUJAR NUESTRO TRIANGULO
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        //Comprobar y llamar eventos, cambiar buffers
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glfwTerminate();
    return 0;
}

//Procesa todos los Input
void processInput(GLFWwindow *window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)  //Si pulsas Escape
        glfwSetWindowShouldClose(window, true);            //Cerrar GLFW

    if(glfwGetKey(window, GLFW_KEY_G) == GLFW_PRESS)    //Si pulsas G
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);      //vista de wireframe.

    if(glfwGetKey(window, GLFW_KEY_H) == GLFW_PRESS)    //Si pulsas H
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);      //vista poligonos normal
}

//Funcion cambio del viewport
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

