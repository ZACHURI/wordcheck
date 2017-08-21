// BSTSet.hpp
//
// ICS 46 Spring 2017
// Project #3: Set the Controls for the Heart of the Sun
//
// A BSTSet is an implementation of a Set that is a binary search tree,
// albeit one that makes no attempt to remain balanced.  (You explicitly
// should not do any balancing here; do that in AVLSet instead, if you
// choose to work on that one.)
//
// You are not permitted to use the containers in the C++ Standard Library
// (such as std::set, std::map, or std::vector).  Instead, you'll need
// to implement your binary search tree using your own dynamically-allocated
// nodes, with pointers connecting them.

#ifndef BSTSET_HPP
#define BSTSET_HPP

#include "Set.hpp"
#include <algorithm>
#include <iostream>



template <typename T>
class BSTSet : public Set<T>
{
public:
    // Initializes a BSTSet to be empty.
    BSTSet();

    // Cleans up the BSTSet so that it leaks no memory.
    virtual ~BSTSet();

    // Initializes a new BSTSet to be a copy of an existing one.
    BSTSet(const BSTSet& s);

    // Initializes a new BSTSet whose contents are moved from an
    // expiring one.
    BSTSet(BSTSet&& s);

    // Assigns an existing BSTSet into another.
    BSTSet& operator=(const BSTSet& s);

    // Assigns an expiring BSTSet into another.
    BSTSet& operator=(BSTSet&& s);


    // isImplemented() should be modified to return true if you've
    // decided to implement a BSTSet, false otherwise.
    virtual bool isImplemented() const;


    // add() adds an element to the set.  If the element is already in the set,
    // this function has no effect.  This function runs in O(n) time when there
    // are n elements in the binary search tree, and is sometimes as fast as
    // O(log n) (when the tree is relatively balanced).
    virtual void add(const T& element);


    // contains() returns true if the given element is already in the set,
    // false otherwise.  This function runs in O(n) time when there
    // are n elements in the binary search tree, and is sometimes as fast as
    // O(log n) (when the tree is relatively balanced).
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


	Node* head;

	void copyBST(Node*& newtree, Node* oldtree);
	void destroyBST(Node* head);
	bool see(Node* curr, const T& element) const;

	unsigned int size(Node* curr) const;


};


template <typename T>
BSTSet<T>::BSTSet()
	: head{nullptr}
{

}


template <typename T>
BSTSet<T>::~BSTSet()
{
	destroyBST(head);
	
}


template <typename T>
BSTSet<T>::BSTSet(const BSTSet& s)
	: head{nullptr}
{
	copyBST(head, s.head);
}


template <typename T>
BSTSet<T>::BSTSet(BSTSet&& s)
	: head{nullptr}
{
	std::swap(head, s.head);
}


template <typename T>
BSTSet<T>& BSTSet<T>::operator=(const BSTSet& s)
{
	if (this != &s)
    {
        destroyBST(head);
        head = nullptr;
        copyBST(head, s.head);
    }
    return *this;
}


template <typename T>
BSTSet<T>& BSTSet<T>::operator=(BSTSet&& s)
{
	std::swap(head, s.head);
    return *this;
}


template <typename T>
bool BSTSet<T>::isImplemented() const
{
    return true;
}


template <typename T>
void BSTSet<T>::add(const T& element)
{
	if (head == nullptr)
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
		if (res->key_value > element) res->left = new Node{element, nullptr, nullptr};
		if (res->key_value < element) res->right = new Node{element, nullptr, nullptr};
	}
	
}


template <typename T>
bool BSTSet<T>::contains(const T& element) const
{
	/*Node* curr = head;

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
unsigned int BSTSet<T>::size() const
{
    return size(head);
}




template <typename T>
unsigned int BSTSet<T>::size(Node* curr) const
{
    if (curr == nullptr)
    {
    	return 0;
    }
    else
    	return (size(curr->left) + size(curr->right) + 1);
}

template <typename T>
void BSTSet<T>::copyBST(Node*& newtree, Node* oldtree)
{
	if ( oldtree == nullptr )
	{
		newtree = nullptr;
	}
	else
	{
		newtree = new Node{oldtree->key_value, oldtree->left, oldtree->right};
		copyBST(newtree->left, oldtree->left);
		copyBST(newtree->right, newtree->right);
	}
}

template <typename T>
bool BSTSet<T>::see(Node* curr, const T& element) const
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
void BSTSet<T>::destroyBST(Node* curr)
{
	if (!curr)
	{
		return;


	}
	destroyBST(curr->right);
	destroyBST(curr->left);
	delete curr;
}


#endif // BSTSET_HPP

