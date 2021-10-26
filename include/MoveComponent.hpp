#pragma once

#include "Component.hpp"

// forward declaration
class Actor;

class MoveComponent : public Component
{
public:
    MoveComponent(Actor* owner, int updateOrder = 10);
    virtual ~MoveComponent();

    void update() override;

    // getters
    float getAngularSpeed() const
    {
        return m_angularSpeed;
    }

    float getForwardSpeed() const
    {
        return m_forwardSpeed;
    }

    // setters
    void setAngularSpeed(float speed)
    {
        m_angularSpeed = speed;
    }

    void setForwardSpeed(float speed)
    {
        m_forwardSpeed = speed;
    }

private:
    float m_angularSpeed;
    float m_forwardSpeed;
};
