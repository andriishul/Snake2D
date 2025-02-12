#include "glBuffer.hpp"
#include "glad/glad.h"

#include <stdexcept>
glVertexBuffer::~glVertexBuffer()
{
	if (glIsBuffer(m_ID))
		glDeleteBuffers(1, &m_ID);
}

glVertexBuffer::glVertexBuffer(int size)
{
	glGenBuffers(1, &m_ID);
	Bind();
	glBufferData(GL_ARRAY_BUFFER, size, nullptr, GL_DYNAMIC_DRAW);
	Unbind();
}

glVertexBuffer::glVertexBuffer(const std::vector<float>& vertices)
{
	int size = vertices.size() * sizeof(float);
	glGenBuffers(1, &m_ID);
	Bind();
	glBufferData(GL_ARRAY_BUFFER, size, vertices.data(), GL_STATIC_DRAW);
	Unbind();
}

void glVertexBuffer::Bind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, m_ID);
}

void glVertexBuffer::Unbind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type)
{
	switch (type)
	{
	case ShaderDataType::Float:    return GL_FLOAT;
	case ShaderDataType::Float2:   return GL_FLOAT;
	case ShaderDataType::Float3:   return GL_FLOAT;
	case ShaderDataType::Float4:   return GL_FLOAT;
	case ShaderDataType::Mat3:     return GL_FLOAT;
	case ShaderDataType::Mat4:     return GL_FLOAT;
	case ShaderDataType::Int:      return GL_INT;
	case ShaderDataType::Int2:     return GL_INT;
	case ShaderDataType::Int3:     return GL_INT;
	case ShaderDataType::Int4:     return GL_INT;
	case ShaderDataType::Bool:     return GL_BOOL;
	}
	throw std::runtime_error("Shader data type not found.");
	return 0;
}

void glVertexBuffer::SetData(const void* data, int offset, int size)
{
	Bind();
	glBufferSubData(GL_ARRAY_BUFFER, offset, size, data);
	Unbind();
}

glVertexArray::~glVertexArray()
{
	if (glIsVertexArray(m_ID))
		glDeleteVertexArrays(1, &m_ID);
}

glVertexArray::glVertexArray():m_VertexBufferIndex(0)
{
	glGenVertexArrays(1, &m_ID);
}
void glVertexArray::SetIndexBuffer(IndexBuffer* ibo)
{
	Bind();
	ibo->Bind();
	m_IndexBuffer = std::unique_ptr<IndexBuffer>(ibo);
	Unbind();
}

static bool IsIntType(ShaderDataType type) 
{
	return type == ShaderDataType::Int || type == ShaderDataType::Int2 || type == ShaderDataType::Int3 || type == ShaderDataType::Int4;
}
void glVertexArray::AddVertexBuffer(VertexBuffer* vbo)
{
	Bind();
	
	vbo->Bind();
	auto layout = vbo->GetLayout();
	int stride = layout.GetStride();
	for (auto& element : layout)
	{
		if (element.shaderType == ShaderDataType::Mat3 || element.shaderType == ShaderDataType::Mat4)
		{
				int count = element.GetComponentCount();
				for (int i = 0; i < count; i++)
				{
					glEnableVertexAttribArray(m_VertexBufferIndex);
					glVertexAttribPointer(m_VertexBufferIndex,
						count,
						ShaderDataTypeToOpenGLBaseType(element.shaderType),
						element.normalized,
						stride,
						(void*)(element.offset + sizeof(float) * count * i));
					glVertexAttribDivisor(m_VertexBufferIndex, 1);
				}
		}
		else {
			glEnableVertexAttribArray(m_VertexBufferIndex);

			if(IsIntType(element.shaderType) || element.shaderType ==  ShaderDataType::Bool)
				glVertexAttribIPointer(m_VertexBufferIndex,
					element.GetComponentCount(),
					ShaderDataTypeToOpenGLBaseType(element.shaderType),
					stride,
					(void*)element.offset);
			else
			glVertexAttribPointer(m_VertexBufferIndex,
				element.GetComponentCount(),
				ShaderDataTypeToOpenGLBaseType(element.shaderType),
				element.normalized,
				stride,
				(void*)element.offset);
		}
		m_VertexBufferIndex++;
	}
	vbo->Unbind();
	Unbind();
	m_VertexBuffers.push_back(std::unique_ptr<VertexBuffer>(vbo));
}

void glVertexArray::Bind() const
{
	glBindVertexArray(m_ID);
}

void glVertexArray::Unbind() const
{
	glBindVertexArray(0);
}

glIndexBuffer::~glIndexBuffer()
{
	if (glIsBuffer(m_ID))
		glDeleteBuffers(1, &m_ID);
}

glIndexBuffer::glIndexBuffer(int count) : m_iCount(count)
{
	glGenBuffers(1, &m_ID);
	Bind();
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned), nullptr, GL_DYNAMIC_DRAW);
	Unbind();
}

glIndexBuffer::glIndexBuffer(const std::vector<unsigned> &indices):m_iCount(indices.size())
{
	glGenBuffers(1, &m_ID);
	Bind();
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned), indices.data(), GL_STATIC_DRAW);
	Unbind();
}

void glIndexBuffer::Bind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ID);
}

void glIndexBuffer::Unbind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void glIndexBuffer::SetData(const std::vector<unsigned>& indices, int offset)
{
	Bind();
	glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, offset, indices.size() * sizeof(unsigned), indices.data());
	Unbind();
}

glUniformBuffer::glUniformBuffer(int size, int binding_point)
{
	glGenBuffers(1, &m_ID);
	Bind();
	glBufferData(GL_UNIFORM_BUFFER, size, 0, GL_DYNAMIC_DRAW);
	Unbind();

	glBindBufferBase(GL_UNIFORM_BUFFER, binding_point, m_ID);
}

glUniformBuffer::~glUniformBuffer()
{
	if (glIsBuffer(m_ID))
		glDeleteBuffers(1, &m_ID);
}

void glUniformBuffer::Bind() const
{
	glBindBuffer(GL_UNIFORM_BUFFER, m_ID);
}

void glUniformBuffer::Unbind() const
{
	glBindBuffer(GL_UNIFORM_BUFFER, 0);
}

void glUniformBuffer::SetData(const void* data, int offset, int size)
{
	Bind();
	glBufferSubData(GL_UNIFORM_BUFFER, offset, size, data);
	Unbind();
}
