#include "Functions.h"

#ifndef AUM_HOST_LOGS
#include "../Log/Log.h"
using namespace AUMLogs;
#define AUM_HOST_LOGS
#endif

namespace AUMFunctions {

    Functions::Functions() {
    }
    Functions::~Functions() {
    }
    void Functions::GetAddresses() {
    }
    void Functions::Run() {
        AUMStatusInfo("Welcome to AUM Work Audio.");
        while (true);
    }
}