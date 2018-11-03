#include "Estado.hpp"
#include "MotorGrafico.hpp"

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

void Jugando::Update()
{
    MotorGrafico *motor = MotorGrafico::getInstance();
    motor->updateMotorJuego();
    //prueba jose ramon para su rama
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

int Cinematica::Esta()
{
    return 3;
}