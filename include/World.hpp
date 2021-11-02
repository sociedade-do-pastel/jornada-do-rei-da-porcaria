#pragma once
#include "Game.hpp"
#include "Terrain.hpp"
#include "Tile.hpp"

#include <raylib.h>
#include <string>

class World
{
private:
    // 0 -> Forest
    // 1 -> Snow
    // 2 -> Desert
    unsigned short current_theme{0};

    // defines what kind of biome this world will have
    Terrain biome;

    // our titles diameter wont change
    unsigned short tile_diameter{48};

    // so we can make our modifications (i.e. add our tiles to the pending
    // actors list)
    Game* game;

    // number of tiles in both directions
    unsigned num_tiles_x{0};
    unsigned num_tiles_y{0};
    // our flimsy grid
    std::vector<std::vector<Tile*>> grid; // as readable as ever

public:
    World(Game* game, unsigned width, unsigned height);
    virtual ~World();
    void generate_world();
    // Tile* get_tile_from_point (Vector2 point);
    // void load_world (std::string filename);
};
