#ifndef ESTADO_HPP
#define ESTADO_HPP
#include <iostream>

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

#endif /* ESTADO_HPP */