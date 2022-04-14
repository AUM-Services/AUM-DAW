//Written by Eric Dee.

#pragma once

#ifndef AUM_WORK_AUDIO_IO_H
#include <stdio.h>
#include <iostream>
#include <map>
#include <memory.h>
#include <vector>
using namespace std;
#define AUM_WORK_AUDIO_IO_H
#endif // !AUM_WORK_AUDIO_IO_H

#ifndef AUM_GRAPHICS_UNIT_TEST_H
#include "../Unit-Testing/GraphicsUnitTest.h"
using namespace AUMUnitTest;
#define AUM_GRAPHICS_UNIT_TEST_H
#endif // !AUM_GRAPHICS_UNIT_TEST_H

namespace AUMContext {

	class GraphicsContext
	{
	public:
		static GraphicsUnitTest Catch;
		static string GetError(int error);
		static string GetErrorType(int error);
		static void PrintInitilizationError(int error);
		static void PrintUpdateError(int error);
	};

	static GraphicsContext _Graphics;

}
