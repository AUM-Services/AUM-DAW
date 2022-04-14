//Written by Eric Dee.

#pragma once

#ifndef AUM_WORKSTATION_UNIT_TEST_H
#include <Unit-Test/AUM-Workstation-Unit-Test.h>
using namespace AUM_Workstation_Unit_Test;
#define AUM_WORKSTATION_UNIT_TEST_H
#endif // !AUM_WORKSTATION_UNIT_TEST_H

#ifndef AUM_ONO_API_ENUMERATE_GRAPHICS_H
#include "../../Enumerate/Graphics/AUM-Ono-API-Enumerate-Graphics-Error.h"
#include "../../Enumerate/Graphics/AUM-Ono-API-Enumerate-Graphics-Error-Type.h"
using namespace AUM_Ono_API_Enumerate_Graphics;
#define AUM_ONO_API_ENUMERATE_GRAPHICS_H
#endif

#ifndef AUM_ONO_API_GRAPHICS_DEPENDENCIES_H
// Include glew before glfw
#include "Vendors/glew//include/GL/glew.h"
#include "Vendors/glfw/include/GLFW/glfw3.h"
#pragma comment(lib, "glew32s.lib")
#pragma comment(lib, "glfw3.lib")
#define AUM_ONO_API_GRAPHICS_DEPENDENCIES_H
#endif

namespace AUM_Ono_API_Unit_Test {

	#define _AssertGL_(x) this->CleanGLErrors(); x; _Assert_(this->ListenForGLErrorEvent(__FILE__, #x, __LINE__));
	#define _TestGL_(x) this->CleanGLErrors(); x; _Test_(this->ListenForGLErrorEvent(__FILE__, #x, __LINE__), _Graphics.Catch);

	class AUMOnoAPIGraphicsUnitTest : public AUMWorkstationUnitTest
	{
	public:
		AUMOnoAPIGraphicsErrorEnum Errors;
		AUMOnoAPIGraphicsErrorTypeEnum ErrorTypes;
		//Construct:
		AUMOnoAPIGraphicsUnitTest();
	};


}