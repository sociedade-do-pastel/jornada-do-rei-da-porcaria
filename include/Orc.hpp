#pragma once

#include "AnimSpriteComponent.hpp"
#include "Enemy.hpp"

// forward declaration
class Game;

class Orc : public Enemy
{
public:
    Orc(Game* game);
    virtual ~Orc();

    void updateActor() override;
    void processKeyboard();

private:
};
