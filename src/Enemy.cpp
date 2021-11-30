#include "../include/Enemy.hpp"
#include "../include/Game.hpp"

Enemy::Enemy(Game* game) : Actor(game)
{
    game->addEnemy(this);
}

Enemy::~Enemy()
{
    getGame()->removeEnemy(this);
}

void Enemy::updateActor()
{
    if (m_inKnockback && m_knockbackTime > 0) {
        --m_knockbackTime;
        if (m_knockbackTime == 0) {
            m_inKnockback = false;
            setSpeed(100);
        }
    }

    if (getHP() <= 0)
        setState(Actor::State::Dead);
}
