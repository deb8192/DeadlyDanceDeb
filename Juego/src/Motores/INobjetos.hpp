#ifndef INobjetos_HPP
#define INobjetos_HPP
#include <iostream>
#include <cstring>

using namespace std;

//aqui definimos la clase interfaz de los objetos(clases no abstractas)
class INobjetos
{
    public:
        virtual ~INobjetos() = default;

    /*el protected es para que tenga acceso sus descendientes o parientes*/
    protected:    	
    	const char * nombreObjeto;
        const char * ruta_objeto; 
        const char * ruta_textura;
        char* cadena_objeto; 
        char* cadena_textura;
        char* cadena_nombre;
        float ancho, largo, alto; 
};

#endif /* INobjetos_HPP */