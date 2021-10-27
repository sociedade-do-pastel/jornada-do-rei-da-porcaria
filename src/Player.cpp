#include "../include/Player.hpp"

#include "../include/AnimSpriteComponent.hpp"
#include "../include/InputComponent.hpp"

Player::Player(Game* game) : Actor(game)
{
    spt = new AnimSpriteComponent(this);
    spt->setAnimTextures("assets/papaco48.png", 16);
	
    ipc = new InputComponent(this);
    ipc->setUpKey(KEY_W);
    ipc->setDownKey(KEY_S);
    ipc->setLeftKey(KEY_A);
    ipc->setRightKey(KEY_D);

    ipc->setMaxVerticalSpeed(150.0f);
    ipc->setMaxHorizontalSpeed(150.0f);
}

Player::~Player()
{
}

void Player::updateActor()
{
    Actor::updateActor();

    if (ipc->getVerticalSpeed() > 0)
        spt->setFrameSeq({4, 5, 6});
	if (ipc->getVerticalSpeed() < 0)
        spt->setFrameSeq({10, 11, 12});
    if (ipc->getHorizontalSpeed() > 0)
        spt->setFrameSeq({1, 2, 3});
    if (ipc->getHorizontalSpeed() < 0)
        spt->setFrameSeq({7, 8, 9});
    if (ipc->getHorizontalSpeed() == 0 && ipc->getVerticalSpeed() == 0)
        spt->setFrameSeq({0});
}

void Player::processKeyboard()
{
}
