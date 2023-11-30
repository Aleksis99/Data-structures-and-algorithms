template <class T>
class BST
{
private:

	struct Node
	{
		T data;
		Node* left;
		Node* right;

		Node(const T& data, Node* left = nullptr, Node* right = nullptr) :
			data(data), left(left), right(right) {};
	};

	Node* root = nullptr;

	void copy(const BST& other);
	void free();

	void free(Node* root);
	Node* copy(Node* root);

	bool contains(const Node* root, const T& data) const;
	Node* insert(Node* root, const T& data);
	Node* remove(Node* root, const T& data);
	T getMin(const Node* root) const;

public:

	BST() = default;
	BST(const BST& other);
	BST& operator=(const BST& other);
	~BST();

	bool contains(const T& data) const;
	void insert(const T& data);
	void remove(const T& data);

};

template<class T>
void BST<T>::copy(const BST& other)
{
	root = copy(other.root);
}

template<class T>
void BST<T>::free()
{
	free(root);
	root = nullptr;
}

template<class T>
void BST<T>::free(Node* root)
{
	if (root != nullptr)
	{
		free(root->left);
		free(root->right);
		delete root;
	}
}

template<class T>
class BST<T>::Node* BST<T>::copy(Node* root)
{
	if (root == nullptr)
		return nullptr;

	return new Node(root->data, copy(root->left), copy(root->right));
}

template<class T>
bool BST<T>::contains(const Node* root, const T& data) const
{
	if(root == nullptr)
		return false;

	if (root->data == data)
		return true;

	if (root->data < data)
		return contains(root->right, data);

	return contains(root->left, data);
}

template<class T>
class BST<T>::Node* BST<T>::insert(Node* root, const T& data)
{
	if (root == nullptr)
		return new Node(data);

	if (root->data == data)
		return root;

	if (root->data < data)
		root->right = insert(root->right, data);

	if (root->data > data)
		root->left = insert(root->left, data);

	return root;
}

template<class T>
class BST<T>::Node* BST<T>::remove(Node* root, const T& data)
{
	if(root == nullptr)
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

		root->data = getMin(root->right);
		root->right = remove(root->right, root->data);

		return root;
	}
}

template<class T>
T BST<T>::getMin(const Node* root) const
{
	if (root == nullptr)
		throw "Empty tree";

	while (root->left != nullptr)
		root = root->left;

	return root->data;
}


template<class T>
BST<T>::BST(const BST& other)
{
	copy(other);
}

template<class T>
BST<T>& BST<T>::operator=(const BST& other)
{
	if (this != &other)
	{
		free();
		copy(other);
	}

	return *this;
}

template<class T>
BST<T>::~BST()
{
	free();
}

template<class T>
bool BST<T>::contains(const T& data) const
{
	return contains(root, data);
}

template<class T>
void BST<T>::insert(const T& data)
{
	root = insert(root, data);
}

template<class T>
void BST<T>::remove(const T& data)
{
	root = remove(root, data);
}
