#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include "tests.h"

// Using the function that you wrote for problem 2, write a function that computesand returns an array with all the positions of the occurrences of a character in a string.
void find_all( char * str, char character, int*  positions, unsigned int cap, unsigned int * l){
    // fill positions with -1
    for (int i = 0; i < cap; i++)
    {
        positions[i] = -1;
    }
    // find all occurences of character in str using strchr and store them in positions maximum cap times and if there are more than one character next to each other, count them as separate occurences
    char* p = str;
    int i = 0;
    while (*p != '\0')
    {
        if (*p == character)
        {
            positions[i] = p - str;
            i++;
        }
        p++;
    }
    // set l to the number of occurences of character in str
    *l = 0;
    for (int i = 0; i < cap; i++)
    {
        if (positions[i] != -1)
        {
            *l += 1;
        }
    }
    
 }

int main()
{
#if  ENABLE_TESTS > 0
    run_tests(true);
#endif 
    return 0;
}
