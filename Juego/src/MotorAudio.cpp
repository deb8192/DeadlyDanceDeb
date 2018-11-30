#include "MotorAudio.hpp"

MotorAudio* MotorAudio::maudio_instancia = 0;

//Comprobar errores en FMOD
void MotorAudio::ERRCHECK(FMOD_RESULT result)
{
  if (result != FMOD_OK){
     printf("FMOD error! (%d) %s\n", result, FMOD_ErrorString(result));
     exit(-1);
  }
}

//Constructor
MotorAudio::MotorAudio()
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

MotorAudio::~MotorAudio()
{

}

//Crear sonido
void MotorAudio::createSound(ClaseSonido *pSound, const char* pFile)
{
  ERRCHECK(plSystem->createSound(pFile, FMOD_3D, 0, pSound));
}

//Ejecutar sonido
void MotorAudio::playSound(ClaseSonido pSound)
{
  ERRCHECK(plSystem->playSound(pSound, 0, false, 0));
}

//Liberar sonido
void MotorAudio::releaseSound(ClaseSonido pSound)
{
  pSound->release();
}
