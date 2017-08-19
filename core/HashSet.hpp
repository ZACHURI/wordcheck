// HashSet.hpp
//
// ICS 46 Spring 2017
// Project #3: Set the Controls for the Heart of the Sun
//
// A HashSet is an implementation of a Set that is a separately-chained
// hash table, implemented as a dynamically-allocated array of linked
// lists.  At any given time, the HashSet has a "size" indicating
// how many elements are stored within it, along with a "capacity"
// indicating the size of the array.
//
// As elements are added to the HashSet and the proportion of the HashSet's
// size to its capacity exceeds 0.8 (i.e., there are more than 80% as many
// elements as there are array cells), the HashSet should be resized so
// that it is twice as large as it was before.
//
// You are not permitted to use the containers in the C++ Standard Library
// (such as std::vector, std::list, or std::array).  Instead, you'll need
// to use a dynamically-allocated array and your own linked list
// implementation; the linked list doesn't have to be its own class,
// though you can do that, if you'd like.

#ifndef HASHSET_HPP
#define HASHSET_HPP

#include <functional>
#include "Set.hpp"



template <typename T>
class HashSet : public Set<T>
{
public:
    // The default capacity of the HashSet before anything has been
    // added to it.
    static constexpr unsigned int DEFAULT_CAPACITY = 10;

    // A HashFunction 
    typedef std::function<unsigned int(const T&)> HashFunction;

public:
    // Initializes a HashSet to be empty, so that it will use the given
    // hash function whenever it needs to hash an element.
    HashSet(HashFunction hashFunction);

    // Cleans up the HashSet so that it leaks no memory.
    virtual ~HashSet();

    // Initializes a new HashSet to be a copy of an existing one.
    HashSet(const HashSet& s);

    // Initializes a new HashSet whose contents are moved from an
    // expiring one.
    HashSet(HashSet&& s);

    // Assigns an existing HashSet into another.
    HashSet& operator=(const HashSet& s);

    // Assigns an expiring HashSet into another.
    HashSet& operator=(HashSet&& s);


    // isImplemented() should be modified to return true if you've
    // decided to implement a HashSet, false otherwise.
    virtual bool isImplemented() const;


    // add() adds an element to the set.  If the element is already in the set,
    // this function has no effect.  This function triggers a resizing of the
    // array when the ratio of size to capacity would exceed 0.8.  In the case
    // where the array is resized, this function runs in linear time (with
    // respect to the number of elements, assuming a good hash function);
    // otherwise, it runs in constant time (again, assuming a good hash
    // function).
    virtual void add(const T& element);


    // contains() returns true if the given element is already in the set,
    // false otherwise.  This function runs in constant time (with respect
    // to the number of elements, assuming a good hash function).
    virtual bool contains(const T& element) const;


    // size() returns the number of elements in the set.
    virtual unsigned int size() const;


private:
    HashFunction hashFunction;

    struct Node
    {
        T key;
        Node* next;
    };

    Node** hashtable;

    unsigned int curr_capacity;

    void copyHT(const HashSet& s);
    void destroyHT();
};



template <typename T>
HashSet<T>::HashSet(HashFunction hashFunction)
    : hashFunction{hashFunction}, hashtable{new Node*[DEFAULT_CAPACITY]{nullptr}}
{
}


template <typename T>
HashSet<T>::~HashSet()
{
    destroyHT();
}


template <typename T>
HashSet<T>::HashSet(const HashSet& s)
    : hashFunction{s.hashFunction}, hashtable{new Node*[s.curr_capacity]{nullptr}}
{
    copyHT(s);
}


template <typename T>
HashSet<T>::HashSet(HashSet&& s)
    : hashFunction{nullptr}
{
    std::swap(hashtable, s.hashtable);
}


template <typename T>
HashSet<T>& HashSet<T>::operator=(const HashSet& s)
{
    if (this != &s)
    {
        destroyHT();
        hashtable = new Node*[s.curr_capacity]{nullptr};
        copyHT(s);
        hashFunction = s.hashFunction;
        curr_capacity = s.curr_capacity;
    }
    return *this;
}


template <typename T>
HashSet<T>& HashSet<T>::operator=(HashSet&& s)
{
    std::swap(hashtable, s.hashtable);
    return *this;
}


template <typename T>
bool HashSet<T>::isImplemented() const
{
    return true;
}


template <typename T>
void HashSet<T>::add(const T& element)
{
    

    if (contains(element) == false)
    {
    	if (size()/curr_capacity > 0.8)
    	{
    		unsigned int new_capacity = curr_capacity * 2;
    		Node** new_hashtable = new Node*[new_capacity]{nullptr};
    		for ( unsigned int i=0 ; i < new_capacity; ++i)
		    {
		        Node* curr = new_hashtable[i];
		        while (curr != nullptr)
		        {
		            if (curr != nullptr)
		                new_hashtable[i] = new Node{curr->key, nullptr};
		            else
		            {
		                Node* temp = new_hashtable[i];
		                while ( temp->next != nullptr)
		                {
		                    temp = temp->next;
		                }
		                temp->next = new Node{curr->key, nullptr};

		            }
		            curr = curr->next;
		        }
		    }
		    hashtable = new_hashtable;


    	}
        unsigned int key_value = hashFunction(element);
        if (hashtable[key_value] == nullptr)
        {
        	hashtable[key_value] = new Node{element, nullptr};
        }
        else
        {
        	Node* next = hashtable[key_value];
        	hashtable[key_value] = new Node{element, next};
        }

    }
}


template <typename T>
bool HashSet<T>::contains(const T& element) const
{
    Node* curr;
    for ( unsigned int i=0; i < curr_capacity; ++i)
    {
        curr = hashtable[i];
        while (curr != nullptr)
        {
            if (curr->key == element)
                return true;
            curr = curr->next;
        }
    }
    return false;
}


template <typename T>
unsigned int HashSet<T>::size() const
{
    unsigned int count = 0;
    Node* curr;
    for ( unsigned int i=0; i < curr_capacity; ++i)
    {
        curr = hashtable[i];
        while (curr != nullptr)
        {
            ++count;
            curr = curr->next;
        }
    }
    return count;
}

template <typename T>
void HashSet<T>::copyHT(const HashSet& s)
{
    for ( unsigned int i=0 ; i < s.curr_capacity; ++i)
    {
        Node* curr = hashtable[i];
        while (curr != nullptr)
        {
            if (curr != nullptr)
                hashtable[i] = new Node{curr->key, nullptr};
            else
            {
                Node* temp = hashtable[i];
                while ( temp->next != nullptr)
                {
                    temp = temp->next;
                }
                temp->next = new Node{curr->key, nullptr};

            }
            curr = curr->next;
        }
    }
}


template <typename T>
void HashSet<T>::destroyHT()
{
    for ( unsigned int i=0 ; i < DEFAULT_CAPACITY; ++i)
    {
        Node* curr = hashtable[i];
        while (curr != nullptr)
        {
            Node* temp = curr;
            curr = curr->next;
            delete temp;
            
        }

    }

    delete[] hashtable;
}





#endif // HASHSET_HPP

