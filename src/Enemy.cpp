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
	if (getHP() == 0)
		setState(Actor::State::Dead);
}
