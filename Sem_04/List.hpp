
template <class T>
class List
{
private:
	struct Node
	{
		T data;
		Node* next;

		Node(const T& data, Node* next = nullptr) : data(data), next(next) {};
	};

	Node* head = nullptr;
	Node* tail = nullptr;
	size_t size = 0;

	void free();
	void copy(const List& other);
public:
	class Iterator;

	List() = default;
	List(const List& other);
	List& operator=(const List& other);
	~List();

	void pop_front();
	void pop_back();
	void push_back(const T& data);
	void push_front(const T& data);
	bool empty() const;
	size_t getSize() const;

	T& back();
	T& front();
	const T& back() const;
	const T& front() const;
	void insert(const T& data, size_t index);
	void eraseAt(size_t index);
	T& at(size_t index);
	const T& at(size_t index) const;

	template <class U>
	friend List<U>& concat(List<U>& lhs, List<U>& rhs)
	{
		if (lhs.size == 0)
			return rhs;


		if (rhs.size > 0)
		{
			lhs.tail->next = rhs.head;
			lhs.tail = rhs.tail;
			lhs.size += rhs.size;

			rhs.head = nullptr;
			rhs.tail = nullptr;
			rhs.size = 0;
		}

		return lhs;
	}

	Iterator begin()
	{
		return Iterator(head);
	}

	Iterator end()
	{
		return Iterator(nullptr);
	}

	class Iterator
	{
	private:
		Node* ptr;

		bool valid()
		{
			return ptr != nullptr;
		}

		Iterator next()
		{
			if(valid())
				return Iterator(ptr->next);

			return Iterator(ptr);
		}

	public:

		Iterator(Node* ptr) : ptr(ptr) {};

		Iterator& operator++()
		{
			*this = next();
			return *this;
		}

		Iterator operator++(int)
		{
			Iterator result = *this;
			*this = next();

			return result;
		}

		T& operator*()
		{
			return ptr->data;
		}

		bool operator==(const Iterator& other)
		{
			return ptr == other.ptr;
		}

		bool operator!=(const Iterator& other)
		{
			return ptr != other.ptr;
		}

		operator bool() const
		{
			return valid();
		}

	};


};

template<class T>
inline void List<T>::free()
{
	while (!empty())
		pop_front();
}

template<class T>
void List<T>::copy(const List& other)
{
	Node* iter = other.head;

	while (iter != nullptr)
	{
		push_back(iter->data);
		iter = iter->next;
	}
}

template<class T>
inline List<T>::List(const List& other)
{
	copy(other);
}

template<class T>
List<T>& List<T>::operator=(const List& other)
{
	if (this != &other)
	{
		free();
		copy(other);
	}

	return *this;
}

template<class T>
inline List<T>::~List()
{
	free();
}

template<class T>
void List<T>::pop_front()
{
	if (size == 0)
		throw "Empty list";

	if (size == 1)
	{
		delete head;
		head = tail = nullptr;
	}
	else
	{
		Node* toDelete = head;
		head = head->next;
		delete toDelete;
	}

	size--;
}

template<class T>
inline void List<T>::pop_back()
{
	if (size == 0)
		throw "List empty";

	if (size == 1)
	{
		delete head;
		head = tail = nullptr;
	}
	else
	{
		Node* iter = head;

		while (iter->next != tail)
		{
			iter = iter->next;
		}

		delete iter->next;
		iter->next = nullptr;
		tail = iter;
	}

	size--;
}

template<class T>
inline void List<T>::push_back(const T& data)
{
	if (size == 0)
	{
		head = tail = new Node(data);
	}
	else
	{
		tail->next = new Node(data);
		tail = tail->next;
	}

	size++;
}

template<class T>
inline void List<T>::push_front(const T& data)
{
	if (size == 0)
	{
		head = tail = new Node(data);
	}
	else
	{
		Node* newHead = new Node(data, head);
		head = newHead;
	}

	size++;
}

template<class T>
inline bool List<T>::empty() const
{
	return size == 0;
}

template<class T>
inline size_t List<T>::getSize() const
{
	return size;
}

template<class T>
inline T& List<T>::back()
{
	return tail->data;
}

template<class T>
inline T& List<T>::front()
{
	return head->data;
}

template<class T>
inline const T& List<T>::back() const
{
	return tail->data;
}

template<class T>
inline const T& List<T>::front() const
{
	return head->data;
}

template<class T>
inline void List<T>::insert(const T& data, size_t index)
{
	if (size < index)
		throw "Index out of bound";

	if (index == 0)
		push_front(data);
	else if (index == size)
		push_back(data);
	else
	{
		Node* iter = head;

		for (size_t i = 0; i < index - 1; i++)
		{
			iter = iter->next;
		}

		Node* newNode = new Node(data, iter->next);
		iter->next = newNode;
		size++;
	}
}

template<class T>
inline void List<T>::eraseAt(size_t index)
{
	if (index >= size)
		throw "Index out bounds";

	if (index == 0)
		pop_front();
	else if (index == size - 1)
		pop_back();
	else
	{
		Node* iter = head;

		for (size_t i = 0; i < index - 1; i++)
		{
			iter = iter->next;
		}

		Node* toDelete = iter->next;
		iter->next = toDelete->next;
		delete toDelete;
		size--;
	}
}

template<class T>
inline T& List<T>::at(size_t index)
{
	if (index >= size)
		throw "Index out bounds";

	Node* iter = head;

	for (size_t i = 0; i < index; i++)
	{
		iter = iter->next;
	}

	return iter->data;
}

template<class T>
inline const T& List<T>::at(size_t index) const
{
	if (index >= size)
		throw "Index out bounds";

	Node* iter = head;

	for (size_t i = 0; i < index; i++)
	{
		iter = iter->next;
	}

	return iter->data;
}
