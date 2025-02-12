#include "SpriteBatch.hpp"
#include <Graphics/RenderCommand.hpp>
#include <glm/ext/matrix_transform.hpp>

const std::array<SpriteVertex, SpriteBatch::VERTICES_PER_SPRITE> SpriteBatch::s_BaseSpriteVertices = {
		SpriteVertex{ {-0.5f, -0.5f} },
		SpriteVertex{ {0.5f, -0.5f} },
		SpriteVertex{ {0.5f, 0.5f} },
		SpriteVertex{ {-0.5f, 0.5f} }
};



SpriteBatch::SpriteBatch() : m_VertexArray(VertexArray::Create())
{
	m_Textures.assign(0);


	VertexBuffer* dynamicVBO = VertexBuffer::Create(m_Vertices.size() * sizeof(SpriteVertex));
	dynamicVBO->SetLayout({
						BufferElement("a_Pos", ShaderDataType::Float2),
						BufferElement("a_Color", ShaderDataType::Float3),
						BufferElement("a_TexID", ShaderDataType::Int)
			});

	const std::vector<float> a_TexCoords =
	{
		0.0f, 1.0f , 
		1.0f, 1.0f, 
		1.0f, 0.0f, 
		0.0f, 0.0f, 
	};

	VertexBuffer* staticVBO = AllocateVertices(a_TexCoords, MAX_SPRITES_NUM);
	staticVBO->SetLayout({
			     BufferElement("a_TexCoords", ShaderDataType::Float2),
		});

	m_VertexArray->AddVertexBuffer(dynamicVBO);
	m_VertexArray->AddVertexBuffer(staticVBO);

	m_VertexArray->SetIndexBuffer(AllocateIndices({ 0, 1, 2, 2, 3, 0 }, VERTICES_PER_SPRITE, MAX_SPRITES_NUM));
}

SpriteBatch::~SpriteBatch()
{
	delete m_VertexArray;
}

void SpriteBatch::AddObjectInternal(const Sprite& sprite)
{
	const Texture2D* texture = sprite.GetTexture();
	if (texture)
		m_Textures[m_TexID] = texture;
	int spriteOffset = m_SpriteID * VERTICES_PER_SPRITE;
	
	glm::vec2 position = sprite.GetPosition();
	glm::vec2 scale = sprite.GetScale();
	glm::vec3 color = sprite.GetColor();
	float rotation = glm::radians(sprite.GetRotation());
	
	float cosTheta = cos(rotation);
	float sinTheta = sin(rotation);
	
	float halfScaleX = 0.5f * scale.x;
	float halfScaleY = 0.5f * scale.y;

	for (int i = 0; i < VERTICES_PER_SPRITE; i++) 
	{
		glm::vec2 basePos = s_BaseSpriteVertices[i].a_Pos;
		
		float scaledX = basePos.x * scale.x;
		float scaledY = basePos.y * scale.y;
		float rotatedX = cosTheta * scaledX - sinTheta * scaledY;
		float rotatedY = sinTheta * scaledX + cosTheta * scaledY;
		// Apply translation to the rotated position and adjust for the sprite's center
		float finalX = rotatedX + position.x + halfScaleX * (cosTheta - 1.0f) - halfScaleY * sinTheta;
		float finalY = rotatedY + position.y + halfScaleY * (cosTheta - 1.0f) + halfScaleX * sinTheta;
		
		m_Vertices[spriteOffset + i].a_Pos = glm::vec2(finalX, finalY);
		m_Vertices[spriteOffset + i].a_Color = color;
		m_Vertices[spriteOffset + i].a_TexID = texture ? m_TexID : 0;
	}

	if (texture) m_TexID++;

	m_SpriteID++;
}

void SpriteBatch::RenderInternal()
{
	if (m_SpriteID > 0) 
	{
		for (int i = 1; i < MAX_TEXTURE_SLOTS; ++i) 
			if (m_Textures[i]) 
				m_Textures[i]->Bind(i);

		m_VertexArray->GetVertexBuffer(0)->SetData(m_Vertices.data(), 0, m_SpriteID * VERTICES_PER_SPRITE * sizeof(SpriteVertex));
		RenderCommand::DrawElements(*m_VertexArray, m_SpriteID * INDICES_PER_SPRITE);
	}
}

void SpriteBatch::Reset()
{
	m_SpriteID = 0, m_TexID = 1; 
}

bool SpriteBatch::IsOverflow() const
{
	return m_TexID >= MAX_TEXTURE_SLOTS || m_SpriteID >= MAX_SPRITES_NUM;
}
