#ifndef INnpc_HPP
#define INnpc_HPP
#include <iostream>

using namespace std;

//aqui definimos la clase interfaz de las entidades genericas (clases no virtuales)
class INnpc {

public:

    virtual int Atacar()=0;//efectua un ataque normal, llama al motor para ejecutar la animacion.
    //virtual void AtacarEspecial()=0;//efectua el ataque especial segun el tipo, esto llama a motor grafico para realizar la animacion, cuando se termina se pone a cero la barra
    virtual int AtacarEspecial()=0;//efectua el ataque especial segun el tipo, esto llama a motor grafico para realizar la animacion, cuando se termina se pone a cero la barra
    virtual void QuitarVida(int)=0;//quita vida a la entidad
    virtual void RecuperarVida(int)=0;//le suma vida a la entidad
    virtual void AumentarBarraAtEs(int)=0;//aumenta el valor de la barra de ataque critico
    virtual void Interactuar(int, int)=0;//llama a la mecanica de interactuar
    
    //set y gets

    virtual void setVida(int vid)=0;
    virtual void setTipo(int tip)=0;
    virtual void setBarraAtEs(int bar)=0;
    virtual void setAtaque(int ataq)=0;
    virtual void setSuerte(int suer)=0;
    virtual void setDanyoCritico(int danyoC)=0;
    virtual void setProAtaCritico(int probabilidad)=0;

    virtual int getVida()=0;
    virtual int getTipo()=0;
    virtual int getBarraAtEs()=0;
    virtual int getAtaque()=0;
    virtual int getSuerte()=0;
    virtual int getDanyoCritico()=0;
    virtual int getProAtaCritico()=0;
    virtual int* getBuffos()=0;

/*el protected es para que tenga acceso sus descendientes o parientes*/
protected:
    int tipo;//tipo de enemigo(mayor de cero) o jugador(0)
    int vida;//vida de la entida
    int barraAtEs;//barra que va de 0 a 100, cuando se 100 se puede ejecutar ataque especial.
    int ataque;//dano base que hace la entidad
    int suerte;//valor que determina la probabilidad de ataque critico y en el caso de jugador tambien de que suerte objetos
    int danyoCritico;//valor base del danyo anyadido a un golpe critico;
    int proAtaCritico;//valor que determina cuantas veces se hacen ataques criticos.
    int buffos[4];//1 aumento de vida, 2 aumento de ataque, 3 aumento de suerte, 4 aumento de pCritica.
    std::string malla; //malla 3d del personaje
    //Variables para el metodo morir
    float animacionMuerteTiem = 3000.0f;//tiempo de animacion del estado muerte para cualquier NPC
    float tiempoPasadoMuerte = 0;
};

#endif /* INnpc_HPP */
