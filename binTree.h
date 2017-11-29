//
// Created by oded on 29/11/17.
//

#ifndef DS_WET_2_BINTREE_H
#define DS_WET_2_BINTREE_H

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

template <class T, typename Compare>
class BinTree{

private:
    T& info;
    BinTree& parent;
    BinTree& left;
    BinTree& right;
    Compare comp;
public:
    //normal constructor
    BinTree(T& i, BinTree& p, BinTree& l, BinTree& r, Compare c):
            info(i), parent(p), left(l), right(r), comp(c) {}
    //constructor without comparison function object
    BinTree(T& i, BinTree& p, BinTree& l, BinTree& r):
            info(i), parent(p), left(l), right(r), comp(DefComp()) {}
    //default destructor
    ~BinTree();

    //find node with relevant info. returns NULL if there is none
    BinTree& find(T& info);

    //insert node with relevant info. returns NULL if there it already exists
    BinTree& insert(T& info);

    //removes the node with relevant info. returns false if it doesn't exist, true otherwise.
    bool remove(T& info);
};

template <class T, typename Compare>
BinTree& BinTree::find(T& info){
    //if this is the tree
    if(comp(info, this->info) == 0){
        return *this;
    }

    //if the info is less, go left if possible
    if(comp(info, this->info) < 0 && left != NULL){
        return left.find(info);
    }

    //if the info is greater, go right if possible
    if(comp(info, this->info) > 0 && right != NULL){
        return right.find(info);
    }

    //if none of the above happened, the info isn't in the tree
    return NULL;
}

template <class T, typename Compare>
BinTree& BinTree::insert(T& info){
    //if tree has no nodes, return a new tree
    if(*this == NULL)
        return BinTree(info, *this, NULL, NULL, comp);

    //if the info is less, go left if needed
    if(comp(info, this->info) < 0){
        if(left != NULL){
            return left.insert(info);
        } else {
            left = BinTree(info, *this, NULL, NULL, comp);
        }
    }

    //if the info is more, go right if needed
    if(comp(info, this->info) > 0){
        if(right != NULL){
            return right.insert(info);
        } else {
            right = BinTree(info, *this, NULL, NULL, comp);
        }
    }

    //if none of the above happened, the info isn't in the tree
    return NULL;
}

template <class T, typename Compare>
bool BinTree::remove(T& info){
    //if the info is less, go left if needed
    if(comp(info, this->info) <0 && left != NULL){
        return left.remove(info);
    }

    //if the info is less, go left if needed
    if(comp(info, this->info) > 0 && right != NULL){
        return right.remove(info);
    }

    //if this is the tree
    if(comp(info, this->info) == 0){
        //if there is only right son
        if(left == NULL && right != NULL){
            //if the left node of the parent is the current node
            if(comp(info, parent->left->info) == 0) {
                parent.left = right;
            } else {
                parent.right = right;
            }
            ~BinTree();
            return true;
        }

        //if there is only a left son
        if(left != NULL && right == NULL){
            //if the left node of the parent is the current node
            if(comp(info, parent->left->info) == 0) {
                parent.left = left;
            } else {
                parent.right = left;
            }
            ~BinTree();
            return true;
        }

        //if its a lead node with no sons, we just delete it
        if(left == NULL && right == NULL) {
            //if the left node of the parent is the current node
            if(comp(info, parent->left->info) == 0) {
                parent.left = NULL;
            } else {
                parent.right = NULL;
            }
            ~BinTree();
            return true;
        }

        //its a node with 2 children:
        //replace the current node with the smallest node in its right subtree
        if(left != NULL && right != NULL){
            //if the current right son is a leaf, replace it with the current node
            if(right.right == NULL && right.left == NULL) {
                *this->info=right.info;
                right.~BinTree();
                right = NULL;
            } else { //right son has children
                if(*this.right.left != NULL) {
                    BinTree& leftest =*this.right.left;
                    while(leftest.left!=NULL){
                        leftest = leftest.left;
                    }
                    *this.info = leftest.info;
                    leftest.parent.left = NULLL;
                    ~leftest;
                } else {

                }
            }

        }

    }

    //if none of the above happened, the info isn't in the tree
    return false;
}


template <class T, typename Compare>

template <class T, typename Compare>

template <class T, typename Compare>

template <class T, typename Compare>

#endif //DS_WET_2_BINTREE_H
