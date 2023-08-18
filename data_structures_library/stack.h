#pragma once

#include <iostream>
#include "component.h"

template <typename KeyType>
class stack
{
private:

    component<KeyType>* first;
    unsigned int size;

public:

    stack();

    void push(KeyType key);
    void pop();

    bool empty();

    void clear();

    component<KeyType>* top();
};

template <typename KeyType>
stack<KeyType>::stack()
{
    first = nullptr;
    size = 0;
}

template <typename KeyType>
void stack<KeyType>::push(KeyType key)
{
    component<KeyType>* newNode = new component<KeyType>;
    newNode->setKey(key);
    newNode->setUp_Left(nullptr);
    newNode->setDown_Right(first);

    if (first)
        first->setUp_Left(newNode);

    first = newNode;

    size++;
}

template <typename KeyType>
void stack<KeyType>::pop()
{
    if (!first)
        return;

    component<KeyType>* current = first->getDown_Right();

    if (current)
        current->setUp_Left(nullptr);

    delete first;
    first = current;

    size--;
}

template <typename KeyType>
bool stack<KeyType>::empty()
{
    return first == nullptr;
}

template <typename KeyType>
void stack<KeyType>::clear()
{
    while (!empty())
        pop();
}

template <typename KeyType>
component<KeyType>* stack<KeyType>::top()
{
    return first;
}