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
    bool remove(T& info) override;

//    //join two trees, where every node in tree2 has a higher info value than those in this tree
//    void join(SplayTree tree2);
//
//    //split the tree in accordance to the inserted pivot
//    SplayTree split(T& pivot);
};

template<class T, class Compare>
T& SplayTree<T, Compare>::find(T& info){
    //find the node or the closest one in value if it does not exist
    TreeNode* found = BinTree::findNode(info);

    //move the found node to the root
    splay(found);

    //if it has the correct info, return it
    if(found->info == info){
        return info;
    }

    //otherwise, it was not found so return NULL
    return NULL;
};

template<class T, class Compare>
T& SplayTree<T, Compare>::findMax() {
    //find the max node
    TreeNode* max_node = BinTree::findMax();

    //move the max node to the root
    splay(max_node);

    //return the max info
    return max_node->info;
}

template<class T, class Compare>
T& SplayTree<T, Compare>::findMin() {
    //find the min node
    TreeNode* min_node = BinTree::findMin();

    //move the min node to the root
    splay(min_node);

    //return the min info
    return min_node->info;
}

template<class T, class Compare>
void SplayTree<T, Compare>::insert(T &info) {
    //temporary
    //insert the info normally
    BinTree::insert(info);

    //find it's node
    TreeNode* new_node = findNode(info);

    //splay the node
    splay(new_node);
}

template<class T, class Compare>
bool SplayTree<T, Compare>::remove(T &info){
    //remove normally
    BinTree::remove(info);
//    //find the node to be removed
//    TreeNode* found = findNode(info);
//
//    //check if it's actually in the tree





}

//template<class T, class Compare>
//void SplayTree<T, Compare>::join(SplayTree tree2){
//
//
//
//
//
//}
//
//template<class T, class Compare>
//SplayTree<T, Compare> SplayTree<T, Compare>::split(T &pivot){
//
//
//
//
//
//}



#endif //DS_WET_2_SPLAYTREE_H
