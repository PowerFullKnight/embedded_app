#ifndef ABSTRACTMODULE_H
#define ABSTRACTMODULE_H

#include <queue>

#include "ModuleEvent.h"

class ModuleManager;

class AbstractModule
{
public:
    AbstractModule(const ModuleManager& manager);
    virtual ~AbstractModule();

    virtual void update() = 0;

    virtual void start();
    virtual void stop();

    bool isEnabled() const;

    void pushEvent(std::unique_ptr<ModuleEvent> event);
    void processEvents();

protected:

    virtual void init();
    virtual void destroy();
    virtual void processEvent(std::unique_ptr<ModuleEvent> event) = 0;

    bool m_isEnabled;
    std::queue< std::unique_ptr<ModuleEvent> > m_eventsQueue;
    const ModuleManager& m_manager;
};

#endif // ABSTRACTMODULE_H
