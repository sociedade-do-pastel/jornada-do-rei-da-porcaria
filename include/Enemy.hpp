#pragma once

#include "Actor.hpp"

// forward declaration
class Game;

class Enemy : public Actor
{
public:
    Enemy(Game* game);
    virtual ~Enemy();

    void updateActor() override;

    // getters
    int getHP() const
    {
        return m_hp;
    }

    float getSpeed() const
    {
        return m_speed;
    }

    virtual Rectangle getColRec() const
    {
        return {0, 0, 0, 0};
    }

    // setters
    void setHP(int hp)
    {
        m_hp = hp;
    }

    void setSpeed(float speed)
    {
        m_speed = speed;
    }

private:
    int m_hp;
    float m_speed;
};
