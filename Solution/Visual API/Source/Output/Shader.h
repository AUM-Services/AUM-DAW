#pragma once

#ifndef AUM_WORK_AUDIO_IO_H
#include <stdio.h>
#include <iostream>
#include <map>
#include <memory.h>
#include <vector>
#include <fstream>
#include <sstream>
using namespace std;
#define AUM_WORK_AUDIO_IO_H
#endif // !AUM_WORK_AUDIO_IO_H

#ifndef AUM_GRAPHICS_DEPENDENCIES_H
// Include glew before glfw
#include "Vendors/glew//include/GL/glew.h"
#include "Vendors/glfw/include/GLFW/glfw3.h"
#pragma comment(lib, "glew32s.lib")
#pragma comment(lib, "glfw3.lib")
#define AUM_GRAPHICS_DEPENDENCIES_H
#endif

#ifndef AUM_GRAPHICS_ERRORS_H
#include "../Enumeration/GraphicsError.h"
#include "../Enumeration/GraphicsErrorType.h"
#define AUM_GRAPHICS_ERRORS_H
#endif // !AUM_GRAPHICS_ERRORS_H

namespace AUMGraphics {

	class Shader
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