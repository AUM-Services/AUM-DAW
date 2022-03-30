#ifndef AUM_WORK_AUDIO
#include <AUMWorkAudio.h>
using namespace AUMFunctions;
#define AUM_WORK_AUDIO
#endif // !AUM_WORK_AUDIO

namespace VisualAPI {
    
    class GUI : public Functions {
    public:
        GUI() {}
        ~GUI() {}
    };
}

/// <summary>
/// Name the functionality in a global scope to the project.
/// This gets run as an assignemnt for int main in AUM Work Audio > Host.h
/// </summary>
/// <returns></returns>
Functions* AUMFunctions::CreateFunctionality() {
    std::string plugin = "Oscillator";
    AUMPluginInfo("Welcome to AUM API. Attempting to connect {0}", plugin);
    return new VisualAPI::GUI();
}