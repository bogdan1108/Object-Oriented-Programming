#include "complex_test.h"
#include <csetjmp>
#include <csignal>
#include <cstdbool>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <string>
#include <cmath>

#define RED "\033[0;31m"
#define CYAN "\033[0;36m"
#define GREEN "\033[0;32m"
#define NC "\033[0m"

#define FIRST_TEST Test_Create
#define MAXSCORE 54
#define CHARITY 0

bool cmpf(float A, float B, float epsilon = 0.005f)
{
	return (fabs(A - B) < epsilon);
}


static uint8_t testsPassed;
static volatile sig_atomic_t testStatus;
static uint8_t disable_exit_handler;
jmp_buf test_crash;


typedef enum {
	Test_Create,
	Test_Add,
	Test_Subtract,
	Test_ScalarMult,
	Test_Mult,
	Test_Conjugate,
	Test_Phase,
	Test_Magnitude,
	Test_Getters_Setters,
	Test_Equals,
	Num_Tests
}TestCases;


void segfault_handler(int signal) {
	testStatus = 255;
	longjmp(test_crash, 1);
}

void exit_attempt_handler(void) {
	if (disable_exit_handler)
		return; // allow this to be disabled
	testStatus = 255;
	longjmp(test_crash, 2);
}

void abrupt_termination_handler(int signal) {
	testStatus = 255;
	longjmp(test_crash, 3);
}

std::string testName(int test);
int run_test(int test);


std::string testName(int test) {
	if (test == Test_Create)
		return "Test_Create";
	if (test == Test_Add)
		return "Test_Add";
	if (test == Test_Subtract)
		return "Test_Subtract";
	if (test == Test_ScalarMult)
		return "Test_ScalarMult";
	if (test == Test_Mult)
		return "Test_Mult";
	if (test == Test_Phase)
		return "Test_Phase";
	if (test == Test_Magnitude)
		return "Test_Magnitude";
	if (test == Test_Conjugate)
		return "Test_Conjugate";
	if (test == Test_Getters_Setters)
		return "Test_Getters_Setters";
	if (test == Test_Equals)
		return "Test_Equals";

	return "";
}

int run_test(int test) {
	switch (test)
	{
	case Test_Create:
	{
		{
			Complex c = complex_create(0, 0);
			if (get_real(c) != 0 || get_imag(c) != 0)
				return 1;
		}

		{
			Complex c = complex_create(100, 1000);
			if (get_real(c) != 100 || get_imag(c) != 1000)
				return 2;
		}

		return 0;

	}

	case Test_Conjugate:
	{
		{
			Complex c = complex_create(0, 0);
			Complex cc = complex_conjugate(c);
			if (get_real(cc) != 0 || get_imag(cc) != 0)
				return 1;
		}

		{
			Complex c = complex_create(10, 10);
			Complex cc = complex_conjugate(c);
			if (get_real(c) != get_real(cc) || get_imag(c) != -get_imag(cc))
				return 2;
		}

		return 0;
	}

	case Test_Add:
	{
		{
			Complex c1 = complex_create(0, 0);
			Complex c2 = complex_create(2, 2);
			Complex sum = complex_add(c1, c2);
			if (get_real(sum) != get_real(c2) || get_imag(sum) != get_imag(c2))
				return 1;
		}

		{
			Complex c1 = complex_create(100, -10);
			Complex c2 = complex_create(-100, 10);
			Complex sum = complex_add(c1, c2);
			if (get_real(sum) != 0 || get_imag(sum) != 0)
				return 2;
		}

		return 0;

	}

	case Test_Subtract: {
		{
			Complex c1 = complex_create(0, 0);
			Complex c2 = complex_create(2, 2);
			Complex diff = complex_subtract(c1, c2);
			if (get_real(diff) != -get_real(c2) || get_imag(diff) != -get_imag(c2))
				return 1;
		}

		{
			Complex c1 = complex_create(100, -10);
			Complex c2 = complex_create(-100, 10);
			Complex diff = complex_subtract(c1, c2);
			if (get_real(diff) != 200 || get_imag(diff) != -20)
				return 2;
		}

		{
			Complex c1 = complex_create(100, -10);
			Complex diff = complex_subtract(c1, c1);
			if (get_real(diff) != 0 || get_imag(diff) != 0)
				return 3;
		}

		return 0;
	}

	case Test_ScalarMult: {
		{
			Complex c1 = complex_create(10, 0);
			complex_scalar_mult(&c1, 0);
			if (get_real(c1) != 0 || get_imag(c1) != 0)
				return 1;
		}

		{
			Complex c1 = complex_create(100, -10);
			complex_scalar_mult(&c1, 2);

			if (get_real(c1) != 200 || get_imag(c1) != -20)
				return 2;
		}

		{
			Complex c1 = complex_create(100, -10);
			complex_scalar_mult(&c1, -2);

			if (get_real(c1) != -200 || get_imag(c1) != 20)
				return 3;
		}
		return 0;
	}

	case Test_Mult: {
		{
			Complex c1 = complex_create(10, 30);
			Complex c2 = complex_create(30, 40);
			Complex sum = complex_multiply(c1, c2);
			if (get_real(sum) != -900 || get_imag(sum) != 1300)
				return 1;
		}

		{
			Complex c1 = complex_create(0, 30);
			Complex c2 = complex_create(300, 40);
			Complex sum = complex_multiply(c1, c2);
			if (get_real(sum) != -1200 || get_imag(sum) != 9000)
				return 2;
		}

		{
			Complex c1 = complex_create(-100, 3);
			Complex c2 = complex_create(7, -40);
			Complex sum = complex_multiply(c1, c2);

			if (get_real(sum) != -580 || get_imag(sum) != 4021)
				return 3;
		}

		{
			Complex c1 = complex_create(-8, -3);
			Complex c2 = complex_create(-7, -4);
			Complex sum = complex_multiply(c1, c2);

			if (get_real(sum) != 44 || get_imag(sum) != 53)
				return 4;
		}

		{
			Complex c1 = complex_create(-8, -3);
			Complex c2 = complex_create(0, 0);
			Complex sum = complex_multiply(c1, c2);

			if (get_real(sum) != 0 || get_imag(sum) != 0)
				return 5;
		}
		return 0;
	}

	case Test_Equals: {
		{
			Complex c1 = complex_create(0, 100);
			Complex c2 = complex_create(0, 100);


			if (!complex_equals(c1, c2))
				return 1;
		}

		{
			Complex c1 = complex_create(-10, 100);
			Complex c2 = complex_create(100, -10);


			if (complex_equals(c1, c2))
				return 2;
		}

		return 0;
	}

	case Test_Phase: {

		{
			Complex c = complex_create(-10, -10);
			if (!cmpf(complex_phase(c), -2.35619))
				return 1;
		}

		{
			Complex c = complex_create(10, 100);
			if (!cmpf(complex_phase(c), 1.47113))
				return 2;
		}

		{
			Complex c = complex_create(-7, 7);
			if (!cmpf(complex_phase(c), 2.35619))
				return 3;
		}

		{
			Complex c = complex_create(1, -1);
			if (!cmpf(complex_phase(c), -0.785398))
				return 4;
			float r;
			float theta;

			complex_to_polar(c, &r, &theta);
			if (!cmpf(theta, -0.785398))
				return 4;
		}

		{
			Complex c = complex_create(0, 0);
			if (!cmpf(complex_phase(c), 0))
				return 5;

			float r;
			float theta;

			complex_to_polar(c, &r, &theta);
			if (!cmpf(theta, 0))
				return 6;
		}

		return 0;
	}

	case Test_Getters_Setters: {
		Complex c = complex_create(0, 0);
		set_real(&c, 4);
		if (!get_real(c) == 4)
			return 1;
		set_real(&c, -4);
		if (!get_real(c) == -4)
			return 2;

		set_imag(&c, 4);
		if (!(get_imag(c) == 4 && get_real(c) == -4))
			return 3;
		set_imag(&c, -40);
		if (!(get_imag(c) == -40 && get_real(c) == -4))
			return 4;
		return 0;
	}


	case Test_Magnitude: {

		{
			Complex c = complex_create(-10, -10);
			if (!cmpf(complex_mag(c), 14.1421))
				return 1;
		}

		{
			Complex c = complex_create(10, 100);
			if (!cmpf(complex_mag(c), 100.499))
				return 2;
		}

		{
			Complex c = complex_create(7, 7);
			float r;
			float theta;

			complex_to_polar(c, &r, &theta);

			if (!cmpf(r, 9.8995))
				return 3;

			if (!cmpf(complex_mag(c), 9.8995))
				return 4;
		}


		{
			Complex c = complex_create(0, 0);
			if (!cmpf(complex_mag(c), 0))
				return 5;
		}
		return 0;
	}

	default:
		break;
	}
	return 255;
}

void run_complex_tests(bool verbose) {
	testsPassed = 0;
	disable_exit_handler = 0;
	atexit(exit_attempt_handler);
	signal(SIGSEGV, segfault_handler);
	signal(SIGTERM, abrupt_termination_handler); // dangerous
	//signal(SIGINT, abrupt_termination_handler);
	//signal(SIGFPE, abrupt_termination_handler);
	//signal(SIGABRT, abrupt_termination_handler);
	for (uint8_t i = FIRST_TEST; i < Num_Tests; i++) {

		uint8_t fail_type;
		try {

			testStatus = run_test(i);
			fail_type = setjmp(test_crash);
		}
		catch (...) {
			testStatus = 255;
			fail_type = 3;
		}
		if (true) { // it's verbose mode
			cout << "Test " + testName(i) + ": "
				<< (testStatus == 0 ? GREEN "PASSED" NC : RED "FAILED" NC);
			if (testStatus == 255) {
				cout << ": due to a " RED << (fail_type == 1 ? "segfault" : (fail_type == 2 ? "program exit" : (fail_type == 3 ? "exception being thrown" : "program interruption"))) << NC << endl;
				cout << "\nWARNING: Program will now stop running tests\n" << endl;
				break;
			}
			else if (testStatus != 0) {
				cout << ": test " CYAN << testStatus << NC << endl;
			}
			else {
				cout << endl;
			}
		}
		if (testStatus == 0) {
			testsPassed++;
		}
	}

	disable_exit_handler = 1;

	short totalScore = testsPassed * 3;
	short maxScore = Num_Tests * 3;
	if (verbose) {
		if (testStatus != 255)
			cout << "\nYou passed " << unsigned(testsPassed) << " out of " << Num_Tests << " tests" << endl;
		else if (testStatus == 255) {
			totalScore = CHARITY;
			cout << RED "Receiving charity points because your program crashes" NC << endl;
		}
		cout << "You will receive " << totalScore << " out of " << maxScore << " possible points on the complex numbers test\n" << endl;
	}
	else {
		if (testStatus == 255)
			totalScore = CHARITY;
		cout << totalScore << endl;
	}
}
