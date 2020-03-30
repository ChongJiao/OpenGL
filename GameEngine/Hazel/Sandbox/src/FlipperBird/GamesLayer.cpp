#include "GamesLayer.h"

FlipperBird::FlipperBird(std::string& name)
	: Layer(name), m_CameraController(1280.0f / 720.0f)
{


}

void FlipperBird::OnAttach()
{
}

void FlipperBird::OnDetach()
{
}

void FlipperBird::OnUpdate(Hazel::Timestep ts)
{
}

void FlipperBird::OnImGuiRender()
{
}

void FlipperBird::OnEvent(Hazel::Event& e)
{
}

void FlipperBird::initMountain()
{
	m_MountainVertexArray = Hazel::VertexArray::Create();
	float mountainVertex[] =
	{
		-0.3f, -0.3f, 0.0f, 0.0f, 0.0f,
		 0.3f, -0.3f, 0.0f, 1.0f, 0.0f,
		 0.0f,  0.2f, 0.0f, 1.0f, 1.0f,
	};

}

void FlipperBird::initFlipperBird()
{
	m_FlipperBirdVertexArray = Hazel::VertexArray::Create();

	float flipperBirdVertex[] = {
		-0.05f, -0.05f, 0.0f, 0.0f, 0.0f,
		 0.05f, -0.05f, 0.0f, 1.0f, 0.0f,
		 0.05f,  0.05f, 0.0f, 1.0f, 1.0f,
		-0.05f,  0.05f, 0.0f, 0.0f, 1.0f
	};

	Hazel::Ref<Hazel::VertexBuffer> flipperVB = Hazel::VertexBuffer::Create(flipperBirdVertex, sizeof(flipperBirdVertex));
	flipperVB->SetLayout({
		{ Hazel::ShaderDataType::Float3, "a_Position" },
		{ Hazel::ShaderDataType::Float2, "a_TexCoord" }
		});
	m_FlipperBirdVertexArray->AddVertexBuffer(flipperVB);
	uint32_t flipperIndices[] = { 0, 1, 2, 2, 3, 0 };
	Hazel::Ref<Hazel::IndexBuffer> flipperIB = Hazel::IndexBuffer::Create(flipperIndices, sizeof(flipperIndices) / sizeof(uint32_t));
	m_FlipperBirdVertexArray->SetIndexBuffer(flipperIB);

	m_FlipperBirdShader = Hazel::Shader::Create("assets/shaders/Texture.glsl");
	m_FlipperBirdTexture = Hazel::Texture2D::Create("assets/textures/flipperBird.png");
}
