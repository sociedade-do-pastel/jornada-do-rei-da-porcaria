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

    Rectangle getColRec() const override
    {
        Rectangle r;
        r.width  = m_spt->getTexWidth();
        r.height = m_spt->getTexHeight();
        r.x      = getPosition().x - r.width / 2.0f;
        r.y      = getPosition().y - r.height / 2.0f;

        return r;
    }

private:
    AnimSpriteComponent* m_spt{nullptr};
};
