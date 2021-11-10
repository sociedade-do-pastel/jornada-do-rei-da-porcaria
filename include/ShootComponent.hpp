#pragma once

#include <raylib.h>
#include <raymath.h>

#include "Component.hpp"

class ShootComponent : public Component
{
public:
    ShootComponent(Actor* owner);
    virtual ~ShootComponent();

    void update() override;

    void shoot(const Vector2& target);

    // getters
    int getShotInterval() const
    {
        return m_shotInterval;
    }

    float getProjectileSpeed() const
    {
        return m_projectileSpeed;
    }

    // setters
    void setShotInterval(int interval)
    {
        m_shotInterval = interval;
    }

    void setProjectileSpeed(float speed)
    {
        m_projectileSpeed = speed;
    }

private:
    int m_shotInterval;
	int m_framesSinceLastShot;
    float m_projectileSpeed;
};
