#pragma once

#include <iostream>
#include <raymath.h>

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
    float getVerticalSpeed() const
    {
        return m_verticalSpeed;
    }

    float getHorizontalSpeed() const
    {
        return m_horizontalSpeed;
    }

    // setters
    void setVerticalSpeed(float speed)
    {
        m_verticalSpeed = speed;
    }

    void setHorizontalSpeed(float speed)
    {
        m_horizontalSpeed = speed;
    }

private:
    float m_verticalSpeed;
    float m_horizontalSpeed;
};
