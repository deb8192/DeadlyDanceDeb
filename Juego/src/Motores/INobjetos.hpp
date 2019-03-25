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
        virtual unsigned short GetTipoObjeto()=0;

    /*el protected es para que tenga acceso sus descendientes o parientes*/
    protected:    	
    	const char * nombreObjeto;
        char* cadena_nombre;
        float ancho, largo, alto;
        unsigned short tipoObjeto;
};

#endif /* INobjetos_HPP */