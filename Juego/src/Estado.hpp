#ifndef ESTADO_HPP
#define ESTADO_HPP
#include <iostream>

//aqui definimos la clase interfaz de los estados
class Estado {
private:
    //funciones que tiene la interfaz como virtual (porque no existen pero deberian)
    virtual void Draw() = 0;
    virtual void Clean() = 0;
    virtual int Esta() = 0;    
public:
    void Pintar(){ Draw(); };
    void Borrar(){ Clean(); };
    int QueEstado(){ return Esta(); };
};

//diferentes clases de estado
//verdaderamente no se necesitarian mas clases si el menu contiene todas sus ventanas y el juego
//tiene pause
class Menu: public Estado{
    private:
        void Draw();
        void Clean();
        int Esta();
};

class Jugando: public Estado{
    private:
        void Draw();
        void Clean();
        int Esta();
};

class Cinematica: public Estado{
    private:
        void Draw();
        void Clean();
        int Esta();
};

#endif /* ESTADO_HPP */