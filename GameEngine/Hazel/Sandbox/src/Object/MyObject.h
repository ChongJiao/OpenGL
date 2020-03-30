#pragma once
#include "Hazel.h"
#include <vector>
enum class MyObjectType
{
	None = 0, MyTriangle, MyRectangle
};
enum class ObjectCollisionMethod
{
	None = 0, AABB, SperatingAxis
};

class MyObject
{
public:
	MyObject(MyObjectType type, std::string& name, 
		float* data, 
		uint32_t dataSize,
		uint32_t pointLength,
		Hazel::BufferLayout& bufferLayout,
		uint32_t* indices = nullptr, 
		int indiceCount = 0);
	MyObject(std::string& file);

	//Copy construction;
	MyObject(MyObject& object);
	
	//Copy assignment
	MyObject& operator=(MyObject& object);

	std::string ReadFile(std::string& file);
	void LoadMesh(std::string& fileStringSrc);
	
	glm::vec3 CalculateCenter();
	void ApplyTransform(const glm::mat4& transform);

	const MyObjectType& GetType() { return m_Type; }

	inline const std::vector<glm::vec3>& GetPoints() const { return m_Points; }
	inline const std::vector<glm::u32vec3>& GetFaces() const { return m_Faces; }
	inline const std::vector<glm::u32vec2>& GetEdges() const { return m_Edges; }
	inline const std::vector<glm::vec2>& GetTextureCoord2() const {return m_TextureCoord2;}
	inline const std::vector<glm::vec3>& GetVertexNormalCoords() const { return m_VertexNormalCoord; }
	inline const Hazel::Ref<Hazel::VertexArray> GetVextexArray() const { return m_VextexArray; }
private:
	MyObjectType m_Type = MyObjectType::None;

	Hazel::Ref<Hazel::VertexArray> m_VextexArray;
	
	std::vector<glm::vec3> m_Points;
	std::vector<glm::u32vec3> m_Faces;
	std::vector<glm::u32vec2> m_Edges;
	std::vector<glm::vec2> m_TextureCoord2;
	std::vector<glm::vec3> m_VertexNormalCoord;
};

bool ObjectCollision(const MyObject& object1, const MyObject& object2, ObjectCollisionMethod& method);