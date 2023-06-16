#include "BigInteger.h"

#include <cctype> // for isdigit
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <sstream>
#include <vector>
#include <string>
#include <cmath>
#include <cstring>

using namespace std;

BigInteger::BigInteger()
{
	length = 100;
	digits = new int[length]();
	sign = 0;
}

BigInteger::BigInteger(std::string s)
{
	int existence_sign = 1;
	if (s[0] == '-')
	{
		existence_sign = -1;
	}
	else if (s[0] == '0' && s[1] == '0')
	{
		existence_sign = 0;
	}
	else if (s[0] == '+')
	{
		existence_sign = 1;
	}
	length = size(s);
	digits = new int[length + 1]();
	if (existence_sign == -1 || existence_sign == 0 || s[0] == '+')
	{
		for (int i = 1, j = 0; i < length; i++, j++)
		{
			digits[j] = s[i] - '0';
		}
		length -= 1;
	}
	else
	{
		for (int i = 0; i < length; i++)
		{
			digits[i] = s[i] - '0';
		}
	}
	if(s == "0")
	{
		existence_sign = 0;
	}
	this->sign = existence_sign;
}

BigInteger::~BigInteger()
{
	delete[] digits;
}


BigInteger& BigInteger::operator = (const BigInteger& other) {

	if (this != &other)
	{
		length = other.length;
		sign = other.sign;

		delete[] this->digits;
		digits = new int[length]();
		for (int i = 0; i < length; i++)
			digits[i] = other.digits[i];
	}
	return *this;
}

BigInteger::BigInteger(const BigInteger& other)
{
	sign = other.sign;
	length = other.length;
	digits = new int[length]();

	for (int i = 0; i < length; i++)
		digits[i] = other.digits[i];
}

void BigInteger::negate()
{
	this->digits[0] = this->digits[0] * (-1);
	this->sign = this->sign * (-1);
}

int BigInteger::sgn() const
{
	return this->sign;
}

bool operator == (const BigInteger& A, const BigInteger& B)
{
	long check_equal = 0;
	for (long i = 0; i < A.length; i++)
	{
		if (A.digits[i] == B.digits[i])
		{
			check_equal += 1;
		}
	}

	if (check_equal == A.length && A.sign == B.sign)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

bool operator != (const BigInteger& A, const BigInteger& B)
{
	return !(A == B);
}

int BigInteger::compare(const BigInteger& N) const
{
	int check_stacked = 0, check_new = 0;
	if (this->sign > N.sign)
	{
		return 1;
	}
	else if (this->sign < N.sign)
	{
		return -1;
	}

	if (this->sign == N.sign == -1)
	{
		if (this->length > N.length)
		{
			return -1;
		}
		else if (this->length < N.length)
		{
			return 1;
		}
	}

	if (this->length > N.length)
	{
		return 1;
	}
	else if (this->length < N.length)
	{
		return -1;
	}
	else if (this->length == N.length)
	{
		for (int i = 0; i < this->length; i++)
		{
			if (this->digits[i] > N.digits[i])
			{
				check_stacked = 1;
			}
			else if (this->digits[i] < N.digits[i])
			{
				check_new = 1;
			}

			if (check_stacked == 1)
			{
				return 1;
			}
			else if (check_new == 1)
			{
				return -1;
			}
		}
	}
	return 0;
}

bool operator < (const BigInteger& A, const BigInteger& B)
{
	if (A.compare(B) == -1)
		return 1;
	else
		return 0;
}
bool operator > (const BigInteger& A, const BigInteger& B)
{
	if (A.compare(B) == 1)
		return 1;
	else
		return 0;
}
bool operator >= (const BigInteger& A, const BigInteger& B)
{
	if (A.compare(B) == 1 || (A == B) == 1)
		return 1;
	else
		return 0;
}
bool operator <= (const BigInteger& A, const BigInteger& B)
{
	if (A.compare(B) == -1 || (A == B) == 1)
		return 1;
	else
		return 0;
}

BigInteger BigInteger::add(const BigInteger& N) const
{
	int FS = this->sign, SS = N.sign, FL = this->length, SL = N.length;
	BigInteger adder, helper;
	helper = *this;
	adder = *this;
	helper.sign = N.sign;
	int HS = helper.sign;
	int HL = helper.length;
	delete[] helper.digits;
	delete[] adder.digits;
	adder.digits = new int[FL + 1]();
	adder.length = FL + 1;
	helper.digits = new int[FL]();
	helper.length = FL;

	for (int i = FL - 1, j = SL - 1; j >= 0; j--, i--)
		helper.digits[i] = N.digits[j];
	helper.sign = N.sign;
	if (FS == HS)
	{
		for (int i = FL - 1; i >= 0; i--)
		{
			adder.digits[i + 1] += helper.digits[i] + this->digits[i];
			if (adder.digits[i + 1] >= 10)
			{
				adder.digits[i + 1] -= 10;
				adder.digits[i] += 1;
			}
		}
	}
	else if (FS != HS)
	{
		if (this->digits[0] > N.digits[0])
		{
			adder.sign = this->sign;
			for (int i = FL - 1; i >= 0; i--)
			{
				adder.digits[i + 1] = this->digits[i] - helper.digits[i];
				if (adder.digits[i + 1] < 0)
				{
					adder.digits[i + 1] = abs(this->digits[i] - helper.digits[i]);
					adder.digits[i] -= 1;
				}
			}
		}
		else if (this->digits[0] < N.digits[0])
		{
			adder.sign = N.sign;
			for (int i = SL - 1; i >= 0; i--)
			{
				adder.digits[i] = helper.digits[i] - this->digits[i];
				if (adder.digits[i] < 0)
				{					
					adder.digits[i ] = abs(helper.digits[i] - this->digits[i]);
					adder.digits[i - 1] -= 1;
				}
			}
		}

		
	}


	if (adder.digits[0] == 0)
	{
		int swapper = 0, i = 0;
		while (adder.digits[i] == 0)
		{
			swapper++;
			i++;
		}
		if (swapper == adder.length)
		{
			delete[] adder.digits;
			adder.digits = new int[1]();
			adder.length = 1;
			adder.sign = 0;
		}
		else
		{
			for (int i = swapper; i < adder.length; i++)
			{
				swap(adder.digits[i], adder.digits[i - swapper]);
			}
			int vec[100];
			for (int i = 0; i < FL; i++)
			{
				vec[i] = adder.digits[i];
			}
			delete[] adder.digits;
			adder.digits = new int[FL]();
			adder.length = FL;
			for (int i = 0; i < FL; i++)
			{
				adder.digits[i] = vec[i];
			}
		}
	}
	return adder;

	
	
}

BigInteger operator + (const BigInteger& A, const BigInteger& B)
{
	BigInteger C;
	C = A.add(B);
	return C;
}

BigInteger& BigInteger::operator+=(const BigInteger& other)
{
	*this = *this + other;
	return *this;
}

BigInteger BigInteger::sub(const BigInteger& N) const
{
	int FS = this->sign  , SS = N.sign * (-1), FL = this->length, SL = N.length;
	BigInteger adder, helper;
	if (FL >= SL)
	{
		helper = *this;
		adder = *this;
		helper.sign = SS;
		int HS = helper.sign;
		int HL = helper.length;
		delete[] helper.digits;
		delete[] adder.digits;
		adder.digits = new int[FL + 1]();
		adder.length = FL + 1;
		helper.digits = new int[FL]();
		helper.length = FL;

		for (int i = FL - 1, j = SL - 1; j >= 0; j--, i--)
			helper.digits[i] = N.digits[j];
		helper.sign = SS;
		if (FS == HS)
		{
			for (int i = FL - 1; i >= 0; i--)
			{
				adder.digits[i + 1] += helper.digits[i] + this->digits[i];
				if (adder.digits[i + 1] >= 10)
				{
					adder.digits[i + 1] -= 10;
					adder.digits[i] += 1;
				}
			}
		}
		else if (FS != HS)
		{
			if (this->digits[0] > N.digits[0])
				adder.sign = this->sign;
			else
				adder.sign = SS;

			for (int i = FL - 1; i >= 0; i--)
			{
				adder.digits[i + 1] += this->digits[i] - helper.digits[i];
				if (adder.digits[i + 1] < 0)
				{
					adder.digits[i + 1] += 10;
					adder.digits[i] -= 1;
				}
			}
		}
		if (adder.digits[0] == 0)
		{
			int swapper = 0, i = 0;
			while (adder.digits[i] == 0)
			{
				swapper++;
				i++;
			}
			if (swapper == adder.length)
			{
				delete[] adder.digits;
				adder.digits = new int[1]();
				adder.length = 1;
				adder.sign = 0;
			}
			else
			{
				for (int i = swapper; i < adder.length; i++)
				{
					swap(adder.digits[i], adder.digits[i - swapper]);
				}
				int vec[100];
				for (int i = 0; i < FL; i++)
				{
					vec[i] = adder.digits[i];
				}
				delete[] adder.digits;
				adder.digits = new int[FL]();
				adder.length = FL;
				for (int i = 0; i < FL; i++)
				{
					adder.digits[i] = vec[i];
				}
			}
		}
	}
	return adder;
}

BigInteger operator - (const BigInteger& A, const BigInteger& B)
{
	return A.sub(B);
}

BigInteger& BigInteger::operator-=(const BigInteger& other)
{
	*this = *this - other;
	return *this;
}

string BigInteger::to_string()
{
	string ns;
	ostringstream str;
	if (this->sign == -1)
	{
		str << '-';
	}
	for (int i = 0; i < this->length; i++)
	{
		str << this->digits[i];
	}
	return str.str();
}

ostream& operator << (ostream& stream, BigInteger N) {
	stream << N.to_string();
	return stream;
}

BigInteger& BigInteger::operator++()
{
	BigInteger X("1");
	*this = *this + X;
	return *this;
}

BigInteger BigInteger::operator++(int t)
{
	BigInteger aux;
	aux = *this;
	++(*this);
	return aux;
}