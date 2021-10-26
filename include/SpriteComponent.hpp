#pragma once

#include <raylib.h>
#include <string>

#include "Component.hpp"

// forward declaration
class Actor;

class SpriteComponent : public Component
{
public:
    SpriteComponent(Actor* owner, int drawOrder = 100);
    virtual ~SpriteComponent();

    void update() override;
    virtual void draw();

    // getters
    int getDrawOrder() const
    {
        return m_drawOrder;
    }

    int getTexHeight() const
    {
        return m_texHeight;
    }

    int getTexWidth() const
    {
        return m_texWidth;
    }

    int getTexSize() const
    {
        return 0;
    }

    // setters
    virtual void setTexture(std::string texture)
    {
        m_texture = LoadTexture(texture.c_str());
    }

protected:
    Rectangle m_frameRec;
    Texture2D m_texture;

private:
    int m_drawOrder;
    int m_texWidth;
    int m_texHeight;
};
