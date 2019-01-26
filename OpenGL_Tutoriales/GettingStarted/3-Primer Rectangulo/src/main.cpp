#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

// Codigo fuente de vertex y fragment shader
const char *vertexShaderSource = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"   //Posicion
    "}\0";
const char *fragmentShaderSource = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"  //Color
    "}\n\0";

int main()
{
    //*********** INICIALIZAR ***********
    // Inicializar GLFW
    // glfwWindowHint para configurar GLFW, mirar en la documentacion los distintos hint
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);  //glfwWindowHint(opcion_hint,valor_hint);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); //Solo para OS X

    //Creamos una ventana
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);  //glfwCreateWindow(ancho,alto,nombre,NULL,NULL)
    if (window == NULL) //si no se crea el objeto ventana, error
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);  //Hacer el contexto principal este objeto ventana
    //Se llama a la funcion "framebuffer_size_callback" cada vez que el usuario cambia el tamanyo de ventana
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    //Inicializar GLAD (administra los punteros de OpenGL)
    //Nos da glfwGetProcAddress, donde se define la funcion dependiendo del Sistema operativo al compilar
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    //*********** SHADERS ***********
    //VertexShader
    //Creamos un objeto shader como vertex shader
    unsigned int vertexShader;                                  //id del vertex shader
    vertexShader = glCreateShader(GL_VERTEX_SHADER);            //crear objeto
    //Adjuntamos el codigo del vertexshader en "vertexShaderSource" al objeto
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL); //glShaderSource(objeto,cadenas,codigofuente,NULL)
    glCompileShader(vertexShader);                              //Compilar el vertexShader
    //Comprobar que no hay fallos, imprimiendo mensaje de error
    int  success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    //FragmentShader
    //Igual que el vertex
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
    shaderProgram = glCreateProgram();              //crear objeto de programa
    glAttachShader(shaderProgram, vertexShader);    //Juntar los shaders en el programa
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);                   //Vincularlos
    //Errores al vincular
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }

    //Borrar objetos shaders despues de vincularlos al programa
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    //***********RECTANGULO***********
    //Vertices de un RECTANGULO (son 2 triangulos), cada uno con x, y, z (dentro de la pantalla entre -1 y 1)
    float vertices[] = {
         0.5f,  0.5f, 0.0f,  // top right
         0.5f, -0.5f, 0.0f,  // bottom right
        -0.5f, -0.5f, 0.0f,  // bottom left
        -0.5f,  0.5f, 0.0f   // top left
    };
    unsigned int indices[] = {  // indice para los dos triangulos, que vertices usar (de esta manera no hay que repetir los vertices en la matriz)
        0, 1, 3,  // primer Triangle
        1, 2, 3   // segundo Triangle
    };

    //Vertex Buffer Object, almacena vertices en la memoria de la GPU
    unsigned int VBO;
    glGenBuffers(1, &VBO);
    //Vincular el buffer creado al array de buffer
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    //Copia los datos de vertice en la memoria del buffer
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);  //glBufferData(tipo_de_buffer,tamanyo_datos,datos,frecuencia_de_cambio)

    //Vertex Array Object, almacena array de vertices
    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);   //Enlazar el objeto Vertex Array

    //Element Buffer Objects, almacena los indices para que OpenGL decida el orden en el que dibujar los vertices
    unsigned int EBO;
    glGenBuffers(1, &EBO);
    //Vincula el buffer creado, al element array buffer (en vez de llamarlo con glDrawArrays, se llama con glDrawElements)
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW); //Similar al buffer de VBO

    //**********VERTICES***********
    //Configurar como va a interpretar OpenGL los datos de los vertices
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    /*glVertexAttribPointer(atributo_vertice_a_configurar,        //empezar en 0
                            tamanyo_del_atributo_de_vertice,      //x,y,z
                            tipo_de_datos,
                            ¿normalizar_datos?,
                            espacio_entre_atributos_en_el_array,  //Esto es porque cada vertice tiene un tamanyo de 3 (x,y,z) en el array, y van uno detras de otro
                            compensar_donde_empiezan_en_buffer
    */
    glEnableVertexAttribArray(0);

    //desligar del buffer   ATENCION: No desligar el EBO mientras un VAO esta activo, ya que el objeto del buffer esta en el VAO
    //glBindBuffer(GL_ARRAY_BUFFER, 0);

    //desligar el objeto Vertex Array
    glBindVertexArray(0);

    //Bucle de render
    while(!glfwWindowShouldClose(window))    //Comprueba al inicio de la iteracion si se ha ordenado cerrar GLFW, si es asi es TRUE y sale del bucle
    {
        //Input
        processInput(window);

        //Comandos de render
        //borrar pantalla
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f); //Designamos a el glClearColor un color
        glClear(GL_COLOR_BUFFER_BIT);         //Borrarmos en el buffer con el glClearColor designado

        //DIBUJAR NUESTRO TRIANGULO
        //Usar objeto de programa (contiene los shaders)
        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        //glDrawArrays(GL_TRIANGLES, 0, 3);                  //glDrawArrays(primitiva_a_dibujar,inicio_del_indice_de_la_matriz,vertices_a_dibujar)
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0); //glDrawArrays(primitiva_a_dibujar,numero_de_elementos,tipo_de_los_indices,desplazamiento_solo_si_no_usas_buffer_de_elementos)

        //Comprobar y llamar eventos, cambiar buffers
        glfwSwapBuffers(window);             //Intercambia los buffer de la ventana
        glfwPollEvents();                    //Verifica si se activa algun evento (teclado,raton,etc...)
    }

    glfwTerminate();   //limpiar todos los recursos en memoria de GLFW
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

//Funcion para que cuando el usuario cambie el tamanyo de ventana, automaticamente esta cambie el viewport
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

