#include "fmod_studio.hpp"
#include "fmod.hpp"
#include "fmod_errors.h"
#include <map>
#include <string>
#include <vector>
#include <math.h>
#include <iostream>

using namespace std;

#ifndef _MOTOR_AUDIO_HPP
#define _MOTOR_AUDIO_HPP

//Vector de 3 dimensiones
struct Vector3 {
    float x;
    float y;
    float z;
};

class MotorAudioEvent;

//Clase motor audio
struct MotorAudioSystem
{
    ~MotorAudioSystem(void);
    //Clase Singleton
    static MotorAudioSystem *getInstance()
    {
        if(maudio_instancia == 0)
          maudio_instancia = new MotorAudioSystem();
        return maudio_instancia;
    }

    MotorAudioEvent* getEvent(std::string name);                   //Devuelve el evento con un nombre
    void setListenerPosition(float posx, float posy, float posz);  //posicion del punto de escucha
    void update(bool paused);                                      //Actualizar motor

    //Comprobar errores en FMOD
    void ERRCHECK(FMOD_RESULT result)
    {
      if (result != FMOD_OK){
         printf("FMOD error! (%d) %s\n", result, FMOD_ErrorString(result));
         exit(-1);
      }
    }

  private:

    MotorAudioSystem();                           //Singleton
    static MotorAudioSystem* maudio_instancia;

    FMOD::Studio::System* pstudioSystem;          //Puntero de instancia a FMOD
    FMOD::System *plowSystem;                     //Puntero de instancia low level
    FMOD::Studio::Bank* masterBank;               //Puntero de Banko maestro
  	FMOD::Studio::Bank* stringsBank;              //Puntero de Banko maestro string
    std::map<std::string, FMOD::Studio::Bank*> banks;       //Mapa de bancos
    std::map<std::string, FMOD::Studio::EventDescription*> eventDescriptions;  //Mapa de descripcion de eventos
    std::map<std::string, MotorAudioEvent*> MotorAudioEvents;                  //Mapa con MotorAudioEvents
};

//Motor de audio de eventos
class MotorAudioEvent
{
  public:
    MotorAudioEvent(FMOD::Studio::EventDescription* eventdesc);
    ~MotorAudioEvent();

    void start();                  //Reproducir el evento
    void stop();                   //Detener el evento
    void pause();                  //Pausar el evento, start() continuar reproduccion
    void setVolume(float vol);     //Modifica el volumen del evento (entre 0 y 1)
    void setPosition(float posx, float posy, float posz); //Posicion 3D del evento
    bool isPlaying();              //Si el evento esta sonando

    //Comprobar errores en FMOD
    void ERRCHECK(FMOD_RESULT result)
    {
      if (result != FMOD_OK){
         printf("FMOD error! (%d) %s\n", result, FMOD_ErrorString(result));
         exit(-1);
      }
    }

  private:
    FMOD::Studio::EventInstance* soundInstance;
};

#endif
