#include "GpioModule.h"

#include "ModuleManager.h"

#include <iostream>

GpioModule::GpioModule(const ModuleManager& manager):
    AbstractModule(manager)
{
}

GpioModule::~GpioModule()
{
    //dtor
}

void GpioModule::update()
{

}

void GpioModule::init()
{

}

void GpioModule::destroy()
{

}

void GpioModule::processEvent(std::unique_ptr<ModuleEvent> event)
{
    if(event->getEventType() == ModuleEvent::Nothing)
    {
        try
        {
            volatile int a = event->get<int>("acceleration");
            //std::cout << "Received event acceleration ( val = " << a << " )\n";
        }
        catch(Error &err)
        {
            std::unique_ptr<ModuleEvent> ev = std::make_unique<ModuleEvent>(ModuleEvent::Warning);

            Error e = err;
            ev->add("error", err);
            m_manager.sendEventTo<LogModule>(std::move(ev));
        }

    }
}
