#include "../include/Component.hpp"

#include "../include/Actor.hpp"

Component::Component(Actor* owner, int updateOrder)
    : m_owner(owner), m_updateOrder(updateOrder)
{
    m_owner->addComponent(this);
}

Component::~Component()
{
    m_owner->removeComponent(this);
}

void Component::update()
{
}

void Component::processInput()
{
}
