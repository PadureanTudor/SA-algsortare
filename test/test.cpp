#include "../src/algoritmi.cpp"
#include "../src/generare_input.cpp"
int main() {
    const int INPUT_SIZE = 10000;
    int *input;
    if(TEST_ALG_TYPE == Algs::Type::COUNT_SORT)
        input = generareInput(INPUT_SIZE, Inputset::Type::NR_MICI);
    else
        input = generareInput(INPUT_SIZE, Inputset::Type::RANDOM);
    task(input, INPUT_SIZE, TEST_ALG_TYPE);

    for(int i = 0; i < INPUT_SIZE-1; i++) {
        if(input[i] > input[i+1]) {
            return 1;
        }
    }
    delete[] input;
    return 0;
}