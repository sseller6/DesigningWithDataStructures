/***********************************************************************
 * Header:
 *    Test
 * Summary:
 *    Driver to test list.h
 * Author
 *    Br. Helfrich
 ************************************************************************/

#ifndef DEBUG
#define DEBUG   
#endif
 //#undef DEBUG  // Remove this comment to disable unit tests

#include "testList.h"       // for the spy unit tests


/**********************************************************************
 * MAIN
 * This is just a simple menu to launch a collection of tests
 ***********************************************************************/
int main()
{
#ifdef DEBUG
   // unit tests
   TestList().run();
#endif // DEBUG
   
   return 0;
}
