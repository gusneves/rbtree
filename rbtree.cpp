/*
    REGRAS DA ESTRUTURA

    1. Cada nó é da cor preta ou vermelha, nunca ambas;
    2. A raiz da árvore é da cor preta;
    3. Cada nó folha é da cor preta;
    4. Se um nó é da cor vermelha, então seus dois filhos são da cor
       preta;
    5. Para cada nó, todos os caminhos simples do nó até suas folhas
       descendentes contêm o mesmo número de nós da cor preta.
*/

#include "rbtree.h"
#include <iostream>
#include <iterator>

using namespace std;
using namespace RedBlackTree;

/* MÉTODOS AUXILIARES */

NodePtr RBTree::get_node(int key) {
  NodePtr current = root;

  while (current != NULL && key != current->key) {
    current = key < current->key ? current->left : current->right;
  }

  return current;
}

NodePtr RBTree::min(NodePtr node) {
  NodePtr current = node == nullptr ? root : node;

  while (current->left != NULL) {
    current = current->left;
  }

  return current;
}

NodePtr RBTree::max(NodePtr node) {
  NodePtr current = node == nullptr ? root : node;

  while (current->right != NULL) {
    current = current->right;
  }

  return current;
}

/* ------------------------------------------------------------ */

/* ROTAÇÔES */

/*
    Algoritmos de Rotação serão utilizados em outras funções da árvore

            y         left_rotate          x
          /   \      <------------       /   \
         x     c     ------------>      a     y
       /  \          right_rotate           /   \
      a    b                               b     c
 */

void RBTree::left_rotate(NodePtr x) {
  // verifica se o nó passado possui filho à direita, e, caso não possua,
  // encerra a função
  if (x->right == nullptr) {
    return;
  }

  NodePtr y = x->right; // copia o valor do filho à direita
  x->right = y->left; // transforma subárvore à esquerda de y na subárvore à
                      // direita de x

  if (y->left != nullptr) {
    y->left->parent = x;
  }

  y->parent = x->parent; // liga o pai de x a y

  if (x->parent == nullptr) {
    root = y;
  } else if (x == x->parent->left) {
    x->parent->left = y;
  } else {
    x->parent->right = y;
  }

  y->left = x; // posiciona x à esquerda de y
  x->parent = y;
}

void RBTree::right_rotate(NodePtr x) {
  if (x->left == nullptr) {
    return;
  }

  NodePtr y = x->left;
  x->left = y->right;

  if (y->right != nullptr) {
    y->right->parent = x;
  }

  y->parent = x->parent;

  if (x->parent == nullptr) {
    root = y;
  } else if (x == x->parent->right) {
    x->parent->right = y;
  } else {
    x->parent->left = y;
  }

  y->right = x;
  x->parent = y;
}

/* ------------------------------------------------------------ */

/* INSERÇÃO */

void RBTree::insert(int key, int value) {
  NodePtr new_node =
      new Node(key, value); // cria novo nó e atribui os valores-padrão

  NodePtr y = nullptr; // Cria nó auxiliar

  NodePtr x = root; // Referencia a raíz da árvore

  // Percorre a árvore até encontrar a posição adequada para o novo nó
  // (de acordo com o valor da key)
  while (x != nullptr) {
    y = x;
    x = new_node->key < x->key ? x->left : x->right;
  }

  new_node->parent = y; // atribui o nó auxiliar como pai do novo nó

  // posiciona o novo nó à esquerda ou direita do nó pai, ou como raíz da
  // árvore, caso esta esteja vazia
  if (y == x) {
    root = new_node;
  } else if (new_node->key < y->key) {
    y->left = new_node;
  } else {
    y->right = new_node;
  }
  // chama a função responsável pelo rebalanceamento da árvore e garantia do
  // cumprimento das regras da estrutura
  insert_fixup(new_node);
}

void RBTree::insert_fixup(NodePtr new_node) {
  while (new_node->parent != nullptr && new_node->parent->color == RED) {
    NodePtr grandparent = new_node->parent->parent;
    /* Pai é um filho à esquerda do Avô */
    if (new_node->parent == grandparent->left) {
      NodePtr uncle = grandparent->right;
      /*
        CASO 1:
        O nó "Tio" também é vermelho - apenas recolorir
      */
      if (uncle != nullptr && uncle->color == RED) {
        new_node->parent->color = uncle->color = BLACK; // caso 1
        grandparent->color = RED;                       // caso 1
        new_node = grandparent;                         // caso 1
      } else {
        /*
          CASO 2:
          Novo nó é filho direito - rotação esquerda necessária
        */
        if (new_node == new_node->parent->right) {
          new_node = new_node->parent; // caso 2
          left_rotate(new_node);       // caso 2
        }
        /*
          CASO 3:
          Novo nó é filho esquerdo - rotação direita necessária
        */
        new_node->parent->color = BLACK; // caso 3
        grandparent->color = RED;        // caso 3
        right_rotate(grandparent);       // caso 3
      }
    } else {
      NodePtr uncle = grandparent->left;
      if (uncle != nullptr && uncle->color == RED) {
        new_node->parent->color = uncle->color = BLACK;
        grandparent->color = RED;
        new_node = grandparent;
      } else {
        if (new_node == new_node->parent->left) {
          new_node = new_node->parent;
          right_rotate(new_node);
        } else {
          new_node->parent->color = BLACK;
          grandparent->color = RED;
          left_rotate(grandparent);
        }
      }
    }
  }
  root->color = BLACK;
}

/* ------------------------------------------------------------ */

/* REMOÇÃO */

void RBTree::transplant(NodePtr u, NodePtr v) {
  if (u == nullptr || v == nullptr) {
    return;
  }

  if (u->parent == nullptr) {
    root = v;
  } else if (u == u->parent->left) {
    u->parent->left = v;
  } else {
    u->parent->right = v;
  }

  v->parent = u->parent;
}

void RBTree::remove(int key) {
  NodePtr z, y = get_node(key);
  if (z == nullptr) {
    return;
  }
  Color original_color = y->color;
}

void RBTree::remove_fixup(NodePtr node) {}

/* ------------------------------------------------------------ */

/* TRAVESSIA DA ÁRVORE - IMPRESSÃO DE VALORES  */

void _preorder(NodePtr x) {
  if (x == nullptr)
    return;
  cout << x->key << "_" << x->color << endl;
  _preorder(x->left);
  _preorder(x->right);
}

void _inorder(NodePtr x) {
  if (x == nullptr)
    return;
  _inorder(x->left);
  cout << x->key << "_" << x->color << endl;
  _inorder(x->right);
}

void _postoder(NodePtr x) {
  if (x == nullptr)
    return;
  _inorder(x->left);
  _inorder(x->right);
  cout << x->key << "_" << x->color << endl;
}

void RBTree::inorder() { _inorder(root); }
void RBTree::preorder() { _preorder(root); }
void RBTree::postorder() { _postoder(root); }

/* ------------------------------------------------------------ */