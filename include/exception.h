#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <stdexcept>
#include <string>

class SnakeException : public std::runtime_error
{
public:
    SnakeException(const std::string& msg);
    virtual ~SnakeException() noexcept;
};

#endif // EXCEPTION_H
