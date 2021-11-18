#pragma once

#include <raylib.h>
#include <string>
#include "Actor.hpp"
#include "SpriteComponent.hpp"

class Tile : public Actor
{
public:
    Tile(Game* game, Vector2 position, std::string terrain_type, bool obstacle);
    virtual ~Tile();
    void updateActor() override;

    Rectangle getColRec() const override
    {
        Rectangle r;
        r.width  = m_spc->getTexWidth();
        r.height = m_spc->getTexHeight();
        r.x      = getPosition().x - r.width / 2.0f;
        r.y      = getPosition().y - r.height / 2.0f;

        return r;
    }

protected:
    SpriteComponent* m_spc{nullptr};

private:
    bool m_is_obstacle{false};
    // let's us assume that they will all be squares
};
