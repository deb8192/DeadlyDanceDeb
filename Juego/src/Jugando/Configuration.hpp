#ifndef Configuration_HPP
#define Configuration_HPP

#include <iostream>
#include <fstream>
#include <cstring>

class Configuration
{
    public:
        
        Configuration();
        void GuardarConfiguracion(const char * ruta);
        bool CargarConfiguracion(const char * ruta);
        void SetConfiguracion(unsigned int,unsigned int,unsigned int,unsigned int,unsigned int,bool,bool,bool);
        unsigned int GetVolAmbiente();
        unsigned int GetVolEfectos();
        unsigned int GetVolVoces();
        unsigned int GetHeight();
        unsigned int GetWidth();
        bool GetMuteAll();
        bool GetVsync();
        bool GetSuavizadoMsaX1();
        

    private:

        struct Configuracion
        {
            unsigned int volAmbiente;
            unsigned int volEfectos;
            unsigned int volVoces;
            unsigned int heightScreen;
            unsigned int widthScreen;
            bool muteAll;
            bool vsync;
            bool suavizadoMsax1;
        };

        Configuracion configuracion;

};

#endif