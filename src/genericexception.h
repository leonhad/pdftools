#ifndef GENERICEXCEPTION_H
#define GENERICEXCEPTION_H

#include <stdexcept>
#include <string>

class GenericException : public std::exception
{
private:
    const std::string m_msg;

public:
    GenericException(std::string msg) noexcept;
    GenericException(GenericException && ex) noexcept;
    virtual ~GenericException() noexcept = default;

    virtual const char* what() const noexcept override;
};

#endif // GENERICEXCEPTION_H
