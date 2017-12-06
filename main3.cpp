//
// Created by oded on 06/12/17.
//

#include "splayTree.h"

template <class T>
class comp : public Compare<T>{
public:
    int operator()(T& x, T& y) {
        if(x == y){
            return 0;
        }

        return (x < y)? -1: 1;
    }
};


bool test1() {
    comp<int>* co = new comp<int>();
    SplayTree<int> t1 = SplayTree<int>(co);

    int a = 15;
    int b = 13;
    int c = 18;
    int d = 16;


    t1.insert(a);
    t1.insert(b);
    t1.insert(c);
    t1.insert(d);
    /*
    TREE:	 16
            /  \
          15   18
         /
       13
    */
    t1.findMax();
    t1.findMin();
    /*
    TREE:	 13
               \
               18
              /
            15
             \
             16
    */
    int e = 14;
    t1.find(e);
    /*
    TREE:	 15
            /  \
          13   18
               /
             16
    */
    t1.remove(b);
    t1.remove(a);
    t1.remove(d);
    t1.remove(c);
    // EMPTY TREE
    return true;
}

bool test2() {
    comp<int>* co = new comp<int>();
    SplayTree<int> t = SplayTree<int>(co);

    int a = 1;
    int b = 2;
    int c = 7;
    int d = 5;
    int e = 6;
    int f = 4;


    t.insert(a);
    t.insert(b);
    t.insert(c);
    t.insert(d);
    t.insert(e);
    t.insert(f);
/*
TREE:		   4
			  / \
			 2   6
	   	    /	/ \
		   1   5   7
*/
    t.remove(e);
/*
TREE:		   7
			  /
			 4
	   	    / \
		   2   5
		  /
		 1
*/
    t.findMin();
/*
TREE:		   1
			  / \
			 2   7
	   	      \
		       4
			    \
				 5

*/
    return true;
}

int main() {
    test1();
    test2();
    return 0;
}



//int main() {
//	SplayTree<int> s;
//	for (int i = 0; i < 100; i++) {
//		s.insert(i);
//	}
//
//	int* array = s.treeToArray();
//	for (int i = 0; i<s.getTreeSize(); i++) {
//		if (i != array[i])std::cout << "fail "<<i;
//	}
//	delete array;
//
//	int size = s.getTreeSize();
//
//	for (int i = 0; i < size; i++) {
//		s.remove(i);
//		array = s.treeToArray();
//		if (array && (i+1 != array[0]))std::cout << "fail " << i;
//		delete array;
//	}
//
//	int max = 0;
//
//	for (int i = 0; i < 200; i++) {
//		int v1 = rand() % 1000;
//		if (v1 > max)max = v1;
//		try { s.insert(v1, v1); }
//		catch (...) {}
//		array = s.treeToArray();
//		for (int j = 0; j < s.getTreeSize()-1; j++) {
//			if (array[j] > array[j + 1]) std::cout << "fail " << i;
//		}
//		delete array;
//
//	}
//	if (max != *s.findMax())std::cout << "fail ";
//
//
//	SplayTree<int, int, comper> s2 = s;
//	array = s.treeToArray();
//	int* array2 = s2.treeToArray();
//	if(*s.findMax()!=*s2.findMax())std::cout << "fail ";
//	if(s.getTreeSize()!=s2.getTreeSize())std::cout << "fail ";
//	for (int i = 0; i < s.getTreeSize(); i++) {
//		if (array[i] != array2[i])std::cout << "fail ";
//	}
//	delete array2;
//	delete array;
//
//	s = s2;
//	array = s.treeToArray();
//	array2 = s2.treeToArray();
//	if (s.findMax() != s2.findMax())std::cout << "fail ";
//	if (s.getTreeSize() != s2.getTreeSize())std::cout << "fail ";
//	for (int i = 0; i < s.getTreeSize(); i++) {
//		if (array[i] != array2[i])std::cout << "fail ";
//	}
//	delete array2;
//	delete array;
//
//	size = s.getTreeSize();
//	for (int i = 0; i < size; i++) {
//		int *toRemove = s.findMax();
//		if (s.getTreeSize() != (size - i))std::cout << "fail tree Size "<< size - i;
//		s.remove(*toRemove);
//		if ((i < s.getTreeSize() - 1) && (*s.findMax() < *toRemove))std::cout << "fail max in tree\n";
//
//	}
//	if (s.getTreeSize() != 0)std::cout << "fail tree Size 0\n";
//
//
//	for (int i = 0; i <10; i++) {
//		s.insert(i);
//	}
//	for (int i = 0; i <10; i++) {
//		int* data = s.find(i);
//		if (*data != i) std::cout << "fail find fun\n";
//	}
//
//	if (s.find(12)) std::cout << "fail find fun\n";
//	try {
//		s.remove(12);
//	}catch(NotFoundException) {
//		std::cout << "success1\n";
//	}
//
//	try {
//		s.insert(3,3);
//	}
//	catch (KeyAllreadyExist) {
//		std::cout << "success2\n";
//	}
//
//	if (*s.findMin() != 0) std::cout << "fail find fun\n";
//
//	s.clearTree();
//	try {
//		s.remove(12);
//	}
//	catch (TreeIsEmpty) {
//		std::cout << "success3\n";
//	}
//
//
//
//
//}