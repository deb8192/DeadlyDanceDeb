#include "Estado.hpp"
#include "MotorGrafico.hpp"
#include "MotorAudio.hpp"
using namespace std;
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

    //Actualiza el motor de audio
    MotorAudioSystem *motora = MotorAudioSystem::getInstance();
    motora->update(false);

    // Release the sound
    // sound.releaseSound(soundSample);

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
