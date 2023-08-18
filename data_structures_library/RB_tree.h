#pragma once

#include <iostream>
#include "RB_node.h"
#include "stack.h"
#include "queue.h"

template <typename KeyType>
class RB_tree
{
protected:

	RB_node<KeyType>* root;
	unsigned int size;
	bool ranked;

	RB_node<KeyType>* find(KeyType);

	void recolourAtInsertion(RB_node<KeyType>*);
	void recolourAtErasion(RB_node<KeyType>*);

	void leftRotation(RB_node<KeyType>*);
	void rightRotation(RB_node<KeyType>*);
	

	RB_node<KeyType>* getPredecessor(RB_node<KeyType>*);
	RB_node<KeyType>* getSuccessor(RB_node<KeyType>*);

	void transplant(RB_node<KeyType>*, RB_node<KeyType>*);

	void rankManager();

public:

	RB_tree();
	RB_tree(KeyType);
	~RB_tree();

	void setRoot(RB_node<KeyType>*);
	RB_node<KeyType>* getRoot();

	void insert(KeyType);
	void erase(KeyType);
	void clear(RB_node<KeyType>*);

	void postorder(RB_node<KeyType>*);
	void inorder(RB_node<KeyType>*);
	void findNthNode(unsigned int);
	void gradesInBetween(KeyType, KeyType);
};

template <typename KeyType>
RB_node<KeyType>* RB_tree<KeyType>::find(KeyType key)
{
	RB_node<KeyType>* parent = nullptr;
	RB_node<KeyType>* current = this->root;

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
void RB_tree<KeyType>::recolourAtInsertion(RB_node<KeyType>* Node)
{
	RB_node<KeyType>* current = Node;

	while(current->getParent()!=nullptr && current->getParent()->getColour()=='r')
	{
		RB_node<KeyType>* uncle;

		if (current->getParent()->getParent()->getLeft() == current->getParent())
		{
			//first case + second case

			uncle = current->getParent()->getParent()->getRight();

			if (uncle)
			{
				if (uncle->getColour() == 'r')
				{
					current->getParent()->setColour('b');
					uncle->setColour('b');
					current->getParent()->getParent()->setColour('r');

					current = current->getParent()->getParent();
				}
			}
			else if ((uncle!=nullptr && uncle->getColour() == 'b') || uncle==nullptr)
			{
				if(current==current->getParent()->getRight())
				{
					current = current->getParent();
					leftRotation(current);
				}

				//third case

				current->setColour('b');
				current->getParent()->getParent()->setColour('r');
				rightRotation(current->getParent()->getParent());
			}
		}
		else
		{
			//first case + second case

			uncle = current->getParent()->getParent()->getLeft();

			if (uncle)
			{
				if (uncle->getColour() == 'r')
				{
					current->getParent()->setColour('b');
					uncle->setColour('b');
					current->getParent()->getParent()->setColour('r');

					current = current->getParent()->getParent();
				}
			}
			else if ((uncle != nullptr && uncle->getColour() == 'b') || uncle == nullptr)
			{
				if (current == current->getParent()->getLeft())
				{
					current = current->getParent();
					rightRotation(current);
				}

				//third case

				current->setColour('b');
				current->getParent()->getParent()->setColour('r');
				leftRotation(current->getParent()->getParent());
			}
		}
	}

	this->root->setColour('b');
}

template <typename KeyType>
void RB_tree<KeyType>::recolourAtErasion(RB_node<KeyType>* Node)
{
	RB_node<KeyType>* current=Node;

	if (current == nullptr)
		return;

	while (current != root && current->getColour() == 'b')
	{
		RB_node<KeyType>* brother;

		if (current == current->getParent()->getLeft())
		{
			brother = current->getParent()->getRight();

			if(brother)
			{
				//first case

				if (brother->getColour() == 'r')
				{
					brother->setColour('b');
					current->getParent()->setColour('r');
					rightRotation(current->getParent());
					brother = current->getParent()->getRight();
				}

				//second case + third case

				if ((brother->getLeft()->getColour() == 'b' || brother->getLeft() == nullptr) && (brother->getRight()->getColour() == 'b' || brother->getRight() == nullptr))
				{
					brother->setColour('r');
					current = current->getParent();
				}
				else if(brother->getLeft() != nullptr && (brother->getRight()->getColour() == 'b' || brother->getRight() == nullptr))
				{
					brother->getLeft()->setColour('b');
					brother->setColour('r');
					rightRotation(brother);
					brother = current->getParent()->getRight();
				}

				//fourth case

				brother->setColour(current->getParent()->getColour());
				current->getParent()->setColour('b');
				if(brother->getRight())
					brother->getRight()->setColour('b');
				leftRotation(current->getParent());
				current = root;
			}
		}
		else
		{
			brother = current->getParent()->getRight();

			if (brother)
			{
				//first case

				if (brother->getColour() == 'r')
				{
					brother->setColour('b');
					current->getParent()->setColour('r');
					leftRotation(current->getParent());
					brother = current->getParent()->getLeft();
				}

				//second case + third case

				if ((brother->getLeft()->getColour() == 'b' || brother->getLeft() == nullptr) && (brother->getRight()->getColour() == 'b' || brother->getRight() == nullptr))
				{
					brother->setColour('r');
					current = current->getParent();
				}
				else if ((brother->getLeft()->getColour() == 'b' || brother->getLeft() == nullptr) && brother->getRight() != nullptr)
				{
					brother->getRight()->setColour('b');
					brother->setColour('r');
					leftRotation(brother);
					brother = current->getParent()->getLeft();
				}

				//fourth case

				brother->setColour(current->getParent()->getColour());
				current->getParent()->setColour('b');
				if (brother->getLeft())
					brother->getLeft()->setColour('b');
				rightRotation(current->getParent());
				current = root;
			}
		}
	}

	//zeroth case

	current->setColour('b');
}

template <typename KeyType>
void RB_tree<KeyType>::leftRotation(RB_node<KeyType>* Node)
{
	RB_node<KeyType>* NodeRight = Node->getRight();
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
}

template <typename KeyType>
void RB_tree<KeyType>::rightRotation(RB_node<KeyType>* Node)
{
	RB_node<KeyType>* NodeLeft = Node->getLeft();
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
}

template <typename KeyType>
RB_node<KeyType>* RB_tree<KeyType>::getPredecessor(RB_node<KeyType>* Node)
{
	if (Node == nullptr)
		return nullptr;

	if (Node->getLeft() != nullptr)
	{
		if (Node->getLeft()->getRight() == nullptr)
			return Node->getLeft();
		else
		{
			RB_node<KeyType>* current = Node->getLeft()->getRight();;
			RB_node<KeyType>* child = current->getRight();

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
		RB_node<KeyType>* current = Node;
		RB_node<KeyType>* parent = Node->getParent();

		while (parent != nullptr && parent->getRight() != current)
		{
			current = parent;
			parent = parent->getParent();
		}

		return parent;
	}
}

template <typename KeyType>
RB_node<KeyType>* RB_tree<KeyType>::getSuccessor(RB_node<KeyType>* Node)
{
	if (Node == nullptr)
		return nullptr;

	if (Node->getRight() != nullptr)
	{
		if (Node->getRight()->getLeft() == nullptr)
			return Node->getRight();
		else
		{
			RB_node<KeyType>* current = Node->getRight()->getLeft();
			RB_node<KeyType>* child = current->getLeft();

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
		RB_node<KeyType>* current = Node;
		RB_node<KeyType>* parent = Node->getParent();

		while (parent != nullptr && parent->getLeft() != current)
		{
			current = parent;
			parent = parent->getParent();
		}

		return parent;
	}
}

template <typename KeyType>
void RB_tree<KeyType>::transplant(RB_node<KeyType>* receiver, RB_node<KeyType>* giver)
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
void reRank(RB_node<KeyType>* root)
{
	if (root == nullptr)
		return;

	stack<RB_node<KeyType>*> nodeStack;
	RB_node<KeyType>* currentNode = root;

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
void RB_tree<KeyType>::rankManager()
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
RB_tree<KeyType>::RB_tree()
{
	this->root = nullptr;
	this->size = 0;
	ranked = false;
}

template <typename KeyType>
RB_tree<KeyType>::RB_tree(KeyType key)
{
	this->root = new RB_node<KeyType>(key);
	this->size = 1;
	this->ranked = false;
}

template <typename KeyType>
RB_tree<KeyType>::~RB_tree()
{
	clear(root);
}

template <typename KeyType>
void RB_tree<KeyType>::setRoot(RB_node<KeyType>* Node)
{
	this->root = Node;
}

template <typename KeyType>
RB_node<KeyType>* RB_tree<KeyType>::getRoot()
{
	return this->root;
}

template <typename KeyType>
void RB_tree<KeyType>::insert(KeyType key)
{
	RB_node<KeyType>* parent = nullptr;
	RB_node<KeyType>* current = this->root;

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

	RB_node<KeyType>* newNode = new RB_node<KeyType>(key);

	newNode->setParent(parent);

	if (parent == nullptr)
	{
		this->root = newNode;
		this->root->setColour('b');
		this->size++;
		return;
	}
	else
		if (key < parent->getKey())
			parent->setLeft(newNode);
		else
			parent->setRight(newNode);

	this->size++;
	recolourAtInsertion(newNode);
	this->ranked = false;
}

template <typename KeyType>
void RB_tree<KeyType>::erase(KeyType key)
{
	RB_node<KeyType>* parent = nullptr;
	RB_node<KeyType>* current = this->root;

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

	RB_node<KeyType>* successor;
	if (getSuccessor(current) != nullptr)
		successor = getSuccessor(current);
	else
		successor = nullptr;

	char colourOfDeleted = current->getColour();

	if (current->getLeft() == nullptr)
	{
		transplant(current, current->getRight());

		if (colourOfDeleted == 'b')
			recolourAtErasion(current->getRight());
	}
	else if (current->getRight() == nullptr)
	{
		transplant(current, current->getLeft());

		if (colourOfDeleted == 'b')
			recolourAtErasion(current->getLeft());
	}
	else
	{
		if (successor == current->getRight() || current == root)
		{
			RB_node<KeyType>* predecessor = getPredecessor(current);

			colourOfDeleted = predecessor->getColour();

			if (current->getRight() != predecessor)
			{
				transplant(predecessor, predecessor->getLeft());
				predecessor->setLeft(current->getLeft());
				current->getLeft()->setParent(predecessor);
			}

			transplant(current, predecessor);
			predecessor->setRight(current->getRight());
			current->getRight()->setParent(current);
			predecessor->setColour(current->getColour());

			if (colourOfDeleted == 'b')
				recolourAtErasion(predecessor->getLeft());
		}
		else
		{
			colourOfDeleted = successor->getColour();

			if (current->getRight() != successor)
			{
				transplant(successor, successor->getRight());
				successor->setRight(current->getRight());
				current->getRight()->setParent(successor);
			}

			transplant(current, successor);
			successor->setLeft(current->getLeft());
			current->getLeft()->setParent(current);
			successor->setColour(current->getColour());

			if (colourOfDeleted == 'b')
				recolourAtErasion(successor->getRight());
		}
	}
	delete current;

	std::cout << colourOfDeleted << std::endl;

	this->size--;
	this->ranked = false;
}

template <typename KeyType>
void RB_tree<KeyType>::clear(RB_node<KeyType>* root)
{
	if (root == nullptr)
		return;

	stack<RB_node<KeyType>*> nodeStack;
	RB_node<KeyType>* lastVisitedNode = nullptr;

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
				RB_node<KeyType>* temp = root;
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
}

template <typename KeyType>
void RB_tree<KeyType>::postorder(RB_node<KeyType>* root)
{
	if (root == nullptr)
		return;

	stack<RB_node<KeyType>*> nodeStack;
	RB_node<KeyType>* lastVisitedNode = nullptr;

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
void RB_tree<KeyType>::inorder(RB_node<KeyType>* root)
{
	if (root == nullptr)
		return;

	stack<RB_node<KeyType>*> nodeStack;
	RB_node<KeyType>* currentNode = root;

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
void RB_tree<KeyType>::findNthNode(unsigned int N)
{
	if (this->ranked == false)
		rankManager();

	if (N > this->size)
		return;

	RB_node<KeyType>* current = root;

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
void RB_tree<KeyType>::gradesInBetween(KeyType begin, KeyType end)
{
	RB_node<KeyType>* current = root;

	if (current == nullptr)
		return;

	queue<RB_node<KeyType>*> order;
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
