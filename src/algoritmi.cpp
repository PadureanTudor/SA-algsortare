#pragma once

#include <iostream>
#include <limits>
#include <utility>
#include <string>

namespace Algs {
    enum Type {
        BUBBLE_SORT, INSERTION_SORT, SELECTION_SORT, MERGE_SORT, QUICK_SORT, COUNT_SORT, RADIX_SORT
    };
    const Type All[] = {BUBBLE_SORT, INSERTION_SORT, SELECTION_SORT, MERGE_SORT, QUICK_SORT, COUNT_SORT, RADIX_SORT};
    const std::string AllChar[] = {"Bubble Sort", "Insertion Sort", "Selection Sort", "Merge Sort", "Quick Sort", "Count Sort", "Radix Sort"};
    const int Count = sizeof(All) / sizeof(Type); 
}

void bubbleSort(int v[], int size) {
    for (int i = 0; i < size - 1; i++) {
        bool swapped = false;
        for (int j = 0; j < size - i - 1; j++) {
            if (v[j] > v[j + 1]) {
                std::swap(v[j], v[j + 1]);
                swapped = true;
            }
        }
      
        // If no two elements were swapped, then break
        if (!swapped)
            break;
    }
}

void insertionSort(int v[], int size) {
    for(int i = 1; i < size; i++) {
        int k = v[i];
        int j = i - 1;

        while(j >= 0 && v[j] > k) {
            v[j+1] = v[j];
            j--;
        }
        v[j+1] = k;
    }
}

void selectionSort(int v[], int size) {
    for(int i = 0; i < size-1; i++) {
        int minim = v[i], mink = i;
        for(int j = i+1; j < size; j++) {
            if(v[j] < minim) {
                minim = v[j];
                mink = j;
            } 
        }
        if(mink != i) {
            std::swap(v[i], v[mink]);
        }
    }
}

int hoarePartition(int a[], int low, int high)
{
    int pivot = a[low];
    int i = low - 1;
    int j = high + 1;
    while (true)
    {
        do {
            i++;
        } while (a[i] < pivot);
 
        do {
            j--;
        } while (a[j] > pivot);
 
        if (i >= j) {
            return j;
        }
 
        std::swap(a[i], a[j]);
    }
}

void quickSortWorker(int v[], int st, int dr) {
    if(dr-st <= 0) {
        return;
    }

    int pivot = hoarePartition(v, st, dr);

    quickSortWorker(v, st, pivot);
    quickSortWorker(v, pivot+1, dr);
}

void quickSort(int v[], int size) {
    quickSortWorker(v, 0, size-1);
}

void merge(int v[], int st, int dr) {
    int mij = (st+dr)/2;
    int n1 = mij - st + 1;
    int n2 = dr - mij;

    int *v1 = new int[n1];
    int *v2 = new int[n2];

    for (int i = 0; i < n1; i++)
        v1[i] = v[st + i];
    for (int j = 0; j < n2; j++)
        v2[j] = v[mij + j + 1];

    int i = 0, j = 0;
    int k = st;

    while (i < n1 && j < n2) {
        if (v1[i] <= v2[j]) {
            v[k] = v1[i];
            i++;
        }
        else {
            v[k] = v2[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        v[k] = v1[i];
        i++;
        k++;
    }

    while (j < n2) {
        v[k] = v2[j];
        j++;
        k++;
    }

    delete[] v1;
    delete[] v2;
}

void mergeSortWorker(int v[], int st, int dr) {
    if(dr-st <= 0) { return; }

    mergeSortWorker(v, st, (st+dr)/2);
    mergeSortWorker(v, (st+dr)/2+1, dr);
    merge(v, st, dr);
}

void mergeSort(int v[], int size) {
    mergeSortWorker(v, 0, size-1);
}

void countSort(int v[], int size) {
    int minim = std::numeric_limits<int>::max();
    int maxim = std::numeric_limits<int>::min();
    for(int i = 0; i < size; i++) {
        minim = std::min(v[i], minim);
        maxim = std::max(v[i], maxim);
    }
    int *frecv = new int[maxim-minim+1];
    for(int i = 0; i < maxim-minim+1; frecv[i++] = 0);
    for(int i = 0; i < size; i++) {
        frecv[v[i]-minim]++;
    }
    int nv = 0;
    for(int i = minim; i <= maxim; i++) {
        while(frecv[i-minim] > 0) {
            v[nv++] = i-minim;
            frecv[i-minim]--;
        }
    }
    delete[] frecv;
}

int getMax(int v[], int n) {
    int mx = v[0];
    for (int i = 1; i < n; i++)
        if (v[i] > mx)
            mx = v[i];
    return mx;
}

void countSortDigit(long long v[], int n, long long exp) {
    long long *output = new long long[n];
    int count[10] = {0};

    for (int i = 0; i < n; i++)
        count[(v[i] / exp) % 10]++;

    for (int i = 1; i < 10; i++)
        count[i] += count[i - 1];

    for (int i = n - 1; i >= 0; i--) {
        output[count[(v[i] / exp) % 10] - 1] = v[i];
        count[(v[i] / exp) % 10]--;
    }

    for (int i = 0; i < n; i++)
        v[i] = output[i];

    delete[] output;
}

void radixSort(int v[], int n) {
    if (n <= 1) return;

    // Use long long to prevent overflow during subtraction/offsetting
    long long min_val = v[0];
    long long max_val = v[0];

    for (int i = 1; i < n; i++) {
        if (v[i] < min_val) min_val = v[i];
        if (v[i] > max_val) max_val = v[i];
    }

    long long *shifted = new long long[n]; 
    for (int i = 0; i < n; i++) {
        shifted[i] = (long long)v[i] - min_val;
    }

    long long range_max = (long long)max_val - min_val;

    for (long long exp = 1; range_max / exp > 0; exp *= 10) {
        countSortDigit(shifted, n, exp);
    }

    for (int i = 0; i < n; i++) {
        v[i] = (int)(shifted[i] + min_val);
    }

    delete[] shifted;
}

void task(int input[], int size, Algs::Type algoritm) {
    switch(algoritm) {
        case Algs::Type::BUBBLE_SORT:
            bubbleSort(input, size);
            break;
        case Algs::Type::INSERTION_SORT:
            insertionSort(input, size);
            break;
        case Algs::Type::SELECTION_SORT:
            selectionSort(input, size);
            break;
        case Algs::Type::MERGE_SORT:
            mergeSort(input, size);
            break;
        case Algs::Type::QUICK_SORT:
            quickSort(input, size);
            break;
        case Algs::Type::COUNT_SORT:
            countSort(input, size);
            break;
        case Algs::Type::RADIX_SORT:
            radixSort(input, size);
            break;
        default:
            std::cerr << "Imposibil!";
            exit(1);
    }
}