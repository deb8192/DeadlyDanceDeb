#ifndef MOTOR_AUDIO_HPP
#define MOTOR_AUDIO_HPP

#include "fmod.hpp"

class MotorAudio
{
  //Puntero de instancia a FMOD
  FMOD::System *pSystem;
  MotorAudio(){}
}

//Clase sonido por defecto
typedef FMOD::Sound* ClaseSonido;

MotorAudio()
{
  //Si ya existe el sistema, error
  if(FMOD::System_Create(&pSystem) != FMOD_OK)
  {
    return; //error
  }

  //Si el PC tiene algun driver de sonido
  int driverCount = 0;
  pSystem->getNumDrivers(&driverCount)

  //Si el PC no tiene driver de sonido
  if(driverCount == 0)
  {
    return; //Error
  }

  //Inicializar la instancia con 36 canales
  pSystem->init(36, FMOD_INIT_NORMAL, NULL);
}

//Crear sonido (puntero de ClaseSonido, ruta del archivo)
void crearSonido(ClaseSonido *pSound, const char* pFile)
 {
    pSystem->crearSonido(pFile, FMOD_HARDWARE, 0, pSound);
 }

//Reproducir sonido (sonido, sonido en bucle o no)
 void playSonido(ClaseSonido pSound, bool bucle = false)
  {
     //Sonido 1 vez
     if (!bucle)
        pSound->setMode(FMOD_LOOP_OFF);
     else
     //Sonido en bucle
     {
        pSound->setMode(FMOD_LOOP_NORMAL);
        pSound->setLoopCount(-1); //Contador de bucles ilimitado
     }

     //Sonido en un canal libre
     m_pSystem->playSound(FMOD_CHANNEL_FREE, pSound, false, 0);
  }

  //Liberar el sonido
  void liberarSonido(SoundClass pSound)
  {
    pSound->release();
  }
#endif
