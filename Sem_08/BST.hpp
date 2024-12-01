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

public:

	BST() = default;
	BST(const BST& other);
	BST& operator=(const BST& other);
	~BST();

	bool contains(const T& data) const;
	void insert(const T& data);
	void remove(const T& data);

};

