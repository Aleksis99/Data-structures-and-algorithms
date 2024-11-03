
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

	void concat(List& second);
	void concat(const List& second);

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

		void next()
		{
			if (!valid())
				throw "Invalid iterator";

			ptr = ptr->next;
		}

	public:

		Iterator(Node* ptr) : ptr(ptr) {};

		Iterator& operator++()
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
void List<T>::free()
{
	while (!empty())
	{
		pop_front();
	}
}

template<class T>
void List<T>::copy(const List& other)
{
	if (other.empty())
	{
		head = tail = nullptr;
		size = 0;
		return;
	}

	head = new Node(other.head->data);
	Node* thisIter = head;
	Node* otherIter = other.head->next;
	while (otherIter != nullptr)
	{
		thisIter->next = new Node(otherIter->data);
		thisIter = thisIter->next;
		otherIter = otherIter->next;
	}

	tail = thisIter;
	size = other.size;

	//node* iter = other.head;

	//while (iter != nullptr)
	//{
	//	push_back(iter->data);
	//}
}

template<class T>
List<T>::List(const List& other)
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
List<T>::~List()
{
	free();
}

template<class T>
void List<T>::pop_front()
{
	if (empty())
		throw "List is empty";

	Node* toDelete = head;
	head = head->next;
	delete toDelete;
	size--;

	if (head == nullptr)
	{
		tail = nullptr;
	}
}

template<class T>
void List<T>::pop_back()
{
	if (empty())
		throw "List is empty";

	if (size == 1)
	{
		delete head;
		head = tail = nullptr;
		size--;
		return;
	}

	Node* iter = head;

	for (size_t i = 0; i < size - 1; i++)
	{
		iter = iter->next;
	}

	delete iter->next;
	iter->next = nullptr;
	size--;
	tail = iter;
}

template<class T>
void List<T>::push_back(const T& data)
{
	if (empty())
	{
		head = tail = new Node(data, nullptr);
		size++;
		return;
	}

	tail->next = new Node(data, nullptr);
	tail = tail->next;
	size++;
}

template<class T>
void List<T>::push_front(const T& data)
{
	Node* newNode = new Node(data, head);
	head = newNode;
	size++;

	if (tail == nullptr)
	{
		tail = head;
	}
}

template<class T>
bool List<T>::empty() const
{
	return size == 0;
}

template<class T>
size_t List<T>::getSize() const
{
	return size;
}

template<class T>
T& List<T>::back()
{
	return tail->data;
}

template<class T>
T& List<T>::front()
{
	return head->data;
}

template<class T>
const T& List<T>::back() const
{
	return tail->data;
}

template<class T>
const T& List<T>::front() const
{
	return head->data;
}

template<class T>
void List<T>::insert(const T& data, size_t index)
{
	if (index > size)
		throw "Index out of bound";

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

	Node* iter = head;

	for (size_t i = 0; i < index - 1; i++)
	{
		iter = iter->next;
	}

	Node* newNode = new Node(data, iter->next);
	iter->next = newNode;
	size++;
}

template<class T>
void List<T>::eraseAt(size_t index)
{
	if (index >= size)
		throw "Index out of bound";

	if (index == 0)
	{
		pop_front();
		return;
	}

	if (index == size-1)
	{
		pop_back();
		return;
	}

	Node* iter = head;

	for (size_t i = 0; i < index - 1; i++)
	{
		iter = iter->next;
	}

	Node* toDelete = iter->next;
	iter->next = iter->next->next;
	delete toDelete;
	size--;
}

template<class T>
T& List<T>::at(size_t index)
{
	if (index >= size)
		throw "Index out of bound";

	Node* iter = head;

	for (size_t i = 0; i < index; i++)
	{
		iter = iter->next;
	}

	return iter->data;
}

template<class T>
const T& List<T>::at(size_t index) const
{
	if (index >= size)
		throw "Index out of bound";

	Node* iter = head;

	for (size_t i = 0; i < index; i++)
	{
		iter = iter->next;
	}

	return iter->data;
}

template<class T>
void List<T>::concat(List& second)
{
	if (second.empty())
		return;

	if (this->empty())
	{
		head = second.head;
		tail = second.tail;
		size = second.size;
		second.head = nullptr;
		second.tail = nullptr;
		second.size = 0;
		return;
	}

	tail->next = second.head;
	tail = second.tail;
	size += second.size;
	second.head = nullptr;
	second.tail = nullptr;
	second.size = 0;
}

template<class T>
void List<T>::concat(const List& second)
{
	Node* iter = second.head;

	while (iter!= nullptr)
	{
		this->push_back(iter->data);
		iter = iter->next;
	}
}

