//Written by Eric Dee.

#include "AUM-Workstation-Runtime-Unit-Test.h"

namespace AUM_Workstation_Unit_Test {

    void AUMWorkstationRuntimeUnitTest::ValidateRuntimeFunctionality
        (vector<unique_ptr<AUMWorkstationItem>>* hostItemBlock)
    {
        hostItemBlock->emplace_back(make_unique<AUMWorkstationItem>());
        auto validationDelegate = []() {
            AUMWorkstationItemTrace("The validation delegate has been called.");
            AUMWorkstationItemTrace("This is a runtime entry point that has been supplied for validation purposes.");
            return 0xf;
        };
        hostItemBlock->emplace_back(make_unique<AUMWorkstationItem>(validationDelegate, "Validation Name"));
        AUMWorkstationItemFactory itemFactory = AUMWorkstationItemFactory();
        auto validationPlugin = []()
        {
            AUMWorkstationItemTrace("The validation plugin has been called.");
            AUMWorkstationItemTrace("This is a runtime function that has been supplied for validation purposes.");
            return 0xffff;
        };
        itemFactory.CreateItemFunctionality(validationPlugin, "Validation Name");
    }

}