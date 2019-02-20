#ifndef INobjetos_HPP
#define INobjetos_HPP
#include <iostream>
#include <cstring>

using namespace std;

//aqui definimos la clase interfaz de los objetos(clases no abstractas)
class INobjetos
{
    public:
        virtual ~INobjetos() {
            delete nombreObjeto;
            delete ruta_objeto;
            delete ruta_textura;
            delete cadena_objeto;
            delete cadena_textura;
            delete cadena_nombre;
            ancho = 0;
            largo = 0;
            alto  = 0;
        };

    /*el protected es para que tenga acceso sus descendientes o parientes*/
    protected:    	
    	const char* nombreObjeto;
        const char* ruta_objeto; 
        const char* ruta_textura;
        char* cadena_objeto; 
        char* cadena_textura;
        char* cadena_nombre;
        float ancho, largo, alto; 
};

#endif /* INobjetos_HPP */