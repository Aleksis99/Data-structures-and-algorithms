#include<iostream>
#include<list>
#include<unordered_map>

template<class K, class V>
class LRUCache 
{
private:
	using CacheList = std::list<std::pair<K, V>>;

	using CacheListIterator = typename CacheList::iterator;
	using CacheMap = std::unordered_map<K, CacheListIterator>;

	int maxSize;
	std::list<std::pair<K, V>> l;
	CacheMap  m;

public:
	LRUCache(int maxSize) 
	{
		this->maxSize = maxSize > 1 ? maxSize : 1;
	}

	void insertKeyValue(const K& key, const V& value)
	{

		if (m.count(key) != 0) 
		{
			CacheListIterator it = m[key];
			it->second = value;
		}
		else 
		{
			if (l.size() == maxSize) 
			{
				const std::pair<K, V>& last = l.back();
				m.erase(last.first);
				l.pop_back();
			}

			l.push_front({key, value});
			m[key] = l.begin();
		}
	}

	V* getValue(const K& key)
	{

		if (m.count(key) != 0) 
		{
			CacheListIterator it = m[key];

			l.push_front(*it);
			l.erase(it);
			m[key] = l.begin();

			return &l.begin()->second;
		}

		return nullptr;
	}

	const K& mostRecentKey() 
	{
		return l.front().first;
	}

};


int main() 
{

	LRUCache<std::string, int> lru(3);
	lru.insertKeyValue("mango", 10);
	lru.insertKeyValue("apple", 20);
	lru.insertKeyValue("guava", 30);
	std::cout << lru.mostRecentKey() << std::endl;

	lru.insertKeyValue("mango", 40);
	std::cout << lru.mostRecentKey() << std::endl;

	int* orders = lru.getValue("mango");

	if (orders != nullptr) 
	{
		std::cout << "Order of Mango " << *orders << std::endl;
	}

	lru.insertKeyValue("banana", 20);

	if (lru.getValue("apple") == nullptr) 
	{
		std::cout << "apple doesn't exist";
	}

	if (lru.getValue("guava") == nullptr) 
	{
		std::cout << "guava doesn't exist";
	}

	if (lru.getValue("banana") == nullptr) 
	{
		std::cout << "banana doesn't exist";
	}

	if (lru.getValue("mango") == nullptr) 
	{
		std::cout << "mango doesn't exist";
	}
}