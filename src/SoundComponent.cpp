#include "../include/SoundComponent.hpp"
#include "../include/Game.hpp"
#include "../include/SoundManager.hpp"

SoundComponent::SoundComponent(Actor* owner, std::string sound_name)
    : Component{owner}, m_sound_name{sound_name}
{
}

void SoundComponent::playSound()
{
    SoundManager* game_smanager
        = this->getOwner()->getGame()->getSoundManager();
    game_smanager->add_sound(this->m_sound_name);
}

SoundComponent::~SoundComponent()
{
}
