/*
 *    INF - UFG
 *    ALGORITMOS E ESTRUTURA DE DAODS 2
 *
 *    IMPLEMENTAÇÃO DE ÁRVORE BINÁRIA RED-BLACK
 *
 *    INTEGRANTES DO GRUPO:
 *    - Daniel SOares de Jesus
 *    - Gustavo Neves Piedade Louzada
 *    - Marcos Vinícius da Rocha
 */

#pragma once

namespace RedBlackTree {

enum Color { BLACK, RED };

struct Node;
class RBTree;

using NodePtr = Node *;

struct Node {
  Node() : color{RED}, left(nullptr), right(nullptr), parent(nullptr) {}
  Node(int k, int v)
      : key(k), value(v), color{RED}, left(nullptr), right(nullptr),
        parent(nullptr) {}
  int key;
  int value;
  Color color;
  NodePtr left;
  NodePtr right;
  NodePtr parent;
};

class RBTree {
  NodePtr root;

protected:
  void left_rotate(NodePtr x);
  void right_rotate(NodePtr y);
  void insert_fixup(NodePtr new_node);
  void transplant(NodePtr u, NodePtr v);
  void remove_fixup(NodePtr x);

public:
  RBTree() : root(nullptr) {}
  void insert(int key, int value);
  void preorder();
  void inorder();
  void postorder();
  void remove(int key);
  NodePtr get_node(int key);
  NodePtr min(NodePtr node = nullptr);
  NodePtr max(NodePtr node = nullptr);
};
} // namespace RedBlackTree