#pragma once

#include <libutils/RefPtr.h>
#include <libutils/StringStorage.h>

class String
{
private:
    RefPtr<StringStorage> _buffer;

public:
    size_t length() { return _buffer->length(); }
    const char *cstring() { return _buffer->cstring(); }

    String(const char *cstring = "")
    {
        _buffer = make<StringStorage>(cstring);
    }

    String(const char *cstring, size_t length)
    {
        _buffer = make<StringStorage>(cstring, length);
    }

    String(const String &other) : _buffer(const_cast<String &>(other)._buffer) {}

    String(String &&other) : _buffer(move(other._buffer)) {}

    ~String() {}

    String &operator=(const String &other)
    {
        if (this != &other)
        {
            _buffer = const_cast<String &>(other)._buffer;
        }

        return *this;
    }

    String &operator=(String &&other)
    {
        if (this != &other)
        {
            _buffer = move(other._buffer);
        }

        return *this;
    }

    bool operator==(String &&other)
    {
        if (length() != other.length())
        {
            return false;
        }

        for (size_t i = 0; i < length(); i++)
        {
            if (cstring()[i] != other.cstring()[i])
            {
                return false;
            }
        }

        return true;
    }
};
