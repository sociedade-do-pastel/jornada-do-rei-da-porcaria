#pragma once

#include "Actor.hpp"

// forward declaration
class Game;
class AnimSpriteComponent;
class InputComponent;
class ShootComponent;

class Player : public Actor
{
public:
    Player(Game* game);
    virtual ~Player();

    void updateActor() override;
    void processKeyboard();

    // getters
    float getSpeed() const
    {
        return m_speed;
    }

    int getLifes() const
    {
        return m_lifes;
    }

private:
    float m_speed;
    int m_lifes;

    AnimSpriteComponent* spt{nullptr};
    InputComponent* ipc{nullptr};
	ShootComponent* shc{nullptr};
};
