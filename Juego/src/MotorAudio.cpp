#include "MotorAudio.hpp"

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
