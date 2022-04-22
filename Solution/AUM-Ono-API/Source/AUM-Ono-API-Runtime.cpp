//Written by Eric Dee.

#include "AUM-Ono-Api-Runtime.h"

/********************************************************************************************************/
    ////                                                        ////
    //// Design the API here, and tell it which runtimes to use ////
    ////                                                        ////
    ////////////////////////////////////////////////////////////////

namespace Runtime {

    class AUMOnoAPIRuntime : public AUMWorkstationRuntime {

    public:
        void InitWorkstationItems() override;
    };

    void AUMOnoAPIRuntime::InitWorkstationItems()
    {
        this->WorkstationItems.emplace_back(make_unique<IAUMOnoAPIGraphics>("Main Window"));
        this->WorkstationItems.emplace_back(make_unique<IAUMGraphicsSynthesizer>("Graphics Synthesizer"));
    }

}

/********************************************************************************************************/
    ////                                                        ////
    //// Send them to the application's host with this function ////
    ////                                                        ////
    ////////////////////////////////////////////////////////////////

AUMWorkstationRuntime AUM_Workstation_Runtime::AUMWorkstationInitMain() {

    using namespace Runtime;
    
    AUMWorkstationRuntimeDebug("*Start of AUM Ono API items**");
    AUMOnoAPIRuntime aumOnoAPI = AUMOnoAPIRuntime();
    aumOnoAPI.InitWorkstationItems();

#ifdef AUM_WORKSTATION_RUN_CASE

    bool overrideToTest = false;
    int CASE = overrideToTest ? 0 : AUM_WORKSTATION_RUN_CASE;

    switch (CASE)
    {
        case 1:
            break;

        default:
            _RuntimeTests.ValidateRuntimeFunctionality(&aumOnoAPI.WorkstationItems);
            break;
    }

#endif

    AUMWorkstationRuntimeDebug("**End of AUM Ono API items****");
    return aumOnoAPI;
};