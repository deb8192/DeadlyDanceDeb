#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <cmath>
#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

// Codigo fuente de vertex y fragment shader
const char *vertexShaderSource = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"    // la variable de posicion tiene el atributo posicion a 0
    "layout (location = 1) in vec3 aColor;\n"  // la variable de color tiene el atributo posicion a 1
    "out vec3 ourColor;\n"                     // out: especificar color de salida del fragment shader
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos, 1.0);\n"      // Posicion (aPos es un vec3)
    "   ourColor = aColor;\n"                  // ourColor es el color obtenido en el atributo
    "}\0";

const char *fragmentShaderSource = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "in vec3 ourColor;\n"                      // recibes la variable desde el vertex shader (mismo nombre y mismo tipo)
    "void main()\n"
    "{\n"
    "   FragColor = vec4(ourColor, 1.0);\n"    // la usamos para el fragment
    "}\n\0";

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
    //VertexShader
    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    //Adjuntamos el codigo del vertexshader en "vertexShaderSource" al objeto
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);
    //Errores de compilacion
    int  success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    //FragmentShader
    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    //Errores de compilacion
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    //Vincular shaders a objeto de programa
    unsigned int shaderProgram;
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    //Errores al vincular
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }

    //Borrar objetos shaders despues de vincularlos al programa
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    //***********TRIANGULO***********
    //Vertices de un TRIANGULO
    float vertices[] = {
         //posiciones        //colores
         0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,   // bottom right
        -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,   // bottom left
         0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f    // top
    };

    //Vertex Buffer Object
    unsigned int VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    //Vertex Array Object
    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    //**********VERTICES***********
    //Configurar como va a interpretar OpenGL los datos de los vertices
    // Atributo posicion
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // Atributo color
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3* sizeof(float)));  //Aqui si necesitamos especificar un desplazamiento ya que no empieza en 0 como la posicion
    glEnableVertexAttribArray(1);                                                                   //...como la posicion, es despues del tercer byte entonces 3 * sizeof(float)

    //desligar el objeto Vertex Array
    glBindVertexArray(0);

    //Bucle de render
    while(!glfwWindowShouldClose(window))
    {
        //Input
        processInput(window);

        //Comandos de render
        //borrar pantalla
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        //UPDATE DE COLOR EN EL TIEMPO CON SHADERS
        glUseProgram(shaderProgram);                                                //usar programa shader
        float timeValue = glfwGetTime();                                            //tiempo de ejecucion en segundos
        float greenValue = (sin(timeValue) / 2.0f) + 0.5f;                          //variacion del color en el tiempo VERDE
        int vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");  //obtenemos el nombre del programa shader y el nombre del uniforme (-1 no se pudo encontrar)
        glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);             //cambiar el uniform del color (glUniform4f espera un uniform de 4 float)

        //DIBUJAR NUESTRO TRIANGULO
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        //Comprobar y llamar eventos, cambiar buffers
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

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

