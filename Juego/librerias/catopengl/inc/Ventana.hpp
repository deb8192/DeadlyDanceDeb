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
        bool CrearVentana(int ,int ,bool ,const char * );//creamos la ventana
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

    private:

        ~Ventana();//destructor
        void draw();//intercambia buffers
        static void redimensionar(GLFWwindow * ,int ,int );//se llama cuando se redimensiona la ventana
        void procesarInputs(GLFWwindow *);//procesa los inputs si estan pulsados o no (teclado,raton)
        void limpiar();//como dice limpia el buffer y la informacion por pantalla
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

        static char tecla [30];//tecla que almacena cuando se recibe una tecla cuando se activa la recepcion de texto
        static bool recogido;//esta a true si se ha recogido, y a false si no
        bool cursor;// la line que te aparece y parpadea | 
        static unsigned int numTecla;

};
#endif
