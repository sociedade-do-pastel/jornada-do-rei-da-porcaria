#include "../include/Player.hpp"
#include <iostream>
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

    float angle = Vector2Angle(getPosition(), GetMousePosition());
    
    if (angle > 45 && angle < 135)
		spt->setFrameSeq({4, 5, 6});
	else if (angle >= 135 && angle <= 225)
        spt->setFrameSeq({7, 8, 9});
    else if (angle > 225 && angle < 315)
        spt->setFrameSeq({10, 11, 12});
	else
		spt->setFrameSeq({1, 2, 3});
}

void Player::processKeyboard()
{
}
