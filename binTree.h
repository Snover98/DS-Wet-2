#ifndef DS_WET_2_BINTREE_H
#define DS_WET_2_BINTREE_H

using namespace std;

template<class T, class Compare>
class BinTree {
protected:
    //node struct
    struct TreeNode {
        TreeNode* parent;
        TreeNode* left;
        TreeNode* right;
        T& info;
    };
    //tree root
    TreeNode* root;

    /* * * * * * * * * * * * *\
    |* CLASS INNER FUNCTIONS *|
    \* * * * * * * * * * * * */
    //switch the info of two nodes
    void switchNodes(TreeNode* t1, TreeNode* t2);

    //find the node with the inputted info. returns the closest node if the info is not in the tree
    TreeNode* findNode(T& info, TreeNode* start);

    //find the maximal node of the sub-tree start
    TreeNode* findMaxNode(TreeNode* start);

    //find the minimal node of the sub-tree start
    TreeNode* findMinNode(TreeNode* start);

    //insert a node into the sub-tree 'start'
    TreeNode* insertNode(TreeNode* t, TreeNode* start);
    //insert info into the tree and return it's node
    TreeNode* insertInfo(T& info);

    //remove a node
    void removeNode(TreeNode* t);
    
    //removing all nodes + deleting all inner info
    void removeAllNodesAndDeleteInfo(TreeNode* p);

    //removing all nodes without deleting the info inside the nodes
    void removeAllNodes(TreeNode* p);

    //the recursive functions that run a function recursively in a certain order (regarding all the orders)
    template <typename Func>
    void recursiveInorder(TreeNode* p, Func& func);

    template <typename Func>
    void recursivePreorder(TreeNode* p, Func& func);

    template <typename Func>
    void recursivePostorder(TreeNode* p, Func& func);

    template <typename Func>
    void recursiveInverseOrder(TreeNode* p, Func& func);
    
    //comparsion function between the nodes in the search tree
    int comp(T& t1, T& t2);

public:
    //normal constructor
    BinTree() : root(NULL) {}

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
    bool remove(T& info);

    //remove all nodes from binary tree
    void removeAll();

    //remove all nodes from binary tree and deletes  the info too (assuming the
    // info was allocated using 'new' - we delete the info using 'delete'
    void removeAllAndDeleteInfo();


    //different orders to run a function on the tree's nodes
    template <typename Func>
    void Inorder(Func& func);

    template <typename Func>
    void Preorder(Func& func);

    template <typename Func>
    void Postorder(Func& func);

    template <typename Func>
    void InverseOrder(Func& func);
};

template<class T, class Compare>
BinTree<T, Compare>::~BinTree(){
    removeAll();
};

template<class T, class Compare>
int BinTree<T, Compare>::comp(T& t1, T& t2){
    return Compare::operator()(t1, t2);
};

template<class T, class Compare>
T* BinTree<T, Compare>::find(T& info) {
    //check if the tree is empty
    if(isEmpty()){
        return NULL;
    }

    //search for a node with the info
    TreeNode* found = findNode(info, root);

    if(comp(found->info, info) == 0){//if the found node was the correct one
        return &(found->info);
    }

    //otherwise, there is no node with the info
    return NULL;
}

template<class T, class Compare>
T* BinTree<T, Compare>::findMax() {
    //check if the tree is empty
    if(isEmpty()){
        return NULL;
    }
    return &(findMaxNode(root)->info);
}

template<class T, class Compare>
T* BinTree<T, Compare>::findMin() {
    //check if the tree is empty
    if(isEmpty()){
        return NULL;
    }
    return &(findMinNode(root)->info);
}

template<class T, class Compare>
void BinTree<T, Compare>::insert(T& info) {
    //use the inner function
    insertInfo(info);
}

template<class T, class Compare>
bool BinTree<T, Compare>::remove(T& info) {
    //the info cannot be in the tree if it's empty
    if(isEmpty()) {
        return false;
    }

    //find the node
    TreeNode* t = findNode(info, root);

    //if the info is not in the tree
    if(comp(info, t->info) != 0){
        return false;
    }

    //remove t
    removeNode(t);
    return true;
}

template<class T, class Compare>
void BinTree<T, Compare>::removeAll() {
    removeAllNodes(root);
    root = NULL;
}

template<class T, class Compare>
void BinTree<T, Compare>::removeAllNodes(TreeNode* p) {
    if (p == NULL){
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
    if(p == NULL){
        return;
    }

    removeAllNodesAndDeleteInfo(p->left);

    removeAllNodesAndDeleteInfo(p->right);

    delete p->info;
    delete p;
}

template<class T, class Compare, typename Func>
void BinTree<T, Compare>::Inorder(Func& func) {
    recursiveInorder(root, func);
}

template<class T, class Compare, typename Func>
void BinTree<T, Compare>::recursiveInorder(TreeNode* p, Func& func) {
    if (p == NULL){
        return;
    }

    recursiveInorder(p->left, func);

    func(p->info);

    recursiveInorder(p->right, func);
}

template<class T, class Compare, typename Func>
void BinTree<T, Compare>::Postorder(Func& func) {
    recursivePostorder(root, func);
}

template<class T, class Compare, typename Func>
void BinTree<T, Compare>::recursivePostorder(TreeNode* p, Func& func) {
    if (p == NULL){
        return;
    }

    recursivePostorder(p->left, func);

    recursivePostorder(p->right, func);

    func(p->info);
}

template<class T, class Compare, typename Func>
void BinTree<T, Compare>::Preorder(Func& func) {
    recursivePreorder(root, func);
}

template<class T, class Compare, typename Func>
void BinTree<T, Compare>::recursivePreorder(TreeNode* p, Func& func) {
    if (p == NULL){
        return;
    }

    func(p->info);

    recursivePreorder(p->left, func);

    recursivePreorder(p->right, func);
}

template<class T, class Compare, typename Func>
void BinTree<T, Compare>::InverseOrder(Func& func){
    recursiveInverseOrder(root, func);
}

template<class T, class Compare, typename Func>
void BinTree<T, Compare>::recursiveInverseOrder(TreeNode* p, Func& func) {
    if (p == NULL){
        return;
    }

    recursiveInverseOrder(p->right, func);

    func(p->info);

    recursiveInverseOrder(p->left, func);
}

template<class T, class Compare>
void BinTree<T, Compare>::switchNodes(TreeNode *t1, TreeNode *t2) {
    T& old_t1_info = t1->info;
    t1->info = t2->info;
    t2->info = old_t1_info;
}

template<class T, class Compare>
BinTree<T, Compare>::TreeNode* BinTree<T, Compare>::findNode(T &info, TreeNode *start){
    TreeNode* curr = start;

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

template<class T, class Compare>
BinTree<T, Compare>::TreeNode* BinTree<T, Compare>::findMaxNode(TreeNode *start){
    if(isEmpty()){
        return NULL;
    }

    TreeNode* curr = start;

    while (curr->right != NULL) {
        curr = curr->right;
    }
    return curr;
}

template<class T, class Compare>
BinTree<T, Compare>::TreeNode* BinTree<T, Compare>::findMinNode(TreeNode *start){
    if(isEmpty()){
        return NULL;
    }

    TreeNode* curr = start;

    while (curr->left != NULL) {
        curr = curr->left;
    }
    return curr;
}

template<class T, class Compare>
BinTree<T, Compare>::TreeNode* BinTree<T, Compare>::insertNode(TreeNode *t, TreeNode *start){
    //find the closest node
    TreeNode* closest = findNode(t->info, start);

    //if the there is no node with the same info
    if(comp(t->info, closest->info) != 0){
        if(closest->left == NULL){  //if it should be to the left of the closest
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
            return insertNode(t, closest->right);
        }
    }

    //return the node
    return t;
}

template<class T, class Compare>
BinTree<T, Compare>::TreeNode* BinTree<T, Compare>::insertInfo(T &info){
    //create the node
    TreeNode* t = new TreeNode;
    t->info = info;
    t->left = NULL;
    t->right = NULL;
    t->parent = NULL;

    //If this is an empty tree
    if(isEmpty()) {
        root = t;
        return t;
    }

    return insertNode(t, root);
}

template<class T, class Compare>
void BinTree<T, Compare>::removeNode(TreeNode *t){
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
        TreeNode *child = (t->left != NULL) ? t->left : t->right;

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
    TreeNode* t_follower = findMinNode(t->right);
    //switch between them
    switchNodes(t, t_follower);

    //now t_follower points to t's original info, so we'll just delete it instead
    removeNode(t_follower);
}





#endif //DS_WET_2_BINTREE_H
