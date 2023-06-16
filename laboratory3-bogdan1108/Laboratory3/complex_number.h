#pragma once
#include <string>
#include <fstream>

class Complex {
public:
	//Default constructor
	Complex();

	//Constructor that initializes a complex number with the real and imaginary parts 
	Complex(float real_part, float imag_part);

	//Getters for the real and imaginary part of the number
	float getReal() const;
	float getImag() const;

	//Setter for the real and imaginary part of the number
	void setReal(float r);
	void setImag(float i);

	//Default Operations
	Complex conjugate() const;
	Complex add(Complex a) const;
	Complex subtract(Complex c) const;
	Complex multiply(Complex c) const;
	Complex division(Complex c) const;

	//Complex Operations
	void multiply(float s);
	bool equals(Complex other) const;
	float magnitude();
	float phase();
	void toPolar(float* r, float* theta);

	//Complex to String
	std::string toString() const;

	//Overloaders for equal and not equal operators
	bool operator == (const Complex& c) const;
	bool operator != (const Complex& c) const;
	
	//Overloaders for common operators
	friend Complex operator + (const Complex& c1, const Complex& c2);
	Complex operator - (const Complex& c) const;
	Complex operator * (const Complex& c) const;
	Complex operator / (const Complex& c) const;

	//Overloaders for stream insertion and extraction operators
	friend std::istream& operator >> (std::istream& in, Complex& c);
	friend std::ostream& operator << (std::ostream& out, const Complex& c);

private:
	float real;
	float imag;

};











