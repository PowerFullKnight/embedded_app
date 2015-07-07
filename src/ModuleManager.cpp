#include "ModuleManager.h"

ModuleManager::ModuleManager()
{
}

ModuleManager::~ModuleManager()
{
    const auto end = m_modules.end();
    for(auto beg = m_modules.begin(); beg != end; ++beg)
    {
        delete beg->second;
    }
}
