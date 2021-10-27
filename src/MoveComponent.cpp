#include "../include/MoveComponent.hpp"

#include "../include/Actor.hpp"

MoveComponent::MoveComponent(Actor* owner, int updateOrder)
    : Component(owner, updateOrder), m_verticalSpeed(0.0f),
      m_horizontalSpeed(0.0f)
{
}

MoveComponent::~MoveComponent()
{
}

void MoveComponent::update()
{
    Vector2 pos = m_owner->getPosition();
	
    pos.x += m_horizontalSpeed * GetFrameTime();
	pos.y += m_verticalSpeed * GetFrameTime();
	
    m_owner->setPosition(pos);
}
