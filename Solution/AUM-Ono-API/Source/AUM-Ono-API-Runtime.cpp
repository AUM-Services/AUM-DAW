//Written by Eric Dee.

#include "AUM-Ono-Api-Runtime.h"

///////////////////////////////////////////////////////////
////                                                   ////
//// Design the API, and tell it which runtimes to use ////
////                                                   ////
///////////////////////////////////////////////////////////

namespace Runtime {

    class AUMOnoAPIRuntime : public AUMWorkstationRuntime {
    public:
        void InitWorkstationItems() override;
    };

    void AUMOnoAPIRuntime::InitWorkstationItems()
    {
        this->WorkstationItems.emplace_back(make_unique<IAUMOnoAPIGraphics>("GLFW GUI"));
    }

}

/////////////////////////////////////////////
////                                     ////
//// Send them to the application's host ////
////                                     ////
/////////////////////////////////////////////

AUMWorkstationRuntime AUM_Workstation_Runtime::AUMWorkstationInitMain() {

    using namespace Runtime;
    #define VALIDATE_BUILD false
    
    AUMWorkstationRuntimeDebug("*Start of AUM Ono API items****");
    AUMOnoAPIRuntime aumOnoAPI = AUMOnoAPIRuntime();
    aumOnoAPI.InitWorkstationItems();
    if (VALIDATE_BUILD)
    {
        _RuntimeTests.ValidateRuntimeFunctionality(&aumOnoAPI.WorkstationItems);
    }
    AUMWorkstationRuntimeDebug("****End of AUM Ono API items****************");

    #undef VALIDATE_BUILD
    return aumOnoAPI;
};