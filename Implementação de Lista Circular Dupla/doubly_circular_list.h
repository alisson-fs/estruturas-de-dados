/// Copyright [2021] <Alisson Fabra da Silva>
#ifndef STRUCTURES_DOUBLY_CIRCULAR_LIST_H
#define STRUCTURES_DOUBLY_CIRCULAR_LIST_H

#include <cstdint>


namespace structures {

template<typename T>
class DoublyCircularList {
 public:
    /// Construtor
    DoublyCircularList();
    /// Destrutor
    ~DoublyCircularList();
    /// Limpar lista
    void clear();
    /// Insere no fim
    void push_back(const T& data);
    /// Insere no início
    void push_front(const T& data);
    /// Insere na posição
    void insert(const T& data, std::size_t index);
    /// Insere em ordem
    void insert_sorted(const T& data);
    /// Retira da posição
    T pop(std::size_t index);
    /// Retira do fim
    T pop_back();
    /// Retira do início
    T pop_front();
    /// Retira específico
    void remove(const T& data);
    /// Lista vazia
    bool empty() const;
    /// Contém
    bool contains(const T& data) const;
    /// Acesso a um elemento (checando limites)
    T& at(std::size_t index);
    /// Getter constante a um elemento
    const T& at(std::size_t index) const;
    /// Posição de um dado
    std::size_t find(const T& data) const;
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

        Node(const T& data, Node* prev, Node* next):
            data_{data},
            prev_{prev},
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
        /// Getter: anterior
        Node* prev() {
            return prev_;
        }
        /// Getter const: anterior
        const Node* prev() const {
            return prev_;
        }
        /// Setter: anterior
        void prev(Node* node) {
            prev_ = node;
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
        Node* prev_;
        Node* next_;
    };
    /// Sentinela
    Node* head;
    /// Tamanho
    std::size_t size_;
};

}  // namespace structures

#endif

template<typename T>
structures::DoublyCircularList<T>::DoublyCircularList() {
    head = new Node(0);
    size_ = 0;
}

template<typename T>
structures::DoublyCircularList<T>::~DoublyCircularList() {
    clear();
    delete head;
}

template<typename T>
void structures::DoublyCircularList<T>::clear() {
    while (size_> 0) {
        pop_front();
    }
}

template<typename T>
void structures::DoublyCircularList<T>::push_back(const T& data) {
    insert(data, size_);
}

template<typename T>
void structures::DoublyCircularList<T>::push_front(const T& data) {
    Node *new_value = new Node(data);
    if (new_value == nullptr) {
        throw std::out_of_range("lista cheia");
    } else {
        if (empty()) {
            new_value->next(head);
            head->prev(new_value);
        } else {
            new_value->next(head->next());
        }
        new_value->prev(head);
        head->next(new_value);
        size_++;
    }
}

template<typename T>
void structures::DoublyCircularList<T>::insert(const T& data,
                                               std::size_t index) {
    if (index > size_ || index < 0) {
        throw std::out_of_range("posicao invalida");
    } else if (index == 0) {
        push_front(data);
    } else {
        Node *new_value = new Node(data);
        if (new_value == nullptr) {
            throw std::out_of_range("lista cheia");
        } else {
            Node *previous = head->next();
            for (std::size_t i = 0; i < index - 1; i++) {
                previous = previous->next();
            }
            new_value->next(previous->next());
            new_value->next()->prev(new_value);
            previous->next(new_value);
            new_value->prev(previous);
            size_++;
        }
    }
}

template<typename T>
void structures::DoublyCircularList<T>::insert_sorted(const T& data) {
    if (empty()) {
        push_front(data);
    } else {
        Node *current = head->next();
        std::size_t position = 0;
        while (current->next() != head && data > current->data()) {
            current = current->next();
            position++;
        }
        if (data > current->data()) {
            insert(data, position + 1);
        } else {
            insert(data, position);
        }
    }
}

template<typename T>
T structures::DoublyCircularList<T>::pop(std::size_t index) {
    if (index >= size_ || index < 0) {
        throw std::out_of_range("posicao invalida");
    } else if (index == 0) {
        return pop_front();
    } else {
        Node *previous = head->next();
        for (std::size_t i = 0; i < index - 1; i++) {
            previous = previous->next();
        }
        Node *eliminate = previous->next();
        T info_back = eliminate->data();
        previous->next(eliminate->next());
        eliminate->next()->prev(previous);
        size_--;
        delete eliminate;
        return info_back;
    }
}

template<typename T>
T structures::DoublyCircularList<T>::pop_back() {
    return pop(size_ - 1);
}

template<typename T>
T structures::DoublyCircularList<T>::pop_front() {
    if (empty()) {
        throw std::out_of_range("lista vazia");
    } else {
        Node *eliminate = head->next();
        T info_back = eliminate->data();
        head->next(eliminate->next());
        eliminate->next()->prev(head);
        size_--;
        delete eliminate;
        return info_back;
    }
}

template<typename T>
void structures::DoublyCircularList<T>::remove(const T& data) {
    pop(find(data));
}

template<typename T>
bool structures::DoublyCircularList<T>::empty() const {
    return (size_ == 0);
}

template<typename T>
bool structures::DoublyCircularList<T>::contains(const T& data) const {
    return (find(data) != size_);
}

template<typename T>
T& structures::DoublyCircularList<T>::at(std::size_t index) {
    if (empty()) {
        throw std::out_of_range("lista vazia");
    } else if (index > size_ || index < 0) {
        throw std::out_of_range("posicao invalida");
    } else {
        Node *current = head->next();
        for (std::size_t i = 0; i < index; i++) {
            current = current->next();
        }
        return current->data();
    }
}

template<typename T>
const T& structures::DoublyCircularList<T>::at(std::size_t index) const {
    if (empty()) {
        throw std::out_of_range("lista vazia");
    } else if (index > size_ || index < 0) {
        throw std::out_of_range("posicao invalida");
    } else {
        Node *current = head->next();
        for (std::size_t i = 0; i < index; i++) {
            current = current->next();
        }
        return current->data();
    }
}

template<typename T>
std::size_t structures::DoublyCircularList<T>::find(const T& data) const {
    Node* current = head->next();
    for (std::size_t i = 0; i < size_; i++) {
        if (data == current->data()) {
            return i;
        }
        current = current->next();
    }
    return size_;
}

template<typename T>
std::size_t structures::DoublyCircularList<T>::size() const {
    return size_;
}
