#include "../include/Orc.hpp"
#include <raylib.h>
#include <raymath.h>
#include "../include/AnimSpriteComponent.hpp"
#include "../include/Tile.hpp"
#include "../include/World.hpp"

Orc::Orc(Game* game) : Enemy(game)
{
    AnimSpriteComponent* anim = new AnimSpriteComponent(this, 99);
    anim->setAnimTextures("orcson.png", 2);
    anim->setFrameSeq({0, 1});
    m_spc = anim;

    auto grd_c = (new GridComponent(this));
    this->setGrid(grd_c);
    auto ai_c = (new AIComponent(this, grd_c));
    this->setAI(ai_c);
    ai_c->setTarget((Actor*)this->getGame()->getPlayer());

    move_component = new MoveComponent(this);
    this->setSpeed(100.0);

	setWeight(200);
    setHP(3);
}

Orc::~Orc()
{
}

// TODO: maybe make this following behaviour a component
void Orc::updateActor()
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

    // center it so this orc tries to walk ON the nodes, rather than between
    // them
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

void Orc::processKeyboard()
{
}
