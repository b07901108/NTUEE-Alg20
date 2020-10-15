// **************************************************************************
//  File       [sort_tool.cpp]
//  Author     [Yu-Hao Ho]
//  Synopsis   [The implementation of the SortTool Class]
//  Modify     [2020/9/15 Mu-Ting Wu]
// **************************************************************************

#include "sort_tool.h"
#include <iostream>
#include <math.h>

// Constructor
SortTool::SortTool() {}

// Insertsion sort method
void SortTool::InsertionSort(vector<int> &data)
{
    // Function : Insertion sort
    // TODO : Please complete insertion sort code here
    for (int i = 1; i < data.size(); ++i)
    {
        for (int j = i; j > 0; --j)
        {
            if (data[j] < data[j - 1])
            {
                int temp = data[j];
                data[j] = data[j - 1];
                data[j - 1] = temp;
            }
            else
            {
                break;
            }
        }
    }
}

// Quick sort method
void SortTool::QuickSort(vector<int> &data)
{
    QuickSortSubVector(data, 0, data.size() - 1);
}
// Sort subvector (Quick sort)
void SortTool::QuickSortSubVector(vector<int> &data, int low, int high)
{
    // Function : Quick sort subvector
    // TODO : Please complete QuickSortSubVector code here
    // Hint : recursively call itself
    //        Partition function is needed
    if (low < high)
    {
        int pivot = Partition(data, low, high);
        QuickSortSubVector(data, low, pivot);
        QuickSortSubVector(data, pivot + 1, high);
    }
}

int SortTool::Partition(vector<int> &data, int low, int high)
{
    // Function : Partition the vector
    // TODO : Please complete the function
    // Hint : Textbook page 171
    int mid = (low + high) / 2;
    int pivot = data[mid];
    int left = low;
    int right = high;
    while (true)
    {
        while (data[right] > pivot && right >= low)
        {
            --right;
        }
        while (data[left] < pivot && left <= high)
        {
            ++left;
        }
        /*
        cout << "low = " << low << "\n";
        cout << "high = " << high << "\n";
        cout << "left = " << left << "\n";
        cout << "right = " << right << "\n";
        */
        if (left < right)
        {
            int temp = data[left];
            data[left] = data[right];
            data[right] = temp;
            ++left;
            --right;
        }
        else
        {
            return right;
        }
    }
}

// Merge sort method
void SortTool::MergeSort(vector<int> &data)
{
    MergeSortSubVector(data, 0, data.size() - 1);
}

// Sort subvector (Merge sort)
void SortTool::MergeSortSubVector(vector<int> &data, int low, int high)
{
    // Function : Merge sort subvector
    // TODO : Please complete MergeSortSubVector code here
    // Hint : recursively call itself
    //        Merge function is needed
    if ((high - low) >= 1) // if not base case
    {
        int middle1 = (high + low) / 2;
        int middle2 = middle1 + 1;
        MergeSortSubVector(data, low, middle1);
        MergeSortSubVector(data, middle2, high);
        Merge(data, low, middle1, middle2, high);
    }
}

// Merge
void SortTool::Merge(vector<int> &data, int low, int middle1, int middle2, int high)
{
    // Function : Merge two sorted subvector
    // TODO : Please complete the function
    int leftIndex = 0;       // index into left subvector
    int rightIndex = 0;      // index into right subvector
    int combinedIndex = low; // index into temporary working vector
    vector<int> left, right;
    for (int i = low; i <= middle1; ++i)
    {
        left.push_back(data[i]);
    }
    for (int i = middle2; i <= high; ++i)
    {
        right.push_back(data[i]);
    }
    int leftCount = left.size();
    int rightCount = right.size();
    //TODO : merge vectors until reaching end of either
    while (leftIndex <= leftCount - 1 && rightIndex <= rightCount - 1)
    {
        // place smaller of two current elements into result
        // and move to next space in vector
        if (left[leftIndex] > right[rightIndex])
        {
            data[combinedIndex] = right[rightIndex];
            combinedIndex++;
            rightIndex++;
        }
        else
        {
            data[combinedIndex] = left[leftIndex];
            combinedIndex++;
            leftIndex++;
        }
    } // end while

    if (leftIndex == leftCount) // if at end of left vector
    {
        // copy in rest of right vector
        for (int i = rightIndex; i <= rightCount - 1; ++i)
        {
            data[combinedIndex] = right[i];
            combinedIndex++;
        }
    }    // end if
    else // at end of right vector
    {
        // copy in rest of left vector
        for (int i = leftIndex; i <= leftCount - 1; ++i)
        {
            data[combinedIndex] = left[i];
            combinedIndex++;
        }
    }
}

// Heap sort method
void SortTool::HeapSort(vector<int> &data)
{
    // Build Max-Heap
    BuildMaxHeap(data);
    // 1. Swap data[0] which is max value and data[i] so that the max value will be in correct location
    // 2. Do max-heapify for data[0]
    for (int i = data.size() - 1; i >= 1; i--)
    {
        swap(data[0], data[i]);
        heapSize--;
        MaxHeapify(data, 0);
    }
}

//Max heapify
void SortTool::MaxHeapify(vector<int> &data, int root)
{
    // Function : Make tree with given root be a max-heap if both right and left sub-tree are max-heap
    // TODO : Please complete max-heapify code here
    int right = (root + 1) * 2;
    int left = right - 1;
    int largest;
    if (left <= heapSize && data[left] > data[root]) {
        largest = left;
    } else {
        largest = root;
    }
    if (right <= heapSize && data[right] > data[largest]) {
        largest = right;
    }
    if (largest != root) {
        swap(data[root], data[largest]);
        MaxHeapify(data, largest);
    }
}

//Build max heap
void SortTool::BuildMaxHeap(vector<int> &data)
{
    heapSize = data.size()-1; // initialize heap size
    // Function : Make input data become a max-heap
    // TODO : Please complete BuildMaxHeap code here
    for (int i=floor(heapSize/2); i>=0; --i) {
        MaxHeapify(data, i);
    }
}
