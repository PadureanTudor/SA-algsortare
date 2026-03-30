#include <algorithm>
#include <cstring>
#include <format>
#include <fstream>
#include <iostream>
#include <chrono>
#include <string>

#include "generare_input.cpp"
#include "algoritmi.cpp"

int main() {
    static std::chrono::high_resolution_clock clock;

    for(int inputTypeI = 0; inputTypeI < Inputset::TypeCount; inputTypeI++) {
        std::string fileName = std::format("../../date/date_{}.csv", Inputset::AllTypesChar[inputTypeI]);
        std::ofstream fout(fileName);

        // Print header
        fout << "Run Length,";
        for(auto algorithm : Algs::AllChar) {
            fout << algorithm << ",";
        }
        fout << std::endl;

        // Oprim algoritmii daca o executie dureaza >30s
        bool shouldRun[Algs::Count];
        for(int i = 0; i < Algs::Count; shouldRun[i++] = true);

        for(int inputLenI = 0; inputLenI < Inputset::LenCount; inputLenI++) {
            int inputLen = Inputset::Len[inputLenI];
            fout << inputLen << ",";

            // Stocam timpul pentru toti algoritmii
            double totalTime[Algs::Count];
            for(int i = 0; i < Algs::Count; totalTime[i++] = 0);

            for(int runs = 0; runs < Inputset::RunsPerLen[inputLenI]; runs++) {
                int *input = generareInput(inputLen, Inputset::AllTypes[inputTypeI]);
                
                for(int i = 0; i < Algs::Count; i++) {
                    if(!shouldRun[Algs::All[i]]) continue;
                    if(Algs::All[i] == Algs::Type::COUNT_SORT 
                        && Inputset::AllTypes[inputTypeI] != Inputset::NR_MICI)
                        continue; // Rulam count sort doar pt nr mici

                    int *input_aux = new int[inputLen];
                    memcpy(input_aux, input, sizeof(int) * inputLen);

                    auto start = clock.now();
                    
                    task(input_aux, inputLen, Algs::All[i]);
                    
                    auto end = clock.now();
                    auto elapsed_seconds = std::chrono::duration<double>(end - start).count();
                    totalTime[i] += elapsed_seconds;
                    
                    delete[] input_aux;

                    if(elapsed_seconds > 30) {
                        shouldRun[Algs::All[i]] = false;
                        totalTime[i] = 0;
                    }
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