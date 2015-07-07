#ifndef ABSTRACTDATA_H_INCLUDED
#define ABSTRACTDATA_H_INCLUDED

#include <string>
#include <typeinfo>

class AbstractData
{
    public:
        AbstractData(const std::string& id):
            m_dataId(id)
        {}

        virtual ~AbstractData() {}

        const std::string id() const { return m_dataId; }

    protected:
        const std::string m_dataId;

};

#endif // ABSTRACTDATA_H_INCLUDED
