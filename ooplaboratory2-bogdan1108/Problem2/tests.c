#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <stdbool.h>

#include "tests.h"

static unsigned char testsPassed;
extern const char* my_strchr(const char* s, char character);

#if ENABLE_TESTS > 0
enum Test {
    NOT_IN_STR = 0,
    FIRST_POS,
    LAST_POS,
    SINGLE_OCCURENCE,
    MULTIPLE_OCCURENCE,
    NUM_TESTS,
};

#define FIRST_TEST NON_ALPHA
#define MAXSCORE 36
#define CHARITY 10


void printTestCase(char* str, char ch){
    printf("Search %c in %s\n", ch, str);
}

unsigned int runTest(int test, bool verbose) {

    switch (test) {
    case NOT_IN_STR: {
        char* str = "yellow";
        char ch = 't';

        const char* res = my_strchr(str, ch);
        char* eres = strchr(str, ch);
        if(res == eres)
            return 1;
        if (verbose){
            printTestCase(str, ch);
            printf("Expected\n NULL, but got\n %s\n", res);
        }
        return 0;
    }

    case FIRST_POS: {
        char* str = "yellow";
        char ch = 'y';

        const char* res = my_strchr(str, ch);
        char* eres = strchr(str, ch);
        if(res == eres)
            return 1;
        if (verbose){
            printTestCase(str, ch);
            printf("Expected\n %s, but got\n %s\n", eres, res);
        }
        return 0;
    }

    case LAST_POS: {
        char* str = "yellow";
        char ch = 'w';

        const char* res = my_strchr(str, ch);
        char* eres = strchr(str, ch);
        if(res == eres)
            return 1;
        if (verbose){
            printTestCase(str, ch);
            printf("Expected\n %s, but got\n %s\n", eres, res);
        }
        return 0;
    }

    case SINGLE_OCCURENCE: {
        char* str = "yellow";
        char ch = 'e';

        const char* res = my_strchr(str, ch);
        char* eres = strchr(str, ch);
        if(res == eres)
            return 1;
        if (verbose){
            printTestCase(str, ch);
            printf("Expected\n %s, but got\n %s\n", eres, res);
        }
        return 0;
    }

    case MULTIPLE_OCCURENCE: {
        char* str = "yellow";
        char ch = 'l';

        const char* res = my_strchr(str, ch);
        char* eres = strchr(str, ch);
        if(res == eres)
            return 1;
        if (verbose){
            printTestCase(str, ch);
            printf("Expected\n %s, but got\n %s\n", eres, res);
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
