#include <iostream>
using namespace std;

// toggle (0 or 1) this to enable/disable tests
#define ENABLE_TESTS 0

#define RED "\033[0;31m"
#define CYAN "\033[0;36m"
#define GREEN "\033[0;32m"
#define NC "\033[0m"

#if ENABLE_TESTS == 0
void run_bigint_tests(bool verbose);
#endif

