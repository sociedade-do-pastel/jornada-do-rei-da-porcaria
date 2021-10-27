#include "../include/SpriteComponent.hpp"

#include "../include/Actor.hpp"
#include "../include/Game.hpp"

SpriteComponent::SpriteComponent(Actor* owner, int drawOrder)
    : Component(owner), m_texture(), m_frameRec(), m_drawOrder(drawOrder),
      m_texWidth(0), m_texHeight(0)
{
    m_owner->getGame()->addSprite(this);
}

SpriteComponent::~SpriteComponent()
{
    UnloadTexture(m_texture);
    m_owner->getGame()->removeSprite(this);
}

void SpriteComponent::update()
{
    m_frameRec = {1.0f, 0.0f, static_cast<float>(m_texture.width - 2.0f),
                  static_cast<float>(m_texture.height)};
}

void SpriteComponent::draw()
{

    DrawTextureRec(m_texture, m_frameRec, m_owner->getPosition(), WHITE);
}
