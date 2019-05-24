#ifndef Ventana_HPP
#define Ventana_HPP

#include <iostream>
#include <glad/glad.h>
#include <glfw3.h>
#include <glm.hpp>

class Ventana
{
    public:

        Ventana();//sirve para inicializar la ventana
        bool CrearVentana(int ,int ,bool ,const char *,bool screenFull = false);//creamos la ventana
        void UpdateLimpiar();//actualiza las teclas y limpia la pantalla
        void UpdateDraw();//renderizada la informacion y cambia los buffers
        bool SigueAbierta();//nos sirve para saber si la ventana sigue en ejecucion
        void Drop();//borramos la informacion de glfw
        double * RecuperarPosicionesMouse();//obtiene de la ventana donde se situa el mouse
        void CambiarColorFondo(float r,float g,float b,float a);//cambiar el color de fondo de la ventana
        void UpdateTitle(const char *);//cambia titulo de la ventana
        void UpdateSize(short unsigned int w, short unsigned int h);//cambia tamayo de la ventana
        bool EstaPulsada(short);//comprueba si la tecla esta pulsada
        bool EstaLiberado(short);//comprueba si la tecla no esta pulsada
        bool MouseEstaPulsado(short);//comprueba que este pulsado alguna tecla del raton o que se mueve
        bool MouseEstaLibre(short);//comprueba que este pulsado alguna tecla del raton o que se mueve
        //void PortaPapeles();
        //devolver tamanyos de la ventana
        short unsigned int getWidth();
        short unsigned int getHeight();

        //cierra la ventana
        void Close();

        //para recoger texto
        void DesactivarRecogida();//desactivamos la recogida de texto
        void ActivarRecogida();//activamos la recogida de texto

        //devuelve texto cuando esta activa la recogida
        char * RecogerLetra();//devuelve el texto que tiene en el momento el campo
        void InicializarLetra(const char * letras);//inicializa el texto con lo que le pases
        void BorrarUltimaTecla();//borra la ultima tecla
        
        //obtener informacion de la pantalla 
        int * GetSizeScreen();//Te devuelve las medidas de la pantalla [0] width [1] height
        int GetRelationAspectScreen();//Te devuelve 1 -> 16:9, 0 -> 4:3
        int GetFrameRate();//te devuelve el numero de fps a la que funciona el monitor
        void AllScreen();//pone el motor como pantalla completa
        void NoAllScreen();//desactiva modo completo

    private:

        ~Ventana();//destructor
        void draw();//intercambia buffers
        static void redimensionar(GLFWwindow * ,int ,int );//se llama cuando se redimensiona la ventana
        void procesarInputs(GLFWwindow *);//procesa los inputs si estan pulsados o no (teclado,raton)
        void limpiar();//como dice limpia el buffer y la informacion por pantalla
        void inicializarScreenParameter();
        GLFWwindow * _window;
        //color fondo
        float red = 0.0f;//rojo para el fondo
        float green = 0.0f;//verde para el fondo
        float blue = 0.0f;//azul para el fondo
        float alpha = 0.0f;//transparencia para el fondo
        //posicion raton actual
        double MouseX = 0;
        double MouseY = 0;

        short unsigned int winwidth = 0,winheight = 0;

        //para detectar las teclas que pulsa
        static void character_callback(GLFWwindow* window, unsigned int codepoint);

        static char * tecla;//tecla que almacena cuando se recibe una tecla cuando se activa la recepcion de texto
        static bool recogido;//esta a true si se ha recogido, y a false si no
        bool cursor;// la line que te aparece y parpadea | 
        static unsigned int numTecla;

        //monitor
        GLFWmonitor * monitorPrimario;//puntero a la estructura que guarda la informacion del monitos
        const GLFWvidmode* mode;//te da una estructura sencilla para obtener las dimensiones, colores y aspecratio
        int screenWidth,screenHeight;//dimensiones completas de la pantalla o monitos
        int aspectRatio;//tipo de pantalla panoramica(16/9) = 1, normal(4:3) = 0
        int frameRate;//framerate que soporta la pantalla
        //monitor en modo ventana
        int * screenWorkWidth; //son las dimensiones sin la barra del sistema
        int * screenWorkHeight; //son las dimensiones sin la barra del sistema
        int * posx;//donde empieza estas(screenWorkWidth,screenWorkHeight) dimensiones
        int * posy;//donde empieza estas(screenWorkWidth,screenWorkHeight) dimensiones
        //pantalla completa
        bool AllScreenB;

};
#endif
