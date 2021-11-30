#include "../include/Moth.hpp"
#include <raylib.h>
#include <raymath.h>
#include "../include/AnimSpriteComponent.hpp"
#include "../include/Tile.hpp"
#include "../include/World.hpp"

Moth::Moth(Game* game) : Enemy(game)
{
    AnimSpriteComponent* anim = new AnimSpriteComponent(this, 99);
    anim->setAnimTextures("brabuleta.png", 2);
    anim->setFrameSeq({0, 1});
    m_spc = anim;

    auto grd_c = (new GridComponent(this));
    this->setGrid(grd_c);
    auto ai_c = (new AIComponent(this, grd_c));
    ai_c->setFlying(true);
    this->setAI(ai_c);

    ai_c->setTarget((Actor*)this->getGame()->getPlayer());

    move_component = new MoveComponent(this);
    this->setSpeed(100.0);

	setWeight(5);
	setHP(2);
}

Moth::~Moth()
{
}

// TODO: maybe make this following behaviour a component
void Moth::updateActor()
{
	Enemy::updateActor();
	
    // if we don't have a path, just stay in place
    if (this->getAI()->getCurrentPath().empty()) {
        move_component->setHorizontalSpeed(0);
        move_component->setVerticalSpeed(0);
        return;
    }

    // get our current target (a node) and translate it to its current
    // position on screen
    Vector2 curr_targ{
        this->getGrid()->get_translated(this->getAI()->getCurrentPath().top())};

    float radius = this->getGame()->getWorld()->get_tile_diameter() / 2.0f;
    curr_targ.x += radius;
    curr_targ.y += radius;

    // get our current position and calculate the (euclidean) distance between
    // we and our target
    Vector2 orc_pos = this->getPosition();
    float distance  = Vector2Distance(orc_pos, curr_targ);

    if (distance >= 0.0 && distance < 1.0) {
        this->getAI()->getCurrentPath().pop();
        return;
    }

    float delta_x = curr_targ.x - orc_pos.x;
    float delta_y = curr_targ.y - orc_pos.y;

    move_component->setHorizontalSpeed((delta_x * getSpeed()) / distance);
    move_component->setVerticalSpeed((delta_y * getSpeed()) / distance);
}

void Moth::processKeyboard()
{
}
