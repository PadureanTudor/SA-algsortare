#include <cstring>
#include <format>
#include <fstream>
#include <iostream>
#include <chrono>
#include <string>
#include <thread>

#include "generare_input.cpp"
#include "algoritmi.cpp"

void mainWorker(int inputTypeI) {
    static std::chrono::high_resolution_clock clock;

    std::string fileName = std::format("../../date/date_{}.csv", Inputset::AllTypesChar[inputTypeI]);
    std::ofstream fout(fileName);

    // Print header
    fout << "Run Length,";
    for(auto algorithm : Algs::AllChar) {
        fout << algorithm << ",";
    }
    fout << std::endl;

    // Oprim algoritmii daca o executie dureaza >30s
    bool isTimedOut[Algs::Count];
    for(int i = 0; i < Algs::Count; isTimedOut[i++] = false);

    for(int inputLenI = 0; inputLenI < Inputset::LenCount; inputLenI++) {
        int inputLen = Inputset::Len[inputLenI];
        fout << inputLen << ",";

        // Stocam timpul pentru toti algoritmii
        double totalTime[Algs::Count];
        for(int i = 0; i < Algs::Count; totalTime[i++] = 0);

        for(int runs = 0; runs < Inputset::RunsPerLen[inputLenI]; runs++) {
            int *input = generareInput(inputLen, Inputset::AllTypes[inputTypeI]);
            
            for(int i = 0; i < Algs::Count; i++) {
                if(isTimedOut[Algs::All[i]]) continue;
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

                if(elapsed_seconds > 30) {
                    isTimedOut[Algs::All[i]] = true;
                    totalTime[i] = 0;
                }
            }
            
            delete[] input;
        }

        for(int i = 0; i < Algs::Count; i++) {
            double avgTime = totalTime[i] / Inputset::RunsPerLen[inputLenI];
            if(avgTime > 1e-9)
                fout << avgTime << ",";
            else
                fout << "-" << ",";
        }

        fout << std::endl;
    }
    fout.close();
}

int main() {
    std::thread threads[Inputset::TypeCount];
    for(int inputTypeI = 0; inputTypeI < Inputset::TypeCount; inputTypeI++) {
        threads[inputTypeI] = std::thread(mainWorker, inputTypeI); 
    }
    for(int inputTypeI = 0; inputTypeI < Inputset::TypeCount; inputTypeI++) {
        threads[inputTypeI].join();
    }
}