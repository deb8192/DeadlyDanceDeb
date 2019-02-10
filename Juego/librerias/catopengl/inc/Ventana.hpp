#ifndef Ventana_HPP
#define Ventana_HPP

class Ventana
{
    public:

        Ventana();//sirve para inicializar la ventana
        void Remove();//elimina la ventana
        bool CrearVentana(int ,int ,bool ,const char * );//creamos la ventana
        void UpdateFase1();//actualiza las teclas y limpia la pantalla
        void UpdateFase2();//renderizada la informacion y cambia los buffers
        bool SigueAbierta();//nos sirve para saber si la ventana sigue en ejecucion
        void Drop();//borramos la informacion de glfw

    private:

        ~Ventana();//destructor
        void draw();//intercambia buffers
        static void redimensionar(GLFWwindow * ,int ,int );//se llama cuando se redimensiona la ventana
        void procesarInputs(GLFWwindow *);//procesa los inputs si estan pulsados o no (teclado,raton)
        void limpiar();//como dice limpia el buffer y la informacion por pantalla
        GLFWwindow * _window;
};
#endif