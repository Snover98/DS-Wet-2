#ifndef DS_WET_2_BINTREE_H
#define DS_WET_2_BINTREE_H

#include <iostream>
#include <cstdlib>

using namespace std;

template<class T>
class DefComp {
public:
    DefComp();

    ~DefComp();

    int operator()(T& t1, T& t2) {
        if(t1 == t2){
            return 0;
        }
        return (t1 < t2) ? -1 : 1;
    }
};

template<class T, class Compare>
class BinTree {
protected:
    struct TreeNode {
        TreeNode* parent;
        TreeNode* left;
        TreeNode* right;
        T& info;
    };
    TreeNode* root;
    Compare comp;

    TreeNode* findNode(T& info){
        TreeNode* curr = root;

        while(curr != NULL) {
            //if this is the node
            if(comp(info, curr->info) == 0) {
                return (curr->info);
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

    TreeNode* findMaxNode(){
        if(isEmpty()){
            return NULL;
        }

        TreeNode* curr = root;

        while (curr->right != NULL) {
            curr = curr->right;
        }
        return curr;
    }

    TreeNode* findMinNode(){
        if(isEmpty()){
            return NULL;
        }

        TreeNode* curr = root;

        while (curr->left != NULL) {
            curr = curr->left;
        }
        return curr;
    }

    void removeAllNodesAndDeleteInfo(TreeNode* p);

    void removeAllNodes(TreeNode* p);

    //the recursive functions that run a function recursively in a certain order
    template <typename Func>
    void recursiveInorder(TreeNode* p, Func func);

    template <typename Func>
    void recursivePreorder(TreeNode* p, Func func);

    template <typename Func>
    void recursivePostorder(TreeNode* p, Func func);

public:
    //normal constructor
    BinTree(Compare comp) : comp(comp), root(NULL) {}

    BinTree() : comp(DefComp<T>()), root(NULL) {}

    ~BinTree();

    //Checks if the tree is empty
    bool isEmpty() const { return root == NULL; }

    //find node with relevant info. returns NULL if there is none
    virtual T& find(T& info);

    //find node with highest info value the tree. returns NULL if there is none
    virtual T& findMax();

    //find node with lowest info value the tree. returns NULL if there is none
    virtual T& findMin();

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
    template <typename Func>
    void Inorder(Func func);

    template <typename Func>
    void Preorder(Func func);

    template <typename Func>
    void Postorder(Func func);
};

template<class T, class Compare>
T& BinTree<T, Compare>::find(T& info) {
    //search for a node with the info
    TreeNode* found = findNode(info);

    if(comp(found->info, info) == 0){//if the found node was the correct one
        return found->info;
    }

    //otherwise, there is no node with the info
    return NULL;
}

template<class T, class Compare>
T& BinTree<T, Compare>::findMax() {
    return findMaxNode()->info;
}

template<class T, class Compare>
T& BinTree<T, Compare>::findMin() {
    return findMinNode()->info;
}


template<class T, class Compare>
void BinTree<T, Compare>::insert(T& info) {
    TreeNode* t = new TreeNode;
    t->info = info;
    t->left = NULL;
    t->right = NULL;
    t->parent = NULL;

    //If this is a new tree
    if(isEmpty()) {
        root = t;
    }

    TreeNode* new_parent = root;
    TreeNode* curr = root;
    //until the needed parent is found (should have it's relative child as NULL)
    while(curr != NULL) {
        new_parent = curr;

        //if the info is less or equal, go right if possible
        if(comp(info, curr->info) >= 0) {
            curr = curr->right;
        } else {//else, go left if possible
            curr = curr->left;
        }
    }

    //check if the new node is the left or right child
    if(comp(info, new_parent->info) < 0) {
        new_parent->left = t;
    } else {
        new_parent->right = t;
    }

    //set the new node's parent
    t->parent = new_parent;
}

template<class T, class Compare>
bool BinTree<T, Compare>::remove(T& info) {
    if(isEmpty()) {
        return false;
    }

    TreeNode* curr = find(info);

    //if there is no node with that info in the tree
    if(curr == NULL){
        return false;
    }

    TreeNode* new_parent = curr->parent;

    //if curr only has a right son
    if(curr->left == NULL && curr->right != NULL) {
        //if the left node of the parent is the current node
        if(new_parent->left == curr) {
            new_parent->left = curr->right;
            curr->right->parent = new_parent;
        } else{//if the right node of the parent is the current node
            new_parent->right = curr->right;
            curr->left->parent = new_parent;
        }
        delete curr;
        return true;
    }

    //if there is only a left son
    if(curr->left != NULL && curr->right == NULL) {
        //if the left node of the parent is the current node
        if(new_parent->left == curr) {
            new_parent->left = curr->left;
            curr->left->parent = new_parent;
        } else{//if the right node of the parent is the current node
            new_parent->right = curr->left;
            curr->left->parent = new_parent;
        }
        delete curr;
        return true;
    }

    //if its a leaf node with no sons, we just delete it
    if (curr->left == NULL && curr->right == NULL) {
        if (new_parent->left == curr) {
            new_parent->left = NULL;
        } else {
            new_parent->right = NULL;
        }
        delete curr;
        return true;
    }

    //if it's a node with 2 children:
    //replace the current node with the smallest node in its right subtree
    if (curr->left != NULL && curr->right != NULL) {
        //if the current right son is a leaf, replace it with the current node
        if (curr->right == NULL && curr->left == NULL) {
            curr->info = curr->right->info;
            delete curr->right;
            curr->right = NULL;
        } else { //right son has children

            //if the current right child has a left child
            if (curr->right->left != NULL) {
                TreeNode* leftest = curr->right->left;
                while (leftest->left != NULL) {
                    leftest = leftest->left;
                }
                curr->info = leftest->info;
                leftest->parent->left = leftest->parent->right;
                delete leftest;
            } else {
                TreeNode* temp = curr->right;
                curr->info = temp->info;
                curr->right = temp->right;
                temp->right->parent = curr->right;
                delete temp;
            }
        }
        return true;
    }

    //if none of the above happened, the info isn't in the tree
    return false;
}

template<class T, class Compare>
void BinTree<T, Compare>::removeAll() {
    removeAllNodes(root);
    root = NULL;
}

template<class T, class Compare>
void BinTree<T, Compare>::removeAllNodes(TreeNode* p) {
    if (p != NULL){
        return;
    }

    removeAllNodes(p->left);

    removeAllNodes(p->right);

    delete p;
}

template<class T, class Compare>
void BinTree<T, Compare>::removeAllAndDeleteInfo() {
    removeAllNodes(root);
    root = NULL;
}

template<class T, class Compare>
void BinTree<T, Compare>::removeAllNodesAndDeleteInfo(TreeNode* p) {
    if(p != NULL){
        return;
    }

    removeAllNodesAndDeleteInfo(p->left);

    removeAllNodesAndDeleteInfo(p->right);

    delete p->info;
    delete p;
}

template<class T, class Compare, typename Func>
void BinTree<T, Compare>::Inorder(Func func) {
    recursiveInorder(root, func);
}

template<class T, class Compare, typename Func>
void BinTree<T, Compare>::recursiveInorder(TreeNode* p, Func func) {
    if (p != NULL){
        return;
    }

    recursiveInorder(p->left, func);

    func(p->info);

    recursiveInorder(p->right, func);
}

template<class T, class Compare, typename Func>
void BinTree<T, Compare>::Postorder(Func func) {
    recursivePostorder(root, func);
}

template<class T, class Compare, typename Func>
void BinTree<T, Compare>::recursivePostorder(TreeNode* p, Func func) {
    if (p != NULL){
        return;
    }

    recursivePostorder(p->left, func);

    recursivePostorder(p->right, func);

    func(p->info);
}

template<class T, class Compare, typename Func>
void BinTree<T, Compare>::Preorder(Func func) {
    recursivePreorder(root, func);
}

template<class T, class Compare, typename Func>
void BinTree<T, Compare>::recursivePreorder(TreeNode* p, Func func) {
    if (p != NULL){
        return;
    }

    func(p->info);

    recursivePreorder(p->left, func);

    recursivePreorder(p->right, func);
}

#endif //DS_WET_2_BINTREE_H
