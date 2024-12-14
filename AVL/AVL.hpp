#include <stack>

template <class T>
class AVL
{
public:
	class Iterator;

private:

	struct Node
	{
		T data;
		Node* left;
		Node* right;
		int height;

		Node(const T& data, Node* left = nullptr, Node* right = nullptr, int height = 1) :
			data(data), left(left), right(right), height(height) {};
	};

	Node* root = nullptr;

	void copy(const AVL& other);
	void free();

	void free(Node* root);
	Node* copy(Node* root);

	bool contains(const Node* root, const T& data) const;
	Node* insert(Node* root, const T& data);
	Node* remove(Node* root, const T& data);
	T getMin(const Node* root) const;
	T getMax(const Node* root) const;

	int height(const Node* root) const;
	int balanceFactor(const Node* root) const;

	Node* LRotation(Node* root) const;
	Node* RRotation(Node* root) const;
	Node* LRRotation(Node* root) const;
	Node* RLRotation(Node* root) const;
	Node* balance(Node* root) const;
	Iterator find(const T& data, Node* root, std::stack<Node*>& s)
	{
		if (root == nullptr)
			return Iterator();

		if (root->data < data)
		{
			return find(data, root->right, s);
		}

		if (root->data == data)
		{
			s.push(root);

			return Iterator(s);
		}

		s.push(root);

		return find(data, root->left, s);

	}

public:

	AVL() = default;
	AVL(const AVL& other);
	AVL& operator=(const AVL& other);
	~AVL();

	bool contains(const T& data) const;
	void insert(const T& data);
	void remove(const T& data);
	int height() const;

	Iterator begin() const 
	{
		return Iterator(root);
	}
	Iterator end() const
	{
		return Iterator();
	}


	Iterator find(const T& data)
	{
		std::stack<Node*> s;

		return find(data, root, s);
	}

	class Iterator
	{
	private:
		std::stack<Node*> s;

		bool valid()
		{
			return !s.empty();
		}

		void pushLeft(Node* root)
		{
			if (root == nullptr)
				return;

			while (root != nullptr)
			{
				s.push(root);
				root = root->left;
			}
		}

		T next()
		{
			Node* temp = s.top();
			s.pop();
			pushLeft(temp->right);

			return temp->data;
		}

	public:

		Iterator() = default;
		Iterator(Node* root)
		{
			pushLeft(root);
		}
		Iterator(std::stack<Node*> s) : s(s) {};

		T& operator*() 
		{
			if (valid())
			{
				return s.top()->data;
			}

			throw "Invalid iterator";
		}

		T operator++()
		{
			return next();
		}

		operator bool()
		{
			return valid();
		}

	};

};

template<class T>
void AVL<T>::copy(const AVL& other)
{
	root = copy(other.root);
}

template<class T>
void AVL<T>::free()
{
	free(root);
	root = nullptr;
}

template<class T>
void AVL<T>::free(Node* root)
{
	if (root != nullptr)
	{
		free(root->left);
		free(root->right);
		delete root;
	}
}

template<class T>
class AVL<T>::Node* AVL<T>::copy(Node* root)
{
	if (root == nullptr)
		return nullptr;

	return new Node(root->data, copy(root->left), copy(root->right), root->height);
}

template<class T>
bool AVL<T>::contains(const Node* root, const T& data) const
{
	if (root == nullptr)
		return false;

	if (root->data == data)
		return true;

	if (root->data < data)
		return contains(root->right, data);

	return contains(root->left, data);
}

template<class T>
class AVL<T>::Node* AVL<T>::insert(Node* root, const T& data)
{
	if (root == nullptr)
		return new Node(data);

	if (root->data == data)
		return root;

	if (root->data < data)
		root->right = insert(root->right, data);

	if (root->data > data)
		root->left = insert(root->left, data);

	return balance(root);
}

template<class T>
class AVL<T>::Node* AVL<T>::remove(Node* root, const T& data)
{
	if (root == nullptr)
		return nullptr;

	if (root->data < data)
		root->right = remove(root->right, data);

	if (root->data > data)
		root->left = remove(root->left, data);

	if (root->data == data)
	{
		if (root->left == nullptr && root->right == nullptr)
		{
			delete root;

			return nullptr;
		}

		if (root->left == nullptr && root->right != nullptr)
		{
			Node* result = root->right;
			delete root;

			return result;
		}

		if (root->right == nullptr && root->left != nullptr)
		{
			Node* result = root->left;
			delete root;

			return result;
		}

		if (height(root->left) < height(root->right))
		{
			root->data = getMin(root->right);
			root->right = remove(root->right, root->data);
		}
		else
		{
			root->data = getMax(root->left);
			root->left = remove(root->left, root->data);
		}

		return balance(root);
	}
}

template<class T>
T AVL<T>::getMin(const Node* root) const
{
	if (root == nullptr)
		throw "Empty tree";

	while (root->left != nullptr)
		root = root->left;

	return root->data;
}

template<class T>
inline T AVL<T>::getMax(const Node* root) const
{
	if (root == nullptr)
		throw "Empty tree";

	while (root->right != nullptr)
		root = root->right;

	return root->data;
}

template<class T>
inline int AVL<T>::height(const Node* root) const
{
	if (root == nullptr)
		return 0;

	int heightLeft = (root->left != nullptr) ? root->left->height : 0;
	int heightRight = (root->right != nullptr) ? root->right->height : 0;

	return std::max(heightLeft, heightRight) + 1;
}

template<class T>
inline int AVL<T>::balanceFactor(const Node* root) const
{
	if (root == nullptr)
		return 0;

	return height(root->left) - height(root->right);
}

/*
A					B

	B		->	A		C

		C
*/
template<class T>
class AVL<T>::Node* AVL<T>::LRotation(Node* root) const
{
	Node* newRoot = root->right;
	root->right = newRoot->left;
	newRoot->left = root;

	root->height = height(root);
	newRoot->height = height(newRoot);

	return newRoot;
}

/*
		A			B

	B		->	C		A

C
*/
template<class T>
class AVL<T>::Node* AVL<T>::RRotation(Node* root) const
{
	Node* newRoot = root->left;
	root->left = newRoot->right;
	newRoot->right = root;

	root->height = height(root);
	newRoot->height = height(newRoot);

	return newRoot;
}

/*
	C				C			B

A		->		B		->	A		C

	B		A
*/
template<class T>
class AVL<T>::Node* AVL<T>::LRRotation(Node* root) const
{
	root->left = LRotation(root->left);

	return RRotation(root);
}

/*
A			A				B

	C	->		B	->	A		C

B					C
*/
template<class T>
class AVL<T>::Node* AVL<T>::RLRotation(Node* root) const
{

	root->right = RRotation(root->right);

	return LRotation(root);
}

template<class T>
class AVL<T>::Node* AVL<T>::balance(Node* root) const
{
	root->height = height(root);

	if (balanceFactor(root) == 2 && balanceFactor(root->left) == 1)
		return RRotation(root);

	if (balanceFactor(root) == 2 && balanceFactor(root->left) == -1)
		return LRRotation(root);

	if (balanceFactor(root) == -2 && balanceFactor(root->right) == 1)
		return RLRotation(root);

	if (balanceFactor(root) == -2 && balanceFactor(root->right) == -1)
		return LRotation(root);

	return root;
}


template<class T>
AVL<T>::AVL(const AVL& other)
{
	copy(other);
}

template<class T>
AVL<T>& AVL<T>::operator=(const AVL& other)
{
	if (this != &other)
	{
		free();
		copy(other);
	}

	return *this;
}

template<class T>
AVL<T>::~AVL()
{
	free();
}

template<class T>
bool AVL<T>::contains(const T& data) const
{
	return contains(root, data);
}

template<class T>
void AVL<T>::insert(const T& data)
{
	root = insert(root, data);
}

template<class T>
void AVL<T>::remove(const T& data)
{
	root = remove(root, data);
}

template<class T>
inline int AVL<T>::height() const
{
	return height(root);
}
