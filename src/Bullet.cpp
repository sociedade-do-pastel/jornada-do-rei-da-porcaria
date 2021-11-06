#include "../include/Bullet.hpp"

#include "../include/Game.hpp"
#include "../include/MoveComponent.hpp"
#include "../include/SpriteComponent.hpp"

Bullet::Bullet(Game* game) : Actor(game)
{
    SpriteComponent* spc = new SpriteComponent(this);
    spc->setTexture("tiru.png");

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
}

void Bullet::setForwardDirection(Vector2 target)
{
    m_mvc->setHorizontalSpeed(target.x);
    m_mvc->setVerticalSpeed(target.y);
}
