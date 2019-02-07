#ifndef Ventana_HPP
#define Ventana_HPP

class Ventana
{
    public:

        Ventana();//sirve para inicializar la ventana
        void Remove();//elimina la ventana
        bool CrearVentana(int,int,bool,const char *);//creamos la ventana

    private:

        ~Ventana();//destructor
        GLFWwindow* window;
};
#endif