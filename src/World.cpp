#include "../include/World.hpp"
#include "../include/SpriteComponent.hpp"

World::World(Game* game, unsigned width, unsigned height)
    : game{game}, num_tiles_x{width}, num_tiles_y{height}, biome{current_theme},
      grid{num_tiles_y, std::vector<Tile*>{num_tiles_x, nullptr}}
{
    // for now that's how we roll
    generate_world();
}

void World::generate_world()
{
    // now this is kinda hacky (temp)
    for (int j{0}; j < num_tiles_y; ++j) {
        for (int i{0}; i < num_tiles_x; ++i) {
            /* generate a random tile based on our main Terrain type */
            std::string chosen_texture_name;
            bool obstacle{false};
            /* its position in pixels (top left corner) */
            float tile_position_x = (float)(i * this->tile_diameter);
            float tile_position_y = (float)(j * this->tile_diameter);

            /* place trees on the edges and on the map itself with 5% chance */
            //
            /* TODO: allow this class to get the player's position so I don't
             have to write an if clause as big as this one */
            /* NOTE: actually this approach doesn't seem to be working perhaps
               because we're working with floating point number comparisons, imo
               the player should have a spawn (maybe an actor) */
            //
            if ((i == 0 || j == 0 || i == (num_tiles_x - 1)
                 || j == (num_tiles_y - 1))
                || ((GetRandomValue(0, 100) <= 10)
                    && tile_position_y != GetScreenHeight() / 2.0f
                    && tile_position_x != GetScreenWidth() / 2.0f)) {
                chosen_texture_name = biome.get_animated_texture_name();
                obstacle            = true; // it's a tree after all
            }
            else
                chosen_texture_name = biome.get_random_tile_texture_name();

            Tile* curr_tile
                = new Tile(this->game, {tile_position_x, tile_position_y},
                           chosen_texture_name, obstacle);

            grid[j][i] = curr_tile;
        }
    }
}

World::~World()
{
}
