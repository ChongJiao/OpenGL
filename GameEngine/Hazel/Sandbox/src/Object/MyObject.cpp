#include "MyObject.h"
#include <fstream>
#include <set>

struct VectorCompare
{
	bool operator()(glm::u32vec2 v1, glm::u32vec2 v2)
	{
		if (v1.x == v2.x && v1.y == v2.y || v1.x == v2.y && v1.y == v2.x)
			return false;
		return v1.x > v2.x;
	}
};

MyObject::MyObject(
	MyObjectType type, 
	std::string& name, 
	float* data, 
	uint32_t dataSize,
	uint32_t pointLength,
	Hazel::BufferLayout& bufferLayout,
	uint32_t* indices,  
	int indiceCount)
{
	if (indices == nullptr)
	{
		HZ_ASSERT(false, "You Need to support the indice of the vertexes");
		return;
	}
	uint32_t pointSize = dataSize / pointLength;
	m_Points.resize(pointSize);
	for (uint32_t i = 0; i < pointSize; i++)
	{
		glm::vec3 point(data[i * pointLength], data[i * pointLength + 1], data[i * pointLength + 2]);
		m_Points[i] = point;
	}
	m_Faces.resize(indiceCount / 3);
	std::set<glm::u32vec2, VectorCompare> edgeSet;
	
	for (uint32_t i = 0; i < indiceCount / 3; i++)
	{
		m_Faces[i].x = indices[i * 3];
		m_Faces[i].y = indices[i * 3 + 1];
		m_Faces[i].z = indices[i * 3 + 2];

		glm::u32vec2 edge1(indices[i * 3], indices[i * 3 + 1]);
		glm::u32vec2 edge2(indices[i * 3 + 1], indices[i * 3 + 2]);
		glm::u32vec2 edge3(indices[i * 3 + 2], indices[i * 3]);

		edgeSet.insert(edge1);
		edgeSet.insert(edge2);
		edgeSet.insert(edge3);
	}
	m_Edges.assign(edgeSet.begin(), edgeSet.end());

	m_VextexArray = Hazel::VertexArray::Create();
	Hazel::Ref<Hazel::VertexBuffer> vb = Hazel::VertexBuffer::Create(data, dataSize);
	vb->SetLayout({
		bufferLayout
		});

	Hazel::Ref<Hazel::IndexBuffer> ib = Hazel::IndexBuffer::Create(indices, indiceCount);
	m_VextexArray->AddVertexBuffer(vb);
	m_VextexArray->SetIndexBuffer(ib);

	m_VextexArray->Bind();
}

MyObject::MyObject(std::string& file)
{
	std::string fileStringSrc = ReadFile(file);
	if (fileStringSrc.size() == 0)
	{
		return;
	}
	LoadMesh(fileStringSrc);
}

MyObject::MyObject(MyObject& object)
{
	//copy contruct
}

MyObject& MyObject::operator=(MyObject& object)
{
	// TODO: 在此处插入 return 语句
	return *this;
}

std::string MyObject::ReadFile(std::string& file)
{
	std::string result;
	std::ifstream in(file, std::ios::in | std::ios::binary);
	if (in)
	{
		in.seekg(0, std::ios::end);
		size_t size = in.tellg();
		if (size != -1)
		{
			result.resize(size);
			in.seekg(0, std::ios::beg);
			in.read(&result[0], size);
			in.close();
		}
		else
		{
			HZ_ERROR("Could not read from the file from {0}", file);
		}
	}
	else
	{
		HZ_ERROR("Could not open file {0}", file);
	}
	return result;
}

void MyObject::LoadMesh(std::string& fileStringSrc)
{
	size_t start = fileStringSrc.find_first_of("v ");

	std::vector<std::string> linesStr;
	if (start == std::string::npos)
	{
		HZ_ERROR("The file do not support the mesh format");
		return;
	}
	else
	{
		size_t end = fileStringSrc.find_first_of("\r\n");
		
		while (end <= std::string::npos)
		{
			linesStr.emplace_back(fileStringSrc.substr(start, end));

			if (end == std::string::npos)
				break;
			
			start = end + 1;
			end = fileStringSrc.find_first_of("\r\n", start);
		}
	}


}

glm::vec3 MyObject::CalculateCenter()
{
	glm::vec3 Center(0.0f, 0.0f, 0.0f);
	
	for (glm::vec3 point : m_Points)
	{
		Center.x += point.x;
		Center.y += point.y;
		Center.z += point.z;
	}
	Center /= m_Points.size();
	return Center;
}

void MyObject::ApplyTransform(const glm::mat4& transform)
{
	for (int i = 0; i < m_Points.size(); i ++)
	{
		auto pos = transform * glm::vec4(m_Points[i], 1.0f);
		m_Points[i].x = pos.x;
		m_Points[i].y = pos.y;
		m_Points[i].z = pos.z;
	}
}

bool InsideTriangle(glm::vec3 p, glm::vec3 v1, glm::vec3 v2, glm::vec3 v3)
{
	glm::vec3 f0, f1, f2;
	f0 = glm::cross(v2, v1);
	f1 = glm::cross(v3, v2);
	f2 = glm::cross(v1, v3);

	return false;
}

bool DoCollision2DBySeparatingAxis(const MyObject& obj1, const MyObject& obj2)
{

	//from https://en.wikipedia.org/wiki/Hyperplane_separation_theorem
	//当所有投影边都相交的时候，证明碰撞了
	auto edges1 = obj1.GetEdges();
	auto edges2 = obj2.GetEdges();
	auto points1 = obj1.GetPoints();
	auto points2 = obj2.GetPoints();

	for (auto e1 : edges1)
	{
		auto p1 = points1[e1.x];
		auto p2 = points1[e1.y];

		glm::vec3 edgeVector = p2 - p1;
		glm::vec3 zVector(0.f, 0.f, 1.0f);
		auto edgeNormal = glm::normalize(glm::cross(edgeVector, zVector));

		glm::vec3 NP1(0, 0, 0);
		glm::vec3 NP2 = NP1 + edgeNormal;
		//计算所有边的投影范围
		glm::vec3 minPoints;
		glm::vec3 maxPoints;

		float minK1 = std::numeric_limits<float>::max();
		float maxK1 = std::numeric_limits<float>::min();

		for (auto P0 : points1)
		{
			float k = glm::dot(P0 - NP1, edgeNormal);

			if (k > maxK1) maxK1 = k;
			if (k < minK1) minK1 = k;
		}

		float minK2 = std::numeric_limits<float>::max();
		float maxK2 = std::numeric_limits<float>::min();

		for (auto P0 : points2)
		{
			float k = glm::dot(P0 - NP1, edgeNormal);

			if (k > maxK1) maxK2 = k;
			if (k < minK1) minK2 = k;
		}

		float max = std::max({ minK1, maxK1, minK2, maxK2 });
		float min = std::min({ minK1, maxK1, minK2, maxK2 });
		if (max - min > (maxK1 - minK1) + (maxK2 - minK2))
			return false;
	}
	return true;
}

bool DoCollisionByAABB(const MyObject& object1, const MyObject& object2)
{
	//AABB 检测盒来判断检测
	return false;
}

bool ObjectCollision(const MyObject& object1, const MyObject& object2, ObjectCollisionMethod& method)
{
	switch (method)
	{
	case ObjectCollisionMethod::None: HZ_ERROR("You should specific a collision way") return false;
	case ObjectCollisionMethod::AABB: return DoCollisionByAABB(object1, object2);
	case ObjectCollisionMethod::SperatingAxis: return DoCollision2DBySeparatingAxis(object1, object2);
	default:
		return false;
		break;
	}
}
