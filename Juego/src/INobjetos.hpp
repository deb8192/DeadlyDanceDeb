#ifndef INobjetos_HPP
#define INobjetos_HPP
#include <iostream>

using namespace std;

//aqui definimos la clase interfaz de los objetos(clases no abstractas)
class INobjetos
{
    public:


    /*el protected es para que tenga acceso sus descendientes o parientes*/
    protected:    	
    	const char* nombreObjeto;
        const char* ruta_objeto; 
        const char* ruta_textura;
        float ancho, largo, alto; 
};

#endif /* INobjetos_HPP */