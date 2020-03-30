#pragma once
#include "Hazel.h"


class FlipperBird : public Hazel::Layer
{
public:
	FlipperBird(std::string& name);

	virtual void OnAttach() override;
	virtual void OnDetach() override;

	virtual void OnUpdate(Hazel::Timestep ts) override;

	virtual void OnImGuiRender() override;
	virtual void OnEvent(Hazel::Event& e) override;

private:
	void initMountain();
	void initFlipperBird();
	Hazel::ShaderLibrary m_ShaderLibrary;

	Hazel::Ref<Hazel::Shader> m_MountainShader;
	Hazel::Ref<Hazel::VertexArray> m_MountainVertexArray;

	Hazel::Ref<Hazel::Texture2D> m_MountainTexture, m_FlipperBirdTexture;

	Hazel::Ref<Hazel::Shader> m_FlipperBirdShader;
	Hazel::Ref<Hazel::VertexArray> m_FlipperBirdVertexArray;

	Hazel::OrthographicCameraController m_CameraController;
};