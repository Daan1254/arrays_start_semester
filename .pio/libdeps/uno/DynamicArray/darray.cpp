// Author:  Chris Yan
// Date:    March 9, 2011
// File:    darray.cpp
// Desc:    Implementation for the darray class.
/////////////////////////////////////////////////////////////////////////
#ifndef __WHYNOMBEDTEMPLATES
#define __WHYNOMBEDTEMPLATES
#include "darray.h"
#include <cassert>

template<typename T>
darray<T>::darray()
{
    cap = 0;
    length = 0;
    arr = 0;
}

template<typename T>
darray<T>::darray( const darray& d):cap(d.cap),length(d.length),arr(0)
{
    arr = new T[cap];
    for( int i = 0; i < length; ++i)
        arr[i] = d.arr[i];
}

template<typename T>
darray<T>::~darray()
{
    delete[] this->arr;
    cap = length = 0;
    arr = 0;
}

template<typename T>
const T& darray<T>::operator [] (unsigned int idx) const
{
    assert( idx < length );
    return arr[idx];
}

template<typename T>
T& darray<T>::operator [] (unsigned int idx)
{
    assert( idx < length );
    return arr[idx];
}

template<typename T>
void darray<T>::pop_back()
{
    assert( length > 0 );
    --length;
}

template<typename T>
void darray<T>::push_back( const T& entry )
{
    if( length < cap )
        arr[length++] = entry;
    else
    {
        T* temp = new T[length + 5];
        
        for( int i = 0; i < length; ++i )
            temp[i] = arr[i];
            
        temp[length] = entry;
        delete[] arr;
        arr = temp;
        cap += 5;
        ++length;
            std::cout << "nAddress of Arr: " << &arr << '\n';
    }
}

template<typename T>
darray<T>& darray<T>::operator = (const darray &d)
{
    if(this != &d)
    {
        //delete[] this;
        this = d;
    }
    return *this;
}


template<typename T>
void darray<T>::reserve(unsigned newcap)
{
    if(cap >= newcap)
        return;
    
    T* temp = new T[newcap];
    for( int i = 0; i < length; ++i )
        temp[i] = arr[i];
    
    delete[] arr;
    arr = temp;
    cap = newcap;
}

//operator += ()

/*
darray operator + (const darray& d1, const darray& d2)
{
    darray temp;
    temp += d1;
    temp += d2;
    return temp;
}
*/

/*
std::ostream& operator << (std::ostream& out, const darray& d)
{
    out << '(';
    int i;
    for( i = 0; i < (d.length-1); ++i )
        out << d.arr[i] << ' ';
    return out << d.arr[i] << ')';
}
*/

template <typename T>
void darray<T>::sort(darray<T>& elems)
{
    for(int top=elems.size()-1; top>0; --top)
    for(int k=0; k<top; ++k)
    if(elems[k] > elems[k+1])
    swap(elems[k], elems[k+1]);
}

template <typename T>
void darray<T>::swap(T& elem1, T& elem2)
{
    T temp = elem1;
    elem1 = elem2;
    elem2 = temp;
}

#endif