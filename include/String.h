//
// Created by maciek on 14.06.16.
//

#pragma once

#include <stdlib.h>
#include <cstdio>

class String
{
private:
    char *_ptr = nullptr;
    unsigned long _maxSize = 0;
    unsigned long _len = 0;

    inline void allocateString()
    {
        _maxSize = _len * 2;
        _ptr = new char[_maxSize];
        _ptr[0] = 0;
    }

    inline void copyString(const char *from)
    {
        strcpy(_ptr, from);
    }

    inline void reallocateString()
    {
        auto lastPtr = _ptr;
        allocateString();
        if (lastPtr != nullptr)
        {
            copyString(lastPtr);
            delete[] lastPtr;
        }
    }

    inline void appendString(const char *string)
    {
        auto len = strlen(string);
        _len += len;
        if (_len >= _maxSize)
            reallocateString();
        strcat(_ptr, string);
    }

    inline void clear()
    {
        if (_ptr != nullptr)
            delete[] _ptr;
        _ptr = nullptr;
        _maxSize = 0;
        _len = 0;
    }

public:

    inline String()
    { }

    inline ~String()
    {
        if (_ptr != nullptr)
            delete[] _ptr;
    }

    inline String(const char *cString)
        : _len(strlen(cString))
    {
        allocateString();
        copyString(cString);
    }

    inline String(const String &string)
        : _len(string._len)
    {
        allocateString();
        copyString(string._ptr);
    }

    inline String(String &&string)
        : _ptr(string._ptr), _maxSize(string._maxSize), _len(string._len)
    {
        string._maxSize = 0;
        string._len = 0;
        string._ptr = nullptr;
    }

    inline bool isEmpty()
    {
        return _maxSize == 0;
    }

    inline unsigned long size()
    {
        return _len;
    }

    inline char &operator [](int index)
    {
        if (index > _len)
            return _ptr[_len];
        return _ptr[index];
    }

    inline String &operator =(const String &other)
    {
        clear();
        _len = other._len;
        allocateString();
        copyString(other._ptr);
        return *this;
    }

    inline void append(const char *string)
    {
        appendString(string);
    }

    inline void append(String &string)
    {
        appendString(string._ptr);
    }

    inline void append(String &&string)
    {
        appendString(string._ptr);
    }

    inline void append(int number)
    {
        char string[32];
        sprintf(string, "%d", number);
        appendString(string);
    }

    inline void append(unsigned int number)
    {
        char string[32];
        sprintf(string, "%u", number);
        appendString(string);
    }

    inline void append(void *address)
    {
        char string[32];
        sprintf(string, "0x%x", address);
        appendString(string);
    }

    inline String &operator <<(String &string)
    {
        appendString(string._ptr);
        return *this;
    }

    inline String &operator <<(const char *string)
    {
        appendString(string);
        return *this;
    }

    inline bool operator ==(const String &string)
    {
        return strcmp(_ptr, string._ptr) == 0;
    }

    inline bool operator ==(const char *string)
    {
        return strcmp(_ptr, string) == 0;
    }

    inline bool operator !=(const String &string)
    {
        return strcmp(_ptr, string._ptr) != 0;
    }

    inline bool operator !=(const char *string)
    {
        return strcmp(_ptr, string) != 0;
    }

    inline operator char *()
    {
        return _ptr;
    }

};

