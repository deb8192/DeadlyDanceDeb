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

    //Motor de audio
    MotorAudioSystem *motora = MotorAudioSystem::getInstance();
    motora->setListenerPosition(0.0f, 0.0f, 0.0f);
    //Reproducir evento
    motora->getEvent("Level02")->setVolume(1.0f);
    motora->getEvent("Level02")->setPosition(0.0f, 0.0f, 0.0f);
    motora->getEvent("Level02")->start();
    //Actualiza el motor de audio
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
