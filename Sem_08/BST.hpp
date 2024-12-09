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
	void free();
	void free(Node* root) const;
	Node* copy(const Node* root) const;
	void copy(const BST& other);
	bool contains(const Node* root, const T& data) const;
	Node* insert(Node* node, const T& data) const;
	Node* remove(Node* node, const T& data) const;

	const T& findMin(const Node* node) const;

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
inline void BST<T>::free()
{
	free(this->root);
}

template<class T>
inline void BST<T>::free(Node* node) const
{
	if (node == nullptr)
		return;

	free(node->left);
	free(node->right);
	delete node;
}

template<class T>
inline BST<T>::Node* BST<T>::copy(const Node* root) const
{
	if (root == nullptr)
	{
		return nullptr;
	}

	return new Node(other.root->data, copy(root->left), copy(root->right));
}

template<class T>
inline void BST<T>::copy(const BST& other)
{
	root = copy(other.root);
}

template<class T>
inline bool BST<T>::contains(const Node* root, const T& data) const
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
BST<T>::Node* BST<T>::insert(Node* node, const T& data) const
{
	if (node == nullptr)
		return new Node(data);

	if (node->data == data)
		return node;

	if (node->data < data)
	{
		node->right = insert(node->right, data);
		return node;
	}

	node->left = insert(node->left, data);
	return node;
}

template<class T>
BST<T>::Node* BST<T>::remove(Node* node, const T& data) const
{
	if (node == nullptr)
		return node;

	if (node->data < data)
	{
		node->right = remove(node->right, data);
		return node;
	}

	if (node->data > data)
	{
		node->left = remove(node->left, data);
		return node;
	}

	if (node->left == nullptr && node->right == nullptr)
	{
		delete node;
		return nullptr;
	}

	if (node->left == nullptr && node->right != nullptr)
	{
		Node* result = node->right;
		delete node;
		return result;
	}

	if (node->left != nullptr && node->right == nullptr)
	{
		Node* result = node->left;
		delete node;
		return result;
	}

	T min = findMin(node->right);
	node->data = min;
	node->right = remove(node->right, min);
	return node;
}

template<class T>
inline const T& BST<T>::findMin(const Node* node) const
{
	if (node == nullptr)
		throw "Empty tree";

	while (node->left != nullptr)
	{
		node = node->left;
	}

	return node->data;
}

template<class T>
inline BST<T>::BST(const BST& other)
{
	copy(other);
}

template<class T>
inline BST<T>& BST<T>::operator=(const BST& other)
{
	if (this != &other)
	{
		free();
		copy(other);
	}

	return *this;
}

template<class T>
inline BST<T>::~BST()
{
	free();
}

template<class T>
inline bool BST<T>::contains(const T& data) const
{
	return contains(root, data);
}

template<class T>
inline void BST<T>::insert(const T& data)
{
	root = insert(root, data);
}

template<class T>
inline void BST<T>::remove(const T& data)
{
	root = remove(root, data);
}
