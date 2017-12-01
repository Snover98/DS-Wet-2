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
    SplayTree(T& i, BinTree& p, BinTree& l, BinTree& r, Compare c):BinTree(i,p,l,r,c){}
    SplayTree(T& i, BinTree& p, BinTree& l, BinTree& r):BinTree(i,p,l,r){}
};

#endif //DS_WET_2_SPLAYTREE_H
