#include "../include/Orc.hpp"

#include "../include/AnimSpriteComponent.hpp"

Orc::Orc(Game* game) : Enemy(game)
{
	AnimSpriteComponent* anim = new AnimSpriteComponent(this, 99);
    anim->setAnimTextures("orcson.png", 2);
    anim->setFrameSeq({0, 1});
	m_spc = anim;

    setPosition({10, 10});
}

Orc::~Orc()
{
}

void Orc::updateActor()
{
}

void Orc::processKeyboard()
{
}
