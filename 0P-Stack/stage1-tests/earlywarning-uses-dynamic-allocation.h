/***
 * ensure dynamic allocation
 */

#ifndef STACK_USE_DYNAMIC_ALLOCATION_H
#define STACK_USE_DYNAMIC_ALLOCATION_H

TEST(ProjectRequirements, UsesDynamicAllocation) {
    stack stk;
    if( sizeof(stk) >= 100 ) {
        std::cerr << "Your _empty_ stack object is very large." << std::endl << 
                     "Are you using dynamically allocated (new[], new) memory (as the write-up says to do)" << std::endl <<
                     "or a statically allocated character array (char array[SOME_BIG_NUMBER])?" << std::endl;
    }
    ASSERT_LT(sizeof(stk), 100);
}

#endif
