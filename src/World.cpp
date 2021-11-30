#include "../include/World.hpp"
#include "../include/Moth.hpp"
#include "../include/Orc.hpp"
#include "../include/SpawnComponent.hpp"

World::World(Game* game, const unsigned top_left_x, const unsigned top_left_y)
    : Actor{game}, top_left_x{top_left_x}, top_left_y{top_left_y},
      spawn_points{0, 7, 0, 8, 0, 9, 15, 7,  15, 8,  15, 9,
                   7, 0, 8, 0, 9, 0, 7,  15, 8,  15, 9,  15}
{
    if (!load_world())
        generate_world();

    load_actors();
}

World::~World()
{
    if (this->file_loaded)
        UnloadFileData((unsigned char*)this->main_grid);
    else
        delete this->main_grid;
}

void World::generate_world()
{
    this->main_grid
        = new Grid{2, this->tile_diameter, NUMBER_OF_NODES_AXIS, 0, 0};

    for (int total_maps{0}; total_maps < main_grid->map_count; ++total_maps) {
        for (int i{0}; i < main_grid->number_of_nodes; ++i) {
            for (int j{0}; j < main_grid->number_of_nodes; ++j) {
                unsigned short int value{0};

                if (std::find_if(spawn_points.begin(), spawn_points.end(),
                                 [=](Vector2& pos) {
                                     return (pos.x == j && pos.y == i);
                                 })
                    != spawn_points.end())
                    value = 1;
                else if ((i != 0 && j != 0 && i != number_of_nodes - 1
                          && j != number_of_nodes - 1)
                         && GetRandomValue(0, 100) > 10)
                    value = GetRandomValue(2, NUMBER_OF_GRD_TEXTURES - 1);

                node* temp       = &(main_grid->world[total_maps][i][j]);
                temp->count      = value;
                temp->i          = i;
                temp->j          = j;
                temp->screen_pos = {(float)(j * main_grid->node_diameter),
                                    (float)(i * main_grid->node_diameter)};
            }
        }
        this->main_grid->types[total_maps] = GetRandomValue(0, 2);
    }
}

bool World::load_world()
{
    unsigned int how_many_bytes{0};
    this->main_grid
        = (Grid*)LoadFileData((this->map_filename).c_str(), &how_many_bytes);

    if (how_many_bytes < sizeof(Grid) || !this->main_grid)
        return false;

    this->file_loaded = true;
    return this->file_loaded;
}

void World::load_actors()
{
    for (int i{0}; i < main_grid->number_of_nodes; ++i) {
        for (int j{0}; j < main_grid->number_of_nodes; ++j) {
            node* curr_node       = &(main_grid->world[this->curr_map][i][j]);
            Vector2 curr_node_pos = curr_node->screen_pos;
            bool obstacle         = false;
            /* now we add in the offset and center our node */
            curr_node_pos.x += (this->tile_diameter / 2.0f) + this->top_left_x;
            curr_node_pos.y += (this->tile_diameter / 2.0f) + this->top_left_y;

            if (curr_node->count == 0)
                obstacle = true;

            Tile* curr_tile{new Tile(
                this->getGame(), curr_node_pos,
                get_texture_name_from_int(curr_node->count), obstacle)};

            /* now put that tile in our tile list */
            this->tiles.emplace_back(curr_tile);

            /* and also see if it's a spawn tile */
            if (curr_node->count == 1)
                place_spawn_tile(curr_tile);
        }
    }
}

void World::unload_actors()
{
    for (Tile* tile : this->tiles)
        tile->setState(Actor::State::Dead);
}

std::string World::get_texture_name_from_int(unsigned short int number)
{
    char temp[100]{0};
    unsigned short int theme = main_grid->types[this->curr_map];

    sprintf(temp, texture_names[theme], "", number);
    return (std::string)temp;
}

void World::place_spawn_tile(Tile* spawn_tile)
{
    (this->getGame()->getSpawnTiles()).emplace_back(spawn_tile);
	new SpawnComponent<Moth>(spawn_tile, getGame()->getRunningTime());
	new SpawnComponent<Orc>(spawn_tile, getGame()->getRunningTime());
}
