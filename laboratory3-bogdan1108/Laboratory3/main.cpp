#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#include "complex_test.h"
#include "complex_number.h"

int main(int argc, char** argv) {

	run_complex_tests(true);

	// define a variable of type ComplexNumber such that it's stored on the stack
	Complex c1 = complex_create(1.0, 2.0);

	// call complex_mag , complex_phase , to_polar , complex_conjugate , multiply_with_scalar
	printf("Magnitude of c1: %f\n", complex_mag(c1));
	printf("Phase of c1: %f\n", complex_phase(c1));
	float mag, phase;
	mag = complex_mag(c1);
	phase = complex_phase(c1);
	complex_to_polar(c1, &mag, &phase);
	Complex c2 = complex_conjugate(c1);
	complex_display(c2);
	printf("\n");
	complex_scalar_mult(&c1, 2);
	complex_display(c1);
	printf("\n");

	// define a variable of type ComplexNumber such that it's stored on the heap
	Complex* c3 = (Complex*)malloc(sizeof(Complex));
	*c3 = complex_create(3.0, 4.0);
	printf("Magnitude of c3: %f\n", complex_mag(*c3));
	printf("Phase of c3: %f\n", complex_phase(*c3));
	mag = complex_mag(*c3);
	phase = complex_phase(*c3);
	complex_to_polar(*c3, &mag, &phase);
	Complex* c4 = (Complex*)malloc(sizeof(Complex));
	*c4 = complex_conjugate(*c3);
	complex_display(*c4);
	printf("\n");
	complex_scalar_mult(c3, 2);
	complex_display(*c3);
	printf("\n");
	
	return 0;
}