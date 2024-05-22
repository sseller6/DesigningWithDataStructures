/***********************************************************************
 * Header:
 *    NODE
 * Summary:
 *    One node in a linked list (and the functions to support them).
 *      __       ____       ____         __
 *     /  |    .'    '.   .'    '.   _  / /
 *     `| |   |  .--.  | |  .--.  | (_)/ /
 *      | |   | |    | | | |    | |   / / _
 *     _| |_  |  `--'  | |  `--'  |  / / (_)
 *    |_____|  '.____.'   '.____.'  /_/
 *
 *
 *    This will contain the class definition of:
 *        Node         : A class representing a Node
 *    Additionally, it will contain a few functions working on Node
 * Author
 *    Noah Li, Steven Sellers, and Josh Hamilton
 ************************************************************************/

#pragma once

#include <cassert>     // for ASSERT
#include <iostream>    // for NULL

/*************************************************
 * NODE
 * the node class.  Since we do not validate any
 * of the setters, there is no point in making them
 * private.  This is the case because only the
 * List class can make validation decisions
 *************************************************/
template <class T>
class Node
{
public:

   //
   // Construct
   //

   Node():data(T()), pPrev(nullptr), pNext(nullptr) {}
   // Copy
   Node(const T &  data):data(data), pPrev(nullptr), pNext(nullptr) {}
   // Move
   Node(      T && data):data(std::move(data)), pPrev(nullptr), pNext(nullptr) {}

   //
   // Member variables
   //

   T data;                 // user data
   Node <T> * pNext;       // pointer to next node
   Node <T> * pPrev;       // pointer to previous node
};

/***********************************************
 * COPY
 * Copy the list from the pSource and return
 * the new list
 *   INPUT  : the list to be copied
 *   OUTPUT : return the new list
 *   COST   : O(n)
 **********************************************/
template <class T>
inline Node <T> * copy(const Node <T> * pSource) 
{
   if (pSource == nullptr)
   {
      return nullptr;
   }
   
   else
   {
      Node<T>* pDest = new Node <T>(pSource->data);
      Node<T>* pCurrentSource = pSource->pNext;
      Node<T>* pCurrentDest = pDest;
      Node<T>* pNewNode = nullptr;

      while (pCurrentSource != nullptr)
      {
         pNewNode = new Node<T>(pCurrentSource->data);

         pCurrentDest->pNext = pNewNode;
         pNewNode->pPrev = pCurrentDest;

         pCurrentDest = pNewNode;
         pCurrentSource = pCurrentSource->pNext;
      }

      return pDest;
   }
}

/***********************************************
 * Assign
 * Copy the values from pSource into pDestination
 * reusing the nodes already created in pDestination if possible.
 *   INPUT  : the list to be copied
 *   OUTPUT : return the new list
 *   COST   : O(n)
 **********************************************/
template <class T>
inline void assign(Node <T> * & pDestination, const Node <T> * pSource)
{
   Node<T>* pDestCurrent = pDestination;
   const Node<T>* pSrcCurrent = pSource;

   Node<T>* pPrevNode = nullptr; // Track the previous node

   // Loop through source and copy destination nodes
   while (pSrcCurrent != nullptr)
   {
      if (pDestCurrent != nullptr)
      {
         // Reuse existing node
         pDestCurrent->data = pSrcCurrent->data;
         pPrevNode = pDestCurrent;
         pDestCurrent = pDestCurrent->pNext;
      }
      else 
      {
         // If no more nodes to reuse, then create a new node
         Node<T>* pNewNode = new Node<T>(pSrcCurrent->data);
         if (pPrevNode == nullptr) 
         {
            // pDestination becomes new node.
            pDestination = pNewNode;
         }
         else 
         {
            // Link the new node to the list
            pPrevNode->pNext = pNewNode;
            pNewNode->pPrev = pPrevNode;
         }
         pPrevNode = pNewNode;
      }
      pSrcCurrent = pSrcCurrent->pNext;
   }

   // Check if last node in destination points to nullptr.
   if (pPrevNode != nullptr) 
   {
      pPrevNode->pNext = nullptr;
   }

   // If the destination list is longer than the source, delete the remaining nodes.
   while (pDestCurrent != nullptr) 
   {
      Node<T>* pToDelete = pDestCurrent;
      pDestCurrent = pDestCurrent->pNext;
      delete pToDelete;
   }

   // If the source list was empty, make sure destination list is cleared.
   if (pSource == nullptr) 
   {
      pDestination = nullptr;
   }
}

/***********************************************
 * SWAP
 * Swap the list from LHS to RHS
 *   COST   : O(1)
 **********************************************/
template <class T>
inline void swap(Node <T>* &pLHS, Node <T>* &pRHS)
{
   Node<T>* temp = pLHS;
   pLHS = pRHS;
   pRHS = temp;
}

/***********************************************
 * REMOVE
 * Remove the node pSource in the linked list
 *   INPUT  : the node to be removed
 *   OUTPUT : the pointer to the parent node
 *   COST   : O(1)
 **********************************************/
template <class T>
inline Node <T> * remove(const Node <T> * pRemove) 
{
   if (pRemove == nullptr)
   {
      return nullptr;
   }

   if (pRemove->pPrev)
   {
      pRemove->pPrev->pNext = pRemove->pNext;
   }

   if (pRemove->pNext)
   {
      pRemove->pNext->pPrev = pRemove->pPrev;
   }

   Node<T>* pReturn = pRemove->pPrev ? pRemove->pPrev : pRemove->pNext;

   delete pRemove;

   return pReturn;
}

/**********************************************
 * INSERT 
 * Insert a new node the the value in "t" into a linked
 * list immediately before the current position.
 *   INPUT   : t - the value to be used for the new node
 *             pCurrent - a pointer to the node before which
 *                we will be inserting the new node
 *             after - whether we will be inserting after
 *   OUTPUT  : return the newly inserted item
 *   COST    : O(1)
 **********************************************/
template <class T>
inline Node <T> * insert(Node <T> * pCurrent,
                  const T & t,
                  bool after = false)
{
   Node<T>* pNewNode = new Node<T>(t);

   if (pCurrent == nullptr)
   {
      return pNewNode;
   }

   if (after)
   {
      pNewNode->pNext = pCurrent->pNext;
      pNewNode->pPrev = pCurrent;
      if (pCurrent->pNext)
      {
         pCurrent->pNext->pPrev = pNewNode;
      }
      pCurrent->pNext = pNewNode;
   }
   else
   {
      pNewNode->pPrev = pCurrent->pPrev;
      pNewNode->pNext = pCurrent;
      if (pCurrent->pPrev)
      {
         pCurrent->pPrev->pNext = pNewNode;
      }
      pCurrent->pPrev = pNewNode;
   }

   return pNewNode;
}

/******************************************************
 * SIZE
 * Find the size an unsorted linked list.  
 *  INPUT   : a pointer to the head of the linked list
 *            the value to be found
 *  OUTPUT  : number of nodes
 *  COST    : O(n)
 ********************************************************/
template <class T>
inline size_t size(const Node <T> * pHead)
{
   size_t count = 0;
   const Node<T>* pCurrent = pHead;
   while (pCurrent != nullptr)
   {
      count++;
      pCurrent = pCurrent->pNext;
   }
   return count;
}

/***********************************************
 * DISPLAY
 * Display all the items in the linked list from here on back
 *    INPUT  : the output stream
 *             pointer to the linked list
 *    OUTPUT : the data from the linked list on the screen
 *    COST   : O(n)
 **********************************************/
template <class T>
inline std::ostream & operator << (std::ostream & out, const Node <T> * pHead)
{
   const Node<T>* pCurrent = pHead;
   while (pCurrent != nullptr)
   {
      out << pCurrent->data << ' ';
      pCurrent = pCurrent->pNext;
   }
   return out;
}

/*****************************************************
 * CLEAR
 * Free all the data currently in the linked list
 *   INPUT   : pointer to the head of the linked list
 *   OUTPUT  : pHead set to NULL
 *   COST    : O(n)
 ****************************************************/
template <class T>
inline void clear(Node <T> * & pHead)
{
   while (pHead != nullptr)
   {
      Node<T>* pNext = pHead->pNext;
      delete pHead;
      pHead = pNext;
   }
}


