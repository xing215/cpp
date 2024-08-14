// Student ID: 23127261
// Full name: Vuong Ngu Tin Thanh

#include <iostream>

using namespace std;

void selection(int a[], int l, int r)
{
    for (int i = l; i < r; i++)
    {
        int min_idx = i;
        for (int j = i + 1; j <= r; j++)
            if (a[j] < a[min_idx])
                min_idx = j;
        swap(a[i], a[min_idx]);
    }
}

void insertion(int a[], int l, int r)
{
    for (int i = l + 1; i <= r; i++)
    {
        int val = a[i], j;
        for (j = i; j > l && a[j] > val; j--)
            a[j] = a[j - 1];
        a[j] = val;
    }
}

void bubble(int a[], int l, int r)
{
    for (int i = l; i < r; i++)
        for (int j = i + 1; j <= r; j++)
            if (a[i] > a[j])
                swap(a[i], a[j]);
}

void merge(int array[], int l, int m, int r)
{
    int leftArrNum = m - l + 1,
        rightArrNum = r - m;

    int *leftArr = new int[leftArrNum],
        *rightArr = new int[rightArrNum];

    for (int i = 0; i < leftArrNum; i++)
        leftArr[i] = array[l + i];
    for (int j = 0; j < rightArrNum; j++)
        rightArr[j] = array[m + 1 + j];

    int leftIdx = 0, rightIdx = 0;
    int mergedIdx = l;

    while (leftIdx < leftArrNum && rightIdx < rightArrNum)
    {
        if (leftArr[leftIdx] <= rightArr[rightIdx])
            array[mergedIdx++] = leftArr[leftIdx++];
        else
            array[mergedIdx++] = rightArr[rightIdx++];
    }

    while (leftIdx < leftArrNum)
        array[mergedIdx++] = leftArr[leftIdx++];

    while (rightIdx < rightArrNum)
        array[mergedIdx++] = rightArr[rightIdx++];
    
    delete[] leftArr;
    delete[] rightArr;
}

void mergeSort(int array[], int l, int r)
{
    if (l < r)
    {
        int m = l + (r - l) / 2;
        mergeSort(array, l, m);
        mergeSort(array, m + 1, r);
        merge(array, l, m, r);
    }
}

int partition(int arr[], int l, int r)
{
    int pivot = arr[l];
    int count = 0;
    for (int i = l + 1; i <= r; i++)
        if (arr[i] <= pivot)
            count++;

    int pivotIndex = l + count;
    swap(arr[pivotIndex], arr[l]);

    int i = l, j = r;

    while (i < pivotIndex && j > pivotIndex) 
    {
        while (arr[i] <= pivot)
            i++;
        while (arr[j] > pivot)
            j--;
        if (i < pivotIndex && j > pivotIndex)
            swap(arr[i++], arr[j--]);
    }
    return pivotIndex;
}

void quickSort(int arr[], int l, int r)
{
    if (l < r)
    {
        int p = partition(arr, l, r);
        quickSort(arr, l, p - 1);
        quickSort(arr, p + 1, r);
    }
}

int main()
{
    int arr[] = {132,14214,2,2321,-21};
    mergeSort(arr, 0, 4);
    for (int i = 0; i < 5; i++)
        cout << arr[i] << ' ';
    
    return 0;
}