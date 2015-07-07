#ifndef MODULEMANAGER_H
#define MODULEMANAGER_H

#include <unordered_map>
#include <type_traits>
#include <iterator>     // std::iterator, std::input_iterator_tag

#include "typename.h"

#include "AbstractModule.h"
#include "GpioModule.h"
#include "LogModule.h"

#include "ModuleError.h"
#include "ModuleEvent.h"


class ModuleIterator : public std::iterator<std::input_iterator_tag, AbstractModule*>
{
    std::unordered_map<std::size_t, AbstractModule* >::iterator m_pos;
public:
    ModuleIterator(std::unordered_map<std::size_t, AbstractModule* >::iterator beg) :m_pos(beg) {}
    ModuleIterator(const ModuleIterator& mit) : m_pos(mit.m_pos) {}
    ModuleIterator& operator++()
    {
        ++m_pos;
        return *this;
    }
    ModuleIterator operator++(int)
    {
        ModuleIterator tmp(*this);
        operator++();
        return tmp;
    }
    bool operator==(const ModuleIterator& rhs)
    {
        return m_pos==rhs.m_pos;
    }
    bool operator!=(const ModuleIterator& rhs)
    {
        return m_pos!=rhs.m_pos;
    }
    AbstractModule* operator*()
    {
        return m_pos->second;
    }
};


class ModuleManager
{
public:
    ModuleManager();
    ~ModuleManager();

    template <typename Module>
    AbstractModule* add()
    {
        static_assert(!std::is_same<AbstractModule, Module>::value, "Impossible d'instancier un objet du type AbstractModule.");

        if(!std::is_base_of<AbstractModule, Module>::value)
            throw Error(Error::InvalidModuleType, "Type de module inconnue (Module = " + type_name<Module>() + ").");

        Module *mod = nullptr;

        auto id = type_hash<Module>();

        // The module of type Module already exists ?
        auto found = m_modules.find(id);
        if( found != m_modules.end())
        {
            throw Error(Error::ModuleAlreadyExists, "Le module de type " + type_name<Module>() + " existe déjà.");
        }
        else
        {
            mod = new Module(*this);
            m_modules[id] = mod;
        }

        return mod;
    }

    template <typename Module>
    AbstractModule* get() const
    {
        static_assert(!std::is_same<AbstractModule, Module>::value, "Impossible d'instancier un objet du type AbstractModule.");

        if(!std::is_base_of<AbstractModule, Module>::value)
            throw Error(Error::InvalidModuleType, "Type de module inconnue (Module = " + type_name<Module>() + ").");

        auto id = type_hash<Module>();
        auto found = m_modules.find(id);
        if(found != m_modules.end())
        {
            return found->second;
        }
        else
        {
            throw Error(Error::ModuleNotCreated, "Le module " + type_name<Module>() + " n'est pas encore créé.");
            return nullptr;
        }
    }

    template <typename Module>
    void destroyModule()
    {
        static_assert(!std::is_same<AbstractModule, Module>::value, "Impossible d'instancier un objet du type AbstractModule.");

        if(!std::is_base_of<AbstractModule, Module>::value)
            throw Error(Error::InvalidModuleType, "Type de module inconnue (Module = " + type_name<Module>() + ").");

        auto id = type_hash<Module>();
        auto found = m_modules.find(id);
        if(found != m_modules.end())
        {
            delete found->second;
            m_modules.erase(found);
        }
        else
        {
            throw Error(Error::ModuleNotCreated, "Le module " + type_name<Module>() + " n'est pas encore créé.");
        }
    }

    template <typename Module>
    void sendEventTo(std::unique_ptr<ModuleEvent> event) const
    {
        auto* mod = get<Module>();
        mod->pushEvent(std::move(event));
    }

    ModuleIterator begin()
    {
        return m_modules.begin();
    }
    ModuleIterator end()
    {
        return m_modules.end();
    }

protected:
    std::unordered_map<std::size_t, AbstractModule* > m_modules;
};

#endif // MODULEMANAGER_H
