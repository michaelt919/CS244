#pragma once
#include <iostream>
#include <exception>

using namespace std;

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
    MutableLinkedListIterator(ListNode<T>* header);

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
};


template <typename T>
class LinkedList
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

    // Remove an item from the front of the list
    void removeFirst();

    // Remove all items from the list
    void clear();

    // Is there anything in the list?
    bool isEmpty() const;

    // get the first element of the list
    const T& getFirst() const;

    // gets the first element of the list, mutable
    T& getFirst();

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
}

template <typename T>
void LinkedList<T>::removeFirst()
{
    if (first)
    {
        ListNode<T>* oldFirst = first;
        first = first->next;
        delete oldFirst;
    }
    else
    {
        throw out_of_range("Empty list");
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
}

template <typename T>
bool LinkedList<T>::isEmpty() const
{
    return first == nullptr;
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
        throw out_of_range("Empty list");
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
        throw out_of_range("Empty list");
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
    return MutableLinkedListIterator<T>{first};
}

template <typename T>
MutableLinkedListIterator<T> LinkedList<T>::end()
{
    return MutableLinkedListIterator<T>{nullptr};
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
    ListNode<T>* start) : current{ start }
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
        delete next;
    }
    else
    {
        throw std::logic_error("No item to remove");
    }
}
