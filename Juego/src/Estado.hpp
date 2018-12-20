#ifndef ESTADO_HPP
#define ESTADO_HPP
#include <iostream>

#include "Puzzle.hpp" // Para pruebas puzzles
#include "PilaFichas.hpp"
#include <stack> // para la pila de fichas

//aqui definimos la clase interfaz de los estados
class Estado {
private:
    //funciones que tiene la interfaz como virtual (porque no existen pero deberian)
    virtual void Draw() = 0;
    virtual void Clean() = 0;
    virtual void Update() = 0;
    virtual int Esta() = 0;
    virtual void Init() = 0;

public:
    void Pintar(){ Draw(); };
    void Borrar(){ Clean(); };
    void Actualizar(){ Update(); };
    int QueEstado(){ return Esta(); };
    void Ini(){Init();};
};

//diferentes clases de estado
//verdaderamente no se necesitarian mas clases si el menu contiene todas sus ventanas y el juego
//tiene pause
class Menu: public Estado{
    private:
        void Draw();
        void Clean();
        void Update();
        int Esta();
        void Init();
        //MotorGrafico *motor = MotorGrafico::getInstance();
};

class Jugando: public Estado{
    private:
        void Draw();
        void Clean();
        void Update();
        int Esta();
        void Init();
        //MotorGrafico *motor = MotorGrafico::getInstance();
};

class Cinematica: public Estado{
    private:
        void Draw();
        void Clean();
        void Update();
        int Esta();
        void Init();

        //MotorGrafico *motor = MotorGrafico::getInstance();
};

// Estado de pruebas para los puzzles
class Puzzles: public Estado{
    public:
        void Iniciar();
        void CrearFichasPila();
        void AsignarPuzzle(Puzzle p);
        short GetTipo();
        std::string GetEnunciado();
        short GetOpciones();
        short GetSolucion();
    private:
        void Draw();
        void Clean();
        void Update();
        int Esta();
        void Init();


        void ComprobarEventosOpciones();
        void ComprobarEventosHanoi();
        void DeseleccionarNodo();
        bool ComprobarPilaVacia(short pila);
        bool ComprobarTopPila(short fichaY);
        bool ComprobarTamanyo();
        short RecolocarFicha();
        void SacarFicha();
        short MeterFicha();
        void ReiniciarPilas();
        void ComprobarGanar();

        //MotorGrafico *motor = MotorGrafico::getInstance();
        Puzzle puzzle;
        bool pulsado=false;
        enum opcPuzzles { P_OPCIONES = 1, P_HANOI = 2 };
        enum posZ { IZQ=-9, CENTRO=0, DER=9, NO_SELECT=-1 };

        // Pilas de fichas
        stack <PilaFichas*> pilaIzq;
        stack <PilaFichas*> pilaCentro;
        stack <PilaFichas*> pilaDer;
        PilaFichas* ficha;
        short pasos, pilaInicial, pilaFinal;
};

#endif /* ESTADO_HPP */
