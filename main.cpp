#include <iostream>
#include <vector>
#include <locale>
#include <memory>

#include "ModuleManager.h"
#include "GpioModule.h"
#include "LogModule.h"

#include "ModuleEvent.h"

#include "Fps.h"

int main()
{
    setlocale(LC_ALL, "");

    ModuleManager manager;
    auto gpio = manager.add<GpioModule>();
    gpio->start();

    auto log = manager.add<LogModule>();
    log->start();

    bool still_running = true;

    Fps fps;

    while(still_running)
    {

        for(auto module : manager)
        {
            module->processEvents();
        }
        for(auto module : manager)
        {
            module->update();
        }

        for(int i(0); i < 500; ++i){
            std::unique_ptr<ModuleEvent> event = std::make_unique<ModuleEvent>(ModuleEvent::Nothing);
            event->add("acceleration", 10);
            manager.sendEventTo<GpioModule>(std::move(event));
        }


        if(fps.update())
            std::cout << "fps : " << fps.getFps() << "\n";
    }

    return 0;
}
