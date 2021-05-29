// Copyright [2021] <Alisson Fabra da Silva>
#ifndef STRUCTURES_AVL_TREE_H
#define STRUCTURES_AVL_TREE_H

#include <algorithm>
#include "array_list.h"


namespace structures {

/// Arvore AVL
template<typename T>
class AVLTree {
public:
    /// Destrutor.
    ~AVLTree();
    /// Insere o elemento na arvore.
    void insert(const T& data);
    /// Remove o elemento da arvore.
    void remove(const T& data);
    /// Verifica se um elemento está contido na árvore.
    bool contains(const T& data) const;
    /// Verifica se está vazio.
    bool empty() const;
    /// Retorna o numero de elementos da arvore.
    std::size_t size() const;
    /// Retorna a altura da árvore.
    int height() const;
    /// Retorna os elementos na ordem raiz, esquerda e direita.
    ArrayList<T> pre_order() const;
    /// Retorna os elementos na ordem esquerda, raiz e direita.
    ArrayList<T> in_order() const;
    /// Retorna os elementos na ordem esquerda, direita e raiz.
    ArrayList<T> post_order() const;

private:
    struct Node {
        explicit Node(const T& data_) {
            data = data_;
        }

        T data;
        int height_{0};
        Node* left{nullptr};
        Node* right{nullptr};

        int height(Node* N) {
            if (N == NULL) {
                return 0;
            }
            return N->height_;
        }

        Node* simpleLeft(Node *k2) {
            Node *k1 = k2->left;
            k2->left = k1->right;
            k1->right = k2;
            // Atualizar alturas.
            k2->height_ = std::max(height(k2->left), height(k2->right)) + 1;
            k1->height_ = std::max(height(k1->left), height(k1->right)) + 1;
            // Retorna o nodo rodado.
            return k1;
        }

        Node* simpleRight(Node *k2) {
            Node *k1 = k2->right;
            k2->right = k1->left;
            k1->left = k2;
            // Atualizar alturas.
            k2->height_ = std::max(height(k2->left), height(k2->right)) + 1;
            k1->height_ = std::max(height(k1->left), height(k1->right)) + 1;
            // Retorna o nodo rodado.
            return k1;
        }

        Node* doubleLeft(Node* k3) {
            // Roda entre k1 e k2.
            k3->left = simpleRight(k3->left);
            // Roda entre k3 e k2.
            return simpleLeft(k3);
        }

        Node* doubleRight(Node* k3) {
            // Roda entre k1 e k2.
            k3->right = simpleLeft(k3->right);
            // Roda entre k3 e k2.
            return simpleRight(k3);
        }

        int get_balance(Node *node) {
            if (node == NULL) {
                return 0;
            }
            return height(node->left) - height(node->right);
        }

        Node* insert(Node* node, const T &data_) {
            // Cria o nodo e retorna.
            if (node == NULL) {
                Node* node = new Node(data_);
                return node;
            }
            if (data_ < node->data) {
                // Vai à esquerda.
                node->left = insert(node->left, data_);
            }
            else if (data_ > node->data) {
                // Vai à direita.
                node->right = insert(node->right, data_);
            }
            else {
                throw std::out_of_range("Elemento inválido.");
            }
            // Atualiza altura.
            node->height_ = std::max(height(node->left),
                                        height(node->right)) + 1;

            // Pegar fator de balanco.
            int balance = get_balance(node);

            // Casos que necessitam de rotacao.
            // Esquerda-esquerda.
            if (balance > 1 && data_ < node->left->data) {
                return simpleLeft(node);
            }
            // Direita-direita.
            if (balance < -1 && data_ > node->right->data) {
                return simpleRight(node);
            }
            // Esquerda-direita.
            if (balance > 1 && data_ > node->left->data) {
                doubleLeft(node);
            }
            // Direita-esquerda.
            if (balance < -1 && data_ < node->right->data) {
                doubleRight(node);
            }
            // Retorna o nodo sem alteracoes.
            return node;
        }

        Node* remove(const T &data_) {
            Node *node = this;
            if (data_ < node->data) {
                // Vai para esquerda.
                node->left = node->left->remove(data_);
            } else if (data > node->data) {
                // Vai para direita.
                node->right = node->right->remove(data_);
            } else {
                // Esse é o nodo a ser deletado.
                if ((node->left == NULL) || (node->right == NULL)) {
                    // 1 filho.
                    // Verificação de qual filho existe.
                    Node *tmp = node->left ?
                                node->left : node->right;

                    // Se não há nenhum filho.
                    if (tmp == NULL) {
                        tmp = node;
                        node = NULL;
                    } else {
                        *node = *tmp;  // Copia os dados.
                        delete tmp;
                    }
                } else {
                    // 2 filhos.
                    // Recebe o menor da direita.
                    Node *tmp = minimum(node->right);
                    // Copia somente o valor para o nodo atual.
                    node->data = tmp->data;
                    // Deleta o sucessor.
                    node->right = node->right->remove(tmp->data);
                }
            }
            if (node == NULL) {
                return node;
            }
            // Atualizar altura.
            node->height_ = std::max(height(node->left),
                                        height(node->right)) + 1;
            // Verifica se precisa rodar.
            int balance = get_balance(node);
            // EE.
            if (balance > 1 && get_balance(node->left) >= 0) {
                return simpleLeft(node);
            }
            // ED.
            if (balance > 1 && get_balance(node->left) < 0) {
                return doubleLeft(node);
            }
            // DD.
            if (balance < -1 && get_balance(node->right) <= 0) {
                return simpleRight(node);
            }
            // DE.
            if (balance < -1 && get_balance(node->right) > 0) {
                return doubleRight(node);
            }
            return node;
        }

        Node *minimum(Node *node) {
            Node *now = node;
            if (node->left != NULL) return node->minimum(node->left);

            return now;
        }

        bool contains(const T& data_) const {
            if (data_ == data) {
                return true;
            } else if (data_ < data && left != nullptr) {
                return left->contains(data_);
            } else if (data_ > data && right != nullptr) {
                return right->contains(data_);
            } else {
                return false;
            }
        }

        void pre_order(ArrayList<T>& v) const {
            // Raiz.
            v.push_back(data);
            // Esquerda.
            if (left != nullptr) {
                left->pre_order(v);
            }
            // Direita.
            if (right != nullptr) {
                right->pre_order(v);
            }
        }

        void in_order(ArrayList<T>& v) const {
            // Esquerda.
            if (left != nullptr) {
                left->in_order(v);
            }
            // Raiz.
            v.push_back(data);
            // Direita.
            if (right != nullptr) {
                right->in_order(v);
            }
        }

        void post_order(ArrayList<T>& v) const {
            // Esquerda.
            if (left != nullptr) {
                left->post_order(v);
            }
            // Direita.
            if (right != nullptr) {
                right->post_order(v);
            }
            // Raiz.
            v.push_back(data);
        }
    };

    Node* root{nullptr};
    std::size_t size_{0u};
};

}  // namespace structures

#endif

template<typename T>
structures::AVLTree<T>::~AVLTree() {
}

template<typename T>
void structures::AVLTree<T>::insert(const T &data) {
    root = root->insert(root, data);
    size_++;
}

template<typename T>
void structures::AVLTree<T>::remove(const T& data) {
    if (empty()) {
        throw std::out_of_range("Arvore vazia!");
    } else {
        root = root->remove(data);
        size_--;
    }
}

template<typename T>
bool structures::AVLTree<T>::contains(const T& data) const {
    if (root != nullptr) {
        return root->contains(data);
    } else {
        return false;
    }
}

template<typename T>
bool structures::AVLTree<T>::empty() const {
    return size_ == 0 ? true : false;
}

template<typename T>
std::size_t structures::AVLTree<T>::size() const {
    return size_;
}


template<typename T>
int structures::AVLTree<T>::height() const {
    return root->height(root);
}

template<typename T>
structures::ArrayList<T> structures::AVLTree<T>::pre_order() const {
    structures::ArrayList<T> v;
    if (root != nullptr) {
        root->pre_order(v);
    }
    return v;
}

template<typename T>
structures::ArrayList<T> structures::AVLTree<T>::in_order() const {
    structures::ArrayList<T> v;
    if (root != nullptr) {
        root->in_order(v);
    }
    return v;
}

template<typename T>
structures::ArrayList<T> structures::AVLTree<T>::post_order() const {
    structures::ArrayList<T> v;
    if (root != nullptr) {
        root->post_order(v);
    }
    return v;
}
