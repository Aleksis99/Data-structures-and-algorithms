#include <iostream>
#include <utility>

int partition(int* arr, int low, int high)
{
    int pivotPosition = low;
    int pivot = arr[high];

    for (int i = low; i < high; i++)
    {
        if (arr[i] < pivot)
        {
            std::swap(arr[i], arr[pivotPosition]);
            pivotPosition++;
        }
    }

    std::swap(arr[pivotPosition], arr[high]);

    return pivotPosition;
}

void quickSort(int* arr, int low, int high)
{
    if (low < high)
    {
        int pivotPosition = partition(arr, low, high);

        quickSort(arr, low, pivotPosition - 1);
        quickSort(arr, pivotPosition + 1, high);
    }
}

int main()
{
    int arr[] = {12, 3, 11, 2, 113};
    const int n = sizeof(arr) / sizeof(arr[0]);

    quickSort(arr, 0, n - 1);

    for (int i = 0; i < n; i++)
    {
        std::cout << arr[i] << " ";
    }
}
