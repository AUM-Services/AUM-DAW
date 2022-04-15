//Written by Eric Dee.

#pragma once

#ifndef AUM_ONO_API_GRAPHICS_VERTEX_BUFFER_H
#include "AUM-Ono-API-Graphics-Vertex-Buffer.h"
using namespace AUM_Ono_API_Graphics;
#define AUM_ONO_API_GRAPHICS_VERTEX_BUFFER_H
#endif // !AUM_ONO_API_GRAPHICS_VERTEX_BUFFER_H

#ifndef AUM_ONO_API_GRAPHICS_VERTEX_BUFFER_LAYOUT_H
#include "AUM-Ono-API-Graphics-Vertex-Buffer-Layout.h"
using namespace AUM_Ono_API_Graphics;
#define AUM_ONO_API_GRAPHICS_VERTEX_BUFFER_LAYOUT_H
#endif // !AUM_ONO_API_GRAPHICS_VERTEX_BUFFER_LAYOUT_H

#ifndef AUM_ONO_API_GRAPHICS_CONTEXT_H
#include "../Contextual-Scope/Graphics/AUM-Ono-API-Context-Graphics.h"
using namespace AUM_Ono_API_Context_Graphics;
#define AUM_ONO_API_GRAPHICS_CONTEXT_H
#endif // !AUM_ONO_API_GRAPHICS_CONTEXT_H

namespace AUM_Ono_API_Graphics {

	class AUMOnoAPIGraphicsVertexArray
	{
	public:
		const char* Name;
		AUMOnoAPIGraphicsVertexArray();
		~AUMOnoAPIGraphicsVertexArray();
	private:
		unsigned int rendererId;
	public:
		void AddToBuffer
			(
			const AUMOnoAPIGraphicsVertexBuffer& vertexBuffer,
			const AUMOnoAPIGraphicsVertexBufferLayout& vertexBufferlayout
			);
		void Bind() const;
		void Unbind() const;
	};

}