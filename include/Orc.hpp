#pragma once

#include "Actor.hpp"

// forward declaration
class Game;
class AnimSpriteComponent;

class Orc : public Actor
{
public:
    Orc(Game* game);
    virtual ~Orc();

    void updateActor() override;
    void processKeyboard();
private:
};
