#include "../include/Player.hpp"

#include "../include/AnimSpriteComponent.hpp"
#include "../include/Bullet.hpp"
#include "../include/Game.hpp"
#include "../include/InputComponent.hpp"
#include "../include/ShootComponent.hpp"

Player::Player(Game* game) : Actor(game)
{
    spt = new AnimSpriteComponent(this);
    spt->setAnimTextures("papaco48.png", 16);

    ipc = new InputComponent(this);
    ipc->setUpKey(KEY_W);
    ipc->setDownKey(KEY_S);
    ipc->setLeftKey(KEY_A);
    ipc->setRightKey(KEY_D);

    ipc->setMaxVerticalSpeed(150.0f);
    ipc->setMaxHorizontalSpeed(150.0f);

    shc = new ShootComponent(this);
    shc->setProjectileSpeed(450.0f);
    shc->setShotInterval(35);
}

Player::~Player()
{
}

void Player::updateActor()
{
    Actor::updateActor();

    float angle = Vector2Angle(getPosition(), GetMousePosition());

    if (ipc->getHorizontalSpeed() != 0 || ipc->getVerticalSpeed() != 0) {
        if (angle > 45 && angle < 135)
            spt->setFrameSeq({4, 5, 6});
        else if (angle >= 135 && angle <= 225)
            spt->setFrameSeq({7, 8, 9});
        else if (angle > 225 && angle < 315)
            spt->setFrameSeq({10, 11, 12});
        else
            spt->setFrameSeq({1, 2, 3});
    }
    else {
        if (angle > 45 && angle < 135)
            spt->setFrameSeq({4});
        else if (angle >= 135 && angle <= 225)
            spt->setFrameSeq({7});
        else if (angle > 225 && angle < 315)
            spt->setFrameSeq({10});
        else
            spt->setFrameSeq({1});
    }
    processKeyboard();
}

void Player::processKeyboard()
{
    if (IsMouseButtonDown(MOUSE_LEFT_BUTTON))
        shc->shoot(GetMousePosition());
}
