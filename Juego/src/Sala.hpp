#include <vector>

#ifndef Salas_HPP
#define Salas_HPP

class Sala
{
    public:
        Sala(int anch,int larg, int nx, int ny, int type);//se le pasa el el ancho(x) y largo(y)
        ~Sala(void);//destructor
        void agregarEntrada(Sala * plataforma);//agrega una plataforma de entrada a esta sala(su puntero)
        void agregarSalida(Sala * plataforma);//agrega una paltaforma de salida a esta sala(su puntero)
        int* getSizes ();//nos devuelve un array donde la primera posicion es el ancho la segunda la altura, tercera posicion en x, cuarta posicion en y
        int getType ();//nos devuelve el tipo de centro que tiene la plataforma o sala
        std::vector<Sala*> getEntradas();//devuelve las plataformas de entrada
        std::vector<Sala*> getSalidas();//devuelve las plataformas de salida
    private:
        int ancho,largo,x,y;//ancho y largo de la plataforma segun el tipo de centro se divide el espacio de una forma o otra. X e Y posicion en la que se encuentra en el mundo 3d
        int tipocentro;//esto es para saber si el centro de la figura esta en el centro(0), derecha-abajo(1), derecha-arriba(2), izquierda-abajo(3), izquierda-arriba(4) 
        std::vector<Sala*> entradas;//punteros a las diferentes salas de entrada
        std::vector<Sala*> salidas;//punteros a las diferentes salas de salida
};

#endif