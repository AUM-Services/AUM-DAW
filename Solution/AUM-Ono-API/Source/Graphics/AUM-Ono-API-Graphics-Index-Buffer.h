//Written by Eric Dee.

#pragma once

#ifndef AUM_ONO_API_GRAPHICS_DEPENDENCIES_H
// Include glew before glfw
#include "Vendors/glew//include/GL/glew.h"
#include "Vendors/glfw/include/GLFW/glfw3.h"
#pragma comment(lib, "glew32s.lib")
#pragma comment(lib, "glfw3.lib")
#define AUM_ONO_API_GRAPHICS_DEPENDENCIES_H
#endif

namespace AUM_Ono_API_Graphics {

	class AUMOnoAPIGraphicsIndexBuffer
	{
	public:
		AUMOnoAPIGraphicsIndexBuffer();
		AUMOnoAPIGraphicsIndexBuffer(unsigned int typeCount, const unsigned int* phaseIndicies);
		void Bind();
		void Unbind() const;
		unsigned int GetCount();
		const unsigned int* GetAddress() const;
	private:
		unsigned int indiciesBufferId;
		unsigned int typeCount;
	};

}