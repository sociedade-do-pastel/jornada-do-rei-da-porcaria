#pragma once

#include "Actor.hpp"
#include "SpriteComponent.hpp"

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

    Rectangle getColRec() const override
    {
        Rectangle r;
        r.width  = m_spc->getTexWidth();
        r.height = m_spc->getTexHeight();
        r.x      = getPosition().x - r.width / 2.0f;
        r.y      = getPosition().y - r.height / 2.0f;

        return r;
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

protected:
    SpriteComponent* m_spc{nullptr};

private:
    int m_hp;
    float m_speed;
};
