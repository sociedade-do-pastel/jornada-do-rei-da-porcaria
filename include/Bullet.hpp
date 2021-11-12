#pragma once

#include "Actor.hpp"
#include "SpriteComponent.hpp"

// forward declaration
class Game;
class MoveComponent;

class Bullet : public Actor
{
public:
    Bullet(Game* game);
    virtual ~Bullet();

    void updateActor() override;

    // getters
    Rectangle getColRec() const
    {		
        Rectangle r;
        r.width  = m_spc->getTexWidth();
        r.height = m_spc->getTexHeight();
        r.x      = getPosition().x - r.width / 2.0f;
        r.y      = getPosition().y - r.height / 2.0f;

        return r;
    }

    // setters
    void setForwardDirection(Vector2 target);

private:
    MoveComponent* m_mvc{nullptr};
    SpriteComponent* m_spc{nullptr};
};
