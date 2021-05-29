/// Copyright [2021] <Alisson Fabra da Silva>

#ifndef STRUCTURES_ARRAY_LIST_H
#define STRUCTURES_ARRAY_LIST_H

#include <cstdint>
#include <stdexcept>  // C++ exceptions

namespace structures {

/// Lista em vetor
template<typename T>
class ArrayList {
 public:
    /// Contrutor.
    ArrayList();
    /// Construtor com tamanho definido.
    explicit ArrayList(std::size_t max_size);
    /// Destrutor.
    ~ArrayList();

    /// Limpa lista.
    void clear();
    /// Insere no fim.
    void push_back(const T& data);
    /// Insere no inicio.
    void push_front(const T& data);
    /// insere na posição.
    void insert(const T& data, std::size_t index);
    /// Insere em ordem.
    void insert_sorted(const T& data);
    /// Retira da posição.
    T pop(std::size_t index);
    /// Retira do fim.
    T pop_back();
    /// Retira do inicio.
    T pop_front();
    /// Retira especifico.
    void remove(const T& data);
    /// Cheio.
    bool full() const;
    /// Vazio.
    bool empty() const;
    /// Contém.
    bool contains(const T& data) const;
    /// Posição do elemento.
    std::size_t find(const T& data) const;
    /// Tamanho.
    std::size_t size() const;
    /// Tamanho máximo.
    std::size_t max_size() const;
    /// Elemento na posição.
    T& at(std::size_t index);
    /// Elemento na posição.
    T& operator[](std::size_t index);
    /// Elemento na posição.
    const T& at(std::size_t index) const;
    /// Elemento na posição.
    const T& operator[](std::size_t index) const;

 private:
    T* contents;
    std::size_t size_;
    std::size_t max_size_;

    static const auto DEFAULT_MAX = 10u;
};

}  // namespace structures


//-------------------------------------


template<typename T>
structures::ArrayList<T>::ArrayList() {
    structures::ArrayList<T>::ArrayList(DEFAULT_MAX);
}

template<typename T>
structures::ArrayList<T>::ArrayList(std::size_t max_size) {
    max_size_ = max_size;
    contents = new T[max_size_];
    size_ = 0;
}

template<typename T>
structures::ArrayList<T>::~ArrayList() {
    delete []contents;
}

template<typename T>
void structures::ArrayList<T>::clear() {
    size_ = 0;
}

template<typename T>
void structures::ArrayList<T>::push_back(const T& data) {
    insert(data, size());
}

template<typename T>
void structures::ArrayList<T>::push_front(const T& data) {
    insert(data, 0);
}

template<typename T>
void structures::ArrayList<T>::insert(const T& data, std::size_t index) {
    if (full()) {
        throw std::out_of_range("full list");
    } else if (index > size()) {
        throw std::out_of_range("invalid index");
    }
    if (size() > 0) {
        for (std::size_t i = size(); i > index; i--) {
            contents[i] = contents[i-1];
        }
    }
    contents[index] = data;
    size_++;
}

template<typename T>
void structures::ArrayList<T>::insert_sorted(const T& data) {
    if (full()) {
        throw std::out_of_range("full list");
    }
    std::size_t index = 0;
    while (index < size() && contents[index] < data) {
        index++;
    }
    insert(data, index);
}

template<typename T>
T structures::ArrayList<T>::pop(std::size_t index) {
    if (empty()) {
        throw std::out_of_range("empty list");
    } else if (index >= size()) {
        throw std::out_of_range("invalid index");
    }
    T data = contents[index];
    for (std::size_t i = index; i < size()-1; i++) {
        contents[i] = contents[i+1];
    }
    size_--;
    return data;
}

template<typename T>
T structures::ArrayList<T>::pop_back() {
    if (empty()) {
        throw std::out_of_range("empty list");
    }
    return pop(size()-1);
}

template<typename T>
T structures::ArrayList<T>::pop_front() {
    if (empty()) {
        throw std::out_of_range("empty list");
    }
    return pop(0);
}

template<typename T>
void structures::ArrayList<T>::remove(const T& data) {
    if (empty()) {
        throw std::out_of_range("empty list");
    }
    std::size_t index;
    for (index = 0; index < size(); index++) {
        if (contents[index] == data)
            break;
    }
    if (index == size()) {
        throw std::out_of_range("data not found");
    }
    pop(index);
}

template<typename T>
bool structures::ArrayList<T>::empty() const {
    if (size() == 0)
        return true;
    return false;
}

template<typename T>
bool structures::ArrayList<T>::full() const {
    return (size() == max_size());
}

template<typename T>
bool structures::ArrayList<T>::contains(const T& data) const {
    size_t index = find(data);
    return (index < size());
}

template<typename T>
std::size_t structures::ArrayList<T>::find(const T& data) const {
    if (empty()) {
        throw std::out_of_range("empty list");
    }
    std::size_t index;
    for (index = 0; index < size(); index++) {
        if (contents[index] == data)
            return index;
    }
    return size();  // not found
}

template<typename T>
std::size_t structures::ArrayList<T>::size() const {
    return size_;
}

template<typename T>
std::size_t structures::ArrayList<T>::max_size() const {
    return max_size_;
}

template<typename T>
T& structures::ArrayList<T>::at(std::size_t index) {
    if (empty()) {
        throw std::out_of_range("empty list");
    } else if (index >= size()) {
        throw std::out_of_range("invalid index");
    }
    return contents[index];
}

template<typename T>
T& structures::ArrayList<T>::operator[](std::size_t index) {
    return at(index);
}

template<typename T>
const T& structures::ArrayList<T>::at(std::size_t index) const {
    const T aux = at(index);
    return aux;
}

template<typename T>
const T& structures::ArrayList<T>::operator[](std::size_t index) const {
    return at(index);
}

#endif
