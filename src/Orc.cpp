#include "../include/Orc.hpp"

#include "../include/AnimSpriteComponent.hpp"

Orc::Orc(Game* game) : Actor(game)
{
	AnimSpriteComponent* spt = new AnimSpriteComponent(this, 99);
    spt->setAnimTextures("orcson.png", 2);
	spt->setFrameSeq({0, 1});
	
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
