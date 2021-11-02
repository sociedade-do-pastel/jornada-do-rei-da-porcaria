#pragma once
#include <raylib.h>
#include "Actor.hpp"

class Tile : public Actor
{
public:
    Tile(Game* game, Vector2 position, Texture terrain_tex, bool obstacle);
    virtual ~Tile();
    void updateActor() override;

private:
    bool m_is_obstacle{false};
    // let's us assume that they will all be squares
    int m_width;
};
