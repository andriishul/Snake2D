#include "TextBatch.hpp"
#include <Graphics/RenderCommand.hpp>
#include <Core/ResourceLoader.hpp>

TextBatch::~TextBatch()
{
    delete m_VertexArray;
}

TextBatch::TextBatch()
    : m_DefaultFont(ResourceLoader::LoadFont("ubuntu.regular.ttf")),
    m_VertexArray(VertexArray::Create()),
    m_CharacterID(0)
{
    VertexBuffer* vertexBuffer = VertexBuffer::Create(m_Vertices.size() * sizeof(TextVertex));
    vertexBuffer->SetLayout({
        BufferElement("a_Pos", ShaderDataType::Float2),
        BufferElement("a_TexCoords", ShaderDataType::Float2),
        BufferElement("a_Color", ShaderDataType::Float3)
        });
    m_VertexArray->AddVertexBuffer(vertexBuffer);
    m_VertexArray->SetIndexBuffer(AllocateIndices({ 0,3,2, 2,1,0 }, VERTICES_PER_CHARACTER, MAX_ÑHARACTERS_NUM));
}

void TextBatch::AddObjectInternal(const Text& text)
{
    const std::string textStr = static_cast<std::string>(text);
    // Normalize scale based on the font's pixel size
    glm::vec2 scale = text.GetScale() / (float)m_DefaultFont->GetPixelSize();
    glm::vec2 position = text.GetPosition();
    glm::vec3 color = text.GetColor();
    float rotation = text.GetRotation();
    Alignment alignment = text.GetAlignment();

    float cosTheta = glm::cos(glm::radians(rotation));
    float sinTheta = glm::sin(glm::radians(rotation));

    // Current text characters for further processing
    std::vector<Character> characters;
    characters.reserve(textStr.length());
    // Pivot point for rotation
    glm::vec2 pivot = position;
    // Total width of text
    float textWidth = 0.0f;
    for (unsigned char c : textStr)
    {
        const Character& ch = (*m_DefaultFont)[c];
        textWidth += (ch.Advance >> 6) * scale.x; 
        characters.emplace_back(ch);
    }

    switch (alignment)
    {
    case Alignment::Center:
        position.x -= textWidth / 2.0f;
        break;
    case Alignment::Right:
        position.x -= textWidth;
        break;
    default:
        break;
    }

    for (Character& ch : characters)
    {
        float xpos = position.x + ch.Bearing.x * scale.x;
        float ypos = position.y - (ch.Size.y - ch.Bearing.y) * scale.y;

        float w = static_cast<float>(ch.Size.x) * scale.x;
        float h = static_cast<float>(ch.Size.y) * scale.y;

        glm::vec2 vertices[VERTICES_PER_CHARACTER] = {
            {xpos, ypos + h},        // Bottom-left
            {xpos, ypos},            // Top-left
            {xpos + w, ypos},        // Top-right
            {xpos + w, ypos + h}     // Bottom-right
        };

        // Apply rotation around the pivot point
        for (int i = 0; i < VERTICES_PER_CHARACTER; ++i)
        {
            // Translate to pivot
            glm::vec2 translated = vertices[i] - pivot;

            // Apply rotation matrix
            float rotatedX = translated.x * cosTheta + translated.y * sinTheta;
            float rotatedY = -translated.x * sinTheta + translated.y * cosTheta;

            // Translate back to the original position
            vertices[i] = glm::vec2(rotatedX, rotatedY) + pivot;
        }

        int characterOffset = m_CharacterID * VERTICES_PER_CHARACTER;

        m_Vertices[characterOffset] = TextVertex{ vertices[0], { ch.TexCoords[0].x, ch.TexCoords[1].y }, color }; // Bottom-left
        m_Vertices[characterOffset + 1] = TextVertex{ vertices[1], ch.TexCoords[0], color }; // Top-left
        m_Vertices[characterOffset + 2] = TextVertex{ vertices[2], { ch.TexCoords[1].x, ch.TexCoords[0].y }, color }; // Top-right
        m_Vertices[characterOffset + 3] = TextVertex{ vertices[3], ch.TexCoords[1], color }; // Bottom-right

        // Move to the next character position
        position.x += (ch.Advance >> 6) * scale.x;
        m_CharacterID++; 
    }
}

void TextBatch::RenderInternal()
{
    if (m_CharacterID > 0)
    {
        m_DefaultFont->GetGlyphAtlas()->Bind();

        m_VertexArray->GetVertexBuffer(0)->SetData(m_Vertices.data(), 0, m_CharacterID * VERTICES_PER_CHARACTER * sizeof(TextVertex));
        RenderCommand::DrawElements(*m_VertexArray, m_CharacterID * INDICES_PER_CHARACTER);
    }
}

void TextBatch::Reset()
{
    m_CharacterID = 0;
}

bool TextBatch::IsOverflow() const
{
    return m_CharacterID + 6 >= VERTICES_PER_CHARACTER * MAX_ÑHARACTERS_NUM;
}
