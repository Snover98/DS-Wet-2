#ifndef DS_WET_2_BINTREE_H
#define DS_WET_2_BINTREE_H

#include "genericFunction.h"
#include "TreeNode.h"

template <typename T>
void swap(T &n1, T &n2) // Note the &
{
    T temp=n1; // Note use the type T
    n1=n2;
    n2=temp;
}

template<class T>
class BinTree {
protected:
    //tree root
    TreeNode<T>* root;

    //comparison function
    Compare<T>& comp;

    /* * * * * * * * * * * * *\
    |* CLASS INNER FUNCTIONS *|
    \* * * * * * * * * * * * */
    //switch the info of two nodes
    void switchNodes(TreeNode<T>* t1, TreeNode<T>* t2);

    //find the node with the inputted info. returns the closest node if the info is not in the tree
    TreeNode<T>* findNode(T& info, TreeNode<T>* start);

    //find the maximal node of the sub-tree start
    TreeNode<T>* findMaxNode(TreeNode<T>* start);

    //find the minimal node of the sub-tree start
    TreeNode<T>* findMinNode(TreeNode<T>* start);

    //insert a node into the sub-tree 'start'
    void insertNode(TreeNode<T>* t, TreeNode<T>* start);
    //insert info into the tree and return it's node
    TreeNode<T>* insertInfo(T& info);

    //remove a node
    void removeNode(TreeNode<T>* t);
    
    //removing all nodes + deleting all inner info
    void removeAllNodesAndDeleteInfo(TreeNode<T>* p);

    //removing all nodes without deleting the info inside the nodes
    void removeAllNodes(TreeNode<T>* p);

    //the recursive functions that run a function recursively in a certain order (regarding all the orders)
    void recursiveInorder(TreeNode<T>* p, Func<T>& func);

    void recursivePreorder(TreeNode<T>* p, Func<T>& func);

    void recursivePostorder(TreeNode<T>* p, Func<T>& func);

    void recursiveInverseOrder(TreeNode<T>* p, Func<T>& func);

public:
    //normal constructor
    BinTree(Compare<T>* c) : root(NULL), comp(*c) {}

    ~BinTree();

    //Checks if the tree is empty
    bool isEmpty() const { return root == NULL; }

    //find node with relevant info. returns NULL if there is none
    virtual T* find(T& info);

    //find node with highest info value the tree. returns NULL if there is none
    virtual T* findMax();

    //find node with lowest info value the tree. returns NULL if there is none
    virtual T* findMin();

    //insert node with relevant info. returns NULL if there it already exists
    virtual void insert(T& info);

    //removes the node with relevant info. returns false if it doesn't exist, true otherwise.
    virtual bool remove(T& info);

    //remove all nodes from binary tree
    void removeAll();

    //remove all nodes from binary tree and deletes  the info too (assuming the
    // info was allocated using 'new' - we delete the info using 'delete'
    void removeAllAndDeleteInfo();


    //different orders to run a function on the tree's nodes
    void Inorder(Func<T>& func);

    void Preorder(Func<T>& func);

    void Postorder(Func<T>& func);

    void InverseOrder(Func<T>& func);
};

template<class T>
BinTree<T>::~BinTree(){
    removeAll();
    delete &comp;
}

template<class T>
T* BinTree<T>::find(T& info) {
    //check if the tree is empty
    if(isEmpty()){
        return NULL;
    }

    //search for a node with the info
    TreeNode<T>* found = findNode(info, root);

    if(comp(found->info, info) == 0){//if the found node was the correct one
        return &(found->info);
    }

    //otherwise, there is no node with the info
    return NULL;
}

template<class T>
T* BinTree<T>::findMax() {
    //check if the tree is empty
    if(isEmpty()){
        return NULL;
    }
    return &(findMaxNode(root)->info);
}

template<class T>
T* BinTree<T>::findMin() {
    //check if the tree is empty
    if(isEmpty()){
        return NULL;
    }
    return &(findMinNode(root)->info);
}

template<class T>
void BinTree<T>::insert(T& info) {
    //use the inner function
    insertInfo(info);
}

template<class T>
bool BinTree<T>::remove(T& info) {
    //the info cannot be in the tree if it's empty
    if(isEmpty()) {
        return false;
    }

    //find the node
    TreeNode<T>* t = findNode(info, root);

    //if the info is not in the tree
    if(comp(info, t->info) != 0){
        return false;
    }

    //remove t
    removeNode(t);
    return true;
}

template<class T>
void BinTree<T>::removeAll() {
    removeAllNodes(root);
    root = NULL;
}

template<class T>
void BinTree<T>::removeAllNodes(TreeNode<T>* p) {
    if (p == NULL){
        return;
    }

    removeAllNodes(p->left);

    removeAllNodes(p->right);

    delete p;
}

template<class T>
void BinTree<T>::removeAllAndDeleteInfo() {
    removeAllNodesAndDeleteInfo(root);
    root = NULL;
}

template<class T>
void BinTree<T>::removeAllNodesAndDeleteInfo(TreeNode<T>* p) {
    if(p == NULL){
        return;
    }

    removeAllNodesAndDeleteInfo(p->left);

    removeAllNodesAndDeleteInfo(p->right);

    delete &(p->info);
    delete p;
}

template<class T>
void BinTree<T>::Inorder(Func<T>& func) {
    recursiveInorder(root, func);
}

template<class T>
void BinTree<T>::recursiveInorder(TreeNode<T>* p, Func<T>& func) {
    if (p == NULL){
        return;
    }

    recursiveInorder(p->left, func);

    func(p->info);

    recursiveInorder(p->right, func);
}

template<class T>
void BinTree<T>::Postorder(Func<T>& func) {
    recursivePostorder(root, func);
}

template<class T>
void BinTree<T>::recursivePostorder(TreeNode<T>* p, Func<T>& func) {
    if (p == NULL){
        return;
    }

    recursivePostorder(p->left, func);

    recursivePostorder(p->right, func);

    func(p->info);
}

template<class T>
void BinTree<T>::Preorder(Func<T>& func) {
    recursivePreorder(root, func);
}

template<class T>
void BinTree<T>::recursivePreorder(TreeNode<T>* p, Func<T>& func) {
    if (p == NULL){
        return;
    }

    func(p->info);

    recursivePreorder(p->left, func);

    recursivePreorder(p->right, func);
}

template<class T>
void BinTree<T>::InverseOrder(Func<T>& func){
    recursiveInverseOrder(root, func);
}

template<class T>
void BinTree<T>::recursiveInverseOrder(TreeNode<T>* p, Func<T>& func) {
    if (p == NULL){
        return;
    }

    recursiveInverseOrder(p->right, func);

    func(p->info);

    recursiveInverseOrder(p->left, func);
}

template<class T>
void BinTree<T>::switchNodes(TreeNode<T> *t1, TreeNode<T> *t2) {
    //switch left children
    if(t1->left != NULL){
        t1->left->parent = t2;
    }

    if(t2->left != NULL){
        t2->left->parent = t1;
    }

    swap(t1->left, t2->left);
//    TreeNode<T>* t1_old_left = t1->left;
//    t1->left = t2->left;
//    t2->left = t1_old_left;

    //switch right children
    if(t1->right != NULL){
        t1->right->parent = t2;
    }

    if(t2->right != NULL){
        t2->right->parent = t1;
    }

    swap(t1->right, t2->right);
//    TreeNode<T>* t1_old_right = t1->right;
//    t1->right = t2->right;
//    t2->right = t1_old_right;

    //switch parents
    if(t1->parent != NULL){
        if(t1->parent->right == t1){
            t1->parent->right = t2;
        } else{
            t1->parent->left = t2;
        }
    }

    if(t2->parent != NULL){
        if(t2->parent->right == t2){
            t2->parent->right = t1;
        } else{
            t2->parent->left = t1;
        }
    }

    swap(t1->parent, t2->parent);

    //if one of them is the root, change the root
    if(root == t1){
        root = t2;
    } else if(root == t2){
        root = t1;
    }


//    TreeNode<T>* t1_old_parent = t1->parent;
//    t1->parent = t2->parent;
//    t2->parent = t1_old_parent;

//
//    T& old_t1_info = t1->info;
//    t1->info = t2->info;
//    t2->info = old_t1_info;
}

template<class T>
TreeNode<T>* BinTree<T>::findNode(T &info, TreeNode<T> *start){
    TreeNode<T>* curr = start;

    while(curr != NULL) {
        //if this is the node
        if(comp(info, curr->info) == 0) {
            return curr;
        }
        //if the info is less, go right if possible
        if(comp(info, curr->info) > 0) {
            if(curr->right == NULL){//if there is no node with the info, return the closet one possible
                return curr;
            } else {
                curr = curr->right;
            }
        } else {//else, go left if possible
            if(curr->left == NULL){//if there is no node with the info, return the closet one possible
                return curr;
            } else {
                curr = curr->left;
            }
        }
    }
    //if none of the above happened, the info isn't in the tree
    return NULL;
}

template<class T>
TreeNode<T>* BinTree<T>::findMaxNode(TreeNode<T> *start){
    if(isEmpty()){
        return NULL;
    }

    TreeNode<T>* curr = start;

    while (curr->right != NULL) {
        curr = curr->right;
    }
    return curr;
}

template<class T>
TreeNode<T>* BinTree<T>::findMinNode(TreeNode<T> *start){
    if(isEmpty()){
        return NULL;
    }

    TreeNode<T>* curr = start;

    while (curr->left != NULL) {
        curr = curr->left;
    }
    return curr;
}

template<class T>
void BinTree<T>::insertNode(TreeNode<T> *t, TreeNode<T> *start){
    //find the closest node
    TreeNode<T>* closest = findNode(t->info, start);

    //if the there is no node with the same info
    if(comp(t->info, closest->info) != 0){
        if(comp(t->info, closest->info) < 0){  //if it should be to the left of the closest
            closest->left = t;
        } else {    //if it should be to the right of the closest
            closest->right = t;
        }
        t->parent = closest;
    } else {    //if there is another node with the same info, put this node to the right of it
        if(closest->right == NULL){ //if the closest node has no right child
            closest->right = t;
            t->parent = closest;
        } else {    //otherwise, insert t to the right of the closest
            insertNode(t, closest->right);
        }
    }
}

template<class T>
TreeNode<T>* BinTree<T>::insertInfo(T &info){
    //create the node
    TreeNode<T>* t = new TreeNode<T>(info);

    //If this is an empty tree
    if(isEmpty()) {
        root = t;
        return t;
    }

    insertNode(t, root);
    return t;
}

template<class T>
void BinTree<T>::removeNode(TreeNode<T> *t){
    //if the node is a leaf
    if(t->right == NULL && t->left == NULL){
        //remove the node from it's parent, if it has one
        if(t->parent != NULL){
            if(t->parent->left == t){
                t->parent->left = NULL;
            } else {
                t->parent->right = NULL;
            }
        } else {
            root = NULL;
        }

        //delete the node
        t->parent = NULL;
        delete t;

        return;
    }

    //if the node only has one child (if we got here we know that it has children)
    if(t->left == NULL || t->right == NULL) {
        //save the child
        TreeNode<T> *child = (t->left != NULL) ? t->left : t->right;

        //replace the node with it's child in its parent, if it has one
        if(t->parent != NULL){
            if (t->parent->left == t) {
                t->parent->left = child;
            } else {
                t->parent->right = child;
            }
        } else {
            root = child;
        }

        child->parent = t->parent;

        //delete the node
        t->left = NULL;
        t->right = NULL;
        t->parent = NULL;
        delete t;

        return;
    }

    //if the node has 2 children (happens if we got here)
    //find the following node
    TreeNode<T>* t_follower = findMinNode(t->right);
    //switch between them
    switchNodes(t, t_follower);

    //remove t again
    removeNode(t);
}





#endif //DS_WET_2_BINTREE_H
