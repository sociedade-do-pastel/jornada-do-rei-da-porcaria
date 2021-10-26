#pragma once

#include "Actor.hpp"

// forward declaration
class Game;

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
};
