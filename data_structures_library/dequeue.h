#pragma once

#include <iostream>
#include "vector.h"

template <typename KeyType>
class dequeue
{
private:

	unsigned int tableSize;
	vector<KeyType> table;
	KeyType* Front, * Back;

public:

	dequeue();
	~dequeue();

	void insert(unsigned int, KeyType);
	void erase(unsigned int);

	void push_front(KeyType);
	void push_back(KeyType);

	void pop_front();
	void pop_back();

	bool empty();
	void clear();

	KeyType* front();
	KeyType* back();

	KeyType& operator [](int) const;
};

template <typename KeyType>
dequeue<KeyType>::dequeue()
{
	tableSize = table.size();
	Front = nullptr;
	Back = nullptr;
}

template <typename KeyType>
dequeue<KeyType>::~dequeue()
{
	tableSize = 0;
	table.clear();
	Front = nullptr;
	Back = nullptr;
}

template <typename KeyType>
void dequeue<KeyType>::insert(unsigned int position, KeyType element)
{
	if (position >= tableSize || position < 0)
		return;

	if (position == 0)
	{
		push_front(element);
		return;
	}
	else
	{
		if (position == tableSize - 1)
		{
			push_back(element);
			return;
		}
		else
			table.insert(position, element);
	}
	tableSize++;

	Front = table.front();
	Back = table.back();
}

template <typename KeyType>
void dequeue<KeyType>::erase(unsigned int position)
{
	if (position >= tableSize || position < 0)
		return;

	if (position == 0)
	{
		pop_front();
		return;
	}
	else
	{
		if (position == tableSize - 1)
		{
			pop_back();
			return;
		}
		else
			table.erase(position);
	}
	tableSize--;

	Front = table.front();
	Back = table.back();
}

template <typename KeyType>
void dequeue<KeyType>::push_front(KeyType element)
{
	table.insert(0, element);
	tableSize++;

	Front = table.front();
	Back = table.back();
}

template <typename KeyType>
void dequeue<KeyType>::push_back(KeyType element)
{
	table.push_back(element);
	tableSize++;

	Front = table.front();
	Back = table.back();
}

template <typename KeyType>
void dequeue<KeyType>::pop_front()
{
	table.erase(0);
	tableSize--;

	Front = table.front();
	Back = table.back();
}

template <typename KeyType>
void dequeue<KeyType>::pop_back()
{
	table.pop_back();
	tableSize--;

	Front = table.front();
	Back = table.back();
}

template <typename KeyType>
bool dequeue<KeyType>::empty()
{
	if (table.empty() == true)
		return true;

	return false;
}

template <typename KeyType>
void dequeue<KeyType>::clear()
{
	while (Front)
		pop_back();

	Front = nullptr;
	Back = nullptr;
}

template <typename KeyType>
KeyType* dequeue<KeyType>::front()
{
	return Front;
}

template <typename KeyType>
KeyType* dequeue<KeyType>::back()
{
	return Back;
}

template <typename KeyType>
KeyType& dequeue<KeyType>::operator[](int index) const
{
	if (index >= 0 && index < tableSize)
		return table[index];
}





