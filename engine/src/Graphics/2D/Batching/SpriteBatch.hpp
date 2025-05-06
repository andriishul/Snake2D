#pragma once
#include <array>
#include <Graphics/Buffer.hpp>
#include <Graphics/Batch.hpp>
#include <Entity/Sprite.hpp>

struct SpriteVertex {
	glm::vec2 a_Pos;
	glm::vec3 a_Color = { 0,0,0 };
	int a_TexID = 0;
};

class SpriteBatch : public Batch<Sprite>
{
private:
	static constexpr int MAX_SPRITES_NUM = 2000;
	static constexpr int VERTICES_PER_SPRITE = 4;
	static constexpr int INDICES_PER_SPRITE = 6;
	static constexpr int MAX_TEXTURE_SLOTS = 32; 
public:
	SpriteBatch();
	~SpriteBatch();
protected:
	Batch<Sprite>* CreateNextBatch() const override { return new SpriteBatch; }
	void AddObjectInternal(const Sprite&) override;
	void RenderInternal() override;
	void Reset() override;
	bool IsOverflow() const override;
private:
	// Array of vertices that defines the base shape of a quad (four vertices).
	// This represents the basic geometry for a single sprite.
	static const std::array<SpriteVertex, VERTICES_PER_SPRITE> s_BaseSpriteVertices;
	VertexArray* m_VertexArray;
	std::array<const Texture2D*, MAX_TEXTURE_SLOTS> m_Textures;
	std::array<SpriteVertex, MAX_SPRITES_NUM * VERTICES_PER_SPRITE> m_Vertices;
	int m_SpriteID = 0, m_TexID = 1;
};