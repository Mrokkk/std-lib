#pragma once

#include "types.h"

namespace yacppl {

template <class Printer>
class output_stream {

    Printer &_printer;

public:

    output_stream(Printer &printer)
        : _printer(printer) {
    }

    template <typename T>
    void print(T str) {
        _printer.append(str);
    }

};

} // namespace yacppl

