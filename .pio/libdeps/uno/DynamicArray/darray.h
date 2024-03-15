// Author:  Chris Yan
// Date:    March 9, 2011
// File:    darray.h
// Desc:    Header for the darray (dynamicalrific array) class.
/////////////////////////////////////////////////////////////////////////

#ifndef _darray
#define _darray

#include <iostream>

template<typename T>
class darray
{
public:
        // Constructors
        
    // Pre: none
    // Post: default constructor is called and default darray results
    darray();
    
    // Pre: darray passed to the copy constructor must have = operator
    // Post: darray passed is copied into the new darray
    darray( const darray &);

        // Destructor
        
    // Pre: computer is turned on
    // Post: darray is tilded and destroyed
    ~darray();
    
        // Constant members
    
    // Pre: none
    // Post: length of darray is returned
    unsigned size() const { return length; }
    
    // Pre: none
    // Post: total capacity of darray is returned
    unsigned capacity() const { return cap; }
    
    // Pre: index accessed must exist or cassert will fail
    // Post: a reference to the value at that index is returned
    const T& operator [] ( unsigned int ) const;

        // Modifiers
        
    // Pre: darray must have a length > 0, otherwise cassert will fail
    // Post: length of darray is decreased by one
    void pop_back();
    
    // Pre: Value passed must be a valid type and have = operator assigned
    // Post: darray is expanded and the type, T, is added to the end of the darray
    void push_back( const T & );
    
    // Pre: index accessed must exist or cassert will fail
    // Post: a non-constant reference to the value at that index is returned
    T& operator [] ( unsigned int );
    
    // Pre: none
    // Post: amount of type * unsigned is reserved in memory
    void reserve(unsigned);
    
    // Pre: darray must have more than one item or memory-out-of-bounds thingy will go nuts on you
    // Post: list is sorted... ... ...backwards
    void sort( darray& );
    
    // Pre: Parameters one and two should most functionally not equal each other...
    // Post: Values at param 1 and param 2 are exchanged and proper locations in the darray are exchanged as well
    void swap( T&, T& );

        // Operators
    
    // Pre: both sides must be valid darrays?
    // Post: darray1 now ='s darray2. Huzzah!
    darray& operator = (const darray&);

        // Friends
    // darrays have no friends, instead, they hold work-relationships with various types
    
private:

    // length and capacity of the darray
    unsigned length, cap;
    // Pointer to the array of types, T.
    T* arr;
    
};

// template include
#include "darray.cpp"

// #endif
#endif