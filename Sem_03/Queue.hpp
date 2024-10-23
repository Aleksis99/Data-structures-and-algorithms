template <class T>
class Queue
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
	void copy(const Queue<T>& other);
	void free();

public:

	Queue() = default;
	Queue(const Queue<T>& other);
	Queue<T>& operator=(const Queue<T>& other);
	~Queue();

	size_t get_size() const;
	bool empty() const;
	void push(const T& data);
	void pop();
	const T& front() const;
	const T& back() const;
};

template<class T>
void Queue<T>::copy(const Queue<T>& other)
{
	Node* otehrIter = other.head;

	while (otehrIter != nullptr)
	{
		this->push(otehrIter->data);
		otehrIter = otehrIter->next;
	}

	//this->size = other.size;
	//if (other.empty())
	//	return;

	//this->head = new Node(other.head->data);
	//Node* thisIter = head;
	//Node* otehrIter = other.head->next;

	//while (otehrIter != nullptr)
	//{
	//	thisIter->next = new Node(otehrIter->data);
	//	thisIter = thisIter->next;
	//	otehrIter = otehrIter->next;
	//}

	//tail = thisIter;
}

template<class T>
void Queue<T>::free()
{
	while (!empty())
	{
		pop();
	}
}

template<class T>
Queue<T>::Queue(const Queue<T>& other)
{
	copy(other);
}

template<class T>
Queue<T>& Queue<T>::operator=(const Queue<T>& other)
{
	if (this != &other)
	{
		free();
		copy(other);
	}

	return *this;
}

template<class T>
Queue<T>::~Queue()
{
	free();
}

template<class T>
size_t Queue<T>::get_size() const
{
	return size;
}

template<class T>
bool Queue<T>::empty() const
{
	return size == 0;
}

template<class T>
void Queue<T>::push(const T& data)
{
	if (empty())
	{
		head = tail = new Node(data);
	}
	else
	{
		Node* newNode = new Node(data);
	
		tail->next = newNode;
		tail = newNode;
	}

	size++;
}

template<class T>
void Queue<T>::pop()
{
	if (empty())
	{
		throw "Empty Queue";
	}

	Node* toDelete = head;
	head = head->next;

	if (head == nullptr)
	{
		tail = nullptr;
	}

	size--;
	delete toDelete;
}

template<class T>
const T& Queue<T>::front() const
{
	if (empty())
	{
		throw "Empty Queue";
	}

	return head->data;
}

template<class T>
const T& Queue<T>::back() const
{
	if (empty())
	{
		throw "Empty Queue";
	}

	return tail->data;
}
