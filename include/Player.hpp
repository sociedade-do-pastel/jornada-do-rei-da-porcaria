#pragma once

#include "Actor.hpp"
#include "AnimSpriteComponent.hpp"

// forward declaration
class Game;
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

    Rectangle getColRec() const override
    {
        Rectangle r;
        r.width  = m_spc->getTexWidth() - 12;
        r.height = m_spc->getTexHeight() - 12;
        r.x      = getPosition().x - r.width / 2.0f;
        r.y      = getPosition().y - r.height / 2.0f;

        return r;
    }

private:
    float m_speed;
    int m_lifes;

    AnimSpriteComponent* m_spc{nullptr};
    InputComponent* m_ipc{nullptr};
    ShootComponent* m_shc{nullptr};
};
