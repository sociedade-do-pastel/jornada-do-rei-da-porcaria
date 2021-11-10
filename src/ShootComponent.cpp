#include "../include/ShootComponent.hpp"

#include "../include/Actor.hpp"
#include "../include/Bullet.hpp"

ShootComponent::ShootComponent(Actor* owner)
    : Component(owner), m_framesSinceLastShot(0)
{
}

ShootComponent::~ShootComponent()
{
}

void ShootComponent::update()
{
    if (m_framesSinceLastShot < m_shotInterval)
        ++m_framesSinceLastShot;
}

void ShootComponent::shoot(const Vector2& target)
{
    if (m_framesSinceLastShot < m_shotInterval)
        return;

    auto b = new Bullet(m_owner->getGame());

    Vector2 m = target;
    Vector2 s = m_owner->getPosition();

    float angle = atan2(m.y - s.y, m.x - s.x);
    float vx    = cos(angle) * m_projectileSpeed;
    float vy    = sin(angle) * m_projectileSpeed;

    b->setPosition(s);
    b->setForwardDirection({vx, vy});
    m_framesSinceLastShot = 0;
}
