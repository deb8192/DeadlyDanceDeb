#ifndef Ventana_HPP
#define Ventana_HPP

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
};
#endif
