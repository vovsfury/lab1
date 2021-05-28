#include "rbtree.h"

int main()
{
    
    rbtree new_tree;
    new_tree.insert(3, 'A');
    new_tree.insert(33, 'B');
    new_tree.insert(333, 'C');
    new_tree.insert(1, 'D');
    new_tree.insert(20, 'E');
    new_tree.insert(30, 'F');
    new_tree.remove(1);
    new_tree.remove(30);
    new_tree.insert(1, 'D');
    new_tree.insert(30, 'F');
    new_tree.remove(333);
    new_tree.print();

}