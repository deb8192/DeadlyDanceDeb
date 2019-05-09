#include "Cofre.hpp"
#include "../Motores/MotorFisicas.hpp"

// Constructor para cofres nuevos
Cofre::Cofre(bool esEne, int id,
    float x, float y, float z, unsigned int tipoObj,
    unsigned int posArana, Sala* sala, unsigned int posMotorG)
: Interactuable(id, -1, 0, 0, 0, //id,codigo,ancho,largo,alto
    x, y, z, tipoObj, 0, 0, 0) // despX, despZ, accion
{
    esArana = esEne;
    _estoy = sala;
    posArrayArana = posArana;
    ancho = 2;
    largo = 4;
    alto = 4;

    ModeloTextura();
    // No utilizar las posiciones devueltas de _motor y _fisicas porque los vectores son dinamicos
    /*posicionArrayObjetos = _motor->CargarObjetos(3,0,x,y,z,ancho,largo,alto,//2,2,2
        _modelo, _textura);*/
    posicionArrayObjetos = posMotorG;
    _motor->CargarCofre(-1,0,x,y,z,_modelo, _textura);

    // Creamos la fisica aqui por el tema del cofre nuevo o cofre ya existente
    MotorFisicas* _fisicas = MotorFisicas::getInstance();
    posObstaculos = _fisicas->CrearCuerpoInter(tipoObj,x/2,y/2,z/2,ancho,alto,largo,0,0);
    _fisicas = nullptr;
}

// Constructor para cofres ya existentes que son aranyas
Cofre::Cofre(int id, unsigned int posMotorG, unsigned int posObs,
    float x, float y, float z, unsigned int tipoObj,
    unsigned int posArana, Sala* sala)
: Interactuable(id, -1, 0, 0, 0, //id,codigo,ancho,largo,alto
    x, y, z, tipoObj, 0, 0, 0) // despX, despZ, accion
{
    esArana = true;
    _estoy = sala;
    posArrayArana = posArana;
    posObstaculos = posObs;
    ancho = 2;
    largo = 4;
    alto = 4;

    ModeloTextura();
    posicionArrayObjetos = posMotorG;
    _motor->CargarCofre(posMotorG,0,x,y,z,_modelo, _textura);
    
    MotorFisicas* _fisicas = MotorFisicas::getInstance();
    _fisicas->CargarCofre(posMotorG,posObs,x/2,y/2,z/2,ancho,alto,largo,0,0);
    _fisicas = nullptr;
}

void Cofre::ModeloTextura()
{
    _modelo = "assets/models/Cofre/cofre.obj";
    _textura = "assets/texture/cofreArana.png";
}

Cofre::~Cofre()
{
    _modelo = nullptr;
    _textura = nullptr;
    _estoy = nullptr;
    esArana=false;
    posArrayArana=0;
}

bool Cofre::GetEsArana()
{
    return esArana;
}

Sala* Cofre::GetSala()
{
    return _estoy;
}

unsigned int Cofre::GetPosArrayArana()
{
    return posArrayArana;
}

unsigned int Cofre::GetPosObs()
{
    return posObstaculos;
}

void Cofre::DesactivarCofre()
{
    // TO DO: Animacion abrir cofre y sonido de abrirse
    setNewRotacion(getRX(), getRY(), getRZ() - 80.0);
        
    accionado = !accionado;
    MotorFisicas* _fisicas = MotorFisicas::getInstance();
    _fisicas->DesactivarCofre(posicionArrayObjetos);
    _fisicas = nullptr;
}

void Cofre::BorrarCofre()
{
    // TO DO: Animacion sale arana y sonido de abrirse

    accionado = !accionado;
    MotorFisicas* _fisicas = MotorFisicas::getInstance();
    _fisicas->EraseCofre(posicionArrayObjetos, posObstaculos);
    _fisicas = nullptr;
    _motor->EraseCofre(posicionArrayObjetos);
}

void Cofre::ActivarCofre()
{
    // TO DO: Animacion de cofre cerrandose y sonido de cerrarse

    accionado = !accionado;
    _motor->CargarCofre(posicionArrayObjetos,0,
        posActual.x,posActual.y,posActual.z,
        _modelo, _textura);
    
    MotorFisicas* _fisicas = MotorFisicas::getInstance();
    _fisicas->CargarCofre(posicionArrayObjetos,posObstaculos,
        posActual.x/2,posActual.y/2,posActual.z/2,
        ancho,alto,largo,0,0);
    _fisicas = nullptr;
}


void Cofre::Render(float updTime, float drawTime)
{
    RotarEntidad(1 / updTime);
    UpdateTimeRotate(drawTime);

    _motor->mostrarCofres(
        posActual.x, posActual.y, posActual.z,
        rotActual.x, rotActual.y, rotActual.z,
        posicionArrayObjetos
    );
}