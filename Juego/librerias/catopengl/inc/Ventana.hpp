#ifndef Ventana_HPP
#define Ventana_HPP

class Ventana
{
    public:

        Ventana();//sirve para inicializar la ventana
        void Remove();//elimina la ventana
        bool CrearVentana(int ,int ,bool ,const char * );//creamos la ventana
        void Update();//actualiza la ventana
        bool SigueAbierta();//nos sirve para saber si la ventana sigue en ejecucion
        void Drop();//borramos la informacion de glfw

    private:

        ~Ventana();//destructor
        void draw();//intercambia buffers
        static void redimensionar(GLFWwindow * ,int ,int );//se llama cuando se redimensiona la ventana
        void procesarInputs(GLFWwindow *);//procesa los inputs si estan pulsados o no (teclado,raton)

        GLFWwindow * _window;
};
#endif