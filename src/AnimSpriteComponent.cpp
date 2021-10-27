#include "../include/AnimSpriteComponent.hpp"

AnimSpriteComponent::AnimSpriteComponent(Actor* owner, int drawOrder)
    : SpriteComponent(owner, drawOrder), m_frameSpeed(8)
{
}

AnimSpriteComponent::~AnimSpriteComponent()
{
}

void AnimSpriteComponent::update()
{
    ++m_frameCounter;

    if (m_frameCounter >= (60 / m_frameSpeed)) {
        m_frameCounter = 0;

        ++m_seqCounter;
        if (m_seqCounter >= m_frameSeq.size())
            m_seqCounter = 0;

        m_currentFrame = m_frameSeq[m_seqCounter];

        m_frameRec.x = static_cast<float>(
            m_currentFrame * m_texture.width / m_qtFrames + 1);
        m_frameRec.width = m_texture.width / m_qtFrames - 2.0f;
    }
}
