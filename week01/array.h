/***********************************************************************
 * Header:
 *    Array
 * Summary:
 *    Our custom implementation of std::array
 *      __       ____       ____         __
 *     /  |    .'    '.   .'    '.   _  / /
 *     `| |   |  .--.  | |  .--.  | (_)/ /
 *      | |   | |    | | | |    | |   / / _
 *     _| |_  |  `--'  | |  `--'  |  / / (_)
 *    |_____|  '.____.'   '.____.'  /_/
 *    
 *    This will contain the class definition of:
 *       array             : similar to std::array
 *       array :: iterator : an iterator through the array
 * Author
 *    Steven Sellers
 ************************************************************************/

#pragma once

#include <stdexcept>

class TestArray;

namespace custom
{

/************************************************
 * ARRAY
 * A class that holds stuff
 ***********************************************/
template <int N>
struct array
{
public:
   //
   // Construct
   //

   // No constructors or destructors needed here

   //
   // Assign
   //

   // No assignment operators needed here

   //
   // Iterator
   //

   // Forward declaration for the iterator class
   class iterator;

   // Begin and end methods
   iterator begin() 
   { 
      return iterator(&front()); 
   }
   iterator end()   
   { 
      return iterator(&back() + 1); 
   }

   // 
   // Access
   //

   // Subscript
   int& operator [] (size_t index)       
   { 
      return __elems_[index]; 
   }
   const int& operator [] (size_t index) const 
   { 
      return __elems_[index]; 
   }

   // At
   int& at(size_t index)
   {
      if (index < 0 || index >= size())
      {
         throw std::out_of_range("ARRAY: index out of range");
      }
      return __elems_[index];
   }
   const int& at(size_t index) const
   {
      if (index < 0 || index >= size())
      {
         throw std::out_of_range("ARRAY: index out of range");
      }
      return __elems_[index];
   }

   // Front and Back
   int& front()       
   { 
      return at(0);
   }
   int& back()        
   {
      return at(size() - 1);
   }
   const int& front() const 
   {
      return at(0);
   }
   const int& back()  const 
   {
      return at(size() - 1);
   }

   //
   // Remove

   // No clear or erase here

   //
   // Status
   //

   // number of elements in the array
   size_t size()  const 
   { 
      size_t size;
      size = N;

      return size;           
   }
   bool empty() const 
   { 
      return size() == size_t(0); 
   }
   
   //
   // Member Variable
   //

   // statically allocated array of T
   int __elems_[N];
};


/**************************************************
 * ARRAY ITERATOR
 * An iterator through array
 *************************************************/
template <int N>
class array <N> :: iterator
{
   friend class ::TestArray;
public:
   // constructors, destructors, and assignment operator
   iterator()     
   { 
      p = nullptr;
   }
   iterator(int * p)   
   { 
      this->p = p;
   }
   iterator(const iterator & rhs) 
   {  
      this->p = rhs.p;
   }
   iterator & operator = (const iterator & rhs)
   {
      this->p = rhs.p;
      return *this;
   }
   
   // equals, not equals operator
   bool operator != (const iterator & rhs) const 
   { 
      return this->p != rhs.p; 
   }
   bool operator == (const iterator & rhs) const 
   { 
      return this->p == rhs.p;
   }
   
   // dereference operator
   int & operator * ()       
   { 
      return *p; 
   }
   const int & operator * () const 
   { 
      return *p; 
   }
   
   // prefix increment
   iterator & operator ++ ()
   {
      p ++;
      return *this;
   }
   
   // postfix increment
   iterator operator ++ (int postfix)
   {
      iterator copy = *this;
      p++;
      return copy;
   }
   
private:
   int * p;
};



}; // namespace custom
