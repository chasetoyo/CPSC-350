#include <iostream>
#ifndef GENSTACK_H
#define GENSTACK_H
using namespace std;

template <class T> class GenStack
{
public:
	GenStack(); //constructor
	GenStack(int maxSize); //overloaded constructor
	~GenStack(); //deconstructor

	void push(T d);
	T pop();
	T peek(); //aka top()

	bool isFull();
	bool isEmpty();

	int size;
	int top;

	T *myArray;
};

template <class T> GenStack<T>::GenStack() //default constructor
{
	myArray = new T[128];
	size = 128;
	top = -1;
}

template <class T> GenStack<T>::GenStack(int maxSize)
{
	myArray = new T[maxSize];
	size = maxSize;
	top = -1;
}

template <class T> GenStack<T>::~GenStack()
{
	delete[] myArray;
}

template <class T> void GenStack<T>::push(T d)
{
	//need to check error/boundary check
	if(isFull()) //if stack is full 
	{
		T* tempArray = new T[size*2]; //dynamically allocate new stack 
		for(int i=0;i<size;++i) //copy original stack to temp stack
		{
			tempArray[i] = myArray[i];
		}
		delete[] myArray; //free the memory of the old stack
		myArray = tempArray; //change pointer of old stack to new stack
		size = size*2;  //update size
		myArray[++top] = d;
	}
	else
		myArray[++top] = d;
}

template <class T> T GenStack<T>::pop()
{
	//error checking, make sure its not empty
	try
	{
		if(isEmpty())
			throw "Error. Stack is empty";
		else
			return myArray[top--];
	}
	catch(char const* s)
	{
		cout << s << endl;
	}
}

template <class T> T GenStack<T>::peek()
{
	//error checking, make sure its not empty
	try
	{
		if(isEmpty())
			throw "Error. Stack is empty";
		else
			return myArray[top];
	}
	catch(char const* s)
	{
		cout << s << endl;
	}
}

template <class T> bool GenStack<T>::isFull()
{
	return (top == size -1);
}

template <class T> bool GenStack<T>::isEmpty()
{
	return (top == -1);
}

#endif