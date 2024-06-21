#include "MyVector.h"
#include <iostream>

int main() {
    // Test the constructor
    MyVector<int> v(5);
    std::cout << "Created a vector with initial capacity of 5." << std::endl;

    // Test push_back
    for (int i = 0; i < 5; ++i) {
        v.push_back(i);
        std::cout << "Pushed back " << i << std::endl;
    }

    // Test the iterator
    std::cout << "Elements in the vector: ";
    for (MyVector<int>::iterator it = v.begin(); it != v.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    // Test the iterator with operator[]
    std::cout << "Elements in the vector using iterator with operator[]: ";
    for (MyVector<int>::iterator it = v.begin(); it != v.end(); ++it) {
        std::cout << it[0] << " ";
    }
    std::cout << std::endl;

    // Test the iterator with operator+
    MyVector<int>::iterator it = v.begin();
    it = it + 2;
    std::cout << "Element at position 2 using iterator with operator+: " << *it << std::endl;

    // Test the iterator with operator-
    it = v.end();
    it = it - 1;
    std::cout << "Last element using iterator with operator-: " << *it << std::endl;

    // Test the iterator with operator+=
    it = v.begin();
    it += 2;
    std::cout << "Element at position 2 using iterator with operator+=: " << *it << std::endl;

    // Test the iterator with operator-=
    it = v.end();
    it -= 1;
    std::cout << "Last element using iterator with operator-=: " << *it << std::endl;

    // Test the iterator with operator++ and operator--
    it = v.begin();
    ++it;
    std::cout << "Element at position 1 using iterator with operator++: " << *it << std::endl;
    --it;
    std::cout << "Element at position 0 using iterator with operator--: " << *it << std::endl;

    // Test the iterator with operator++(int) and operator--(int)
    it = v.begin();
    it++;
    std::cout << "Element at position 1 using iterator with operator++(int): " << *it << std::endl;
    it--;
    std::cout << "Element at position 0 using iterator with operator--(int): " << *it << std::endl;

    // Test the iterator with relational operators
    MyVector<int>::iterator it1 = v.begin();
    MyVector<int>::iterator it2 = v.begin() + 1;
    std::cout << "it1 == it2: " << (it1 == it2) << std::endl;
    std::cout << "it1 != it2: " << (it1 != it2) << std::endl;
    std::cout << "it1 < it2: " << (it1 < it2) << std::endl;
    std::cout << "it1 <= it2: " << (it1 <= it2) << std::endl;
    std::cout << "it1 > it2: " << (it1 > it2) << std::endl;
    std::cout << "it1 >= it2: " << (it1 >= it2) << std::endl;

    return 0;
}