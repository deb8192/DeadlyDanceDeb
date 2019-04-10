#include "CatOpengl.hpp"//cuidado aqui se pone asi para no tener que poner la ruta ya va incluida en el programa de compilacion (make)

unsigned int Ventana::numTecla = 0;

char Ventana::tecla [30]; 

bool Ventana::recogido = false;

//USO: inicializa las variables
Ventana::Ventana()
{
    _window = nullptr;
}

//USO: borra los datos que no se borren correctamente por el sistema
Ventana::~Ventana()
{
    Drop();
}

//USO: se utiliza para crear una ventana
bool Ventana::CrearVentana(int h, int w, bool redimensionar,const char * titulo)
{
    winwidth = w;
    winheight = h;
    // Inicializar GLFW
    // glfwWindowHint para configurar GLFW, mirar en la documentacion los distintos hint
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);  //glfwWindowHint(opcion_hint,valor_hint);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_SAMPLES, 4); //MSAA x 4
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

    //Activar suavizado MSAA
    glEnable(GL_MULTISAMPLE);

    //Profundidad Z-Buffer
    glEnable(GL_DEPTH_TEST);   //Necesario para el zoom/fov

    //Activar Blending
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    //Activar CULLING
    glEnable(GL_CULL_FACE);
    glCullFace(GL_FRONT);
    glFrontFace(GL_CW);

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
    //PortaPapeles();
}

//USO: limpia toda la informacion de la ventana
//CUIDADO: esta funcion se llama preferentemente despues de cerrar la ventana.
void Ventana::Drop()
{
    if(_window != nullptr)
    {
        glfwTerminate();//limpiar todos los recursos en memoria de GLFW
        _window = nullptr;
    }
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
    /*if(glfwGetKey(_ventana, GLFW_KEY_ESCAPE) == GLFW_PRESS)  //Si pulsas Escape
    {
        glfwSetWindowShouldClose(_ventana, true);            //Cerrar GLFW
    }*/
}

void Ventana::limpiar()
{
    if(_window != nullptr)
    {
        //actualizar inputs(teclado y raton)
        procesarInputs(_window);

        //Comandos de render
        glClearColor(red, green, blue, alpha); //Designamos a el glClearColor un color
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);         //Borrarmos en el buffer con el glClearColor designado
    }
}

double * Ventana::RecuperarPosicionesMouse()
{
    if(_window != nullptr)
    {
        double * posiciones = new double[2];//se destruye en funcion de destino
        glfwGetCursorPos(_window,&posiciones[0],&posiciones[1]);
        return posiciones;
    }
    return nullptr;
}

void Ventana::CambiarColorFondo(float r, float g, float b,float a)
{
    red = r;
    green = g;
    blue = b;
    alpha = a;
}

void Ventana::UpdateTitle(const char * _title)
{
    if(_window != nullptr)
    {
        glfwSetWindowTitle(_window, _title);
    }
}

void Ventana::UpdateSize(short unsigned int w, short unsigned int h)
{
    if(_window != nullptr)
    {
        glfwSetWindowSize(_window, w, h);
    }
}

bool Ventana::EstaPulsada(short tecla)
{
    if(glfwGetKey(_window,tecla) == GLFW_PRESS)  //Si pulsas Escape
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool Ventana::MouseEstaPulsado(short boton)
{
    if(boton == 666)
    {
        double * datos = Ventana::RecuperarPosicionesMouse();

        if(MouseX != datos[0] || MouseY != datos[1])
        {
            MouseX = datos[0];
            MouseY = datos[1];
            return true;
        }

        delete datos;

    }
    else
    {
        if(glfwGetMouseButton(_window,boton) == GLFW_PRESS)
        {
            //se ha pulsado entonces devolvemos true
            return true;
        }
    }

    return false;
}

short unsigned int Ventana::getWidth()
{
    return winwidth;
}

short unsigned int Ventana::getHeight()
{
    return winheight;
}

void Ventana::Close()
{
    if(_window != nullptr)
    {    
        glfwSetWindowShouldClose(_window, true);
    }
}

bool Ventana::EstaLiberado(short tecla)
{
    if(glfwGetKey(_window,tecla) == GLFW_RELEASE)  //Si pulsas Escape
    {
        return true;
    }
    else
    {
        return false;
    }
    
}

/* void Ventana::PortaPapeles()
{
    const char* text = glfwGetClipboardString(_window);
    if (text)
    {
        std::cout << text << std::endl;
    }
}
 */

void Ventana::character_callback(GLFWwindow* window, unsigned int codepoint)
{
    if(numTecla < 30)
    {
        tecla[numTecla] = (char)codepoint;
        numTecla++;
        //std::cout << " Recogido: " << tecla << std::endl;
        recogido = false;
    }  
}

void Ventana::ActivarRecogida()
{
    glfwSetCharCallback(_window,this->character_callback);
    recogido = true;
    numTecla = 0;
    for(int i = 0; i < 30;i++)
    {
        tecla[i] = ' ';
    }

}

void Ventana::DesactivarRecogida()
{
    glfwSetCharCallback(_window,nullptr);
    recogido = true;
    numTecla = 0;
    for(int i = 0; i < 30;i++)
    {
        tecla[i] = ' ';
    }

}

char * Ventana::RecogerLetra()
{
    return tecla;
}

void Ventana::InicializarLetra(const char * letras)
{
    //inicializamos a los valores que hayan
    int longitud = strlen(letras);
    numTecla = longitud;
    for(int i = 0; i < 30 && i < longitud;i++)
    { 
        tecla[i] = letras[i];
    } 
}

void Ventana::BorrarUltimaTecla()
{
    if(numTecla != 0)
    {
        numTecla--;
        tecla[numTecla] = ' ';
    }
}