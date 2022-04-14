//Written by Eric Dee.

#pragma once

#ifndef AUM_WORKSTATION_LOG_H
#include <Log/AUM-Workstation-Log.h>
using namespace AUM_Workstation_Log;
#define AUM_WORKSTATION_LOG_H
#endif // !AUM_WORKSTATION_LOG_H

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
#endif

namespace AUM_Ono_API_Graphics {

	class AUMOnoAPIGraphicsShader
	{
	public:
		unsigned int CompileShader(unsigned int type, const string& source);
		unsigned int CreateShader();
		void SetVertexShader(string value);
		void SetFragmentShader(string value);
		void ReadShaderFile(const string& filePath);
	private:
		string vertexShader;
		string fragmentShader;
	};

}