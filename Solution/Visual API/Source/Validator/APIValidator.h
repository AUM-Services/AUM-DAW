//Written by Eric Dee.

#pragma once

#ifndef AUM_WORK_AUDIO_LOGS_H
#include "Log/Log.h"
using namespace AUMLog;
#define AUM_WORK_AUDIO_LOGS_H
#endif // !AUM_WORK_AUDIO_LOGS_H

#ifndef AUM_WORK_STATION_ITEM_H
#include "Workstation/WorkStationItem.h"
#include "Workstation/WorkstationItemFactory.h"
using namespace AUMWorkstation;
#define AUM_WORK_STATION_ITEM_H
#endif // !AUM_WORK_AUDIO_H

namespace AUMAPIValidation {

	#define _Assert_(x) if(!(x)) __debugbreak();

	class RuntimeValidator
	{
	public:
		int ValidationDelegate();
		void ValidateRuntimeFunctionality(vector<unique_ptr<AUMWorkstationItem>>* hostItemBlock);
	};

}

