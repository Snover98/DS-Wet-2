//
// Created by oded on 29/11/17.
//

#ifndef DS_WET_2_SPLAYTREE_H
#define DS_WET_2_SPLAYTREE_H

#include "binTree.h"

template <class T, class Compare>
class SplayTree:BinTree<T,Compare>{
private:
    void splay();
public:
    SplayTree(T& i, BinTree<T,Compare>& p, BinTree<T,Compare>& l, BinTree<T,Compare>& r, Compare c):BinTree<T,Compare>(i,p,l,r,c){}
    SplayTree(T& i, BinTree<T,Compare>& p, BinTree<T,Compare>& l, BinTree<T,Compare>& r):BinTree<T,Compare>(i,p,l,r){}
};

#endif //DS_WET_2_SPLAYTREE_H
