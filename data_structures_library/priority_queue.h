#pragma once

#include <iostream>
#include "vector.h"

template <typename KeyType>
class priority_queue
{
private:

    vector<KeyType> heap;
    unsigned int heapSize;

    void increase_priority(unsigned int&, unsigned int, KeyType);
    void max_heapfy(int);

public:

    priority_queue();
    ~priority_queue();

    void push(KeyType);
    void pop();
    void clear();

    KeyType* top();
};

template <typename KeyType>
void priority_queue<KeyType>::increase_priority(unsigned int& heap_size, unsigned int index, KeyType value)
{
    if (value > heap[index])
    {
        heap[index] = value;
        int position = (index - 1) / 2;

        while (index > 0 && heap[position] < value)
        {
            heap[index] = heap[position];
            index = position;
            position = (index - 1) / 2;
        }
        heap[index] = value;
    }
}

template <typename KeyType>
void priority_queue<KeyType>::max_heapfy(int index)
{
    int left = 2 * index + 1;
    int right = 2 * index + 2;
    int maxIndex = index;

    if (left < heapSize && heap[left] > heap[maxIndex])
        maxIndex = left;

    if (right < heapSize && heap[right] > heap[maxIndex])
        maxIndex = right;

    if (maxIndex != index)
    {
        heap[index] = heap[index] + heap[maxIndex];
        heap[maxIndex] = heap[index] - heap[maxIndex];
        heap[index] = heap[index] - heap[maxIndex];
        max_heapfy(heap, heapSize, maxIndex);
    }
}

template <typename KeyType>
priority_queue<KeyType>::priority_queue()
{
    heapSize = 0;
}

template <typename KeyType>
priority_queue<KeyType>::~priority_queue()
{
    clear();
}

template <typename KeyType>
void priority_queue<KeyType>::push(KeyType value)
{
    heap[heapSize] = 0;
    heapSize++;
    increase_priority(heap, heapSize, heapSize - 1, value);
}

template<typename KeyType>
void priority_queue<KeyType>::pop()
{
    heap[0] = heap[heapSize - 1];
    heapSize--;
    max_heapfy(heap, heapSize, 0);
}

template <typename KeyType>
void priority_queue<KeyType>::clear()
{
    while (top())
        pop();
}

template <typename KeyType>
KeyType* priority_queue<KeyType>::top()
{
    return heap[0];
}
