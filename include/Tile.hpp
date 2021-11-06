#pragma once
#include <raylib.h>
#include <string>
#include "Actor.hpp"

class Tile : public Actor
{
public:
    Tile(Game* game, Vector2 position, std::string terrain_type, bool obstacle);
    virtual ~Tile();
    void updateActor() override;

private:
    bool m_is_obstacle{false};
    // let's us assume that they will all be squares
};
