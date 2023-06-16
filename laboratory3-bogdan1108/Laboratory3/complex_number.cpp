#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "complex_number.h"

// function to create a complex number
Complex complex_create(float real, float imag) {
    Complex c;
    c.real = real;
    c.imag = imag;
    return c;
}

// function to get the real part of a complex number
float get_real(Complex c) {
    return c.real;
}

// function to get the imag part of a complex number
float get_imag(Complex c) {
    return c.imag;
}

// function to set the real part of a complex number
void set_real(Complex* c, float real) {
    c->real = real;
}

// function to set the imag part of a complex number
void set_imag(Complex* c, float imag) {
    c->imag = imag;
}

// function to create the conjungate of a complex number
Complex complex_conjugate(Complex c) {
    Complex conj;
    conj.real = c.real;
    conj.imag = -c.imag;
    return conj;
}

// function to add two complex numbers
Complex complex_add(Complex c1, Complex c2) {
    Complex sum;
    sum.real = c1.real + c2.real;
    sum.imag = c1.imag + c2.imag;
    return sum;
}

// function to subtract two complex numbers
Complex complex_subtract(Complex c1, Complex c2) {
    Complex diff;
    diff.real = c1.real - c2.real;
    diff.imag = c1.imag - c2.imag;
    return diff;
}

// function to multiply two complex numbers
Complex complex_multiply(Complex c1, Complex c2) {
    Complex prod;
    prod.real = c1.real * c2.real - c1.imag * c2.imag;
    prod.imag = c1.real * c2.imag + c1.imag * c2.real;
    return prod;
}

// function to multiply a complex number with a scalar
void complex_scalar_mult(Complex* c, float scalar) {
    c->real *= scalar;
    c->imag *= scalar;
}

// function to check if two complex numbers are equal
bool complex_equals(Complex c1, Complex c2) {
    return c1.real == c2.real && c1.imag == c2.imag;
}

// function to compute the magnitude of a complex number
float complex_mag(Complex c) {
    return sqrt(c.real * c.real + c.imag * c.imag);
}

// function to compute the phase of a complex number
float complex_phase(Complex c) {
    return atan2(c.imag, c.real);
}

// function to express the complex number in polar form
void complex_to_polar(Complex c, float* mag, float* phase) {
    *mag = complex_mag(c);
    *phase = complex_phase(c);
}

// function to display a complex number
void complex_display(Complex c) {
    if (c.imag >= 0) {
        printf("%f + %fi", c.real, c.imag);
    } else {
        printf("%f - %fi", c.real, -c.imag);
    }
}