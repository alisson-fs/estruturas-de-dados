/// Copyright [2021] <Alisson Fabra da Silva>
#ifndef STRUCTURES_LINKED_QUEUE_H
#define STRUCTURES_LINKED_QUEUE_H

#include <cstdint>

namespace structures {

/// Classe fila encadeada
template<typename T>
class LinkedQueue {
 public:
    /// Construtor padrão
    LinkedQueue();
    /// Destrutor
    ~LinkedQueue();
    /// Limpar
    void clear();
    /// Enfilerar
    void enqueue(const T& data);
    /// Desenfilerar
    T dequeue();
    /// Primeiro dado
    T& front() const;
    /// Último dado
    T& back() const;
    /// Fila vazia
    bool empty() const;
    /// Tamanho
    std::size_t size() const;

 private:
    /// Elemento
    class Node {
     public:
        explicit Node(const T& data):
            data_{data}
        {}
        Node(const T& data, Node* next):
            data_{data},
            next_{next}
        {}
        /// Getter: dado
        T& data() {
            return data_;
        }
        /// Getter const: dado
        const T& data() const {
            return data_;
        }
        /// Getter: próximo
        Node* next() {
            return next_;
        }
        /// Getter const: próximo
        const Node* next() const {
            return next_;
        }
        /// Setter: próximo
        void next(Node* node) {
            next_ = node;
        }

     private:
        T data_;
        Node* next_{nullptr};
    };
    /// Nodo-cabeça
    Node* head;
    /// Nodo-fim
    Node* tail;
    /// Tamanho
    std::size_t size_;
};

}  // namespace structures

#endif

template<typename T>
structures::LinkedQueue<T>::LinkedQueue() {
    head = nullptr;
    tail = nullptr;
    size_ = 0;
}

template<typename T>
structures::LinkedQueue<T>::~LinkedQueue() {
    clear();
}

template<typename T>
void structures::LinkedQueue<T>::clear() {
    while (size_ > 0) {
        dequeue();
    }
}

template<typename T>
void structures::LinkedQueue<T>::enqueue(const T& data) {
    Node *new_value = new Node(data, tail);
    if (new_value == nullptr) {
        throw std::out_of_range("fila cheia");
    }
    if (empty()) {
        head = new_value;
    } else {
        tail->next(new_value);
    }
    tail = new_value;
    size_++;
}

template<typename T>
T structures::LinkedQueue<T>::dequeue() {
    if (empty()) {
        throw std::out_of_range("fila vazia");
    } else {
        Node *eliminate = head;
        T info_back = eliminate->data();
        head = eliminate->next();
        size_--;
        delete eliminate;
        return info_back;
    }
}

template<typename T>
T& structures::LinkedQueue<T>::front() const {
    if (empty()) {
        throw std::out_of_range("fila vazia");
    } else {
        return head->data();
    }
}

template<typename T>
T& structures::LinkedQueue<T>::back() const {
    if (empty()) {
        throw std::out_of_range("fila vazia");
    } else {
        return tail->data();
    }
}

template<typename T>
bool structures::LinkedQueue<T>::empty() const {
    return (size_ == 0);
}

template<typename T>
std::size_t structures::LinkedQueue<T>::size() const {
    return size_;
}
