#pragma once
#define NUM_GENERIC_TEXTURES 5
#include <raylib.h>
#include <string>

class Terrain
{
private:
    unsigned type_of_terrain{0};
    Texture ground_textures[NUM_GENERIC_TEXTURES];
    Texture animated_texture;

public:
    Terrain(unsigned type);
    Texture get_random_tile_texture();
    bool load_structures(std::string filename_prefix);
    Texture get_animated_texture();
    std::string get_filename(unsigned type);
    void change_terrain(unsigned type);
};
