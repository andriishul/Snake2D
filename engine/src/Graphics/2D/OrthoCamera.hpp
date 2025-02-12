#pragma once
#include <Graphics/Camera.hpp>

class OrthoCamera : public Camera
{
public:
	explicit OrthoCamera(const glm::vec2 position = { 0, 0 });

	void SetPosition(const glm::vec2 position);
	void SetProjection(float left, float right, float bottom, float top);

	const glm::vec2 GetPosition() const { return m_Position; }
	virtual const glm::mat4 GetViewProjectionMatrix() const override { return m_Projection * m_View; }
private:
	glm::mat4 m_Projection, m_View;
	glm::vec2 m_Position;
};
