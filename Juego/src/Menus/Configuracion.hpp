#ifndef CONFIGURACION_HPP
#define CONFIGURACION_HPP

#include "../Estado.hpp"
#include "../Jugando/Configuration.hpp"

class Configuracion: public Estado {
    public:
        Configuracion();
        ~Configuracion();
        
        void Iniciar();
        void Render();
        void Update();
        void ManejarEventos();

    private:
        void atras();
        void borrarResoluciones();//borra los desplegables de las resoluciones
        Configuration configuracion;
        unsigned int volAmbiente;
        unsigned int volEfectos;
        unsigned int volVoces;
        unsigned int heightScreen;
        unsigned int widthScreen;
        bool muteAll;
        bool vsync;
        bool suavizadoMsax1;
        unsigned int idsElementos[8];
        unsigned int resolucion[6];//contiene los desplegables de la resolucion
        
};
#endif /* CONFIGURACION_HPP */