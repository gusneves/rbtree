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

#include "rbtree.hpp"
#include <assert.h>
#include <cstddef>
#include <iostream>
#include <iterator>
#include <string>

using namespace std;
using namespace RedBlackTree;

/* MÉTODOS AUXILIARES */

NodePtr RBTree::get_node(int key) {
  NodePtr current = root;

  while (current != nullptr && key != current->key) {
    current = key < current->key ? current->left : current->right;
  }

  return current;
}

NodePtr RBTree::min() {
  NodePtr current = root;

  while (current->left != NULL) {
    current = current->left;
  }

  return current;
}

NodePtr RBTree::min(NodePtr node) {
  NodePtr current = node;

  while (current->left != NULL) {
    current = current->left;
  }

  return current;
}

NodePtr RBTree::max() {
  NodePtr current = root;

  while (current->right != NULL) {
    current = current->right;
  }

  return current;
}

NodePtr RBTree::max(NodePtr node) {
  NodePtr current = node;

  while (current->right != NULL) {
    current = current->right;
  }

  return current;
}

/* ------------------------------------------------------------ */

/* ROTAÇÔES */

/*
    Algoritmos de Rotação serão utilizados em outras funções da árvore
    Efetuam a seguinte transformação em uma árvore:

            y         left_rotate(x)          x
          /   \      <---------------       /   \
         x     c     --------------->      a     y
       /  \          right_rotate(y)           /   \
      a    b                                  b     c
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

// Faz o segundo nó tomar o lugar do primeiro
void RBTree::transplant(NodePtr u, NodePtr v) {
  if (u == nullptr) {
    return;
  }

  if (u->parent == nullptr) {
    root = v;
  } else if (u == u->parent->left) {
    u->parent->left = v;
  } else {
    u->parent->right = v;
  }
  if (v != nullptr) {
    v->parent = u->parent;
  }
}

void RBTree::remove(int key) {
  // Busca o nó pela key passada por parâmetro
  NodePtr z = get_node(key);
  if (z == nullptr) {
    return;
  }

  NodePtr x;
  NodePtr p = nullptr;
  Color original_color = z->color;
  /*
    Caso o nó a ser excluído possua apenas um filho, seu filho toma seu lugar.
    Seja um filho à direita ou um filho à esquerda.
  */
  if (z->left == nullptr) {
    x = z->right;
    transplant(z, x);
  } else if (z->right == nullptr) {
    x = z->left;
    transplant(z, x);
  } else {
    /*
      Caso o nó possua os dois filhos, devemos escolher uma das seguintes opções
      para substituir o nó a ser excluído:
        1 - O maior nó da subárvore à esquerda;
        2 - O menor nó da subárvore à direita;

      Neste caso, optamos pela segunda opção e atribuímos este nó ao ponteiro y.
    */
    NodePtr y = min(z->right);
    original_color = y->color;
    // Pegamos também o ponteiro x, que aponta para o nó que entrará no lugar do
    // nó apontado por y
    x = y->right;
    p = y->parent;
    if (y->parent == z) {
      if (x != nullptr) {
        x->parent = y;
      } else {
        p = y;
      }
    } else {
      // Transplantamos y por x
      transplant(y, x);
      y->right = z->right;
      y->right->parent = y;
    }
    // Por fim, transplantamos z por y
    transplant(z, y);
    y->left = z->left;
    y->left->parent = y;
    y->color = z->color;
  }
  delete z;

  /*
    Se a cor original do nó y for vermelha, as propriedades da árvore se
    manterão pelas seguintes razões:
      - Nenhuma black-height foi alterada;
      - Nenhum nó vermelho foi feito adjacente;
      - Como y não não pode ser a raíz se for vermelho, a raíz continua preta.
   */
  if (original_color == BLACK) {
    /*
      Casos de violação das regras:
        1. Se o nó removido for a raíz, e um nó vermelho tomou seu lugar;
        2. Se tanto x quanto seu pai forem vermelhos;
        3. Simplesmente mover o nó y pela árvore, pode resultar em algum caminho
      da árvore contendo um nó preto a menos.
    */
    remove_fixup(x, p); // Passamos o nó pai de x (apontado por p) para
                        // tratarmos o caso em que x é um ponteiro para nulo
  }
}

bool _is_node_black(NodePtr n) { return n == nullptr || n->color == BLACK; }

bool _both_child_black(Node n) {
  return _is_node_black(n.right) && _is_node_black(n.left);
}

void RBTree::remove_fixup(NodePtr node, NodePtr parent) {
  if (node == root) {
    return;
  }
  while (node == nullptr || (node != root && node->color == BLACK)) {
    // Checagem para o caso em que 'node' é enviado como nullptr
    NodePtr p = node == nullptr ? parent : node->parent; // nó pai
    NodePtr s;                                           // nó irmão
    if (node == p->left) {
      s = p->right;
      if (s->color == RED) {
        s->color = BLACK;
        p->color = RED;
        left_rotate(p);
        s = p->right;
      }
      // Checa se ambos os filhos do nó irmão são nós pretos
      if (_both_child_black(*s)) {
        s->color = RED;
        node = p;
      } else {
        if (_is_node_black(s->right)) {
          s->left->color = BLACK;
          s->color = RED;
          right_rotate(s);
          s = p->right;
        }
        s->color = p->color;
        p->color = BLACK;
        s->right->color = BLACK;
        left_rotate(p);
        node = root;
      }
    } else {
      s = p->left;
      if (s->color == RED) {
        s->color = BLACK;
        p->color = RED;
        right_rotate(p);
        s = node->left;
      }
      if (_both_child_black(*s)) {
        s->color = RED;
        node = p;
      } else {
        if (_is_node_black(s->left)) {
          s->right->color = BLACK;
          s->color = RED;
          left_rotate(s);
          s = p->left;
        }
        s->color = p->color;
        p->color = BLACK;
        s->left->color = BLACK;
        right_rotate(p);
        node = root;
      }
    }
  }
  node->color = BLACK;
}

/* ------------------------------------------------------------ */

/* TRAVESSIA DA ÁRVORE - IMPRESSÃO DE VALORES  */

string _getColorAsString(Node x) { return x.color == BLACK ? "BLACK" : "RED"; }

void _preorder(NodePtr x) {
  if (x == nullptr)
    return;
  cout << x->key << "_" << x->value << "_" << _getColorAsString(*x) << endl;
  _preorder(x->left);
  _preorder(x->right);
}

void _inorder(NodePtr x) {
  if (x == nullptr)
    return;
  _inorder(x->left);
  cout << x->key << "_" << x->value << "_" << _getColorAsString(*x) << endl;
  _inorder(x->right);
}

void _postoder(NodePtr x) {
  if (x == nullptr)
    return;
  _inorder(x->left);
  _inorder(x->right);
  cout << x->key << "_" << x->value << "_" << _getColorAsString(*x) << endl;
}

void RBTree::inorder() { _inorder(root); }
void RBTree::preorder() { _preorder(root); }
void RBTree::postorder() { _postoder(root); }

/* ------------------------------------------------------------ */