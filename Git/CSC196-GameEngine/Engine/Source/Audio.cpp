#include "Audio.h"
#include <iostream>

bool Audio::Initialize()
{
    return true;
}

void Audio::Shutdown()
{
    m_audio->close();
}

void Audio::Update()
{
    m_audio->update();
}

void Audio::AddSound(const std::string& name)
{
    FMOD::Sound8 sound = nullptr;
    m_audio->createSound(name.c_str(), FMOD_DEFAULT, 0, &sound);

    if (sound == nullptr) {
        std::cerr << "Could not load sound: " << name << std::endl;
        return false;
    }
    m_sounds[name] = sound;
    return true;
}

void Audio::PlaySound(const std::string& name)
{
    if (m_sounds.find(name) == m_sounds.end()) {
        if(!Addsound) return false;
    }
    m_audio->playSound(m_sounds[name, 0, false, nullptr]);

    return true;
}
