#ifndef MINHEAP_H_
#define MINHEAP_H_

// Defines a MinHeap class using a binary tree

#include <vector>
#include <array>
#include <iostream>


// Defines the MinHeap data structure
// T - Type of the MinHeap.
// T assumes that it has the comparison operators
template <class T>
class MinHeap
{
public:
	// constructor that takes an array (pointer), and the length of the array to use as the heap
	MinHeap(T* heap, unsigned int length);
	// Construct a heap on a vector
	// use of explicit so the compiler prevents an implicit conversion with the constructor
	explicit MinHeap(const std::vector<T>& vector);
	// Default empty constructor to construct am empty heap
	MinHeap();

	// Insert - Inserts value into the heap
	// value - the value to insert
	// Returns - void
	void Insert(T value);

	// Getmin - Gets the min value in the heap
	// Returns - min value in heap (root)
	T GetMin();

	// Search - searches for the an occurance of an element in the heap. Returns as soon as it finds the first one
	// search - the value we are searching for
	// Returns - the index the element was found out, -1 if it was not found
	int Search(T search);

	// Delete - Deletes the first of an element in the heap and heapifies the heap
	// value - the value we are deleting
	// Returns - void
	void Delete(T value);

	// Change - Changes a value to a have a new value (changes all occurences)
	// oldValue - the value we are looking to change
	// newValue - the new value we are changing it too
	// Returns - void
	void Change(T oldValue, T newValue);

	// PrintPostOrder - prints the heap using postorder
	// stream - the ouput stream to print it out to
	// Returns - void
	void PrintPostOrder(std::ostream& stream);

	// Pop - Pops the min value off the heap
	// Returns - void
	void Pop();

	// Size - returns the size of the min heap
	// Returns - size_t
	size_t Size();

private:
	std::vector<T> heap;
	// BubbleDown - with a node is violating the heap rule, switch this node with the minimum child. Recursively called until no longer violating heap rules
	//index - the ndoe index
	// Returns - void
	void BubbleDown(unsigned int index);

	// BubbleUp - Similar to BubbleDown, except only swiches with the parent and recursively goes up
	// index - the nodes index
	// Returns - void
	void BubbleUp(unsigned int index);

	// Actually makes a heap out of the vector of T types
	void Heapify();

	// Recursive driver function to run PrintPostOrder
	//void PrintPostOrder(typename std::vector<T>::const_iterator iter);
	// Recursive driver function to run PrintPostOrder
	void PrintPostOrder(unsigned int node, std::ostream& stream);
};


// Implementation of MinHeap class template
// Default empty constructor
template <class T>
MinHeap<T>::MinHeap()
{
}

// create a heap from an array of T Types with a defined length
template <class T>
MinHeap<T>::MinHeap(T* heap, unsigned length) : heap(heap, heap + length)
{
	Heapify();
}

// Generate a heap based on a vector of T types
template <class T>
MinHeap<T>::MinHeap(const std::vector<T>& vector) : heap(vector)
{
	Heapify();
}

// Insert a new object into the min heap, then keep the heap property
template <class T>
void MinHeap<T>::Insert(T value)
{
	heap.push_back(value);

	BubbleUp(heap.size() - 1);
}

// return the root (smallest) value in the heap
template <class T>
T MinHeap<T>::GetMin()
{
	return heap[0];
}

// search the heap for the value.
// Returns the first occurence of the value in the heap, -1 if it can't find it
template <class T>
int MinHeap<T>::Search(T search)
{
	auto iter = heap.begin();

	while(*iter == search)
	{
		if(*iter == search)
		{
			return iter - heap.begin();
		}
		++iter;
	}

	return -1;
}

// Delete all occurences of this object in the min heap
template <class T>
void MinHeap<T>::Delete(T value)
{
	auto index = Search(value);

	if (index == -1)
		return;

	// still finding occurences of T in the heap
	while(index != -1)
	{
		// swap this element with the last one for easy deletion
		std::iter_swap(heap.begin() + index, heap.end());
		// just pop the last one off for fast deletion
		heap.pop_back();
		// another occurence?
		index = Search(value);
	}

	// heap property more than likely got messed up, restore it
	Heapify();
}

// Changes all occurences of a value to new one
template <class T>
void MinHeap<T>::Change(T oldValue, T newValue)
{
	auto index = Search(oldValue);

	// not in the min heap
	if (index == -1)
		return;

	while(index != -1)
	{
		heap[index] = newValue;
		index = Search(oldValue);
	}

	Heapify();
}

// Prints out the heap using post order to the specified stream
template <class T>
void MinHeap<T>::PrintPostOrder(std::ostream& stream)
{
	PrintPostOrder(0, stream);
}

// pop the root element off the min heap
template <class T>
void MinHeap<T>::Pop()
{
	if (heap.size() == 0)
		return;

	heap[0] = heap[heap.size() - 1];
	heap.pop_back();

	BubbleDown(0);
}

template <class T>
size_t MinHeap<T>::Size()
{
	return heap.size();
}

template <class T>
void MinHeap<T>::BubbleDown(unsigned int index)
{
	// calculate left and right children
	auto left = 2 * index + 1;
	auto right = 2 * index + 2;
	auto minIndex = index;

	// leaf
	if (left >= heap.size())
	{
		return;
	}

	// left child is larger
	if (heap[index] > heap[left])
	{
		minIndex = left;
	}

	// has a right child and right child is larger
	if ((right < heap.size()) && (heap[minIndex] > heap[right]))
	{
		minIndex = right;
	}

	// smallest element is not the root
	if (minIndex != index)
	{
		// need to swap the root with the current index
		std::swap(heap[index], heap[minIndex]);
		BubbleDown(minIndex);
	}
}

template <class T>
void MinHeap<T>::BubbleUp(unsigned int index)
{
	if (index == 0)
	{
		return;
	}

	auto parent = (index - 1) / 2;

	if (heap[parent] > heap[index])
	{
		std::swap(heap[parent], heap[index]);
		BubbleUp(index);
	}
}

// Go over all elements in the vector in reverse order
// for every element bubbledown on this element
// Runs in O(n) complexity
template <class T>
void MinHeap<T>::Heapify()
{
	if (heap.size() == 0)
		return;

	for (int i = (heap.size() / 2) - 1; i >= 0; --i)
	{
		BubbleDown(i);
	}
}

// private helper driver method for printing via postorder traversal
template <class T>
void MinHeap<T>::PrintPostOrder(unsigned int node, std::ostream& stream)
{
	// calculate left and right children
	auto left = 2 * node + 1;
	auto right = 2 * node + 2;

	// has left child
	if (heap.size() > left)
	{
		PrintPostOrder(left, stream);
	}
	// has right child
	if (heap.size() > right)
	{
		PrintPostOrder(right, stream);
	}

	stream << heap[node] << ", ";
}


#endif

