//Written by Eric Dee.

#pragma once

#ifndef AUM_UNIT_TEST_H
#include "UnitTest.h"
using namespace AUMUnitTest;
#define AUM_UNIT_TEST_H
#endif // !AUM_UNIT_TEST_H

#ifndef AUM_GRAPHICS_ENUMERATION_H
#include "../Graphics-Enumeration/GraphicsError.h"
#include "../Graphics-Enumeration/GraphicsErrorType.h"
using namespace AUMEnumerate;
#define AUM_GRAPHICS_ENUMERATION_H
#endif

#ifndef AUM_GRAPHICS_DEPENDENCIES_H
// Include glew before glfw
#include "Vendors/glew//include/GL/glew.h"
#include "Vendors/glfw/include/GLFW/glfw3.h"
#pragma comment(lib, "glew32s.lib")
#pragma comment(lib, "glfw3.lib")
#define AUM_GRAPHICS_DEPENDENCIES_H
#endif

namespace AUMUnitTest {

	#define _AssertGL_(x) this->CleanGLErrors(); x; _Assert_(this->ListenForGLErrorEvent(__FILE__, #x, __LINE__));
	#define _TestGL_(x) this->CleanGLErrors(); x; _Test_(this->ListenForGLErrorEvent(__FILE__, #x, __LINE__), _Graphics.Catch);

	class GraphicsUnitTest : public UnitTest
	{
	public:
		AUMGraphicsErrorEnum Errors;
		AUMGraphicsErrorTypeEnum ErrorTypes;
		//Construct:
		GraphicsUnitTest();
	};


}