#pragma once

#include <iostream>
#include "BS_node.h"
#include "queue.h"
#include "stack.h"

template <typename KeyType>
class BS_tree
{
private:
    BS_node<KeyType>* _root;

    BS_node<KeyType>* _maximum(BS_node<KeyType>*);
    BS_node<KeyType>* _minimum(BS_node<KeyType>*);

    BS_node<KeyType>* _successor(BS_node<KeyType>*);
    BS_node<KeyType>* _predeccessor(BS_node<KeyType>*);

    void _transpalnt(BS_node<KeyType>*, BS_node<KeyType>*);

    void _erase(BS_node<KeyType>*);

    void _preorderTraversal(BS_node<KeyType>*);
    void _inorderTraversal(BS_node<KeyType>*);
    void _postorderTraversal(BS_node<KeyType>*);
    void _levelorderTraversal(BS_node<KeyType>*);
    void _reverseInorderTraversal(BS_node<KeyType>*);

public:
    BS_tree();
    BS_tree(KeyType);

    void setRoot(BS_node<KeyType>*);
    BS_node<KeyType>* getRoot();

    void insert(KeyType);

    BS_node<KeyType>* findNode(KeyType);

    void nodeRank(BS_node<KeyType>*, int&);

    void deleteNode(KeyType);

    void print_tree(int);

    bool empty();

    void clear();

    BS_node<KeyType>* findNthElev(int);

    void gradesInBetween(KeyType, KeyType);
};

template <typename KeyType>
BS_node<KeyType>* BS_tree<KeyType>::_maximum(BS_node<KeyType>* x)
{
    BS_node<KeyType>* current = x;

    while (current->getRight() != nullptr)
        current = current->getRight();

    return current;
}

template <typename KeyType>
BS_node<KeyType>* BS_tree<KeyType>::_minimum(BS_node<KeyType>* x)
{
    BS_node<KeyType>* current = x;

    while (current->getLeft() != nullptr)
        current = current->getLeft();

    return current;
}

template <typename KeyType>
BS_node<KeyType>* BS_tree<KeyType>::_successor(BS_node<KeyType>* x)
{
    BS_node<KeyType>* current;

    if (x->getRight() != nullptr)
        current = _minimum(x->getRight());
    else
    {
        current = x->getParent();

        while (current != nullptr && x == current->getRight())
        {
            x = current;
            current = current->getParent();
        }
    }

    return current;
}

template <typename KeyType>
BS_node<KeyType>* BS_tree<KeyType>::_predeccessor(BS_node<KeyType>* x)
{
    BS_node<KeyType>* current;

    if (x->getLeft() != nullptr)
        current = _maximum(x->getLeft());
    else
    {
        current = x->getParent();

        while (current != nullptr && x == current->getLeft())
        {
            x = current;
            current = current->getParent();
        }
    }

    return current;
}

template <typename KeyType>
void BS_tree<KeyType>::_transpalnt(BS_node<KeyType>* z, BS_node<KeyType>* y)
{
    if (z->getParent() == nullptr)
        this->setRoot(y);
    else
    {
        if (z == z->getParent()->getLeft())
            z->getParent()->setLeft(y);
        else
            z->getParent()->setRight(y);
    }

    if (y != nullptr)
        y->setParent(z->getParent());
}

template <typename KeyType>
void BS_tree<KeyType>::_erase(BS_node<KeyType>* z)
{
    int rank = 0;
    if (z->getLeft() == nullptr)
    {
        _transpalnt(z, z->getRight());
        delete z;
        nodeRank(this->_root, rank);
        return;
    }

    else
    {
        if (z->getRight() == nullptr)
        {
            _transpalnt(z, z->getLeft());
            delete z;
            nodeRank(this->_root, rank);
            return;
        }
        else
        {
            BS_node<KeyType>* y = _successor(z);

            if (y != z->getRight())
            {
                _transpalnt(y, y->getRight());
                y->setRight(z->getRight());
                z->getRight()->setParent(y);
            }
            _transpalnt(z, y);
            y->setLeft(z->getLeft());
            z->getLeft()->setParent(y);
            delete z;
            nodeRank(this->_root, rank);
            return;
        }
    }
}

template <typename KeyType>
void BS_tree<KeyType>::_preorderTraversal(BS_node<KeyType>* root)
{
    if (root == nullptr)
        return;

    std::cout << root->getKey() << " ";
    _preorderTraversal(root->getLeft());
    _preorderTraversal(root->getRight());
}

template <typename KeyType>
void BS_tree<KeyType>::_inorderTraversal(BS_node<KeyType>* root)
{
    if (root == nullptr)
        return;

    _inorderTraversal(root->getLeft());
    std::cout << root->getKey() << " ";
    _inorderTraversal(root->getRight());
}

template <typename KeyType>
void BS_tree<KeyType>::_postorderTraversal(BS_node<KeyType>* root)
{
    if (root == nullptr)
        return;

    _postorderTraversal(root->getLeft());
    _postorderTraversal(root->getRight());
    std::cout << root->getKey() << " ";
}

template <typename KeyType>
void BS_tree<KeyType>::_levelorderTraversal(BS_node<KeyType>* root)
{
    if (root == nullptr)
        return;

    queue<BS_node<KeyType>*> ordine;
    ordine.push(root);

    while (!ordine.empty())
    {
        std::cout << ordine.front()->getKey()->getKey() << " ";

        if (ordine.front()->getKey()->getLeft() != nullptr)
            ordine.push(ordine.front()->getKey()->getLeft());
        if (ordine.front()->getKey()->getRight() != nullptr)
            ordine.push(ordine.front()->getKey()->getRight());

        ordine.pop();
    }
}

template <typename KeyType>
void BS_tree<KeyType>::_reverseInorderTraversal(BS_node<KeyType>* root)
{
    if (root == nullptr)
        return;

    _reverseInorderTraversal(root->getRight());
    std::cout << root->getKey() << " ";
    _reverseInorderTraversal(root->getLeft());
}

template <typename KeyType>
BS_tree<KeyType>::BS_tree()
{
    this->_root = nullptr;
}

template <typename KeyType>
BS_tree<KeyType>::BS_tree(KeyType key)
{
    this->_root = new BS_node<KeyType>(key);
    this->_root->setLeft(nullptr);
    this->_root->setLeft(nullptr);
    this->_root->setParent(nullptr);
}

template <typename KeyType>
void BS_tree<KeyType>::setRoot(BS_node<KeyType>* x)
{
    this->_root = x;
}

template <typename KeyType>
BS_node<KeyType>* BS_tree<KeyType>::getRoot()
{
    return this->_root;
}

template <typename KeyType>
void BS_tree<KeyType>::nodeRank(BS_node<KeyType>* node, int& rank)
{
    if (node == nullptr)
        return;

    nodeRank(node->getRight(), rank);

    node->setRank(rank + 1);
    rank++;

    nodeRank(node->getLeft(), rank);
}

template <typename KeyType>
void BS_tree<KeyType>::insert(KeyType key)
{
    BS_node<KeyType>* newNode = new BS_node<KeyType>(key);
    BS_node<KeyType>* parent = nullptr;
    BS_node<KeyType>* current = this->_root;
    int rank = 0;

    while (current != nullptr)
    {
        parent = current;

        if (key < current->getKey())
            current = current->getLeft();
        else
        {
            if (key > current->getKey())
                current = current->getRight();
            else
                return;
        }
    }

    newNode->setParent(parent);

    if (parent == nullptr)
        this->_root = newNode;
    else
    {
        if (key < parent->getKey())
            parent->setLeft(newNode);
        else
            parent->setRight(newNode);
    }
    nodeRank(this->_root, rank);
}

template <typename KeyType>
void BS_tree<KeyType>::deleteNode(KeyType key)
{
    BS_node<KeyType>* z = findNode(key);

    if (z != nullptr)
    {
        _erase(z);
        std::cout << "Node has been deleted!" << std::endl;
    }
    else
        std::cout << "Node doesn't exist!" << std::endl;
}

template <typename KeyType>
void BS_tree<KeyType>::print_tree(int opt)
{
    switch (opt)
    {
    case 1:
    {
        _preorderTraversal(this->_root);
        break;
    }
    case 2:
    {
        _inorderTraversal(this->_root);
        break;
    }
    case 3:
    {
        _postorderTraversal(this->_root);
        break;
    }
    case 4:
    {
        _levelorderTraversal(this->_root);
        break;
    }
    case 5:
    {
        _reverseInorderTraversal(this->_root);
        break;
    }
    default:
    {
        std::cout << "Invalid option!" << std::endl;
        break;
    }
    }
}

template <typename KeyType>
bool BS_tree<KeyType>::empty()
{
    if (this->_root == nullptr)
        return true;
    return false;
}

template <typename KeyType>
void BS_tree<KeyType>::clear()
{
    while (!empty())
    {
        _erase(this->_root);
    }
}

template <typename KeyType>
BS_node<KeyType>* BS_tree<KeyType>::findNode(KeyType key)
{
    BS_node<KeyType>* current = this->_root;

    if (current == nullptr)
        return nullptr;

    while (current != nullptr)
    {
        if (key < current->getKey())
            current = current->getLeft();
        else
        {
            if (key > current->getKey())
                current = current->getRight();
            else
                return current;
        }
    }

    return nullptr;
}

template <typename KeyType>
BS_node<KeyType>* BS_tree<KeyType>::findNthElev(int Nth)
{
    BS_node<KeyType>* current = this->getRoot();

    if (current == nullptr)
        return nullptr;

    while (current != nullptr)
    {
        if (Nth > current->getRank())
            current = current->getLeft();
        else
        {
            if (Nth < current->getRank())
                current = current->getRight();
            else
                return current;
        }
    }

    return nullptr;
}

template <typename KeyType>
void BS_tree<KeyType>::gradesInBetween(KeyType begin, KeyType end)
{
    BS_node<KeyType>* current = _root;

    if (current == nullptr)
        return;

    queue<BS_node<KeyType>*> order;
    order.push(current);

    unsigned int numberOfGrades = 0;

    while (order.empty() == false)
    {
        KeyType currentGrade = order.front()->getKey()->getKey();

        if (currentGrade >= begin && currentGrade <= end)
        {
            numberOfGrades++;
            std::cout << order.front()->getKey()->getKey() << std::endl;
        }

        if (order.front()->getKey()->getLeft())
        {
            if (currentGrade >= begin)
                order.push(order.front()->getKey()->getLeft());
        }

        if (order.front()->getKey()->getRight())
        {
            if (currentGrade <= end)
                order.push(order.front()->getKey()->getRight());
        }

        order.pop();
    }

    std::cout << std::endl;
    std::cout << numberOfGrades << " grades" << std::endl;
}