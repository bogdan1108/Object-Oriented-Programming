#include <stdio.h>
#include <limits.h>
#include "tests.h"

// Write a function that takes as an input an array of integer numbers (both positive and negative numbers and returns the value of the triplet with the maximum product, as well as the elements that form this triplet (in increasing order). 
// Use pass by pointer/address to return the elements that form that triplet. 
// Think about the appropriate data type for the result. If the size of the array is less than 3, you should return the minimum
// representable value of the data type and the elements that form the triplet should be set to 0.
long long computeMaxTriplet(int arr[], unsigned int sz, int *t1, int *t2, int *t3){
    // max product value of 3 number from an array
    if (sz < 3)
    {
        *t1 = 0;
        *t2 = 0;
        *t3 = 0;

        printf("The array has less than 3 elements. Application will now stop.");
        return LLONG_MIN;
    }
    if (sz == 3)
    {
        *t1 = arr[0];
        *t2 = arr[1];
        *t3 = arr[2];
        return arr[0] * arr[1] * arr[2];
    }
    long long max = LLONG_MIN;
    int i, j, k;
    for(i = 0; i < sz; i++)
    {
        for(j = i + 1; j < sz; j++)
        {
            for(k = j + 1; k < sz; k++)
            {
                if(((long long)arr[i] * arr[j] * arr[k]) > max)
                {
                    max = (long long)arr[i] * arr[j] * arr[k];
                    if (arr[i] > arr[j] && arr[i] > arr[k]) {
                        *t3 = arr[i];
                        if (arr[j] > arr[k]) {
                            *t2 = arr[j];
                            *t1 = arr[k];
                        } else {
                            *t2 = arr[k];
                            *t1 = arr[j];
                        }
                    } else if (arr[j] > arr[i] && arr[j] > arr[k]) {
                        *t3 = arr[j];
                        if (arr[i] > arr[k]) {
                            *t2 = arr[i];
                            *t1 = arr[k];
                        } else {
                            *t2 = arr[k];
                            *t1 = arr[i];
                        }
                    } else {
                        *t3 = arr[k];
                        if (arr[i] > arr[j]) {
                            *t2 = arr[i];
                            *t1 = arr[j];
                        } else {
                            *t2 = arr[j];
                            *t1 = arr[i];
                        }
                    }
                }
            }
        }
    }

    return max;
}

int main()
{
#if ENABLE_TESTS == 1
    run_tests(true);
#endif
    unsigned int n;
    scanf("%d", &n);
    int a[n];
    for(int i = 0; i < n; i++)
        scanf("%d", &a[i]);
    int t1, t2, t3;
    long long max = computeMaxTriplet(a, n, &t1, &t2, &t3);
    printf("The maximum triplet is (%d, %d, %d) with a product of ”%lld”", t1, t2, t3, max);
    return 0;
}
