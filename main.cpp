#include "rbtree.h"
#include <iostream>

using namespace RedBlackTree;
using namespace std;

int main() {
  RBTree tree;
  tree.insert(30, 300);
  tree.insert(10, 100);
  tree.insert(70, 700);
  tree.insert(50, 500);
  tree.insert(40, 400);
  tree.insert(60, 600);
  tree.insert(20, 200);
  tree.insert(100, 1000);
  tree.insert(99, 990);
  tree.insert(95, 950);

  tree.preorder();

  tree.remove(10);

  tree.preorder();
  return 0;
}