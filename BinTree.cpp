//
// Created by Assaf-Haik-Barouch on 26/11/2017.
//

template <class T>
class BinNode{
    private:
    T& info;
    BinNode* right_son;
    BinNode* left_son;
    BinNode* parent;

    public:
    BinNode(T& i = NULL):info(i){}

    T& getInfo(){ return info;}
    BinNode* getRightSon(){ return right_son;}
    BinNode* getLeftSon(){ return left_son;}
    BinNode* getParent(){ return parent;}

    void setInfo(T& i){info = i;}
    void setRightSon(BinNode* r){right_son = r;}
    void setLeftSon(BinNode* l){left_son = l;}
    void setParent(BinNode* p){parent = p;}

    friend BinTree;
};



template <class T>
class BinTree{






};