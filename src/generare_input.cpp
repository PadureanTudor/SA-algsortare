#include <random>

// Pentru fiecare Type, executam fiecare Len pentru fiecare Algs::Type de RunsPerLen ori.
// Deci 4 for().
namespace Inputset {
    enum Type {
        RANDOM
    };
    const Type AllTypes[] = {RANDOM};
    const std::string AllTypesChar[] = {"random"};
    // const int Len[] = {10, 20, 50, 100, 1'000, 10'000, 100'000, 10'000'000};
    // const int RunsPerLen[] = {1000, 1000, 1000, 500, 500, 20, 10, 5};
    const int Len[] = {10, 20, 50, 10000};
    const int RunsPerLen[] = {10, 10, 1, 5};
    const int TypeCount = sizeof(AllTypes) / sizeof(AllTypes[0]);
    const int LenCount = sizeof(Len) / sizeof(Len[0]);
}

int* generareInput(int size, Inputset::Type tip) {
    static std::random_device dev;
    static std::mt19937 mt(dev());
    static std::uniform_int_distribution<int> random(
        -std::numeric_limits<int>::max(),
        std::numeric_limits<int>::max()
    );

    int *v = new int[size];
    for(int i = 0; i < size; i++) {
        v[i] =random(mt);
    }

    return v;
}
