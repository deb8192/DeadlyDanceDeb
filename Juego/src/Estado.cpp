#include "Estado.hpp"
#include "Pathfinder.hpp"
#include "MotorGrafico.hpp"
#include "Enemigo.hpp"
#include "Nivel.hpp"

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
    Nivel *nivel = Nivel::getInstance();//se recoge la instancia de nivel
    motor->updateMotorJuego();
    Pathfinder path;
    vector <struct Pathfinder::NodeRecord> camino = path.encontrarCamino(nivel->getPrimerEnemigo().getSala(), nivel->getPrimeraSala());
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