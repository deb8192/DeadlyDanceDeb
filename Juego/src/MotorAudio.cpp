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

  //Cargar eventos
  FMOD::Studio::EventDescription* pEventInstance;
  ERRCHECK(pstudioSystem->getEvent("event:/Music/Level 01", &pEventInstance));
  if(pEventInstance)eventDescriptions["Level01"] = pEventInstance; //Insertar en el mapa de descripcion de eventos
  ERRCHECK(pstudioSystem->getEvent("event:/Music/Level 02", &pEventInstance));
  if(pEventInstance)eventDescriptions["Level02"] = pEventInstance;
  ERRCHECK(pstudioSystem->getEvent("event:/Music/Level 03", &pEventInstance));
  if(pEventInstance)eventDescriptions["Level03"] = pEventInstance;

 //***********EJEMPLO DE EJECUCION MUSICA*****************
  FMOD::Studio::EventInstance* eventInstance;
  ERRCHECK(eventDescriptions["Level02"]->createInstance(&eventInstance));
  ERRCHECK(eventInstance->start());

}

//Destructor
MotorAudioSystem::~MotorAudioSystem()
{
  ERRCHECK(pstudioSystem->unloadAll());
  ERRCHECK(pstudioSystem->release());
}

//Actualizar
void MotorAudioSystem::update(bool paused)
{
  //Actualizar systema, una vez por frame (si no estas en pausa)
  if(paused == false)ERRCHECK(pstudioSystem->update());
}
