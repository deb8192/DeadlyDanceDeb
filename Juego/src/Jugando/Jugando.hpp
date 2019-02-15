#ifndef JUGANDO_HPP
#define JUGANDO_HPP

#include "../Estado.hpp"
#include "../Personajes/Jugador.hpp"
#include "../Motores/SenseEventos.hpp"
#include "../Motores/MotorAudio.hpp"
#include "../Motores/MotorGrafico.hpp"
#include "../CargadorNiveles.hpp"

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
        void Render();
        void Update();
        void UpdateIA();
        void ManejarEventos();
        void Vaciar();
        void Pausar();
        void Reanudar();
        void Reiniciar();

        //Funciones propias
        bool CargarNivel(int level);

        void CrearJugador(int accion, int x,int y,int z, int ancho, int largo, int alto, const char* ruta_objeto, const char *ruta_textura, int* propiedades);//lo utilizamos para crear su objeto
        Sala* CrearPlataforma(int accion, int x,int y,int z, int ancho, int largo, int alto, int centro, const char* ruta_objeto, const char* ruta_textura);//lo utilizamos para crear su modelo en motorgrafico y su objeto
        

    private:
        //clase singleton 
        static Jugando* _unica_instancia;
        //fin clase singleton private

        MotorAudioSystem* _motora;
        SenseEventos* _sense;
        MotorGrafico* _motor;
        MotorFisicas* _fisicas;

        CargadorNiveles cargador;//nos ayuda a cargar los niveles
        Sala* _primeraSala;// la primera sala del arbol
        
        bool reiniciando;
        Jugador jugador;

        int id;//id para las figuras
};
#endif /* JUGANDO_HPP */