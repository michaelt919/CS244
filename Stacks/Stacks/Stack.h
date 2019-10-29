#pragma once
#include "Collection.h"

template <typename T>
class Stack : public Collection<T>
{
public:
    virtual ~Stack() = 0;

    virtual bool isEmpty() const = 0;
    virtual const T& peek() const = 0;
    virtual T& peek() = 0;

    virtual void push(const T& item) = 0;
    virtual void pop() = 0;
};

template <typename T>
Stack<T>::~Stack()
{
}
