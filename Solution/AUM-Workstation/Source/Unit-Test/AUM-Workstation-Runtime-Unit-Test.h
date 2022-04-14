//Written by Eric Dee.

#pragma once

#ifndef AUM_WORKSTATION_UNIT_TEST_H
#include "AUM-Workstation-Unit-Test.h"
using namespace AUM_Workstation_Unit_Test;
#define AUM_WORKSTATION_UNIT_TEST_H
#endif // !AUM_WORK_STATION_UNIT_TEST_H

#ifndef AUM_WORKSTATION_ITEM_H
#include "Workstation/AUM-Workstation-Item.h"
using namespace AUM_Workstation_Item;
#define AUM_WORKSTATION_ITEM_H
#endif // !AUM_WORKSTATION_ITEM_H

#ifndef AUM_WORKSTATION_ITEM_FACTORY_H
#include "Workstation/AUM-Workstation-Item-Factory.h"
using namespace AUM_Workstation_Item_Factory;
#define AUM_WORKSTATION_ITEM_FACTORY_H
#endif // !AUM_WORKSTATION_ITEM_FACTORY_H

namespace AUM_Workstation_Unit_Test {

	class AUMWorkstationBuildMacro AUMWorkstationRuntimeUnitTest : public AUMWorkstationUnitTest
	{
	public:
		static void ValidateRuntimeFunctionality(vector<unique_ptr<AUMWorkstationItem>>* hostItemBlock);
	};

	static AUMWorkstationRuntimeUnitTest _RuntimeTests = AUMWorkstationRuntimeUnitTest();

}