#include "OrthoCamera.hpp"
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>

OrthoCamera::OrthoCamera(const glm::vec2 position)
{
	SetPosition(position);
	SetProjection(-1, 1, -1, 1);
}

void OrthoCamera::SetPosition(const glm::vec2 position)
{
	m_Position = position;

	m_View = glm::inverse(glm::translate(glm::mat4(1.0f), glm::vec3(m_Position, 0.0)));
}

void OrthoCamera::SetProjection(float left, float right, float bottom, float top)
{
	m_Projection = glm::ortho(left, right, bottom, top);
}


