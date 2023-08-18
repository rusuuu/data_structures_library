#pragma once

template <typename KeyType>
class AVL_node
{
protected:
    KeyType key;
    AVL_node* left, * right, * parent;
    unsigned int height;
    int balanceFactor;
    unsigned int rank;

public:
    AVL_node(KeyType);

    void setKey(KeyType);
    KeyType getKey();

    void setLeft(AVL_node*);
    AVL_node* getLeft();

    void setRight(AVL_node*);
    AVL_node* getRight();

    void setParent(AVL_node*);
    AVL_node* getParent();

    void setHeight(unsigned int);
    unsigned int getHeight();

    void setBalanceFactor(int);
    int getBalanceFactor();

    void setRank(unsigned int);
    unsigned int getRank();
};

template <typename KeyType>
AVL_node<KeyType>::AVL_node(KeyType key) : key(key)
{
    this->left = nullptr;
    this->right = nullptr;
    this->parent = nullptr;
    this->height = 1;
    this->balanceFactor = 0;
    this->rank = 1;
}

template <typename KeyType>
void AVL_node<KeyType>::setKey(KeyType key)
{
    this->key = key;
}

template <typename KeyType>
KeyType AVL_node<KeyType>::getKey()
{
    return this->key;
}

template <typename KeyType>
void AVL_node<KeyType>::setLeft(AVL_node* Node)
{
    this->left = Node;
}

template <typename KeyType>
AVL_node<KeyType>* AVL_node<KeyType>::getLeft()
{
    return this->left;
}

template <typename KeyType>
void AVL_node<KeyType>::setRight(AVL_node* Node)
{
    this->right = Node;
}

template <typename KeyType>
AVL_node<KeyType>* AVL_node<KeyType>::getRight()
{
    return this->right;
}

template <typename KeyType>
void AVL_node<KeyType>::setParent(AVL_node* Node)
{
    this->parent = Node;
}

template <typename KeyType>
AVL_node<KeyType>* AVL_node<KeyType>::getParent()
{
    return this->parent;
}

template <typename KeyType>
void AVL_node<KeyType>::setHeight(unsigned int height)
{
    this->height = height;
}

template <typename KeyType>
unsigned int AVL_node<KeyType>::getHeight()
{
    return this->height;
}

template <typename KeyType>
void AVL_node<KeyType>::setBalanceFactor(int balance_factor)
{
    this->balanceFactor = balance_factor;
}

template <typename KeyType>
int AVL_node<KeyType>::getBalanceFactor()
{
    return this->balanceFactor;
}

template <typename KeyType>
void AVL_node<KeyType>::setRank(unsigned int rank)
{
    this->rank = rank;
}

template <typename KeyType>
unsigned int AVL_node<KeyType>::getRank()
{
    return this->rank;
}