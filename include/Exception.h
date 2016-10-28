#pragma once

class Exception {

public:
    virtual const char *what()
    {
        return "Standard exception";
    }
};

class EmptyContainerException : public Exception {

public:
    const char *what() final override
    {
        return "Empty container exception";
    }
};


