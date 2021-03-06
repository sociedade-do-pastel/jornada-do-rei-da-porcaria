#include "../include/Bullet.hpp"

#include "../include/Enemy.hpp"
#include "../include/Game.hpp"
#include "../include/MoveComponent.hpp"
#include "../include/SoundComponent.hpp"
#include "../include/SpriteComponent.hpp"
#include "../include/Tile.hpp"

Bullet::Bullet(Game* game) : Actor(game)
{
    m_spc = new SpriteComponent(this);
    m_spc->setTexture("tiru.png");

    m_mvc = new MoveComponent(this);

    (new SoundComponent(this, "tiru.ogg"))->playSound();
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
		if (m_alreadyHit)
			break;
        if (CheckCollisionRecs(getColRec(), e->getColRec())) {
			m_alreadyHit = true;
            setState(Actor::State::Dead);
            e->setHP(e->getHP() - 1);
			e->setKnockback(5);
        }
    }

    for (auto& e : getGame()->getCollisionTiles()) {
        if (CheckCollisionRecs(getColRec(), e->getColRec()))
            setState(Actor::State::Dead);
    }
	
    for (auto& e : getGame()->getSpawnTiles()) {
        if (CheckCollisionRecs(getColRec(), e->getColRec()))
            setState(Actor::State::Dead);
    }
}

void Bullet::setForwardDirection(Vector2 target)
{
    m_mvc->setHorizontalSpeed(target.x);
    m_mvc->setVerticalSpeed(target.y);
}
