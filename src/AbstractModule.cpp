#include "AbstractModule.h"

#include "ModuleManager.h"

AbstractModule::AbstractModule(const ModuleManager& manager):
    m_isEnabled(false), m_manager(manager)
{
}

AbstractModule::~AbstractModule()
{
    destroy();
}

void AbstractModule::start()
{
    m_isEnabled = true;
    try
    {
        init();
    }
    catch(...)
    {
        m_isEnabled = false;
        throw;
    }
}

void AbstractModule::stop()
{
    m_isEnabled = false;
    try
    {
        destroy();
    }
    catch(...)
    {
        m_isEnabled = true;
        throw;
    }
}

bool AbstractModule::isEnabled() const
{
    return m_isEnabled;
}

void AbstractModule::init()
{

}

void AbstractModule::destroy()
{

}

void AbstractModule::pushEvent(std::unique_ptr<ModuleEvent> event)
{
    m_eventsQueue.push(std::move(event));
}

void AbstractModule::processEvents()
{
    while (! m_eventsQueue.empty())
    {
        std::unique_ptr<ModuleEvent> event = std::move(m_eventsQueue.front());
        m_eventsQueue.pop();

        processEvent(std::move(event));
    }
}
