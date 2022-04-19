#pragma once

#ifndef AUM_WORKSTATION_LOG_H
#include "../Log/AUM-Workstation-Log.h"
using namespace AUM_Workstation_Log;
#define AUM_WORKSTATION_LOG_H
#endif // !AUM_WORKSTATION_LOG_H

namespace AUM_Workstation_Unit_Test {

	#define _Assert_(x) if(!(x)) __debugbreak();
	#define _Test_(x, unitTest) if(!(x)) unitTest.SetError();

	class AUMWorkstationBuildMacro AUMWorkstationUnitTest {

	private:
		//Field
		static bool hasError;

	public:
		//Method
		static bool Validate();
		static void ResetError();
		static bool ValidateAndReset();
		static void SetError();
		static bool HasError();

	public:
		//Ctr
		AUMWorkstationUnitTest();
	};

}