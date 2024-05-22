/***********************************************************************
 * Header:
 *    VECTOR
 * Summary:
 *    Our custom implementation of std::vector
 *
 *      __       ____       ____         __
 *     /  |    .'    '.   .'    '.   _  / /
 *     `| |   |  .--.  | |  .--.  | (_)/ /
 *      | |   | |    | | | |    | |   / / _
 *     _| |_  |  `--'  | |  `--'  |  / / (_)
 *    |_____|  '.____.'   '.____.'  /_/
 *
 *
 *    This will contain the class definition of:
 *        vector                 : A class that represents a Vector
 *        vector::iterator       : An interator through Vector
 * Author
 *    Noah Li, Josh Hamilton & Steven Sellers
 ************************************************************************/

#pragma once

#include <cassert>  // because I am paranoid. lol
#include <new>      // std::bad_alloc
#include <memory>   // for std::allocator

class TestVector; // forward declaration for unit tests
class TestStack;
class TestPQueue;
class TestHash;

namespace custom
{

/*****************************************
 * VECTOR
 * Just like the std :: vector <T> class
 ****************************************/
template <typename T>
class vector
{
   friend class ::TestVector; // give unit tests access to the privates
   friend class ::TestStack;
   friend class ::TestPQueue;
   friend class ::TestHash;
public:
   
   // 
   // Construct
   //

   vector();
   vector(size_t numElements                );
   vector(size_t numElements, const T & t   );
   vector(const std::initializer_list<T>& l );
   vector(const vector &  rhs);
   vector(      vector && rhs);
   ~vector();

   //
   // Assign
   //

   void swap(vector& rhs)
   {
      // Temporary Holders
      T* tempData = this->data;
      size_t tempNumCapacity = this->numCapacity;
      size_t tempNumElements = this->numElements;
      
      // Set this values to rhs
      this->data = rhs.data;
      this->numCapacity = rhs.numCapacity;
      this->numElements = rhs.numElements;
      
      // Set rhs values to temp
      rhs.data = tempData;
      rhs.numCapacity = tempNumCapacity;
      rhs.numElements = tempNumElements;
   }
   vector & operator = (const vector & rhs);
   vector& operator = (vector&& rhs);

   //
   // Iterator
   //

   class iterator;
   iterator       begin() { if (data == nullptr) return iterator(nullptr); else return iterator(&data[0]); }
   iterator       end() { if (data == nullptr) return iterator(nullptr); else return iterator(&data[numElements]); }

   //
   // Access
   //

         T& operator [] (size_t index);
   const T& operator [] (size_t index) const;
         T& front();
   const T& front() const;
         T& back();
   const T& back() const;

   //
   // Insert
   //

   void push_back(const T& t);
   void push_back(T&& t);
   void reserve(size_t newCapacity);
   void resize(size_t newElements);
   void resize(size_t newElements, const T& t);

   //
   // Remove
   //

   void clear();
   void pop_back();
   void shrink_to_fit();

   //
   // Status
   //

   size_t  size()          const { return numElements;}
   size_t  capacity()      const { return numCapacity;}
   bool empty()            const { return numElements == 0;}
   
   // adjust the size of the buffer
   
   // vector-specific interfaces
   
private:
   
   T *  data;                 // user data, a dynamically-allocated array
   size_t  numCapacity;       // the capacity of the array
   size_t  numElements;       // the number of items currently used
};

/**************************************************
 * VECTOR ITERATOR
 * An iterator through vector.  You only need to
 * support the following:
 *   1. Constructors (default and copy)
 *   2. Not equals operator
 *   3. Increment (prefix and postfix)
 *   4. Dereference
 * This particular iterator is a bi-directional meaning
 * that ++ and -- both work.  Not all iterators are that way.
 *************************************************/
template <typename T>
class vector <T> ::iterator
{
   friend class ::TestVector; // give unit tests access to the privates
   friend class ::TestStack;
   friend class ::TestPQueue;
   friend class ::TestHash;
public:
   // constructors, destructors, and assignment operator
   iterator()                           { this->p = nullptr; }
   iterator(T* p)                       { this->p = p; }
   iterator(const iterator& rhs)        { this->p = rhs.p; }
   iterator(size_t index, vector<T>& v) { this->p = &v[index]; }
   iterator& operator = (const iterator& rhs)
   {
      this->p = new T;
      return *this;
   }

   // equals, not equals operator
   bool operator != (const iterator& rhs) const { return this->p != rhs.p; }
   bool operator == (const iterator& rhs) const { return this->p == rhs.p; }

   // dereference operator
   T& operator * ()
   {
      return *p;
   }

   // prefix increment
   iterator& operator ++ ()
   {
      p++;
      return *this;
   }

   // postfix increment
   iterator operator ++ (int postfix)
   {
      iterator copy = *this;
      p++;
      return copy;
   }

   // prefix decrement
   iterator& operator -- ()
   {
      p--;
      return *this;
   }

   // postfix decrement
   iterator operator -- (int postfix)
   {
      iterator copy = *this;
      p--;
      return copy;
   }

private:
   T* p;
};

/*****************************************
 * VECTOR :: DEFAULT constructors
 * Default constructor: set the number of elements,
 * construct each element, and copy the values over
 ****************************************/
template <typename T>
vector <T> :: vector()
{
   data = nullptr;
   numCapacity = 0;
   numElements = 0;
}

/*****************************************
 * VECTOR :: NON-DEFAULT constructors
 * non-default constructor: set the number of elements,
 * construct each element, and copy the values over
 ****************************************/
template <typename T>
vector <T> :: vector(size_t num, const T & t) 
{
   if (num == 0)
   {
      data = nullptr;
   }
   else
   {
      data = new T[num];
      for (int i = 0; i < num; i++)
      {
         data[i] = t;
      }
   }
   numCapacity = num;
   numElements = num;
}

/*****************************************
 * VECTOR :: INITIALIZATION LIST constructors
 * Create a vector with an initialization list.
 ****************************************/
template <typename T>
vector <T> :: vector(const std::initializer_list<T> & l) 
{
   if (l.size() == 0)
   {
      data = nullptr;
   }
   else
   {
      data = new T[l.size()];
      int i = 0;
      for (T it : l)
      {
         data[i++] = it;
      }
   }
   numElements = l.size();
   numCapacity = l.size();
}

/*****************************************
 * VECTOR :: NON-DEFAULT constructors
 * non-default constructor: set the number of elements,
 * construct each element, and copy the values over
 ****************************************/
template <typename T>
vector <T> :: vector(size_t num) 
{
   if (num == 0)
   {
      data = nullptr;
   }
   else
   {
      data = new T[num];
      for (int i = 0; i < num; i++)
      {
         data[i] = 0;
      }
   }
   numCapacity = num;
   numElements = num;
}

/*****************************************
 * VECTOR :: COPY CONSTRUCTOR
 * Allocate the space for numElements and
 * call the copy constructor on each element
 ****************************************/
template <typename T>
vector <T> :: vector (const vector & rhs) 
{
   if (rhs.numElements == 0)
   {
      data = nullptr;
   }
   else
   {
      data = new T[rhs.numElements];
      for (int i = 0; i < rhs.numElements; i++)
      {
         data[i] = rhs.data[i];
      }
   }
   numCapacity = rhs.numElements;
   numElements = rhs.numElements;
}

/*****************************************
 * VECTOR :: MOVE CONSTRUCTOR
 * Steal the values from the RHS and set it to zero.
 ****************************************/
template <typename T>
vector <T> :: vector (vector && rhs)
{
   if (rhs.numCapacity == 0)
   {
      data = nullptr;
   }
   else
   {
      data = rhs.data;
   }
   numCapacity = rhs.numCapacity;
   numElements = rhs.numElements;

   rhs.data = nullptr;
   rhs.numElements = 0;
   rhs.numCapacity = 0;
}

/*****************************************
 * VECTOR :: DESTRUCTOR
 * Call the destructor for each element from 0..numElements
 * and then free the memory
 ****************************************/
template <typename T>
vector <T> :: ~vector()
{
   
}

/***************************************
 * VECTOR :: RESIZE
 * This method will adjust the size to newElements.
 * This will either grow or shrink newElements.
 *     INPUT  : newCapacity the size of the new buffer
 *     OUTPUT :
 **************************************/
template <typename T>
void vector <T> :: resize(size_t newElements)
{
   if (newElements == 0)
   {
      numElements = 0;
   }
   else
   {
      numCapacity = newElements;
      T* newData = new T[numCapacity];
      for (int i = 0; i < numCapacity; i++)
      {
         if (i < numElements)
            newData[i] = data[i];
         else
            newData[i] = 0;
      }
      
      data = newData;
   }
}

template <typename T>
void vector <T> :: resize(size_t newElements, const T & t)
{
   if (newElements > 0)
   {
      numCapacity = newElements;
      T* newData = new T[numCapacity];
      for (int i = 0; i < numCapacity; i++)
      {
         if (i < numElements)
            newData[i] = data[i];
         else
            newData[i] = t;
      }
      numElements = newElements;
      data = newData;
   }
}

/***************************************
 * VECTOR :: RESERVE
 * This method will grow the current buffer
 * to newCapacity.  It will also copy all
 * the data from the old buffer into the new
 *     INPUT  : newCapacity the size of the new buffer
 *     OUTPUT :
 **************************************/
template <typename T>
void vector <T> :: reserve(size_t newCapacity)
{
   if (newCapacity > numCapacity)
   {
      numCapacity = newCapacity;
   }
}

/***************************************
 * VECTOR :: SHRINK TO FIT
 * Get rid of any extra capacity
 *     INPUT  :
 *     OUTPUT :
 **************************************/
template <typename T>
void vector <T> :: shrink_to_fit()
{
   if (numElements == 0)
   {
      delete[] data;
      data = nullptr;
      numCapacity = 0;
   }
   else if (numCapacity > numElements) 
   {
      T* newData = new T[numElements];
      for (size_t i = 0; i < numElements; i++) 
      {
         newData[i] = data[i];
      }
      delete[] data;
      data = newData;
      numCapacity = numElements; // Update capacity
   }
}

/***************************************
 * VECTOR :: POP
 * Get rid of any extra capacity
 *     INPUT  :
 *     OUTPUT :
 **************************************/
template <typename T>
void vector <T> :: pop_back()
{
   if (numElements > 0)
   {
      --numElements;
      if (numElements == 0)
      {
         delete[] data;
         data = nullptr;
         numCapacity = 0;
      }
   }
}

/***************************************
 * VECTOR :: Clear
 * Get rid of any extra capacity
 *     INPUT  :
 *     OUTPUT :
 **************************************/
template <typename T>
void vector <T> :: clear()
{
      numElements = 0;
}



/*****************************************
 * VECTOR :: SUBSCRIPT
 * Read-Write access
 ****************************************/
template <typename T>
T & vector <T> :: operator [] (size_t index)
{
   return data[index];
}

/******************************************
 * VECTOR :: SUBSCRIPT
 * Read-Write access
 *****************************************/
template <typename T>
const T & vector <T> :: operator [] (size_t index) const
{
   return data[index];
}

/*****************************************
 * VECTOR :: FRONT
 * Read-Write access
 ****************************************/
template <typename T>
T & vector <T> :: front ()
{
   return data[0];
}

/******************************************
 * VECTOR :: FRONT
 * Read access
 *****************************************/
template <typename T>
const T & vector <T> :: front () const
{
   return data[0];
}

/*****************************************
 * VECTOR :: BACK
 * Read-Write access
 ****************************************/
template <typename T>
T & vector <T> :: back()
{
   return data[numElements - 1];
}

/******************************************
 * VECTOR :: BACK
 * Read access
 *****************************************/
template <typename T>
const T & vector <T> :: back() const
{
   return data[numElements - 1];
}

/***************************************
 * VECTOR :: PUSH BACK
 * This method will add the element 't' to the
 * end of the current buffer.  It will also grow
 * the buffer as needed to accomodate the new element
 *     INPUT  : 't' the new element to be added
 *     OUTPUT : *this
 **************************************/
template <typename T>
void vector <T> :: push_back (const T & t)
{
   if (data == nullptr)
   {
      data = new T[1];
      data[0] = t;
      numCapacity = 1;
      numElements = 1;
   }
   else
   {
      if (numCapacity == numElements)
      {
         resize(numCapacity * 2);
      }
      data[numElements++] = t;
   }
}

template <typename T>
void vector <T> ::push_back(T && t)
{
   if (data == nullptr)
   {
      data = new T[1];
      data[0] = t;
      numCapacity = 1;
      numElements = 1;
   }
   else
   {
      if (numCapacity == numElements)
      {
         resize(numCapacity * 2);
      }
      data[numElements++] = t;
   }
}

/***************************************
 * VECTOR :: ASSIGNMENT
 * This operator will copy the contents of the
 * rhs onto *this, growing the buffer as needed
 *     INPUT  : rhs the vector to copy from
 *     OUTPUT : *this
 **************************************/
template <typename T>
vector <T> & vector <T> :: operator = (const vector & rhs)
{
   if (rhs.numElements == 0)
   {
      this->data = nullptr;
   }
   else
   {
      this->data = new T[rhs.numElements];
      for (int i = 0; i < rhs.numElements; i++)
      {
         this->data[i] = rhs.data[i];
      }
   }
   if (this->numCapacity < rhs.numCapacity)
   {
      this->numCapacity = rhs.numCapacity;
   }
   this->numElements = rhs.numElements;
   return *this;
}
template <typename T>
vector <T>& vector <T> :: operator = (vector&& rhs)
{
   if (rhs.numElements == 0)
   {
      this->data = nullptr;
   }
   else
   {
      this->data = new T[rhs.numElements];
      for (int i = 0; i < rhs.numElements; i++)
      {
         this->data[i] = rhs.data[i];
      }
   }
   this->numCapacity = rhs.numCapacity;
   this->numElements = rhs.numElements;

   rhs.data = nullptr;
   rhs.numElements = 0;
   rhs.numCapacity = 0;

   return *this;
}




} // namespace custom

