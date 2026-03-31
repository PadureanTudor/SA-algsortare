#include <random>

#include "algoritmi.cpp"


// Pentru fiecare Type, executam fiecare Len pentru fiecare Algs::Type de RunsPerLen ori.
// Deci 4 for().
namespace Inputset {
    enum Type {
        RANDOM, SORTAT, INVERS_SORTAT, NR_MICI, APROAPE_SORTAT
    };
    const Type AllTypes[] = {RANDOM, SORTAT, INVERS_SORTAT, NR_MICI, APROAPE_SORTAT};
    const std::string AllTypesChar[] = {"random", "sortat", "invers_sortat", "nr_mici", "aproape_sortat"};
    const int Len[] = {10, 20, 50, 100, 1'000, 10'000, 100'000, 250'000, 500'000, 1'000'000, 2'500'000, 5'000'000, 10'000'000};
    const int RunsPerLen[] = {10000, 10000, 5000, 1000, 500, 10, 1, 1, 1, 1, 1, 1, 1};
    const int TypeCount = sizeof(AllTypes) / sizeof(AllTypes[0]);
    const int LenCount = sizeof(Len) / sizeof(Len[0]);
}

int* inputRandom(int size) {
    static std::random_device dev;
    static std::mt19937 mt(dev());
    static std::uniform_int_distribution<int> random(
        -std::numeric_limits<int>::max(),
        std::numeric_limits<int>::max()
    );

    int *v = new int[size];
    for(int i = 0; i < size; i++) {
        v[i] = random(mt);
    }

    return v;
}

int* inputSortat(int size) {
    int* rand = inputRandom(size);
    quickSort(rand, size);
    return rand;
}

int *inputInvSortat(int size) {
    int *sortat = inputSortat(size);
    int *v = new int[size];
    for(int i = 0; i < size / 2; i++) {
        v[i] = sortat[size-i-1];
    }
    delete[] sortat;
    return v;
}

int *inputNrMici(int size) {
    int* rand = inputRandom(size);
    for(int i = 0; i < size; i++) {
        rand[i] = rand[i] & 0xffff;
    }
    return rand;
}

void partialQuicksort(int v[], int st, int dr, int k) {
    if(dr-st <= 0) {
        return;
    }

    int pivot = hoarePartition(v, st, dr);

    quickSortWorker(v, st, pivot);
    if(pivot < k-1)
        quickSortWorker(v, pivot+1, dr);
}

int *inputAproapeSortat(int size) {
    int *rand = inputRandom(size);
    partialQuicksort(rand, 0, size-1, size * 4 / 5);
    return rand;
}

int* generareInput(int size, Inputset::Type tip) {
    switch(tip) {
        case Inputset::Type::RANDOM:
            return inputRandom(size);
        case Inputset::Type::SORTAT:
            return inputSortat(size);
        case Inputset::Type::INVERS_SORTAT:
            return inputInvSortat(size);
        case Inputset::Type::NR_MICI:
            return inputNrMici(size);
        case Inputset::Type::APROAPE_SORTAT:
            return inputAproapeSortat(size);
    }
}

