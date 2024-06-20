#include "MyVector.h"
#include <iostream>

int main() {
    // Create a MyVector with initial capacity of 5
    MyVector<int> v(5);

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
    MyVector<int> v_copy(v);
    std::cout << "Element at index 2 in the copied vector: " << v_copy[2] << std::endl;

    // Test the assignment operator
    MyVector<int> v_assign;
    v_assign = v;
    std::cout << "Element at index 3 in the assigned vector: " << v_assign[3] << std::endl;

    // Test the addition operator
    MyVector<int> v_res = v + v_copy;
    std::cout << "Size of resulting vector after addition: " << v_res.get_size() << std::endl;

    // Test the new constructor with a large size that is expected to fail
    MyVector<int> v_nothrow(static_cast<size_t>(-1), std::nothrow);
    if (v_nothrow.is_data_null()) {
        std::cout << "Failed to allocate memory for vector with nothrow constructor." << std::endl;
    } else {
        std::cout << "Successfully created a vector with nothrow constructor." << std::endl;
    }

    // Test the resize method with a large size that is expected to fail
    MyVector<int> v_resize(5);
    if (!v_resize.resize(static_cast<size_t>(-1), std::nothrow)) {
        std::cout << "Failed to resize vector with nothrow." << std::endl;
    } else {
        std::cout << "Successfully resized vector with nothrow." << std::endl;
    }

    return 0;
}