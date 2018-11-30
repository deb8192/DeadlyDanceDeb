#ifndef MOTOR_AUDIO_HPP
#define MOTOR_AUDIO_HPP

#include "fmod_studio.hpp"
#include "fmod.hpp"
#include "fmod_errors.h"
#include <iostream>

//Clase sonido por defecto
typedef FMOD::Sound* ClaseSonido;

//Clase motor audio
struct MotorAudio
{
    ~MotorAudio(void);
    static MotorAudio *getInstance()
    {
        if(maudio_instancia == 0)
        maudio_instancia = new MotorAudio();
        return maudio_instancia;
    }
    void createSound(ClaseSonido *pSound, const char* pFile);   //Crear sonido
    void playSound(ClaseSonido pSound);                         //Ejecutar sonido
    void releaseSound(ClaseSonido pSound);                      //Liberar sonido

  private:

    FMOD::Studio::System* pSystem;      //Puntero de instancia a FMOD
    FMOD::System *plSystem;             //Puntero de instancia low level
    void ERRCHECK(FMOD_RESULT result);  //Comprobar errores en FMOD
    MotorAudio();                       //Singleton
    static MotorAudio* maudio_instancia;


};

#endif
