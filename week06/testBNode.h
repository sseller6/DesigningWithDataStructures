/***********************************************************************
 * Header:
 *    TEST BINARY NODE
 * Summary:
 *    Unit tests for bnode
 * Author
 *    Br. Helfrich
 ************************************************************************/

#pragma once

#ifdef DEBUG
#include "bnode.h"
#include "unitTest.h"

#include <cassert>
#include <memory>
#include <iostream>
#include <sstream>


class TestBNode : public UnitTest
{

public:
   void run()
   {
      reset();

      // Construct
      test_construct_default();
      test_constructValue_copy();
      test_constructValue_move();
      test_copy_nullptr();
      test_copy_one();
      test_copy_standard();

      // Assign
      test_assign_emptyToEmpty();
      test_assign_standardToEmpty();
      test_assign_emptyToStandard();
      test_assign_oneToStandard();
      test_assign_standardToOne();
      test_assign_standardToStandard();
      test_swap_emptyEmpty();
      test_swap_emptyStandard();
      test_swap_standardEmpty();
      test_swap_oneTwo();

      // Insert
      test_addLeft_oneValue();
      test_addLeft_standardValue();
      test_addRight_oneValue();
      test_addRight_standardValue();
      test_addLeftMove_oneValue();
      test_addLeftMove_standardValue();
      test_addRightMove_oneValue();
      test_addRightMove_standardValue();
      test_addLeft_oneTree();
      test_addLeft_standardTree();
      test_addRight_oneTree();
      test_addRight_standardTree();

      // Remove
      test_clear_empty();
      test_clear_one();
      test_clear_standard();

      // Status
      test_size_empty();
      test_size_one();
      test_size_standard();

      report("BNode");
   }

   /***************************************
    * CREATE
    ***************************************/

    // default constructor, no allocations
   void test_construct_default()
   {  // setup
      std::allocator<BNode <int>> alloc;
      BNode <int> bn;
      bn.data = 99;
      bn.pLeft   = (BNode <int>*)0xBADF00D1;
      bn.pRight  = (BNode <int>*)0xBADF00D2;
      bn.pParent = (BNode <int>*)0xBADF00D3;
      // exercise
      alloc.construct(&bn);  // just call the constructor by itself
      // verify
      //                      (00) = bn
      assertUnit(bn.data == 0);
      assertUnit(bn.pLeft == nullptr);
      assertUnit(bn.pRight == nullptr);
      assertUnit(bn.pParent == nullptr);
      // teardown
   }

   // use the non-default constructor to copy a value
   void test_constructValue_copy()
   {  // setup
      std::allocator<BNode <int>> alloc;
      BNode <int> bn;
      bn.data = 55;
      bn.pLeft   = (BNode <int>*)0xBADF00D1;
      bn.pRight  = (BNode <int>*)0xBADF00D2;
      bn.pParent = (BNode <int>*)0xBADF00D3;
      int s(99);
      // exercise
      alloc.construct(&bn, s);  // just call the constructor by itself
      // verify
      assertUnit(s == int(99));
      //                      (99) = bn
      assertUnit(bn.data == int(99));
      assertUnit(bn.pLeft == nullptr);
      assertUnit(bn.pRight == nullptr);
      assertUnit(bn.pParent == nullptr);
      // teardown
   }

   // use the non-default constructor to move a value
   void test_constructValue_move()
   {  // setup
      std::allocator<BNode <int>> alloc;
      BNode <int> bn;
      bn.data = 55;
      bn.pLeft   = (BNode <int>*)0xBADF00D1;
      bn.pRight  = (BNode <int>*)0xBADF00D2;
      bn.pParent = (BNode <int>*)0xBADF00D3;
      int s(99);
      // exercise
      alloc.construct(&bn, std::move(s));  // just call the constructor by itself
      // verify
      assertUnit(s == int(99));
      //                      (99) = bn
      assertUnit(bn.data == int(99));
      assertUnit(bn.pLeft == nullptr);
      assertUnit(bn.pRight == nullptr);
      assertUnit(bn.pParent == nullptr);
   }  // teardown

   /***************************************
    * COPY 
    ***************************************/

   // copy with a nullptr pointer
   void test_copy_nullptr()
   {  // setup
      BNode <int>* pSrc = nullptr;
      BNode <int>* pDest = nullptr;
      // exercise
      pDest = copy(pSrc);
      // verify
      assertUnit(pSrc == nullptr);
      assertUnit(pDest == nullptr);
   }  // teardown

   // copy a btree with a single node
   void test_copy_one()
   {  // setup
      //                      (50) = pSrc
      BNode <int>* pSrc = new BNode <int>(int(50));
      BNode <int>* pDest = nullptr;\
      // exercise
      pDest = copy(pSrc);
      // verify
      assertUnit(pSrc != pDest);
      //                      (50) = pSrc
      assertUnit(pSrc != nullptr);
      if (pSrc)
      {
         assertUnit(pSrc->data == int(50));
         assertUnit(pSrc->pLeft == nullptr);
         assertUnit(pSrc->pRight == nullptr);
         assertUnit(pSrc->pParent == nullptr);
      }
      //                      (50) = pDes
      assertUnit(pDest != nullptr);
      if (pDest)
      {
         assertUnit(pDest->data == int(50));
         assertUnit(pDest->pLeft == nullptr);
         assertUnit(pDest->pRight == nullptr);
         assertUnit(pDest->pParent == nullptr);
      }
      // teardown
      delete pSrc;
      delete pDest;
   }

   // copy the standard fixture
   void test_copy_standard()
   {  // setup
      //                      (50) = pSrc
      //            +----------+----------+
      //           (38)                  (73)
      //       +----+----+           +----+----+
      //      (26)      (49)        (64)      (85)
      BNode <int>* pSrc = setupStandardFixture();
      BNode <int>* pDest = nullptr;
      // exercise
      pDest = copy(pSrc);
      // verify
      assertUnit(pSrc != pDest);
      //                      (50) = pDest
      //            +----------+----------+
      //           (38)                  (73)
      //       +----+----+           +----+----+
      //      (26)      (49)        (64)      (85)
      assertStandardFixture(pSrc);
      assertStandardFixture(pDest);
      // teardown
      teardownStandardFixture(pSrc);
      teardownStandardFixture(pDest);
   }

   /***************************************
    * Assignment
    *    void assign(BNode <T> * & pDest, const BNode <T>* pSrc)
    ***************************************/

   // assignment operator: empty = empty
   void test_assign_emptyToEmpty()
   {  // setup
      BNode <int>* pSrc  = nullptr;
      BNode <int>* pDest = nullptr;
      // exercise
      assign(pDest, pSrc);
      // verify
      assertUnit(pSrc == nullptr);
      assertUnit(pDest == nullptr);
   }  // teardown

   // assignment operator: empty = standard
   void test_assign_standardToEmpty()
   {  // setup
      //                      (50) = pSrc
      //            +----------+----------+
      //           (38)                  (73)
      //       +----+----+           +----+----+
      //      (26)      (49)        (64)      (85)
      BNode <int>* pSrc = setupStandardFixture();
      BNode <int>* pDest = nullptr;
      // exercise
      assign(pDest, pSrc);
      // verify
      assertUnit(pSrc != pDest);
      if (pSrc && pDest)
      {
         assertUnit(pSrc->pLeft != pDest->pLeft);
         assertUnit(pSrc->pRight != pDest->pRight);
      }
      //                      (50)
      //            +----------+----------+
      //           (38)                  (73)
      //       +----+----+           +----+----+
      //      (26)      (49)        (64)      (85)
      assertStandardFixture(pSrc);
      assertStandardFixture(pDest);
      // teardown
      teardownStandardFixture(pSrc);
      teardownStandardFixture(pDest);
   }

   // assignment operator: standard = empty
   void test_assign_emptyToStandard()
   {  // setup
      BNode <int>* pSrc = nullptr;
      //                      (50) = pDest
      //            +----------+----------+
      //           (38)                  (73)
      //       +----+----+           +----+----+
      //      (26)      (49)        (64)      (85)
      BNode <int>* pDest = setupStandardFixture();
      // exercise
      assign(pDest, pSrc);
      // verify
      assertUnit(pSrc == nullptr);
      assertUnit(pDest == nullptr);
   }  // teardown

   // assignment operator : one = standard
   void test_assign_oneToStandard()
   {  // setup
      //                      (50) = pSrc
      //            +----------+----------+
      //           (38)                  (73)
      //       +----+----+           +----+----+
      //      (26)      (49)        (64)      (85)
      BNode <int> * pSrc = setupStandardFixture();
      //                (99) = pDest
      BNode <int> * pDest = new BNode<int>(int(99));
      // exercise
      assign(pDest, pSrc);
      // verify
      assertUnit(pDest != pSrc);
      if (pSrc && pDest)
      {
         assertUnit(pSrc->pLeft != pDest->pLeft);
         assertUnit(pSrc->pRight != pDest->pRight);
      }
      //                      (50)
      //            +----------+----------+
      //           (38)                  (73)
      //       +----+----+           +----+----+
      //      (26)      (49)        (64)      (85)
      assertStandardFixture(pSrc);
      assertStandardFixture(pDest);
      // teardown
      teardownStandardFixture(pSrc);
      teardownStandardFixture(pDest);
   }

   // assignment operator : standard = one
   void test_assign_standardToOne()
   {  // setup
      //                (99) = pSrc
      BNode <int>* pSrc = new BNode<int>(int(99));
      //                      (50) = pDest
      //            +----------+----------+
      //           (38)                  (73)
      //       +----+----+           +----+----+
      //      (26)      (49)        (64)      (85)
      BNode <int>* pDest = setupStandardFixture();
      // exercise
      assign(pDest, pSrc);
      // verify
      assertUnit(pDest != pSrc);
      //                (99) = bstSrc
      assertUnit(pSrc != nullptr);
      if (pSrc)
      {
         assertUnit(pSrc->data == int(99));
         assertUnit(pSrc->pParent == nullptr);
         assertUnit(pSrc->pLeft == nullptr);
         assertUnit(pSrc->pRight == nullptr);
      }
      //                (99) = pDest
      assertUnit(pDest != nullptr);
      if (pDest)
      {
       assertUnit(pDest->data == int(99));
       assertUnit(pDest->pParent == nullptr);
       assertUnit(pDest->pLeft == nullptr);
       assertUnit(pDest->pRight == nullptr);
    }
    // teardown
    teardownStandardFixture(pSrc);
    teardownStandardFixture(pDest);
   }

   // assignment operator : standard = standard
   void test_assign_standardToStandard()
   {  // setup
      //                      (50) = pSrc
      //            +----------+----------+
      //           (38)                  (73)
      //       +----+----+           +----+----+
      //      (26)      (49)        (64)      (85)
      BNode <int>* pSrc = setupStandardFixture();
      //                      (50) = pDest
      //            +----------+----------+
      //           (38)                  (73)
      //       +----+----+           +----+----+
      //      (26)      (49)        (64)      (85)
      BNode <int>* pDest = setupStandardFixture();\
      // exercise
      assign(pDest, pSrc);
      // verify
      assertUnit(pDest != pSrc);
     if (pSrc && pDest)
     {
        assertUnit(pSrc->pLeft != pDest->pLeft);
        assertUnit(pSrc->pRight != pDest->pRight);
     }
     //                (50b)
     //          +-------+-------+
     //        (30b)           (70b)
     //     +----+----+     +----+----+
     //   (20r)     (40r) (60r)     (80r)
     assertStandardFixture(pSrc);
     assertStandardFixture(pDest);
     // teardown
     teardownStandardFixture(pSrc);
     teardownStandardFixture(pDest);
   }

   /***************************************
    * SWAP
    ***************************************/

    // swap two empty pointers
   void test_swap_emptyEmpty()
   {  // setup
      BNode <int>* pLHS = nullptr;
      BNode <int>* pRHS = nullptr;
      // exercise
      swap(pLHS, pRHS);
      // verify
      assertUnit(pLHS == nullptr);
      assertUnit(pRHS == nullptr);
   }  // teardown

   // swap an empty fixture with the standard fixture
   void test_swap_emptyStandard()
   {  // setup
      BNode <int>* pLHS = nullptr;
      //                      (50) = pRHS
      //            +----------+----------+
      //           (38)                  (73)
      //       +----+----+           +----+----+
      //      (26)      (49)        (64)      (85)
      BNode <int>* pRHS = setupStandardFixture();
      // exercise
      swap(pLHS, pRHS);
      // verify
      //                      (50) = pLHS
      //            +----------+----------+
      //           (38)                  (73)
      //       +----+----+           +----+----+
      //      (26)      (49)        (64)      (85)
      assertStandardFixture(pLHS);
      assertUnit(pRHS == nullptr);
      // teardown
      teardownStandardFixture(pLHS);
   }

   // swap an empty fixture with the standard fixture
   void test_swap_standardEmpty()
   {  // setup
      //                      (50) = pLHS
      //            +----------+----------+
      //           (38)                  (73)
      //       +----+----+           +----+----+
      //      (26)      (49)        (64)      (85)
      BNode <int>* pLHS = setupStandardFixture();
      BNode <int>* pRHS = nullptr;
      // exercise
      swap(pLHS, pRHS);
      // verify
      //                      (50) = pRHS
      //            +----------+----------+
      //           (38)                  (73)
      //       +----+----+           +----+----+
      //      (26)      (49)        (64)      (85)
      assertStandardFixture(pRHS);
      assertUnit(pLHS == nullptr);
      // teardown
      teardownStandardFixture(pRHS);
   }

   // swap two non-empty lists
   void test_swap_oneTwo()
   {  // setup
      //                      (50) = pLHS
      //            +----------+----------+
      //           (38)                  (73)
      //       +----+----+           +----+----+
      //      (26)      (49)        (64)      (85)
      BNode <int>* pLHS = setupStandardFixture();
      //                      (99) = pRHS
      BNode <int>* pRHS = new BNode <int>(int(99));
      // exercise
      swap(pLHS, pRHS);
      // verify
      //                      (99) = pLHS
      assertUnit(pLHS != nullptr);
      if (pLHS)
      {
         assertUnit(pLHS->data == int(99));
         assertUnit(pLHS->pParent == nullptr);
         assertUnit(pLHS->pLeft   == nullptr);
         assertUnit(pLHS->pRight  == nullptr);
      }
      //                      (50) = pRHS
      //            +----------+----------+
      //           (38)                  (73)
      //       +----+----+           +----+----+
      //      (26)      (49)        (64)      (85)
      assertStandardFixture(pRHS);
      // teardown
      teardownStandardFixture(pRHS);
      teardownStandardFixture(pLHS);
   }


   /***************************************
    * SIZE 
    ***************************************/

   // size of an empty btree
   void test_size_empty()
   {  // setup
      BNode <int>* p = nullptr;
      // exercise
      size_t s = size(p);
      // verify
      assertUnit(s == 0);
      assertUnit(p == nullptr);
   }  // teardown

   // size of a btree with a single node
   void test_size_one()
   {  // setup
      //                      (50) = p
      BNode <int>* p = new BNode <int>(int(50));
      // exercise
      size_t s = size(p);
      // verify
      assertUnit(s == 1);
      //                      (50)
      assertUnit(p != nullptr);
      assertUnit(p->data == 50);
      assertUnit(p->pLeft == nullptr);
      assertUnit(p->pRight == nullptr);
      assertUnit(p->pParent == nullptr);
      // teardown
      delete p;
   }

   // size of the standard fixture
   void test_size_standard()
   {  // setup
      //                      (50) 
      //            +----------+----------+
      //           (38)                  (73)
      //       +----+----+           +----+----+
      //      (26)      (49)        (64)      (85)
      BNode <int>* p = setupStandardFixture();
      // exercise
      size_t s = size(p);
      // verify
      assertUnit(s == 7);
      assertStandardFixture(p);
      // teardown
      teardownStandardFixture(p);
   }

   /***************************************
    * ADD 
    * addLeft() and addRight()
    ***************************************/

   // add one copy-value to the left of a single-node btree
   void test_addLeft_oneValue()
   {  // setup
      //                      (50) = p50
      BNode <int>* p50 = new BNode <int>(int(50));
      int s(99);
      // exercise
      addLeft(p50, s);
      // verify
      assertUnit(s == int(99));
      //                      (50) = p50
      //            +----------+
      //           (99)        
      assertUnit(p50 != nullptr);
      if (p50)
      {
         assertUnit(p50->data == int(50));
         assertUnit(p50->pLeft != nullptr);
         assertUnit(p50->pRight == nullptr);
         assertUnit(p50->pParent == nullptr);

         if (p50->pLeft)
         {
            assertUnit(p50->pLeft->pLeft == nullptr);
            assertUnit(p50->pLeft->pRight == nullptr);
            assertUnit(p50->pLeft->pParent == p50);
            assertUnit(p50->pLeft->data == int(99));
         }
      }
      // teardown
      if (p50)
      {
         if (p50->pLeft && p50 != p50->pLeft)
            delete p50->pLeft;
         delete p50;
      }
   }

   // add one copy-value to the left of the standard fixture
   void test_addLeft_standardValue()
   {  // setup
      //                      (50) = pSrc
      //            +----------+----------+
      //           (38)                  (73)
      //       +----+----+           +----+----+
      //      (26)      (49)        (64)      (85)
      BNode <int>* pSrc = setupStandardFixture();
      BNode <int>* p64 = nullptr;
      if (pSrc && pSrc->pRight)
         p64 = pSrc->pRight->pLeft;
      int s(59);
      // exercise
      addLeft(p64, s);
      // verify
      assertUnit(s == int(59));
      //                      (50) = pSrc
      //            +----------+----------+
      //           (38)                  (73)
      //       +----+----+           +----+----+
      //      (26)      (49)        (64)      (85)
      //                          +--+
      //                         (59)
      assertUnit(pSrc != nullptr);
      if (pSrc)
      {
         assertUnit(pSrc->pRight != nullptr);
         if (pSrc->pRight)
         {
            assertUnit(pSrc->pRight->pLeft);
            if (pSrc->pRight->pLeft)
            {
               assertUnit(pSrc->pRight->pLeft->pLeft != nullptr);
               if (pSrc->pRight->pLeft->pLeft)
               {
                  assertUnit(pSrc->pRight->pLeft->pLeft->data == int(59));
                  assertUnit(pSrc->pRight->pLeft->pLeft->pLeft == nullptr);
                  assertUnit(pSrc->pRight->pLeft->pLeft->pRight == nullptr);
                  assertUnit(pSrc->pRight->pLeft->pLeft->pParent == pSrc->pRight->pLeft);
                  if (pSrc->pRight->pLeft->pLeft != pSrc->pRight->pLeft)
                     delete pSrc->pRight->pLeft->pLeft;
                  pSrc->pRight->pLeft->pLeft = nullptr;
               }
            }
         }
      }
      assertStandardFixture(pSrc);
      // teardown
      teardownStandardFixture(pSrc);
   }

   // add one copy-value to the right of a single-node btree
   void test_addRight_oneValue()
   {  // setup
      //                      (50) = p50
      BNode <int>* p50 = new BNode <int>(int(50));
      int s(99);
      // exercise
      addRight(p50, s);
      // verify
      assertUnit(s == int(99));
      //                      (50) = p50
      //                        +----------+
      //                                  (99)        
      assertUnit(p50 != nullptr);
      if (p50)
      {
         assertUnit(p50->data == int(50));
         assertUnit(p50->pLeft == nullptr);
         assertUnit(p50->pParent == nullptr);
         assertUnit(p50->pRight != nullptr);
         if (p50->pRight)
         {
            assertUnit(p50->pRight->pLeft == nullptr);
            assertUnit(p50->pRight->pRight == nullptr);
            assertUnit(p50->pRight->pParent == p50);
            assertUnit(p50->pRight->data == int(99));
         }
      }
      // teardown
      if (p50)
      {
         if (p50->pRight && p50 != p50->pRight)
            delete p50->pRight;
         delete p50;
      }
   }

   // add one copy-value to the left of the standard fixture
   void test_addRight_standardValue()
   {  // setup
      //                      (50) = pSrc
      //            +----------+----------+
      //           (38)                  (73)
      //       +----+----+           +----+----+
      //      (26)      (49)        (64)      (85)
      BNode <int>* pSrc = setupStandardFixture();
      BNode <int>* p64 = nullptr;
      if (pSrc && pSrc->pRight)
         p64 = pSrc->pRight->pLeft;
      int s(67);
      // exercise
      addRight(p64, s);
      // verify
      assertUnit(s == int(67));
      //                      (50) = pSrc
      //            +----------+----------+
      //           (38)                  (73)
      //       +----+----+           +----+----+
      //      (26)      (49)        (64)      (85)
      //                             +--+
      //                               (67)
      assertUnit(pSrc != nullptr);
      if (pSrc)
      {
         assertUnit(pSrc->pRight != nullptr);
         if (pSrc->pRight)
         {
            assertUnit(pSrc->pRight->pLeft);
            if (pSrc->pRight->pLeft)
            {
               assertUnit(pSrc->pRight->pLeft->pRight != nullptr);
               if (pSrc->pRight->pLeft->pRight)
               {
                  assertUnit(pSrc->pRight->pLeft->pRight->data == int(67));
                  assertUnit(pSrc->pRight->pLeft->pRight->pLeft == nullptr);
                  assertUnit(pSrc->pRight->pLeft->pRight->pRight == nullptr);
                  assertUnit(pSrc->pRight->pLeft->pRight->pParent == pSrc->pRight->pLeft);
                  if (pSrc->pRight->pLeft->pRight != pSrc->pRight->pLeft)
                     delete pSrc->pRight->pLeft->pRight;
                  pSrc->pRight->pLeft->pRight = nullptr;
               }
            }
         }
      }
      assertStandardFixture(pSrc);
      // teardown
      teardownStandardFixture(pSrc);
   }

   // add one moved value to the left of a single-node btree
   void test_addLeftMove_oneValue()
   {  // setup
      //                      (50) = p50
      BNode <int>* p50 = new BNode <int>(int(50));
      int s(99);
      // exercise
      addLeft(p50, std::move(s));
      // verify
      assertUnit(s == 99);
      //                      (50) = p50
      //            +----------+
      //           (99)        
      assertUnit(p50 != nullptr);
      if (p50)
      {
         assertUnit(p50->data == int(50));
         assertUnit(p50->pLeft != nullptr);
         assertUnit(p50->pRight == nullptr);
         assertUnit(p50->pParent == nullptr);

         if (p50->pLeft)
         {
            assertUnit(p50->pLeft->pLeft == nullptr);
            assertUnit(p50->pLeft->pRight == nullptr);
            assertUnit(p50->pLeft->pParent == p50);
            assertUnit(p50->pLeft->data == int(99));
         }
      }
      // teardown
      if (p50)
      {
         if (p50->pLeft && p50->pLeft != p50)
            delete p50->pLeft;
         delete p50;
      }
   }

   // add one move-value to the left of the standard fixture
   void test_addLeftMove_standardValue()
   {  // setup
      //                      (50) = pSrc
      //            +----------+----------+
      //           (38)                  (73)
      //       +----+----+           +----+----+
      //      (26)      (49)        (64)      (85)
      BNode <int>* pSrc = setupStandardFixture();
      BNode <int>* p64 = nullptr;
      if (pSrc && pSrc->pRight)
         p64 = pSrc->pRight->pLeft;
      int s(59);
      // exercise
      addLeft(p64, std::move(s));
      // verify
      assertUnit(s == 59);
      //                      (50) = pSrc
      //            +----------+----------+
      //           (38)                  (73)
      //       +----+----+           +----+----+
      //      (26)      (49)        (64)      (85)
      //                          +--+
      //                         (59)
      assertUnit(pSrc != nullptr);
      if (pSrc)
      {
         assertUnit(pSrc->pRight != nullptr);
         if (pSrc->pRight)
         {
            assertUnit(pSrc->pRight->pLeft);
            if (pSrc->pRight->pLeft)
            {
               assertUnit(pSrc->pRight->pLeft->pLeft != nullptr);
               if (pSrc->pRight->pLeft->pLeft)
               {
                  assertUnit(pSrc->pRight->pLeft->pLeft->data == int(59));
                  assertUnit(pSrc->pRight->pLeft->pLeft->pLeft == nullptr);
                  assertUnit(pSrc->pRight->pLeft->pLeft->pRight == nullptr);
                  assertUnit(pSrc->pRight->pLeft->pLeft->pParent == pSrc->pRight->pLeft);
                  if (pSrc->pRight->pLeft->pLeft != pSrc->pRight->pLeft)
                     delete pSrc->pRight->pLeft->pLeft;
                  pSrc->pRight->pLeft->pLeft = nullptr;
               }
            }
         }
      }
      assertStandardFixture(pSrc);
      // teardown
      teardownStandardFixture(pSrc);
   }

   // add one move-value to the right of a single-node btree
   void test_addRightMove_oneValue()
   {  // setup
      //                      (50) = p50
      BNode <int>* p50 = new BNode <int>(int(50));
      int s(99);
      // exercise
      addRight(p50, std::move(s));
      // verify
      assertUnit(s == 99);
      //                      (50) = p50
      //                        +----------+
      //                                  (99)        
      assertUnit(p50 != nullptr);
      if (p50)
      {
         assertUnit(p50->data == int(50));
         assertUnit(p50->pLeft == nullptr);
         assertUnit(p50->pParent == nullptr);
         assertUnit(p50->pRight != nullptr);
         if (p50->pRight)
         {
            assertUnit(p50->pRight->pLeft == nullptr);
            assertUnit(p50->pRight->pRight == nullptr);
            assertUnit(p50->pRight->pParent == p50);
            assertUnit(p50->pRight->data == int(99));
         }
      }
      // teardown
      if (p50)
      {
         if (p50->pRight && p50->pRight != p50)
            delete p50->pRight;
         delete p50;
      }
   }

   // add one move-value to the left of the standard fixture
   void test_addRightMove_standardValue()
   {  // setup
      //                      (50) = pSrc
      //            +----------+----------+
      //           (38)                  (73)
      //       +----+----+           +----+----+
      //      (26)      (49)        (64)      (85)
      BNode <int>* pSrc = setupStandardFixture();
      BNode <int>* p64 = nullptr;
      if (pSrc && pSrc->pRight)
         p64 = pSrc->pRight->pLeft;
      int s(67);
      // exercise
      addRight(p64, std::move(s));
      // verify
      assertUnit(s == 67);
      //                      (50) = pSrc
      //            +----------+----------+
      //           (38)                  (73)
      //       +----+----+           +----+----+
      //      (26)      (49)        (64)      (85)
      //                             +--+
      //                               (67)
      assertUnit(pSrc != nullptr);
      if (pSrc)
      {
         assertUnit(pSrc->pRight != nullptr);
         if (pSrc->pRight)
         {
            assertUnit(pSrc->pRight->pLeft);
            if (pSrc->pRight->pLeft)
            {
               assertUnit(pSrc->pRight->pLeft->pRight != nullptr);
               if (pSrc->pRight->pLeft->pRight)
               {
                  assertUnit(pSrc->pRight->pLeft->pRight->data == int(67));
                  assertUnit(pSrc->pRight->pLeft->pRight->pLeft == nullptr);
                  assertUnit(pSrc->pRight->pLeft->pRight->pRight == nullptr);
                  assertUnit(pSrc->pRight->pLeft->pRight->pParent == pSrc->pRight->pLeft);
                  if (pSrc->pRight->pLeft->pRight != pSrc->pRight->pLeft)
                     delete pSrc->pRight->pLeft->pRight;
                  pSrc->pRight->pLeft->pRight = nullptr;
               }
            }
         }
      }
      assertStandardFixture(pSrc);
      // teardown
      teardownStandardFixture(pSrc);
   }

   // add one node to the left of a single-node btree
   void test_addLeft_oneTree()
   {  // setup
      //                      (50) = p50
      BNode <int>* p50 = new BNode <int>(50);
      BNode <int>* p99 = new BNode <int>(99);
      // exercise
      addLeft(p50, p99);
      // verify
      //                      (50) = p50
      //            +----------+
      //           (99) = p99      
      assertUnit(p50 != nullptr);
      if (p50)
      {
         assertUnit(p50->data == int(50));
         assertUnit(p50->pParent == nullptr);
         assertUnit(p50->pRight == nullptr);
         assertUnit(p50->pLeft != nullptr);
         if (p50->pLeft)
         { 
            assertUnit(p50->pLeft->data == int(99));
            assertUnit(p50->pLeft->pLeft == nullptr);
            assertUnit(p50->pLeft->pRight == nullptr);
            assertUnit(p50->pLeft->pParent == p50);
         }
      }
      // teardown
      if (p99)
         delete p99;
      if (p50)
         delete p50;
   }

   // add one node to the left of a tree
   void test_addLeft_standardTree()
   {  // setup
      //                      (50) = p50
      //            +----------+----------+
      //           (38) = p38            (73) = p73
      BNode <int>* p50 = new BNode <int>(int(50));
      BNode <int>* p38 = new BNode <int>(int(38));
      BNode <int>* p73 = new BNode <int>(int(73));
      p50->pLeft = p38;
      p50->pRight = p73;
      p38->pParent = p73->pParent = p50;
      //                      (64) = p64
      //            +----------+----------+
      //           (61) = p61            (67) = p67
      BNode <int>* p64 = new BNode <int>(int(64));
      BNode <int>* p61 = new BNode <int>(int(61));
      BNode <int>* p67 = new BNode <int>(int(67));
      p64->pLeft = p61;
      p64->pRight = p67;
      p61->pParent = p67->pParent = p64;
      // exercise
      addLeft(p73, p64);
      // verify
      //                      (50) = p50
      //            +----------+----------+
      //           (38) = p38            (73) = p73
      //                             +----+
      //                           (64) = p64
      //                         +---+---+
      //                  p61 = (61)    (67) = p67
      assertUnit(p50 != nullptr); 
      if (p50)
      {
         assertUnit(p50->data == int(50));
         assertUnit(p50->pLeft == p38);
         assertUnit(p50->pRight == p73);
         assertUnit(p50->pParent == nullptr);
      }

      assertUnit(p38 != nullptr);
      if (p38)
      {
         assertUnit(p38->data == int(38));
         assertUnit(p38->pLeft == nullptr);
         assertUnit(p38->pRight == nullptr);
         assertUnit(p38->pParent == p50);
      }

      assertUnit(p73 != nullptr);
      if (p73)
      {
         assertUnit(p73->data == int(73));
         assertUnit(p73->pLeft == p64);
         assertUnit(p73->pRight == nullptr);
         assertUnit(p73->pParent == p50);
      }

      assertUnit(p64 != nullptr);
      if (p64)
      {
         assertUnit(p64->data == int(64));
         assertUnit(p64->pLeft == p61);
         assertUnit(p64->pRight == p67);
         assertUnit(p64->pParent == p73);
      }

      assertUnit(p61 != nullptr);
      if (p61)
      {
         assertUnit(p61->data == int(61));
         assertUnit(p61->pLeft == nullptr);
         assertUnit(p61->pRight == nullptr);
         assertUnit(p61->pParent == p64);
      }

      assertUnit(p67 != nullptr);
      if (p67)
      {
         assertUnit(p67->data == int(67));
         assertUnit(p67->pLeft == nullptr);
         assertUnit(p67->pRight == nullptr);
         assertUnit(p67->pParent == p64);
      }
      // teardown
      if (p67)
         delete p67;
      if (p61)
         delete p61;
      if (p64)
         delete p64;
      if (p73)
         delete p73;
      if (p38)
         delete p38;
      if (p50)
         delete p50;
   }

   // add one node to the right of a single-node btree
   void test_addRight_oneTree()
   {  // setup
      //                      (50) = p50
      BNode <int>* p50 = new BNode <int>(int(50));
      BNode <int>* p99 = new BNode <int>(int(99));
      // exercise
      addRight(p50, p99);
      // verify
      //                      (50) = p50
      //                       +----------+
      //                                 (99) = p99    
      assertUnit(p50 != nullptr);
      if (p50)
      {
         assertUnit(p50->data == int(50));
         assertUnit(p50->pLeft == nullptr);
         assertUnit(p50->pRight == p99);
         assertUnit(p50->pParent == nullptr);
      }

      assertUnit(p99 != nullptr);
      if (p99)
      {
         assertUnit(p99->data == int(99));
         assertUnit(p99->pLeft == nullptr);
         assertUnit(p99->pRight == nullptr);
         assertUnit(p99->pParent == p50);
      }
      // teardown
      if (p99)
         delete p99;
      if (p50)
         delete p50;
   }

   // add one node to the left of a tree
   void test_addRight_standardTree()
   {  // setup
      //                      (50) = p50
      //            +----------+----------+
      //           (38) = p38            (73) = p73
      BNode <int>* p50 = new BNode <int>(int(50));
      BNode <int>* p38 = new BNode <int>(int(38));
      BNode <int>* p73 = new BNode <int>(int(73));
      p50->pLeft = p38;
      p50->pRight = p73;
      p38->pParent = p73->pParent = p50;
      //                      (44) = p44
      //            +----------+----------+
      //           (42) = p42            (49) = p49
      BNode <int>* p44 = new BNode <int>(int(44));
      BNode <int>* p42 = new BNode <int>(int(42));
      BNode <int>* p49 = new BNode <int>(int(49));
      p44->pLeft = p42;
      p44->pRight = p49;
      p42->pParent = p49->pParent = p44;
      // exercise
      addRight(p38, p44);
      // verify
      //                      (50) = p50
      //            +----------+----------+
      //           (38) = p38            (73) = p73
      //            +----+
      //                (44) = p44
      //              +---+---+
      //       p42 = (42)    (49) = p49
      assertUnit(p50 != nullptr);
      if (p50)
      {
         assertUnit(p50->data == int(50));
         assertUnit(p50->pLeft == p38);
         assertUnit(p50->pRight == p73);
         assertUnit(p50->pParent == nullptr);
      }

      assertUnit(p38 != nullptr);
      if (p38)
      {
         assertUnit(p38->data == int(38));
         assertUnit(p38->pLeft == nullptr);
         assertUnit(p38->pRight == p44);
         assertUnit(p38->pParent == p50);
      }

      assertUnit(p73 != nullptr);
      if (p73)
      {
         assertUnit(p73->data == int(73));
         assertUnit(p73->pLeft == nullptr);
         assertUnit(p73->pRight == nullptr);
         assertUnit(p73->pParent == p50);
      }

      assertUnit(p44 != nullptr);
      if (p44)
      {
         assertUnit(p44->data == int(44));
         assertUnit(p44->pLeft == p42);
         assertUnit(p44->pRight == p49);
         assertUnit(p44->pParent == p38);
      }

      assertUnit(p42 != nullptr);
      if (p42)
      {
         assertUnit(p42->data == int(42));
         assertUnit(p42->pLeft == nullptr);
         assertUnit(p42->pRight == nullptr);
         assertUnit(p42->pParent == p44);
      }

      assertUnit(p49 != nullptr);
      if (p49)
      {
         assertUnit(p49->data == int(49));
         assertUnit(p49->pLeft == nullptr);
         assertUnit(p49->pRight == nullptr);
         assertUnit(p49->pParent == p44);
      }
      // teardown
      if (p42)
         delete p42;
      if (p49)
         delete p49;
      if (p44)
         delete p44;
      if (p73)
         delete p73;
      if (p38)
         delete p38;
      if (p50)
         delete p50;
   }

   /***************************************
    * CLEAR 
    ***************************************/

   // attempt to delete an empty BTree
   void test_clear_empty()
   {  // setup
      BNode <int>* p = nullptr;
      // exercise
      clear(p);
      // verify
      assertUnit(p == nullptr);
   }  // teardown

   // attempt to delete a B Tree with one node
   void test_clear_one()
   {  // setup
      //                      (50) = p
      BNode <int>* p = new BNode <int>(int(50));
      // exercise
      clear(p);
      // verify
      assertUnit(p == nullptr);
   }  // teardown

   // delete a standard fixture
   void test_clear_standard()
   {  // setup
      //                      (50) = p
      //            +----------+----------+
      //           (38)                  (73)
      //       +----+----+           +----+----+
      //      (26)      (49)        (64)      (85)
      BNode <int>* p = setupStandardFixture();
      // exercise
      clear(p);
      // verify
      assertUnit(p == nullptr);
   }  // teardown



   /*************************************************************
    * SETUP STANDARD FIXTURE
    *                   (50)
    *         +----------+----------+
    *        (38)                  (73)
    *    +----+----+           +----+----+
    *  (26)       (49)       (64)       (85)
    *************************************************************/
   BNode <int>* setupStandardFixture()
   {
      // allocate
      BNode <int>* p50 = new BNode <int>(int(50));
      BNode <int>* p38 = new BNode <int>(int(38));
      BNode <int>* p73 = new BNode <int>(int(73));
      BNode <int>* p26 = new BNode <int>(int(26));
      BNode <int>* p49 = new BNode <int>(int(49));
      BNode <int>* p64 = new BNode <int>(int(64));
      BNode <int>* p85 = new BNode <int>(int(85));

      // connect down
      p50->pLeft  = p38;
      p50->pRight = p73;
      p38->pLeft  = p26;
      p38->pRight = p49;
      p73->pLeft  = p64;
      p73->pRight = p85;

      // connect up
      p38->pParent = p73->pParent = p50;
      p26->pParent = p49->pParent = p38;
      p64->pParent = p85->pParent = p73;

      return p50;
   }

   /*************************************************************
    * VERIFY STANDARD FIXTURE
    *                   (50)
    *         +----------+----------+
    *        (38)                  (73)
    *    +----+----+           +----+----+
    *  (26)       (49)       (64)       (85)
    *************************************************************/
   void assertStandardFixtureParameters(const BNode <int>* pRoot, int line, const char *function)
   {
      // verify root
      assertIndirect(pRoot != nullptr);
      if (pRoot == nullptr)
         return;

      assertIndirect(pRoot->data    == int(50));
      assertIndirect(pRoot->pParent == nullptr);
      assertIndirect(pRoot->pLeft   != nullptr);
      assertIndirect(pRoot->pRight  != nullptr);


      // verify the left side of the tree
      if (pRoot->pLeft)
      {
         assertIndirect(pRoot->pLeft->data    == int(38));
         assertIndirect(pRoot->pLeft->pParent == pRoot);
         assertIndirect(pRoot->pLeft->pLeft   != nullptr);
         assertIndirect(pRoot->pLeft->pRight  != nullptr);

         // verify the left-left side of the tree
         if (pRoot->pLeft->pLeft)
         {
            assertIndirect(pRoot->pLeft->pLeft->data    == int(26));
            assertIndirect(pRoot->pLeft->pLeft->pParent == pRoot->pLeft);
            assertIndirect(pRoot->pLeft->pLeft->pLeft   == nullptr);
            assertIndirect(pRoot->pLeft->pLeft->pRight  == nullptr);
         }

         // verify the left-right side of the tree
         if (pRoot->pLeft->pRight)
         {
            assertIndirect(pRoot->pLeft->pRight->data == int(49));
            assertIndirect(pRoot->pLeft->pRight->pParent == pRoot->pLeft);
            assertIndirect(pRoot->pLeft->pRight->pLeft   == nullptr);
            assertIndirect(pRoot->pLeft->pRight->pRight  == nullptr);
         }
      }

      // verify the right side of the tree
      if (pRoot->pRight)
      {
         assertIndirect(pRoot->pRight->data    == int(73));
         assertIndirect(pRoot->pRight->pParent == pRoot);
         assertIndirect(pRoot->pRight->pLeft   != nullptr);
         assertIndirect(pRoot->pRight->pRight  != nullptr);

         // verify the right-left side of the tree
         if (pRoot->pRight->pLeft)
         {
            assertIndirect(pRoot->pRight->pLeft->data    == int(64));
            assertIndirect(pRoot->pRight->pLeft->pParent == pRoot->pRight);
            assertIndirect(pRoot->pRight->pLeft->pLeft   == nullptr);
            assertIndirect(pRoot->pRight->pLeft->pRight  == nullptr);
         }

         // verify the right-right side of the tree
         if (pRoot->pRight->pRight)
         {
            assertIndirect(pRoot->pRight->pRight->data    == int(85));
            assertIndirect(pRoot->pRight->pRight->pParent == pRoot->pRight);
            assertIndirect(pRoot->pRight->pRight->pLeft   == nullptr);
            assertIndirect(pRoot->pRight->pRight->pRight  == nullptr);
         }
      }
   }

   /*************************************************************
    * TEARDOWN STANDARD FIXTURE
    *                   ( )
    *         +----------+----------+
    *        ( )                   ( )
    *    +----+----+           +----+----+
    *   ( )       ( )         ( )       ( )
    *************************************************************/
   void teardownStandardFixture(BNode <int>* pRoot)
   {
      if (nullptr != pRoot)
      {
         if (nullptr != pRoot->pLeft && pRoot != pRoot->pLeft)
         {
            if (nullptr != pRoot->pLeft->pLeft && pRoot != pRoot->pLeft->pLeft && pRoot->pLeft != pRoot->pLeft->pLeft)
               delete pRoot->pLeft->pLeft;
            if (nullptr != pRoot->pLeft->pRight && pRoot != pRoot->pLeft->pRight && pRoot->pLeft != pRoot->pLeft->pRight)
               delete pRoot->pLeft->pRight;

            delete pRoot->pLeft;
         }

         if (nullptr != pRoot->pRight && pRoot != pRoot->pLeft)
         {
            if (nullptr != pRoot->pRight->pLeft && pRoot != pRoot->pRight->pLeft && pRoot->pRight != pRoot->pRight->pLeft)
               delete pRoot->pRight->pLeft;
            if (nullptr != pRoot->pRight->pRight && pRoot != pRoot->pRight->pRight && pRoot->pRight != pRoot->pRight->pRight)
               delete pRoot->pRight->pRight;

            delete pRoot->pRight;
         }

         delete pRoot;
      }
   }

};

#endif // DEBUG
