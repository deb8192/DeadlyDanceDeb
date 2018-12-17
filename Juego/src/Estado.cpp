#include "Estado.hpp"
#include "Pathfinder.hpp"
//#include "MotorGrafico.hpp"
#include "SenseEventos.hpp"
//#include "Nivel.hpp"
#include "Enemigo.hpp"
#include "MotorAudio.hpp"

void Menu::Draw()
{
    //contiene los pintados del menu
}

void Menu::Clean()
{
    //se pintan los menus
}

void Menu::Update()
{
    MotorGrafico *motor = MotorGrafico::getInstance();
    motor->updateMotorMenu();

    //Actualiza el motor de audio
    MotorAudioSystem *motora = MotorAudioSystem::getInstance();
    motora->update(false);
}

void Menu::Init()
{

}

int Menu::Esta()
{
    return 1;
}

void Jugando::Draw()
{
    //se llaman a los draw de los diferentes objetos
}

void Jugando::Clean()
{
    //se borran los objetos y escenarios
}

void Jugando::Init()
{
    MotorGrafico *motor = MotorGrafico::getInstance();
    motor->CrearCamara();
}

void Jugando::Update()
{
    MotorGrafico *motor = MotorGrafico::getInstance();
    motor->clearDebug();
    Nivel *nivel = Nivel::getInstance();
    SenseEventos *sense = SenseEventos::getInstance();
    sense->update();//se actualizan sentidos
    nivel->update();//se actualiza posiciones y interpolado
    motor->updateMotorJuego();// se actualiza lo que se ve por pantalla
    
    //Actualiza el motor de audio
    MotorAudioSystem *motora = MotorAudioSystem::getInstance();
    motora->update(false);

    //Prueba de Patfinder y ataque especial
    std::vector <Enemigo*> enemigos = nivel->getEnemigos();
    if(motor->estaPulsado(8))
    {
        Pathfinder path;
        vector <struct Pathfinder::NodeRecord> camino = path.encontrarCamino(enemigos.at(1)->getSala(), nivel->getPrimeraSala());
    }
}

int Jugando::Esta()
{
    return 2;
}

void Cinematica::Draw()
{
    //em
}

void Cinematica::Clean()
{
    //em
}

void Cinematica::Update()
{
    MotorGrafico *motor = MotorGrafico::getInstance();
    motor->updateMotorCinematica();
}
void Cinematica::Init()
{

}
int Cinematica::Esta()
{
    return 3;
}
