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

// Cores do nó (BLACK ou RED)
enum Color { BLACK, RED };

struct Node;
class RBTree;

using NodePtr = Node *;

// Definição da estrutura do nó
struct Node {

  // Construtores
  // Um com valores de chave e valor indefinidos e outro com recebimento destes
  // valores
  Node() : color{RED}, left(nullptr), right(nullptr), parent(nullptr) {}
  Node(int k, int v)
      : key(k), value(v), color{RED}, left(nullptr), right(nullptr),
        parent(nullptr) {}

  // Atributos
  int key;        // Chave
  int value;      // Valor
  Color color;    // Cor do nó
  NodePtr left;   // Ponteiro para o filho à esquerda
  NodePtr right;  // Ponteiro para o filho à direita
  NodePtr parent; // Ponteiro para o nó pai
};

// Definição da classe da árvore Red-Black
class RBTree {
  NodePtr root; // Ponteiro de nó privado - raíz da árvore

  // Funções de uso interno
protected:
  // Funções de rotação (à esquerda e à direita)
  void left_rotate(NodePtr x);
  void right_rotate(NodePtr y);

  // Funções de rebalanceamento e garantia de cumprimento de propriedades
  void insert_fixup(NodePtr new_node);
  void remove_fixup(NodePtr x, NodePtr p = nullptr);

  // Função para "transplantar" dois nós
  void transplant(NodePtr u, NodePtr v);

  // Funções públicas
public:
  // Construtor da árvore - inicializa o objeto e atribui um ponteiro para nulo
  // à raíz
  RBTree() : root(nullptr) {}

  // Método de inserção de novo nó
  void insert(int key, int value);

  // Métodos de percorrimento da árvore
  void preorder();
  void inorder();
  void postorder();

  // Método de remoção de nó da árvore
  void remove(int key);

  // Método de busca de nó por chave
  NodePtr get_node(int key);

  // Métodos de busca de chaves máximas e mínimas
  // (de toda a árvore ou de subárvore)
  NodePtr min();
  NodePtr min(NodePtr node);
  NodePtr max();
  NodePtr max(NodePtr node);
};
} // namespace RedBlackTree