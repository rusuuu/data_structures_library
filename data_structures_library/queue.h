#pragma once

#include <iostream>
#include "component.h"

template <typename KeyType>
class queue
{
private:

	component<KeyType>* head, * tail;
	unsigned int size;

public:

	queue();

	void push(KeyType key);
	void pop();

	bool empty();

	void clear();

    component<KeyType>* front();
	component<KeyType>* back();
};

template <typename KeyType>
queue<KeyType>::queue()
{
    head = nullptr;
    tail = nullptr;
    size = 0;
}

template <typename KeyType>
void queue<KeyType>::push(KeyType key)
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
void queue<KeyType>::pop()
{
    if (!head)
        return;

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
bool queue<KeyType>::empty()
{
    if (head == nullptr)
        return true;

    return false;
}

template <typename KeyType>
void queue<KeyType>::clear()
{
    while (!empty())
        pop();
}

template <typename KeyType>
component<KeyType>* queue<KeyType>::front()
{
    return head;
}

template <typename KeyType>
component<KeyType>* queue<KeyType>::back()
{
    return tail;
}