#pragma once

#include <iostream>

template <typename KeyType>
class BS_node
{
private:

    KeyType key;
    BS_node* left, * right, * parent;
    int rank;

public:

    BS_node();
    BS_node(KeyType);

    void setKey(KeyType);
    KeyType getKey();

    void setLeft(BS_node*);
    BS_node* getLeft();

    void setRight(BS_node*);
    BS_node* getRight();

    void setParent(BS_node*);
    BS_node* getParent();

    void setRank(int);
    int getRank();
};

template <typename KeyType>
BS_node<KeyType>::BS_node()
{
    this->key = KeyType();
    this->rank = 1;
    this->left = nullptr;
    this->right = nullptr;
    this->parent = nullptr;
}

template <typename KeyType>
BS_node<KeyType>::BS_node(KeyType key)
{
    this->key = key;
    this->rank = 1;
    this->left = nullptr;
    this->right = nullptr;
    this->parent = nullptr;
}

template <typename KeyType>
void BS_node<KeyType>::setKey(KeyType key)
{
    this->key = key;
}

template <typename KeyType>
KeyType BS_node<KeyType>::getKey()
{
    return this->key;
}

template <typename KeyType>
void BS_node<KeyType>::setLeft(BS_node* left)
{
    this->left = left;
}

template <typename KeyType>
BS_node<KeyType>* BS_node<KeyType>::getLeft()
{
    return this->left;
}

template <typename KeyType>
void BS_node<KeyType>::setRight(BS_node* right)
{
    this->right = right;
}

template <typename KeyType>
BS_node<KeyType>* BS_node<KeyType>::getRight()
{
    return this->right;
}

template <typename KeyType>
void BS_node<KeyType>::setParent(BS_node* parent)
{
    this->parent = parent;
}

template <typename KeyType>
BS_node<KeyType>* BS_node<KeyType>::getParent()
{
    return this->parent;
}

template <typename KeyType>
void BS_node<KeyType>::setRank(int rank)
{
    this->rank = rank;
}

template <typename KeyType>
int BS_node<KeyType>::getRank()
{
    return this->rank;
}