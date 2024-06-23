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

    ~MyVector() {
        delete[] data;
    }

    // Operator overloads
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

    // Methods
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

    bool is_data_null() const {
        return data == nullptr;
    }

    // Iterator
    class iterator {
    private:
        T* ptr;
        T* begin_ptr;
        T* end_ptr;

    public:
        iterator(T* p, T* begin, T* end) : ptr(p), begin_ptr(begin), end_ptr(end) {}

        iterator& operator++() {
            if (ptr >= end_ptr) throw std::out_of_range("Iterator out of range");
            ++ptr;
            return *this;
        }

        iterator operator++(int) {
            iterator temp = *this;
            if (ptr >= end_ptr) throw std::out_of_range("Iterator out of range");
            ++ptr;
            return temp;
        }

        iterator& operator--() {
            if (ptr <= begin_ptr) throw std::out_of_range("Iterator out of range");
            --ptr;
            return *this;
        }

        iterator operator--(int) {
            iterator temp = *this;
            if (ptr <= begin_ptr) throw std::out_of_range("Iterator out of range");
            --ptr;
            return temp;
        }

        iterator operator+(size_t n) const {
            iterator temp = *this;
            temp.ptr = (temp.ptr + n < end_ptr) ? temp.ptr + n : end_ptr;
            return temp;
        }

        iterator operator-(size_t n) const {
            iterator temp = *this;
            temp.ptr = (temp.ptr >= begin_ptr + n) ? temp.ptr - n : begin_ptr;
            return temp;
        }

        iterator& operator+=(size_t n) {
            ptr = (ptr + n < end_ptr) ? ptr + n : end_ptr;
            return *this;
        }

        iterator& operator-=(size_t n) {
            ptr = (ptr >= begin_ptr + n) ? ptr - n : begin_ptr;
            return *this;
        }

        bool operator==(const iterator& other) const { return ptr == other.ptr; }
        bool operator!=(const iterator& other) const { return ptr != other.ptr; }
        bool operator<(const iterator& other) const { return ptr < other.ptr; }
        bool operator<=(const iterator& other) const { return ptr <= other.ptr; }
        bool operator>(const iterator& other) const { return ptr > other.ptr; }
        bool operator>=(const iterator& other) const { return ptr >= other.ptr; }

        // Access to element
        T& operator*() {
            if (ptr >= end_ptr) throw std::out_of_range("Iterator out of range");
            return *ptr;
        }

        const T& operator*() const {
            if (ptr >= end_ptr) throw std::out_of_range("Iterator out of range");
            return *ptr;
        }

        T* operator->() {
            if (ptr >= end_ptr) throw std::out_of_range("Iterator out of range");
            return ptr;
        }

        const T* operator->() const {
            if (ptr >= end_ptr) throw std::out_of_range("Iterator out of range");
            return ptr;
        }

        T& operator[](size_t n) {
            if (ptr + n >= end_ptr || ptr + n < begin_ptr) throw std::out_of_range("Iterator out of range");
            return *(ptr + n);
        }

        const T& operator[](size_t n) const {
            if (ptr + n >= end_ptr || ptr + n < begin_ptr) throw std::out_of_range("Iterator out of range");
            return *(ptr + n);
        }
    };

    iterator begin() { return iterator(data, data, data + size); }
    iterator end() { return iterator(data + size, data, data + size); }

};

#endif