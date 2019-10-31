#pragma once
#include <iostream>
#include <exception>
#include <functional>
#include "Collection.h"

template <typename T>
struct ListNode
{
public:
    T value;
    ListNode<T>* next = nullptr;
};

template <typename T>
class LinkedListIterator
{
public:
    LinkedListIterator(ListNode<T> const* start);

    // pre-increment
    LinkedListIterator<T>& operator ++ ();

    // post-increment
    void operator ++ (int);

    bool operator == (const LinkedListIterator<T>& other) const;
    bool operator != (const LinkedListIterator<T>& other) const;

    T const& operator * () const;
    T const* operator -> () const;

private:
    ListNode<T> const* current = nullptr;
};

template <class T>
class MutableLinkedListIterator
{
public:
    MutableLinkedListIterator(ListNode<T>* start, ListNode<T>*& last);

    // pre-increment
    MutableLinkedListIterator<T>& operator ++ ();

    // post-increment
    void operator ++ (int);

    bool operator == (const MutableLinkedListIterator<T>& other) const;
    bool operator != (const MutableLinkedListIterator<T>& other) const;

    T& operator * ();
    T* operator -> ();

    bool hasNext() const;
    T& peekNext();
    void addNext(T value);
    void removeNext();

private:
    ListNode<T>* current;
    ListNode<T>*& last;
};


template <typename T>
class LinkedList : public Collection<T>
{
public:

    // Use default constructor
    LinkedList() = default;

    // Implement destructor but disable copy constructor and copy assignment (for now)
    LinkedList(const LinkedList<T>& original) = delete;
    ~LinkedList();
    LinkedList<T>& operator= (
        const LinkedList<T>& original) = delete;

    // Add an item to the front of the list
    void addFirst(T value);

    // Add an item to the back of the list
    void addLast(T value);

    // Remove an item from the front of the list
    void removeFirst();

    // Remove all items from the list
    void clear();

    // Is there anything in the list?
    bool isEmpty() const;

    virtual unsigned int getSize() const override;

    virtual void forEach(
        const std::function<void(const T&)>& accept)
        const override;

    virtual void forEach(
        const std::function<void(T&)>& accept)
        override;


    // get the first element of the list
    const T& getFirst() const;

    // gets the first element of the list, mutable
    T& getFirst();

    // get the last element of the list
    const T& getLast() const;

    // gets the last element of the list, mutable
    T& getLast();

    template <typename T2>
    friend std::ostream& operator << (
        std::ostream& os,
        const LinkedList<T2>& list);

    // Gets an iterator for use with range-based for loop
    LinkedListIterator<T> begin() const;
    LinkedListIterator<T> end() const;

    // Gets an iterator with extended functionality 
    // for making changes in the middle of the list
    MutableLinkedListIterator<T> begin();
    MutableLinkedListIterator<T> end();

private:
    ListNode<T>* first = nullptr;
    ListNode<T>* last = nullptr;
};

template<typename T>
LinkedList<T>::~LinkedList()
{
    clear();
}

template <typename T>
void LinkedList<T>::addFirst(T value)
{
    // Create a new node
    ListNode<T>* newNode = new ListNode<T>();

    // Store the new element in the new node
    newNode->value = value;

    // Link the new node to the old first node
    newNode->next = first;

    // Set the new node as the first node
    first = newNode;

    if (!last)
    {
        // If there is just one element in the list, 
        // first and last are the same.
        last = first;
    }
}

template <typename T>
void LinkedList<T>::addLast(T value)
{
    // Create a new node
    ListNode<T>* newNode = new ListNode<T>();

    // Store the new element in the new node
    newNode->value = value;

    if (last)
    {
        // Link the new node to the old last node
        last->next = newNode;
    }
    else
    {
        // If there is just one element in the list, 
        // first and last are the same.
        first = newNode;
    }

    // Set the new node as the last node
    last = newNode;
}

template <typename T>
void LinkedList<T>::removeFirst()
{
    if (first)
    {
        ListNode<T>* oldFirst = first;
        first = first->next;
        delete oldFirst;

        if (!first)
        {
            // If we deleted the last element
            // in the list, last is nullptr
            last = nullptr;
        }
    }
    else
    {
        throw std::out_of_range("Empty list");
    }
}

template<typename T>
void LinkedList<T>::clear()
{
    ListNode<T>* toDelete = first;
    while (toDelete)
    {
        first = toDelete->next;
        delete toDelete;
        toDelete = first;
    }

    last = nullptr;
}

template <typename T>
bool LinkedList<T>::isEmpty() const
{
    return first == nullptr;
}

template<typename T>
unsigned int LinkedList<T>::getSize() const
{
    // lab exercise
    throw std::logic_error("getSize() is not implemented.");
}

template<typename T>
void LinkedList<T>::forEach(const std::function<void(const T&)>& accept) const
{
    for (const T& item : *this)
    {
        accept(item);
    }
}

template<typename T>
void LinkedList<T>::forEach(const std::function<void(T&)>& accept)
{
    for (T& item : *this)
    {
        accept(item);
    }
}

template <typename T>
T const& LinkedList<T>::getFirst() const
{
    if (first)
    {
        return first->value;
    }
    else
    {
        throw std::out_of_range("Empty list");
    }
}

template <typename T>
T& LinkedList<T>::getFirst()
{
    if (first)
    {
        return first->value;
    }
    else
    {
        throw std::out_of_range("Empty list");
    }
}

template <typename T>
T const& LinkedList<T>::getLast() const
{
    if (last)
    {
        return last->value;
    }
    else
    {
        throw std::out_of_range("Empty list");
    }
}

template <typename T>
T& LinkedList<T>::getLast()
{
    if (last)
    {
        return last->value;
    }
    else
    {
        throw std::out_of_range("Empty list");
    }
}

template <typename T>
std::ostream& operator << (std::ostream& os,
    const LinkedList<T>& list)
{
    if (list.isEmpty())
    {
        os << "[]";
    }
    else
    {
        os << "[" << list.first->value;

        for (ListNode<T>* current = list.first->next;
            current != nullptr;
            current = current->next)
        {
            os << ", " << current->value;
        }

        os << "]";
    }

    return os;
}

template <typename T>
LinkedListIterator<T> LinkedList<T>::begin() const
{
    return LinkedListIterator<T>{first};
}

template <typename T>
LinkedListIterator<T> LinkedList<T>::end() const
{
    return LinkedListIterator<T>{nullptr};
}

template <typename T>
MutableLinkedListIterator<T> LinkedList<T>::begin()
{
    return MutableLinkedListIterator<T>{first, last};
}

template <typename T>
MutableLinkedListIterator<T> LinkedList<T>::end()
{
    return MutableLinkedListIterator<T>{nullptr, last};
}

template <typename T>
LinkedListIterator<T>::LinkedListIterator(
    ListNode<T> const* start) : current{ start }
{
}

template <typename T>
typename LinkedListIterator<T>& LinkedListIterator<T>::operator ++ () // pre-increment
{
    current = current->next;
    return *this;
}

template <typename T>
void LinkedListIterator<T>::operator ++ (int) // post-increment
{
    current = current->next;
}


template <typename T>
bool LinkedListIterator<T>::operator == (const LinkedListIterator<T>& other) const
{
    return this->current == other.current;
}

template <typename T>
bool LinkedListIterator<T>::operator != (const LinkedListIterator<T>& other) const
{
    return !(*this == other);
}

template <typename T>
T const& LinkedListIterator<T>::operator * () const
{
    return current->value;
}

template <typename T>
T const* LinkedListIterator<T>::operator -> () const
{
    return &(current->value);
}

template <typename T>
MutableLinkedListIterator<T>::MutableLinkedListIterator(
        ListNode<T>* start, ListNode<T>*& last)
    : current{ start }, last{ last }
{
}

template <typename T>
typename MutableLinkedListIterator<T>& MutableLinkedListIterator<T>::operator ++ () // pre-increment
{
    current = current->next;
    return *this;
}

template <typename T>
void MutableLinkedListIterator<T>::operator ++ (int) // post-increment
{
    current = current->next;
}


template <typename T>
bool MutableLinkedListIterator<T>::operator == (const MutableLinkedListIterator<T>& other) const
{
    return this->current == other.current;
}

template <typename T>
bool MutableLinkedListIterator<T>::operator != (const MutableLinkedListIterator<T>& other) const
{
    return !(*this == other);
}


template <typename T>
T& MutableLinkedListIterator<T>::operator * ()
{
    return current->value;
}

template <typename T>
T* MutableLinkedListIterator<T>::operator -> ()
{
    return &(current->value);
}

template<class T>
bool MutableLinkedListIterator<T>::hasNext() const
{
    return current != nullptr && current->next != nullptr;
}

template<class T>
T& MutableLinkedListIterator<T>::peekNext()
{
    ListNode<T>* next = current->next;

    // Prevent null pointer access when trying 
    // to peek past the end of the list.
    if (hasNext())
    {
        return next->value;
    }
    else
    {
        throw std::logic_error(
            "No item to peek at");
    }
}

template<class T>
void MutableLinkedListIterator<T>::addNext(T value)
{
    // in-class exercise
    throw std::logic_error("addNext() is not implemented.");
}

template<class T>
void MutableLinkedListIterator<T>::removeNext()
{
    ListNode<T>* next = current->next;

    // Prevent null pointer access when trying 
    // to remove past the end of the list.
    if (hasNext())
    {
        current->next = next->next;

        if (next == last)
        {
            last = current;
        }

        delete next;
    }
    else
    {
        throw std::logic_error("No item to remove");
    }
}