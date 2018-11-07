#ifndef INnpc_HPP
#define INnpc_HPP
#include <iostream>

using namespace std;

//aqui definimos la clase interfaz de las entidades genericas (clases no virtuales)
class INnpc {

public:

    virtual ~INnpc(){};
    virtual void Atacar(){cout << "Se realiza ataque normal generico" << endl;};//efectua un ataque normal, llama al motor para ejecutar la animacion.
    virtual void AtacarEspecial(){cout << "Se realiza ataque especial generico" << endl;};//efectua el ataque especial segun el tipo, esto llama a motor grafico para realizar la animacion, cuando se termina se pone a cero la barra 
    virtual void QuitarVida(int){};//quita vida a la entidad
    virtual void RecuperarVida(int){};//le suma vida a la entidad
    virtual void AumentarBarraAtEs(int){};//aumenta el valor de la barra de ataque critico 
    virtual void Interactuar(int, int){};//llama a la mecanica de interactuar
    
    //set y gets
    
    virtual void setVida(int vid){ vida = vid; };
    virtual void setTipo(int tip){ tipo = tip; };
    virtual void setBarraAtEs(int bar){ if(bar <= 100){barraAtEs=bar;}};
    virtual void setAtaque(int ataq){ataque = ataq;};
    virtual void setSuerte(int suer){suerte = suer;};
    virtual void setProAtaCritico(int probabilidad){if(probabilidad <= 100){proAtaCritico=probabilidad;}};
    
    virtual int getVida(){return vida;};
    virtual int getTipo(){return tipo;};
    virtual int getBarraAtEs(){return barraAtEs;};
    virtual int getAtaque(){return ataque;};
    virtual int getSuerte(){return suerte;};
    virtual int getProAtaCritico(){return proAtaCritico;};
    virtual int* getBuffos(){return buffos;};

/*el protected es para que tenga acceso sus descendientes o parientes*/
protected:
    int tipo;//tipo de enemigo(mayor de cero) o jugador(0)
    int vida;//vida de la entida
    int barraAtEs;//barra que va de 0 a 100, cuando se 100 se puede ejecutar ataque especial.
    int ataque;//dano base que hace la entidad  
    int suerte;//valor que determina la probabilidad de ataque critico y en el caso de jugador tambien de que suerte objetos 
    int proAtaCritico;//valor que determina cuantas veces se hacen ataques criticos.
    int buffos[4];//1 aumento de vida, 2 aumento de ataque, 3 aumento de suerte, 4 aumento de pCritica.
};

#endif /* INnpc_HPP */