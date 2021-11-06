#pragma once

#include "Actor.hpp"

// forward declaration
class Game;
class MoveComponent;

class Bullet : public Actor
{
public:
    Bullet(Game* game);
    virtual ~Bullet();

    void updateActor() override;

	void setForwardDirection(Vector2 target);

private:
	MoveComponent* m_mvc{nullptr};
};
