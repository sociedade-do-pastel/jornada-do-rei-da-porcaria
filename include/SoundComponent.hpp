#pragma once
#include <string>
#include "Component.hpp"

class SoundComponent : public Component
{
public:
    SoundComponent(Actor* owner, std::string sound_name);
    ~SoundComponent();
    void playSound();

private:
    std::string m_sound_name;
};
