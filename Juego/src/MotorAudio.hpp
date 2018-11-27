#ifndef MOTOR_AUDIO_HPP
#define MOTOR_AUDIO_HPP

#include "fmod.hpp"

class MotorAudio
{
  //Puntero de instancia a FMOD
  FMOD::System *m_pSystem;
  MotorAudio(){}
}

//Clase sonido por defecto
typedef FMOD::Sound* ClaseSonido;

MotorAudio()
{
  //Si ya existe el sistema, error
  if(FMOD::System_Create(&m_pSystem) != FMOD_OK)
  {
    return; //error
  }

  //Contar los
  int driverCount = 0;
  m_pSystem->getNumDrivers(&driverCount)

  if/driverCount == 0)
  {
    return; //Error
  }
}

#endif
