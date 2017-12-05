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

template<class T>
class Compare{
public:
    virtual int operator()(T& t1, T& t2);
};

#endif //DS_WET_2_GENERICFUNCTION_H
