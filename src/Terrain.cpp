#include "../include/Terrain.hpp"

Terrain::Terrain(unsigned type) : type_of_terrain{type}
{
    change_terrain(type);
}

void Terrain::change_terrain(unsigned type)
{
    // since our filenames are in a way "hardcoded"
    std::string filename_prefix{get_filename(type)};
    // load our array of generic textures (they aren't animated)
    // since this returns a bool, it'd be nice to do some error checking
    load_structures(filename_prefix);
}

std::string Terrain::get_filename(unsigned type)
{
    switch (type) {
    case 0:
        return "pradaria"; // no need to break
    case 1:
        return "neve";
    default:
        return "deserto";
    }
}

bool Terrain::load_structures(std::string filename_prefix)
{
    std::string extension{".png"};
    for (int i{0}; i < NUM_GENERIC_TEXTURES; ++i) {
        ground_textures[i]
            = filename_prefix + std::to_string(i + 1) + extension;
    }

    animated_texture = filename_prefix + "_anim" + extension;
    return true;
}

std::string Terrain::get_random_tile_texture_name()
{
    return ground_textures[GetRandomValue(0, NUM_GENERIC_TEXTURES - 1)];
}

std::string Terrain::get_animated_texture_name()
{
    return animated_texture;
}
