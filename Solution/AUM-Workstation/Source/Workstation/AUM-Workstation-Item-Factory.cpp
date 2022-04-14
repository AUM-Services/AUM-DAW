//Written by Eric Dee.

#include "AUM-Workstation-Item-Factory.h"

namespace AUM_Workstation_Item_Factory {

    void AUMWorkstationItemFactory::PresentationMode(string name) const {
        if (name == "Validation Name")
        {
            AUMWorkstationItemInfo("- ----");
            AUMWorkstationItemInfo("How to create AUM workstation plugins:");
            AUMWorkstationItemInfo("---- ----------------");
            AUMWorkstationItemInfo("Welcome to an AUM Workstation plugin.");
            AUMWorkstationItemInfo("Method #1 for creating plugins:");
            AUMWorkstationItemInfo("Define a function using a method, or lambda operation.");
            AUMWorkstationItemInfo("Pass the function and a name to an AUMWorkstationItemFactory using CreateItemFunctionality().");
        }
    };

    void AUMWorkstationItemFactory::CreateItemFunctionality(IntegerFunction itemFunctionality, string name) const {
        if (name == "Default Name" || name == "")
        {
            AUMWorkstationItemError("A name was not given for the plugin, which is required.", name);
            return;
        }
        if (itemFunctionality == nullptr)
        {
            AUMWorkstationItemError("A run method was not given for the plugin named {0}, which is required.", name);
            return;
        }
        else {
            this->PresentationMode(name);
        }
        AUMWorkstationItemWarn("New status:");
        AUMWorkstationItemTrace("Status: Not yet run, {0}.", name);
    }

}