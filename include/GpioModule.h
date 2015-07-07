#ifndef GPIOMODULE_H
#define GPIOMODULE_H

#include "AbstractModule.h"

class GpioModule : public AbstractModule
{
public:
    GpioModule(const ModuleManager& manager);
    ~GpioModule() override;

    void update() override;

protected:
    void init() override;
    void destroy() override;
    void processEvent(std::unique_ptr<ModuleEvent> event);

};

#endif // GPIOMODULE_H
