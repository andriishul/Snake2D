#pragma once
#include <string>
#include <vector>

enum class ShaderDataType
{
	Float, Float2, Float3, Float4, Mat3, Mat4, Int, Int2, Int3, Int4, Bool
};

struct BufferElement
{
	std::string name;
	ShaderDataType shaderType;
	bool normalized;
	unsigned offset, size;

	BufferElement(std::string const& name, ShaderDataType const& shaderType) :
		offset(0), name(name), normalized(false), size(0), shaderType(shaderType)
	{
		switch (shaderType)
		{
			case ShaderDataType::Float:    size = 4; return;
			case ShaderDataType::Float2:   size = 4 * 2; return;
			case ShaderDataType::Float3:   size = 4 * 3; return;
			case ShaderDataType::Float4:   size = 4 * 4; return;
			case ShaderDataType::Mat3:     size = 4 * 3 * 3; return;
			case ShaderDataType::Mat4:     size = 4 * 4 * 4; return;
			case ShaderDataType::Int:      size = 4; return;
			case ShaderDataType::Int2:     size = 4 * 2; return;
			case ShaderDataType::Int3:     size = 4 * 3; return;
			case ShaderDataType::Int4:     size = 4 * 4; return;
			case ShaderDataType::Bool:     size = 1; return;
		}
	}
	int GetComponentCount() const 
	{
		return shaderType == ShaderDataType::Float || shaderType == ShaderDataType::Int || shaderType == ShaderDataType::Bool ? 1
			: shaderType == ShaderDataType::Float2 || shaderType == ShaderDataType::Int2 ? 2
			: shaderType == ShaderDataType::Float3 || shaderType == ShaderDataType::Int3 || shaderType == ShaderDataType::Mat3 ? 3
			: shaderType == ShaderDataType::Float4 || shaderType == ShaderDataType::Int4 || shaderType == ShaderDataType::Mat4 ? 4
			: 0;
	}

};

class BufferLayout 
{
public:
	BufferLayout() = default;
	BufferLayout(const std::initializer_list<BufferElement>& elements) :
		m_Stride(0), m_Elements(elements)
	{
		for (auto& element : elements)
			m_Stride += element.size;
		for (int i = 1; i < m_Elements.size(); i++)
			m_Elements[i].offset = m_Elements[i - 1].offset + m_Elements[i - 1].size;
	}
	BufferElement& operator[](int index) { return m_Elements[index]; }
	
	std::vector<BufferElement>::iterator begin() { return m_Elements.begin(); }
	std::vector<BufferElement>::iterator end() { return m_Elements.end(); }
	int GetStride() const { return m_Stride; }
private:
	std::vector<BufferElement> m_Elements;
	int m_Stride;
};

class VertexBuffer 
{
public:
	virtual ~VertexBuffer() = default;

	virtual void Bind() const = 0;
	virtual void Unbind() const = 0;

	virtual void SetLayout(const BufferLayout&) = 0;
	virtual BufferLayout GetLayout() const = 0;

	virtual void SetData(const void* data, int offset, int size) = 0;
	
	static VertexBuffer* Create(const std::vector<float>&);
	static VertexBuffer* Create(int size);
};
// Allocates and creates a VertexBuffer by duplicating the baseVertices 'count' times.
// Each duplication is appended to form a larger buffer of vertices.
VertexBuffer* AllocateVertices(const std::vector<float>& baseVertices, int count);

class IndexBuffer 
{
public:
	virtual ~IndexBuffer() = default;

	virtual void Bind() const = 0;
	virtual void Unbind() const = 0;

	virtual void SetData(const std::vector<unsigned>& indices, int offset) = 0;

	virtual int GetCount() const = 0;

	static IndexBuffer* Create(const std::vector<unsigned>&);
};
// Allocates and creates an IndexBuffer by duplicating and offsetting baseIndices for 'totalItems' items.
// Each base index is offset by the corresponding item, with 'pointsPerItem' determining the offset size.
IndexBuffer* AllocateIndices(const std::vector<unsigned>& baseIndices, int pointsPerItem, int totalItems);

class VertexArray
{
public:
	// If a vertex array is deleted, it should also delete its associated vertex and index buffers.
	virtual ~VertexArray() = default;

	virtual void SetIndexBuffer(IndexBuffer*) = 0;
	virtual void AddVertexBuffer(VertexBuffer*) = 0;

	virtual const IndexBuffer* GetIndexBuffer() const = 0;
	virtual VertexBuffer* GetVertexBuffer(int index) const = 0;
	virtual int GetVertexBufferCount() const = 0;

	virtual void Bind() const = 0;
	virtual void Unbind() const = 0;

	static VertexArray* Create();
};


class UniformBuffer 
{
public:
	virtual ~UniformBuffer() = default;

	virtual void Bind() const = 0;
	virtual void Unbind() const = 0;

	virtual void SetData(const void* data, int offset, int size) = 0;

	static UniformBuffer* Create(int size, int binding_point);
};