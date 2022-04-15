//Written by Eric Dee.

#pragma once

#ifndef AUM_WORKSTATION_IO_H
#include <IO/AUM-Workstation-IO.h>
#define AUM_WORKSTATION_IO_H
#endif // !AUM_WORKSTATION_IO_H

#ifndef AUM_GRAPHICS_DEPENDENCIES_H
// Include glew before glfw
#include "Vendors/glew//include/GL/glew.h"
#include "Vendors/glfw/include/GLFW/glfw3.h"
#pragma comment(lib, "glew32s.lib")
#pragma comment(lib, "glfw3.lib")
#define AUM_GRAPHICS_DEPENDENCIES_H
#endif // !AUM_GRAPHICS_DEPENDENCIES_H

#ifndef AUM_ONO_API_GRAPHICS_CONTEXT_H
#include "../Contextual-Scope/Graphics/AUM-Ono-API-Context-Graphics.h"
using namespace AUM_Ono_API_Context_Graphics;
#define AUM_ONO_API_GRAPHICS_CONTEXT_H
#endif // !AUM_API_GRAPHICS_CONTEXT_H

namespace AUM_Ono_API_Graphics {

	struct AUMOnoAPIGraphicsVertexBufferElement
	{
		unsigned int Type_;
		unsigned int Count_;
		unsigned char GLNormalized_;

		static unsigned int GetSizeOfType
			(unsigned int type)
		{
			switch(type)
			{
				case GL_FLOAT: return 4;

				case GL_UNSIGNED_INT: return 4;

				case GL_UNSIGNED_BYTE: return 1;
			}

			_Assert_(false);

			return 0;
		}
	};

	class AUMOnoAPIGraphicsVertexBufferLayout
	{
	public:
		AUMOnoAPIGraphicsVertexBufferLayout() :stride(0) {};
	private:
		unsigned int stride;
		vector<AUMOnoAPIGraphicsVertexBufferElement> elements;
	public:
		template<typename T>
		void Push(unsigned int count)
		{
			static_assert(true);
		}

		template<>
		void Push<float>(unsigned int count)
		{
			// count, type, normalized?
			this->elements.push_back(
				{
					GL_FLOAT,
					count,
					GL_FALSE
				}
			);
			this->stride += AUMOnoAPIGraphicsVertexBufferElement::GetSizeOfType(GL_FLOAT) *count;
		}

		template<>
		void Push<unsigned int>(unsigned int count)
		{
			// count, type, normalized?
			this->elements.push_back(
				{
					GL_UNSIGNED_INT,
					count,
					GL_FALSE
				}
			);
			this->stride += AUMOnoAPIGraphicsVertexBufferElement::GetSizeOfType(GL_UNSIGNED_INT) *count;
		}

		template<>
		void Push<unsigned char>(unsigned int count)
		{
			// count, type, normalized?
			this->elements.push_back(
				{
					GL_UNSIGNED_BYTE,
					count,
					GL_TRUE
				}
			);
			this->stride += AUMOnoAPIGraphicsVertexBufferElement::GetSizeOfType(GL_UNSIGNED_BYTE) *count;
		}

		vector<AUMOnoAPIGraphicsVertexBufferElement> GetElements
			() const
		{
			return elements;
		}

		unsigned int GetStride
			() const
		{
			return stride;
		}

	};

}