#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb_image.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <cmath>
#include <iostream>

#include "Shader.hpp"
#include "Camara.hpp"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);   //Tamanyo de ventana de renderizado
void mouse_callback(GLFWwindow* window, double xpos, double ypos);           //Movimiento con el raton
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);    //Scroll con la rueda del raton
void processInput(GLFWwindow *window);                                       //Input de teclado

//Opciones de pantalla
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

//Posiciones de la camara, inicializadas
Camara *camera = new Camara(glm::vec3(0.0f, 0.0f, 3.0f)); // Creas un objeto camara (yaw,pitch,fov(como ZOOM) inicializados en el constructor)
float lastX = SCR_WIDTH / 2.0f;                           // Centro del primer frame (normalmente centro de la ventana)
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;                                   // para asegurar datos la primera vez

//Tiempos
float deltaTime = 0.0f;	// Tiempo entre el actual frame y el ultimo
float lastFrame = 0.0f; // Tiempo del ultimo frame

int main()
{
    //*********** INICIALIZAR ***********
    // Inicializar GLFW (glfwWindowHint para configurar GLFW, mirar en la documentacion los distintos hint)
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);     //glfwWindowHint(opcion_hint,valor_hint);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); //Solo para OS X
#endif

    //Creamos una ventana
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL); //glfwCreateWindow(ancho,alto,nombre,NULL,NULL)
    if (window == NULL) //si no se crea el objeto ventana, error
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);                                    //Hacer el contexto principal este objeto ventana
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback); //Se llama a la funcion "framebuffer_size_callback" cada vez que el usuario cambia el tamanyo de ventana
    glfwSetCursorPosCallback(window, mouse_callback);                  //Iniciar mouse
    glfwSetScrollCallback(window, scroll_callback);                    //Iniciar scroll
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);       //Le dice a GLFW que capture el raton, de esta manera no se saldra de pantalla, ademas de esconder el cursor

    //Inicializar GLAD (administra los punteros de OpenGL)
    //Nos da glfwGetProcAddress, donde se define la funcion dependiendo del Sistema operativo al compilar
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    //*********** APLICAR PROFUNDIDAD Z-BUFFER ***********
    glEnable(GL_DEPTH_TEST);   //Necesario para el zoom/fov

    //*********** SHADERS ***********
    Shader *ourShader = new Shader("shaders/shader.vs", "shaders/shader.fs");

    //***********RECTANGULO***********
    float vertices[] = {
         // positions         //Coordenadas de la textura (ejes s,t)
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

    //Vertex Buffer Object (VBO) && Vertex Array Object (VAO)
    unsigned int VBO, VAO;
    glGenVertexArrays(1, &VAO); //VAO: almacena información sobre el estado del búfer y de los atributos de vértices.
    glGenBuffers(1, &VBO);      //VBO: objeto de búfer que asigna memoria y almacena todos los datos de vértices para la tarjeta gráfica a utilizar.

    glBindVertexArray(VAO);     //Enlazar el objeto Vertex Array

    glBindBuffer(GL_ARRAY_BUFFER, VBO);                                        //Vincular el buffer creado al array de buffer
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); //Copia los datos de vertice en la memoria del buffer
                                                                               //glBufferData(tipo_de_buffer,tamanyo_datos,datos,frecuencia_de_cambio)
    //**********VERTICES***********
    // Atributo posicion
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    /*glVertexAttribPointer(atributo_vertice_a_configurar,    //empezar en 0
                        tamanyo_del_atributo_de_vertice,      //x,y,z = 3
                        tipo_de_datos,
                        ¿normalizar_datos?,
                        espacio_entre_atributos_en_el_array,  //Esto es porque cada vertice tiene un tamanyo de 3 (x,y,z) en el array, y van uno detras de otro
                        compensar_donde_empiezan_en_buffer);
    */
    // Atributo textura
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));  //Aqui si necesitamos especificar un desplazamiento ya que no empieza en 0 como la posicion
    glEnableVertexAttribArray(1);                                                                    //...como la posicion, es despues del tercer byte entonces 3 * sizeof(float)

    //*********** TEXTURAS ***********
    //TEXTURA 1
    //Crear textura
    unsigned int texture1;
    glGenTextures(1, &texture1); //primer parametro el numero de texturas

    //Enlazar textura
    glBindTexture(GL_TEXTURE_2D, texture1);

    //Parametros de la textura
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);   //glTexParameteri(tipo_de_textura,opcion_y_eje,modo_de_ajuste)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);   //GL_MIRRORED_REPEAT:se repite la textura si no encaja, pero girada

    //Filtrado y escalado de texturas (GL_NEAREST:mas pixelado, mejor para minimizar/ GL_LINEAR:mas suave y borroso, mejor para aumentar)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);       //Filtrado al minimizar
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);        //Filtrado al aumentar

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
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);  //al ser PNG es RGBA
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
    while(!glfwWindowShouldClose(window))  //Comprueba al inicio de la iteracion si se ha ordenado cerrar GLFW, si es asi es TRUE y sale del bucle
    {
        //Tiempo por frame
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        //Input
        processInput(window);

        //Comandos de render
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);                //Designamos a el glClearColor un color
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  //Borrarmos en el buffer con el glClearColor designado

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
        projection = glm::perspective(glm::radians(camera->Zoom), (float)SCR_WIDTH/(float)SCR_HEIGHT, 0.1f, 100.0f);   //agregamos el fov (Zoom)
        ourShader->setMat4("projection",projection);
        //Vista, Funcion lookAt, calculo de la matriz final
        glm::mat4 view = camera->GetViewMatrix();
        ourShader->setMat4("view", view);

        //DIBUJAR ARRAY DE CUBOS
        glBindVertexArray(VAO);
        for(unsigned int i = 0; i < 10; i++)
        {
          glm::mat4 model = glm::mat4(1.0f);                                             //inicializar matriz de transformacion (si no la inicializas seria matriz nula)
          model = glm::translate(model, cubePositions[i]);                               //Trasladar cubo a posicion
          float angle = 20.0f * i;                                                       //angulo para rotar
          model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));  //Rotar cubo "angle" grados
          ourShader->setMat4("model", model);                                            //Pasar a la variable uniform "model" del shader

          glDrawArrays(GL_TRIANGLES, 0, 36);                                             //Dibujado
        }

        //Comprobar y llamar eventos, cambiar buffers
        glfwSwapBuffers(window);   //Intercambia los buffer de la ventana
        glfwPollEvents();          //Verifica si se activa algun evento (teclado,raton,etc...)
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glfwTerminate();               //limpiar todos los recursos en memoria de GLFW
    return 0;
}

//Procesa todos los Input
void processInput(GLFWwindow *window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)  //Si pulsas Escape
        glfwSetWindowShouldClose(window, true);            //Cerrar GLFW

    if(glfwGetKey(window, GLFW_KEY_G) == GLFW_PRESS)       //Si pulsas G
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);         //vista de wireframe.

    if(glfwGetKey(window, GLFW_KEY_H) == GLFW_PRESS)       //Si pulsas H
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);         //vista poligonos normal

    //Movimiento de la camara
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera->ProcessKeyboard(FORWARD, deltaTime);     //Llamadas en la clase Camara
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera->ProcessKeyboard(BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera->ProcessKeyboard(LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera->ProcessKeyboard(RIGHT, deltaTime);
}

//Funcion cambio del viewport (tamanyo de la ventanta de renderizado)
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height); //glViewport(esq_inf_izquierda_x,esq_inf_izquierda_y,ancho,alto);
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

    camera->ProcessMouseMovement(xoffset, yoffset);
}

//glfw: Cada vez que haces scroll con el raton, esta funcion se llama
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    camera->ProcessMouseScroll(yoffset);
}

