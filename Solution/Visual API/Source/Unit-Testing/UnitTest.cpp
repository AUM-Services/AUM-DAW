//Written by Eric Dee.

#include "UnitTest.h"

namespace AUMUnitTest {

    bool UnitTest::hasError;

    UnitTest::UnitTest
        ()
    {
        UnitTest::hasError = false;
    }

    bool UnitTest::Validate
        ()
    {
        if (UnitTest::hasError)
        {
            UnitTest::hasError = true;
            return true;
        }
        else {
            return false;
        }
    }

    void UnitTest::ResetError
        ()
    {
        UnitTest::hasError = false;
    }

    bool UnitTest::ValidateAndReset
        ()
    {
        if (UnitTest::hasError)
        {
            UnitTest::hasError = true;
            UnitTest::ResetError();
            return true;
        }
        else {
            return false;
        }
    }

    void UnitTest::SetError
        ()
    {
        UnitTest::hasError = true;
    }

    bool UnitTest::HasError
        ()
    {
        return UnitTest::hasError;
    }

}