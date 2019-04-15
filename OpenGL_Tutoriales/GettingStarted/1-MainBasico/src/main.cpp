#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

int main()
{
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


    //Inicializar GLAD (administra los punteros de OpenGL)
    //Nos da glfwGetProcAddress, donde se define la funcion dependiendo del Sistema operativo al compilar
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    //Viewport, tamanyo de la ventanta de renderizado, para que openGL pueda calcular y mostrar los datos en pantalla (mismo tamanyo que ventana GLFW)
    glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);  //glViewport(esq_inf_izquierda_x,esq_inf_izquierda_y,ancho,alto);

    //Se llama a la funcion "framebuffer_size_callback" cada vez que el usuario cambia el tamanyo de ventana
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    //Bucle de render
    while(!glfwWindowShouldClose(window))    //Comprueba al inicio de la iteracion si se ha ordenado cerrar GLFW, si es asi es TRUE y sale del bucle
    {
        //Input
        processInput(window);

        //Comandos de render
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f); //Designamos a el glClearColor un color
        glClear(GL_COLOR_BUFFER_BIT);         //Borrarmos en el buffer con el glClearColor designado

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
}

//Funcion para que cuando el usuario cambie el tamanyo de ventana, automaticamente esta cambie el viewport
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

