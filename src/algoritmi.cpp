#include <limits>
#include <utility>

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
    for(int i = 2; i < size; i++) {
        v[0] = v[i];
        int j = i-1;
        while(v[0] < v[j]) {
            v[j+1] = v[j];
            j--;
        } 
        v[j+1] = v[0];
    }
}

void selectionSort(int v[], int size) {
    for(int i = 0; i < size-1; i++) {
        int minim = std::numeric_limits<int>::max(), mink = -1;
        for(int j = i+1; j < size; j++) {
            if(v[i] < minim) {
                minim = v[i];
                mink = j;
            } 
        }
        if(mink != -1) {
            std::swap(v[i], v[mink]);
        }
    }
}

void quickSortWorker(int v[], int st, int dr) {
    if(dr-st == 0) {
        return;
    }

    int pivot = v[st];
    int i = st-1, j = dr+1;
    for(;;) {
        do {
            i++;
        } while(v[i] < pivot);
        do {
            j--;
        } while(v[j] > pivot);

        if(i >= j) {
            break;
        }

        std::swap(v[i], v[j]);
    }


    quickSortWorker(v, st, j);
    quickSortWorker(v, j+1, dr);
}

void quickSort(int v[], int size) {
    quickSortWorker(v, 0, size);
}

