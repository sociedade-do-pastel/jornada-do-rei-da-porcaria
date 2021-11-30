#pragma once

#include <string>

#include "Actor.hpp"

class LifeHUD : public Actor
{
public:
    LifeHUD(Game* game);
    virtual ~LifeHUD();

    void updateActor() override;
    void drawHP(int hp);

private:
    Texture2D m_texture;
};
