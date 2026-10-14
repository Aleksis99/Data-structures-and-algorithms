#include <iostream>
#include <utility>

// BC == WC == AC == O(1)
long long foo(const int* arr, size_t n)
{
	long long result = 0;

	for (size_t i = 0; i < 5000000; i++)
	{
		result += i;
	}

	return result;
}

// BC == WC == AC == O(n)
int* bar(const int* arr, size_t n)
{
	// size(arr) == n
	return new int[n]();
}

// BC == WC == AC == O(n)
int sum(const int* arr, size_t n)
{
	int result = 0;

	for (size_t i = 0; i < n; i++)
	{
		result += arr[i];
	}

	return result;
}

// BC == WC == AC == O(n*m), i.e. linear in the size of the input
int matrixSum(const int* const* matrix, size_t n, size_t m)
{
	int result = 0;

	for (size_t i = 0; i < n; i++)
	{
		for (size_t j = 0; j < m; j++)
		{
			result += matrix[i][j];
		}
	}

	return result;
}
// BC == WC == AC == O(n)
size_t findMinIndex(const int* arr, size_t n)
{
	size_t result = 0;

	for (size_t i = 1; i < n; i++)
	{
		if (arr[i] < arr[result])
		{
			result = i;
		}
	}

	return result;
}

// BC == WC == AC == O(n^2)
void selectionSort(int* arr, size_t n)
{
	for (size_t i = 0; i < n; i++)
	{
		size_t minIndex = i + findMinIndex(arr + i, n - i);
		std::swap(arr[i], arr[minIndex]);
	}
}

// BC == O(1), WC == AC == O(log(n))
int binSearch(const int* arr, int key, int low, int high)
{
	if (low > high)
		return -1;

	int mid = low + (high - low) / 2;

	if (arr[mid] == key)
		return mid;

	if (arr[mid] < key)
		return binSearch(arr, key, mid + 1, high);

	return binSearch(arr, key, low, mid-1);
}

// BC == O(1), WC == AC == O(log(n)) but faster practically
int binSearchIt(const int* arr, int key, int n)
{
	int low = 0;
	int high = n - 1;

	while (low <= high)
	{
		int mid = low + (high - low) / 2;

		if (arr[mid] == key)
			return mid;

		if (arr[mid] < key)
		{
			low = mid + 1;
		}
		else
		{
			high = mid - 1;
		}
	}

	return -1;
}

// BC == WC == AC == O(n)
void merge(int* arr, size_t left, size_t leftEnd, size_t right, size_t rightEnd, int* buffer)
{
	size_t buffIndex = left;
	size_t start = left;
	while (left <= leftEnd && right <= rightEnd)
	{
		if (arr[left] <= arr[right])
		{
			buffer[buffIndex] = arr[left];
			left++;
		}
		else
		{
			buffer[buffIndex] = arr[right];
			right++;
		}
		buffIndex++;
	}

	while (left <= leftEnd)
	{
		buffer[buffIndex] = arr[left];
		left++;
		buffIndex++;
	}
	while (right <= rightEnd)
	{
		buffer[buffIndex] = arr[right];
		right++;
		buffIndex++;
	}

	for (size_t i = start; i <= rightEnd; i++)
	{
		arr[i] = buffer[i];
	}
}

// BC == WC == AC == O(n*log(n))
void mergesortHelp(int* arr, size_t low, size_t high, int* buffer)
{
	if (low == high)
		return;

	size_t mid = low + (high - low) / 2;
	mergesortHelp(arr, low, mid, buffer);
	mergesortHelp(arr, mid+1, high, buffer);
	merge(arr, low, mid, mid+1, high, buffer);

}

// BC == WC == AC == O(n*log(n))
void mergesort(int* arr, size_t n)
{
	if (n == 0)
		return;

	int* buffer = new int[n];
	mergesortHelp(arr, 0, n - 1, buffer);
	delete[] buffer;
}

int main()
{
	int arr[] = {1, 8, 2, -5, 12, -19};
	const size_t n = sizeof(arr) / sizeof(arr[0]);

	mergesort(arr, n);

	for (size_t i = 0; i < n; i++)
	{
		std::cout << arr[i] << " ";
	}
}
