#include "Buffer.hpp"
#include "platform/opengl/glBuffer.hpp"

VertexBuffer* VertexBuffer::Create(const std::vector<float>& vertices)
{
	return new glVertexBuffer(vertices);
}

VertexBuffer* VertexBuffer::Create(int size)
{
	return new glVertexBuffer(size);
}

IndexBuffer* IndexBuffer::Create(const std::vector<unsigned>& indices)
{
	return new glIndexBuffer(indices);
}

VertexBuffer* AllocateVertices(const std::vector<float>& baseVertices, int count)
{
	std::vector<float> vertices;
	vertices.resize(baseVertices.size() * count);
	
	for (int i = 0; i < count; ++i)
	{
		std::copy(baseVertices.begin(), baseVertices.end(), vertices.begin() + i * baseVertices.size());
	}

	return VertexBuffer::Create(vertices);
}

IndexBuffer* AllocateIndices(const std::vector<unsigned>& baseIndices, int pointsPerItem, int totalItems)
{
	std::vector<unsigned> indices;

	for (int i = 0; i < totalItems; ++i) {
		for (unsigned index : baseIndices)
			indices.emplace_back(index + i * pointsPerItem);
	}

	return IndexBuffer::Create(indices);
}

VertexArray* VertexArray::Create()
{
	return new glVertexArray;
}

UniformBuffer* UniformBuffer::Create(int size, int binding_point)
{
	return new glUniformBuffer(size, binding_point);
}


