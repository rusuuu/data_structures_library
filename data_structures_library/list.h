#pragma once

#include <iostream>
#include "component.h"

template <typename KeyType>
class list
{
private:

    component<KeyType>* head, * tail;
    unsigned int size;

    void remove(component<KeyType>*);

public:

    list();
    ~list();

    void push_front(KeyType);
    void push_back(KeyType);

    void pop_front();
    void pop_back();

    component<KeyType>* find(KeyType);

    void insert_after(component<KeyType>*, KeyType);
    void erase(KeyType);

    bool empty();

    void clear();

    void print();

    component<KeyType>* front();
    component<KeyType>* back();
};

template <typename KeyType>
void list<KeyType>::remove(component<KeyType>* toBeDeleted)
{
    if (toBeDeleted == head)
        pop_front();
    else
        if (toBeDeleted == tail)
            pop_back();
        else
        {
            component<KeyType>* prevNod = toBeDeleted->getUp_Left();
            component<KeyType>* nextNod = toBeDeleted->getDown_Right();
            prevNod->setDown_Right(nextNod);
            nextNod->setUp_Left(prevNod);
            delete toBeDeleted;

            size--;
        }
}

template<typename KeyType>
list<KeyType>::list()
{
    head = nullptr;
    tail = nullptr;
    size = 0;
}

template <typename KeyType>
list<KeyType>::~list()
{
    clear();
}

template <typename KeyType>
void list<KeyType>::push_front(KeyType key)
{
    component<KeyType>* newNode = new component<KeyType>;
    newNode->setKey(key);
    newNode->setUp_Left(nullptr);
    newNode->setDown_Right(head);

    if (head)
        head->setUp_Left(newNode);
    else
        tail = newNode;

    head = newNode;

    size++;
}

template <typename KeyType>
void list<KeyType>::push_back(KeyType key)
{
    component<KeyType>* newNode = new component<KeyType>;
    newNode->setKey(key);
    newNode->setUp_Left(tail);
    newNode->setDown_Right(nullptr);

    if (tail)
        tail->setDown_Right(newNode);
    else
        head = newNode;

    tail = newNode;

    size++;
}

template <typename KeyType>
void list<KeyType>::pop_front()
{
    if (!head) return;

    component<KeyType>* current = head->getDown_Right();

    if (current)
        current->setUp_Left(nullptr);
    else
        tail = nullptr;

    delete head;
    head = current;

    size--;
}

template <typename KeyType>
void list<KeyType>::pop_back()
{
    if (!tail) return;

    component<KeyType>* current = tail->getUp_Left();

    if (current)
        current->setDown_Right(nullptr);
    else
        head = nullptr;

    delete tail;
    tail = current;

    size--;
}

template <typename KeyType>
component<KeyType>* list<KeyType>::find(KeyType key)
{
    component<KeyType>* current = head;

    while (current)
    {
        if (current->getKey() == key)
            return current;

        current = current->getDown_Right();
    }
    return nullptr;
}

template <typename KeyType>
void list<KeyType>::insert_after(component<KeyType>* afterComponent, KeyType key)
{
    if (!head)
        return;
    else
        if (head == afterComponent)
            push_front(key);
        else
        {
            component<KeyType>* newNode = new component<KeyType>;
            newNode->setKey(key);
            newNode->setDown_Right(afterComponent);
            newNode->setUp_Left(afterComponent->getUp_Left());
            afterComponent->getUp_Left()->setDown_Right(newNode);
            afterComponent->getUp_Left(newNode);

            size++;
        }
}

template <typename KeyType>
void list<KeyType>::erase(KeyType key)
{
    component<KeyType>* current = head;

    while (current)
    {
        current = find(key);

        if (current)
            remove(current);
        else
            return;
    }
}

template <typename KeyType>
bool list<KeyType>::empty()
{
    if (!head)
        return true;

    return false;
}

template <typename KeyType>
void list<KeyType>::clear()
{
    while (empty() == false)
    {
        pop_front();
    }
    size = 0;
}

template <typename KeyType>
void list<KeyType>::print()
{
    component<KeyType>* current = head;

    while (current)
    {
        std::cout << current->getKey() << " ";
        current = current->getDown_Right();
    }
    std::cout << std::endl;
}

template <typename KeyType>
component<KeyType>* list<KeyType>::front()
{
    return head;
}

template <typename KeyType>
component<KeyType>* list<KeyType>::back()
{
    return tail;
}
