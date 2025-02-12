#include "Renderer2D.hpp"
#include <Graphics/RenderCommand.hpp>

#include "Core/ResourceLoader.hpp"
#include "Batching/SpriteBatch.hpp"
#include "Batching/TextBatch.hpp"

struct CameraInfo 
{
	glm::mat4 u_ProjectionView;
} cameraInfo;

Shader *spriteShader = 0, *textShader = 0;

std::unique_ptr<UniformBuffer> cameraBuffer;
std::unique_ptr<SpriteBatch> spriteBatch;
std::unique_ptr<TextBatch> textBatch;

static void InitSpriteRendering() 
{
	spriteBatch = std::make_unique<SpriteBatch>();

	spriteShader = ResourceLoader::LoadShader("quad");
	
	spriteShader->Use();
	/* Set the value of each uniform to the corresponding texture unit index,
	This allows the shader to know which texture unit to use for each texture sampler */
	for (int i = 0; i < 32; i++)
		spriteShader->SetInt(("u_Textures[" + std::to_string(i) + "]").c_str(), i);
}
static void InitTextRendering()
{
	textBatch = std::make_unique<TextBatch>();

	textShader = ResourceLoader::LoadShader("text");
}

void Renderer2D::Init()
{
	cameraBuffer = std::unique_ptr<UniformBuffer>(UniformBuffer::Create(sizeof(CameraInfo), 0));
	InitSpriteRendering();
	InitTextRendering();
}

void Renderer2D::Begin(OrthoCamera& camera)
{
	if (cameraInfo.u_ProjectionView != camera.GetViewProjectionMatrix())
	{
		cameraInfo.u_ProjectionView = camera.GetViewProjectionMatrix();
		cameraBuffer->SetData(&cameraInfo, 0, sizeof(CameraInfo));
	}
}

void Renderer2D::DrawText(const Text& text) 
{
	textBatch->AddObject(text);
}
void Renderer2D::DrawSprite(const Sprite& sprite)
{
	spriteBatch->AddObject(sprite);
}

void Renderer2D::End()
{
	spriteShader->Use();
	spriteBatch->Render();

	textShader->Use();
	textBatch->Render();
}
