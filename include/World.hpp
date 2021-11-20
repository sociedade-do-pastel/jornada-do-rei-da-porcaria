#pragma once
#include "Actor.hpp"
#include "Grid.h"
#include "MapConstants.h"
#include "Tile.hpp"

#include <raylib.h>
#include <stdio.h>

#include <string>
#include <vector>

class World : public Actor
{
public:
    World(Game* game, const unsigned int top_left_x = 0,
          const unsigned int top_right_y = 0);
    virtual ~World();

    Grid* get_main_grid()
    {
        return this->main_grid;
    }

    Vector2 get_top_left()
    {
        return Vector2{(float)top_left_x, (float)top_left_y};
    };

    unsigned short int get_curr_map()
    {
        return this->curr_map;
    }

    unsigned short get_tile_diameter()
    {
        return this->tile_diameter;
    }
  
    void generate_world();
    bool load_world();
    void load_actors();
    void unload_actors();
    std::string get_texture_name_from_int(unsigned short int number);

private:
    // our titles diameter wont change
    unsigned short tile_diameter{NODE_DIAMETER}; // in px

    // number of tiles in both directions
    unsigned number_of_nodes{NUMBER_OF_NODES_AXIS};

    // point that will define where our grid is gonna get drawn on
    unsigned top_left_x{0}; // in px
    unsigned top_left_y{0}; // in px

    // the filename for our maps will be hardcoded for now
    std::string map_filename{"map.jooj"};

    // main grid
    Grid* main_grid;
    bool file_loaded{false};
    unsigned short curr_map{0};

    // vector of actors added by our world
    std::vector<Tile*> tiles;
};
