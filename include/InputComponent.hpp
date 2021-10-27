#pragma once

#include "MoveComponent.hpp"

// forward declaration
class Actor;

class InputComponent : public MoveComponent
{
public:
    // Lower update order to update first
    InputComponent(Actor* owner);

    void processInput() override;

    // getters
	float getMaxVerticalSpeed()
	{
		return m_maxVerticalSpeed;
	}

	float getMaxHorizontalSpeed()
	{
		return m_maxHorizontalSpeed;
	}

	int getUpKey()
	{
		return m_upKey;
	}

	int getDownKey()
	{
		return m_downKey;
	}

	int getLeftKey()
	{
		return m_leftKey;
	}

	int getRightKey()
	{
		return m_rightKey;
	}

	// setters
	void setMaxVerticalSpeed(float speed)
	{
		m_maxVerticalSpeed = speed;;
	}

	void setMaxHorizontalSpeed(float speed)
	{
		m_maxHorizontalSpeed = speed;
	}

	void setUpKey(int key)
	{
		m_upKey = key;
	}

	void setDownKey(int key)
	{
		m_downKey = key;
	}

	void setLeftKey(int key)
	{
		m_leftKey = key;
	}

	void setRightKey(int key)
	{
		m_rightKey = key;
	}

	
private:
    float m_maxVerticalSpeed;
    float m_maxHorizontalSpeed;

    int m_upKey;
    int m_downKey;
    int m_leftKey;
    int m_rightKey;
};
