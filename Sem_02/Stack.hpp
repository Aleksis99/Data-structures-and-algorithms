#pragma once
#include <cstddef>
#include <stdexcept>
#include <utility>

template <class T>
class Stack
{
private:
	struct Node
	{
		T data;
		Node *next;
		Node(const T &data, Node *next = nullptr) : data(data), next(next) {}
	};

	size_t size = 0;
	Node *head = nullptr;

	void free();
	void copy(const Stack<T> &other);
	void swap(Stack<T> &other) noexcept;

public:
	Stack() = default;
	Stack(const Stack<T> &other);
	Stack(Stack<T> &&other) noexcept;
	Stack &operator=(const Stack<T> &other);
	Stack &operator=(Stack<T> &&other) noexcept;
	~Stack();

	const T &top() const;
	void pop();
	size_t getSize() const;
	void push(const T &data);
	bool empty() const;
};

template <class T>
void Stack<T>::copy(const Stack<T> &other)
{
	if (other.empty())
		return;

	this->head = new Node(other.head->data);
	this->size = 1;
	Node *thisIter = this->head;
	Node *otherIter = other.head->next;

	while (otherIter != nullptr)
	{
		thisIter->next = new Node(otherIter->data);
		this->size++;
		otherIter = otherIter->next;
		thisIter = thisIter->next;
	}
}

template <class T>
void Stack<T>::free()
{
	while (!this->empty())
	{
		this->pop();
	}
}

template <class T>
void Stack<T>::swap(Stack<T> &other) noexcept
{
	std::swap(this->head, other.head);
	std::swap(this->size, other.size);
}

template <class T>
Stack<T>::Stack(const Stack<T> &other)
{
	copy(other);
}

template <class T>
Stack<T>::Stack(Stack<T> &&other) noexcept
{
	swap(other);
}

template <class T>
Stack<T> &Stack<T>::operator=(const Stack<T> &other)
{
	if (this != &other)
	{
		free();
		copy(other);
	}

	return *this;
}

template <class T>
Stack<T> &Stack<T>::operator=(Stack<T> &&other) noexcept
{
	if (this != &other)
	{
		free();
		swap(other);
	}

	return *this;
}

template <class T>
Stack<T>::~Stack()
{
	free();
}

template <class T>
const T &Stack<T>::top() const
{
	if (this->empty())
		throw std::out_of_range("Empty stack");

	return head->data;
}

template <class T>
void Stack<T>::pop()
{
	if (this->empty())
		throw std::out_of_range("Empty stack");

	Node *temp = this->head;
	this->head = this->head->next;
	size--;
	delete temp;
}

template <class T>
void Stack<T>::push(const T &data)
{
	Node *newNode = new Node(data, this->head);
	this->head = newNode;
	size++;
}

template <class T>
size_t Stack<T>::getSize() const
{
	return this->size;
}

template <class T>
bool Stack<T>::empty() const
{
	return this->size == 0;
}
