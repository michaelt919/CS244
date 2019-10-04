#pragma once
#include <iostream>

class DoubleArrayList
{
public:
    DoubleArrayList(unsigned int capacity);

    // copy constructor
    DoubleArrayList(const DoubleArrayList& original);

    // destructor
    ~DoubleArrayList();
    
    // copy assignment
    DoubleArrayList& operator= (const DoubleArrayList& original);

    // gets size of the list
    unsigned int getSize() const; 

    // gets a single element of the list
    const double& operator[] (unsigned int index) const;

    // gets a single, mutable element of the list
    double& operator[] (unsigned int index);

    // add an item to the end of the list
    void add(double value);

    // remove an item from the list
    void remove();

    // add multiple items to the end of the list
    void addAll(const double* values, int count);

    friend std::ostream& operator<<(std::ostream& os, const DoubleArrayList& list);

private:
    void resize(unsigned int newCapacity);

    double* arr;
    unsigned int capacity;
    unsigned int size = 0;
};
