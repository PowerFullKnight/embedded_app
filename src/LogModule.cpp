#include "LogModule.h"

#include <iostream>

LogModule::LogModule(const ModuleManager& manager):
    AbstractModule(manager)
{

}

LogModule::~LogModule()
{
    //dtor
}


void LogModule::update()
{

}

void LogModule::init()
{

}

void LogModule::destroy()
{

}

void LogModule::processEvent(std::unique_ptr<ModuleEvent> event)
{
    if(event->getEventType() == ModuleEvent::Warning)
    {
        try
        {
            std::cout << event->get<Error>("error").getErrorString() << std::endl;
        }
        catch(Error &err)
        {
            std::cerr << err.getErrorString();
        }
    }
}
