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

	class AUMOnoAPIGraphicsShaderCompiler {

	private:
		//Fields
		string filePath;
		string vertexShader;
		string fragmentShader;
		int uniformLocation;

	public:
		//Methods
		unsigned int CompileVertexAndFragmentShaders(unsigned int type, const string& source) const;
		unsigned int BuildVertexAndFragmentShaders(const string& filePath);
		void SetTheVertexShader(string value);
		void SetTheFragmentShader(string value);
		void ReadAndSetTheShaderFromShaderFile(const string& filePath);
		void SetUniformLocation(unsigned int shader, const char* name);
		int GetUniformLocation();
		void SetUniform4f(float v0, float v1, float v2, float v3);
		void UseShader(unsigned int shader);
		void UnbindThisUniformLocation();

		//Ctr
		AUMOnoAPIGraphicsShaderCompiler();
	};

}