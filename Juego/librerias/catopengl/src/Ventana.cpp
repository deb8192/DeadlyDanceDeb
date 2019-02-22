#include "CatOpengl.hpp"//cuidado aqui se pone asi para no tener que poner la ruta ya va incluida en el programa de compilacion (make)

//USO: inicializa las variables
Ventana::Ventana()
{
    std::cout << "inicializar ventana" << std::endl;
    _window = nullptr;
}

//USO: borra los datos que no se borren correctamente por el sistema
Ventana::~Ventana()
{

}

//USO: llama al destructor de la ventana
void Ventana::Remove()
{
    this->~Ventana();
}

//USO: se utiliza para crear una ventana
bool Ventana::CrearVentana(int h, int w, bool redimensionar,const char * titulo)
{
    std::cout << "valores: " << h << " " << w << "" << titulo << std::endl;

    // Inicializar GLFW
    // glfwWindowHint para configurar GLFW, mirar en la documentacion los distintos hint
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);  //glfwWindowHint(opcion_hint,valor_hint);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); //Solo para OS X

    //Creamos una ventana
    _window = glfwCreateWindow(w, h,titulo, NULL, NULL);  //glfwCreateWindow(ancho,alto,nombre,NULL,NULL)

    if (_window == NULL) //si no se crea el objeto ventana, error
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        Drop();
        return false;
    }

    glfwMakeContextCurrent(_window);  //Hacer el contexto principal este objeto ventana
    //Inicializar GLAD (administra los punteros de OpenGL)
    //Nos da glfwGetProcAddress, donde se define la funcion dependiendo del Sistema operativo al compilar
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return false;
    }

    //Viewport, tamanyo de la ventanta de renderizado, para que openGL pueda calcular y mostrar los datos en pantalla (mismo tamanyo que ventana GLFW)
    glViewport(0, 0, w, h);  //glViewport(esq_inf_izquierda_x,esq_inf_izquierda_y,ancho,alto);

    //Se llama a la funcion "framebuffer_size_callback" cada vez que el usuario cambia el tamanyo de ventana
    glfwSetFramebufferSizeCallback(_window,this->redimensionar);

    return true;
}

//USO: comprueba que esta ventana este abierta
//SALIDAS: si la ventana esta abierta = true, si esta cerrada = false
bool Ventana::SigueAbierta()
{
    if(!glfwWindowShouldClose(_window))
    {
        return true;
    }
    return false;
}

//USO: sirve para limpiar el buffer y cambiar el color ambiente
void Ventana::draw()
{
    //Comprobar y llamar eventos, cambiar buffers
    glfwSwapBuffers(_window);             //Intercambia los buffer de la ventana
    glfwPollEvents();
}

//USO: sirve para unificar el update general de la ventana(se llaman a las diferentes funciones necesarias para actualizar la ventana)
void Ventana::UpdateLimpiar()
{
    limpiar();
}

//USO: llamamos a pintar buffers
void Ventana::UpdateDraw()
{
    draw();
}

//USO: limpia toda la informacion de la ventana
//CUIDADO: esta funcion se llama preferentemente despues de cerrar la ventana.
void Ventana::Drop()
{
    glfwTerminate();//limpiar todos los recursos en memoria de GLFW
    _window = nullptr;
}

//USO: se llama automaticamente cuando se redimensiona la pantalla, sirve para redimensionar la pantalla
//Entradas: _ventana = instancia de la ventana, width = ancho nuevo, height = alto nuevo
void Ventana::redimensionar(GLFWwindow * _ventana, int width, int height)
{
    glViewport(0, 0, width, height);
}

//USO: revisa los inputs para ponerlos como pulsados o no pulsados
void Ventana::procesarInputs(GLFWwindow * _ventana)
{
    if(glfwGetKey(_ventana, GLFW_KEY_ESCAPE) == GLFW_PRESS)  //Si pulsas Escape
    {
        glfwSetWindowShouldClose(_ventana, true);            //Cerrar GLFW
    }
}


void Ventana::limpiar()
{
    //actualizar inputs(teclado y raton)
    procesarInputs(_window);

    //Comandos de render
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f); //Designamos a el glClearColor un color
    glClear(GL_COLOR_BUFFER_BIT);         //Borrarmos en el buffer con el glClearColor designado
}
