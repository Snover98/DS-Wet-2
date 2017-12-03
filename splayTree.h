//
// Created by oded on 29/11/17.
//

#ifndef DS_WET_2_SPLAYTREE_H
#define DS_WET_2_SPLAYTREE_H

#include "binTree.h"

template <class T, class Compare>
class SplayTree:BinTree{
private:

    //the splay - moving a node to the root
    void splay(TreeNode* t);

    //the rolls used in the splay
    void zig(TreeNode* t);
    void zag(TreeNode* t);
    void zigZig(TreeNode* t);
    void zagZag(TreeNode* t);
    void zigZag(TreeNode* t);
    void zagZig(TreeNode* t);
public:
    SplayTree(Compare c):BinTree(c){}
    SplayTree():BinTree(){}

    //find node with relevant info. returns NULL if there is none
    T& find(T& info) override;

    //find node with highest info value the tree. returns NULL if there is none
    T& findMax() override;

    //find node with lowest info value the tree. returns NULL if there is none
    T& findMin() override;

    //insert node with relevant info. returns NULL if there it already exists
    void insert(T& info) override;

    //removes the node with relevant info. returns false if it doesn't exist, true otherwise.
    virtual bool remove(T& info) override;

    //join two trees, where every node in tree2 has a higher info value than those in this tree
    void join(SplayTree tree2);

    //split the tree in accordance to the inserted pivot
    SplayTree split();
};

#endif //DS_WET_2_SPLAYTREE_H
