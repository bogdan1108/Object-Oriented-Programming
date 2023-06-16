#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <stdbool.h>

#include "tests.h"

static unsigned char testsPassed;
long long computeMaxTriplet(int arr[], unsigned int sz, int* t1, int* t2, int* t3);


#if ENABLE_TESTS > 0
enum Test {
    LESS_THAN_3 = 0,
    EXACTLY_3,
    POS_NEG_1,
    POS_NEG_2,
    POS_NEG_3,
    LARGE_RES_1,
    LARGE_RES_2,
    NUM_TESTS,
};

#define FIRST_TEST NON_ALPHA
#define MAXSCORE 36
#define CHARITY 10

char* testName(int test) {
    if (test == LESS_THAN_3)
        return "Less than three elements";
    if (test == EXACTLY_3)
        return "Exactly three elements";
    if (test == POS_NEG_1)
        return "Positive and negative values 1";
    if (test == POS_NEG_2)
        return "Positive and negative values 2";
    if (test == POS_NEG_3)
        return "Positive and negative values 3";
    if (test == LARGE_RES_1)
        return "Large result 1";
    if (test == LARGE_RES_2)
        return "Large result 2";
    if (test == NUM_TESTS)
        return "NUM_TESTS";

    return "";
}

void printArray(int arr[], unsigned int sz){
    printf("\nInput array:\n");
    for(int i = 0; i < sz; i++){
        printf("%d ", arr[i]);
    }
    printf("\n");
}

unsigned int runTest(int test, bool verbose) {


    switch (test) {
    case LESS_THAN_3: {
        int arr[] = {0, 1};
        unsigned int sz = sizeof(arr)/sizeof(arr[0]);
        long long res = 0, eres = LLONG_MIN;
        int t1, t2, t3;
        int et1 = 0, et2 = 0, et3 = 0;
        res = computeMaxTriplet(arr, sz, &t1, &t2, &t3);
        if(res == eres && t1 == et1 && t2 == et2 && t3 == et3)
            return 1;
        if (verbose){
            printArray(arr, sz);
            printf("Expected\n %d*%d*%d=%lld, but got\n %d*%d*%d=%lld\n", et1, et2, et3, eres, t1, t2, t3, res);
        }
        return 0;
    }

    case EXACTLY_3: {
        int arr[] = {1, 11, 12};
        unsigned int sz = sizeof(arr)/sizeof(arr[0]);
        long long res = 0, eres = 132;
        int t1, t2, t3;
        int et1 = 1, et2 = 11, et3 = 12;
        res = computeMaxTriplet(arr, sz, &t1, &t2, &t3);
        if(res == eres && t1 == et1 && t2 == et2 && t3 == et3)
            return 1;

        if (verbose){
            printArray(arr, sz);
            printf("Expected\n %d*%d*%d=%lld, but got\n %d*%d*%d=%lld\n", et1, et2, et3, eres, t1, t2, t3, res);
        }
        return 0;
    }

    case POS_NEG_1: {
        int arr[] = {-11, 12, 1, 40, 70, 90, 40, -100};
        unsigned int sz = sizeof(arr)/sizeof(arr[0]);
        long long res = 0, eres = 252000;
        int t1, t2, t3;
        int et1 = 40, et2 = 70, et3 = 90;
        res = computeMaxTriplet(arr, sz, &t1, &t2, &t3);
        if(res == eres && t1 == et1 && t2 == et2 && t3 == et3)
            return 1;

        if (verbose){
            printArray(arr, sz);
            printf("Expected\n %d*%d*%d=%lld, but got\n %d*%d*%d=%lld\n", et1, et2, et3, eres, t1, t2, t3, res);
        }
        return 0;
    }

    case POS_NEG_2: {
        int arr[] = {-101, 12, 1, 40, 70, 90, 40, -100};
        unsigned int sz = sizeof(arr)/sizeof(arr[0]);
        long long res = 0, eres = 909000 ;
        int t1, t2, t3;
        int et1 = -101, et2 = -100, et3 = 90;
        res = computeMaxTriplet(arr, sz, &t1, &t2, &t3);
        if(res == eres && t1 == et1 && t2 == et2 && t3 == et3)
            return 1;

        if (verbose){
            printArray(arr, sz);
            printf("Expected\n %d*%d*%d=%lld, but got\n %d*%d*%d=%lld\n", et1, et2, et3, eres, t1, t2, t3, res);
        }
        return 0;
    }

    case POS_NEG_3: {
        int arr[] = {-59, -83, -66, -60, -11, -36, -52, -82, -48, -26, -65, -35, -39, -13, -39, -59, -75};
        unsigned int sz = sizeof(arr)/sizeof(arr[0]);
        long long res = 0, eres = -3718 ;
        int t1, t2, t3;
        int et1 = -26, et2 = -13, et3 = -11;
        res = computeMaxTriplet(arr, sz, &t1, &t2, &t3);
        if(res == eres && t1 == et1 && t2 == et2 && t3 == et3)
            return 1;

        if (verbose){
            printArray(arr, sz);
            printf("Expected\n %d*%d*%d=%lld, but got\n %d*%d*%d=%lld\n", et1, et2, et3, eres, t1, t2, t3, res);
        }
        return 0;
    }

    case LARGE_RES_1: {
        int arr[] = {-59, 1495, -93, 1092, 88, 861, 833, 1841, 1554, 1165, 1387, 628, -18, 1964, 1425, 391, 786, 1297, 509, 1118, 656, 1850, 1693, 53, 192, 1737, 449, 1744, 637, 814, 1129, 536, -92, 893, 1769, 831, 259, 891, 63, 1358, 1186, 512, 1696};
        unsigned int sz = sizeof(arr)/sizeof(arr[0]);
        long long res = 0, eres = 6689089400 ;
        int t1, t2, t3;
        int et1 = 1841, et2 = 1850, et3 = 1964;
        res = computeMaxTriplet(arr, sz, &t1, &t2, &t3);
        if(res == eres && t1 == et1 && t2 == et2 && t3 == et3)
            return 1;

        if (verbose){
            printArray(arr, sz);
            printf("Expected\n %d*%d*%d=%lld, but got\n %d*%d*%d=%lld\n", et1, et2, et3, eres, t1, t2, t3, res);
        }
        return 0;
    }

    case LARGE_RES_2: {
        int arr[] = {-1001, 134002, 100, 40000, 7000, 9000, 1440000, -10000};
        unsigned int sz = sizeof(arr)/sizeof(arr[0]);
        long long res = 0, eres = 7718515200000000;
        int t1, t2, t3;
        int et1 = 40000, et2 = 134002, et3 = 1440000;
        res = computeMaxTriplet(arr, sz, &t1, &t2, &t3);
        if(res == eres && t1 == et1 && t2 == et2 && t3 == et3)
            return 1;

        if (verbose){
            printArray(arr, sz);
            printf("Expected\n %d*%d*%d=%lld, but got\n %d*%d*%d=%lld\n", et1, et2, et3, eres, t1, t2, t3, res);
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
    for (unsigned int i = LESS_THAN_3; i < NUM_TESTS; i++) {
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
    printf("Problem 1 tests %d/%d (passed/total)\nGrade: %.2f\n", testsPassed, NUM_TESTS, (float)testsPassed / NUM_TESTS*10);

}
#endif
