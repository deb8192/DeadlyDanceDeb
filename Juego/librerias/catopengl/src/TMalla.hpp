#ifndef TMalla_HPP
#define TMalla_HPP

#include "TEntidad.hpp"

class TMalla : public TEntidad
{
    private:
        // Malla * malla;

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
