#include "../include/Player.hpp"

#include "../include/AnimSpriteComponent.hpp"
#include "../include/Bullet.hpp"
#include "../include/Enemy.hpp"
#include "../include/Game.hpp"
#include "../include/InputComponent.hpp"
#include "../include/ShootComponent.hpp"

Player::Player(Game* game) : Actor(game)
{
    m_spt = new AnimSpriteComponent(this);
    m_spt->setAnimTextures("papaco48.png", 16);

    m_ipc = new InputComponent(this);
    m_ipc->setUpKey(KEY_W);
    m_ipc->setDownKey(KEY_S);
    m_ipc->setLeftKey(KEY_A);
    m_ipc->setRightKey(KEY_D);

    m_ipc->setMaxVerticalSpeed(150.0f);
    m_ipc->setMaxHorizontalSpeed(150.0f);

    m_shc = new ShootComponent(this);
    m_shc->setProjectileSpeed(450.0f);
    m_shc->setShotInterval(35);
}

Player::~Player()
{
}

void Player::updateActor()
{
    Actor::updateActor();

    float angle = Vector2Angle(getPosition(), GetMousePosition());

    if (m_ipc->getHorizontalSpeed() != 0 || m_ipc->getVerticalSpeed() != 0) {
        if (angle > 45 && angle < 135)
            m_spt->setFrameSeq({4, 5, 6});
        else if (angle >= 135 && angle <= 225)
            m_spt->setFrameSeq({7, 8, 9});
        else if (angle > 225 && angle < 315)
            m_spt->setFrameSeq({10, 11, 12});
        else
            m_spt->setFrameSeq({1, 2, 3});
    }
    else {
        if (angle > 45 && angle < 135)
            m_spt->setFrameSeq({4});
        else if (angle >= 135 && angle <= 225)
            m_spt->setFrameSeq({7});
        else if (angle > 225 && angle < 315)
            m_spt->setFrameSeq({10});
        else
            m_spt->setFrameSeq({1});
    }

    processKeyboard();
}

void Player::processKeyboard()
{
    if (IsMouseButtonDown(MOUSE_LEFT_BUTTON))
        m_shc->shoot(GetMousePosition());
}
