#pragma once

#include "AnimSpriteComponent.hpp"
#include "Enemy.hpp"
#include "MoveComponent.hpp"

// forward declaration
class Game;

class Moth : public Enemy
{
public:
    Moth(Game* game);
    virtual ~Moth();

    void updateActor() override;
    void processKeyboard();

private:
    MoveComponent* move_component;
};
