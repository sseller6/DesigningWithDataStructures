/***********************************************************************
 * Header:
 *    TEST PRIORITY QUEUE
 * Summary:
 *    Unit tests for the priority queue
 * Author:
 *    James Helfrich, PhD. (c) 2022 by Kendall Hunt
 ************************************************************************/

#pragma once

#ifdef DEBUG

#include "priority_queue.h"
#include "unitTest.h"
#include "spy.h"

#include <cassert>
#include <memory>


class TestPQueue : public UnitTest
{

public:
   void run()
   {
      reset();

      // Construct
      test_construct_default();
      test_constructCopy_empty();
      test_constructCopy_standard();
      test_constructMove_empty();
      test_constructMove_standard();
      test_constructRange_empty();
      test_constructRange_one();
      test_constructRange_staandard();
      test_constructMoveInit_empty();
      test_constructMoveInit_one();
      test_constructMoveInit_standard();
      test_constructMoveInit_twoLevels();

      // Assign
      test_swap_emptyEmpty();
      test_swap_standardEmpty();
      test_swap_emptyStandard();
      test_swap_standardStandard();

      // Access
      test_top_empty();
      test_top_standard();

      // Insert
      test_push_empty();
      test_push_levelZero();
      test_push_levelOne();
      test_push_levelTwo();
      test_push_levelThree();
      test_pushMove_empty();
      test_pushMove_levelZero();
      test_pushMove_levelOne();
      test_pushMove_levelTwo();
      test_pushMove_levelThree();

      // Remove
      test_pop_empty();
      test_pop_one();
      test_pop_two();
      test_pop_standard();

      // Status
      test_size_empty();
      test_size_standard();
      test_empty_empty();
      test_empty_standard();
      
      // Utility
      test_percolateDown_nothing();
      test_percolateDown_oneLevel();
      test_percolateDown_twoLevels();
      test_heapify_nothing();
      test_heapify_oneLevel();
      test_heapify_twoLevels();

      report("PQueue");
   }

   /***************************************
    * CONSTRUCTOR
    ***************************************/

   // default constructor, no allocations
   void test_construct_default()
   {  // setup
      // exercise
      custom::priority_queue <int> pq;
      // verify
      assertUnit(pq.container.empty());
   }  // teardown


   
   /***************************************
    * COPY CONSTRUCTOR
    ***************************************/
   
   // copy constructor of an empty vector
   void test_constructCopy_empty()
   {  // setup
      custom::priority_queue<int> pqSrc;
      // exercise
      custom::priority_queue<int> pqDest(pqSrc);
      // verify
      assertEmptyFixture(pqSrc);
      assertEmptyFixture(pqDest);
   }  // teardown
   
   // copy constructor of a 4-element collection
   void test_constructCopy_standard()
   {  // setup
      //  +---+---+---+---+---+---+---+---+---+
      //  | 10| 8 | 9 | 4 | 3 | 7 | 5 |   |   |
      //  +---+---+---+---+---+---+---+---+---+
      //                10
      //          8            9
      //       4     3      7     5
      custom::priority_queue<int> pqSrc;
      setupStandardFixture(pqSrc);
      // exercise
      custom::priority_queue<int> pqDest(pqSrc);
      // verify
      assertUnit(pqSrc.container.data != pqDest.container.data);
      //  +---+---+---+---+---+---+---+---+---+
      //  | 10| 8 | 9 | 4 | 3 | 7 | 5 |   |   |
      //  +---+---+---+---+---+---+---+---+---+
      //                10
      //          8            9
      //       4     3      7     5
      assertStandardFixture(pqSrc);
      //  +---+---+---+---+---+---+---+---+---+
      //  | 10| 8 | 9 | 4 | 3 | 7 | 5 |   |   |
      //  +---+---+---+---+---+---+---+---+---+
      //                10
      //          8            9
      //       4     3      7     5
      assertStandardFixture(pqDest);
      // teardown
      teardownStandardFixture(pqSrc);
      teardownStandardFixture(pqDest);
   }
   
   /***************************************
    * MOVE CONSTRUCTOR
    ***************************************/
   
   // move constructor of an empty container
   void test_constructMove_empty()
   {  // setup
      custom::priority_queue<int> pqSrc;
      // exercise
      custom::priority_queue<int> pqDest(std::move(pqSrc));
      // verify
      assertEmptyFixture(pqSrc);
      assertEmptyFixture(pqDest);
   }  // teardown
   
   // move constructor of a standard fixture
   void test_constructMove_standard()
   {  // setup
      //  +---+---+---+---+---+---+---+---+---+
      //  | 10| 8 | 9 | 4 | 3 | 7 | 5 |   |   |
      //  +---+---+---+---+---+---+---+---+---+
      //                10
      //          8            9
      //       4     3      7     5
      custom::priority_queue<int> pqSrc;
      setupStandardFixture(pqSrc);
      // exercise
      custom::priority_queue<int> pqDest(std::move(pqSrc));
      // verify
      assertEmptyFixture(pqSrc);
      //  +---+---+---+---+---+---+---+---+---+
      //  | 10| 8 | 9 | 4 | 3 | 7 | 5 |   |   |
      //  +---+---+---+---+---+---+---+---+---+
      //                10
      //          8            9
      //       4     3      7     5
      assertStandardFixture(pqDest);
      // teardown
      teardownStandardFixture(pqDest);
   }
   
   /***************************************
    * RANGE CONSTRUCTOR
    ***************************************/
   
   // priority_queue({})
   void test_constructRange_empty()
   {  // setup
      std::initializer_list<int> il;
      // exercise
      custom::priority_queue<int> pq(il.begin(), il.end());
      // verify
      assertEmptyFixture(pq);
      // teardown
      teardownStandardFixture(pq);
   }
   
   // priority_queue({50})
   void test_constructRange_one()
   {  // setup
      //   il = {50}
      std::initializer_list<int> il{int(50)};
      // exercise
      custom::priority_queue<int> pq(il.begin(), il.end());
      // verify
      assertUnit(pq.container.size() == 1);
      assertUnit(pq.container.capacity() == 1);
      if (pq.container.size() == 1)
         assertUnit(pq.container[0] == int(50));
      // teardown
      teardownStandardFixture(pq);
   }

   // priority_queue({10, 9, 8})
   void test_constructRange_staandard()
   {  // setup
      //  il = {10, 9, 8}
      std::initializer_list<int> il{int(10), int(9), int(8)};
      // exercise
      custom::priority_queue<int> pq(il.begin(), il.end());
      // verify
      //  +---+---+---+
      //  | 10| 9 | 8 |
      //  +---+---+---+
      //                10
      //          9            8
      assertUnit(pq.container.size() == 3);
      assertUnit(pq.container.capacity() == 3);
      if (pq.container.size() == 3)
      {
         assertUnit(pq.container[0] == int(10));
         assertUnit(pq.container[1] == int(9));
         assertUnit(pq.container[2] == int(8));
      }
      // teardown
      teardownStandardFixture(pq);
   }
   
   /***************************************
    * MOVE CONTAINER INITIALIZE CONSTRUCTOR
    ***************************************/
   
   // priority_queue({})
   void test_constructMoveInit_empty()
   {  // setup
      custom::vector <int> v;
      // exercise
      custom::priority_queue <int> pq(std::move(v));
      // verify
      assertEmptyFixture(pq);
      assertUnit(v.size() == 0);
      // teardown
      teardownStandardFixture(pq);
   }
   
   // priority_queue({50})
   void test_constructMoveInit_one()
   {  // setup
      //   v = [50]
      custom::vector <int> v{int(50)};
      // exercise
      custom::priority_queue <int> pq(std::move(v));
      // verify
      //  +----+
      //  | 50 |
      //  +----+
      assertUnit(pq.container.size() == 1);
      if (pq.container.size() == 1)
         assertUnit(pq.container[0] == int(50));
      assertUnit(v.size() == 0);
      // teardown
      teardownStandardFixture(pq);
   }
   
   // priority_queue({9, 10, 8})
   void test_constructMoveInit_standard()
   {  // setup
      //   v = [9,10,8]
      custom::vector <int> v{int(9), int(10), int(8)};
      // exercise
      custom::priority_queue <int> pq(std::move(v));
      // verify
      //  +---+---+---+
      //  | 10| 9 | 8 |
      //  +---+---+---+
      //                10
      //          9            8
      assertUnit(pq.container.size() == 3);
      assertUnit(pq.container.capacity() == 3);
      if (pq.container.size() == 3)
      {
         assertUnit(pq.container[0] == int(10));
         assertUnit(pq.container[1] == int(9));
         assertUnit(pq.container[2] == int(8));
      }
      assertUnit(v.size() == 0);
      // teardown
      teardownStandardFixture(pq);
   }
   
   // priority_queue({1, 2, 3, 4, 5, 6, 7})
   void test_constructMoveInit_twoLevels()
   {  // setup
      //   v = [9,10,8]
      custom::vector <int> v{ 1, 2, 3, 4, 5, 6, 7 };
      // exercise
      custom::priority_queue <int> pq(std::move(v));
      // verify
      //    1   2   3   4   5   6   7
      //  +---+---+---+---+---+---+---+---+---+
      //  | 7 | 5 | 6 | 4 | 2 | 1 | 3 |   |   |
      //  +---+---+---+---+---+---+---+---+---+
      //             7
      //          5      6
      //         4 2    1 3
      assertUnit(pq.container.size() == 7);
      assertUnit(pq.container.capacity() == 7);
      if (pq.container.size() == 7)
      {
         assertUnit(pq.container[0] == int(7));
         assertUnit(pq.container[1] == int(5));
         assertUnit(pq.container[2] == int(6));
         assertUnit(pq.container[3] == int(4));
         assertUnit(pq.container[4] == int(2));
         assertUnit(pq.container[5] == int(1));
         assertUnit(pq.container[6] == int(3));
      }
      assertUnit(v.size() == 0);
      // teardown
      teardownStandardFixture(pq);
   }

   /***************************************
    * SIZE EMPTY
    ***************************************/

   // size of a priority queue that is empty
   void test_size_empty()
   {  // setup
      custom::priority_queue <int> pq;
      // exercise
      size_t size = pq.size();
      // verify
      assertUnit(size == 0);
      assertEmptyFixture(pq);
   }  // teardown

   // size of a priority queue that is standard
   void test_size_standard()
   {  // setup
      //  +---+---+---+---+---+---+---+---+---+
      //  | 10| 8 | 9 | 4 | 3 | 7 | 5 |   |   |
      //  +---+---+---+---+---+---+---+---+---+
      //                10
      //          8            9
      //       4     3      7     5
      custom::priority_queue <int> pq;
      setupStandardFixture(pq);
      // exercise
      size_t size = pq.size();
      // verify
      assertUnit(size == 7);
      assertStandardFixture(pq);
      // teardown
      teardownStandardFixture(pq);
   }

   // whether an empty priority queue is empty
   void test_empty_empty()
   {  // setup
      custom::priority_queue <int> pq;
      // exercise
      bool empty = pq.empty();
      // verify
      assertUnit(empty == true);
      assertEmptyFixture(pq);
   }  // teardown

   // whether a standard priority queue is empty
   void test_empty_standard()
   {  // setup
      //  +---+---+---+---+---+---+---+---+---+
      //  | 10| 8 | 9 | 4 | 3 | 7 | 5 |   |   |
      //  +---+---+---+---+---+---+---+---+---+
      //                10
      //          8            9
      //       4     3      7     5
      custom::priority_queue <int> pq;
      setupStandardFixture(pq);
      // exercise
      bool empty = pq.empty();
      // verify
      assertUnit(empty == false);
      assertStandardFixture(pq);
      // teardown
      teardownStandardFixture(pq);
   }

   /***************************************
    * SWAP
    ***************************************/
   
   // swap(empty, empty)
   void test_swap_emptyEmpty()
   {  // setup
      custom::priority_queue <int> pqLHS;
      custom::priority_queue <int> pqRHS;
      // exercise
      swap(pqLHS, pqRHS);
      // verify
      assertEmptyFixture(pqLHS);
      assertEmptyFixture(pqRHS);
      // teardown
      teardownStandardFixture(pqLHS);
      teardownStandardFixture(pqRHS);
   }
   
   // swap(standard, empty)
   void test_swap_standardEmpty()
   {  // setup
      //  +---+---+---+---+---+---+---+---+---+
      //  | 10| 8 | 9 | 4 | 3 | 7 | 5 |   |   | = pqLHS
      //  +---+---+---+---+---+---+---+---+---+
      //                10
      //          8            9
      //       4     3      7     5
      custom::priority_queue <int> pqLHS;
      setupStandardFixture(pqLHS);
      custom::priority_queue <int> pqRHS;
      // exercise
      swap(pqLHS, pqRHS);
      // verify
      //  +---+---+---+---+---+---+---+---+---+
      //  | 10| 8 | 9 | 4 | 3 | 7 | 5 |   |   | = pqRHS
      //  +---+---+---+---+---+---+---+---+---+
      //                10
      //          8            9
      //       4     3      7     5
      assertStandardFixture(pqRHS);
      assertEmptyFixture(pqLHS);
      // teardown
      teardownStandardFixture(pqLHS);
      teardownStandardFixture(pqRHS);
   }
      
   // swap(empty, standard
   void test_swap_emptyStandard()
   {  // setup
      custom::priority_queue <int> pqLHS;
      //  +---+---+---+---+---+---+---+---+---+
      //  | 10| 8 | 9 | 4 | 3 | 7 | 5 |   |   | = pqRHS
      //  +---+---+---+---+---+---+---+---+---+
      //                10
      //          8            9
      //       4     3      7     5
      custom::priority_queue <int> pqRHS;
      setupStandardFixture(pqRHS);
      // exercise
      swap(pqLHS, pqRHS);
      // verify
      //  +---+---+---+---+---+---+---+---+---+
      //  | 10| 8 | 9 | 4 | 3 | 7 | 5 |   |   | = pqLHS
      //  +---+---+---+---+---+---+---+---+---+
      //                10
      //          8            9
      //       4     3      7     5
      assertStandardFixture(pqLHS);
      assertEmptyFixture(pqRHS);
      // teardown
      teardownStandardFixture(pqLHS);
      teardownStandardFixture(pqRHS);
   }
   
   // swap(standard, stuff)
   void test_swap_standardStandard()
   {  // setup
      //  +---+---+---+---+---+---+---+---+---+
      //  | 10| 8 | 9 | 4 | 3 | 7 | 5 |   |   | = pqLHS
      //  +---+---+---+---+---+---+---+---+---+
      //                10
      //          8            9
      //       4     3      7     5
      custom::priority_queue <int> pqLHS;
      setupStandardFixture(pqLHS);
      custom::priority_queue <int> pqRHS;
      //  +----+----+----+
      //  | 99 | 88 | 77 | = pqRHS
      //  +----+----+----+
      //                99
      //          88            77
      pqRHS.container = {int(99), int(88), int(77)};
      // exercise
      swap(pqLHS, pqRHS);
      // verify
      //  +---+---+---+---+---+---+---+---+---+
      //  | 10| 8 | 9 | 4 | 3 | 7 | 5 |   |   | = pqRHS
      //  +---+---+---+---+---+---+---+---+---+
      //                10
      //          8            9
      //       4     3      7     5
      assertStandardFixture(pqRHS);
      //  +----+----+----+
      //  | 99 | 88 | 77 | = pqLHS
      //  +----+----+----+
      //                99
      //          88            77
      assertUnit(pqLHS.container.size() == 3);
      if (pqLHS.container.size() == 3)
      {
         assertUnit(pqLHS.container[0] == int(99));
         assertUnit(pqLHS.container[1] == int(88));
         assertUnit(pqLHS.container[2] == int(77));
      }
      // teardown
      teardownStandardFixture(pqLHS);
      teardownStandardFixture(pqRHS);
   }
   
   
   /***************************************
    * PERCOLATE
    ***************************************/

   // test percolate down with no change
   void test_percolateDown_nothing()
   {  // setup
      //    0   1   2   3   4   5   6
      //  +---+---+---+---+---+---+---+---+---+
      //  | 10| 8 | 7 | 4 | 3 | 9 | 5 |   |   |
      //  +---+---+---+---+---+---+---+---+---+
      //               10
      //         8            7
      //      4     3      9     5
      custom::priority_queue <int> pq;
      setupStandardFixture(pq);
      // Exercise
      bool returnValue = pq.percolateDown(1 /*indexHeap*/);
      // Verify
      //    1   2   3   4   5   6   7   8   9
      //  +---+---+---+---+---+---+---+---+---+
      //  | 10| 8 | 9 | 4 | 3 | 7 | 5 |   |   |
      //  +---+---+---+---+---+---+---+---+---+
      //               10
      //         8            9
      //      4     3      7     5
      assertUnit(returnValue == false);
      assertStandardFixture(pq);
      // Teardown
      teardownStandardFixture(pq);
   }
   
   // test percolate down on a one-level change
   void test_percolateDown_oneLevel()
   {  // setup
      //    0   1   2   3   4   5   6
      //  +---+---+---+---+---+---+---+---+---+
      //  | 10| 8 | 7 | 4 | 3 | 9 | 5 |   |   |
      //  +---+---+---+---+---+---+---+---+---+
      //               10
      //         8            7
      //      4     3      9     5
      custom::priority_queue <int> pq;
      setupStandardFixture(pq);
      pq.container[3-1] = int(7);
      pq.container[6-1] = int(9);
      // Exercise
      bool returnValue = pq.percolateDown(3 /*indexHeap*/);
      // Verify
      //    1   2   3   4   5   6   7   8   9
      //  +---+---+---+---+---+---+---+---+---+
      //  | 10| 8 | 9 | 4 | 3 | 7 | 5 |   |   |
      //  +---+---+---+---+---+---+---+---+---+
      //               10
      //         8            9
      //      4     3      7     5
      assertUnit(returnValue == true);
      assertStandardFixture(pq);
      // Teardown
      teardownStandardFixture(pq);
   }

   // test percolate down on a one-level change
   void test_percolateDown_twoLevels()
   {  // setup
      //    1   2   3   4   5   6   7   8   9
      //  +---+---+---+---+---+---+---+---+---+
      //  | 5 | 8 | 10| 4 | 3 | 7 | 9 |   |   |
      //  +---+---+---+---+---+---+---+---+---+
      //               5
      //         8            10
      //      4     3      7     9
      custom::priority_queue <int> pq;
      setupStandardFixture(pq);
      pq.container[1-1] = int(5);
      pq.container[3-1] = int(10);
      pq.container[7-1] = int(9);
      // Exercise
      bool returnValue = pq.percolateDown(1 /*indexHeap*/);
      // Verify
      //    1   2   3   4   5   6   7   8   9
      //  +---+---+---+---+---+---+---+---+---+
      //  | 10| 8 | 9 | 4 | 3 | 7 | 5 |   |   |
      //  +---+---+---+---+---+---+---+---+---+
      //               10
      //         8            9
      //      4     3      7     5
      assertUnit(returnValue == true);
      assertStandardFixture(pq);
      // Teardown
      teardownStandardFixture(pq);
   }

   /***************************************
    * HEAPIFY
    ***************************************/

    // test heap down with no elements
   void test_heapify_nothing()
   {  // setup
      //  +---+---+---+---+---+---+---+---+---+
      //  |   |   |   |   |   |   |   |   |   |
      //  +---+---+---+---+---+---+---+---+---+
      custom::priority_queue <int> pq;
      Spy::reset();
      // Exercise
      pq.heapify();
      // Verify
      assertUnit(pq.container.size() == 0);
      // Teardown
   }

   // test heap down with three elements
   void test_heapify_oneLevel()
   {  // setup
      //  +---+---+---+---+---+---+---+---+---+
      //  | 3 | 4 | 5 |   |   |   |   |   |   |
      //  +---+---+---+---+---+---+---+---+---+
      //             3
      //          4      5
      custom::priority_queue <int> pq;
      pq.container = { 3, 4, 5 };
      Spy::reset();
      // Exercise
      pq.heapify();
      // Verify
      //    1   2   3
      //  +---+---+---+---+---+---+---+---+---+
      //  | 5 | 4 | 3 |   |   |   |   |   |   |
      //  +---+---+---+---+---+---+---+---+---+
      //             5
      //          4      3
      assertUnit(pq.container.size() == 3);
      if (pq.container.size() == 3)
      {
         assertUnit(pq.container[1 - 1] == 5);
         assertUnit(pq.container[2 - 1] == 4);
         assertUnit(pq.container[3 - 1] == 3);
      }
      // Teardown
      pq.container.clear();
   }

   // test heap down with seven elements
   void test_heapify_twoLevels()
   {  // setup
      //    1   2   3   4   5   6   7
      //  +---+---+---+---+---+---+---+---+---+
      //  | 1 | 2 | 3 | 4 | 5 | 6 | 7 |   |   |
      //  +---+---+---+---+---+---+---+---+---+
      //             1
      //          2      3
      //         4 5    6 7
      custom::priority_queue <int> pq;
      pq.container = {1, 2, 3, 4, 5, 6, 7 };
      Spy::reset();
      // Exercise
      pq.heapify();
      // Verify
      //    1   2   3   4   5   6   7
      //  +---+---+---+---+---+---+---+---+---+
      //  | 7 | 5 | 6 | 4 | 2 | 1 | 3 |   |   |
      //  +---+---+---+---+---+---+---+---+---+
      //             7
      //          5      6
      //         4 2    1 3
      assertUnit(pq.container.size() == 7);
      if (pq.container.size() == 7)
      {
         assertUnit(pq.container[1 - 1] == int(7));
         assertUnit(pq.container[2 - 1] == int(5));
         assertUnit(pq.container[3 - 1] == int(6));
         assertUnit(pq.container[4 - 1] == int(4));
         assertUnit(pq.container[5 - 1] == int(2));
         assertUnit(pq.container[6 - 1] == int(1));
         assertUnit(pq.container[7 - 1] == int(3));
      }
      // Teardown
      pq.container.clear();
   }

   /***************************************
    * TOP
    ***************************************/

   // top of an empty priority queue
   void test_top_empty()
   {  // setup
      custom::priority_queue <int> pq;
      int value(99);
      // exercise
      try
      {
         value = pq.top();
         // verify
         assertUnit(false);
      }
      catch (const std::out_of_range& error)
      {
         assertUnit(error.what() == std::string("std:out_of_range"));
      }
      assertUnit(value == int(99));
      assertEmptyFixture(pq);
   }  // teardown

   // top of the standard fixture
   void test_top_standard()
   {  // setup
      //  +---+---+---+---+---+---+---+---+---+
      //  | 10| 8 | 9 | 4 | 3 | 7 | 5 |   |   |
      //  +---+---+---+---+---+---+---+---+---+
      custom::priority_queue <int> pq;
      setupStandardFixture(pq);
      int value(99);
      // exercise
      value = pq.top();
      // verify
      assertUnit(value == int(10));
      assertStandardFixture(pq);
      // teardown
      teardownStandardFixture(pq);
   }  

  /***************************************
   * POP
   ***************************************/

   // pop an empty priority queue
   void test_pop_empty()
   {  // setup
      custom::priority_queue <int> pq;
      // exercise
      pq.pop();
      // verify
      assertEmptyFixture(pq);
   }  // teardown

   // pop a priority queue with a single element
   void test_pop_one()
   {  // setup
      //  +----+
      //  | 99 |
      //  +----+
      custom::priority_queue <int> pq;
      pq.container.push_back(int(99));
      // exercise
      pq.pop();
      // verify
      //  +----+
      //  |    |
      //  +----+
      assertEmptyFixture(pq);
      // teardown
   }

   // pop a priority queue with two elements
   void test_pop_two()
   {  // setup
      //               10
      //         8
      //  +---+---+
      //  | 10| 8 |
      //  +---+---+
      custom::priority_queue <int> pq;
      pq.container.push_back(int(10));
      pq.container.push_back(int(8));
      // exercise
      pq.pop();
      // verify
      //  +---+
      //  | 8 |
      //  +---+
      assertUnit(pq.container.size() == 1);
      if (pq.container.size() == 1)
         assertUnit(pq.container[0] == int(8));
      // teardown
      teardownStandardFixture(pq);
   }

   // pop a priority queue with three elements
   void test_pop_three()
   {  // setup
      //               10
      //         8            9
      //  +---+---+---+
      //  | 10| 8 | 9 |
      //  +---+---+---+
      custom::priority_queue <int> pq;
      pq.container.push_back(int(10));
      pq.container.push_back(int(8));
      pq.container.push_back(int(9));
      // exercise
      pq.pop();
      // verify
      //               9
      //         8
      //  +---+---+
      //  | 9 | 8 |
      //  +---+---+
      assertUnit(pq.container.size() == 2);
      if (pq.container.size() == 2)
      {
         assertUnit(pq.container[0] == int(9));
         assertUnit(pq.container[1] == int(8));
      }
      // teardown
      teardownStandardFixture(pq);
   }
   
   // pop from the standard fixture
   void test_pop_standard()
   {  // setup
      //               10
      //         8            9
      //      4     3      7     5
      //  +---+---+---+---+---+---+---+---+---+
      //  | 10| 8 | 9 | 4 | 3 | 7 | 5 |   |   |
      //  +---+---+---+---+---+---+---+---+---+
      custom::priority_queue <int> pq;
      setupStandardFixture(pq);
      // exercise
      pq.pop();
      // verify
      //    0   1   2   3   4   5
      //  +---+---+---+---+---+---+---+---+---+
      //  | 9 | 8 | 7 | 4 | 3 | 5 |   |   |   |
      //  +---+---+---+---+---+---+---+---+---+
      //                9
      //          8            7
      //       4     3      5
      assertUnit(pq.container.size() == 6);
      if (pq.container.size() == 6)
      {
         assertUnit(pq.container[0] == int(9));
         assertUnit(pq.container[1] == int(8));
         assertUnit(pq.container[2] == int(7));
         assertUnit(pq.container[3] == int(4));
         assertUnit(pq.container[4] == int(3));
         assertUnit(pq.container[5] == int(5));
      }
      // teardown
      teardownStandardFixture(pq);
   }

   

   /***************************************
    * PUSH
    ***************************************/

   void test_push_empty()
   {  // setup
      custom::priority_queue <int> pq;
      int s(10);
      // exercise
      pq.push(s);
      // verify
      //  +----+
      //  | 10 |
      //  +----+
      assertUnit(pq.container.size() == 1);
      if (pq.container.size() == 1)
         assertUnit(pq.container[0] == int(10));
      // teardown
      teardownStandardFixture(pq);
   }

   // push an element to the bottom of a priority queue - level zero
   void test_push_levelZero()
   {  // setup
      //  +---+---+---+---+---+---+---+---+---+
      //  | 10| 8 | 9 | 4 | 3 | 7 | 5 |   |   |
      //  +---+---+---+---+---+---+---+---+---+
      //                10
      //          8            9
      //       4     3      7     5
      custom::priority_queue <int> pq;
      setupStandardFixture(pq);
      int s(1);
      // exercise
      pq.push(s);
      // verify
      //    1   2   3   4   5   6   7   8
      //  +---+---+---+---+---+---+---+---+---+
      //  | 10| 8 | 9 | 4 | 3 | 7 | 5 | 1 |   |
      //  +---+---+---+---+---+---+---+---+---+
      //                10
      //          8            9
      //       4     3      7     5
      //      1
      assertUnit(pq.container.size() == 8);
      if (pq.container.size() == 8)
      {
         assertUnit(pq.container[0] == int(10));
         assertUnit(pq.container[1] == int(8));
         assertUnit(pq.container[2] == int(9));
         assertUnit(pq.container[3] == int(4));
         assertUnit(pq.container[4] == int(3));
         assertUnit(pq.container[5] == int(7));
         assertUnit(pq.container[6] == int(5));
         assertUnit(pq.container[7] == int(1));
      }
      // teardown
      teardownStandardFixture(pq);
   }

   // push an element to a priority queue which goes up one level
   void test_push_levelOne()
   {  // setup
      //  +---+---+---+---+---+---+---+---+---+
      //  | 10| 8 | 9 | 4 | 3 | 7 | 5 |   |   |
      //  +---+---+---+---+---+---+---+---+---+
      //                10
      //          8            9
      //       4     3      7     5
      custom::priority_queue <int> pq;
      setupStandardFixture(pq);
      int s(6);
      // exercise
      pq.push(s);
      // verify
      //    1   2   3   4   5   6   7   8
      //  +---+---+---+---+---+---+---+---+---+
      //  | 10| 8 | 9 | 6 | 3 | 7 | 5 | 4 |   |
      //  +---+---+---+---+---+---+---+---+---+
      //                10
      //          8            9
      //       6     3      7     5
      //      4
      assertUnit(pq.container.size() == 8);
      if (pq.container.size() == 8)
      {
         assertUnit(pq.container[0] == int(10));
         assertUnit(pq.container[1] == int(8));
         assertUnit(pq.container[2] == int(9));
         assertUnit(pq.container[3] == int(6));
         assertUnit(pq.container[4] == int(3));
         assertUnit(pq.container[5] == int(7));
         assertUnit(pq.container[6] == int(5));
         assertUnit(pq.container[7] == int(4));
      }
      // teardown
      teardownStandardFixture(pq);
   }   
   
   // push an element to a priorty queue that goes up two levels
   void test_push_levelTwo()
   {  // setup
      //  +---+---+---+---+---+---+---+---+---+
      //  | 10| 8 | 9 | 4 | 3 | 7 | 5 |   |   |
      //  +---+---+---+---+---+---+---+---+---+
      //                10
      //          8            9
      //       4     3      7     5
      custom::priority_queue <int> pq;
      setupStandardFixture(pq);
      int s(9);
      // exercise
      pq.push(s);
      // verify
      //    1   2   3   4   5   6   7   8
      //  +---+---+---+---+---+---+---+---+---+
      //  | 10| 9 | 9 | 8 | 3 | 7 | 5 | 4 |   |
      //  +---+---+---+---+---+---+---+---+---+
      //                10
      //          9            9
      //       8     3      7     5
      //      4
      assertUnit(pq.container.size() == 8);
      if (pq.container.size() == 8)
      {
         assertUnit(pq.container[0] == int(10));
         assertUnit(pq.container[1] == int(9));
         assertUnit(pq.container[2] == int(9));
         assertUnit(pq.container[3] == int(8));
         assertUnit(pq.container[4] == int(3));
         assertUnit(pq.container[5] == int(7));
         assertUnit(pq.container[6] == int(5));
         assertUnit(pq.container[7] == int(4));
      }
      // teardown
      teardownStandardFixture(pq);
   }

   // push an element to the top of a priority queue
   void test_push_levelThree()
   {  // setup
      //  +---+---+---+---+---+---+---+---+---+
      //  | 10| 8 | 9 | 4 | 3 | 7 | 5 |   |   |
      //  +---+---+---+---+---+---+---+---+---+
      //                10
      //          8            9
      //       4     3      7     5
      custom::priority_queue <int> pq;
      setupStandardFixture(pq);
      int s(11);
      // exercise
      pq.push(s);
      // verify
      //    1   2   3   4   5   6   7   8
      //  +---+---+---+---+---+---+---+---+---+
      //  | 11| 10| 9 | 8 | 3 | 7 | 5 | 4 |   |
      //  +---+---+---+---+---+---+---+---+---+
      //                11
      //          10            9
      //       8     3      7     5
      //      4
      assertUnit(pq.container.size() == 8);
      if (pq.container.size() == 8)
      {
         assertUnit(pq.container[0] == int(11));
         assertUnit(pq.container[1] == int(10));
         assertUnit(pq.container[2] == int(9));
         assertUnit(pq.container[3] == int(8));
         assertUnit(pq.container[4] == int(3));
         assertUnit(pq.container[5] == int(7));
         assertUnit(pq.container[6] == int(5));
         assertUnit(pq.container[7] == int(4));
      }      // teardown
      teardownStandardFixture(pq);
   }

   // move push an element on an empty priority queue
   void test_pushMove_empty()
   {  // setup
      custom::priority_queue <int> pq;
      int s(10);
      // exercise
      pq.push(std::move(s));
      // verify
      //  +----+
      //  | 10 |
      //  +----+
      assertUnit(pq.container.size() == 1);
      if (pq.container.size() == 1)
         assertUnit(pq.container[0] == int(10));
      // teardown
      teardownStandardFixture(pq);
   }

   // move push an element to the bottom of a priority queue - level zero
   void test_pushMove_levelZero()
   {  // setup
      //  +---+---+---+---+---+---+---+---+---+
      //  | 10| 8 | 9 | 4 | 3 | 7 | 5 |   |   |
      //  +---+---+---+---+---+---+---+---+---+
      //                10
      //          8            9
      //       4     3      7     5
      custom::priority_queue <int> pq;
      setupStandardFixture(pq);
      int s(1);
      // exercise
      pq.push(std::move(s));
      // verify
      //    1   2   3   4   5   6   7   8
      //  +---+---+---+---+---+---+---+---+---+
      //  | 10| 8 | 9 | 4 | 3 | 7 | 5 | 1 |   |
      //  +---+---+---+---+---+---+---+---+---+
      //                10
      //          8            9
      //       4     3      7     5
      //      1
      assertUnit(pq.container.size() == 8);
      if (pq.container.size() == 8)
      {
         assertUnit(pq.container[0] == int(10));
         assertUnit(pq.container[1] == int(8));
         assertUnit(pq.container[2] == int(9));
         assertUnit(pq.container[3] == int(4));
         assertUnit(pq.container[4] == int(3));
         assertUnit(pq.container[5] == int(7));
         assertUnit(pq.container[6] == int(5));
         assertUnit(pq.container[7] == int(1));
      }
      // teardown
      teardownStandardFixture(pq);
   }

   // move push an element to a priority queue which goes up one level
   void test_pushMove_levelOne()
   {  // setup
      //  +---+---+---+---+---+---+---+---+---+
      //  | 10| 8 | 9 | 4 | 3 | 7 | 5 |   |   |
      //  +---+---+---+---+---+---+---+---+---+
      //                10
      //          8            9
      //       4     3      7     5
      custom::priority_queue <int> pq;
      setupStandardFixture(pq);
      int s(6);
      // exercise
      pq.push(std::move(s));
      // verify
      //    1   2   3   4   5   6   7   8
      //  +---+---+---+---+---+---+---+---+---+
      //  | 10| 8 | 9 | 6 | 3 | 7 | 5 | 4 |   |
      //  +---+---+---+---+---+---+---+---+---+
      //                10
      //          8            9
      //       6     3      7     5
      //      4
      assertUnit(pq.container.size() == 8);
      if (pq.container.size() == 8)
      {
         assertUnit(pq.container[0] == int(10));
         assertUnit(pq.container[1] == int(8));
         assertUnit(pq.container[2] == int(9));
         assertUnit(pq.container[3] == int(6));
         assertUnit(pq.container[4] == int(3));
         assertUnit(pq.container[5] == int(7));
         assertUnit(pq.container[6] == int(5));
         assertUnit(pq.container[7] == int(4));
      }
      // teardown
      teardownStandardFixture(pq);
   }

   // move push an element to a priorty queue that goes up two levels
   void test_pushMove_levelTwo()
   {  // setup
      //  +---+---+---+---+---+---+---+---+---+
      //  | 10| 8 | 9 | 4 | 3 | 7 | 5 |   |   |
      //  +---+---+---+---+---+---+---+---+---+
      //                10
      //          8            9
      //       4     3      7     5
      custom::priority_queue <int> pq;
      setupStandardFixture(pq);
      int s(9);
      // exercise
      pq.push(std::move(s));
      // verify
      //    1   2   3   4   5   6   7   8
      //  +---+---+---+---+---+---+---+---+---+
      //  | 10| 9 | 9 | 8 | 3 | 7 | 5 | 4 |   |
      //  +---+---+---+---+---+---+---+---+---+
      //                10
      //          9            9
      //       8     3      7     5
      //      4
      assertUnit(pq.container.size() == 8);
      if (pq.container.size() == 8)
      {
         assertUnit(pq.container[0] == int(10));
         assertUnit(pq.container[1] == int(9));
         assertUnit(pq.container[2] == int(9));
         assertUnit(pq.container[3] == int(8));
         assertUnit(pq.container[4] == int(3));
         assertUnit(pq.container[5] == int(7));
         assertUnit(pq.container[6] == int(5));
         assertUnit(pq.container[7] == int(4));
      }
      // teardown
      teardownStandardFixture(pq);
   }

   // move push an element to the top of a priority queue
   void test_pushMove_levelThree()
   {  // setup
      //  +---+---+---+---+---+---+---+---+---+
      //  | 10| 8 | 9 | 4 | 3 | 7 | 5 |   |   |
      //  +---+---+---+---+---+---+---+---+---+
      //                10
      //          8            9
      //       4     3      7     5
      custom::priority_queue <int> pq;
      setupStandardFixture(pq);
      int s(11);
      // exercise
      pq.push(std::move(s));
      // verify
      //    1   2   3   4   5   6   7   8
      //  +---+---+---+---+---+---+---+---+---+
      //  | 11| 10| 9 | 8 | 3 | 7 | 5 | 4 |   |
      //  +---+---+---+---+---+---+---+---+---+
      //                11
      //          10            9
      //       8     3      7     5
      //      4
      assertUnit(pq.container.size() == 8);
      if (pq.container.size() == 8)
      {
         assertUnit(pq.container[0] == int(11));
         assertUnit(pq.container[1] == int(10));
         assertUnit(pq.container[2] == int(9));
         assertUnit(pq.container[3] == int(8));
         assertUnit(pq.container[4] == int(3));
         assertUnit(pq.container[5] == int(7));
         assertUnit(pq.container[6] == int(5));
         assertUnit(pq.container[7] == int(4));
      }      // teardown
      teardownStandardFixture(pq);
   }

   /***************************************************
    * SETUP STANDARD FIXTURE
    *                 10
    *           8            9
    *        4     3      7     5
    * 
    *   +---+---+---+---+---+---+---+---+---+
    *   | 10| 8 | 9 | 4 | 3 | 7 | 5 |   |   |
    *   +---+---+---+---+---+---+---+---+---+
    ***************************************************/
   void setupStandardFixture(custom::priority_queue <int>& pq)
   {
      pq.container = {int(10), int(8), int(9), int(4), int(3), int(7), int(5)};
      pq.container.reserve(9);
   }
   
   /***************************************************
    * VERIFY EMPTY FIXTURE
    ***************************************************/
   void assertEmptyFixtureParameters(const custom::priority_queue <int>& pq, int line, const char* function)
   {
      assertIndirect(pq.container.empty());
   }
   
   /***************************************************
    * VERIFY STANDARD FIXTURE
    *                 10
    *           8            9
    *        4     3      7     5
    *
    *   +---+---+---+---+---+---+---+---+---+
    *   | 10| 8 | 9 | 4 | 3 | 7 | 5 |   |   |
    *   +---+---+---+---+---+---+---+---+---+
    ***************************************************/
   void assertStandardFixtureParameters(const custom::priority_queue <int>& pq, int line, const char* function)
   {
      assertIndirect(pq.container.size() == 7);
      
      if (pq.container.size() >= 7)
      {
         assertIndirect(pq.container[1-1] == int(10));
         assertIndirect(pq.container[2-1] == int(8));
         assertIndirect(pq.container[3-1] == int(9));
         assertIndirect(pq.container[4-1] == int(4));
         assertIndirect(pq.container[5-1] == int(3));
         assertIndirect(pq.container[6-1] == int(7));
         assertIndirect(pq.container[7-1] == int(5));
      }
   }
   
   /***************************************************
    * VERIFY TIGHT FIXTURE 
    *                 10
    *           8            9
    *        4     3      7     5
    *
    *   +---+---+---+---+---+---+---+
    *   | 10| 8 | 9 | 4 | 3 | 7 | 5 |
    *   +---+---+---+---+---+---+---+
    ***************************************************/
   void assertTightFixtureParametersX(const custom::priority_queue <int>& pq, int line, const char* function)
   {
      assertIndirect(pq.container.size() == 7);

      if (pq.container.size() >= 7)
      {
         assertIndirect(pq.container[1-1] == int(10));
         assertIndirect(pq.container[2-1] == int(8));
         assertIndirect(pq.container[3-1] == int(9));
         assertIndirect(pq.container[4-1] == int(4));
         assertIndirect(pq.container[5-1] == int(3));
         assertIndirect(pq.container[6-1] == int(7));
         assertIndirect(pq.container[7-1] == int(5));
      }
   }
   
   /***************************************************
    * TEARDOWN STANDARD FIXTURE
    *   +---+---+---+---+---+---+---+---+---+---+
    *   |   |   |   |   |   |   |   |   |   |   |
    *   +---+---+---+---+---+---+---+---+---+---+
    ***************************************************/
   void teardownStandardFixture(custom::priority_queue <int>& pq)
   {
      pq.container.empty();
   }
};

#endif // DEBUG
