/***********************************************************************
* Header:
*    Set
* Summary:
*      __       ____       ____         __
*     /  |    .'    '.   .'    '.   _  / /
*     `| |   |  .--.  | |  .--.  | (_)/ /
*      | |   | |    | | | |    | |   / / _
*     _| |_  |  `--'  | |  `--'  |  / / (_)
*    |_____|  '.____.'   '.____.'  /_/
*
*    This will contain the class definition of:
*        set                 : A class that represents a Set
*        set::iterator       : An iterator through Set
* Author
*    Josh Hamilton, Noah Li, & Steven Sellers
************************************************************************/

#pragma once

#include <cassert>
#include <iostream>
#include "bst.h"
#include <memory>     // for std::allocator
#include <functional> // for std::less

class TestSet;        // forward declaration for unit tests

namespace custom
{

/************************************************
 * SET
 * A class that represents a Set
 ***********************************************/
template <typename T>
class set
{
   friend class ::TestSet; // give unit tests access to the privates
public:
   
   // 
   // Construct
   //
    set()
    {
    }

    set(const set& rhs)
    {
        bst = rhs.bst;
    }

    set(set&& rhs) noexcept : bst(std::move(rhs.bst))
    {
    }

    set(const std::initializer_list <T>& il)
    {
        for (const auto& elem : il)
            bst.insert(elem);
    }

    template <class Iterator>
    set(Iterator first, Iterator last)
    {
        for (auto it = first; it != last; ++it)
            bst.insert(*it);
    }

  ~set() { }

   //
   // Assign
   //

   set & operator = (const set & rhs)
   {
       if (this != &rhs)
           bst = rhs.bst;
       return *this;
   }
   set & operator = (set && rhs)
   {
       if (this != &rhs)
           bst = std::move(rhs.bst);
       return *this;
   }
   set & operator = (const std::initializer_list <T> & il)
   {
       bst.clear();
       for (const auto& elem : il)
           bst.insert(elem);
       return *this;
   }
   void swap(set& rhs) noexcept
   {
       std::swap(bst, rhs.bst);
   }

   //
   // Iterator
   //

   class iterator;
   iterator begin() const noexcept 
   { 
      return iterator(bst.begin());
   }
   iterator end() const noexcept 
   { 
       return iterator(bst.end());
   }

   //
   // Access
   //
   iterator find(const T& t) 
   { 
      return iterator(bst.find(t));
   }

   //
   // Status
   //
   bool   empty() const noexcept 
   { 
      return bst.empty();    
   }
   size_t size() const noexcept 
   { 
     return bst.size();  
   }

   //
   // Insert
   //
   std::pair<iterator, bool> insert(const T& t)
   {
       auto result = bst.insert(t, true);  // Ensure keepUnique is true
       return { iterator(result.first), result.second };
   }

   std::pair<iterator, bool> insert(T&& t)
   {
       auto result = bst.insert(std::move(t), true);  // Ensure keepUnique is true
       return { iterator(result.first), result.second };
   }

   void insert(const std::initializer_list<T>& il)
   {
       for (const auto& elem : il)
       {
           bst.insert(elem, true);  // Ensure keepUnique is true
       }
   }

   template <class Iterator>
   void insert(Iterator first, Iterator last)
   {
       for (auto it = first; it != last; ++it)
       {
           bst.insert(*it, true);  // Ensure keepUnique is true
       }
   }


   //
   // Remove
   //
   void clear() noexcept
   {
       bst.clear();
   }

   iterator erase(iterator& it)
   {
       auto next = bst.erase(it.it);
       return iterator(next);
   }

   size_t erase(const T& t)
   {
       auto it = bst.find(t);
       if (it != bst.end())
       {
           bst.erase(it);
           return 1;
       }
       return 0;
   }

   iterator erase(iterator& itBegin, iterator& itEnd)
   {
       for (auto it = itBegin; it != itEnd; )
           it = erase(it);
       return itEnd;
   }

private:
   
   custom::BST <T> bst;
};


/**************************************************
 * SET ITERATOR
 * An iterator through Set
 *************************************************/
template <typename T>
class set <T> :: iterator
{
   friend class ::TestSet; // give unit tests access to the privates
   friend class custom::set<T>;

public:
   // constructors, destructors, and assignment operator
    iterator() = default;

    iterator(const typename custom::BST<T>::iterator & itRHS) : it(itRHS) {}

    iterator(const iterator & rhs) = default;

    iterator& operator = (const iterator & rhs) = default;

    // Equals, not equals operator
    bool operator != (const iterator & rhs) const
    {
        return it != rhs.it;
    }

    bool operator == (const iterator & rhs) const
    {
        return it == rhs.it;
    }

    // Dereference operator
    const T& operator * () const
    {
        return *it;
    }

    // Prefix increment
    iterator& operator ++ ()
    {
        ++it;
        return *this;
    }

    // Postfix increment
    iterator operator++ (int)
    {
        iterator tmp(*this);
        ++it;
        return tmp;
    }

    // Prefix decrement
    iterator& operator -- ()
    {
        --it;
        return *this;
    }

    // Postfix decrement
    iterator operator-- (int)
    {
        iterator tmp(*this);
        --it;
        return tmp;
    }
   
private:

   typename custom::BST<T>::iterator it;
};


}; // namespace custom



