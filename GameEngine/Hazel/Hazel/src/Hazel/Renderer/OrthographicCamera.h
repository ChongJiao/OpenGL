#pragma once

#include <glm/glm.hpp>

namespace Hazel
{
	class OrthographicCamera {
	public:
		OrthographicCamera(float left, float right, float bottom, float top);

		void setProjection(float left, float right, float bottom, float top);

		void setPosition(const glm::vec3& position) { m_Position = position; }
		
		void setRotation(float rotation) { m_Rotation = rotation; RecalculateViewMatrix(); }

		const glm::mat4 GetProjectMatrix() { return m_ProjectionMatrix; }
		const glm::mat4 GetViewMatrix() { return m_ViewMatrix; }
		const glm::mat4 GetViewProjectMatrix() { return m_ViewProjectionMatrix; }

		const glm::vec3 GetPosition() { return m_Position; }
		float GetRotation() { return m_Rotation; }
	private:
		void RecalculateViewMatrix();
	private:
		glm::vec3 m_Position = { 0.0f, 0.0f, 0.0f };
		glm::mat4 m_ProjectionMatrix;
		glm::mat4 m_ViewMatrix;
		glm::mat4 m_ViewProjectionMatrix;
	
		float m_Rotation = 0.0f;
	};
}