#pragma once

#include <string>
#include <unordered_map>
struct ShaderProgramSource
{
	std::string VertexSource;
	std::string FragmentSource;
};
class Shader
{
private:
	std::string m_FilePath;
	unsigned int m_RendererID;
	//caching for uniform;
	std::unordered_map<std::string, int> m_uniformLocationCache;

public:
	Shader(const std::string& filepath);
	~Shader();

	void Bind() const;
	void Unbind() const;

	// set uniform
	void SetUniform1i(const std::string& name, int value);
	void SetUniform1f(const std::string& name, float value);
	void SetUniform4f(const std::string& name, float v0, float f1, float f2, float f3);

private:
	ShaderProgramSource ParseShader();
	unsigned int CompileShader(unsigned int type, const std::string& source);
	unsigned int CreateShader(const std::string vertexShader, const std::string fragmentShader);
	
	int GetUniformLoaction(const std::string& name);
};