#pragma once
#include <array>
#include <Graphics/Texture.hpp>
#include <Graphics/Buffer.hpp>
#include <Graphics/Batch.hpp>
#include <Entity/Text.hpp>


struct TextVertex {
	glm::vec2 a_Pos, a_TexCoords;
	glm::vec3 a_Color = { 0,0,0 };
};

class TextBatch : public Batch<Text>
{
private:
	static constexpr int MAX_ÑHARACTERS_NUM = 2000;
	static constexpr int VERTICES_PER_CHARACTER = 4;
	static constexpr int INDICES_PER_CHARACTER = 6;
public:
	~TextBatch();
	TextBatch();
protected:
	Batch<Text>* CreateNextBatch() const override { return new TextBatch; }
	void AddObjectInternal(const Text&) override;
	void RenderInternal() override;
	void Reset() override;
	bool IsOverflow() const override;
private:
	const class Font* m_DefaultFont;
	VertexArray* m_VertexArray;
	std::array<TextVertex, MAX_ÑHARACTERS_NUM*VERTICES_PER_CHARACTER> m_Vertices;
	int m_CharacterID = 0;
};