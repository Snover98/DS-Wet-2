//
// Created by oded on 29/11/17.
//

#ifndef DS_WET_2_SPLAYTREE_H
#define DS_WET_2_SPLAYTREE_H

#include "binTree.h"

template <class T, class Compare>
class SplayTree:BinTree{
private:
    void splay();
public:
    SplayTree(Compare c):BinTree(c){}
    SplayTree():BinTree(){}
};

#endif //DS_WET_2_SPLAYTREE_H
