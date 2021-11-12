#include "../include/Orc.hpp"

#include "../include/AnimSpriteComponent.hpp"

Orc::Orc(Game* game) : Enemy(game)
{
    m_spt = new AnimSpriteComponent(this, 99);
    m_spt->setAnimTextures("orcson.png", 2);
	m_spt->setFrameSeq({0, 1});
	
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
