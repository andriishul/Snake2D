#include "RendererAPI.h"
#include "platform/opengl/glRendererAPI.h"
RendererAPI* RendererAPI::Create()
{
	return new glRendererAPI;
}
