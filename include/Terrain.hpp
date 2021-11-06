#pragma once
#define NUM_GENERIC_TEXTURES 5
#include <raylib.h>
#include <string>

class Terrain
{
private:
    unsigned type_of_terrain{0};
    std::string ground_textures[NUM_GENERIC_TEXTURES];
    std::string animated_texture;

public:
    Terrain(unsigned type);
    std::string get_random_tile_texture_name();
    bool load_structures(std::string filename_prefix);
    std::string get_animated_texture_name();
    std::string get_filename(unsigned type);
    void change_terrain(unsigned type);
};
