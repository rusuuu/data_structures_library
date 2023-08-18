#pragma once

#include <iostream>
#include "component.h"

template <typename KeyType>
class forward_list
{
private:

	component<KeyType>* head;
	unsigned int size;

public:

	forward_list();
	~forward_list();

	void push_front(KeyType);
	void pop_front();

	component<KeyType>* find(KeyType);

	void insert_after(component<KeyType>*, KeyType);
	void erase_after(component<KeyType>*);

	bool empty();

	void clear();

	void print();

	component<KeyType>* front();
};

template <typename KeyType>
forward_list<KeyType>::forward_list()
{
	head = nullptr;
	size = 0;
}

template <typename KeyType>
forward_list<KeyType>::~forward_list()
{
	clear();
}

template<typename KeyType>
inline void forward_list<KeyType>::push_front(KeyType key)
{
	component<KeyType>* newNode = new component<KeyType>;

	newNode->setKey(key);
	newNode->setDown_Right(head);
	head = newNode;

	size++;
}

template <typename KeyType>
void forward_list<KeyType>::pop_front()
{
	if (!head)
		return;

	component<KeyType>* current = head->getDown_Right();

	delete head;
	head = current;

	size--;
}

template <typename KeyType>
component<KeyType>* forward_list<KeyType>::find(KeyType key)
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
void forward_list<KeyType>::insert_after(component<KeyType>* afterComponent, KeyType key)
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

			component<KeyType>* afterAfterComponent = afterComponent->getDown_Right();
			afterComponent->setDown_Right(newNode);
			newNode->setDown_Right(afterAfterComponent);

			size++;
		}
}

template<typename KeyType>
inline void forward_list<KeyType>::erase_after(component<KeyType>* afterComponent)
{
	if (!head)
		return;
	else
		if (head == afterComponent)
			pop_front();
		else
		{
			component<KeyType>* afterNode = afterComponent->getDown_Right()->getDown_Right();

			delete afterComponent->getDown_Right();
			afterComponent->setDown_Right(afterNode);

			size--;
		}
}

template <typename KeyType>
bool forward_list<KeyType>::empty()
{
	if (!head)
		return true;

	return false;
}

template <typename KeyType>
void forward_list<KeyType>::clear()
{
	while (empty() == false)
	{
		pop_front();
	}
	size = 0;
}

template <typename KeyType>
void forward_list<KeyType>::print()
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
component<KeyType>* forward_list<KeyType>::front()
{
	return head;
}



