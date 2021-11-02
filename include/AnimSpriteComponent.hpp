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

        m_frameRec = {1.0f, 1.0f,
                      static_cast<float>(m_texture.width / qtFrames - 2.0f),
                      static_cast<float>(m_texture.height - 2.0f)};
    }

  void setAnimTextures(Texture texture, int qtFrames)
    {
        setTexture(texture);
        m_qtFrames = qtFrames;

        m_frameRec = {1.0f, 1.0f,
                      static_cast<float>(m_texture.width / qtFrames - 2.0f),
                      static_cast<float>(m_texture.height - 2.0f)};
    }

    void setFrameSpeed(int speed)
    {
        m_frameSpeed = speed;
    }

    void setFrameSeq(std::vector<int> seq)
    {
        m_frameSeq = seq;
    }

private:
    int m_frameCounter{0};
    int m_currentFrame{0};
    int m_qtFrames{0};
    int m_frameSpeed;

    std::vector<int> m_frameSeq;
    int m_seqCounter;
};
