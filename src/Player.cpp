#include "../include/Player.hpp"

#include <algorithm>
#include <raymath.h>

#include "../include/AnimSpriteComponent.hpp"
#include "../include/Bullet.hpp"
#include "../include/Enemy.hpp"
#include "../include/Game.hpp"
#include "../include/InputComponent.hpp"
#include "../include/ShootComponent.hpp"
#include "../include/Tile.hpp"

Player::Player(Game* game) : Actor(game)
{
    m_spc = new AnimSpriteComponent(this);
    m_spc->setAnimTextures("papaco48.png", 16);

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

    m_hp = 5;
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
            m_spc->setFrameSeq({4, 5, 6});
        else if (angle >= 135 && angle <= 225)
            m_spc->setFrameSeq({7, 8, 9});
        else if (angle > 225 && angle < 315)
            m_spc->setFrameSeq({10, 11, 12});
        else
            m_spc->setFrameSeq({1, 2, 3});
    }
    else {
        if (angle > 45 && angle < 135)
            m_spc->setFrameSeq({4});
        else if (angle >= 135 && angle <= 225)
            m_spc->setFrameSeq({7});
        else if (angle > 225 && angle < 315)
            m_spc->setFrameSeq({10});
        else
            m_spc->setFrameSeq({1});
    }

    for (auto& e : getGame()->getCollisionTiles()) {
        if (CheckCollisionRecs(getColRec(), e->getColRec())) {
            auto r = GetCollisionRec(getColRec(), e->getColRec());
            if (r.width > r.height && getPosition().y < r.y)
                setPosition(Vector2Subtract(getPosition(), {0, r.height}));
            else if (r.width > r.height && getPosition().y >= r.y)
                setPosition(Vector2Add(getPosition(), {0, r.height}));
            else if (r.height > r.width && getPosition().x < r.x)
                setPosition(Vector2Subtract(getPosition(), {r.width, 0}));
            else if (r.height > r.width && getPosition().x >= r.x)
                setPosition(Vector2Add(getPosition(), {r.width, 0}));
        }
    }

    for (auto& e : getGame()->getEnemies()) {
        if (CheckCollisionRecs(getColRec(), e->getColRec())) {
            m_hp -= 1;

            for (auto& f : getGame()->getEnemies())
                f->setState(Actor::State::Paused);

            e->setState(Actor::State::Dead);
        }
    }

    // if (getHP() == 0)
    // 	setState(Actor::State::Dead);

    processKeyboard();
}

void Player::processKeyboard()
{
    if (IsMouseButtonDown(MOUSE_LEFT_BUTTON))
        m_shc->shoot(GetMousePosition());
}
