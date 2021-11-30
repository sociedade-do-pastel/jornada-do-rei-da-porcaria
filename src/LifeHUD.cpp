#include "../include/LifeHUD.hpp"

#include "../include/Game.hpp"

LifeHUD::LifeHUD(Game* game) : Actor(game)
{
    m_texture = getGame()->getTexture("cabecao.png");
}

LifeHUD::~LifeHUD()
{
}

void LifeHUD::updateActor()
{
}

void LifeHUD::drawHP(int hp)
{
    std::string t = "x" + std::to_string(hp);

    DrawTexture(m_texture, getPosition().x, getPosition().y, WHITE);
    DrawText(t.c_str(), getPosition().x + 40, getPosition().y + 5, 25, WHITE);
}
