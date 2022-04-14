//Written by Eric Dee.

#include "RuntimeUnitTest.h"

namespace AUMUnitTest {

    void RuntimeUnitTest::ValidateRuntimeFunctionality
        (vector<unique_ptr<AUMWorkstationItem>>* hostItemBlock)
    {
        hostItemBlock->emplace_back(make_unique<AUMWorkstationItem>());
        auto validationDelegate = []() {
            AUMPluginTrace("The validation delegate has been called.");
            AUMPluginTrace("This is a runtime entry point that has been supplied for validation purposes.");
            return 0xf;
        };
        hostItemBlock->emplace_back(make_unique<AUMWorkstationItem>(validationDelegate, "Validation Name"));
        AUMWorkstationItemFactory itemFactory = AUMWorkstationItemFactory();
        auto validationPlugin = []()
        {
            AUMPluginTrace("The validation plugin has been called.");
            AUMPluginTrace("This is a runtime function that has been supplied for validation purposes.");
            return 0xffff;
        };
        itemFactory.CreateItemFunctionality(validationPlugin, "Validation Name");
    }

}