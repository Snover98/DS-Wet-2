//
// Created by oded on 30/11/17.
//

#ifndef DS_WET_2_EXCEPTIONS_H
#define DS_WET_2_EXCEPTIONS_H

#include <stdexcept>

namespace DSExceptions {
    class ElementNotFound : public std::runtime_error {
    public:
        ElementNotFound() : std::runtime_error("Element not found") {}
    };
    class TrainerNotFound : public std::runtime_error {
    public:
        TrainerNotFound() : std::runtime_error("Element not found") {}
    };
    class TrainerAlreadyIn : public std::runtime_error {
    public:
        TrainerAlreadyIn() : std::runtime_error("Element is already in") {}
    };
    class GladiatorNotFound : public std::runtime_error {
    public:
        GladiatorNotFound() : std::runtime_error("Element not found") {}
    };
    class GladiatorAlreadyIn : public std::runtime_error {
    public:
        GladiatorAlreadyIn() : std::runtime_error("Element is already in") {}
    };

}

#endif //DS_WET_2_EXCEPTIONS_H
