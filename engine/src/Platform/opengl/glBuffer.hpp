#pragma once
#include <Graphics/Buffer.hpp>

#include <memory>

class glVertexBuffer : public VertexBuffer
{
public:
	~glVertexBuffer();
	glVertexBuffer() = delete;
	glVertexBuffer(int size);
	glVertexBuffer(const std::vector<float>&);

	virtual void Bind() const override;
	virtual void Unbind() const override;

	virtual void SetLayout(const BufferLayout& layout) override { m_Layout = layout; }
	virtual BufferLayout GetLayout() const override { return m_Layout; }

	virtual void SetData(const void* data, int offset ,int size) override;
private:
	BufferLayout m_Layout;
	unsigned m_ID;
};

class glIndexBuffer : public IndexBuffer
{
public:
	~glIndexBuffer();
	glIndexBuffer(int count);
	glIndexBuffer(const std::vector<unsigned>&);

	virtual void Bind() const override;
	virtual void Unbind() const override;

	virtual void SetData(const std::vector<unsigned>& indices, int offset) override;

	virtual int GetCount() const override { return m_iCount; }
private:	
	unsigned m_ID, /*indices count*/ m_iCount;
};


class glVertexArray : public VertexArray
{
public:
	~glVertexArray();
	glVertexArray();

	virtual void SetIndexBuffer(IndexBuffer*) override;
	virtual void AddVertexBuffer(VertexBuffer*) override;

	virtual const IndexBuffer* GetIndexBuffer() const override { return m_IndexBuffer.get(); }
	virtual VertexBuffer* GetVertexBuffer(int index) const override { return m_VertexBuffers.size() > index ? m_VertexBuffers[index].get() : 0; }
	virtual int GetVertexBufferCount() const override { return m_VertexBuffers.size(); }

	virtual void Bind() const override;
	virtual void Unbind() const override;
private:
	std::unique_ptr<IndexBuffer> m_IndexBuffer;
	std::vector<std::unique_ptr<VertexBuffer>> m_VertexBuffers;
	int m_VertexBufferIndex;
	unsigned m_ID;
};

class glUniformBuffer : public UniformBuffer
{
public:
	glUniformBuffer(int size, int binding_point);
	~glUniformBuffer();

	virtual void Bind() const override;
	virtual void Unbind() const override;

	virtual void SetData(const void* data, int offset, int size) override;
private:
	unsigned m_ID;
};