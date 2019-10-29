#pragma once
#include "Stack.h"
#include "ArrayList.h"

template <typename T>
class ArrayStack : public Stack<T>
{
public:
    ArrayStack(unsigned int initialCapacity);

    virtual bool isEmpty() const override;
    virtual unsigned int getSize()
        const override;

    virtual void forEach(
        const std::function<void(const T&)>& accept)
        const override;

    virtual void forEach(
        const std::function<void(T&)>& accept);

    virtual const T& peek() const override;
    virtual T& peek() override;

    virtual void push(const T& item) override;
    virtual void pop() override;

private:
    ArrayList<T> base;
};

template <typename T>
ArrayStack<T>::ArrayStack(unsigned int initialCapacity)
    : base{ initialCapacity }
{
}

template <typename T>
bool ArrayStack<T>::isEmpty() const
{
    return base.getSize() == 0;
}

template <typename T>
unsigned int ArrayStack<T>::getSize() const
{
    return base.getSize();
}

template<typename T>
void ArrayStack<T>::forEach(
    const std::function<void(const T&)>& accept)
    const
{
    for (int i = base.getSize()-1; i >= 0; i--)
    {
        accept(base[i]);
    }
}

template<typename T>
void ArrayStack<T>::forEach(
    const std::function<void(T&)>& accept)
{
    for (int i = base.getSize() - 1; i >= 0; i--)
    {
        accept(base[i]);
    }
}

template <typename T>
const T& ArrayStack<T>::peek() const
{
    return base[base.getSize() - 1];
}

template <typename T>
T& ArrayStack<T>::peek()
{
    return base[base.getSize() - 1];
}

template <typename T>
void ArrayStack<T>::push(const T& item)
{
    base.add(item);
}


template <typename T>
void ArrayStack<T>::pop()
{
    base.remove();
}
