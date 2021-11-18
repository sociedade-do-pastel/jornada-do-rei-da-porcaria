#include "../include/Bullet.hpp"

#include "../include/Enemy.hpp"
#include "../include/Game.hpp"
#include "../include/MoveComponent.hpp"
#include "../include/SpriteComponent.hpp"
#include "../include/Tile.hpp"

Bullet::Bullet(Game* game) : Actor(game)
{
    m_spc = new SpriteComponent(this);
    m_spc->setTexture("tiru.png");

    m_mvc = new MoveComponent(this);
}

Bullet::~Bullet()
{
}

void Bullet::updateActor()
{
    if (getPosition().x > GetScreenWidth() || getPosition().x < 0
        || getPosition().y > GetScreenHeight() || getPosition().y < 0)
        setState(Actor::State::Dead);

    for (auto& e : getGame()->getEnemies()) {
        if (CheckCollisionRecs(getColRec(), e->getColRec()))
            setState(Actor::State::Dead);
    }

    for (auto& e : getGame()->getCollisionTiles()) {
        if (CheckCollisionRecs(getColRec(), e->getColRec()))
            setState(Actor::State::Dead);
    }
}

void Bullet::setForwardDirection(Vector2 target)
{
    m_mvc->setHorizontalSpeed(target.x);
    m_mvc->setVerticalSpeed(target.y);
}
