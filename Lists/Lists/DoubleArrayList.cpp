#include "DoubleArrayList.h"
#include <string>
#include <iostream>
#include <exception>

using namespace std;

DoubleArrayList::DoubleArrayList(unsigned int capacity) :
    capacity { capacity }, 
    arr { new double[capacity] }
{
}

DoubleArrayList::DoubleArrayList(const DoubleArrayList & other) 
    : DoubleArrayList { 2 * other.size }
{
    // Copy constructor: construct as normal (using the size of the other list 
    // to inform the capacity of the new list) and then copy elements
    for (unsigned int i = 0; i < other.size; i++)
    {
        add(other.arr[i]);
    }
}

DoubleArrayList::~DoubleArrayList()
{
    delete[] arr;
}

DoubleArrayList& DoubleArrayList::operator= (const DoubleArrayList& other)
{
    // Copy assignment: first delete the original array
    delete[] arr;

    // Set new capacity based on list to be copied and then allocate new array
    capacity = other.size * 2;
    arr = new double[other.size * 2];
    size = 0;

    // Copy elements
    for (unsigned int i = 0; i < other.size; i++)
    {
        add(other.arr[i]);
    }

    return *this;
}

unsigned int DoubleArrayList::getSize() const
{
    return size;
}

const double& DoubleArrayList::operator[] (unsigned int index) const
{
    if (index >= size)
    {
        throw out_of_range(
            "Index: " + to_string(index) +
            ", Size: " + to_string(size));
    }
    else
    {
        return arr[index];
    }
}

double& DoubleArrayList::operator[] (unsigned int index)
{
    if (index >= size)
    {
        throw out_of_range(
            "Index: " + to_string(index) +
            ", Size: " + to_string(size));
    }
    else
    {
        return arr[index];
    }
}

void DoubleArrayList::resize(unsigned int newCapacity)
{
    // Keep a temporary pointer to the original array
    double* original = arr;

    // Allocate a new array
    capacity = newCapacity;
    arr = new double[newCapacity];

    // Copy from the original to the new array
    for (unsigned int i = 0; i < size; i++)
    {
        arr[i] = original[i];
    }

    // Delete the original array
    delete[] original;
}

void DoubleArrayList::add(double value)
{
    if (size == capacity)
    {
        resize(size * 2);
    }

    arr[size] = value;
    size++;
}


void DoubleArrayList::remove()
{
    // in-class exercise
    throw std::logic_error("remove() is not implemented.");
}

void DoubleArrayList::addAll(const double* values, int count)
{
    for (int i = 0; i < count; i++)
    {
        add(values[i]);
    }
}

std::ostream& operator<<(std::ostream& os, const DoubleArrayList& list)
{
    if (list.getSize() == 0)
    {
        os << "[]";
    }
    else
    {
        os << "[";
        
        if (list.getSize() > 0)
        {
            os << list[0];

            for (unsigned int i = 1; i < list.getSize(); i++)
            {
                os << ", " << list[i];
            }
        }

        os << "]";
    }

    return os;
}
