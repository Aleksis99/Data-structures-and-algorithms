#include <iostream>

// WC = AC = BC = O(2^n)
size_t fib(size_t n)
{
	if (n < 2)
	{
		return n;
	}

	return fib(n - 1) + fib(n - 2);
}

// WC = AC = BC = O(n)
size_t fibLinear(size_t n)
{
	size_t last = 0;
	size_t curr = 1;

	for (size_t i = 0; i < n; i++)
	{
		size_t newNum = last + curr;
		last = curr;
		curr = newNum;
	}

	return last;
}

// WC = AC = BC = O(n)
int sum(int* arr, size_t n)
{
	int result = 0;

	for (size_t i = 0; i < n; i++)
	{
		result += arr[i];
	}

	return result;
}

// BC = WA = AC = O(n)
size_t findMinIndex(int* arr, size_t start, size_t n)
{
	size_t minIndex = start;

	for (size_t i = start + 1; i < n; i++)
	{
		if (arr[i] < arr[minIndex])
		{
			minIndex = i;
		}
	}

	return minIndex;
}

// WC = BC = AC = O(n^2)
void selectionSort(int* arr, size_t n)
{
	for (size_t i = 0; i < n - 1; i++)
	{
		size_t minIndex = findMinIndex(arr, i, n);
		std::swap(arr[i], arr[minIndex]);
	}
}

void printArr(int* arr, size_t n)
{
	for (size_t i = 0; i < n; i++)
	{
		std::cout << arr[i] << " ";
	}

	std::cout << std::endl;
}

// BC = O(1) WC = AC = O(Log(n))
size_t binSearch(int* arr, size_t n, int key)
{
	size_t l = 0;
	size_t r = n - 1;
	while (l <= r) 
	{
		size_t mid = (l + r) / 2;

		if (arr[mid] == key) 
		{
			return mid;
		}

		if (arr[mid] > key) 
		{
			r = mid - 1;
		}
		else 
		{
			l = mid + 1;
		}
	}

	return -1;
}

// BC = O(n) AC = WC = O(n^2)
void insertionSort(int* arr, size_t n)
{
	for (size_t i = 1; i < n; i++)
	{
		int key = arr[i];

		size_t j = i;

		while (j > 0 && arr[j - 1] > key)
		{
			arr[j] = arr[j - 1];
			j--;
		}

		arr[j] = key;
	}
}
// WC = BC = AC = O(n)
int* merge(int* arr1, size_t n1, int* arr2, size_t n2)
{
	int* result = new int[n1 + n2];
	int i1 = 0, i2 = 0, iRes = 0;

	while (i1 < n1 && i2 < n2)
	{
		if (arr1[i1] < arr2[i2])
		{
			result[iRes++] = arr1[i1++];
		}
		else
		{
			result[iRes++] = arr2[i2++];
		}
	}

	while (i1 < n1)
	{
		result[iRes++] = arr1[i1++];
	}

	while (i2 < n2)
	{
		result[iRes++] = arr2[i2++];
	}

	return result;
}

int main()
{
	int arr[]{ 5, 1, 13, 7 };
	
	insertionSort(arr, 4);
	printArr(arr, 4);

	std::cout<<binSearch(arr, 4, 7);

}

