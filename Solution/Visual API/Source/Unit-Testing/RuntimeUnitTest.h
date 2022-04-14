//Written by Eric Dee.

#pragma once

#ifndef AUM_UNIT_TEST_H
#include "UnitTest.h"
using namespace AUMUnitTest;
#define AUM_UNIT_TEST_H
#endif // !AUM_UNIT_TEST_H

#ifndef AUM_WORK_STATION_ITEM_H
#include "Workstation/WorkStationItem.h"
#include "Workstation/WorkstationItemFactory.h"
using namespace AUMWorkstation;
#define AUM_WORK_STATION_ITEM_H
#endif // !AUM_WORK_AUDIO_H

namespace AUMUnitTest {

	class RuntimeUnitTest : public UnitTest
	{
	public:
		static void ValidateRuntimeFunctionality(vector<unique_ptr<AUMWorkstationItem>>* hostItemBlock);
	};

	static RuntimeUnitTest _RuntimeTests = RuntimeUnitTest();

}