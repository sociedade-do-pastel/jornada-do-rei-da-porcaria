#include "../include/World.hpp"

World::World(Game* game, const unsigned top_left_x, const unsigned top_left_y)
    : Actor{game}, top_left_x{top_left_x}, top_left_y{top_left_y}
{
    if (!load_world())
        generate_world();

    load_actors();
}

World::~World()
{
    if (this->file_loaded)
        UnloadFileData((unsigned char*)this->world);
    else
        delete this->world;
}

void World::generate_world()
{
    this->world = new Grid{2, this->tile_diameter, NUMBER_OF_NODES_AXIS, 0, 0};

    for (int total_maps{0}; total_maps < world->map_count; ++total_maps) {
        for (int i{0}; i < world->number_of_nodes; ++i) {
            for (int j{0}; j < world->number_of_nodes; ++j) {
                unsigned short int value{0};

                if ((i != 0 && j != 0 && i != number_of_nodes - 1
                     && j != number_of_nodes - 1)
                    && GetRandomValue(0, 100) > 10)
                    value = GetRandomValue(1, NUMBER_OF_GRD_TEXTURES - 1);

                world->world[total_maps][i][j]
                    = (node){value, (float)(i * world->node_diameter),
                             (float)(j * world->node_diameter)};
            }
        }
        this->world->types[total_maps] = GetRandomValue(0, 2);
    }
}

bool World::load_world()
{
    unsigned int how_many_bytes{0};
    this->world
        = (Grid*)LoadFileData((this->map_filename).c_str(), &how_many_bytes);

    if (how_many_bytes < sizeof(Grid) || !this->world)
        return false;

    this->file_loaded = true;
    return this->file_loaded;
}

void World::load_actors()
{
    for (int i{0}; i < world->number_of_nodes; ++i) {
        for (int j{0}; j < world->number_of_nodes; ++j) {
            node* curr_node       = &(world->world[this->curr_map][j][i]);
            Vector2 curr_node_pos = curr_node->screen_pos;
            bool obstacle         = false;
            /* now we add in the offset and center our node */
            curr_node_pos.x += (this->tile_diameter / 2.0f) + this->top_left_x;
            curr_node_pos.y += (this->tile_diameter / 2.0f) + this->top_left_y;

            if (curr_node->count == 0)
                obstacle = true;

            /* now create a tile with that position */
            this->tiles.emplace_back(new Tile(
                this->getGame(), curr_node_pos,
                get_texture_name_from_int(curr_node->count), obstacle));
        }
    }
}

void World::unload_actors ()
{
  for (Tile* tile : this->tiles)
    tile->setState(Actor::State::Dead);
}

std::string World::get_texture_name_from_int(unsigned short int number)
{
    char temp[100]{0};
    unsigned short int theme = world->types[this->curr_map];

    sprintf(temp, texture_names[theme], "", number);
    return (std::string)temp;
}
