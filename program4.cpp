/*
* Name: Chad Smith
* Assignment: Program 4 - Min Heaps
* Due Date: November 14, 2015
*/
#include <iostream>
#include <fstream>

#include "Helpers.h"
#include "MinHeap.h"

template <class T>
void RunOperation(char operation, const std::vector<std::string>& arguments, MinHeap<T>& heap, std::ostream& file);

int main(int argc, char** argv)
{
	std::vector<int> heapVector;
	std::vector<std::string> commandVector;
	BuildVector(commandVector, std::cin);
	heapVector.reserve(500);
	MinHeap<int> heap(heapVector);

	std::ofstream file;
	file.open("output.txt");
	std::vector<std::string>::iterator iter;
	for (iter = commandVector.begin(); iter != commandVector.end(); ++iter)
	{
		// split on the space to get the operation and command
		auto command = SplitString(*iter, ' ');
		auto operation = (*command.begin())[0];
		RunOperation(operation, command, heap, std::cout);
	}
	file.close();

	return 0;
}

// Runs the specified operation on the given heap with the arguments
template<class T> 
void RunOperation(char operation, const std::vector<std::string>& arguments,  MinHeap<T>& heap, std::ostream& file)
{
	if(operation == 'I')
	{
		auto value = ToInt(arguments[1]);
		heap.Insert(value);
	}
	else if(operation == 'D')
	{
		auto value = ToInt(arguments[1]);
		heap.Delete(value);
	}
	else if(operation == 'C')
	{
		auto oldValue = ToInt(arguments[1]);
		auto newValue = ToInt(arguments[2]);
		heap.Change(oldValue, newValue);
	}
	else if(operation == 'P')
	{
		heap.PrintPostOrder(file);
		file << std::endl;
	}

}