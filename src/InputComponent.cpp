#include "../include/InputComponent.hpp"

#include "../include/Actor.hpp"

InputComponent::InputComponent(Actor* owner)
    : MoveComponent(owner), m_upKey(0), m_downKey(0), m_leftKey(0),
      m_rightKey(0)
{
}

void InputComponent::processInput()
{
    float verticalSpeed   = 0.0f;
    float horizontalSpeed = 0.0f;

    if (IsKeyDown(m_upKey))
        verticalSpeed -= m_maxVerticalSpeed;
    if (IsKeyDown(m_downKey))
        verticalSpeed += m_maxVerticalSpeed;

    setVerticalSpeed(verticalSpeed);

    if (IsKeyDown(m_leftKey))
        horizontalSpeed -= m_maxHorizontalSpeed;
    if (IsKeyDown(m_rightKey))
        horizontalSpeed += m_maxHorizontalSpeed;

    setHorizontalSpeed(horizontalSpeed);
}
