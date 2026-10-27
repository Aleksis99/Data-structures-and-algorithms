#pragma once
#include <cstddef>
#include <stdexcept>
#include <utility>

template <class T>
class List
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
	size_t size = 0;

	void free();
	void copy(const List &other);
	void swap(List &other) noexcept;
	Node *getNode(size_t index) const;

public:
	class Iterator;
	class ConstIterator;

	List() = default;
	List(const List &other);
	List(List &&other) noexcept;
	List &operator=(const List &other);
	List &operator=(List &&other) noexcept;
	~List();

	void pop_front();
	void pop_back();
	void push_back(const T &data);
	void push_front(const T &data);
	bool empty() const;
	size_t getSize() const;

	T &back();
	T &front();
	const T &back() const;
	const T &front() const;
	void insert(const T &data, size_t index);
	void eraseAt(size_t index);
	T &at(size_t index);
	const T &at(size_t index) const;

	// Moves the nodes of second to the end of this list in O(1). second is left empty.
	void concat(List &&second);
	// Copies the elements of second to the end of this list in O(n).
	void concat(const List &second);

	class Iterator
	{
	private:
		Node *ptr;

		Iterator(Node *ptr) : ptr(ptr) {}

		bool valid() const
		{
			return ptr != nullptr;
		}

		void next()
		{
			if (!valid())
				throw std::out_of_range("Invalid iterator");

			ptr = ptr->next;
		}

	public:
		Iterator &operator++()
		{
			next();
			return *this;
		}

		Iterator operator++(int)
		{
			Iterator result = *this;
			next();
			return result;
		}

		T &operator*() const
		{
			return ptr->data;
		}

		T *operator->() const
		{
			return &ptr->data;
		}

		bool operator==(const Iterator &other) const
		{
			return ptr == other.ptr;
		}

		bool operator!=(const Iterator &other) const
		{
			return !(*this == other);
		}

		explicit operator bool() const
		{
			return valid();
		}

		friend class List;
	};

	class ConstIterator
	{
	private:
		const Node *ptr;

		ConstIterator(const Node *ptr) : ptr(ptr) {}

		bool valid() const
		{
			return ptr != nullptr;
		}

		void next()
		{
			if (!valid())
				throw std::out_of_range("Invalid iterator");

			ptr = ptr->next;
		}

	public:
		ConstIterator &operator++()
		{
			next();
			return *this;
		}

		ConstIterator operator++(int)
		{
			ConstIterator result = *this;
			next();
			return result;
		}

		const T &operator*() const
		{
			return ptr->data;
		}

		const T *operator->() const
		{
			return &ptr->data;
		}

		bool operator==(const ConstIterator &other) const
		{
			return ptr == other.ptr;
		}

		bool operator!=(const ConstIterator &other) const
		{
			return !(*this == other);
		}

		explicit operator bool() const
		{
			return valid();
		}

		friend class List;
	};

	Iterator begin()
	{
		return Iterator(head);
	}

	Iterator end()
	{
		return Iterator(nullptr);
	}

	ConstIterator begin() const
	{
		return ConstIterator(head);
	}

	ConstIterator end() const
	{
		return ConstIterator(nullptr);
	}

	ConstIterator cbegin() const
	{
		return ConstIterator(head);
	}

	ConstIterator cend() const
	{
		return ConstIterator(nullptr);
	}
};

template <class T>
void List<T>::free()
{
	while (!empty())
	{
		pop_front();
	}
}

template <class T>
void List<T>::copy(const List &other)
{
	Node *iter = other.head;

	while (iter != nullptr)
	{
		push_back(iter->data);
		iter = iter->next;
	}
}

template <class T>
void List<T>::swap(List &other) noexcept
{
	std::swap(head, other.head);
	std::swap(tail, other.tail);
	std::swap(size, other.size);
}

template <class T>
typename List<T>::Node *List<T>::getNode(size_t index) const
{
	if (index >= size)
		throw std::out_of_range("Index out of bound");

	Node *iter = head;

	for (size_t i = 0; i < index; i++)
	{
		iter = iter->next;
	}

	return iter;
}

template <class T>
List<T>::List(const List &other)
{
	try
	{
		copy(other);
	}
	catch (...)
	{
		free();
		throw;
	}
}

template <class T>
List<T>::List(List &&other) noexcept
{
	swap(other);
}

template <class T>
List<T> &List<T>::operator=(const List &other)
{
	if (this != &other)
	{
		List temp(other);
		swap(temp);
	}

	return *this;
}

template <class T>
List<T> &List<T>::operator=(List &&other) noexcept
{
	if (this != &other)
	{
		free();
		swap(other);
	}

	return *this;
}

template <class T>
List<T>::~List()
{
	free();
}

template <class T>
void List<T>::pop_front()
{
	if (empty())
		throw std::out_of_range("List is empty");

	Node *toDelete = head;
	head = head->next;
	delete toDelete;
	size--;

	if (head == nullptr)
	{
		tail = nullptr;
	}
}

template <class T>
void List<T>::pop_back()
{
	if (empty())
		throw std::out_of_range("List is empty");

	if (size == 1)
	{
		delete head;
		head = tail = nullptr;
		size--;
		return;
	}

	Node *iter = head;

	while (iter->next != tail)
	{
		iter = iter->next;
	}

	delete tail;
	iter->next = nullptr;
	tail = iter;
	size--;
}

template <class T>
void List<T>::push_back(const T &data)
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

	size++;
}

template <class T>
void List<T>::push_front(const T &data)
{
	head = new Node(data, head);
	size++;

	if (tail == nullptr)
	{
		tail = head;
	}
}

template <class T>
bool List<T>::empty() const
{
	return size == 0;
}

template <class T>
size_t List<T>::getSize() const
{
	return size;
}

template <class T>
T &List<T>::back()
{
	if (empty())
		throw std::out_of_range("List is empty");

	return tail->data;
}

template <class T>
T &List<T>::front()
{
	if (empty())
		throw std::out_of_range("List is empty");

	return head->data;
}

template <class T>
const T &List<T>::back() const
{
	if (empty())
		throw std::out_of_range("List is empty");

	return tail->data;
}

template <class T>
const T &List<T>::front() const
{
	if (empty())
		throw std::out_of_range("List is empty");

	return head->data;
}

template <class T>
void List<T>::insert(const T &data, size_t index)
{
	if (index > size)
		throw std::out_of_range("Index out of bound");

	if (index == 0)
	{
		push_front(data);
		return;
	}

	if (index == size)
	{
		push_back(data);
		return;
	}

	Node *prev = getNode(index - 1);
	prev->next = new Node(data, prev->next);
	size++;
}

template <class T>
void List<T>::eraseAt(size_t index)
{
	if (index >= size)
		throw std::out_of_range("Index out of bound");

	if (index == 0)
	{
		pop_front();
		return;
	}

	if (index == size - 1)
	{
		pop_back();
		return;
	}

	Node *prev = getNode(index - 1);
	Node *toDelete = prev->next;
	prev->next = toDelete->next;
	delete toDelete;
	size--;
}

template <class T>
T &List<T>::at(size_t index)
{
	return getNode(index)->data;
}

template <class T>
const T &List<T>::at(size_t index) const
{
	return getNode(index)->data;
}

template <class T>
void List<T>::concat(List &&second)
{
	if (this == &second || second.empty())
		return;

	if (empty())
		head = second.head;
	else
		tail->next = second.head;

	tail = second.tail;
	size += second.size;

	second.head = second.tail = nullptr;
	second.size = 0;
}

template <class T>
void List<T>::concat(const List &second)
{
	size_t count = second.size;
	Node *iter = second.head;

	for (size_t i = 0; i < count; i++)
	{
		push_back(iter->data);
		iter = iter->next;
	}
}
