#include <format>
#include <fstream>
#include <iostream>
#include <chrono>
#include <string>

namespace Algs {
    enum Type {
        BUBBLE_SORT
    };
    const Type All[] = {BUBBLE_SORT};
    const std::string AllChar[] = {"Bubble Sort"};
    const int Count = sizeof(All) / sizeof(Type); 
}

#include "generare_input.cpp"
#include "algoritmi.cpp"

bool ordCrescatoare(int a, int b) {
    return a < b;
}

void task(int input[], int size, Algs::Type algoritm) {
    switch(algoritm) {
        case Algs::Type::BUBBLE_SORT:
            bubbleSort(input, size, ordCrescatoare);
            break;
        default:
            exit(1);
    }
}

int main() {
    static std::chrono::high_resolution_clock clock;

    for(int inputTypeI = 0; inputTypeI < Inputset::TypeCount; inputTypeI++) {
        std::string fileName = std::format("../date/date_{}.csv", Inputset::AllTypesChar[inputTypeI]);
        std::ofstream fout(fileName);

        // Print header
        fout << "Run Length,";
        for(auto algorithm : Algs::AllChar) {
            fout << algorithm << ",";
        }
        fout << std::endl;

        for(int inputLenI = 0; inputLenI < Inputset::LenCount; inputLenI++) {
            int inputLen = Inputset::Len[inputLenI];
            fout << inputLen << ",";

            // Stocam timpul pentru toti algoritmii
            double totalTime[Algs::Count];
            for(int i = 0; i < Algs::Count; totalTime[i++] = 0);

            for(int runs = 0; runs < Inputset::RunsPerLen[inputLenI]; runs++) {
                int *input = generareInput(inputLen, Inputset::AllTypes[inputTypeI]);
                
                for(int i = 0; i < Algs::Count; i++) {
                    auto start = clock.now();
                    
                    task(input, inputLen, Algs::All[i]);

                    auto end = clock.now();
                    auto elapsed_seconds = std::chrono::duration<double>(end - start).count();
                    totalTime[i] += elapsed_seconds;
                }
                
                delete[] input;
            }

            for(int i = 0; i < Algs::Count; i++) {
                double avgTime = totalTime[i] / Inputset::RunsPerLen[inputLenI];
                fout << avgTime << ",";
            }

            fout << std::endl;
        }
        fout.close();
    }    
}