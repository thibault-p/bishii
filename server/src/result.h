#pragma once

#include <optional.hpp>

#include <exception>
#include <string>


template<class T>
class Result
{
public:
    static Result<T> failure(std::string error)
    {
        return Result(false,nonstd::nullopt, nonstd::optional<std::string>(error));
    }

    static Result<T> success(T value)
    {
        return Result(true, nonstd::optional<T>(value), nonstd::nullopt);
    }

    bool isFailure() const
    {
        return !m_success;
    }

    bool isSuccess() const
    {
        return m_success;
    }

    const T& getValue() const
    {
        if (!m_success)
        {
            throw std::runtime_error("");
        }
        return m_value.value();
    }

    const std::string& getError() const
    {
        if (m_success)
        {
            throw std::runtime_error("");
        }
        return m_error.value();
    }

private:
    Result(bool success, nonstd::optional<T> value, nonstd::optional<std::string> error) :
        m_success(success), m_value(value), m_error(error)
    {}

    bool m_success;
    const nonstd::optional<T> m_value;
    const nonstd::optional<std::string> m_error;
};
