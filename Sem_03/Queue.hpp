#pragma once
#include <cstddef>
#include <stdexcept>
#include <utility>

template <class T>
class Queue
{
private:
	struct Node
	{
		T data;
		Node *next;

		Node(const T &data, Node *next = nullptr) : data(data), next(next) {}
	};

	Node *head = nullptr;
	Node *tail = nullptr;
	size_t count = 0;

	void copy(const Queue<T> &other);
	void free();
	void swap(Queue<T> &other) noexcept;

public:
	Queue() = default;
	Queue(const Queue<T> &other);
	Queue(Queue<T> &&other) noexcept;
	Queue<T> &operator=(const Queue<T> &other);
	Queue<T> &operator=(Queue<T> &&other) noexcept;
	~Queue();

	size_t size() const;
	bool empty() const;
	void push(const T &data);
	void pop();
	T &front();
	const T &front() const;
	T &back();
	const T &back() const;
};

template <class T>
void Queue<T>::copy(const Queue<T> &other)
{
	Node *otherIter = other.head;

	while (otherIter != nullptr)
	{
		push(otherIter->data);
		otherIter = otherIter->next;
	}
}

template <class T>
void Queue<T>::free()
{
	while (!empty())
	{
		pop();
	}
}

template <class T>
void Queue<T>::swap(Queue<T> &other) noexcept
{
	std::swap(head, other.head);
	std::swap(tail, other.tail);
	std::swap(count, other.count);
}

template <class T>
Queue<T>::Queue(const Queue<T> &other)
{
	try
	{
		copy(other);
	}
	catch (...)
	{
		// The destructor is not called if the constructor throws
		free();
		throw;
	}
}

template <class T>
Queue<T>::Queue(Queue<T> &&other) noexcept
{
	swap(other);
}

template <class T>
Queue<T> &Queue<T>::operator=(const Queue<T> &other)
{
	if (this != &other)
	{
		Queue<T> temp(other);
		swap(temp);
	}

	return *this;
}

template <class T>
Queue<T> &Queue<T>::operator=(Queue<T> &&other) noexcept
{
	if (this != &other)
	{
		free();
		swap(other);
	}

	return *this;
}

template <class T>
Queue<T>::~Queue()
{
	free();
}

template <class T>
size_t Queue<T>::size() const
{
	return count;
}

template <class T>
bool Queue<T>::empty() const
{
	return count == 0;
}

template <class T>
void Queue<T>::push(const T &data)
{
	Node *newNode = new Node(data);

	if (empty())
	{
		head = tail = newNode;
	}
	else
	{
		tail->next = newNode;
		tail = newNode;
	}

	count++;
}

template <class T>
void Queue<T>::pop()
{
	if (empty())
	{
		throw std::out_of_range("Empty queue");
	}

	Node *toDelete = head;
	head = head->next;

	if (head == nullptr)
	{
		tail = nullptr;
	}

	count--;
	delete toDelete;
}

template <class T>
T &Queue<T>::front()
{
	if (empty())
	{
		throw std::out_of_range("Empty queue");
	}

	return head->data;
}

template <class T>
const T &Queue<T>::front() const
{
	if (empty())
	{
		throw std::out_of_range("Empty queue");
	}

	return head->data;
}

template <class T>
T &Queue<T>::back()
{
	if (empty())
	{
		throw std::out_of_range("Empty queue");
	}

	return tail->data;
}

template <class T>
const T &Queue<T>::back() const
{
	if (empty())
	{
		throw std::out_of_range("Empty queue");
	}

	return tail->data;
}
