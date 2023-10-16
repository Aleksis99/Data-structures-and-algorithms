template <class T>
class Stack
{
private:
	struct Node
	{
		T data;
		Node* next;

		Node(const T& data, Node* next=nullptr) : data(data), next(next) {};
	};

	Node* head;
	size_t size;

	void free();
	void copy(const Stack<T>& other);

public:

	Stack();
	Stack(const Stack<T>& other);
	Stack<T>& operator=(const Stack<T>& other);
	~Stack();

	void pop();
	T top() const;
	void push(const T& data);
	bool empty() const;
	size_t getSize() const;
};

template<class T>
void Stack<T>::free()
{
	while (!this->empty())
	{
		this->pop();
	}
}

template<class T>
void Stack<T>::copy(const Stack<T>& other)
{
	this->size = other.size;

	if (other.empty())
	{
		this->head = nullptr;
		return;
	}

	this->head = new Node(other.head->data);
	Node* thisIter = this->head;
	Node* otherIter = other.head->next;

	while (otherIter != nullptr)
	{
		thisIter->next = new Node(otherIter->data);
		thisIter = thisIter->next;
		otherIter = otherIter->next;
	}
}

template<class T>
Stack<T>::Stack() : head(nullptr), size(0)
{
}

template<class T>
Stack<T>::~Stack()
{
	free();
}

template<class T>
Stack<T>::Stack(const Stack<T>& other)
{
	copy(other);
}

template<class T>
Stack<T>& Stack<T>::operator=(const Stack<T>& other)
{
	if (this != &other)
	{
		free();
		copy(other);
	}

	return *this;
}

template<class T>
bool Stack<T>::empty() const
{
	return this->size == 0;
}

template<class T>
size_t Stack<T>::getSize() const
{
	return this->size;
}

template<class T>
void Stack<T>::pop()
{
	if (empty())
		throw "Empty stack";

	size--;
	Node* temp = head;
	head = head->next;
	delete temp;
}

template<class T>
void Stack<T>::push(const T& data)
{
	size++;
	Node* newNode = new Node(data, head);
	head = newNode;
}

template<class T>
T Stack<T>::top() const
{
	if (empty())
		throw "Stack empty";

	return head->data;
}
