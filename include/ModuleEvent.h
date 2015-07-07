#ifndef MODULEEVENT_H
#define MODULEEVENT_H

#include <memory>
#include "make_unique.h"
#include <string>
#include <map>
#include <typeinfo>
#include <type_traits>


#include "ModuleError.h"
#include "EventData.h"
#include "typename.h"

class ModuleEvent
{
public:
    enum EventType
    {
        Nothing = 0,

        // Gpio
        MotorGoAhead,
        MotorStop,
        MotorRotateLeft,
        MotoroRotateRight,

        // System
        RaspberryShutdown,
        RaspberryReboot,

        // Log
        Warning,
        Error,
        Critical
    };

    ModuleEvent(EventType type):
        m_datas(), m_type(type)
    {

    }
    ModuleEvent(const ModuleEvent& event) = delete;

    ~ModuleEvent()
    {
        for(auto pair : m_datas)
        {
            delete pair.second;
        }
    }

    template <class Type>
    void add(const std::string& id, const Type& value)
    {
        if(m_datas.find(id) == m_datas.end())
        {
            EventData<Type>* prop = new EventData<Type>(id, value);
            m_datas[id] = prop;
        }
        else
        {
            throw ::Error(::Error::DataAlreadyExists, "La donnée correspondant à l'identifiant " + id + " existe déjà.");
        }
    }

    template <class Type>
    Type get(const std::string& id)
    {
        const auto iter = m_datas.find(id);
        if(iter != m_datas.end())
        {
            EventData<Type>* data = dynamic_cast<EventData<Type>*>(iter->second);
            if(data != nullptr)
            {
                return data->value();
            }
            else
            {
                throw ::Error(::Error::NoDataFound, "La donnée correspondant à l'identifiant " + id + " n'est pas de type " + type_name<Type>());
            }
        }
        else
        {
            throw ::Error(::Error::NoDataFound, "La donnée correspondant à l'identifiant " + id + " n'a pas été trouvée.");
        }
    }

    EventType getEventType() const
    {
        return m_type;
    }

protected:
    std::map<std::string, AbstractData*> m_datas;
    const EventType m_type;

};


#endif // MODULEEVENT_H
