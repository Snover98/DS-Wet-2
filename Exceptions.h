//
// Created by oded on 30/11/17.
//

#ifndef DS_WET_2_EXCEPTIONS_H
#define DS_WET_2_EXCEPTIONS_H

#include <stdexcept>

namespace ListExceptions {
    class ElementNotFound : public std::runtime_error {
    public:
        ElementNotFound() : std::runtime_error("Element not found") {}
    };
}

#endif //DS_WET_2_EXCEPTIONS_H
