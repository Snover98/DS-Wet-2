//
// Created by Assaf-Haik-Barouch on 05/12/2017.
//

#ifndef DS_WET_2_TREENODE_H
#define DS_WET_2_TREENODE_H

#include <clocale>

//node struct
template<class T>
struct TreeNode {
public:
    TreeNode* parent;
    TreeNode* left;
    TreeNode* right;
    T& info;
    TreeNode(T& t): parent(NULL), left(NULL), right(NULL), info(t){}
    ~TreeNode(){
        parent = NULL;
        left = NULL;
        right = NULL;
    }
};





#endif //DS_WET_2_TREENODE_H
