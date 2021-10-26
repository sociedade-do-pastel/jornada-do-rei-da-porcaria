#include "../include/Player.hpp"

#include "../include/AnimSpriteComponent.hpp"

Player::Player(Game* game) : Actor(game)
{
	AnimSpriteComponent* spt = new AnimSpriteComponent(this);
	spt->setAnimTextures("assets/papaco48.png", 16);

	setPosition({200, 200});
}

Player::~Player()
{
}

void Player::updateActor()
{
	Actor::updateActor();
	Vector2 pos = getPosition();

	// do something
	
	setPosition(pos);
}

void Player::processKeyboard()
{
}
