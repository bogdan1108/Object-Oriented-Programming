#pragma once
#include <string>
#include <ostream>
using namespace std;

typedef int ElementType;

class DynamicArray
{
public:
	DynamicArray(int capacity = 100);
	~DynamicArray();
	DynamicArray(const DynamicArray& other);

	DynamicArray& operator=(const DynamicArray& other);

	inline unsigned int getLength() const
	{
		return length;
	}

	inline unsigned int getCapacity() const
	{
		return capacity;
	}


	void append(ElementType v, bool* err = nullptr);

	ElementType popBack();

	ElementType remove_at_index(unsigned int index);

	ElementType& get_at_index(unsigned int index);

	friend ostream& operator<<(ostream& s, const DynamicArray& arr);
	friend bool operator == (const DynamicArray& arr1, const DynamicArray& arr2);
	friend bool operator != (const DynamicArray& arr1, const DynamicArray& arr2);
	void resize(unsigned int newCapacity);


private:

	//static int count;
	unsigned int length;
	unsigned int capacity;
	ElementType* data;
};

