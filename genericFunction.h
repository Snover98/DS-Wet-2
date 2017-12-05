//
// Created by Assaf-Haik-Barouch on 05/12/2017.
//

#ifndef DS_WET_2_GENERICFUNCTION_H
#define DS_WET_2_GENERICFUNCTION_H

template<class T>
class Func{
public:
    virtual void operator()(T& t);
};

#endif //DS_WET_2_GENERICFUNCTION_H
