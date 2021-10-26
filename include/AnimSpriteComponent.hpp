#pragma once

#include <string>
#include <vector>

#include "SpriteComponent.hpp"

// forward declaration
class Actor;

class AnimSpriteComponent : public SpriteComponent
{
public:
    AnimSpriteComponent(Actor* owner, int drawOrder = 100);
    virtual ~AnimSpriteComponent();

    void update() override;

    // getters
    int getAnimFPS() const
    {
        return m_frameSpeed;
    }

    // setters
    void setAnimTextures(const std::string texture, int qtFrames)
    {
        setTexture(texture);
        m_qtFrames = qtFrames;

        m_frameRec = {0.0f, 0.0f, (float)m_texture.width / qtFrames,
                      (float)m_texture.height};
    }

    void setFrameSpeed(int speed)
    {
        m_frameSpeed = speed;
    }

private:
    int m_frameCounter{0};
    int m_currentFrame{0};
    int m_qtFrames{0};
    int m_frameSpeed;
};
