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
  ERRCHECK(pstudioSystem->loadBankFile("assets/sounds/Dialogos.bank", FMOD_STUDIO_LOAD_BANK_NORMAL, &pBank));
  if(pBank)banks["Dialogos"] = pBank; //Insertar en el mapa de Bancos

  //Cargar eventos
  LoadEvent("event:/Musica/Musica-situacion estandar n1","Nivel1",0);
  LoadEvent("event:/Musica/Musica-situacion estandar n2","Nivel2",0);
  LoadEvent("event:/Musica/Musica-menu principal","Menu",0);
  LoadEvent("event:/Ambientes/Ambiente-Gritos de lamentos","AmbienteGritos",0);
  LoadEvent("event:/Ambientes/Ambiente-rio de lava","AmbienteLava",0);

  LoadEvent("event:/SFX/SFX-Personaje Arpa golpea","Arpa",1);
  LoadEvent("event:/SFX/SFX-Arma flauta","Flauta",1);
  LoadEvent("event:/SFX/SFX-ruido coger objeto","Recoger",1);
  LoadEvent("event:/SFX/SFX-ruido dejar objeto","Soltar",1);
   LoadEvent("event:/SFX/SFX-Victoria en el puzzle","VictoriaPuzzle",1);
   LoadEvent("event:/SFX/SFX-Aparece puzzle en pantalla","AparecePuzzle",1);//error al cambiar estado
   LoadEvent("event:/SFX/SFX-Derrota en el puzzle","DerrotaPuzzle",1);
   LoadEvent("event:/SFX/SFX-Movimiento de piezas puzzle","MoverPieza",1);
   LoadEvent("event:/SFX/SFX-Boss derrotado","BossDerrota",1);
   LoadEvent("event:/SFX/SFX-Jugador derrotado","JugadorDerrota",1);//error al cambiar estado
   LoadEvent("event:/SFX/SFX-Dialogo tipo1","Dialogo1",1);//error al cambiar estado
   LoadEvent("event:/SFX/SFX-Dialogo tipo2","Dialogo2",1);
   LoadEvent("event:/SFX/SFX-Guardian sorpresa al encontrarlo","GuardianVisto",1);
  LoadEvent("event:/SFX/SFX-Personaje cabezazo del heavy","SinArma",1);
  LoadEvent("event:/SFX/SFX-Personaje Guitarra golpea","GolpeGuitarra",1);
  LoadEvent("event:/SFX/SFX-Personaje Guitarra Especial","GuitarraEspecial",1);
  LoadEvent("event:/SFX/SFX-Pollo Grito de alerta","Chicken2",1);
  LoadEvent("event:/SFX/SFX-Murcielago enfadado","Murci2",1);
  LoadEvent("event:/SFX/SFX-Objetos Chirrido de abrir puerta","AbrirPuerta",1);
  LoadEvent("event:/SFX/SFX-Objetos Cerrar puerta","CerrarPuerta",1);
  LoadEvent("event:/SFX/SFX-Objetos Romper pared","RomperPared",1);
  LoadEvent("event:/SFX/SFX-Objetos Abrir cerradura con llave","AbrirCerradura",1);

  LoadEvent("event:/Diálogos/Dialogo-Muerte Omnipresente jugador debil","MuerteEstasDebil",2);
  LoadEvent("event:/Diálogos/Dialogo-Muerte Omnipresente jugador muere","MuerteMueres",2); //error con estados
  LoadEvent("event:/Diálogos/Dialogo-Muerte Omnipresente jugador pasea","MuertePaseas",2);
  LoadEvent("event:/Diálogos/Dialogo-Muerte Omnipresente Penultima sala","MuertePenultima",2);
  LoadEvent("event:/Diálogos/Dialogo-Muerte Omnipresente Presentacion nivel 1","MuerteBienvenida1",2);
  LoadEvent("event:/Diálogos/Dialogo-Muerte Omnipresente Presentacion nivel 2","MuerteBienvenida2",2);
  LoadEvent("event:/Diálogos/Dialogo-Muerte Omnipresente respawnean enemigos","MuerteRespawn1",2);
  LoadEvent("event:/Diálogos/Dialogo-Muerte Omnipresente respawnean murcis","MuerteRespawn2",2);
   LoadEvent("event:/Diálogos/Dialogo-Muerte Omnipresente te persigue arana y murci","MuertePerseguido1",2);
   LoadEvent("event:/Diálogos/Dialogo-Muerte Omnipresente te persigue pollo","MuertePerseguido2",2);
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
    motorfound = MusicaEvents.find(name);
    if(motorfound == MusicaEvents.end())
    {
        motorfound = SFXEvents.find(name);
        if(motorfound == SFXEvents.end())
        {
            motorfound = VocesEvents.find(name);
        }
    }

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

//Crear intancia de un evento (tipo: 0-Musica 1-SFX 2-Voces)
void MotorAudioSystem::LoadEvent(const char *path,std::string name,unsigned short tipo)
{
    FMOD::Studio::EventDescription* pEventInstance;
    ERRCHECK(pstudioSystem->getEvent(path, &pEventInstance));
    if(pEventInstance)
    {
        eventDescriptions[name] = pEventInstance; //Insertar en el mapa de descripcion de eventos
        MotorAudioEvent * newEvent = new MotorAudioEvent(pEventInstance);
        if(tipo == 0)
        {
            newEvent->setVolume(generalVolumeMusica);
            MusicaEvents.insert(pair<std::string, MotorAudioEvent*>(name,newEvent));
        }
        else if(tipo == 1)
        {
            newEvent->setVolume(generalVolumeSFX);
            SFXEvents.insert(pair<std::string, MotorAudioEvent*>(name,newEvent));
        }
        else if(tipo == 2)
        {
            newEvent->setVolume(generalVolumeVoces);
            VocesEvents.insert(pair<std::string, MotorAudioEvent*>(name,newEvent));
        }
    }
}

//Modifica el volumen (entre 0 y 1) de todos los eventos de un tipo
void MotorAudioSystem::setVolumeAll(unsigned short tipo, float vol)
{
    if(tipo == 0)
    {
        if(vol != generalVolumeMusica)
        {
            if(MusicaEvents.size() > 0)
            {
                // std::cout << " --> CAMBIANDO VOLUMEN MUSICA" << std::endl;
                for(auto i = MusicaEvents.begin(); i != MusicaEvents.end(); i++)
                {
                    i->second->setVolume(vol);
                }
                generalVolumeMusica = vol;
            }
        }
    }
    else if(tipo == 1)
    {
        if(vol != generalVolumeSFX)
        {
            if(SFXEvents.size() > 0)
            {
                // std::cout << " --> CAMBIANDO VOLUMEN SFX" << std::endl;
                for(auto i = SFXEvents.begin(); i != SFXEvents.end(); i++)
                {
                    i->second->setVolume(vol);
                }
                generalVolumeSFX = vol;
            }
        }
    }
    else if(tipo == 2)
    {
        if(vol != generalVolumeVoces)
        {
            if(VocesEvents.size() > 0)
            {
                // std::cout << " --> CAMBIANDO VOLUMEN VOCES" << std::endl;
                for(auto i = VocesEvents.begin(); i != VocesEvents.end(); i++)
                {
                    i->second->setVolume(vol);
                }
                generalVolumeVoces = vol;
            }
        }
    }
}

//Detiene todos los sonidos
void MotorAudioSystem::stopAll()
{
    if(MusicaEvents.size() > 0)
    {
        for(auto i = MusicaEvents.begin(); i != MusicaEvents.end(); i++)
        {
            i->second->stop();
        }
    }
    if(SFXEvents.size() > 0)
    {
        for(auto i = SFXEvents.begin(); i != SFXEvents.end(); i++)
        {
            i->second->stop();
        }
    }
    if(VocesEvents.size() > 0)
    {
        for(auto i = VocesEvents.begin(); i != VocesEvents.end(); i++)
        {
            i->second->stop();
        }
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
    if(vol < 0.0f)vol = 0.0f;
    if(vol > 1.0f)vol = 1.0f;
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
