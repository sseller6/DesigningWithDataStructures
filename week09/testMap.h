/***********************************************************************
 * Header:
 *    TEST MAP
 * Summary:
 *    Unit tests for Map
 * Author
 *    Br. Helfrich
 ************************************************************************/

#pragma once
#ifdef DEBUG

#include "map.h"        // class under test
#include "unitTest.h"   // unit test baseclass


#include <map>
#include <vector>

/***********************************************
 * TEST MAP
 * Unit tests for the Map class
 ***********************************************/
class TestMap : public UnitTest
{
public:
   void run()
   {
      reset();

      // Construct
      test_construct_default();
      test_constructCopy_empty();
      test_constructCopy_one();
      test_constructCopy_standard();
      test_constructMove_empty();
      test_constructMove_one();
      test_constructMove_standard();
      test_constructInit_empty();
      test_constructInit_one();
      test_constructInit_standard();
      test_constructRange_empty();
      test_constructRange_one();
      test_constructRange_standard();
      test_destructor_empty();
      test_destructor_standard();

      // Assign
      test_assign_emptyToEmpty();
      test_assign_standardToEmpty();
      test_assign_emptyToStandard();
      test_assign_standardToNotempty();
      test_assignMove_emptyToEmpty();
      test_assignMove_standardToEmpty();
      test_assignMove_emptyToStandard();
      test_assignMove_standardToNotempty();
      test_assignInit_emptyToEmpty();
      test_assignInit_standardToEmpty();
      test_assignInit_emptyToStandard();
      test_assignInit_standardToNotempty();
      test_swap_emptyToEmpty();
      test_swap_standardToEmpty();
      test_swap_emptyToStandard();
      test_swap_standardToStandard();

      // Iterator
      test_begin_empty();
      test_begin_standard();
      test_end_standard();
      test_iterator_increment_standardToChild();
      test_iterator_increment_standardToParent();
      test_iterator_dereference_standardRead();

      // Access
      test_access_standardRootRead();
      test_access_standardLeftRead();
      test_access_standardRightRead();
      test_access_standardRootWrite();
      test_access_standardLeftWrite();
      test_access_standardRightWrite();
      test_access_emptyWrite();
      test_access_standardFrontInsert();
      test_access_standardMiddleInsert();
      test_at_standardRootRead();
      test_at_standardLeftRead();
      test_at_standardRightRead();
      test_at_standardRootWrite();
      test_at_standardLeftWrite();
      test_at_standardRightWrite();
      test_at_emptyWrite();
      test_at_standardWrite();
      test_find_empty();
      test_find_standardRoot();
      test_find_standardLeft();
      test_find_standardRight();
      test_find_standardMissing();

      // Insert
      test_insertCopy_empty();
      test_insertCopy_standardFront();
      test_insertCopy_standardMiddle();
      test_insertMove_empty();
      test_insertMove_standard();

      // Remove
      test_clear_empty();
      test_clear_standard();
      test_erase_emptyKey();
      test_erase_standardKey();
      test_erase_standardKeyMissing();
      test_erase_emptyIterator();
      test_erase_standardIterator();
      test_erase_standardIteratorMissing();
      test_erase_emptyRange();
      test_erase_standardRange();

      // Status
      test_empty_empty();
      test_empty_standard();
      test_size_empty();
      test_size_standard();

      report("Map");
   }

   /***************************************
    * CONSTRUCTOR
    *    map::map()
    ***************************************/

    // default constructor, no allocations
   void test_construct_default()
   {  // setup
      
      // exercise
      custom::map<std::string, int> m;
      // verify
      assertEmptyFixture(m);
   }  // teardown


   /***************************************
    * COPY
    *     map::map(const map &)
    ***************************************/

   // copy an empty map
   void test_constructCopy_empty()
   {  // setup
      custom::map<std::string, int> mSrc;
      
      // exercise
      custom::map<std::string, int> mDes(mSrc);
      // verify
      assertEmptyFixture(mSrc);
      assertEmptyFixture(mDes);
   }  // teardown

   // copy a one-element map
   void test_constructCopy_one()
   {  // setup
      //    "50"
      //   +----+
      //   | 50 |
      //   +----+
      custom::map<std::string, int> mSrc;
      custom::pair<std::string, int> p50(std::string("50"), int(50));
      custom::BST < custom::pair<std::string, int> > ::BNode* bnode50;
      bnode50 = new custom::BST < custom::pair<std::string, int> > ::BNode(p50);
      mSrc.bst.root = bnode50;
      mSrc.bst.numElements = 1;
      
      // exercise
      custom::map<std::string, int> mDes(mSrc);
      // verify
      assertUnit(mSrc.bst.root != mDes.bst.root);
      //    "50"
      //   +----+
      //   | 50 |
      //   +----+
      assertUnit(mSrc.bst.numElements == 1);
      assertUnit(mSrc.bst.root != nullptr);
      if (mSrc.bst.root)
      {
         assertUnit(mSrc.bst.root->data.first == std::string("50"));
         assertUnit(mSrc.bst.root->data.second == int(50));
         assertUnit(mSrc.bst.root->pLeft == nullptr);
         assertUnit(mSrc.bst.root->pRight == nullptr);
         assertUnit(mSrc.bst.root->pParent == nullptr);
      }
      //    "50"
      //   +----+
      //   | 50 |
      //   +----+
      assertUnit(mDes.bst.numElements == 1);
      assertUnit(mDes.bst.root != nullptr);
      if (mDes.bst.root)
      {
         assertUnit(mDes.bst.root->data.first == std::string("50"));
         assertUnit(mDes.bst.root->data.second == int(50));
         assertUnit(mDes.bst.root->pLeft == nullptr);
         assertUnit(mDes.bst.root->pRight == nullptr);
         assertUnit(mDes.bst.root->pParent == nullptr);
      }
      // teardown
      teardownStandardFixture(mSrc);
      teardownStandardFixture(mDes);
   }

   // copy the standard fixture
   void test_constructCopy_standard()
   {  // setup
      //    "30"     "50"     "70" 
      //   +----+   +----+   +----+
      //   | 30 | - | 50 | - | 70 |
      //   +----+   +----+   +----+
      custom::map<std::string, int> mSrc;
      setupStandardFixture(mSrc);
      
      // exercise
      custom::map<std::string, int> mDes(mSrc);
      // verify
      //    "30"     "50"     "70" 
      //   +----+   +----+   +----+
      //   | 30 | - | 50 | - | 70 |
      //   +----+   +----+   +----+
      assertUnit(mSrc.bst.root != mDes.bst.root);
      assertStandardFixture(mSrc);
      assertStandardFixture(mDes);
      // teardown
      teardownStandardFixture(mSrc);
      teardownStandardFixture(mDes);
   }

   /***************************************
    * MOVE
    *     map::map(map &&)
    ***************************************/

    // copy an empty map
   void test_constructMove_empty()
   {  // setup
      custom::map<std::string, int> mSrc;
      
      // exercise
      custom::map<std::string, int> mDes(std::move(mSrc));
      // verify
      assertEmptyFixture(mSrc);
      assertEmptyFixture(mDes);
   }  // teardown

   // copy a one-element map
   void test_constructMove_one()
   {  // setup
      //    "50"
      //   +----+
      //   | 50 |
      //   +----+
      custom::map<std::string, int> mSrc;
      custom::pair<std::string, int> p50(std::string("50"), int(50));
      custom::BST < custom::pair<std::string, int> > ::BNode* bnode50;
      bnode50 = new custom::BST < custom::pair<std::string, int> > ::BNode(p50);
      mSrc.bst.root = bnode50;
      mSrc.bst.numElements = 1;
      
      // exercise
      custom::map<std::string, int> mDes(std::move(mSrc));
      // verify
      assertUnit(mSrc.bst.root != mDes.bst.root);
      //    "50"
      //   +----+
      //   | 50 |
      //   +----+
      assertUnit(mDes.bst.numElements == 1);
      assertUnit(mDes.bst.root != nullptr);
      if (mDes.bst.root)
      {
         assertUnit(mDes.bst.root->data.first == std::string("50"));
         assertUnit(mDes.bst.root->data.second == int(50));
         assertUnit(mDes.bst.root->pLeft == nullptr);
         assertUnit(mDes.bst.root->pRight == nullptr);
         assertUnit(mDes.bst.root->pParent == nullptr);
      }
      assertEmptyFixture(mSrc);
      // teardown
      teardownStandardFixture(mDes);
   }

   // copy the standard fixture
   void test_constructMove_standard()
   {  // setup
      //    "30"     "50"     "70" 
      //   +----+   +----+   +----+
      //   | 30 | - | 50 | - | 70 |
      //   +----+   +----+   +----+
      custom::map<std::string, int> mSrc;
      setupStandardFixture(mSrc);
      
      // exercise
      custom::map<std::string, int> mDes(std::move(mSrc));
      // verify
      //    "30"     "50"     "70" 
      //   +----+   +----+   +----+
      //   | 30 | - | 50 | - | 70 |
      //   +----+   +----+   +----+
      assertUnit(mSrc.bst.root != mDes.bst.root);
      assertStandardFixture(mDes);
      assertEmptyFixture(mSrc);
      // teardown
      teardownStandardFixture(mDes);
   }

   /***************************************
    * INITIALIZER LIST CONSTRUCTOR
    *     map::map(const initializer_list &)
    ***************************************/

    // copy an empty map
   void test_constructInit_empty()
   {  // setup
      //     {  }
      std::initializer_list<custom::pair<std::string, int>> il{};
      
      // exercise
      custom::map<std::string, int> m(il);
      // verify
      assertEmptyFixture(m);
   }  // teardown

   // copy a one-element map
   void test_constructInit_one()
   {  // setup
      //      { ("50",50) }
      custom::pair<std::string, int> p50(std::string("50"), int(50));
      std::initializer_list<custom::pair<std::string, int>> il{p50};
      
      // exercise
      custom::map<std::string, int> m(il);
      // verify
      //    "50"
      //   +----+
      //   | 50 |
      //   +----+
      assertUnit(m.bst.numElements == 1);
      assertUnit(m.bst.root != nullptr);
      if (m.bst.root)
      {
         assertUnit(m.bst.root->data.first == std::string("50"));
         assertUnit(m.bst.root->data.second == int(50));
         assertUnit(m.bst.root->pLeft == nullptr);
         assertUnit(m.bst.root->pRight == nullptr);
         assertUnit(m.bst.root->pParent == nullptr);
      }
      // teardown
      teardownStandardFixture(m);
   }

   // copy the standard fixture
   void test_constructInit_standard()
   {  // setup
      //      { ("50",50)  ("30",30)  ("70",70) }
      custom::pair<std::string, int> p50(std::string("50"), int(50));
      custom::pair<std::string, int> p30(std::string("30"), int(30));
      custom::pair<std::string, int> p70(std::string("70"), int(70));
      std::initializer_list<custom::pair<std::string, int>> il{ p50, p30, p70 };
      
      // exercise
      custom::map<std::string, int> m(il);
      // verify
      //    "30"     "50"     "70" 
      //   +----+   +----+   +----+
      //   | 30 | - | 50 | - | 70 |
      //   +----+   +----+   +----+
      assertStandardFixture(m);
      // teardown
      teardownStandardFixture(m);
   }

   /***************************************
    * RANGE CONSTRUCTOR
    *     map::map(first, last)
    ***************************************/

    // copy an empty map
   void test_constructRange_empty()
   {  // setup
      //     {  }
      std::initializer_list<custom::pair<std::string, int>> il{};
      auto itBegin = il.begin();
      auto itEnd = il.end();
      
      // exercise
      custom::map<std::string, int> m(itBegin, itEnd);
      // verify
      assertEmptyFixture(m);
   }  // teardown

   // copy a one-element map
   void test_constructRange_one()
   {  // setup
      //      { ("50",50) }
      custom::pair<std::string, int> p50(std::string("50"), int(50));
      std::initializer_list<custom::pair<std::string, int>> il{ p50 };
      auto itBegin = il.begin();
      auto itEnd = il.end();
      
      // exercise
      custom::map<std::string, int> m(itBegin, itEnd);
      // verify
      //    "50"
      //   +----+
      //   | 50 |
      //   +----+
      assertUnit(m.bst.numElements == 1);
      assertUnit(m.bst.root != nullptr);
      if (m.bst.root)
      {
         assertUnit(m.bst.root->data.first == std::string("50"));
         assertUnit(m.bst.root->data.second == int(50));
         assertUnit(m.bst.root->pLeft == nullptr);
         assertUnit(m.bst.root->pRight == nullptr);
         assertUnit(m.bst.root->pParent == nullptr);
      }
      // teardown
      teardownStandardFixture(m);
   }

   // copy the standard fixture
   void test_constructRange_standard()
   {  // setup
      //      { ("50",50)  ("30",30)  ("70",70) }
      custom::pair<std::string, int> p50(std::string("50"), int(50));
      custom::pair<std::string, int> p30(std::string("30"), int(30));
      custom::pair<std::string, int> p70(std::string("70"), int(70));
      std::initializer_list<custom::pair<std::string, int>> il{ p50, p30, p70 };
      auto itBegin = il.begin();
      auto itEnd = il.end();
      
      // exercise
      custom::map<std::string, int> m(itBegin, itEnd);
      // verify
      //    "30"     "50"     "70" 
      //   +----+   +----+   +----+
      //   | 30 | - | 50 | - | 70 |
      //   +----+   +----+   +----+
      assertStandardFixture(m);
      // teardown
      teardownStandardFixture(m);
   }

   /***************************************
    * DESTRUCTOR
    ***************************************/

    // destroy an empty set
   void test_destructor_empty()
   {  // setup
      {
         custom::map<std::string, int> m;
         
      }  // exercise
      // verify
   }  // teardown

   // destroy the standard fixture
   void test_destructor_standard()
   {  // setup
      {
         //    "30"     "50"     "70" 
         //   +----+   +----+   +----+
         //   | 30 | - | 50 | - | 70 |
         //   +----+   +----+   +----+
         custom::map<std::string, int> m;
         setupStandardFixture(m);
         
      }  // exercise
      // verify
   }  // teardown

   /***************************************
    * SIZE, EMPTY
    *    map::empty()
    *    map::size()
    ***************************************/

    // is the empty map empty?
   void test_empty_empty()
   {  // setup
      custom::map<std::string, int> m;
      
      // exercise
      bool empty = m.empty();
      // verify
      assertUnit(empty == true);
      assertEmptyFixture(m);
   }  // teardown

   // is the standard fixture empty?
   void test_empty_standard()
   {  // setup
      //    "30"     "50"     "70" 
      //   +----+   +----+   +----+
      //   | 30 | - | 50 | - | 70 |
      //   +----+   +----+   +----+
      custom::map<std::string, int> m;
      setupStandardFixture(m);
      
      // exercise
      bool empty = m.empty();
      // verify
      assertUnit(empty == false);
      assertStandardFixture(m);
      // teardown
      teardownStandardFixture(m);
   }

   // what is the size of an empty map?
   void test_size_empty()
   {  // setup
      custom::map<std::string, int> m;
      
      // exercise
      size_t size = m.size();
      // verify
      assertUnit(size == 0);
      assertEmptyFixture(m);
   }  // teardown

   // what is the size of the standard fixture?
   void test_size_standard()
   {  // setup
      //    "30"     "50"     "70" 
      //   +----+   +----+   +----+
      //   | 30 | - | 50 | - | 70 |
      //   +----+   +----+   +----+
      custom::map<std::string, int> m;
      setupStandardFixture(m);
      
      // exercise
      size_t size = m.size();
      // verify
      assertUnit(size == 3);
      assertStandardFixture(m);
      // teardown
      teardownStandardFixture(m);
   }

   /***************************************
    * ASSIGNMENT
    *    map::operator=(const map &)
    ***************************************/

   // assign: empty = empty
   void test_assign_emptyToEmpty()
   {  // setup
      custom::map<std::string, int> mSrc;
      custom::map<std::string, int> mDes;
      
      // exercise
      mDes = mSrc;
      // verify
      assertEmptyFixture(mSrc);
      assertEmptyFixture(mDes);
   }  // teardown

   // assign: empty = standard
   void test_assign_standardToEmpty()
   {  // setup
      //    "30"     "50"     "70"   = mSrc
      //   +----+   +----+   +----+
      //   | 30 | - | 50 | - | 70 |
      //   +----+   +----+   +----+
      custom::map<std::string, int> mSrc;
      setupStandardFixture(mSrc);
      custom::map<std::string, int> mDes;
      
      // exercise
      mDes = mSrc;
      // verify
      assertUnit(mSrc.bst.root != mDes.bst.root);
      //    "30"     "50"     "70" 
      //   +----+   +----+   +----+
      //   | 30 | - | 50 | - | 70 |
      //   +----+   +----+   +----+
      assertStandardFixture(mSrc);
      assertStandardFixture(mDes);
      // teardown
      teardownStandardFixture(mSrc);
      teardownStandardFixture(mDes);
   }

   // assign: standard = empty
   void test_assign_emptyToStandard()
   {  // setup
      custom::map<std::string, int> mSrc;
      //    "30"     "50"     "70"   = mDes
      //   +----+   +----+   +----+
      //   | 30 | - | 50 | - | 70 |
      //   +----+   +----+   +----+
      custom::map<std::string, int> mDes;
      setupStandardFixture(mDes);
      
      // exercise
      mDes = mSrc;
      // verify
      assertEmptyFixture(mSrc);
      assertEmptyFixture(mDes);
   }  // teardown

   // assign: notempty = standard
   void test_assign_standardToNotempty() 
   {  // setup
      //    "30"     "50"     "70"   = mSrc
      //   +----+   +----+   +----+
      //   | 30 | - | 50 | - | 70 |
      //   +----+   +----+   +----+
      //        (50)
      //    +-----+-----+
      //  (30)        (70)
      custom::map<std::string, int> mSrc;
      setupStandardFixture(mSrc);
      //    "40"     "60"  = mDes
      //   +----+   +----+ 
      //   | 40 | - | 60 | 
      //   +----+   +----+ 
      //     p40      p60
      //        (40)
      //          +-----+
      //              (60)
      custom::map<std::string, int> mDes;
      custom::pair<std::string, int> pair40(std::string("40"), int(40));
      custom::pair<std::string, int> pair60(std::string("60"), int(60));
      custom::BST < custom::pair<std::string, int> > ::BNode* bnode40;
      custom::BST < custom::pair<std::string, int> > ::BNode* bnode60;
      bnode40 = new custom::BST < custom::pair<std::string, int> > ::BNode(pair40);
      bnode60 = new custom::BST < custom::pair<std::string, int> > ::BNode(pair60);
      bnode40->pRight = bnode60;
      bnode60->pParent = bnode40;
      mDes.bst.root = bnode40;
      mDes.bst.numElements = 2;
      
      // exercise
      mDes = mSrc;
      // verify
      assertUnit(mSrc.bst.root != mDes.bst.root);
      //    "30"     "50"     "70"   
      //   +----+   +----+   +----+
      //   | 30 | - | 50 | - | 70 |
      //   +----+   +----+   +----+
      assertStandardFixture(mSrc);
      assertStandardFixture(mDes);
      // teardown
      teardownStandardFixture(mSrc);
      teardownStandardFixture(mDes);
   }

   /***************************************
    * ASSIGNMENT - Move
    *    map::operator=(map &&)
    ***************************************/

    // assign: empty = move(empty)
   void test_assignMove_emptyToEmpty()
   {  // setup
      custom::map<std::string, int> mSrc;
      custom::map<std::string, int> mDes;
      
      // exercise
      mDes = std::move(mSrc);
      // verify
      assertEmptyFixture(mSrc);
      assertEmptyFixture(mDes);
   }  // teardown

   // assign: empty = move(standard)
   void test_assignMove_standardToEmpty()
   {  // setup
      //    "30"     "50"     "70"   = mSrc
      //   +----+   +----+   +----+
      //   | 30 | - | 50 | - | 70 |
      //   +----+   +----+   +----+
      custom::map<std::string, int> mSrc;
      setupStandardFixture(mSrc);
      custom::map<std::string, int> mDes;
      
      // exercise
      mDes = std::move(mSrc);
      // verify
      assertUnit(mSrc.bst.root != mDes.bst.root);
      //    "30"     "50"     "70" = mDes
      //   +----+   +----+   +----+
      //   | 30 | - | 50 | - | 70 |
      //   +----+   +----+   +----+
      assertStandardFixture(mDes);
      assertEmptyFixture(mSrc);
      // teardown
      teardownStandardFixture(mDes);
   }

   // assign: standard = move(empty)
   void test_assignMove_emptyToStandard()
   {  // setup
      custom::map<std::string, int> mSrc;
      //    "30"     "50"     "70"   = mDes
      //   +----+   +----+   +----+
      //   | 30 | - | 50 | - | 70 |
      //   +----+   +----+   +----+
      custom::map<std::string, int> mDes;
      setupStandardFixture(mDes);
      
      // exercise
      mDes = std::move(mSrc);
      // verify
      assertEmptyFixture(mSrc);
      assertEmptyFixture(mDes);
   }  // teardown

   // assign: notempty = move(standard)
   void test_assignMove_standardToNotempty()
   {  // setup
      //    "30"     "50"     "70"   = mSrc
      //   +----+   +----+   +----+
      //   | 30 | - | 50 | - | 70 |
      //   +----+   +----+   +----+
      custom::map<std::string, int> mSrc;
      setupStandardFixture(mSrc);
      //    "40"     "60"  = mDes
      //   +----+   +----+ 
      //   | 40 | - | 60 | 
      //   +----+   +----+ 
      //     p40      p60
      custom::map<std::string, int> mDes;
      custom::pair<std::string, int> pair40(std::string("40"), int(40));
      custom::pair<std::string, int> pair60(std::string("60"), int(60));
      custom::BST < custom::pair<std::string, int> > ::BNode* bnode40;
      custom::BST < custom::pair<std::string, int> > ::BNode* bnode60;
      bnode40 = new custom::BST < custom::pair<std::string, int> > ::BNode(pair40);
      bnode60 = new custom::BST < custom::pair<std::string, int> > ::BNode(pair60);
      bnode40->pRight = bnode60;
      bnode60->pParent = bnode40;
      mDes.bst.root = bnode40;
      mDes.bst.numElements = 2;
      
      // exercise
      mDes = std::move(mSrc);
      // verify
      assertUnit(mSrc.bst.root != mDes.bst.root);
      //    "30"     "50"     "70"   = mDes
      //   +----+   +----+   +----+
      //   | 30 | - | 50 | - | 70 |
      //   +----+   +----+   +----+
      assertEmptyFixture(mSrc);
      assertStandardFixture(mDes);
      // teardown
      teardownStandardFixture(mDes);
   }

   /***************************************
    * ASSIGNMENT - Initialization List
    *    map::operator={}
    ***************************************/

    // assign: empty = {}
   void test_assignInit_emptyToEmpty()
   {  // setup
      //      {  } = il
      std::initializer_list<custom::pair<std::string, int>> il{ };
      custom::map<std::string, int> m;
      
      // exercise
      m = il;
      // verify
      assertEmptyFixture(m);
   }  // teardown

   // assign: empty = {50, 30, 70}
   void test_assignInit_standardToEmpty()
   {  // setup
      //      { ("50",50) ("30",30) ("70",70)}
      custom::pair<std::string, int> p50(std::string("50"), int(50));
      custom::pair<std::string, int> p30(std::string("30"), int(30));
      custom::pair<std::string, int> p70(std::string("70"), int(70));
      std::initializer_list<custom::pair<std::string, int>> il{ p50, p30, p70 };
      custom::map<std::string, int> m;
      
      // exercise
      m = il;
      // verify
      //    "30"     "50"     "70" = m
      //   +----+   +----+   +----+
      //   | 30 | - | 50 | - | 70 |
      //   +----+   +----+   +----+
      assertStandardFixture(m);
      // teardown
      teardownStandardFixture(m);
   }

   // assign: standard = move(empty)
   void test_assignInit_emptyToStandard()
   {  // setup
      //      {  } = il
      std::initializer_list<custom::pair<std::string, int>> il{ };
      //    "30"     "50"     "70"   = m
      //   +----+   +----+   +----+
      //   | 30 | - | 50 | - | 70 |
      //   +----+   +----+   +----+
      custom::map<std::string, int> m;
      setupStandardFixture(m);
      
      // exercise
      m = il;
      // verify
      assertEmptyFixture(m);
   }  // teardown

   // assign: notempty = move(standard)
   void test_assignInit_standardToNotempty()
   {  // setup
      //      { ("50",50) ("30",30) ("70",70)}
      custom::pair<std::string, int> p50(std::string("50"), int(50));
      custom::pair<std::string, int> p30(std::string("30"), int(30));
      custom::pair<std::string, int> p70(std::string("70"), int(70));
      std::initializer_list<custom::pair<std::string, int>> il{ p50, p30, p70 };
      //    "40"     "60"  = m
      //   +----+   +----+ 
      //   | 40 | - | 60 | 
      //   +----+   +----+ 
      //     p40      p60
      custom::map<std::string, int> m;
      custom::pair<std::string, int> pair40(std::string("40"), int(40));
      custom::pair<std::string, int> pair60(std::string("60"), int(60));
      custom::BST < custom::pair<std::string, int> > ::BNode* bnode40;
      custom::BST < custom::pair<std::string, int> > ::BNode* bnode60;
      bnode40 = new custom::BST < custom::pair<std::string, int> > ::BNode(pair40);
      bnode60 = new custom::BST < custom::pair<std::string, int> > ::BNode(pair60);
      bnode40->pRight = bnode60;
      bnode60->pParent = bnode40;
      m.bst.root = bnode40;
      m.bst.numElements = 2;
      
      // exercise
      m = il;
      // verify
      //    "30"     "50"     "70"   = m
      //   +----+   +----+   +----+
      //   | 30 | - | 50 | - | 70 |
      //   +----+   +----+   +----+
      assertStandardFixture(m);
      // teardown
      teardownStandardFixture(m);
   }

   /***************************************
    * SWAP
    *    swap(lhs, rhs)
    ***************************************/

    // swap(empty, empty)
   void test_swap_emptyToEmpty()
   {  // setup
      custom::map<std::string, int> mRHS;
      custom::map<std::string, int> mLHS;
      
      // exercise
      swap(mLHS, mRHS);
      // verify
      assertEmptyFixture(mRHS);
      assertEmptyFixture(mLHS);
   }  // teardown

   // swap(standard, empty)
   void test_swap_standardToEmpty()
   {  // setup
      //    "30"     "50"     "70"   = mLHS
      //   +----+   +----+   +----+
      //   | 30 | - | 50 | - | 70 |
      //   +----+   +----+   +----+
      custom::map<std::string, int> mLHS;
      setupStandardFixture(mLHS);
      custom::map<std::string, int> mRHS;
      
      // exercise
      swap(mLHS, mRHS);
      // verify
      assertUnit(mLHS.bst.root != mRHS.bst.root);
      //    "30"     "50"     "70" = mRHS
      //   +----+   +----+   +----+
      //   | 30 | - | 50 | - | 70 |
      //   +----+   +----+   +----+
      assertStandardFixture(mRHS);
      assertEmptyFixture(mLHS);
      // teardown
      teardownStandardFixture(mRHS);
   }

   // swap(empty, standard)
   void test_swap_emptyToStandard()
   {  // setup
      custom::map<std::string, int> mLHS;
      //    "30"     "50"     "70"   = mRHS
      //   +----+   +----+   +----+
      //   | 30 | - | 50 | - | 70 |
      //   +----+   +----+   +----+
      custom::map<std::string, int> mRHS;
      setupStandardFixture(mRHS);
      
      // exercise
      swap(mLHS, mRHS);
      // verify
      assertStandardFixture(mLHS);
      assertEmptyFixture(mRHS);
      // teardown 
      teardownStandardFixture(mLHS);
   }

   // swap(standard, different)
   void test_swap_standardToStandard()
   {  // setup
      //    "30"     "50"     "70"   = mLHS
      //   +----+   +----+   +----+
      //   | 30 | - | 50 | - | 70 |
      //   +----+   +----+   +----+
      custom::map<std::string, int> mLHS;
      setupStandardFixture(mLHS);
      //    "40"     "60"  = mRHS
      //   +----+   +----+ 
      //   | 40 | - | 60 | 
      //   +----+   +----+ 
      //     p40      p60
      custom::map<std::string, int> mRHS;
      custom::pair<std::string, int> pair40(std::string("40"), int(40));
      custom::pair<std::string, int> pair60(std::string("60"), int(60));
      custom::BST < custom::pair<std::string, int> > ::BNode* bnode40;
      custom::BST < custom::pair<std::string, int> > ::BNode* bnode60;
      bnode40 = new custom::BST < custom::pair<std::string, int> > ::BNode(pair40);
      bnode60 = new custom::BST < custom::pair<std::string, int> > ::BNode(pair60);
      bnode40->pRight = bnode60;
      bnode60->pParent = bnode40;
      mRHS.bst.root = bnode40;
      mRHS.bst.numElements = 2;
      
      // exercise
      swap(mLHS, mRHS);
      // verify
      assertUnit(mLHS.bst.root != mRHS.bst.root);
      //    "30"     "50"     "70"   = mRHS
      //   +----+   +----+   +----+
      //   | 30 | - | 50 | - | 70 |
      //   +----+   +----+   +----+
      assertStandardFixture(mRHS);
      //    "40"     "60"  = mLHS
      //   +----+   +----+ 
      //   | 40 | - | 60 | 
      //   +----+   +----+ 
      assertUnit(mLHS.bst.numElements == 2);
      assertUnit(mLHS.bst.root != nullptr);
      //         (40)
      //          +-----+
      //               (60)
      if (mLHS.bst.root)
      {
         assertUnit(mLHS.bst.root->data.first == std::string("40"));
         assertUnit(mLHS.bst.root->data.second == int(40));
         assertUnit(mLHS.bst.root->pParent == nullptr);
         assertUnit(mLHS.bst.root->pLeft == nullptr);
         assertUnit(mLHS.bst.root->pRight != nullptr);
         if (mLHS.bst.root->pRight)
         {
            assertUnit(mLHS.bst.root->pRight->data.first == std::string("60"));
            assertUnit(mLHS.bst.root->pRight->data.second == int(60));
            assertUnit(mLHS.bst.root->pRight->pParent == mLHS.bst.root);
            assertUnit(mLHS.bst.root->pRight->pLeft == nullptr);
            assertUnit(mLHS.bst.root->pRight->pRight == nullptr);
         }
      }
      // teardown
      teardownStandardFixture(mLHS);
      teardownStandardFixture(mRHS);
   }


   /***************************************
    * CLEAR
    *     map::clear()
    ***************************************/

   // clear an empty map
   void test_clear_empty()
   {  // setup
      custom::map<std::string, int> m;
      
      // exercise
      m.clear();
      // verify
      assertEmptyFixture(m);
   }  // teardown

   // clear the standard map
   void test_clear_standard()
   {  // setup
      //    "30"     "50"     "70"   = m
      //   +----+   +----+   +----+
      //   | 30 | - | 50 | - | 70 |
      //   +----+   +----+   +----+
      custom::map<std::string, int> m;
      setupStandardFixture(m);
      
      // exercise
      m.clear();
      // verify
      assertEmptyFixture(m);
   }  // teardown


   /***************************************
    * ITERATOR
    *     map::begin()
    *     map::end()
    *     map::iterator::operaator++()
    *     map::iterator::operator*()
    ***************************************/

   // begin() from an empty map
   void test_begin_empty()
   {  // setup
      custom::map<std::string, int> m;
      custom::map<std::string, int>::iterator it;
      // exercise
      it = m.begin();
      // verify
      assertUnit(it.it.pNode == nullptr);
      assertEmptyFixture(m);
   }  // teardown

   // begin() from the standard fixture
   void test_begin_standard()
   {  // setup
      custom::map<std::string, int>::iterator it;
      //    "30"     "50"     "70"   = m
      //   +----+   +----+   +----+
      //   | 30 | - | 50 | - | 70 |
      //   +----+   +----+   +----+
      custom::map<std::string, int> m;
      setupStandardFixture(m);
      
      // exercise
      it = m.begin();
      // verify
      //    "30"     "50"     "70"   = m
      //   +----+   +----+   +----+
      //   | 30 | - | 50 | - | 70 |
      //   +----+   +----+   +----+
      //     it
      assertUnit(it.it.pNode == m.bst.root->pLeft);
      assertStandardFixture(m);
      // teardown
      teardownStandardFixture(m);
   }

   // end() from the standard fixture
   void test_end_standard()
   {  // setup
      custom::map<std::string, int>::iterator it;
      //    "30"     "50"     "70"   = m
      //   +----+   +----+   +----+
      //   | 30 | - | 50 | - | 70 |
      //   +----+   +----+   +----+
      custom::map<std::string, int> m;
      setupStandardFixture(m);
      
      // exercise
      it = m.end();
      // verify
      assertUnit(it.it.pNode == nullptr);
      //    "30"     "50"     "70"   = m
      //   +----+   +----+   +----+
      //   | 30 | - | 50 | - | 70 |
      //   +----+   +----+   +----+
      //                               it
      assertStandardFixture(m);
      // teardown
      teardownStandardFixture(m);
   }

   // iterator increment to the parent from the standard fixture
   void test_iterator_increment_standardToParent()
   {  // setup
      custom::map<std::string, int>::iterator it;
      //    "30"     "50"     "70"   = m
      //   +----+   +----+   +----+
      //   | 30 | - | 50 | - | 70 |
      //   +----+   +----+   +----+
      //     it
      custom::map<std::string, int> m;
      setupStandardFixture(m);
      it.it.pNode = m.bst.root->pLeft;
      
      // exercise
      ++it;
      // verify
      //    "30"     "50"     "70"   = m
      //   +----+   +----+   +----+
      //   | 30 | - | 50 | - | 70 |
      //   +----+   +----+   +----+
      //              it
      assertUnit(it.it.pNode == m.bst.root);
      assertStandardFixture(m);
      // teardown
      teardownStandardFixture(m);
   }

   // iterator increment to the child from the standard fixture
   void test_iterator_increment_standardToChild()
   {  // setup
      custom::map<std::string, int>::iterator it;
      //    "30"     "50"     "70"   = m
      //   +----+   +----+   +----+
      //   | 30 | - | 50 | - | 70 |
      //   +----+   +----+   +----+
      //              it
      custom::map<std::string, int> m;
      setupStandardFixture(m);
      it.it.pNode = m.bst.root;
      
      // exercise
      ++it;
      // verify
      assertUnit(it.it.pNode == m.bst.root->pRight);
      //    "30"     "50"     "70"   = m
      //   +----+   +----+   +----+
      //   | 30 | - | 50 | - | 70 |
      //   +----+   +----+   +----+
      //                       it
      assertStandardFixture(m);
      // teardown
      teardownStandardFixture(m);
   }

   // read one element from the standard fixture
   void test_iterator_dereference_standardRead()
   {  // setup
      custom::map<std::string, int>::iterator it;
      //    "30"     "50"     "70"   = m
      //   +----+   +----+   +----+
      //   | 30 | - | 50 | - | 70 |
      //   +----+   +----+   +----+
      //              it
      custom::map<std::string, int> m;
      setupStandardFixture(m);
      it.it.pNode = m.bst.root;
      
      // exercise
      custom::pair<std::string, int> value = *it;
      // verify
      assertUnit(value.first == std::string("50"));
      assertUnit(value.second == int(50));
      //    "30"     "50"     "70"   = m
      //   +----+   +----+   +----+
      //   | 30 | - | 50 | - | 70 |
      //   +----+   +----+   +----+
      //              it
      assertStandardFixture(m);
      // teardown
      teardownStandardFixture(m);
   }

   /***************************************
    * FIND
    *    map::find()
    ***************************************/

   // attempt to find something from an empty map
   void test_find_empty()
   {  // setup
      custom::map<std::string, int> m;
      custom::map<std::string, int>::iterator it;
      std::string s50("50");
      
      // exercise
      it = m.find(s50);
      // verify
      assertUnit(it.it.pNode == nullptr);
      assertEmptyFixture(m);
   }  // teardown

   // attempt to find something at the root from the standard fixture
   void test_find_standardRoot()
   {  // setup
      custom::map<std::string, int>::iterator it;
      //    "30"     "50"     "70"   = m
      //   +----+   +----+   +----+
      //   | 30 | - | 50 | - | 70 |
      //   +----+   +----+   +----+
      custom::map<std::string, int> m;
      setupStandardFixture(m);
      std::string s50("50");
      
      // exercise
      it = m.find(s50);
      // verify
      //    "30"     "50"     "70"   = m
      //   +----+   +----+   +----+
      //   | 30 | - | 50 | - | 70 |
      //   +----+   +----+   +----+
      //              it
      assertUnit(it.it.pNode == m.bst.root);
      assertStandardFixture(m);
      // teardown
      teardownStandardFixture(m);
   }

   // attempt to find something at the left corner of the standard fixture
   void test_find_standardLeft()
   {  // setup
      custom::map<std::string, int>::iterator it;
      //    "30"     "50"     "70"   = m
      //   +----+   +----+   +----+
      //   | 30 | - | 50 | - | 70 |
      //   +----+   +----+   +----+
      custom::map<std::string, int> m;
      setupStandardFixture(m);
      std::string s30("30");
      
      // exercise
      it = m.find(s30);
      // verify
      //    "30"     "50"     "70"   = m
      //   +----+   +----+   +----+
      //   | 30 | - | 50 | - | 70 |
      //   +----+   +----+   +----+
      //    it
      assertUnit(it.it.pNode == m.bst.root->pLeft);
      assertStandardFixture(m);
      // teardown
      teardownStandardFixture(m);
   }

   // attempt to find something at the right corner of the standard fixture
   void test_find_standardRight()
   {  // setup
      custom::map<std::string, int>::iterator it;
      //    "30"     "50"     "70"   = m
      //   +----+   +----+   +----+
      //   | 30 | - | 50 | - | 70 |
      //   +----+   +----+   +----+
      custom::map<std::string, int> m;
      setupStandardFixture(m);
      std::string s70("70");
      
      // exercise
      it = m.find(s70);
      // verify
      //    "30"     "50"     "70"   = m
      //   +----+   +----+   +----+
      //   | 30 | - | 50 | - | 70 |
      //   +----+   +----+   +----+
      //                        it
      assertUnit(it.it.pNode == m.bst.root->pRight);
      assertStandardFixture(m);
      // teardown
      teardownStandardFixture(m);
   }

   // attempt to find something from the standard fixture that is not there
   void test_find_standardMissing()
   {  // setup
      custom::map<std::string, int>::iterator it;
      //    "30"     "50"     "70"   = m
      //   +----+   +----+   +----+
      //   | 30 | - | 50 | - | 70 |
      //   +----+   +----+   +----+
      custom::map<std::string, int> m;
      setupStandardFixture(m);
      std::string s99("99");
      
      // exercise
      it = m.find(s99);
      // verify
      //    "30"     "50"     "70"   = m
      //   +----+   +----+   +----+
      //   | 30 | - | 50 | - | 70 |
      //   +----+   +----+   +----+
      //                                     it
      assertUnit(it.it.pNode == nullptr);
      assertStandardFixture(m);
      // teardown
      teardownStandardFixture(m);
   }

   /***************************************
    * INSERT
    *    map::insert(const T &)
    ***************************************/

   // insert into an empty fixture
   void test_insertCopy_empty()
   {  // setup
      custom::map<std::string, int> m;
      custom::pair<std::string, int> pair50(std::string("50"), int(50));
      
      // exercise
      m.insert(pair50);
      // verify
      //    "50"
      //   +----+
      //   | 50 |
      //   +----+
      assertUnit(m.bst.numElements == 1);
      assertUnit(m.bst.root != nullptr);
      if (m.bst.root)
      {
         assertUnit(m.bst.root->data.first == std::string("50"));
         assertUnit(m.bst.root->data.second == int(50));
         assertUnit(m.bst.root->pLeft == nullptr);
         assertUnit(m.bst.root->pRight == nullptr);
         assertUnit(m.bst.root->pParent == nullptr);
      }
      // teardown
      teardownStandardFixture(m);
   }

   // insert onto the front of the standard fixture
   void test_insertCopy_standardFront()
   {  // setup
      custom::pair<std::string, int> pair10(std::string("10"), int(10));
      //    "30"     "50"     "70"   = m
      //   +----+   +----+   +----+
      //   | 30 | - | 50 | - | 70 |
      //   +----+   +----+   +----+
      custom::map<std::string, int> m;
      setupStandardFixture(m);
      custom::pair<custom::map<std::string, int>::iterator, bool> pReturn;
      
      // exercise
      pReturn = m.insert(pair10);
      // verify
      //    "10"     "30"     "50"     "70"   = m
      //   +----+   +----+   +----+   +----+
      //   | 10 | - | 30 | - | 50 | - | 70 |
      //   +----+   +----+   +----+   +----+
      //   pReturn
      //
      assertUnit(pReturn.first.it.pNode != nullptr);
      assertUnit(pReturn.second == true);
      if (m.bst.root && m.bst.root->pLeft)
         assertUnit(pReturn.first.it.pNode == m.bst.root->pLeft->pLeft);
      assertUnit(m.bst.numElements == 4);
      assertUnit(m.bst.root != nullptr);
      //                  (50)
      //              +-----+-----+
      //            (30)        (70)
      //          +---+
      //        (10)
      if (m.bst.root)
      {
         assertUnit(m.bst.root->data.first == std::string("50"));
         assertUnit(m.bst.root->data.second == int(50));
         assertUnit(m.bst.root->pParent == nullptr);
         assertUnit(m.bst.root->pLeft != nullptr);
         if (m.bst.root->pLeft)
         {
            assertUnit(m.bst.root->pLeft->data.first == std::string("30"));
            assertUnit(m.bst.root->pLeft->data.second == int(30));
            assertUnit(m.bst.root->pLeft->pParent == m.bst.root);
            assertUnit(m.bst.root->pLeft->pLeft != nullptr);
            assertUnit(m.bst.root->pLeft->pRight == nullptr);
            if (m.bst.root->pLeft->pLeft)
            {
               assertUnit(m.bst.root->pLeft->pLeft->data.first == std::string("10"));
               assertUnit(m.bst.root->pLeft->pLeft->data.second == int(10));
               assertUnit(m.bst.root->pLeft->pLeft->pParent == m.bst.root->pLeft);
               assertUnit(m.bst.root->pLeft->pLeft->pLeft == nullptr);
               assertUnit(m.bst.root->pLeft->pLeft->pRight == nullptr);
            }
         }
         assertUnit(m.bst.root->pRight != nullptr);
         if (m.bst.root->pRight)
         {
            assertUnit(m.bst.root->pRight->data.first == std::string("70"));
            assertUnit(m.bst.root->pRight->data.second == int(70));
            assertUnit(m.bst.root->pRight->pParent == m.bst.root);
            assertUnit(m.bst.root->pRight->pLeft == nullptr);
            assertUnit(m.bst.root->pRight->pRight == nullptr);
         }
      }
      // teardown
      teardownStandardFixture(m);
   }

   // insert something into the middle of the standard fixture
   void test_insertCopy_standardMiddle()
   {  // setup
      custom::pair<std::string, int> pair60(std::string("60"), int(60));
      //    "30"     "50"     "70"   = m
      //   +----+   +----+   +----+
      //   | 30 | - | 50 | - | 70 |
      //   +----+   +----+   +----+
      custom::map<std::string, int> m;
      setupStandardFixture(m);
      custom::pair<custom::map<std::string, int>::iterator, bool> pReturn;
      
      // exercise
      pReturn = m.insert(pair60);
      // verify
      //    "30"     "50"     "60"     "70"   = m
      //   +----+   +----+   +----+   +----+
      //   | 30 | - | 50 | - | 60 | - | 70 |
      //   +----+   +----+   +----+   +----+
      //   pReturn
      //
      assertUnit(pReturn.first.it.pNode != nullptr);
      assertUnit(pReturn.second == true);
      if (m.bst.root && m.bst.root->pRight)
         assertUnit(pReturn.first.it.pNode == m.bst.root->pRight->pLeft);
      assertUnit(m.bst.numElements == 4);
      assertUnit(m.bst.root != nullptr);
      //                  (50)
      //              +-----+-----+
      //            (30)        (70)
      //                       +--+
      //                     (60)
      if (m.bst.root)
      {
         assertUnit(m.bst.root->data.first == std::string("50"));
         assertUnit(m.bst.root->data.second == int(50));
         assertUnit(m.bst.root->pParent == nullptr);
         assertUnit(m.bst.root->pLeft != nullptr);
         if (m.bst.root->pLeft)
         {
            assertUnit(m.bst.root->pLeft->data.first == std::string("30"));
            assertUnit(m.bst.root->pLeft->data.second == int(30));
            assertUnit(m.bst.root->pLeft->pParent == m.bst.root);
            assertUnit(m.bst.root->pLeft->pLeft == nullptr);
            assertUnit(m.bst.root->pLeft->pRight == nullptr);
         }
         assertUnit(m.bst.root->pRight != nullptr);
         if (m.bst.root->pRight)
         {
            assertUnit(m.bst.root->pRight->data.first == std::string("70"));
            assertUnit(m.bst.root->pRight->data.second == int(70));
            assertUnit(m.bst.root->pRight->pParent == m.bst.root);
            assertUnit(m.bst.root->pRight->pLeft != nullptr);
            if (m.bst.root->pRight->pLeft)
            {
               assertUnit(m.bst.root->pRight->pLeft->data.first == std::string("60"));
               assertUnit(m.bst.root->pRight->pLeft->data.second == int(60));
               assertUnit(m.bst.root->pRight->pLeft->pParent == m.bst.root->pRight);
               assertUnit(m.bst.root->pRight->pLeft->pLeft == nullptr);
               assertUnit(m.bst.root->pRight->pLeft->pRight == nullptr);
            }
            assertUnit(m.bst.root->pRight->pRight == nullptr);
         }
      }
      // teardown
      teardownStandardFixture(m);
   }

   /***************************************
    * INSERT
    *    map::insert(T &&)
    ***************************************/

    // insert into an empty fixture
   void test_insertMove_empty()
   {  // setup
      custom::map<std::string, int> m;
      custom::pair<std::string, int> pair50(std::string("50"), int(50));
      
      // exercise
      m.insert(std::move(pair50));
      // verify
      //    "50"
      //   +----+
      //   | 50 |
      //   +----+
      assertUnit(m.bst.numElements == 1);
      assertUnit(m.bst.root != nullptr);
      if (m.bst.root)
      {
         assertUnit(m.bst.root->data.first == std::string("50"));
         assertUnit(m.bst.root->data.second == int(50));
         assertUnit(m.bst.root->pLeft == nullptr);
         assertUnit(m.bst.root->pRight == nullptr);
         assertUnit(m.bst.root->pParent == nullptr);
      }
      // teardown
      teardownStandardFixture(m);
   }


   // insert something into the middle of the standard fixture
   void test_insertMove_standard()
   {  // setup
      custom::pair<std::string, int> pair60(std::string("60"), int(60));
      //    "30"     "50"     "70"   = m
      //   +----+   +----+   +----+
      //   | 30 | - | 50 | - | 70 |
      //   +----+   +----+   +----+
      custom::map<std::string, int> m;
      setupStandardFixture(m);
      custom::pair<custom::map<std::string, int>::iterator, bool> pReturn;
      
      // exercise
      pReturn = m.insert(std::move(pair60));
      // verify
      //    "30"     "50"     "60"     "70"   = m
      //   +----+   +----+   +----+   +----+
      //   | 30 | - | 50 | - | 60 | - | 70 |
      //   +----+   +----+   +----+   +----+
      //   pReturn
      //
      assertUnit(pReturn.first.it.pNode != nullptr);
      assertUnit(pReturn.second == true);
      if (m.bst.root && m.bst.root->pRight)
         assertUnit(pReturn.first.it.pNode == m.bst.root->pRight->pLeft);
      assertUnit(m.bst.numElements == 4);
      assertUnit(m.bst.root != nullptr);
      //                  (50)
      //              +-----+-----+
      //            (30)        (70)
      //                       +--+
      //                     (60)
      if (m.bst.root)
      {
         assertUnit(m.bst.root->data.first == std::string("50"));
         assertUnit(m.bst.root->data.second == int(50));
         assertUnit(m.bst.root->pParent == nullptr);
         assertUnit(m.bst.root->pLeft != nullptr);
         if (m.bst.root->pLeft)
         {
            assertUnit(m.bst.root->pLeft->data.first == std::string("30"));
            assertUnit(m.bst.root->pLeft->data.second == int(30));
            assertUnit(m.bst.root->pLeft->pParent == m.bst.root);
            assertUnit(m.bst.root->pLeft->pLeft == nullptr);
            assertUnit(m.bst.root->pLeft->pRight == nullptr);
         }
         assertUnit(m.bst.root->pRight != nullptr);
         if (m.bst.root->pRight)
         {
            assertUnit(m.bst.root->pRight->data.first == std::string("70"));
            assertUnit(m.bst.root->pRight->data.second == int(70));
            assertUnit(m.bst.root->pRight->pParent == m.bst.root);
            assertUnit(m.bst.root->pRight->pLeft != nullptr);
            if (m.bst.root->pRight->pLeft)
            {
               assertUnit(m.bst.root->pRight->pLeft->data.first == std::string("60"));
               assertUnit(m.bst.root->pRight->pLeft->data.second == int(60));
               assertUnit(m.bst.root->pRight->pLeft->pParent == m.bst.root->pRight);
               assertUnit(m.bst.root->pRight->pLeft->pLeft == nullptr);
               assertUnit(m.bst.root->pRight->pLeft->pRight == nullptr);
            }
            assertUnit(m.bst.root->pRight->pRight == nullptr);
         }
      }
      // teardown
      teardownStandardFixture(m);
   }


   /***************************************
    * SQUARE BRACKET
    *     map::operator[](const T &)
    ***************************************/

   // read something from the root of the standard fixture
   void test_access_standardRootRead()
   {  // setup
      //    "30"     "50"     "70"   = m
      //   +----+   +----+   +----+
      //   | 30 | - | 50 | - | 70 |
      //   +----+   +----+   +----+
      custom::map<std::string, int> m;
      setupStandardFixture(m);
      int s(99);
      
      // exercise
      s = m[std::string("50")];
      // verify
      assertUnit(s == int(50));
      //    "30"     "50"     "70"   = m
      //   +----+   +----+   +----+
      //   | 30 | - | 50 | - | 70 |
      //   +----+   +----+   +----+
      assertStandardFixture(m);
      // teardown
      teardownStandardFixture(m);
   }

   // read something from the left corner of the standard fixture
   void test_access_standardLeftRead()
   {  // setup
      //    "30"     "50"     "70"   = m
      //   +----+   +----+   +----+
      //   | 30 | - | 50 | - | 70 |
      //   +----+   +----+   +----+
      custom::map<std::string, int> m;
      setupStandardFixture(m);
      int s(99);
      
      // exercise
      s = m[std::string("30")];
      // verify
      assertUnit(s == int(30));
      //    "30"     "50"     "70"   = m
      //   +----+   +----+   +----+
      //   | 30 | - | 50 | - | 70 |
      //   +----+   +----+   +----+
      assertStandardFixture(m);
      // teardown
      teardownStandardFixture(m);
   }

   // read something from the right corner of the standard fixture
   void test_access_standardRightRead()
   {  // setup
      //    "30"     "50"     "70"   = m
      //   +----+   +----+   +----+
      //   | 30 | - | 50 | - | 70 |
      //   +----+   +----+   +----+
      custom::map<std::string, int> m;
      setupStandardFixture(m);
      int s(99);
      
      // exercise
      s = m[std::string("70")];
      // verify
      assertUnit(s == int(70));
      //    "30"     "50"     "70"   = m
      //   +----+   +----+   +----+
      //   | 30 | - | 50 | - | 70 |
      //   +----+   +----+   +----+
      assertStandardFixture(m);
      // teardown
      teardownStandardFixture(m);
   }

   // write something from the root of the standard fixture
   void test_access_standardRootWrite()
   {  // setup
      //    "30"     "50"     "70"   = m
      //   +----+   +----+   +----+
      //   | 30 | - | 50 | - | 70 |
      //   +----+   +----+   +----+
      custom::map<std::string, int> m;
      setupStandardFixture(m);
      int s(55);
      
      // exercise
      m[std::string("50")] = s;
      // verify
      assertUnit(m.bst.root != nullptr);
      //    "30"     "50"     "70"   = m
      //   +----+   +----+   +----+
      //   | 30 | - | 55 | - | 70 |
      //   +----+   +----+   +----+
      if (m.bst.root)
      {
         assertUnit(m.bst.root->data.first == std::string("50"));
         assertUnit(m.bst.root->data.second == int(55));
         m.bst.root->data.second = int(50);
      }
      assertStandardFixture(m);
      // teardown
      teardownStandardFixture(m);
   }

   // write something from the left corner of the standard fixture
   void test_access_standardLeftWrite()
   {  // setup
      //    "30"     "50"     "70"   = m
      //   +----+   +----+   +----+
      //   | 30 | - | 50 | - | 70 |
      //   +----+   +----+   +----+
      custom::map<std::string, int> m;
      setupStandardFixture(m);
      int s(33);
      
      // exercise
      m[std::string("30")] = s;
      // verify
      assertUnit(m.bst.root != nullptr);
      assertUnit(m.bst.root->pLeft != nullptr);
      //    "30"     "50"     "70"   = m
      //   +----+   +----+   +----+
      //   | 33 | - | 50 | - | 70 |
      //   +----+   +----+   +----+
      if (m.bst.root && m.bst.root->pLeft)
      {
         assertUnit(m.bst.root->pLeft->data.first == std::string("30"));
         assertUnit(m.bst.root->pLeft->data.second == int(33));
         m.bst.root->pLeft->data.second = int(30);
      }
      assertStandardFixture(m);
      // teardown
      teardownStandardFixture(m);
   }

   // write something from the right corner of the standard fixture
   void test_access_standardRightWrite()
   {  // setup
      //    "30"     "50"     "70"   = m
      //   +----+   +----+   +----+
      //   | 30 | - | 50 | - | 70 |
      //   +----+   +----+   +----+
      custom::map<std::string, int> m;
      setupStandardFixture(m);
      int s(77);
      
      // exercise
      m[std::string("70")] = s;
      // verify
      assertUnit(m.bst.root != nullptr);
      assertUnit(m.bst.root->pRight != nullptr);
      //    "30"     "50"     "70"   = m
      //   +----+   +----+   +----+
      //   | 30 | - | 50 | - | 77 |
      //   +----+   +----+   +----+
      if (m.bst.root && m.bst.root->pRight)
      {
         assertUnit(m.bst.root->pRight->data.first == std::string("70"));
         assertUnit(m.bst.root->pRight->data.second == int(77));
         m.bst.root->pRight->data.second = int(70);
      }
      assertStandardFixture(m);
      // teardown
      teardownStandardFixture(m);
   }

   // insert something into an empty map using the [] operator
   void test_access_emptyWrite()
   {  // setup
      custom::map<std::string, int> m;
      int s(50);
      
      // exercise
      m[std::string("50")] = s;
      // verify
      //    "50"
      //   +----+
      //   | 50 |
      //   +----+
      assertUnit(m.bst.numElements == 1);
      assertUnit(m.bst.root != nullptr);
      if (m.bst.root)
      {
         assertUnit(m.bst.root->data.first == std::string("50"));
         assertUnit(m.bst.root->data.second == int(50));
         assertUnit(m.bst.root->pLeft == nullptr);
         assertUnit(m.bst.root->pRight == nullptr);
         assertUnit(m.bst.root->pParent == nullptr);
      }
      // teardown 
      teardownStandardFixture(m);
   }

   // insert something to the front of the standard fixture using the square bracket operator
   void test_access_standardFrontInsert()
   {  // setup
      int s(10);
      //    "30"     "50"     "70"   = m
      //   +----+   +----+   +----+
      //   | 30 | - | 50 | - | 70 |
      //   +----+   +----+   +----+
      custom::map<std::string, int> m;
      setupStandardFixture(m);
      
      // exercise
      m[std::string("10")] = s;
      // verify
      //    "10"     "30"     "50"     "70"   = m
      //   +----+   +----+   +----+   +----+
      //   | 10 | - | 30 | - | 50 | - | 70 |
      //   +----+   +----+   +----+   +----+
      assertUnit(m.bst.numElements == 4);
      assertUnit(m.bst.root != nullptr);
      //                  (50)
      //              +-----+-----+
      //            (30)        (70)
      //          +---+
      //        (10)
      if (m.bst.root)
      {
         assertUnit(m.bst.root->data.first == std::string("50"));
         assertUnit(m.bst.root->data.second == int(50));
         assertUnit(m.bst.root->pParent == nullptr);
         assertUnit(m.bst.root->pLeft != nullptr);
         if (m.bst.root->pLeft)
         {
            assertUnit(m.bst.root->pLeft->data.first == std::string("30"));
            assertUnit(m.bst.root->pLeft->data.second == int(30));
            assertUnit(m.bst.root->pLeft->pParent == m.bst.root);
            assertUnit(m.bst.root->pLeft->pLeft != nullptr);
            assertUnit(m.bst.root->pLeft->pRight == nullptr);
            if (m.bst.root->pLeft->pLeft)
            {
               assertUnit(m.bst.root->pLeft->pLeft->data.first == std::string("10"));
               assertUnit(m.bst.root->pLeft->pLeft->data.second == int(10));
               assertUnit(m.bst.root->pLeft->pLeft->pParent == m.bst.root->pLeft);
               assertUnit(m.bst.root->pLeft->pLeft->pLeft == nullptr);
               assertUnit(m.bst.root->pLeft->pLeft->pRight == nullptr);
            }
         }
         assertUnit(m.bst.root->pRight != nullptr);
         if (m.bst.root->pRight)
         {
            assertUnit(m.bst.root->pRight->data.first == std::string("70"));
            assertUnit(m.bst.root->pRight->data.second == int(70));
            assertUnit(m.bst.root->pRight->pParent == m.bst.root);
            assertUnit(m.bst.root->pRight->pLeft == nullptr);
            assertUnit(m.bst.root->pRight->pRight == nullptr);
         }
      }
      // teardown
      teardownStandardFixture(m);
   }


   // insert something to the moiddle of the standard fixture using the square bracket operator
   void test_access_standardMiddleInsert()
   {  // setup
      int s(60);
      //    "30"     "50"     "70"   = m
      //   +----+   +----+   +----+
      //   | 30 | - | 50 | - | 70 |
      //   +----+   +----+   +----+
      custom::map<std::string, int> m;
      setupStandardFixture(m);
      
      // exercise
      m[std::string("60")] = s;
      // verify
      //    "30"     "50"     "60"     "70"   = m
      //   +----+   +----+   +----+   +----+
      //   | 30 | - | 50 | - | 60 | - | 70 |
      //   +----+   +----+   +----+   +----+
      assertUnit(m.bst.numElements == 4);
      assertUnit(m.bst.root != nullptr);
      //                  (50)
      //              +-----+-----+
      //            (30)        (70)
      //                       +--+
      //                      (60)
      if (m.bst.root)
      {
         assertUnit(m.bst.root->data.first == std::string("50"));
         assertUnit(m.bst.root->data.second == int(50));
         assertUnit(m.bst.root->pParent == nullptr);
         assertUnit(m.bst.root->pLeft != nullptr);
         if (m.bst.root->pLeft)
         {
            assertUnit(m.bst.root->pLeft->data.first == std::string("30"));
            assertUnit(m.bst.root->pLeft->data.second == int(30));
            assertUnit(m.bst.root->pLeft->pParent == m.bst.root);
            assertUnit(m.bst.root->pLeft->pLeft == nullptr);
            assertUnit(m.bst.root->pLeft->pRight == nullptr);
         }
         assertUnit(m.bst.root->pRight != nullptr);
         if (m.bst.root->pRight)
         {
            assertUnit(m.bst.root->pRight->data.first == std::string("70"));
            assertUnit(m.bst.root->pRight->data.second == int(70));
            assertUnit(m.bst.root->pRight->pParent == m.bst.root);
            assertUnit(m.bst.root->pRight->pLeft != nullptr);
            if (m.bst.root->pRight->pLeft)
            {
               assertUnit(m.bst.root->pRight->pLeft->data.first == std::string("60"));
               assertUnit(m.bst.root->pRight->pLeft->data.second == int(60));
               assertUnit(m.bst.root->pRight->pLeft->pParent == m.bst.root->pRight);
               assertUnit(m.bst.root->pRight->pLeft->pLeft == nullptr);
               assertUnit(m.bst.root->pRight->pLeft->pRight == nullptr);
            }
            assertUnit(m.bst.root->pRight->pRight == nullptr);
         }
      }
      // teardown
      teardownStandardFixture(m);
   }


   /***************************************
    * AT
    *     map::at(const T &)
    ***************************************/

    // read something from the root of the standard fixture
   void test_at_standardRootRead()
   {  // setup
      //    "30"     "50"     "70"   = m
      //   +----+   +----+   +----+
      //   | 30 | - | 50 | - | 70 |
      //   +----+   +----+   +----+
      custom::map<std::string, int> m;
      setupStandardFixture(m);
      int s(99);
      
      // exercise
      s = m.at(std::string("50"));
      // verify
      assertUnit(s == int(50));
      //    "30"     "50"     "70"   = m
      //   +----+   +----+   +----+
      //   | 30 | - | 50 | - | 70 |
      //   +----+   +----+   +----+
      assertStandardFixture(m);
      // teardown
      teardownStandardFixture(m);
   }

   // read something from the left corner of the standard fixture
   void test_at_standardLeftRead()
   {  // setup
      //    "30"     "50"     "70"   = m
      //   +----+   +----+   +----+
      //   | 30 | - | 50 | - | 70 |
      //   +----+   +----+   +----+
      custom::map<std::string, int> m;
      setupStandardFixture(m);
      int s(99);
      
      // exercise
      s = m.at(std::string("30"));
      // verify
      assertUnit(s == int(30));
      //    "30"     "50"     "70"   = m
      //   +----+   +----+   +----+
      //   | 30 | - | 50 | - | 70 |
      //   +----+   +----+   +----+
      assertStandardFixture(m);
      // teardown
      teardownStandardFixture(m);
   }

   // read something from the right corner of the standard fixture
   void test_at_standardRightRead()
   {  // setup
      //    "30"     "50"     "70"   = m
      //   +----+   +----+   +----+
      //   | 30 | - | 50 | - | 70 |
      //   +----+   +----+   +----+
      custom::map<std::string, int> m;
      setupStandardFixture(m);
      int s(99);
      
      // exercise
      s = m.at(std::string("70"));
      // verify
      assertUnit(s == int(70));
      //    "30"     "50"     "70"   = m
      //   +----+   +----+   +----+
      //   | 30 | - | 50 | - | 70 |
      //   +----+   +----+   +----+
      assertStandardFixture(m);
      // teardown
      teardownStandardFixture(m);
   }

   // write something from the root of the standard fixture
   void test_at_standardRootWrite()
   {  // setup
      //    "30"     "50"     "70"   = m
      //   +----+   +----+   +----+
      //   | 30 | - | 50 | - | 70 |
      //   +----+   +----+   +----+
      custom::map<std::string, int> m;
      setupStandardFixture(m);
      int s(55);
      
      // exercise
      m.at(std::string("50")) = s;
      // verify
      assertUnit(m.bst.root != nullptr);
      //    "30"     "50"     "70"   = m
      //   +----+   +----+   +----+
      //   | 30 | - | 55 | - | 70 |
      //   +----+   +----+   +----+
      if (m.bst.root)
      {
         assertUnit(m.bst.root->data.first == std::string("50"));
         assertUnit(m.bst.root->data.second == int(55));
         m.bst.root->data.second = int(50);
      }
      assertStandardFixture(m);
      // teardown
      teardownStandardFixture(m);
   }

   // write something from the left corner of the standard fixture
   void test_at_standardLeftWrite()
   {  // setup
      //    "30"     "50"     "70"   = m
      //   +----+   +----+   +----+
      //   | 30 | - | 50 | - | 70 |
      //   +----+   +----+   +----+
      custom::map<std::string, int> m;
      setupStandardFixture(m);
      int s(33);
      
      // exercise
      m.at(std::string("30")) = s;
      // verify
      assertUnit(m.bst.root != nullptr);
      assertUnit(m.bst.root->pLeft != nullptr);
      //    "30"     "50"     "70"   = m
      //   +----+   +----+   +----+
      //   | 33 | - | 50 | - | 70 |
      //   +----+   +----+   +----+
      if (m.bst.root && m.bst.root->pLeft)
      {
         assertUnit(m.bst.root->pLeft->data.first == std::string("30"));
         assertUnit(m.bst.root->pLeft->data.second == int(33));
         m.bst.root->pLeft->data.second = int(30);
      }
      assertStandardFixture(m);
      // teardown
      teardownStandardFixture(m);
   }

   // write something from the right corner of the standard fixture
   void test_at_standardRightWrite()
   {  // setup
      //    "30"     "50"     "70"   = m
      //   +----+   +----+   +----+
      //   | 30 | - | 50 | - | 70 |
      //   +----+   +----+   +----+
      custom::map<std::string, int> m;
      setupStandardFixture(m);
      int s(77);
      
      // exercise
      m.at(std::string("70")) = s;
      // verify
      assertUnit(m.bst.root != nullptr);
      assertUnit(m.bst.root->pRight != nullptr);
      //    "30"     "50"     "70"   = m
      //   +----+   +----+   +----+
      //   | 30 | - | 50 | - | 77 |
      //   +----+   +----+   +----+
      if (m.bst.root && m.bst.root->pRight)
      {
         assertUnit(m.bst.root->pRight->data.first == std::string("70"));
         assertUnit(m.bst.root->pRight->data.second == int(77));
         m.bst.root->pRight->data.second = int(70);
      }
      assertStandardFixture(m);
      // teardown
      teardownStandardFixture(m);
   }

   // insert something into an empty map using the [] operator
   void test_at_emptyWrite()
   {  // setup
      custom::map<std::string, int> m;
      int s(50);
      
      // exercise
      try
      {
         m.at(std::string("50")) = s;
         // verify
         assertUnit(false);
      }
      catch (const std::out_of_range & e)
      {
         assertUnit(e.what() == std::string("invalid map<K, T> key"));
      }
      assertEmptyFixture(m);
      // teardown 
      teardownStandardFixture(m);
   }

   // insert something to the front of the standard fixture using the square bracket operator
   void test_at_standardWrite()
   {  // setup
      int s(10);
      //    "30"     "50"     "70"   = m
      //   +----+   +----+   +----+
      //   | 30 | - | 50 | - | 70 |
      //   +----+   +----+   +----+
      custom::map<std::string, int> m;
      setupStandardFixture(m);
      
      // exercise
      try
      {
         m.at(std::string("10")) = s;
         // verify
         assertUnit(false);
      }
      catch (const std::out_of_range& e)
      {
         assertUnit(e.what() == std::string("invalid map<K, T> key"));
      }
      assertStandardFixture(m);
      // teardown
      teardownStandardFixture(m);
   }

   /***************************************
    * ERASE
    *     map::erase()
    ***************************************/

   // attempt to erase from an empty map
   void test_erase_emptyKey()
   {  // setup
      custom::map<std::string, int> m;
      size_t size;
      std::string key("50");
      
      // exercise
      size = m.erase(key);
      // verify
      assertUnit(size == 0);
      assertEmptyFixture(m);
      // teardown
      teardownStandardFixture(m);
   }

   // erase an element from the standard fixture
   void test_erase_standardKey()
   {  // setup
      //    "30"     "50"     "70"   = m
      //   +----+   +----+   +----+
      //   | 30 | - | 50 | - | 70 |
      //   +----+   +----+   +----+
      custom::map<std::string, int> m;
      setupStandardFixture(m);
      size_t size;
      std::string key("50");
      
      // exercise
      size = m.erase(key);
      // verify
      assertUnit(size == 1);
      //    "30"     "70"   = m
      //   +----+   +----+
      //   | 30 | - | 70 |
      //   +----+   +----+
      assertUnit(m.bst.size() == 2);
      assertUnit(m.bst.root != nullptr);
      //                  (70)
      //              +-----+
      //            (30)    
      if (m.bst.root)
      {
         assertUnit(m.bst.root->data.first == std::string("70"));
         assertUnit(m.bst.root->data.second == int(70));
         assertUnit(m.bst.root->pParent == nullptr);
         assertUnit(m.bst.root->pLeft != nullptr);
         if (m.bst.root->pLeft)
         {
            assertUnit(m.bst.root->pLeft->data.first == std::string("30"));
            assertUnit(m.bst.root->pLeft->data.second == int(30));
            assertUnit(m.bst.root->pLeft->pParent == m.bst.root);
            assertUnit(m.bst.root->pLeft->pLeft == nullptr);
            assertUnit(m.bst.root->pLeft->pRight == nullptr);
         }
         assertUnit(m.bst.root->pRight == nullptr);
      }      
      // teardown
      teardownStandardFixture(m);
   }

   // attempt to erase an element that does not exist
   void test_erase_standardKeyMissing()
   {  // setup
      //    "30"     "50"     "70"   = m
      //   +----+   +----+   +----+
      //   | 30 | - | 50 | - | 70 |
      //   +----+   +----+   +----+
      custom::map<std::string, int> m;
      setupStandardFixture(m);
      size_t size;
      std::string key("40");
      
      // exercise
      size = m.erase(key);
      // verify
      assertUnit(size == 0);
      //    "30"     "50"     "70"   = m
      //   +----+   +----+   +----+
      //   | 30 | - | 50 | - | 70 |
      //   +----+   +----+   +----+
      assertStandardFixture(m);
      // teardown
      teardownStandardFixture(m);
   }

   // attempt to erase from an empty map
   void test_erase_emptyIterator()
   {  // setup
      custom::map<std::string, int> m;
      custom::map<std::string, int>::iterator itReturn;
      custom::map<std::string, int>::iterator itErase = m.end();
      
      // exercise
      itReturn = m.erase(itErase);
      // verify
      assertEmptyFixture(m);
      // teardown
      teardownStandardFixture(m);
   }

   // erase one element from a map with an iterator
   void test_erase_standardIterator()
   {  // setup
      //    "30"     "50"     "70"   = m
      //   +----+   +----+   +----+
      //   | 30 | - | 50 | - | 70 |
      //   +----+   +----+   +----+
      custom::map<std::string, int> m;
      setupStandardFixture(m);
      custom::map<std::string, int>::iterator itReturn;
      custom::map<std::string, int>::iterator itErase = m.begin();
      
      // exercise
      itReturn = m.erase(itErase);
      // verify
      assertUnit(itReturn != m.end());
      if (itReturn != m.end())
      {
         assertUnit((*itReturn).first == std::string("50"));
         assertUnit((*itReturn).second == int(50));
      }
      //    "50"     "70"   = m
      //   +----+   +----+ 
      //   | 50 | - | 70 | 
      //   +----+   +----+ 
      assertUnit(m.bst.size() == 2);
      assertUnit(m.bst.root != nullptr);
      //                  (50)
      //                    +-----+
      //                        (70)    
      if (m.bst.root)
      {
         assertUnit(m.bst.root->data.first == std::string("50"));
         assertUnit(m.bst.root->data.second == int(50));
         assertUnit(m.bst.root->pParent == nullptr);
         assertUnit(m.bst.root->pLeft == nullptr);
         assertUnit(m.bst.root->pRight != nullptr);
         if (m.bst.root->pRight)
         {
            assertUnit(m.bst.root->pRight->data.first == std::string("70"));
            assertUnit(m.bst.root->pRight->data.second == int(70));
            assertUnit(m.bst.root->pRight->pParent == m.bst.root);
            assertUnit(m.bst.root->pRight->pLeft == nullptr);
            assertUnit(m.bst.root->pRight->pRight == nullptr);
         }
      }
      // teardown
      teardownStandardFixture(m);
   }

   // attempt to erase one element from a map that is not there
   void test_erase_standardIteratorMissing()
   {  // setup
      //    "30"     "50"     "70"   = m
      //   +----+   +----+   +----+
      //   | 30 | - | 50 | - | 70 |
      //   +----+   +----+   +----+
      custom::map<std::string, int> m;
      setupStandardFixture(m);
      custom::map<std::string, int>::iterator itReturn;
      custom::map<std::string, int>::iterator itErase = m.end();
      
      // exercise
      itReturn = m.erase(itErase);
      // verify
      assertUnit(itReturn == m.end());
      //    "30"     "50"     "70"   = m
      //   +----+   +----+   +----+
      //   | 30 | - | 50 | - | 70 |
      //   +----+   +----+   +----+
      assertStandardFixture(m);
      // teardown
      teardownStandardFixture(m);
   }

   // attempt to erase from an empty map
   void test_erase_emptyRange()
   {  // setup
      custom::map<std::string, int> m;
      custom::map<std::string, int>::iterator itFirst = m.begin();
      custom::map<std::string, int>::iterator itLast = m.end();
      custom::map<std::string, int>::iterator itReturn;
      
      // exercise
      itReturn = m.erase(itFirst, itLast);
      // verify
      assertEmptyFixture(m);
      // teardown
      teardownStandardFixture(m);
   }   
   
   void test_erase_standardRange()
   {  // setup
      //    "30"     "50"     "70"   = m
      //   +----+   +----+   +----+
      //   | 30 | - | 50 | - | 70 |
      //   +----+   +----+   +----+
      //     itFirst           itLast
      custom::map<std::string, int> m;
      setupStandardFixture(m);
      custom::map<std::string, int>::iterator itFirst = m.begin();
      custom::map<std::string, int>::iterator itLast = m.begin();
      ++itLast;
      ++itLast;
      custom::map<std::string, int>::iterator itReturn;
      
      // exercise
      itReturn = m.erase(itFirst, itLast);
      // verify
      assertUnit(itReturn == m.begin());
      //    "70"     = m
      //   +----+ 
      //   | 70 |
      //   +----+
      //   itReturn
      assertUnit(m.bst.numElements == 1);
      assertUnit(m.bst.root != nullptr);
      if (m.bst.root)
      {
         assertUnit(m.bst.root->data.first == std::string("70"));
         assertUnit(m.bst.root->data.second == int(70));
         assertUnit(m.bst.root->pLeft == nullptr);
         assertUnit(m.bst.root->pRight == nullptr);
         assertUnit(m.bst.root->pParent == nullptr);
      }
      // teardown
      teardownStandardFixture(m);
   }
   /****************************************************************
    * Setup Standard Fixture
    *    "30"     "50"     "70"
    *   +----+   +----+   +----+
    *   | 30 | - | 50 | - | 70 |
    *   +----+   +----+   +----+
    *   bst pointers
    *                  (50)
    *              +-----+-----+
    *            (30)        (70)
    ****************************************************************/
   void setupStandardFixture(custom::map<std::string, int>& m)
   {
      // set up the pairs
      custom::pair<std::string, int> pair30(std::string("30"), int(30));
      custom::pair<std::string, int> pair50(std::string("50"), int(50));
      custom::pair<std::string, int> pair70(std::string("70"), int(70));

      // create the nodes
      //               (50)b
      //           +-----+-----+
      //         (30)r        (70)r
      custom::BST < custom::pair<std::string, int> > ::BNode* bnode30;
      custom::BST < custom::pair<std::string, int> > ::BNode* bnode50;
      custom::BST < custom::pair<std::string, int> > ::BNode* bnode70;
      bnode30 = new custom::BST < custom::pair<std::string, int> > ::BNode(pair30);
      bnode50 = new custom::BST < custom::pair<std::string, int> > ::BNode(pair50);
      bnode70 = new custom::BST < custom::pair<std::string, int> > ::BNode(pair70);

      // hook up the links and stuff
      bnode50->pLeft  = bnode30;
      bnode50->pRight = bnode70;
      bnode30->pParent = bnode70->pParent = bnode50;

      // place the nodes in the bst
      m.bst.root = bnode50;
      m.bst.numElements = 3;
   }

   /****************************************************************
    * Verify Empty Fixture
    ****************************************************************/
   void assertEmptyFixtureParameters(const custom::map<std::string, int>& m, int line, const char* function)
   {
      // bst stuff
      assertIndirect(m.bst.size() == 0);
      assertIndirect(m.bst.empty() == true);
      assertIndirect(m.bst.numElements == 0);
   }

   /****************************************************************
    * Verify Standard Fixture
    *    "30"     "50"     "70"
    *   +----+   +----+   +----+
    *   | 30 | - | 50 | - | 70 |
    *   +----+   +----+   +----+
    *   bst pointers
    *                  (50)
    *              +-----+-----+
    *            (30)        (70)
    ****************************************************************/
   void assertStandardFixtureParameters(const custom::map<std::string, int> & m, int line, const char* function)
   {
      assertIndirect(m.bst.numElements == 3);

      // check that we have a tree
      assertIndirect(m.bst.root != nullptr);
      if (m.bst.root == nullptr)
         return;

      // check the root
      assertIndirect(m.bst.root->data.first == std::string("50"));
      assertIndirect(m.bst.root->data.second == int(50));
      assertIndirect(m.bst.root->pLeft != nullptr);
      assertIndirect(m.bst.root->pRight != nullptr);
      assertIndirect(m.bst.root->pParent == nullptr);

      // check left branch
      if (m.bst.root->pLeft)
      {
         assertIndirect(m.bst.root->pLeft->data.first == std::string("30"));
         assertIndirect(m.bst.root->pLeft->data.second == int(30));
         assertIndirect(m.bst.root->pLeft->pLeft == nullptr);
         assertIndirect(m.bst.root->pLeft->pRight == nullptr);
         assertIndirect(m.bst.root->pLeft->pParent == m.bst.root);
      }

      // check right branch
      if (m.bst.root->pRight)
      {
         assertIndirect(m.bst.root->pRight->data.first == std::string("70"));
         assertIndirect(m.bst.root->pRight->data.second == int(70));
         assertIndirect(m.bst.root->pRight->pLeft == nullptr);
         assertIndirect(m.bst.root->pRight->pRight == nullptr);
         assertIndirect(m.bst.root->pRight->pParent == m.bst.root);
      }
   }


   /****************************************************************
    * Teardown Standard Fixture
    *    "30"     "50"     "70" 
    *   +----+   +----+   +----+
    *   | 30 | - | 50 | - | 70 |
    *   +----+   +----+   +----+
    *   bst pointers
    *                  (50)
    *              +-----+-----+
    *            (30)        (70)
    ****************************************************************/
   void teardownStandardFixture(custom::map<std::string, double>& m)
   {
      // delete the nodes
      if (m.bst.root)
      {
         if (m.bst.root->pLeft)
         {
            if (m.bst.root->pLeft->pLeft)
               delete m.bst.root->pLeft->pLeft;
            if (m.bst.root->pLeft->pRight)
               delete m.bst.root->pLeft->pRight;

            delete m.bst.root->pLeft;
         }

         if (m.bst.root->pRight)
         {
            if (m.bst.root->pRight->pLeft)
               delete m.bst.root->pRight->pLeft;
            if (m.bst.root->pRight->pRight)
               delete m.bst.root->pRight->pRight;

            delete m.bst.root->pRight;
         }
         delete m.bst.root;
      }
      m.bst.root = nullptr;
      m.bst.numElements = 0;
   }

   void teardownStandardFixture(custom::map<std::string, int>& m)
   {
      // delete the nodes
      if (m.bst.root)
      {
         if (m.bst.root->pLeft && m.bst.root->pLeft != m.bst.root)
         {
            if (m.bst.root->pLeft->pLeft && m.bst.root->pLeft->pLeft != m.bst.root->pLeft)
               delete m.bst.root->pLeft->pLeft;
            if (m.bst.root->pLeft->pRight && m.bst.root->pLeft->pRight != m.bst.root->pLeft)
               delete m.bst.root->pLeft->pRight;

            delete m.bst.root->pLeft;
         }

         if (m.bst.root->pRight && m.bst.root->pRight != m.bst.root)
         {
            if (m.bst.root->pRight->pLeft && m.bst.root->pRight->pLeft != m.bst.root->pRight)
               delete m.bst.root->pRight->pLeft;
            if (m.bst.root->pRight->pRight && m.bst.root->pRight->pRight != m.bst.root->pRight)
               delete m.bst.root->pRight->pRight;

            delete m.bst.root->pRight;
         }
         delete m.bst.root;
      }
      m.bst.root = nullptr;
      m.bst.numElements = 0;
   }
};

#endif // DEBUG
