#include "MotorAudio.hpp"

MotorAudioSystem* MotorAudioSystem::maudio_instancia = 0;

//Constructor
MotorAudioSystem::MotorAudioSystem()
{
  //Creamos el sistema
  ERRCHECK(FMOD::Studio::System::create(&pstudioSystem));

  //Obtener LOW-level system
  ERRCHECK(pstudioSystem->getLowLevelSystem(&plowSystem));
  ERRCHECK(plowSystem->setSoftwareFormat(0,FMOD_SPEAKERMODE_5POINT1, 0));
  ERRCHECK(plowSystem->setOutput(FMOD_OUTPUTTYPE_AUTODETECT));

  //Inicializar la instancia con x canales
  ERRCHECK(pstudioSystem->initialize(1024, FMOD_STUDIO_INIT_NORMAL, FMOD_INIT_NORMAL, 0));

  //Cargar Banco Maestro
  ERRCHECK(pstudioSystem->loadBankFile("assets/sounds/Master Bank.bank", FMOD_STUDIO_LOAD_BANK_NORMAL, &masterBank));
  ERRCHECK(pstudioSystem->loadBankFile("assets/sounds/Master Bank.strings.bank", FMOD_STUDIO_LOAD_BANK_NORMAL, &stringsBank));

  //Cargar Bancos
  FMOD::Studio::Bank* pBank;
  ERRCHECK(pstudioSystem->loadBankFile("assets/sounds/Music.bank", FMOD_STUDIO_LOAD_BANK_NORMAL, &pBank));
  if(pBank)banks["Music"] = pBank; //Insertar en el mapa de Bancos
  ERRCHECK(pstudioSystem->loadBankFile("assets/sounds/SFX.bank", FMOD_STUDIO_LOAD_BANK_NORMAL, &pBank));
  if(pBank)banks["SFX"] = pBank; //Insertar en el mapa de Bancos

  //Cargar eventos
  FMOD::Studio::EventDescription* pEventInstance;
  ERRCHECK(pstudioSystem->getEvent("event:/Level 01", &pEventInstance));
cout << "Aqui todo bien" << endl;
  if(pEventInstance)
  {
    eventDescriptions["Level01"] = pEventInstance; //Insertar en el mapa de descripcion de eventos
    MotorAudioEvents.insert(pair<std::string, MotorAudioEvent*>("Level01",new MotorAudioEvent(pEventInstance)));
  }
  ERRCHECK(pstudioSystem->getEvent("event:/Level 02", &pEventInstance));
  if(pEventInstance)
  {
    eventDescriptions["Level02"] = pEventInstance; //Insertar en el mapa de descripcion de eventos
    MotorAudioEvents.insert(pair<std::string, MotorAudioEvent*>("Level02",new MotorAudioEvent(pEventInstance)));
  }
  ERRCHECK(pstudioSystem->getEvent("event:/Level 03", &pEventInstance));
  if(pEventInstance)
  {
    eventDescriptions["Level03"] = pEventInstance; //Insertar en el mapa de descripcion de eventos
    MotorAudioEvents.insert(pair<std::string, MotorAudioEvent*>("Level03",new MotorAudioEvent(pEventInstance)));
  }
  ERRCHECK(pstudioSystem->getEvent("event:/Bow", &pEventInstance));
  if(pEventInstance)
  {
    eventDescriptions["Bow"] = pEventInstance; //Insertar en el mapa de descripcion de eventos
    MotorAudioEvents.insert(pair<std::string, MotorAudioEvent*>("Bow",new MotorAudioEvent(pEventInstance)));
  }

 //***********EJEMPLO DE EJECUCION MUSICA*****************
  // FMOD::Studio::EventInstance* eventInstance;
  // ERRCHECK(eventDescriptions["Level02"]->createInstance(&eventInstance));
  // ERRCHECK(eventInstance->start());

}

//Destructor
MotorAudioSystem::~MotorAudioSystem()
{
  ERRCHECK(pstudioSystem->unloadAll());
  ERRCHECK(pstudioSystem->release());
}

MotorAudioEvent* MotorAudioSystem::getEvent(std::string name)
{
  map<std::string, MotorAudioEvent*>::iterator motorfound;
  motorfound = MotorAudioEvents.find(name);
  return motorfound->second;
}

//Posicion del punto de escucha
void MotorAudioSystem::setListenerPosition(float posx, float posy, float posz)
{
  FMOD_3D_ATTRIBUTES attributes = {{0}};
  attributes.forward.z = 1.0f;
  attributes.up.y = 1.0f;
  attributes.position.x = posx;
  attributes.position.y = posy;
  attributes.position.z = posz;
  ERRCHECK(pstudioSystem->setListenerAttributes(0, &attributes));
}

//Actualizar
void MotorAudioSystem::update(bool paused)
{
  //Actualizar systema, una vez por frame (si no estas en pausa)
  if(paused == false)ERRCHECK(pstudioSystem->update());
}

//**********************************************
//********** MOTOR AUDIO EVENTOS ***************
//**********************************************

//Constructor
MotorAudioEvent::MotorAudioEvent(FMOD::Studio::EventDescription* eventdesc)
{
  ERRCHECK(eventdesc->createInstance(&soundInstance));
}

//Destructor
MotorAudioEvent::~MotorAudioEvent()
{

}

//Reproducir el evento
void MotorAudioEvent::start()
{
  ERRCHECK(soundInstance->start());
  //ERRCHECK(soundInstance->setPaused(false));
}

//Detener el evento
void MotorAudioEvent::stop()
{
    ERRCHECK(soundInstance->stop(FMOD_STUDIO_STOP_IMMEDIATE));
}

//Pausar el evento
void MotorAudioEvent::pause()
{
  ERRCHECK(soundInstance->setPaused(true));
}

//Modifica el volumen del evento (entre 0 y 1)
void MotorAudioEvent::setVolume(float vol)
{
  ERRCHECK(soundInstance->setVolume(vol));
}

//Posicion 3D del evento
void MotorAudioEvent::setPosition(float posx, float posy, float posz)
{
  FMOD_3D_ATTRIBUTES attributes = {{0}};
  attributes.forward.z = 1.0f;
  attributes.up.y = 1.0f;
  attributes.position.x = posx;
  attributes.position.y = posy;
  attributes.position.z = posz;
  ERRCHECK(soundInstance->set3DAttributes(&attributes));
}

//Si el evento esta sonando
bool MotorAudioEvent::isPlaying()
{
  // FMOD_STUDIO_PLAYBACK_STATE* stateplay = NULL;
  // ERRCHECK(soundInstance->getPlaybackState(stateplay));
  // if(*stateplay == FMOD_STUDIO_PLAYBACK_PLAYING)
  // {
  //   return true;
  // }
   return false;
}
