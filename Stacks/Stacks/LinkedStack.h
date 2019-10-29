#pragma once
#include "Stack.h"
#include "LinkedList.h"

template <typename T>
class LinkedStack : public Stack<T>
{
public:
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
    LinkedList<T> base;
};

template <typename T>
bool LinkedStack<T>::isEmpty() const
{
    return base.isEmpty();
}

template <typename T>
unsigned int LinkedStack<T>::getSize() const
{
    return base.getSize();
}

template<typename T>
void LinkedStack <T>::forEach(
    const std::function<void(const T&)>& accept)
    const
{
    base.forEach(accept);
}

template<typename T>
void LinkedStack <T>::forEach(
    const std::function<void(T&)>& accept)
{
    base.forEach(accept);
}
template <typename T>
const T& LinkedStack<T>::peek() const
{
    return base.getFirst();
}

template <typename T>
T& LinkedStack<T>::peek()
{
    return base.getFirst();
}

template <typename T>
void LinkedStack<T>::push(const T& item)
{
    base.addFirst(item);
}

template <typename T>
void LinkedStack<T>::pop()
{
    base.removeFirst();
}
