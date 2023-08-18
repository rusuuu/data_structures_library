#pragma once
#pragma once

#include <iostream>

template <typename KeyType>
class RB_node
{
private:

    KeyType key;
    RB_node* left, * right, * parent;
    char colour;
    int rank;

public:

    RB_node();
    RB_node(KeyType);

    void setKey(KeyType);
    KeyType getKey();

    void setLeft(RB_node*);
    RB_node* getLeft();

    void setRight(RB_node*);
    RB_node* getRight();

    void setParent(RB_node*);
    RB_node* getParent();

    void setColour(char);
    char getColour();

    void setRank(int);
    int getRank();
};

template <typename KeyType>
RB_node<KeyType>::RB_node()
{
    this->key = KeyType();
    this->rank = 1;
    this->left = nullptr;
    this->right = nullptr;
    this->parent = nullptr;
    this->colour = 'r';
}

template <typename KeyType>
RB_node<KeyType>::RB_node(KeyType key)
{
    this->key = key;
    this->rank = 1;
    this->left = nullptr;
    this->right = nullptr;
    this->parent = nullptr;
    this->colour = 'r';
}

template <typename KeyType>
void RB_node<KeyType>::setKey(KeyType key)
{
    this->key = key;
}

template <typename KeyType>
KeyType RB_node<KeyType>::getKey()
{
    return this->key;
}

template <typename KeyType>
void RB_node<KeyType>::setLeft(RB_node* left)
{
    this->left = left;
}

template <typename KeyType>
RB_node<KeyType>* RB_node<KeyType>::getLeft()
{
    return this->left;
}

template <typename KeyType>
void RB_node<KeyType>::setRight(RB_node* right)
{
    this->right = right;
}

template <typename KeyType>
RB_node<KeyType>* RB_node<KeyType>::getRight()
{
    return this->right;
}

template <typename KeyType>
void RB_node<KeyType>::setParent(RB_node* parent)
{
    this->parent = parent;
}

template <typename KeyType>
RB_node<KeyType>* RB_node<KeyType>::getParent()
{
    return this->parent;
}

template <typename KeyType>
void RB_node<KeyType>::setColour(char colour)
{
    this->colour = colour;
}

template <typename KeyType>
char RB_node<KeyType>::getColour()
{
    return colour;
}

template <typename KeyType>
void RB_node<KeyType>::setRank(int rank)
{
    this->rank = rank;
}

template <typename KeyType>
int RB_node<KeyType>::getRank()
{
    return this->rank;
}


