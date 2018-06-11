#include "exception.h"

SnakeException::SnakeException(const std::string& msg)
    : std::runtime_error(msg) {}

SnakeException::~SnakeException() noexcept = default;
