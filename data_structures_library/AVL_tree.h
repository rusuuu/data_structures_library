#pragma once

#include <iostream>
#include "AVL_node.h"
#include "stack.h"
#include "queue.h"

template <typename KeyType>
class AVL_tree
{
protected:
    AVL_node<KeyType>* root;
    unsigned int size, height;
    bool ranked;

    AVL_node<KeyType>* find(KeyType);

    void recalculateHeightAndBalanceFactorAtInsertion(AVL_node<KeyType>*);
    void recalculateHeightAndBalanceFactorAtErasion(AVL_node<KeyType>*, AVL_node<KeyType>*);
    void recalculateTreeHeight();
    void recalculateNodeHeight(AVL_node<KeyType>*);
    void recalculateNodeBalanceFactor(AVL_node<KeyType>*);

	void leftRotation(AVL_node<KeyType>*);
    void rightRotation(AVL_node<KeyType>*);
    void rotationManager(AVL_node<KeyType>*);

    AVL_node<KeyType>* getPredecessor(AVL_node<KeyType>*);
    AVL_node<KeyType>* getSuccessor(AVL_node<KeyType>*);

    void transplant(AVL_node<KeyType>*, AVL_node<KeyType>*);

    void rankManager();

public:

	AVL_tree();
    AVL_tree(KeyType);
    ~AVL_tree();

    void setRoot(AVL_node<KeyType>*);
    AVL_node<KeyType>* getRoot();

    void insert(KeyType);
    void erase(KeyType);
    void clear(AVL_node<KeyType>*);

    void postorder(AVL_node<KeyType>*);
    void inorder(AVL_node<KeyType>*);
    void findNthNode(unsigned int);
    void gradesInBetween(KeyType, KeyType);
};

template <typename KeyType>
AVL_node<KeyType>* AVL_tree<KeyType>::find(KeyType key)
{
	AVL_node<KeyType>* parent = nullptr;
	AVL_node<KeyType>* current = this->root;

	while (current != nullptr)
	{
		parent = current;

		if (key == current->getKey())
			return current;

		if (key < current->getKey())
			current = current->getLeft();
		else
			current = current->getRight();
	}

	return nullptr;
}

template <typename KeyType>
void AVL_tree<KeyType>::recalculateHeightAndBalanceFactorAtInsertion(AVL_node<KeyType>* Node)
{
	AVL_node<KeyType>* parent = Node->getParent();

	AVL_node<KeyType>* leftBrother = Node->getParent()->getLeft();
	AVL_node<KeyType>* rightBrother = Node->getParent()->getRight();

	//if the node is the root any operation is nonsense
	if (parent == nullptr)
		return;

	//if the inserted node has a brother it doesn't make sense to recalculate the height in an AVL, so we only set the balance factor of its parent to 0
	if (Node == leftBrother)
	{
		if (rightBrother != nullptr)
		{
			parent->setBalanceFactor(0);
			return;
		}
	}
	else
	{
		if (leftBrother != nullptr)
		{
			parent->setBalanceFactor(0);
			return;
		}
	}

	unsigned int leftHeight, rightHeight;
	int balance_factor = 0;

	do
	{
		//recalculating the height

		if (parent->getLeft() == nullptr)
			leftHeight = 0;
		else
			leftHeight = parent->getLeft()->getHeight();

		if (parent->getRight() == nullptr)
			rightHeight = 0;
		else
			rightHeight = parent->getRight()->getHeight();

		parent->setHeight(leftHeight > rightHeight ? leftHeight + 1 : rightHeight + 1);

		//recalculating the balance factor

		balance_factor = 0;

		if (parent->getRight() != nullptr)
			balance_factor += parent->getRight()->getHeight();

		if (parent->getLeft() != nullptr)
			balance_factor -= parent->getLeft()->getHeight();

		parent->setBalanceFactor(balance_factor);

		if (parent->getBalanceFactor() == 2 || parent->getBalanceFactor() == -2)
		{
			rotationManager(parent);
		}

		parent = parent->getParent();

	} while (balance_factor != 0 && parent != nullptr);
}

template <typename KeyType>
void ::AVL_tree<KeyType>::recalculateHeightAndBalanceFactorAtErasion(AVL_node<KeyType>* Node, AVL_node<KeyType>* deletedSuccessor)
{
	AVL_node<KeyType>* parent = Node;

	if (parent == nullptr)
		return;

	unsigned int leftHeight, rightHeight;
	int balance_factor = 0;

	if (deletedSuccessor != nullptr)
	{
		recalculateNodeHeight(deletedSuccessor);
		recalculateNodeBalanceFactor(deletedSuccessor);
	}

	do
	{
		//recalculating the height

		if (parent->getLeft() == nullptr)
			leftHeight = 0;
		else
			leftHeight = parent->getLeft()->getHeight();

		if (parent->getRight() == nullptr)
			rightHeight = 0;
		else
			rightHeight = parent->getRight()->getHeight();

		parent->setHeight(leftHeight > rightHeight ? leftHeight + 1 : rightHeight + 1);

		//recalculating the balance factor

		balance_factor = 0;

		if (parent->getRight() != nullptr)
			balance_factor += parent->getRight()->getHeight();

		if (parent->getLeft() != nullptr)
			balance_factor -= parent->getLeft()->getHeight();

		parent->setBalanceFactor(balance_factor);

		//if the new nde has the new balance factor -2 and his left one 0 or +2 and his right one 0 it doesn't make sense to continue recalculating the height   

		if (parent->getBalanceFactor() == 2)
		{
			if (parent->getRight()->getBalanceFactor() == 0)
				if (deletedSuccessor != nullptr && deletedSuccessor->getBalanceFactor() == 0)
				{
					rotationManager(parent);
					return;
				}
				else
					rotationManager(parent);
		}

		if (parent->getBalanceFactor() == -2)
		{
			if (parent->getLeft()->getBalanceFactor() == 0)
				if (deletedSuccessor != nullptr && deletedSuccessor->getBalanceFactor() == 0)
				{
					rotationManager(parent);
					return;
				}
				else
					rotationManager(parent);
		}

		//if it isn't a case from above we just rebalance the sub-tree and continue recalculating

		if (parent->getBalanceFactor() == 2 || parent->getBalanceFactor() == -2)
		{
			rotationManager(parent);
		}

		parent = parent->getParent();


	} while ((balance_factor != 1 && balance_factor != -1) && parent != nullptr);
}

template <typename KeyType>
void AVL_tree<KeyType>::recalculateTreeHeight()
{
	this->height = this->root->getHeight() - 1;
}

template <typename KeyType>
void AVL_tree<KeyType>::recalculateNodeHeight(AVL_node<KeyType>* Node)
{
	Node->setHeight(std::max((Node->getLeft() != nullptr ? Node->getLeft()->getHeight() : NULL), (Node->getRight() != nullptr ? Node->getRight()->getHeight() : NULL)) + 1);
}

template <typename KeyType>
void AVL_tree<KeyType>::recalculateNodeBalanceFactor(AVL_node<KeyType>* Node)
{
	unsigned int balance_factor = 0;

	if (Node->getRight() != nullptr)
		balance_factor += Node->getRight()->getHeight();

	if (Node->getLeft() != nullptr)
		balance_factor -= Node->getLeft()->getHeight();

	Node->setBalanceFactor(balance_factor);
}

template <typename KeyType>
void AVL_tree<KeyType>::leftRotation(AVL_node<KeyType>* Node)
{
	AVL_node<KeyType>* NodeRight = Node->getRight();
	Node->setRight(NodeRight->getLeft());

	if (NodeRight->getLeft() != nullptr)
		NodeRight->getLeft()->setParent(Node);

	NodeRight->setParent(Node->getParent());

	if (Node->getParent() == nullptr)
		this->root = NodeRight;
	else
	{
		if (Node == Node->getParent()->getLeft())
			Node->getParent()->setLeft(NodeRight);
		else
			Node->getParent()->setRight(NodeRight);
	}

	NodeRight->setLeft(Node);
	Node->setParent(NodeRight);

	if (NodeRight->getRight() != nullptr)
		recalculateNodeBalanceFactor(NodeRight->getRight());
	recalculateNodeHeight(Node);
	recalculateNodeBalanceFactor(Node);
	recalculateNodeHeight(NodeRight);
	recalculateNodeBalanceFactor(NodeRight);
}

template <typename KeyType>
void AVL_tree<KeyType>::rightRotation(AVL_node<KeyType>* Node)
{
	AVL_node<KeyType>* NodeLeft = Node->getLeft();
	Node->setLeft(NodeLeft->getRight());

	if (NodeLeft->getRight() != nullptr)
		NodeLeft->getRight()->setParent(Node);

	NodeLeft->setParent(Node->getParent());

	if (Node->getParent() == nullptr)
		this->root = NodeLeft;
	else
	{
		if (Node == Node->getParent()->getRight())
			Node->getParent()->setRight(NodeLeft);
		else
			Node->getParent()->setLeft(NodeLeft);
	}

	NodeLeft->setRight(Node);
	Node->setParent(NodeLeft);

	if (NodeLeft->getLeft() != nullptr)
		recalculateNodeBalanceFactor(NodeLeft->getLeft());
	recalculateNodeHeight(Node);
	recalculateNodeBalanceFactor(Node);
	recalculateNodeHeight(NodeLeft);
	recalculateNodeBalanceFactor(NodeLeft);
}

template <typename KeyType>
void AVL_tree<KeyType>::rotationManager(AVL_node<KeyType>* Node)
{
	if (Node == nullptr)
		return;

	if (Node->getBalanceFactor() == 2)
	{
		if (Node->getRight() == nullptr)
			return;

		if (Node->getRight()->getBalanceFactor() == 1 || Node->getRight()->getBalanceFactor() == 0)
		{
			leftRotation(Node);
			return;
		}

		if (Node->getRight()->getBalanceFactor() == -1)
		{
			rightRotation(Node->getRight());
			leftRotation(Node);
			return;
		}
	}

	if (Node->getBalanceFactor() == -2)
	{
		if (Node->getLeft() == nullptr)
			return;

		if (Node->getLeft()->getBalanceFactor() == -1 || Node->getLeft()->getBalanceFactor() == 0)
		{
			rightRotation(Node);
			return;
		}

		if (Node->getLeft()->getBalanceFactor() == 1)
		{
			leftRotation(Node->getLeft());
			rightRotation(Node);
			return;
		}
	}
}

template <typename KeyType>
AVL_node<KeyType>* AVL_tree<KeyType>::getPredecessor(AVL_node<KeyType>* Node)
{
	if (Node == nullptr)
		return nullptr;

	if (Node->getLeft() != nullptr)
	{
		if (Node->getLeft()->getRight() == nullptr)
			return Node->getLeft();
		else
		{
			AVL_node<KeyType>* current = Node->getLeft()->getRight();;
			AVL_node<KeyType>* child = current->getRight();

			while (child != nullptr)
			{
				current = child;
				child = child->getRight();
			}

			return current;
		}
	}
	else
	{
		AVL_node<KeyType>* current = Node;
		AVL_node<KeyType>* parent = Node->getParent();

		while (parent != nullptr && parent->getRight() != current)
		{
			current = parent;
			parent = parent->getParent();
		}

		return parent;
	}
}

template <typename KeyType>
AVL_node<KeyType>* AVL_tree<KeyType>::getSuccessor(AVL_node<KeyType>* Node)
{
	if (Node == nullptr)
		return nullptr;

	if (Node->getRight() != nullptr)
	{
		if (Node->getRight()->getLeft() == nullptr)
			return Node->getRight();
		else
		{
			AVL_node<KeyType>* current = Node->getRight()->getLeft();
			AVL_node<KeyType>* child = current->getLeft();

			while (child != nullptr)
			{
				current = child;
				child = child->getLeft();
			}

			return current;
		}
	}
	else
	{
		AVL_node<KeyType>* current = Node;
		AVL_node<KeyType>* parent = Node->getParent();

		while (parent != nullptr && parent->getLeft() != current)
		{
			current = parent;
			parent = parent->getParent();
		}

		return parent;
	}
}

template <typename KeyType>
void AVL_tree<KeyType>::transplant(AVL_node<KeyType>* receiver, AVL_node<KeyType>* giver)
{
	if (receiver == nullptr)
		return;

	if (receiver->getParent() == nullptr)
		this->root = giver;
	else
		if (receiver->getParent()->getLeft() == receiver)
			receiver->getParent()->setLeft(giver);
		else
			receiver->getParent()->setRight(giver);

	if (giver != nullptr)
		giver->setParent(receiver->getParent());
}

template <typename KeyType>
void reRank(AVL_node<KeyType>* root)
{
	if (root == nullptr)
		return;

	stack<AVL_node<KeyType>*> nodeStack;
	AVL_node<KeyType>* currentNode = root;

	unsigned int rank = 1;

	while (nodeStack.empty() == false || currentNode != nullptr)
	{
		if (currentNode != nullptr)
		{
			nodeStack.push(currentNode);

			currentNode = currentNode->getRight();
		}
		else
		{
			currentNode = nodeStack.top()->getKey();
			nodeStack.pop();

			currentNode->setRank(rank);
			rank++;

			currentNode = currentNode->getLeft();
		}
	}
}

template <typename KeyType>
void AVL_tree<KeyType>::rankManager()
{
	if (ranked == false)
	{
		reRank(this->root);
		this->ranked = true;
	}
	else
		return;
}

template <typename KeyType>
AVL_tree<KeyType>::AVL_tree()
{
	this->root = nullptr;
	this->size = 0;
	this->height = 0;
	ranked = false;
}

template <typename KeyType>
AVL_tree<KeyType>::AVL_tree(KeyType key)
{
	this->root = new AVL_node<KeyType>(key);
	this->size = 1;
	this->height = 0;
	this->ranked = false;
}

template <typename KeyType>
AVL_tree<KeyType>::~AVL_tree()
{
	clear(root);
}

template <typename KeyType>
void AVL_tree<KeyType>::setRoot(AVL_node<KeyType>* Node)
{
	this->root = Node;
}

template <typename KeyType>
AVL_node<KeyType>* AVL_tree<KeyType>::getRoot()
{
	return this->root;
}

template <typename KeyType>
void AVL_tree<KeyType>::insert(KeyType key)
{
	AVL_node<KeyType>* parent = nullptr;
	AVL_node<KeyType>* current = this->root;

	while (current != nullptr)
	{
		parent = current;

		if (key < current->getKey())
			current = current->getLeft();
		else
			if (key > current->getKey())
				current = current->getRight();
			else
				return;
	}

	AVL_node<KeyType>* newNode = new AVL_node<KeyType>(key);

	newNode->setParent(parent);

	if (parent == nullptr)
	{
		this->root = newNode;
		this->size++;
		recalculateTreeHeight();
		return;
	}
	else
		if (key < parent->getKey())
			parent->setLeft(newNode);
		else
			parent->setRight(newNode);

	this->size++;
	recalculateHeightAndBalanceFactorAtInsertion(newNode);
	recalculateTreeHeight();
	this->ranked = false;
}

template <typename KeyType>
void AVL_tree<KeyType>::erase(KeyType key)
{
	AVL_node<KeyType>* parent = nullptr;
	AVL_node<KeyType>* current = this->root;

	while (current != nullptr)
	{
		if (key == current->getKey())
			break;
		else
		{
			parent = current;

			if (key < current->getKey())
				current = current->getLeft();
			else
				current = current->getRight();
		}
	}
	if (current == nullptr)
		return;

	AVL_node<KeyType>* successor;
	if (getSuccessor(current) != nullptr)
		successor = getSuccessor(current);
	else
		successor = nullptr;

	if (current->getLeft() == nullptr)
	{
		transplant(current, current->getRight());
		recalculateHeightAndBalanceFactorAtErasion(parent, successor);
	}
	else if (current->getRight() == nullptr)
	{
		transplant(current, current->getLeft());
		recalculateHeightAndBalanceFactorAtErasion(parent, successor);
	}
	else
	{
		if (current == root)
		{
			AVL_node<KeyType>* predecessor = getPredecessor(current);

			if (current->getLeft() != predecessor)
			{
				transplant(predecessor, predecessor->getLeft());
				predecessor->setLeft(current->getLeft());
				current->getLeft()->setParent(predecessor);
			}

			transplant(current, predecessor);
			predecessor->setRight(current->getRight());
			current->getRight()->setParent(predecessor);

			recalculateNodeHeight(predecessor);
			recalculateNodeBalanceFactor(predecessor);
			if (predecessor->getLeft() != nullptr)
			{
				recalculateNodeHeight(predecessor->getLeft());
				recalculateNodeBalanceFactor(predecessor->getLeft());
				recalculateHeightAndBalanceFactorAtErasion(predecessor->getLeft(), nullptr);
			}
		}
		else
		{
			if (current->getRight() != successor)
			{
				transplant(successor, successor->getRight());
				successor->setRight(current->getRight());
				current->getRight()->setParent(successor);
			}

			transplant(current, successor);
			successor->setLeft(current->getLeft());
			current->getLeft()->setParent(successor);

			recalculateNodeHeight(successor);
			recalculateNodeBalanceFactor(successor);
			recalculateHeightAndBalanceFactorAtErasion(successor->getParent(), successor);
		}
	}
	delete current;

	this->size--;
	recalculateTreeHeight();
	this->ranked = false;
}

template <typename KeyType>
void AVL_tree<KeyType>::clear(AVL_node<KeyType>* root)
{
	if (root == nullptr)
		return;

	stack<AVL_node<KeyType>*> nodeStack;
	AVL_node<KeyType>* lastVisitedNode = nullptr;

	while (!nodeStack.empty() || root != nullptr)
	{
		if (root != nullptr)
		{
			nodeStack.push(root);
			nodeStack.push(root);
			root = root->getLeft();
		}
		else
		{
			root = nodeStack.top()->getKey();
			nodeStack.pop();

			if (!nodeStack.empty() && nodeStack.top()->getKey() == root)
				root = root->getRight();
			else
			{
				AVL_node<KeyType>* temp = root;
				root = nullptr;

				if (temp != nullptr)
				{
					lastVisitedNode = temp;
					delete temp;
				}
			}
		}
	}

	this->root = nullptr;
	this->size = 0;
	this->height = 0;
}

template <typename KeyType>
void AVL_tree<KeyType>::postorder(AVL_node<KeyType>* root)
{
	if (root == nullptr)
		return;

	stack<AVL_node<KeyType>*> nodeStack;
	AVL_node<KeyType>* lastVisitedNode = nullptr;

	while (!nodeStack.empty() || root != nullptr)
	{
		if (root != nullptr)
		{
			nodeStack.push(root);
			nodeStack.push(root);
			root = root->getLeft();
		}
		else
		{
			root = nodeStack.top()->getKey();
			nodeStack.pop();

			if (!nodeStack.empty() && nodeStack.top()->getKey() == root)
				root = root->getRight();
			else
			{
				std::cout << root->getKey() << " ";
				root = nullptr;
			}
		}
	}
}

template <typename KeyType>
void AVL_tree<KeyType>::inorder(AVL_node<KeyType>* root)
{
	if (root == nullptr)
		return;

	stack<AVL_node<KeyType>*> nodeStack;
	AVL_node<KeyType>* currentNode = root;

	while (nodeStack.empty() == false || currentNode != nullptr)
	{
		if (currentNode != nullptr)
		{
			nodeStack.push(currentNode);

			currentNode = currentNode->getLeft();
		}
		else
		{
			currentNode = nodeStack.top()->getKey();
			nodeStack.pop();
			std::cout << currentNode->getKey() << " ";

			currentNode = currentNode->getRight();
		}
	}
}

template <typename KeyType>
void AVL_tree<KeyType>::findNthNode(unsigned int N)
{
	if (this->ranked == false)
		rankManager();

	if (N > this->size)
		return;

	AVL_node<KeyType>* current = root;

	while (current->getRank() != N)
	{
		if (N > current->getRank())
			current = current->getLeft();
		else
			current = current->getRight();
	}

	std::cout << current->getKey() << std::endl;
}

template <typename KeyType>
void AVL_tree<KeyType>::gradesInBetween(KeyType begin, KeyType end)
{
	AVL_node<KeyType>* current = root;

	if (current == nullptr)
		return;

	queue<AVL_node<KeyType>*> order;
	order.push(current);

	unsigned int numberOfGrades = 0;

	while (order.empty() == false)
	{
		float currentGrade = order.front()->getKey()->getKey();

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

