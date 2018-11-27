#include "MotorAudio.hpp"

//Constructor de Implementation, crea los sistemas de FMOD
Implementation::Implementation() {
    mpStudioSystem = NULL;
    CAudioEngine::ErrorCheck(FMOD::Studio::System::create(&mpStudioSystem));
    CAudioEngine::ErrorCheck(mpStudioSystem->initialize(32, FMOD_STUDIO_INIT_LIVEUPDATE, FMOD_INIT_PROFILE_ENABLE, NULL));

    mpSystem = NULL;
    CAudioEngine::ErrorCheck(mpStudioSystem->getLowLevelSystem(&mpSystem));
}

Implementation::~Implementation() {
    CAudioEngine::ErrorCheck(mpStudioSystem->unloadAll());
    CAudioEngine::ErrorCheck(mpStudioSystem->release());
}

//Comprobamos si un canal deja de reproducirse, si es el caso borramos el canal
void Implementation::Update() {
    vector<ChannelMap::iterator> pStoppedChannels;
    for (auto it = mChannels.begin(), itEnd = mChannels.end(); it != itEnd; ++it)
    {
        bool bIsPlaying = false;
        it->second->isPlaying(&bIsPlaying);
        if (!bIsPlaying)
        {
             pStoppedChannels.push_back(it);
        }
    }
    for (auto& it : pStoppedChannels)
    {
         mChannels.erase(it);
    }
    CAudioEngine::ErrorCheck(mpStudioSystem->update());
}

//Instacia a la Implementation
Implementation* sgpImplementation = nullptr;


//Motor de Audio crear
void CAudioEngine::Init() {
    sgpImplementation = new Implementation;
}

//Motor de Audio actualizar
void CAudioEngine::Update() {
    sgpImplementation->Update();
}

//Motor de Audio cargar sonido
void CAudioEngine::LoadSound(const std::string& strSoundName, bool b3d, bool bLooping, bool bStream)
{
    auto tFoundIt = sgpImplementation->mSounds.find(strSoundName);
    if (tFoundIt != sgpImplementation->mSounds.end())
        return;

    FMOD_MODE eMode = FMOD_DEFAULT;
    eMode |= b3d ? FMOD_3D : FMOD_2D;
    eMode |= bLooping ? FMOD_LOOP_NORMAL : FMOD_LOOP_OFF;
    eMode |= bStream ? FMOD_CREATESTREAM : FMOD_CREATECOMPRESSEDSAMPLE;

    FMOD::Sound* pSound = nullptr;
    CAudioEngine::ErrorCheck(sgpImplementation->mpSystem->createSound(strSoundName.c_str(), eMode, nullptr, &pSound));
    if (pSound){
        sgpImplementation->mSounds[strSoundName] = pSound;
    }

}

//Motor de Audio descargar sonido borrandolo del mapa
void CAudioEngine::UnLoadSound(const std::string& strSoundName)
{
    auto tFoundIt = sgpImplementation->mSounds.find(strSoundName);
    if (tFoundIt == sgpImplementation->mSounds.end())
        return;

    CAudioEngine::ErrorCheck(tFoundIt->second->release());
    sgpImplementation->mSounds.erase(tFoundIt);
}

//Ejecutar sonido
/*
  Primero vemos si tenemos ese sonido en nuestro mapa de sonido. Si no, lo cargamos.
  Si todavía no lo encontramos, significa que algo salió mal y que no podemos reproducir
  el sonido. Si encontramos el sonido bien entonces creamos un nuevo canal para alojar el
  sonido y decirle al sonido que se reproduzca, pero empezamos el sonido en pausa.
  Esto es para que no aparezca un pop en el audio cuando establecemos los parámetros.
  Si el canal fue ajustado correctamente, entonces actualizamos todos los parámetros
  posibles como el volumen y la posición y luego desactivamos el sonido. Y finalmente
  devolvemos el encapsulado de identificación del canal al que nos referiremos más adelante.
*/
int CAudioEngine::PlaySounds(const string& strSoundName, const Vector3& vPosition, float fVolumedB)
{
    int nChannelId = sgpImplementation->mnNextChannelId++;
    auto tFoundIt = sgpImplementation->mSounds.find(strSoundName);
    if (tFoundIt == sgpImplementation->mSounds.end())
    {
        LoadSound(strSoundName);
        tFoundIt = sgpImplementation->mSounds.find(strSoundName);
        if (tFoundIt == sgpImplementation->mSounds.end())
        {
            return nChannelId;
        }
    }
    FMOD::Channel* pChannel = nullptr;
    CAudioEngine::ErrorCheck(sgpImplementation->mpSystem->playSound(tFoundIt->second, nullptr, true, &pChannel));
    if (pChannel)
    {
        FMOD_MODE currMode;
        tFoundIt->second->getMode(&currMode);
        if (currMode & FMOD_3D){
            FMOD_VECTOR position = VectorToFmod(vPosition);
            CAudioEngine::ErrorCheck(pChannel->set3DAttributes(&position, nullptr));
        }
        CAudioEngine::ErrorCheck(pChannel->setVolume(dbToVolume(fVolumedB)));
        CAudioEngine::ErrorCheck(pChannel->setPaused(false));
        sgpImplementation->mChannels[nChannelId] = pChannel;
    }
    return nChannelId;
}

//Posicion del sonido
void CAudioEngine::SetChannel3dPosition(int nChannelId, const Vector3& vPosition)
{
    auto tFoundIt = sgpImplementation->mChannels.find(nChannelId);
    if (tFoundIt == sgpImplementation->mChannels.end())
        return;

    FMOD_VECTOR position = VectorToFmod(vPosition);
    CAudioEngine::ErrorCheck(tFoundIt->second->set3DAttributes(&position, NULL));
}

//Volumen del sonido
void CAudioEngine::SetChannelVolume(int nChannelId, float fVolumedB)
{
    auto tFoundIt = sgpImplementation->mChannels.find(nChannelId);
    if (tFoundIt == sgpImplementation->mChannels.end())
        return;

    CAudioEngine::ErrorCheck(tFoundIt->second->setVolume(dbToVolume(fVolumedB)));
}

//EVENTOS
//Cargamos los bancos de sonidos con la informacion de los eventos
void CAudioEngine::LoadBank(const std::string& strBankName, FMOD_STUDIO_LOAD_BANK_FLAGS flags) {
    auto tFoundIt = sgpImplementation->mBanks.find(strBankName);
    if (tFoundIt != sgpImplementation->mBanks.end())
        return;
    FMOD::Studio::Bank* pBank;
    CAudioEngine::ErrorCheck(sgpImplementation->mpStudioSystem->loadBankFile(strBankName.c_str(), flags, &pBank));
    if (pBank) {
        sgpImplementation->mBanks[strBankName] = pBank;
    }
}

//Cargar evento
void CAudioEngine::LoadEvent(const std::string& strEventName) {
    auto tFoundit = sgpImplementation->mEvents.find(strEventName);
    if (tFoundit != sgpImplementation->mEvents.end())
        return;
    FMOD::Studio::EventDescription* pEventDescription = NULL;
    CAudioEngine::ErrorCheck(sgpImplementation->mpStudioSystem->getEvent(strEventName.c_str(), &pEventDescription));
    if (pEventDescription){
        FMOD::Studio::EventInstance* pEventInstance = NULL;
        CAudioEngine::ErrorCheck(pEventDescription->createInstance(&pEventInstance));
        if (pEventInstance){
            sgpImplementation->mEvents[strEventName] = pEventInstance;
        }
    }
}

//Ejecutar evento
void CAudioEngine::PlayEvent(const string &strEventName) {
    auto tFoundit = sgpImplementation->mEvents.find(strEventName);
    if (tFoundit == sgpImplementation->mEvents.end()){
        LoadEvent(strEventName);
        tFoundit = sgpImplementation->mEvents.find(strEventName);
        if (tFoundit == sgpImplementation->mEvents.end())
            return;
    }
    tFoundit->second->start();
}

//Detener evento
void CAudioEngine::StopEvent(const string &strEventName, bool bImmediate) {
    auto tFoundIt = sgpImplementation->mEvents.find(strEventName);
    if (tFoundIt == sgpImplementation->mEvents.end())
        return;

    FMOD_STUDIO_STOP_MODE eMode;
    eMode = bImmediate ? FMOD_STUDIO_STOP_IMMEDIATE : FMOD_STUDIO_STOP_ALLOWFADEOUT;
    CAudioEngine::ErrorCheck(tFoundIt->second->stop(eMode));
}

//Comprobar si se esta ejecutando un evento
bool CAudioEngine::IsEventPlaying(const string &strEventName) const {
    auto tFoundIt = sgpImplementation->mEvents.find(strEventName);
    if (tFoundIt == sgpImplementation->mEvents.end())
        return false;

    FMOD_STUDIO_PLAYBACK_STATE* state = NULL;
    if (tFoundIt->second->getPlaybackState(state) == FMOD_STUDIO_PLAYBACK_PLAYING) {
        return true;
    }
    return false;
}

//Obtener parametros de un evento
void CAudioEngine::GetEventParameter(const string &strEventName, const string &strParameterName, float* parameter) {
    auto tFoundIt = sgpImplementation->mEvents.find(strEventName);
    if (tFoundIt == sgpImplementation->mEvents.end())
        return;

    FMOD::Studio::ParameterInstance* pParameter = NULL;
    CAudioEngine::ErrorCheck(tFoundIt->second->getParameter(strParameterName.c_str(), &pParameter));
    CAudioEngine::ErrorCheck(pParameter->getValue(parameter));
}

//Cambiar parametros de un evento
void CAudioEngine::SetEventParameter(const string &strEventName, const string &strParameterName, float fValue) {
    auto tFoundIt = sgpImplementation->mEvents.find(strEventName);
    if (tFoundIt == sgpImplementation->mEvents.end())
        return;

    FMOD::Studio::ParameterInstance* pParameter = NULL;
    CAudioEngine::ErrorCheck(tFoundIt->second->getParameter(strParameterName.c_str(), &pParameter));
    CAudioEngine::ErrorCheck(pParameter->setValue(fValue));
}

//Transformar el vector3 a FMOD
FMOD_VECTOR CAudioEngine::VectorToFmod(const Vector3& vPosition){
    FMOD_VECTOR fVec;
    fVec.x = vPosition.x;
    fVec.y = vPosition.y;
    fVec.z = vPosition.z;
    return fVec;
}

//Transformar dB a volumen
float  CAudioEngine::dbToVolume(float dB)
{
    return powf(10.0f, 0.05f * dB);
}

//Transformar volumen a dB
float  CAudioEngine::VolumeTodB(float volume)
{
    return 20.0f * log10f(volume);
}

//Comprobar errores
int CAudioEngine::ErrorCheck(FMOD_RESULT result) {
    if (result != FMOD_OK){
        cout << "FMOD ERROR " << result << endl;
        return 1;
    }
    // cout << "FMOD all good" << endl;
    return 0;
}

//Borrar Implementation
void CAudioEngine::Shutdown() {
    delete sgpImplementation;
}
