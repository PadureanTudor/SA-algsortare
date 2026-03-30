#pragma once

#include <iostream>
#include <limits>
#include <utility>
#include <string>
#include <vector>

namespace Algs {
    enum Type {
        BUBBLE_SORT, INSERTION_SORT, SELECTION_SORT, MERGE_SORT, QUICK_SORT, COUNT_SORT
    };
    const Type All[] = {BUBBLE_SORT, INSERTION_SORT, SELECTION_SORT, MERGE_SORT, QUICK_SORT, COUNT_SORT};
    const std::string AllChar[] = {"Bubble Sort", "Insertion Sort", "Selection Sort", "Merge Sort", "Quick Sort", "Count Sort"};
    const int Count = sizeof(All) / sizeof(Type); 
}

void bubbleSort(int v[], int size) {
    bool swapped;
  
    for (int i = 0; i < size - 1; i++) {
        swapped = false;
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
    while (1)
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
        default:
            std::cerr << "Imposibil!";
            exit(1);
    }
}