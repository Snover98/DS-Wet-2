//
// Created by oded on 29/11/17.
//

#ifndef DS_WET_2_BINTREE_H
#define DS_WET_2_BINTREE_H

#include <iostream>
#include <cstdlib>
using namespace std;

template <class T>
class DefComp{
public:
    DefComp();
    ~DefComp();

    int operator()(T& t1, T& t2){
        if(t1 == t2){
            return 0;
        }
        return (t1<t2)?-1:1;
    }
};

template<class T, class Compare>
class BinTree{
private:
    struct tree_node {
        tree_node* parent;
        tree_node* left;
        tree_node* right;
        T* info;
    };
    tree_node* root;
    Compare comp;
public:
    //normal constructor
    BinTree(Compare comp): comp(comp), root(NULL) {}
    BinTree():comp(DefComp<T>()), root(NULL) {}
    ~BinTree();

    //Checks if the tree is empty
    bool isEmpty() const { return root==NULL; }

    //find node with relevant info. returns NULL if there is none
    T& find(T& info);

    //find node with highest info value the tree. returns NULL if there is none
    T& findTop();

    //insert node with relevant info. returns NULL if there it already exists
    void insert(T& info);

    //removes the node with relevant info. returns false if it doesn't exist, true otherwise.
    bool remove(T& info);

    //different prints in a binary search tree
    void printInorder(tree_node* p);
    void Inorder();
    void printPreorder(tree_node* p);
    void Preorder();
    void printPostorder(tree_node* p);
    void Postorder();
};

template <class T, class Compare>
T& BinTree<T,Compare>::find(T& info){
    tree_node* curr=root;

    while(curr) {
        //if this is the node
        if(comp(info, curr->info) == 0){
            return *(curr->info);
        }
        //if the info is less, go right if possible
        if(comp(info, curr->info) > 0) {
            curr = curr->right;
        } else {//else, go left if possible
            curr = curr->left;
        }
    }
    //if none of the above happened, the info isn't in the tree
    return NULL;
}

template <class T, class Compare>
T& BinTree<T,Compare>::findTop() {
    tree_node* curr=root;

    while(curr->right != NULL) {
        curr = curr->right;
    }
    return *(curr->info);
}

template <class T, class Compare>
void BinTree<T,Compare>::insert(T& info){
    tree_node* t = new tree_node;
    t->info=info;
    t->left=NULL;
    t->right=NULL;
    t->parent=NULL;
    //If this is a new tree
    if(isEmpty()) {
        root = t;
    }

    tree_node* new_parent;
    tree_node* curr = root;
    while(curr) {
        new_parent = curr;

        //if the info is less or equal, go right if possible
        if(comp(info, curr->info) >= 0) {
            curr = curr->right;
        } else {//else, go left if possible
            curr = curr->left;
        }
    }

    if(comp(info, new_parent->info) < 0) {
        new_parent->left = t;
    } else {
        new_parent->right = t;
    }

    t->parent=new_parent;
}

template <class T, class Compare>
bool BinTree<T,Compare>::remove(T& info){
    if(isEmpty()) {
        return false;
    }

    tree_node* curr = find(info);

    if(!curr)
        return false;

    tree_node* new_parent = curr->parent;

    //if curr has only right son
    if(curr->left == NULL && curr->right != NULL){
        //if the left node of the parent is the current node
        if(new_parent->left == curr) {
            new_parent->left = curr->right;
            curr->right->parent=new_parent;
        } else {
            new_parent->right = curr->right;
            curr->left->parent=new_parent;
        }
        delete curr;
        return true;
    }

    //if there is only a left son
    if(left != NULL && right == NULL){
        //if the left node of the parent is the current node
        if(new_parent->left == curr) {
            new_parent->left = curr->left;
            curr->left->parent=new_parent;
        } else {
            new_parent->right = curr->left;
            curr->left->parent=new_parent;
        }
        delete curr;
        return true;
    }

    //if its a leaf node with no sons, we just delete it
    if(left == NULL && right == NULL) {
        if(new_parent->left == curr) {
            new_parent->left = NULL;
        } else {
            new_parent->right = NULL;
        }
        delete curr;
        return true;
    }

    //its a node with 2 children:
    //replace the current node with the smallest node in its right subtree
    if(left != NULL && right != NULL){
        //if the current right son is a leaf, replace it with the current node
        if(curr->right == NULL && curr->left == NULL) {
            curr->info=curr->right->info;
            delete curr->right;
            curr->right = NULL;
        } else { //right son has children

            //if the current right child has a left child
            if(curr->right->left != NULL) {
                tree_node* leftest =curr->right->left;
                while(leftest->left!=NULL){
                    leftest = leftest->left;
                }
                curr->info = leftest->info;
                leftest->parent->left=leftest->parent->right;
                delete leftest;
            } else {
                tree_node* temp = curr->right;
                curr->info=temp->info;
                curr->right=temp->right;
                temp->right->parent=curr->right;
                delete temp;
            }
        }
        return true;
    }

    //if none of the above happened, the info isn't in the tree
    return false;
}

template <class T, class Compare>
void BinTree<T,Compare>::Inorder() {
    printInorder(root);
}

template <class T, class Compare>
void BinTree<T,Compare>::printInorder(tree_node* p) {
    if(p != NULL)
        return;

    if(p->left)
        printInorder(p->left);

    cout<<" "<<p->info<<" ";

    if(p->right)
        printInorder(p->right);

    return;
}

template <class T, class Compare>
void BinTree<T,Compare>::Postorder() {
    printPostorder(root);
}

template <class T, class Compare>
void BinTree<T,Compare>::printPostorder(tree_node* p) {
    if(p != NULL)
        return;

    if(p->left)
        printInorder(p->left);

    if(p->right)
        printInorder(p->right);

    cout<<" "<<p->info<<" ";

    return;
}

template <class T, class Compare>
void BinTree<T,Compare>::Preorder() {
    printPreorder(root);
}

template <class T, class Compare>
void BinTree<T,Compare>::printPreorder(tree_node* p)  {
    if(p != NULL)
        return;

    cout<<" "<<p->info<<" ";

    if(p->left)
        printInorder(p->left);

    if(p->right)
        printInorder(p->right);

    return;
}

#endif //DS_WET_2_BINTREE_H
