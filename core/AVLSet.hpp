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
	void addAVL(const T& element, Node*& head);
	bool containsAVL(const T& element, Node* head) const;
	void destroyAVL(Node* head);
	unsigned int sizeAVL(Node* curr) const;

	void RRrotation(Node*& head);
	void LLrotation(Node*& head);
	void RLrotation(Node*& head);
	void LRrotation(Node*& head);

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
	addAVL( element, head);
}


template <typename T>
bool AVLSet<T>::contains(const T& element) const
{
    return containsAVL(element, head);
}


template <typename T>
unsigned int AVLSet<T>::size() const
{
    return sizeAVL(head);
}


template <typename T>
bool AVLSet<T>::containsAVL(const T& element, Node* head) const
{
	if (head == nullptr)
	{
		return false;
	}
	else if ( element < head->key_value )
	{
		containsAVL(element, head->left);
	}
	else if ( element > head->key_value )
	{
		containsAVL(element, head->right);
	}
	else
	{
		return true;
	}
}

template <typename T>
void AVLSet<T>::addAVL(const T& element, Node*& head)
{
	if (head == nullptr)
	{
		head = new Node{element, nullptr, nullptr};
	}
	else if ( element < head->key_value )
	{
		addAVL(element, head->right);
		if ( sizeAVL(head->right) == sizeAVL(head->left) )
		{
			if ( element > head->right->key_value )
				RRrotation(head);
			else
				RLrotation(head);
		}
	}
	else if ( element > head->key_value )
	{
		addAVL(element, head->left);
		if ( sizeAVL(head->right) == sizeAVL(head->left) )
		{
			if ( element < head->left->key_value )
				LLrotation(head);
			else
				LRrotation(head);
		}
	}
	

}

template <typename T>
void AVLSet<T>::RRrotation(Node*& head)
{
	Node* temp;
	temp = head->right;
	head->right = temp->left;
	temp->left = head;
	head = temp;

}

template <typename T>
void AVLSet<T>::LLrotation(Node*& head)
{
	Node* temp;
	temp = head->left;
	head->left = temp->right;
	temp->right = head;
	head = temp;

}

template <typename T>
void AVLSet<T>::LRrotation(Node*& head)
{
	RRrotation(head->left);
	LLrotation(head);
}

template <typename T>
void AVLSet<T>::RLrotation(Node*& head)
{
	LLrotation(head->right);
	RRrotation(head);
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
void AVLSet<T>::destroyAVL(Node* head)
{
	if (head != nullptr)
	{
		destroyAVL(head->right);
		destroyAVL(head->left);
		delete head;
	}
}


#endif // AVLSET_HPP

