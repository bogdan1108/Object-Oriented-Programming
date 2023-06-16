#define FIRST_TEST NON_ALPHA
#define MAXSCORE 36
#define CHARITY 10

#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include "tests.h"

static unsigned char testsPassed;
extern void encrypt(char message[], int offset);


#if ENABLE_TESTS > 0
enum Test_e {
    NON_ALPHA = 0,
    POSITIVE_OFFSET,
    NEGATIVE_OFFSET,
    ALPHANUM,
    ZERO_OFFSET,
    MAX_OFFSET,
    NUM_TESTS,
};

char* testName(int test) {
    if (test == NON_ALPHA)
        return "Non-alpha string";
    if (test == POSITIVE_OFFSET)
        return "Positive offset";
    if (test == NEGATIVE_OFFSET)
        return "Negative offset";
    if (test == ALPHANUM)
        return "Alphanumeric message";
    if (test == ZERO_OFFSET)
        return "Zero offset";
    if (test == MAX_OFFSET)
        return "Offset 26";
    if (test == NUM_TESTS)
        return "NUM_TESTS";

    return "";
}

unsigned int runTest(int test, bool verbose) {


    switch (test) {
    case NON_ALPHA: {
        char msg[] = "123 566. 7.;'[][]`23445";
        char expected[] = "123 566. 7.;'[][]`23445";
        encrypt(msg, 3);
        if (!strcmp(msg, expected))
            return 1;
        if(verbose)
            printf("Expected\n %s, but got\n %s\n", expected, msg);
        return 0;
    }

    case POSITIVE_OFFSET: {
        char msg[] = "Cato, I grudge you your death, as you would have grudged me the preservation of your life.";
        char expected[] = "Jhav, P nybknl fvb fvby klhao, hz fvb dvbsk ohcl nybknlk tl aol wylzlychapvu vm fvby spml.";
        int offset = 7;
        encrypt(msg, offset);
        if (!strcmp(msg, expected))
            return 1;
        if (verbose)
            printf("Expected\n %s, but got\n %s\n", expected, msg);
        return 0;
    }

    case NEGATIVE_OFFSET: {
        char expected[] = "Cato, I grudge you your death, as you would have grudged me the preservation of your life.";
        char msg[] = "Jhav, P nybknl fvb fvby klhao, hz fvb dvbsk ohcl nybknlk tl aol wylzlychapvu vm fvby spml.";
        int offset = -7;
        encrypt(msg, offset);
        if (!strcmp(msg, expected))
            return 1;
        if (verbose)
            printf("Expected\n %s, but got\n %s\n", expected, msg);
        return 0;
    }

    case ZERO_OFFSET: {
        char expected[] = "veni, vidi, vici";
        char msg[] = "veni, vidi, vici";
        int offset = 0;
        encrypt(msg, offset);
        if (!strcmp(msg, expected))
            return 1;
        if (verbose)
            printf("Expected\n %s, but got\n %s\n", expected, msg);
        return 0;
    }

    case MAX_OFFSET: {
        char expected[] = "If he had anything confidential to say, he wrote it in cipher, that is, by so changing the order of the letters of the alphabet, that not a word could be made out.";
        char msg[] = "If he had anything confidential to say, he wrote it in cipher, that is, by so changing the order of the letters of the alphabet, that not a word could be made out.";
        int offset = 26;
        encrypt(msg, offset);
        if (!strcmp(msg, expected))
            return 1;
        if (verbose)
            printf("Expected\n %s, but got\n %s\n", expected, msg);
        return 0;
    }

    case ALPHANUM: {
        char msg[] = "The Battle of Pharsalus was the decisive battle of Caesar's Civil War fought on 9 August 48 BC near Pharsalus in central Greece. Julius Caesar and his allies formed up opposite the army of the Roman Republic under the command of Pompey.";
        char expected[] = "Dro Lkddvo yp Zrkbckvec gkc dro nomscsfo lkddvo yp Mkockb'c Msfsv Gkb pyeqrd yx 9 Keqecd 48 LM xokb Zrkbckvec sx moxdbkv Qboomo. Tevsec Mkockb kxn rsc kvvsoc pybwon ez yzzycsdo dro kbwi yp dro Bywkx Bozelvsm exnob dro mywwkxn yp Zywzoi.";
        int offset = 10;
        encrypt(msg, offset);
        if (!strcmp(msg, expected))
            return 1;

        if (verbose)
            printf("Expected\n %s, but got\n %s\n", expected, msg);
        return 0;
    }
    }

    return 255;
}

#include <stdio.h>
void red() {
    printf("\033[1;31m");
}


void reset() {
    printf("\033[0m");
}

void run_tests(bool verbose)
{

    testsPassed = 0;
    for (unsigned int i = FIRST_TEST; i < NUM_TESTS; i++) {
        unsigned int res =  runTest(i, verbose);
        if(verbose)
            if (!res) {
                red();
                printf("Test %s failed\n", testName(i));
                reset();
            }
        testsPassed += res;
    }
    printf("Problem 4 tests passed %d/%d, grade: %f\n", testsPassed, NUM_TESTS, (float)testsPassed / NUM_TESTS*10);

}
#endif
