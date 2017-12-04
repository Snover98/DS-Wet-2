//
// Created by oded on 29/11/17.
//

#ifndef DS_WET_2_SPLAYTREE_H
#define DS_WET_2_SPLAYTREE_H

#include "binTree.h"

template <class T, class Compare>
class SplayTree:BinTree{
private:
    //the rolls used in the splay
    //when t's parent is the root and t is a left son
    void zig(TreeNode* t){
        TreeNode* parent = t->parent;

        //move t's right subtree to the parent
        t->right->parent = parent;
        parent->left = t->right;


        //change t's parent, it's the new root
        t->parent = NULL;

        //make t the former parent's parent
        parent->parent = t;
        t->right = parent;
    }

    //when t's parent is the root and t is a right son
    void zag(TreeNode* t){
        TreeNode* parent = t->parent;

        //move t's left subtree to the parent
        t->left->parent = parent;
        parent->right = t->left;


        //change t's parent, it's the new root
        t->parent = NULL;

        //make t the former parent's parent
        parent->parent = t;
        t->left = parent;
    }

    //t is the left son of a left son
    void zigZig(TreeNode* t){
        TreeNode* parent = t->parent;
        TreeNode* grand_parent = parent->parent;

        //make sure that the grandparent's parent is now t's parent (only make it t's parent if it's NULL)
        t->parent = grand_parent->parent;
        if(grand_parent->parent->left == grand_parent && grand_parent->parent != NULL){
            grand_parent->parent->left = t;
        } else if(grand_parent->parent != NULL){
            grand_parent->parent->right = t;
        }

        //move the parent's right son to the grandparent's left son
        parent->right->parent = grand_parent;
        grand_parent->left = parent->right;

        //move t's right son to the parent's left son
        t->right->parent = parent;
        parent->left = t->right;

        //make the former parent t's right son
        parent->parent = t;
        t->right = parent;

        //make the former grandparent the former parent's right son
        grand_parent->parent = parent;
        parent->right = parent;
    }

    //t is the right son of a right son
    void zagZag(TreeNode* t){
        TreeNode* parent = t->parent;
        TreeNode* grand_parent = parent->parent;

        //make sure that the grandparent's parent is now t's parent (only make it t's parent if it's NULL)
        t->parent = grand_parent->parent;
        if(grand_parent->parent->left == grand_parent && grand_parent->parent != NULL){
            grand_parent->parent->left = t;
        } else if(grand_parent->parent != NULL){
            grand_parent->parent->right = t;
        }

        //move the parent's left son to the grandparent's right son
        parent->left->parent = grand_parent;
        grand_parent->right = parent->left;

        //move t's left son to the parent's right son
        t->left->parent = parent;
        parent->right = t->left;

        //make the former parent t's left son
        parent->parent = t;
        t->left = parent;

        //make the former grandparent the former parent's left son
        grand_parent->parent = parent;
        parent->left = parent;
    }

    //t is the right son of a left son
    void zigZag(TreeNode* t){
        TreeNode* parent = t->parent;
        TreeNode* grand_parent = parent->parent;

        //make sure that the grandparent's parent is now t's parent (only make it t's parent if it's NULL)
        t->parent = grand_parent->parent;
        if(grand_parent->parent->left == grand_parent && grand_parent->parent != NULL){
            grand_parent->parent->left = t;
        } else if(grand_parent->parent != NULL){
            grand_parent->parent->right = t;
        }

        //move t's left son to the parent's right son
        t->left->parent = parent;
        parent->right = t->left;

        //move t's right son to the grandparent's left son
        t->right->parent = grand_parent;
        grand_parent->left = t->right;

        //make the former parent into t's left son
        parent->parent = t;
        t->left = parent;

        //make the former grandparent into t's right son
        grand_parent->parent = t;
        t->right = grand_parent;
    }

    //t is the left son of a right son
    void zagZig(TreeNode* t){
        TreeNode* parent = t->parent;
        TreeNode* grand_parent = parent->parent;

        //make sure that the grandparent's parent is now t's parent (only make it t's parent if it's NULL)
        t->parent = grand_parent->parent;
        if(grand_parent->parent->left == grand_parent && grand_parent->parent != NULL){
            grand_parent->parent->left = t;
        } else if(grand_parent->parent != NULL){
            grand_parent->parent->right = t;
        }

        //move t's right son to the parent's left son
        t->right->parent = parent;
        parent->left = t->right;

        //move t's left son to the grandparent's right son
        t->left->parent = grand_parent;
        grand_parent->right = t->left;

        //make the former parent into t's right son
        parent->parent = t;
        t->right = parent;

        //make the former grandparent into t's left son
        grand_parent->parent = t;
        t->left = grand_parent;
    }

    //the splay - moving a node to the root
    void splay(TreeNode* t){
        //as long as t is not the root
        while(t->parent != NULL){
            if(t->parent->left == t){//if t is a left son
                if(t->parent->parent == NULL){//if t's parent is the root, zig
                    zig(t);
                } else if(t->parent->parent->left == t->parent){//if t is the left son of a left son zigZig
                    zigZig(t);
                } else{//if t is the left son of a right son zagZig
                    zagZig(t);
                }
            } else{//if t is right son
                if(t->parent->parent == NULL){//if t's parent is the root, zag
                    zag(t);
                } else if(t->parent->parent->right == t->parent){//if t is the right son of a right son zagZag
                    zagZag(t);
                } else{//if t is the right son of a left son zigZag
                    zigZag(t);
                }
            }
        }

        //update the root
        root = t;
    }

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
    //if the tree is empty, return NULL
    if(isEmpty()){
        return NULL;
    }

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
    //return NULL if the tree is empty
    if(isEmpty()){
        return NULL;
    }

    //find the max node
    TreeNode* max_node = BinTree::findMax();

    //move the max node to the root
    splay(max_node);

    //return the max info
    return max_node->info;
}

template<class T, class Compare>
T& SplayTree<T, Compare>::findMin() {
    //return NULL if the tree is empty
    if(isEmpty()){
        return NULL;
    }

    //find the min node
    TreeNode* min_node = BinTree::findMin();

    //move the min node to the root
    splay(min_node);

    //return the min info
    return min_node->info;
}

template<class T, class Compare>
void SplayTree<T, Compare>::insert(T &info) {
    //if the tree is empty, insert normally in the root
    if(isEmpty()){
        BinTree::insert(info);
    }

    //create the node
    TreeNode* t = new TreeNode;
    t->info = info;
    t->left = NULL;
    t->right = NULL;
    t->parent = NULL;


    //move the closet node to the info into the root
    //using split: this is the same as splitting the tree around info
    T& closest_info = find(info);

    //everything to the left of the root should have lower info value than info,
    //and everything to the right of the root should have higher info value than info,
    //but we need to check the root itself
    if(comp(info, root->info) <= 0){//if the root has an info value lower or equal to info's
        t->left = root;     //put the root to the left of the info
        root->parent = t;
        t->right = root->right;
        root->right = NULL;
        t->right->parent = t;
    } else{//if the root has an info value greater than info's
        t->right = root;    //put the root to the right of the info
        root->parent = t;
        t->left = root->left;
        root->left = NULL;
        t->left->parent = t;
    }

    //update the root
    root = t;
}

template<class T, class Compare>
bool SplayTree<T, Compare>::remove(T &info){
    //if the tree is empty or the info is the root, just remove normally
    if(isEmpty()){
        return false;
    }

    //find the closest info
    T& closest_info = find(info);

    //if the info is not in the tree, return false
    if(comp(info, closest_info) != 0){
        return false;
    }

    //split the tree around info
    TreeNode* left_subtree = root->left;
    TreeNode* right_subtree = root->right;
    left_subtree->parent = NULL;
    right_subtree->parent = NULL;
    //delete the node with the info
    root->left = NULL;
    root->right = NULL;
    delete root;
    //find the max info in the left subtree, splay it and make it the root
    root = left_subtree;//due to the implementation of splay, we will act as if the tree is only the left part for a bit
    findMaxNode();  //this splays the max node in the left subtree
    root->right = right_subtree;    //joins the subtree
    right_subtree->parent = root;

    //if the removal was successful, return true
    return true;
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
