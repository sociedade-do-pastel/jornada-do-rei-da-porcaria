#include "../include/MoveComponent.hpp"

#include "../include/Actor.hpp"

MoveComponent::MoveComponent(Actor* owner, int updateOrder)
    : Component(owner, updateOrder)
{
}

MoveComponent::~MoveComponent()
{
}

void MoveComponent::update()
{
	if (m_angularSpeed >= 0.001f) {
		float rot = m_owner->getRotation();
		rot += m_angularSpeed * GetFrameTime();
		m_owner->setRotation(rot);
	}
    if (m_forwardSpeed >= 0.001f) {
		Vector2 pos = m_owner->getPosition();
    }
}
