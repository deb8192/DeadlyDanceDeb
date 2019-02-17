#ifndef TNodo_HPP
#define TNodo_HPP

#include <vector>
#include "TEntidad.hpp"


class TNodo
{
    private:
        TEntidad * entidad;//funcion que cumple, si es nullptr es la raiz
        std::vector<TNodo*> hijos;//array de hijos
        TNodo * padre;// puntero al TNodo padre

        bool existeHijo(TNodo*);//comprueba si existe el hijo en array de hijos

    public:
        //destructor y constructor
        TNodo();
        ~TNodo();

        //funciones de propiedades
        int addHijo(TNodo*);//aqui se agrega un hijo al final del vector de hijos se devuelve su posicion
        int remHijo(TNodo*);//se elimina un hijo del vector de hijos
        bool setEntidad(TEntidad *);//se comprueba si es una entidad valida para la posicion
        TNodo * getPadre();//se devuelve el padre
        void setPadre(TNodo*);//se agrega el padre
        
        //pintado
        void draw();//se llama a las funciones de pintado

};

#endif


