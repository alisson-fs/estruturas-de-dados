/// Copyright [2021] <Alisson Fabra da Silva>
#ifndef STRUCTURES_ARRAY_LIST_H
#define STRUCTURES_ARRAY_LIST_H

#include <cstdint>


namespace structures {

template<typename T>
class ArrayList {
 public:
    ArrayList();
    explicit ArrayList(std::size_t max_size);
    ~ArrayList();
    void clear();
    void push_back(const T& data);
    void push_front(const T& data);
    void insert(const T& data, std::size_t index);
    void insert_sorted(const T& data);
    T pop(std::size_t index);
    T pop_back();
    T pop_front();
    void remove(const T& data);
    bool full() const;
    bool empty() const;
    bool contains(const T& data) const;
    std::size_t find(const T& data) const;
    std::size_t size() const;
    std::size_t max_size() const;
    T& at(std::size_t index);
    T& operator[](std::size_t index);
    const T& at(std::size_t index) const;
    const T& operator[](std::size_t index) const;

 private:
    T* contents;
    std::size_t size_;
    std::size_t max_size_;

    static const auto DEFAULT_MAX = 10u;
};

}  // namespace structures

#endif

template<typename T>
structures::ArrayList<T>::ArrayList() {
    max_size_ = DEFAULT_MAX;
    contents = new T[max_size_];
    size_ = -1;
}

template<typename T>
structures::ArrayList<T>::ArrayList(std::size_t max_size) {
    max_size_ = max_size;
    contents = new T[max_size_];
    size_ = -1;
}

template<typename T>
structures::ArrayList<T>::~ArrayList() {
    delete [] contents;
}


template<typename T>
void structures::ArrayList<T>::clear() {
    size_ = -1;
}

template<typename T>
void structures::ArrayList<T>::push_back(const T& data) {
    if (full()) {
        throw std::out_of_range("lista cheia");
    } else {
        size_++;
        contents[size_] = data;
    }
}

template<typename T>
void structures::ArrayList<T>::push_front(const T& data) {
    if (full()) {
        throw std::out_of_range("lista cheia");
    } else {
        size_++;
        std::size_t position = size_;
        while (position > 0) {
            contents[position] = contents[position - 1];
            position--;
        }
        contents[0] = data;
    }
}


template<typename T>
void structures::ArrayList<T>::insert(const T& data, std::size_t index) {
    if (full()) {
        throw std::out_of_range("lista cheia");
    } else {
        if (index > size_ + 1 || index < 0) {
            throw std::out_of_range("posicao invalida");
        }
        size_++;
        std::size_t position = size_;
        while (position > index) {
            contents[position] = contents[position - 1];
            position--;
        }
        contents[index] = data;
    }
}

template<typename T>
void structures::ArrayList<T>::insert_sorted(const T& data) {
    if (full()) {
        throw std::out_of_range("lista cheia");
    } else {
        std::size_t position = 0;
        while (position < size_ + 1 && data > contents[position]) {
            position++;
        }
        insert(data, position);
    }
}

template<typename T>
T structures::ArrayList<T>::pop(std::size_t index) {
    if (index > size_ || index < 0) {
        throw std::out_of_range("posicao invalida");
    } else {
        if (empty()) {
            throw std::out_of_range("lista vazia");
        } else {
            size_--;
            T value = contents[index];
            std::size_t position = index;
            while (position <= size_) {
                contents[position] = contents[position + 1];
                position++;
            }
            return value;
        }
    }
}

template<typename T>
T structures::ArrayList<T>::pop_back() {
    if (empty()) {
        throw std::out_of_range("lista vazia");
    } else {
        size_--;
        return contents[size_ + 1];
    }
}

template<typename T>
T structures::ArrayList<T>::pop_front() {
    if (empty()) {
        throw std::out_of_range("lista vazia");
    } else {
        size_--;
        T value = contents[0];
        std::size_t position = 0;
        while (position < size_ + 1) {
            contents[position] = contents[position + 1];
            position++;
        }
        return value;
    }
}

template<typename T>
void structures::ArrayList<T>::remove(const T& data) {
    if (empty()) {
        throw std::out_of_range("lista vazia");
    } else {
        std::size_t position = find(data);
        if (position < 0) {
            throw std::out_of_range("posicao invalida");
        } else {
            pop(position);
        }
    }
}

template<typename T>
bool structures::ArrayList<T>::full() const {
    return (size_ + 1 == max_size_);
}

template<typename T>
bool structures::ArrayList<T>::empty() const {
    return (size_ + 1 == 0);
}

template<typename T>
bool structures::ArrayList<T>::contains(const T& data) const {
    std::size_t position = 0;
    while (position <= size_) {
        if (contents[position] == data) {
            return true;
        }
        position++;
    }
    return false;
}

template<typename T>
std::size_t structures::ArrayList<T>::find(const T& data) const {
    std::size_t position = 0;
    while (position <= size_ && data != contents[position]) {
        position++;
    }
    return position;
}

template<typename T>
std::size_t structures::ArrayList<T>::size() const {
    return (size_ + 1);
}

template<typename T>
std::size_t structures::ArrayList<T>::max_size() const {
    return max_size_;
}

template<typename T>
T& structures::ArrayList<T>::at(std::size_t index) {
    if (empty()) {
        throw std::out_of_range("lista vazia");
    } else {
        if (index > size_ || index < 0) {
            throw std::out_of_range("posicao invalida");
        } else {
            return contents[index];
        }
    }
}

template<typename T>
T& structures::ArrayList<T>::operator[](std::size_t index) {
    return contents[index];
}

template<typename T>
const T& structures::ArrayList<T>::at(std::size_t index) const {
    if (empty()) {
        throw std::out_of_range("lista vazia");
    } else {
        if (index > size_ || index < 0) {
            throw std::out_of_range("posicao invalida");
        } else {
            return contents[index];
        }
    }
}

template<typename T>
const T& structures::ArrayList<T>::operator[](std::size_t index) const {
    return contents[index];
}
