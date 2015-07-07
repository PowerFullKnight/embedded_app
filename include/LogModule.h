#ifndef LOGMODULE_H
#define LOGMODULE_H

#include "AbstractModule.h"

class LogModule : public AbstractModule
{
public:
    LogModule(const ModuleManager& manager);
    ~LogModule() override;

    void update() override;

protected:
    void init() override;
    void destroy() override;
    void processEvent(std::unique_ptr<ModuleEvent> event);

};

#endif // LOGMODULE_H
