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

	int av_size;
	struct Node
	{
		int key_value;
		Node *left;
		Node *right;
	};
	Node *head;

	void copyAVT(Node*& newtree, Node* oldtree);
	void addAVT(const T& element, Node*& head);
	bool containsAVT(const T& element, Node*& head)
	void deleteAVT(Node* head);

};


template <typename T>
AVLSet<T>::AVLSet()
	: head{nullptr}, av_size{0}
{
	
}


template <typename T>
AVLSet<T>::~AVLSet()
{
	deleteAVT(head);
}


template <typename T>
AVLSet<T>::AVLSet(const AVLSet& s)
{
	copyAVT(head, s.head);
}


template <typename T>
AVLSet<T>::AVLSet(AVLSet&& s)
{
	copyAVT(head, s.head);
}


template <typename T>
AVLSet<T>& AVLSet<T>::operator=(const AVLSet& s)
{
	av_size = s.av_size;
	copyAVT(head, s.head);
    return *this;
}


template <typename T>
AVLSet<T>& AVLSet<T>::operator=(AVLSet&& s)
{
	av_size = s.av_size;
	copyAVT(head, s.head);
    return *this;
}


template <typename T>
bool AVLSet<T>::isImplemented() const
{
    return false;
}


template <typename T>
void AVLSet<T>::add(const T& element)
{
	addAVT( element, head);
}


template <typename T>
bool AVLSet<T>::contains(const T& element) const
{
    return false;
}


template <typename T>
unsigned int AVLSet<T>::size() const
{
    return av_size;
}


template <typename T>
void addAVT(const T& element, Node*& head)
{
	if (head == nullptr)
	{
		head = new Node{element, nullptr, nullptr};
		++bs_size;
	}
	else if ( element < head->key )
	{
		addAVT(element, head->left);
	}
	else if ( element > head->key )
	{
		addAVT(element, head->right);
	}

}

template <typename T>
bool containsAVT(const T& element, Node*& head)
{
	if (head == nullptr)
	{
		return false;
	}
	else if ( element < head->key )
	{
		addAVT(element, head->left);
	}
	else if ( element > head->key )
	{
		addAVT(element, head->right);
	}
	else
	{
		return true;
	}

}

template <typename T>
void BSTSet<T>::copyAVT(Node*& newtree, Node* oldtree)
{
	if ( oldtree == nullptr )
	{
		newtree = nullptr;
	}
	else
	{
		newtree = new Node{oldtree->key_value, oldtree->left, oldtree->right};
		copyAVT(newtree->left, oldtree->left);
		copyAVT(newtree->right, newtree->right);
	}

template <typename T>
void BSTSet<T>::deleteAVT(Node* head)
{
	if (head != nullptr)
	{
		deleteAVT(head->right);
		deleteAVT(head->left);
		delete head;
	}
}


#endif // AVLSET_HPP

