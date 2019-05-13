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
  ERRCHECK(pstudioSystem->loadBankFile("assets/sounds/Ambient.bank", FMOD_STUDIO_LOAD_BANK_NORMAL, &pBank));
  if(pBank)banks["Ambient"] = pBank; //Insertar en el mapa de Bancos

  //Cargar eventos
  LoadEvent("event:/Musica/Musica-situacion estandar n1","Nivel1");
  LoadEvent("event:/Musica/Musica-situacion estandar n2","Nivel2");
  LoadEvent("event:/Musica/Musica-menu principal","Menu");

  LoadEvent("event:/SFX/SFX-Personaje Arpa golpea","Arpa");
  LoadEvent("event:/SFX/SFX-Arma flauta","Flauta");
  LoadEvent("event:/SFX/SFX-ruido coger objeto","Recoger");
  LoadEvent("event:/SFX/SFX-ruido dejar objeto","Soltar");
   LoadEvent("event:/SFX/SFX-Victoria en el puzzle","VictoriaPuzzle");
   LoadEvent("event:/SFX/SFX-Aparece puzzle en pantalla","AparecePuzzle");//error al cambiar estado
   LoadEvent("event:/SFX/SFX-Derrota en el puzzle","DerrotaPuzzle");
   LoadEvent("event:/SFX/SFX-Movimiento de piezas puzzle","MoverPieza");
   LoadEvent("event:/SFX/SFX-Boss derrotado","BossDerrota");
   LoadEvent("event:/SFX/SFX-Jugador derrotado","JugadorDerrota");//error al cambiar estado
   LoadEvent("event:/SFX/SFX-Dialogo tipo1","Dialogo1");//error al cambiar estado
   LoadEvent("event:/SFX/SFX-Dialogo tipo2","Dialogo2");
   LoadEvent("event:/SFX/SFX-Guardian sorpresa al encontrarlo","GuardianVisto");
  LoadEvent("event:/SFX/SFX-Personaje cabezazo del heavy","SinArma");
  LoadEvent("event:/SFX/SFX-Personaje Guitarra golpea","GolpeGuitarra");
  LoadEvent("event:/SFX/SFX-Personaje Guitarra Especial","GuitarraEspecial");
  LoadEvent("event:/SFX/SFX-Pollo Grito de alerta","Chicken2");
  LoadEvent("event:/SFX/SFX-Murcielago enfadado","Murci2");
  LoadEvent("event:/SFX/SFX-Objetos Chirrido de abrir puerta","AbrirPuerta");
  LoadEvent("event:/SFX/SFX-Objetos Cerrar puerta","CerrarPuerta");
  LoadEvent("event:/SFX/SFX-Objetos Romper pared","RomperPared");

  LoadEvent("event:/SFX/SFX-Objetos Abrir cerradura con llave","AbrirCerradura");
  LoadEvent("event:/Ambientes/Ambiente-Gritos de lamentos","AmbienteGritos");
  LoadEvent("event:/Ambientes/Ambiente-rio de lava","AmbienteLava");
  //LoadEvent("event:/Chicken1","Chicken1");

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

//Crear intancia de un evento
void MotorAudioSystem::LoadEvent(const char *path,std::string name)
{
  FMOD::Studio::EventDescription* pEventInstance;
  ERRCHECK(pstudioSystem->getEvent(path, &pEventInstance));
  if(pEventInstance)
  {
    eventDescriptions[name] = pEventInstance; //Insertar en el mapa de descripcion de eventos
    MotorAudioEvents.insert(pair<std::string, MotorAudioEvent*>(name,new MotorAudioEvent(pEventInstance)));
  }
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

//Reproducir instancia del evento
void MotorAudioEvent::start()
{
  ERRCHECK(soundInstance->start());
}

//Detener instancia del evento
void MotorAudioEvent::stop()
{
    ERRCHECK(soundInstance->stop(FMOD_STUDIO_STOP_IMMEDIATE));
}

//Pausar instancia del evento
void MotorAudioEvent::pause()
{
  ERRCHECK(soundInstance->setPaused(true));
}

//Modifica el volumen instancia del evento (entre 0 y 1)
void MotorAudioEvent::setVolume(float vol)
{
  ERRCHECK(soundInstance->setVolume(vol));
}

//Modifica el reverb
void MotorAudioEvent::setReverbLevel(int index, float level)
{
  ERRCHECK(soundInstance->setReverbLevel(index,level));
}

//Posicion 3D instancia del evento
void MotorAudioEvent::setPosition(float posx, float posy, float posz)
{
  FMOD_3D_ATTRIBUTES attributes = {{0}};
  attributes.forward.x = 1.0f;
  attributes.forward.y = 1.0f;
  attributes.forward.z = 1.0f;
  attributes.up.x = 1.0f;
  attributes.up.y = 1.0f;
  attributes.up.z = 1.0f;
  attributes.position.x = posx;
  attributes.position.y = posy;
  attributes.position.z = posz;
  ERRCHECK(soundInstance->set3DAttributes(&attributes));
}
