/***********************************************************************
 * Module:
 *    Stack
 * Summary:
 *    Our custom implementation of std::stack
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
 *       stack             : similar to std::stack
 * Author
 *    <your names here>
 ************************************************************************/

#pragma once

#include <cassert>  // because I am paranoid
//#include "vector.h"
#include <vector>

class TestStack; // forward declaration for unit tests

namespace custom
{

/**************************************************
 * STACK
 * First-in-Last-out data structure
 *************************************************/
template<class T>
class stack
{
   friend class ::TestStack; // give unit tests access to the privates
public:
  
   // 
   // Construct
   // 

   stack()                            { container.resize(0); }
   stack(const stack <T> &  rhs)      { this->container = rhs.container; }
   stack(      stack <T> && rhs)      { this->container = rhs.container; }
   stack(const std::vector<T> &  rhs) { *this = rhs; }
   stack(std::vector<T>&& rhs)        { *this = std::move(rhs); }
   ~stack()                           {                      }

   //
   // Assign
   //

   stack <T> & operator = (const stack <T> & rhs)
   {
      return *this;
   }
   stack <T>& operator = (stack <T> && rhs)
   {
      return *this;
   }
   void swap(stack <T>& rhs)
   {

   }

   // 
   // Access
   //

         T& top()       { return *(new T); }
   const T& top() const { return *(new T); }

   // 
   // Insert
   // 

   void push(const T&  t) {  }
   void push(      T&& t) {  }

   //
   // Remove
   //

   void pop() 
   { 
      
   }

   //
   // Status
   //
   size_t  size () const { return 99;  }
   bool empty   () const { return true; }
   
private:
   
  std::vector<T> container;  // underlying container
};



} // custom namespace


