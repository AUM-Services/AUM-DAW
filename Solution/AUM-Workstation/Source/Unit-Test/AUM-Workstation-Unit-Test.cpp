//Written by Eric Dee.

#include "AUM-Workstation-Unit-Test.h"

namespace AUM_Workstation_Unit_Test {

    bool AUMWorkstationUnitTest::hasError;

    AUMWorkstationUnitTest::AUMWorkstationUnitTest
        ()
    {
        AUMWorkstationUnitTest::hasError = false;
    }

    bool AUMWorkstationUnitTest::Validate
        ()
    {
        if (AUMWorkstationUnitTest::hasError)
        {
            AUMWorkstationUnitTest::hasError = true;
            return true;
        }
        else {
            return false;
        }
    }

    void AUMWorkstationUnitTest::ResetError
        ()
    {
        AUMWorkstationUnitTest::hasError = false;
    }

    bool AUMWorkstationUnitTest::ValidateAndReset
        ()
    {
        if (AUMWorkstationUnitTest::hasError)
        {
            AUMWorkstationUnitTest::hasError = true;
            AUMWorkstationUnitTest::ResetError();
            return true;
        }
        else {
            return false;
        }
    }

    void AUMWorkstationUnitTest::SetError
        ()
    {
        AUMWorkstationUnitTest::hasError = true;
    }

    bool AUMWorkstationUnitTest::HasError
        ()
    {
        return AUMWorkstationUnitTest::hasError;
    }

}