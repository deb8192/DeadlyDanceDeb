#ifndef TMalla_HPP
#define TMalla_HPP

#include "TEntidad.hpp"

//recursos necesarios para tmalla
#include "RImagen.hpp"
#include "RMalla.hpp"

class TMalla : public TEntidad
{
    private:
        //punteros a recursos
        RMalla * objetos[250];//diferentes frames para animaciones
        RImagen * texturas[3];//3: textura, brillos, relieves

    public:
        // Constructor y destructor
        TMalla();
        ~TMalla();
        void remove();
        // Propiedades 
        void cargarMalla();
        
        // sobrecarga metodos TEntidad
        void beginDraw();
        void endDraw();

};

#endif
