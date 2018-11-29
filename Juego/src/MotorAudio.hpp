#ifndef MOTOR_AUDIO_HPP
#define MOTOR_AUDIO_HPP

#include "fmod_studio.h"
#include "fmod_studio.hpp"
#include "fmod.hpp"
#include "fmod_errors.h"
#include <iostream>

//Clase sonido por defecto
typedef FMOD::Sound* ClaseSonido;

//Clase motor audio
class MotorAudio
{
  FMOD::Studio::System* pSystem = NULL;  //Puntero de instancia a FMOD
  FMOD::System *plSystem = NULL;         //Puntero de instancia low level

  //Comprobar errores en FMOD
  void ERRCHECK(FMOD_RESULT result)
  {
    if (result != FMOD_OK){
       printf("FMOD error! (%d) %s\n", result, FMOD_ErrorString(result));
       exit(-1);
    }
  }

public:
  //Constructor
  MotorAudio()
  {
    //Creamos el sistema
    ERRCHECK(FMOD::Studio::System::create(&pSystem));

    //Obtener LOW-level system
    ERRCHECK(pSystem->getLowLevelSystem(&plSystem));
    ERRCHECK(plSystem->setSoftwareFormat(0,FMOD_SPEAKERMODE_5POINT1, 0));
    ERRCHECK(plSystem->setOutput(FMOD_OUTPUTTYPE_AUTODETECT));

    //Inicializar la instancia con x canales
    ERRCHECK(pSystem->initialize(1024, FMOD_STUDIO_INIT_NORMAL, FMOD_INIT_NORMAL, 0));
  }

  void createSound(ClaseSonido *pSound, const char* pFile)
  {
     ERRCHECK(plSystem->createSound(pFile, FMOD_3D, 0, pSound));
  }

  void playSound(ClaseSonido pSound)
  {
     ERRCHECK(plSystem->playSound(pSound, 0, false, 0));
  }

  void releaseSound(ClaseSonido pSound)
  {
     pSound->release();
  }

};

#endif
