#pragma once

#include <iostream>
#include <string>
#include <exception>

using namespace std;

template <typename T>
class ArrayList
{
public:
    ArrayList(unsigned int capacity);

    // copy constructor
    ArrayList(const ArrayList<T>& original);

    // destructor
    ~ArrayList();

    // copy assignment
    ArrayList<T>& operator= (
        const ArrayList<T>& original);

    // gets size of the list
    unsigned int getSize() const;

    // gets a single element of the list
    const T& operator[] (unsigned int index) const;

    // gets a single, mutable element of the list
    T& operator[] (unsigned int index);

    // add an item to the end of the list
    void add(T value);

    // remove an item from the list
    void remove();

    // add multiple items to the end of the list
    void addAll(const T* values, int count);

    // add an item in the middle of the list
    void add(unsigned int index, T value);

    // add multiple items in the middle of the list
    void addAll(unsigned int index, T* values, unsigned int count);

    // remove multiple items from the middle of the list
    void remove(unsigned int index, unsigned int count);

    template <typename T2>
    friend std::ostream& operator<<(std::ostream& os, const ArrayList<T2>& list);

private:
    void resize(unsigned int newCapacity);
    void shiftRight(unsigned int index, unsigned int amount);
    void shiftLeft(unsigned int index, unsigned int amount);

    T* arr;
    unsigned int capacity;
    unsigned int size = 0;
};


template <typename T>
ArrayList<T>::ArrayList(unsigned int capacity) :
    capacity{ capacity },
    arr{ new T[capacity] }
{
}

template <typename T>
ArrayList<T>::ArrayList(const ArrayList<T>& other)
    : ArrayList{ 2 * other.size }
{
    // Copy constructor: construct as normal (using the size of the other list 
    // to inform the capacity of the new list) and then copy elements
    for (unsigned int i = 0; i < other.size; i++)
    {
        add(other.arr[i]);
    }
}

template <typename T>
ArrayList<T>::~ArrayList()
{
    delete[] arr;
}

template <typename T>
ArrayList<T>& ArrayList<T>::operator= (
    const ArrayList<T>& other)
{
    // Copy assignment: first delete the original array
    delete[] arr;

    // Set new capacity based on list to be copied and then allocate new array
    capacity = other.size * 2;
    arr = new T[other.size * 2];
    size = 0;

    // Copy elements
    for (unsigned int i = 0; i < other.size; i++)
    {
        add(other.arr[i]);
    }

    return *this;
}

template <typename T>
unsigned int ArrayList<T>::getSize() const
{
    return size;
}

template <typename T>
const T& ArrayList<T>::operator[] (unsigned int index) const
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

template <typename T>
T& ArrayList<T>::operator[] (unsigned int index)
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

template <typename T>
void ArrayList<T>::resize(unsigned int newCapacity)
{
    // Keep a temporary pointer to the original array
    T* original = arr;

    // Allocate a new array
    capacity = newCapacity;
    arr = new T[newCapacity];

    // Copy from the original to the new array
    for (unsigned int i = 0; i < size; i++)
    {
        arr[i] = original[i];
    }

    // Delete the original array
    delete[] original;
}

template <typename T>
void ArrayList<T>::add(T value)
{
    if (size == capacity)
    {
        resize(size * 2);
    }

    arr[size] = value;
    size++;
}

template <typename T>
void ArrayList<T>::remove()
{
    // in-class exercise
    throw std::logic_error("remove() is not implemented.");
}

template <typename T>
void ArrayList<T>::addAll(const T* values, int count)
{
    for (int i = 0; i < count; i++)
    {
        add(values[i]);
    }
}

template <typename T>
std::ostream& operator<<(std::ostream& os, const ArrayList<T>& list)
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

template <typename T>
void ArrayList<T>::shiftRight(unsigned int index, unsigned int amount)
{
    for (int k = size - 1; k >= static_cast<int>(index); k--)
    {
        arr[k + amount] = arr[k];
    }
}

template <typename T>
void ArrayList<T>::add(unsigned int index, T value)
{
    if (index > size)
    {
        throw out_of_range(
            "Index: " + to_string(index)
            + ", Size: " + to_string(size));
    }

    if (size == capacity)
    {
        resize(size * 2);
    }

    shiftRight(index, 1);
    arr[index] = value;
    size++;
}

template <typename T>
void ArrayList<T>::addAll(unsigned int index, T* values, unsigned int count)
{
    if (index > size)
    {
        throw out_of_range(
            "Index: " + to_string(index)
            + ", Size: " + to_string(size));
    }

    if (size + count > capacity)
    {
        resize((size + count) * 2);
    }

    shiftRight(index, count);

    for (unsigned int k = 0; k < count; k++)
    {
        arr[index + k] = values[k];
    }
    size += count;
}

template <typename T>
void ArrayList<T>::remove(unsigned int index, unsigned int count)
{
    if (index + count > size)
    {
        throw out_of_range(
            "Index: " + to_string(index)
            + ", Size: " + to_string(size));
    }
    else
    {
        shiftLeft(index, count);
        size -= count;
    }
}

template <typename T>
void ArrayList<T>::shiftLeft(unsigned int index, unsigned int amount)
{
    // in-class exercise
    throw std::logic_error("shiftLeft() is not implemented.");
}