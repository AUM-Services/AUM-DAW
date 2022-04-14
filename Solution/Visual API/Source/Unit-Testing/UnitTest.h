#pragma once

#ifndef AUM_WORK_AUDIO_LOGS_H
#include "Log/Log.h"
using namespace AUMLog;
#define AUM_WORK_AUDIO_LOGS_H
#endif // !AUM_WORK_AUDIO_LOGS_H

namespace AUMUnitTest {

	#define _Assert_(x) if(!(x)) __debugbreak();
	#define _Test_(x, unitTest) if(!(x)) unitTest.SetError();

	class UnitTest {
	public:
		UnitTest();
		static bool Validate();
		static void ResetError();
		static bool ValidateAndReset();
		static void SetError();
		static bool HasError();
	private:
		static bool hasError;
	};

}