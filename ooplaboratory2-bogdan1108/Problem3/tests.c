#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <stdbool.h>

#include "tests.h"

static unsigned char testsPassed;

void find_all( const char * str, char character, int*  positions, unsigned int cap, unsigned int * l);

#if ENABLE_TESTS > 0
enum Test {
    NOT_IN_STR = 0,
    FIRST_POS,
    LAST_POS,
    MULTIPLE,
    MULTIPLE_OWERFLOW,
    NUM_TESTS,
};


void printTestCase(char* str, char ch){
    printf("----------------------\n");
    printf("Search %c in %s\n", ch, str);
}

bool arraysEqual(int* arr1, int* arr2, int cap){
    for(int i = 0; i < cap; i++)
        if(arr1[i] != arr2[i])
            return false;
    return true;
}

void printArray(int* arr, int cap){
    for(int i = 0; i < cap; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

unsigned int runTest(int test, bool verbose) {

    switch (test) {
    case NOT_IN_STR: {
        char* str = "yellow";
        char ch = 't';
        int cap = 5;
        int positions[5];
        unsigned int l;

        int ePositions[5] = {-1, -1, -1, -1, -1};
        find_all(str, ch, positions, cap, &l);

        if(arraysEqual(positions, ePositions, cap))
            return 1;
        if(verbose){
            printTestCase(str, ch);
            printf("Expected\n");
        }
        return 0;
    }

    case FIRST_POS: {
        char* str = "yellow";
        char ch = 'y';
        int cap = 5;
        int positions[5];
        unsigned int l;

        int ePositions[5] = {0, -1, -1, -1, -1};
        find_all(str, ch, positions, cap, &l);

        if(arraysEqual(positions, ePositions, cap))
            return 1;
        if(verbose){
            printTestCase(str, ch);
            printf("Expected\n");
        }
        return 0;
    }


    case LAST_POS: {
        char* str = "yellow";
        char ch = 'w';
        int cap = 5;
        int positions[5];
        unsigned int l;

        int ePositions[5] = {5, -1, -1, -1, -1};
        find_all(str, ch, positions, cap, &l);

        if(arraysEqual(positions, ePositions, cap))
            return 1;
        if(verbose){
            printTestCase(str, ch);
            printf("Expected\n");
        }
        return 0;
    }

    case MULTIPLE: {
        char* str = "yellow";
        char ch = 'l';
        int cap = 5;
        int positions[5];
        unsigned int l;

        int ePositions[5] = {2, 3, -1, -1, -1};
        find_all(str, ch, positions, cap, &l);

        if(arraysEqual(positions, ePositions, cap))
            return 1;
        if(verbose){
            printTestCase(str, ch);
            printf("Expected\n");
            printArray(ePositions, cap);
            printf(", but got\n");
            printArray(positions, cap);
        }
        return 0;
    }

    case MULTIPLE_OWERFLOW: {
        char* str = "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa";
        char ch = 'a';
        int cap = 5;
        int positions[5];
        unsigned int l;

        int ePositions[5] = {0, 1, 2, 3, 4};
        find_all(str, ch, positions, cap, &l);

        if(arraysEqual(positions, ePositions, cap))
            return 1;
        if(verbose){
            printTestCase(str, ch);
            printf("Expected\n");
            printArray(ePositions, cap);
            printf(", but got\n");
            printArray(positions, cap);
        }
        return 0;
    }



    }

    return 255;
}


void red() {
    printf("\033[1;31m");
}

void green() {
    printf("\033[32m");
}

void reset() {
    printf("\033[0m");
}

void run_tests(bool verbose)
{

    testsPassed = 0;
    for (unsigned int i = NOT_IN_STR; i < NUM_TESTS; i++) {
        unsigned int res =  runTest(i, verbose);
        if(verbose){
            if (!res) {
                red();
                printf("Test %d failed\n", i+1);
                reset();
            }else{
                green();
                printf("Test %d passed\n", i+1);
                reset();
            }
        }
        testsPassed += res;
    }
    printf("Problem 2 tests %d/%d (passed/total), grade: %f\n", testsPassed, NUM_TESTS, (float)testsPassed / NUM_TESTS*10);

}
#endif
