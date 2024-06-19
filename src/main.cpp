#include <iostream>
#include <stdexcept>

template <typename T>
class Vector {
private:
    T* data = nullptr;
    size_t size = 0;
    size_t capacity = 0;

public:
    Vector() : data(nullptr), size(0), capacity(0) {}

    explicit Vector(size_t initial_capacity) : data(new T[initial_capacity]), size(0), capacity(initial_capacity) {}

    Vector(size_t initial_capacity, std::nothrow_t) noexcept : data(new (std::nothrow) T[initial_capacity]), size(0), capacity(initial_capacity) {
        if (data == nullptr) {
            std::cout << "Failed to allocate memory" << std::endl;
        }
    }

    Vector(const Vector& other) : data(new T[other.capacity]), size(other.size), capacity(other.capacity) {
        if (data == nullptr || other.data == nullptr) {
            throw std::runtime_error("Vector data is null");
        }
        std::copy(other.data, other.data + other.size, data);
    }

    bool is_data_null() const {
        return data == nullptr;
    }

    Vector& operator=(const Vector& other) {
        if (this != &other) {
            if (other.data == nullptr) {
                throw std::runtime_error("Other vector data is null");
            }
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

    Vector operator+(const Vector& other) {
        if (data == nullptr || other.data == nullptr) {
            throw std::runtime_error("Vector data is null");
        }
        Vector result(capacity + other.capacity);
        std::copy(data, data + size, result.data);
        std::copy(other.data, other.data + other.size, result.data + size);
        result.size = size + other.size;
        return result;
    }

    ~Vector() {
        delete[] data;
    }

    void push_back(const T& item) {
        if (size >= capacity) {
            // If vector is full, create a new array with double capacity
            capacity = (capacity == 0) ? 1 : capacity * 2;
            T* new_data = new T[capacity];
            if (data != nullptr) {
                std::copy(data, data + size, new_data);
                delete[] data;
            }
            data = new_data;
            std::cout << "Resizing capacity to: " << capacity << std::endl;
        }
        // Add the new item
        data[size++] = item;
        std::cout << "Pushed back new item: " << item << std::endl;
    }

    bool resize(size_t new_capacity, std::nothrow_t) noexcept {
        T* new_data = new (std::nothrow) T[new_capacity];
        if (new_data == nullptr) {
            std::cout << "Failed to allocate memory" << std::endl;
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


int main() {
    // Create a Vector with initial capacity of 5
    Vector<int> v(5);

    // Add some elements to the vector
    for (int i = 0; i < 5; ++i) {
        v.push_back(i);
    }

    // Access and print elements of the vector
    for (size_t i = 0; i < 5; ++i) {
        std::cout << "Element at index " << i << ": " << v[i] << std::endl;
    }

    v.push_back(5);
    v.push_back(6);
    v.push_back(7);

    // Test the copy constructor
    Vector<int> v_copy(v);
    std::cout << "Element at index 2 in the copied vector: " << v_copy[2] << std::endl;

    // Test the assignment operator
    Vector<int> v_assign;
    v_assign = v;
    std::cout << "Element at index 3 in the assigned vector: " << v_assign[3] << std::endl;

    // Test the addition operator
    Vector<int> v_res = v + v_copy;
    std::cout << "Size of resulting vector after addition: " << v_res.get_size() << std::endl;

    // Test the new constructor with a large size that is expected to fail
    Vector<int> v_nothrow(static_cast<size_t>(-1), std::nothrow);
    if (v_nothrow.is_data_null()) {
        std::cout << "Failed to allocate memory for vector with nothrow constructor." << std::endl;
    } else {
        std::cout << "Successfully created a vector with nothrow constructor." << std::endl;
    }

    // Test the resize method with a large size that is expected to fail
    Vector<int> v_resize(5);
    if (!v_resize.resize(static_cast<size_t>(-1), std::nothrow)) {
        std::cout << "Failed to resize vector with nothrow." << std::endl;
    } else {
        std::cout << "Successfully resized vector with nothrow." << std::endl;
    }

    return 0;
}