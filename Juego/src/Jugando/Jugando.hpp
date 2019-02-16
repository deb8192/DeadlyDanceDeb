#ifndef JUGANDO_HPP
#define JUGANDO_HPP

#include "../Estado.hpp"
#include "../Motores/SenseEventos.hpp"
#include "../Motores/MotorAudio.hpp"
#include "../Motores/MotorGrafico.hpp"
#include "../CargadorNiveles.hpp"
#include "../Times.hpp"
#include "../Personajes/Jugador.hpp"
#include "Zona.hpp"

class Jugando: public Estado {
    public:
        Jugando();
        ~Jugando();

        //clase singleton en public
        static Jugando* GetInstance() //esto se utiliza para crear el objeto una sola vez
        {
            if(!_unica_instancia)
                _unica_instancia = new Jugando();
            return _unica_instancia;  
        }
        //fin singleton public

        // Funciones de Estado
        void Iniciar();
        void ManejarEventos();
        void Update(); // Se actualiza todo lo de nivel (interpolacion(cy-y)^2), posiciones, iluminacion)
        void UpdateIA(); // Se llama 4 veces por segundo
        void Render();//dibuja y actualiza las posiciones del interpolado
        
        void Vaciar();
        void Pausar();
        void Reanudar();
        void Reiniciar();

        //Funciones propias
        void ValoresPorDefecto();
        void ValoresPorDefectoJugador();

        bool CargarNivel(int level); //Niveles en assets/maps/xml/
        void CrearJugador(int accion, int x,int y,int z, int ancho, int largo, int alto, const char* ruta_objeto, const char *ruta_textura, int* propiedades);//lo utilizamos para crear su objeto
        Sala* CrearPlataforma(int accion, int x,int y,int z, int ancho, int largo, int alto, int centro, const char* ruta_objeto, const char* ruta_textura);//lo utilizamos para crear su modelo en motorgrafico y su objeto
        void CrearLuz(int x,int y,int z);
        void CrearZona(int accion,int x,int y,int z,int ancho,int largo,int alto, const char* tipo, int* propiedades); //lo usamos para crear zonas
        

    private:
        //clase singleton 
        static Jugando* _unica_instancia;
        //fin clase singleton private

        MotorAudioSystem* _motora;
        SenseEventos* _sense;
        MotorGrafico* _motor;
        MotorFisicas* _fisicas;
        Times* _controladorTiempo;

        CargadorNiveles cargador;//nos ayuda a cargar los niveles
        Sala* _primeraSala;// la primera sala del arbol
        
        //TO DO: cambiar a lista
        std::vector<Zona*> zonas; //Array de zonas

        bool reiniciando; // Se utiliza solo en Reanudar por el cambio entre Estados
        Jugador jugador;
        bool jugadorInmovil; // Para las colisiones
        float xIni, yIni, zIni; // Para reiniciar posJugador
        float drawTime, lastDrawTime;

        int id;//id para las figuras
};
#endif /* JUGANDO_HPP */