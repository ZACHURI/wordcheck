// AVLSet.hpp
//
// ICS 46 Spring 2017
// Project #3: Set the Controls for the Heart of the Sun
//
// An AVLSet is an implementation of a Set that is an AVL tree, which uses
// the algorithms we discussed in lecture to maintain balance every time a
// new element is added to the set.
//
// You are not permitted to use the containers in the C++ Standard Library
// (such as std::set, std::map, or std::vector).  Instead, you'll need
// to implement your AVL tree using your own dynamically-allocated nodes,
// with pointers connecting them, and with your own balancing algorithms
// used.

#ifndef AVLSET_HPP
#define AVLSET_HPP

#include "Set.hpp"
#include <algorithm>
#include <iostream>



template <typename T>
class AVLSet : public Set<T>
{
public:
    // Initializes an AVLSet to be empty.
    AVLSet();

    // Cleans up the AVLSet so that it leaks no memory.
    virtual ~AVLSet();

    // Initializes a new AVLSet to be a copy of an existing one.
    AVLSet(const AVLSet& s);

    // Initializes a new AVLSet whose contents are moved from an
    // expiring one.
    AVLSet(AVLSet&& s);

    // Assigns an existing AVLSet into another.
    AVLSet& operator=(const AVLSet& s);

    // Assigns an expiring AVLSet into another.
    AVLSet& operator=(AVLSet&& s);


    // isImplemented() should be modified to return true if you've
    // decided to implement an AVLSet, false otherwise.
    virtual bool isImplemented() const;


    // add() adds an element to the set.  If the element is already in the set,
    // this function has no effect.  This function always runs in O(log n) time
    // when there are n elements in the AVL tree.
    virtual void add(const T& element);


    // contains() returns true if the given element is already in the set,
    // false otherwise.  This function always runs in O(log n) time when
    // there are n elements in the AVL tree.
    virtual bool contains(const T& element) const;


    // size() returns the number of elements in the set.
    virtual unsigned int size() const;


private:

	struct Node
	{
		T key_value;
		Node *left;
		Node *right;
	};
	Node *head;

	void copyAVL(Node*& newtree, Node* oldtree);
	void destroyAVL(Node* head);

	bool see(Node* curr, const T& element) const;

	unsigned int sizeAVL(Node* curr) const;
	Node* insert(Node* head, const T& element) const;

	Node* RRrotation(Node* head) const;
	Node* LLrotation(Node* head) const;


};


template <typename T>
AVLSet<T>::AVLSet()
	: head{nullptr}
{
}


template <typename T>
AVLSet<T>::~AVLSet()
{
	destroyAVL(head);
}


template <typename T>
AVLSet<T>::AVLSet(const AVLSet& s)
{
	copyAVL(head, s.head);
}


template <typename T>
AVLSet<T>::AVLSet(AVLSet&& s)
	: head{nullptr}
{
	std::swap(head, s.head);
}


template <typename T>
AVLSet<T>& AVLSet<T>::operator=(const AVLSet& s)
{
	if (this != &s)
    {
        destroyAVL(head);
        head = nullptr;
        copyAVL(head, s.head);
    }
    return *this;
}


template <typename T>
AVLSet<T>& AVLSet<T>::operator=(AVLSet&& s)
{
	std::swap(head, s.head);
    return *this;
}


template <typename T>
bool AVLSet<T>::isImplemented() const
{
    return true;
}


template <typename T>
void AVLSet<T>::add(const T& element)
{
	/*if (head == nullptr)
	{
		head = new Node{element, nullptr, nullptr};
	}
	else
	{
		Node* temp  = head;
		Node* res = head;
		while(temp != nullptr)
		{
			if (temp->key_value == element) return;
			else if (temp->key_value > element)
			{

				res = temp;
				temp = temp->left;
			}
			else if (temp->key_value < element)
			{
				res = temp;
				temp = temp->right;
			}
		}
		if (res->key_value > element)
		{
			res->left = new Node{element, nullptr, nullptr};
			if ( sizeAVL(res->right) == sizeAVL(res->left) )
			{
				if ( element > res->right->key_value )
				{
					RRrotation(res);
				}
				else
				{
					RLrotation(res);
				}
			}

		}
		if (res->key_value < element) 
		{
			res->right = new Node{element, nullptr, nullptr};
			if ( sizeAVL(res->right) == sizeAVL(res->left) )
			{
				if ( element < res->left->key_value )
				{
					LLrotation(res);
				}
				else
				{
					LRrotation(res);
				}
			}
		}
	}*/
	Node* temp = head;
	head = insert(temp, element);
}

template <typename T>
typename AVLSet<T>::Node* AVLSet<T>::insert(Node* head, const T& element) const
{
	if (head == nullptr)
	{
		head = new Node{element, nullptr, nullptr};
	}
	if (head->key_value > element)
	{
		head->left = insert(head->left, element);
	}
	else if (head->key_value < element)
	{
		head->right = insert(head->right, element);
	}
	else
		return head;

	int dif;
	dif = sizeAVL(head->left) - sizeAVL(head->right);
	if (head->left)
	{
		if (element < head->left->key_value && dif>1) return RRrotation(head);
		if (element > head->left->key_value && dif>1)
		{
			head->left = LLrotation(head->left);
			return RRrotation(head);
		}
	}
	if (head->right)
	{
		if (element > head->right->key_value && dif<-1) return LLrotation(head);
		if (element < head->right->key_value && dif<-1)
		{
			head->right = RRrotation(head->right);
			return LLrotation(head);
		}
	}
	return head;
}


template <typename T>
bool AVLSet<T>::contains(const T& element) const
{
    /*


    Node* curr = head;
	if (curr == nullptr) return false;
	while (curr != nullptr)
	{
	    if (curr->key_value == element)
		{
			return true;
		}
		
		else if ( head->key_value > element )
		{
			curr = curr -> left;
		}
		else
		{
			curr = curr -> right;
		}
		
	}
	return false;*/

	return see(head, element);
}


template <typename T>
unsigned int AVLSet<T>::size() const
{
    return sizeAVL(head);
}

template <typename T>
typename AVLSet<T>::Node* AVLSet<T>::RRrotation(Node* head) const
{

	Node* temp;
	Node* temp2;
	temp = head->left;
	temp2 = temp->right;
	temp->right = head;
	head->left = temp2;
	return temp;

}

template <typename T>
typename AVLSet<T>::Node* AVLSet<T>::LLrotation(Node* head) const
{
	Node* temp;
	Node* temp2;
	temp = head->right;
	temp2 = temp->left;
	temp->left = head;
	head->right = temp2;
	return temp;

}







template <typename T>
void AVLSet<T>::copyAVL(Node*& newtree, Node* oldtree)
{
	if ( oldtree == nullptr )
	{
		newtree = nullptr;
	}
	else
	{
		newtree = new Node{oldtree->key_value, oldtree->left, oldtree->right};
		copyAVL(newtree->left, oldtree->left);
		copyAVL(newtree->right, newtree->right);
	}
}

template <typename T>
unsigned int AVLSet<T>::sizeAVL(Node* curr) const
{
    if (curr == nullptr)
    	return 0;
    else
    	return (sizeAVL(curr->left) + sizeAVL(curr->right) + 1);
}

template <typename T>
bool AVLSet<T>::see(Node* curr, const T& element) const
{
	if ( curr == nullptr )
	{
		
	}
	else
	{
		if (curr->key_value == element)
		{
			return true;
		}
		if (curr->key_value > element)
		{
			if (see(curr->left, element) == true) return true;
		}
		else
		{
			if (see(curr->right, element) == true) return true;
		}
	}
	return false;

}

template <typename T>
void AVLSet<T>::destroyAVL(Node* curr)
{
	if (!curr)
	{
		return;


	}
	destroyAVL(curr->right);
	destroyAVL(curr->left);
	delete curr;
}


#endif // AVLSET_HPP

