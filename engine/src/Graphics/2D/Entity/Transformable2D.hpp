#pragma once
#include <glm/glm.hpp>

class Transformable2D
{
protected:
	Transformable2D(glm::vec2 position, glm::vec2 scale,
		glm::vec3 color, float rotation) 
	{
		SetPosition(position);
		SetColor(color);
		SetScale(scale);
		SetRotation(rotation);
	}
public:
	Transformable2D() = delete;

	void SetPosition(const glm::vec2 position) { m_Position = position; }
	const glm::vec2 GetPosition() const { return m_Position; }

	void SetScale(const glm::vec2 scale) { m_Scale = scale; }
	const glm::vec2 GetScale() const { return m_Scale; }

	void SetColor(const glm::vec3 color) { m_Color = color; }
	const glm::vec3 GetColor() const { return m_Color; }

	void SetRotation(const float rotation) { if (rotation >= 360) m_Rotation = 0; m_Rotation = rotation; }
	float GetRotation() const { return m_Rotation; }
private:
	glm::vec2 m_Position, m_Scale;
	float m_Rotation;
	glm::vec3 m_Color;
};