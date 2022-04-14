//Written by Eric Dee.

#pragma once

#ifndef AUM_WORKSTATION_IO_H
#include <IO/AUM-Workstation-IO.h>
#define AUM_WORKSTATION_IO_H
#endif // !AUM_WORKSTATION_IO_H

#ifndef AUM_ONO_API_UNIT_TEST_GRAPHICS_H
#include "../../Unit-Test/Graphics/AUM-Ono-API-Unit-Test-Graphics.h"
using namespace AUM_Ono_API_Unit_Test;
#define AUM_ONO_API_UNIT_TEST_GRAPHICS_H
#endif // !AUM_GRAPHICS_UNIT_TEST_H

namespace AUM_Ono_API_Context_Graphics {

	class AUMOnoAPIContextGraphics
	{
	public:
		static AUMOnoAPIGraphicsUnitTest Catch;
		static string GetError(int error);
		static string GetErrorType(int error);
		static void PrintInitilizationError(int error);
		static void PrintUpdateError(int error);
	};

	static AUMOnoAPIContextGraphics _Graphics = AUMOnoAPIContextGraphics();

}
