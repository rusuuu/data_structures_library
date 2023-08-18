#pragma once

#include <iostream>

template <typename KeyType>
class vector
{
private:

	unsigned int tableCapacity;
	unsigned int tableSize;
	KeyType* table;
	KeyType* Front, * Back;

	void resize();

public:

	vector();
	~vector();

	void insert(unsigned int, KeyType);
	void erase(unsigned int);

	void push_back(KeyType);
	void pop_back();

	bool empty();
	void clear();

	unsigned int capacity();
	unsigned int size();

	KeyType* front();
	KeyType* back();

	KeyType& operator [](int) const;
};

template <typename KeyType>
void vector<KeyType>::resize()
{
	if(tableSize==tableCapacity)
	{
		//a new vector with the size as the old one is created

		KeyType* temporaryTable = new KeyType[tableCapacity];

		//a pointer that changes the addresses between the initial vector and the temporary one is made

		KeyType* swapTable = table;
		table = swapTable;
		temporaryTable = swapTable;

		//the memory of the initial vector is reallocated

		delete[] table;

		tableCapacity *= 2;

		table = new KeyType[tableCapacity];

		for (int index = 0; index < tableSize; index++)
		{
			push_back(temporaryTable[index]);
		}
	}
}

template <typename KeyType>
vector<KeyType>::vector()
{
	tableCapacity = 16;
	tableSize = 0;
	table = new KeyType[tableCapacity];
	Front = nullptr;
	Back = nullptr;
}

template <typename KeyType>
vector<KeyType>::~vector()
{
	clear();
	delete[] table;
}

template <typename KeyType>
void vector<KeyType>::insert(unsigned int position, KeyType key)
{
	if (position >= tableSize || position < 0)
		return;

	if (position == tableSize - 1)
		push_back(key);

	for (int index = tableSize; index > position; index--)
	{
		table[index] = table[index-1];
	}

	tableSize++;
	table[position] = key;

	resize();
}

template <typename KeyType>
void vector<KeyType>::erase(unsigned int position)
{
	if (position >= tableSize || position < 0)
		return;

	if (position == tableSize-1)
	{
		pop_back();
	}

	for (int index = position; index < tableSize-1; index++)
	{
		table[index] = table[index+1];
	}

	tableSize--;
	table[tableSize] = KeyType();
}

template <typename KeyType>
void vector<KeyType>::push_back(KeyType key)
{
	tableSize++;

	if (tableSize == 1)
		Front= &table[tableSize - 1];

	table[tableSize - 1] = key;
	Back = &table[tableSize - 1];

	resize();
}

template<typename KeyType>
inline void vector<KeyType>::pop_back()
{
	if (tableSize < 1)
		return;

	if (tableSize == 1)
		Front = nullptr;

	tableSize--;

	table[tableSize] = KeyType();
	Back = &table[tableSize];
}

template <typename KeyType>
bool vector<KeyType>::empty()
{
	if (front == nullptr)
		return true;

	return false;
}

template <typename KeyType>
void vector<KeyType>::clear()
{
	while (Front)
		pop_back();

	Front = nullptr;
	Back = nullptr;
}

template <typename KeyType>
unsigned int vector<KeyType>::capacity()
{
	return tableCapacity;
}

template <typename KeyType>
unsigned vector<KeyType>::size()
{
	return tableSize;
}

template <typename KeyType>
KeyType* vector<KeyType>::front()
{
	return Front;
}

template <typename KeyType>
KeyType* vector<KeyType>::back()
{
	return Back;
}

template <typename KeyType>
KeyType& vector<KeyType>::operator[](int index) const
{
	if (index >= 0 && index < tableSize)
		return table[index];
}


