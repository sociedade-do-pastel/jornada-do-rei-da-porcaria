#include "../include/Tile.hpp"
#include "../include/AnimSpriteComponent.hpp"
#include "../include/SpriteComponent.hpp"

Tile::Tile(Game* game, Vector2 position, std::string terrain_type,
           bool obstacle)
    : Actor{game}, m_is_obstacle{obstacle}
{
    this->setPosition(position);

    // am I a tree?
    if (obstacle) {
        auto sprite_anim = (new AnimSpriteComponent(this, 10));
        sprite_anim->setAnimTextures(terrain_type, 2);
        sprite_anim->setFrameSeq({0, 1});
        sprite_anim->setFrameSpeed(1);
        // new CollisionComponent
    }
    else
        (new SpriteComponent(this, 10))->setTexture(terrain_type);
}

Tile::~Tile()
{
}

void Tile::updateActor()
{
    Actor::updateActor();
}
