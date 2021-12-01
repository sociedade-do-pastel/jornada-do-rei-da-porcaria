#include "../include/Enemy.hpp"
#include "../include/Game.hpp"
#include "../include/World.hpp"

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

    auto a = getGame()->getWorld()->get_top_left();

    if (getPosition().x < a.x)
        setPosition({a.x + 25, getPosition().y});
    if (getPosition().y < a.y)
        setPosition({getPosition().x, a.y + 25});
    if (getPosition().x > a.x + 768)
        setPosition({a.x + 743, getPosition().y});
    if (getPosition().y > a.y + 768)
        setPosition({getPosition().x, a.y + 743});

    if (getHP() <= 0)
        setState(Actor::State::Dead);
}
