#pragma once
#include<string>
#include<iostream>
#include "DynamicArray.h"
class BigInteger{

public:
	BigInteger();
	BigInteger(std::string s);

	~BigInteger();
	BigInteger(const BigInteger& other);
	

	BigInteger& operator = (const BigInteger& other);

	int sgn() const;
	void negate();
	void setLength(int l) 
	{
		length = l;
	}

	BigInteger& operator ++ ();
	BigInteger operator ++ (int t);

	friend std::ostream& operator << (std::ostream& stream, BigInteger N);
	friend bool operator == (const BigInteger& A, const BigInteger& B);
	friend bool operator != (const BigInteger& A, const BigInteger& B);
	friend bool operator < (const BigInteger& A, const BigInteger& B);
	friend bool operator <= (const BigInteger& A, const BigInteger& B);
	friend bool operator > (const BigInteger& A, const BigInteger& B);
	friend bool operator >= (const BigInteger& A, const BigInteger& B);

	friend BigInteger operator + (const BigInteger& A, const BigInteger& B);
	BigInteger& operator += (const BigInteger& other);


	friend BigInteger operator - (const BigInteger& A, const BigInteger& B);
	BigInteger& operator -= (const BigInteger& other);

private:
	
	int sign;
	int length;
	int *digits;

	BigInteger(int max_length, BigInteger A);

	BigInteger add(const BigInteger& N) const;
	BigInteger sub(const BigInteger& N) const;
	int compare(const BigInteger& N) const;

	std::string to_string();

};
