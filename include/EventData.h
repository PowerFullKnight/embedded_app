#ifndef EVENTDATA_H_INCLUDED
#define EVENTDATA_H_INCLUDED

#include <typeinfo>

#include "AbstractData.h"

template <typename Type = int>
class EventData : public AbstractData
{
    public:
        EventData(const std::string& id, Type value) : AbstractData(id),
            m_value(value)
        {

        }

        virtual ~EventData() {}

        void setValue(Type& value)
        {
            m_value = value;
        }

        Type value() const { return m_value; }

    private:
        Type    m_value;
};

#endif // EVENTDATA_H_INCLUDED
