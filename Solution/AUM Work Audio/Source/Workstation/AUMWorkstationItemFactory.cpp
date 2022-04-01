// Written by Eric Dee.

#include "AUMWorkstationItemFactory.h"

namespace AUMWorkstation {

    void AUMWorkstationItemFactory::PresentationMode(string name) const {
        if (name == "ExamplePlugin")
        {
            AUMPluginInfo("Welcome to AUM Work Audio Plugins.");
            AUMPluginInfo("Method #1 for creating plugins:");
            AUMPluginInfo("Create an item by defining a method/function.");
            AUMPluginInfo("then pass the method/function to AUMWorkstationItemFactory::CreateItemFunctionality()");
        }
    };

    void AUMWorkstationItemFactory::CreateItemFunctionality(IntegerFunction runDelegate, string name) const {
        if (name == "Default" || name == "")
        {
            AUMPluginError("A name was not given for the plugin, which is required.", name);
            return;
        }
        if (runDelegate == nullptr)
        {
            AUMPluginError("A run method was not given for the plugin named {0}, which is required.", name);
            return;
        }
        else {
            this->PresentationMode(name);
        }
        AUMPluginInfo("Status: {0}, {1}", runDelegate(), name);
        AUMPluginInfo("________________\n");
    }

}