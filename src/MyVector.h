#ifndef MYVECTOR_MYVECTOR_H
#define MYVECTOR_MYVECTOR_H

#include <iostream>
#include <stdexcept>

template <typename T>
class MyVector {
private:
    T* data;
    size_t size;
    size_t capacity;

public:
    MyVector() : data(nullptr), size(0), capacity(0) {}

    explicit MyVector(size_t initial_capacity) : data(new T[initial_capacity]), size(0), capacity(initial_capacity) {}

    MyVector(size_t initial_capacity, std::nothrow_t) noexcept : data(new (std::nothrow) T[initial_capacity]), size(0), capacity(initial_capacity) {}

    MyVector(const MyVector& other) : data(new T[other.capacity]), size(other.size), capacity(other.capacity) {
        std::copy(other.data, other.data + other.size, data);
    }

    bool is_data_null() const {
        return data == nullptr;
    }

    MyVector& operator=(const MyVector& other) {
        if (this != &other) {
            delete[] data;
            data = new T[other.capacity];
            size = other.size;
            capacity = other.capacity;
            std::copy(other.data, other.data + other.size, data);
        }
        return *this;
    }

    T& operator[](size_t index) {
        if (data == nullptr) {
            throw std::runtime_error("Vector data is null");
        }
        if (index < size) {
            return data[index];
        } else {
            throw std::out_of_range("Vector index out of range");
        }
    }

    MyVector operator+(const MyVector& other) {
        if (data == nullptr || other.data == nullptr) {
            throw std::runtime_error("Vector data is null");
        }
        MyVector result(capacity + other.capacity);
        std::copy(data, data + size, result.data);
        std::copy(other.data, other.data + other.size, result.data + size);
        result.size = size + other.size;
        return result;
    }

    ~MyVector() {
        delete[] data;
    }

    void push_back(const T& item) {
        if (size >= capacity) {
            capacity = (capacity == 0) ? 1 : capacity * 2;
            T* new_data = new T[capacity];
            if (data != nullptr) {
                std::copy(data, data + size, new_data);
                delete[] data;
            }
            data = new_data;
        }
        data[size++] = item;
    }

    bool resize(size_t new_capacity, std::nothrow_t) noexcept {
        T* new_data = new (std::nothrow) T[new_capacity];
        if (new_data == nullptr) {
            return false;
        }
        size_t new_size = (new_capacity < size) ? new_capacity : size;
        std::copy(data, data + new_size, new_data);
        delete[] data;
        data = new_data;
        size = new_size;
        capacity = new_capacity;
        return true;
    }

    size_t get_size() const {
        return size;
    }
};

#endif //MYVECTOR_MYVECTOR_H