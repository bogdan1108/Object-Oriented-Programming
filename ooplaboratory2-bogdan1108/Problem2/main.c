#include <stdio.h>
#include <limits.h>
#include "tests.h"


// The strchr function is used to locate a character in a string. 
// More specifically, it returns a pointer to the first occurrence of the character in the string and NULL otherwise. 
// Write a function my_strchr, with the same parametersand return value as strchr.
char* my_strchr(char* s, char character){
    // write my_strchr without using strchr, strlen or [] operator
    char* p = s;
    while (*p != '\0')
    {
        if (*p == character)
        {
            return p;
        }
        p++;
    }
    return NULL;
}

int main()
{
#if ENABLE_TESTS > 0
    run_tests(true);
#endif
    char s[] = "Hello World!";
    char c = 'o';
    printf("%s\n", my_strchr(s, c));
    return 0;
}
