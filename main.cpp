#include "rbtree.hpp"
#include <iostream>

using namespace RedBlackTree;
using namespace std;

int main() {
  RBTree tree;
  int num;
  while (1) {
    cout << "\n\tÁrvore Red-Black\n" << endl;
    cout << "Escolha uma das operações:" << endl;
    cout << "\t1 - Inserir novo nó na árvore" << endl;
    cout << "\t2 - Remover nó da árvore" << endl;
    cout << "\t3 - Mostrar nó com a maior chave" << endl;
    cout << "\t4 - Mostrar nó com a menor chave" << endl;
    cout << "\t5 - Buscar chave na árvore" << endl;
    cout << "\t6 - Percorrer a árvore" << endl;

    cout << endl << "Digite a opção desejada (0 para sair): ";
    cin >> num;

    if (num == 0) {
      break;
    }

    int key, value;
    NodePtr node;

    switch (num) {
    case 1:
      cout << endl << "Insira a chave: ";
      cin >> key;
      cout << "Insira o valor: ";
      cin >> value;
      tree.insert(key, value);
      break;
    case 2:
      cout << endl << "Insira a chave do nó a ser removido: ";
      cin >> key;
      tree.remove(key);
      break;
    case 3:
      node = tree.max();
      cout << endl << "Chave: " << node->key;
      cout << endl << "Valor: " << node->value;
      cout << endl
           << "Cor: " << (node->color == BLACK ? "BLACK" : "RED") << endl;
      break;
    case 4:
      node = tree.min();
      cout << endl << "Chave: " << node->key;
      cout << endl << "Valor: " << node->value;
      cout << endl
           << "Cor: " << (node->color == BLACK ? "BLACK" : "RED") << endl;
      break;
    case 5:
      cout << endl << "Insira a chave: ";
      cin >> key;
      node = tree.get_node(key);
      if (node != nullptr) {
        cout << endl << "Chave: " << node->key;
        cout << endl << "Valor: " << node->value;
        cout << endl
             << "Cor: " << (node->color == BLACK ? "BLACK" : "RED") << endl;
      } else {
        cout << endl << "Nó não encontrado!" << endl;
      }
      break;
    case 6:
      cout << "\n\nEscolha uma ordem:" << endl;
      cout << "\t1 - Pré-fixada" << endl;
      cout << "\t2 - Central" << endl;
      cout << "\t3 - Pós-fixada" << endl;

      cin >> num;

      switch (num) {
      case 1:
        tree.preorder();
        break;
      case 2:
        tree.inorder();
        break;
      case 3:
        tree.postorder();
        break;
      default:
        break;
      }
      cout << endl;
      break;
    default:
      cout << "Opção inválida!" << endl;
    }
  }
  return 0;
}