#include <utility>

void bubbleSort(int v[], int size, bool (*criteriu)(int, int)) {
    for(int i = 0; i < size; i++) {
        for(int j = i+1; j < size; j++) {
            if(criteriu(v[i], v[j])) {
                std::swap(v[i], v[j]);
            }
        }
    }
}