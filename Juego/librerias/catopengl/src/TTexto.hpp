#ifndef TTexto_HPP
#define TTexto_HPP

#include <map>

#include <ft2build.h>
#include FT_FREETYPE_H

#include "TEntidad.hpp"

class TTexto : public TEntidad
{
    private:


    public:
        // Constructor y destructor
        TTexto();
        ~TTexto();

        // sobrecarga metodos TEntidad
        void beginDraw();
        void endDraw();
};

#endif
