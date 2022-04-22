//Written by Eric Dee.

#pragma once

#ifndef AUM_WORKSTATION_IO_H
#include <IO/AUM-Workstation-IO.h>
#define AUM_WORKSTATION_IO_H
#endif // !AUM_WORKSTATION_IO_H

#ifndef AUM_ONO_API_GRAPHICS_VERTEX_BUFFER_H
#include "../../Graphics/Main-Functionality/AUM-Ono-API-Graphics-Vertex-Buffer.h"
using namespace AUM_Ono_API_Graphics;
#define AUM_ONO_API_GRAPHICS_VERTEX_BUFFER_H
#endif // !AUM_ONO_API_GRAPHICS_VERTEX_BUFFER_H

#ifndef AUM_ONO_API_UNIT_TEST_GRAPHICS_H
#include "../../Unit-Test/Graphics/AUM-Ono-API-Unit-Test-Graphics.h"
using namespace AUM_Ono_API_Unit_Test;
#define AUM_ONO_API_UNIT_TEST_GRAPHICS_H
#endif // !AUM_ONO_API_UNIT_TEST_GRAPHICS_H

namespace AUM_Ono_API_Context_Graphics {

	class AUMOnoAPIContextGraphics {

	public:
		//Field
		static struct PlotAxisFFOZZ {
			float x;
			float y;
		} RawDataCacheFFOZZ[44100];
		static struct PlotAxisEETZZ {
			float x;
			float y;
		} RawDataCacheEETZZ[88200];
		static AUMOnoAPIGraphicsUnitTest Catch;
		static AUMOnoAPIGraphicsVertexBuffer VertexBuffer;
		static unsigned int CurrentShader;
		static GLFWwindow* CurrentOutput;
		static int Resolution;
		static float Frequency;
		static bool ResolutionShouldRebind;
		static bool FrequencyShouldRebind;

		//Method
		static string GetError(int error);
		static string GetErrorType(int error);
		static void PrintInitilizationError(int error);
		static void PrintUpdateError(int error);
		static void CleanGLErrors();
		static void GetGLErrors();
		static bool ListenForGLErrorEvent(const char* file, const char* function, int line);

		//Ctr
		AUMOnoAPIContextGraphics(const AUMOnoAPIContextGraphics&) = delete;
		AUMOnoAPIContextGraphics();
	};
	//Namespace scoped
	static AUMOnoAPIContextGraphics _Graphics;

}