//Written by Eric Dee.

#include "WorkstationItemFactory.h"

namespace AUMWorkstation {

    void AUMWorkstationItemFactory::PresentationMode(string name) const {
        if (name == "Validation Name")
        {
            AUMPluginInfo("- ----");
            AUMPluginInfo("How to create AUM workstation plugins:");
            AUMPluginInfo("---- ----------------");
            AUMPluginInfo("Welcome to an AUM Workstation plugin.");
            AUMPluginInfo("Method #1 for creating plugins:");
            AUMPluginInfo("Define a function using a method, or lambda operation.");
            AUMPluginInfo("Pass the function and a name to an AUMWorkstationItemFactory using CreateItemFunctionality().");
        }
    };

    void AUMWorkstationItemFactory::CreateItemFunctionality(IntegerFunction itemFunctionality, string name) const {
        if (name == "Default Name" || name == "")
        {
            AUMPluginError("A name was not given for the plugin, which is required.", name);
            return;
        }
        if (itemFunctionality == nullptr)
        {
            AUMPluginError("A run method was not given for the plugin named {0}, which is required.", name);
            return;
        }
        else {
            this->PresentationMode(name);
        }
        AUMPluginWarn("New status:");
        AUMPluginTrace("Status: Not yet run, {0}.", name);
    }

}