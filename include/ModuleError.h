#ifndef MODULEERROR_H_INCLUDED
#define MODULEERROR_H_INCLUDED

#include <string>
#include <exception>
#include <chrono>

class Error : public std::exception
{
public:
    enum ErrorCode
    {
        None = 0,

        // Modules errors
        InvalidModuleType,
        ModuleNotCreated,
        ModuleAlreadyExists,

        // Events errors
        NoDataFound,
        DataAlreadyExists
    };


    Error(ErrorCode code, const std::string& msg):
        m_code(code), m_message(msg), m_time(0)
    {
        std::chrono::steady_clock::time_point tp = std::chrono::steady_clock::now();
        std::chrono::steady_clock::duration dtn  = tp.time_since_epoch();
        m_time = dtn.count() * std::chrono::steady_clock::period::num / std::chrono::steady_clock::period::den;
    }

    ErrorCode getErrorCode() const noexcept
    {
        return m_code;
    }

    const char* what() const noexcept override
    {
        return m_message.c_str();
    }

    std::string getErrorString() const noexcept
    {
        return m_message;
    }

    long long int getTime() const noexcept
    {
        return m_time;
    }


protected :
    const ErrorCode m_code;
    const std::string m_message;
    long long int m_time; // Number of seconds since epoch
};

#endif // MODULEERROR_H_INCLUDED
