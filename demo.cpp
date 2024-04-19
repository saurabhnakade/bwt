#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <chrono>
#include <cstdlib>
#include <fstream> 

#include "bwt.hpp"

using namespace std;

#define NOW() chrono::high_resolution_clock::now()

string bwt_cpu(const string sequence) {
    const size_t n = sequence.size();
    const char* c_sequence = sequence.c_str();

    vector<int> table(n);

    for (size_t i = 0; i < n; i++){
        table[i] = i;
    }

    list<int> sorted_table(table.begin(), table.end());
    sorted_table.sort([c_sequence,n](const int& a, const int& b) -> bool {
        for(size_t i = 0; i < n; i++) {
            if(c_sequence[(a + i) % n] != c_sequence[(b + i) % n]) {
                return c_sequence[(a + i) % n] < c_sequence[(b + i) % n];
            }
        }
        return false;
    });
    

    string transformed_sequence;


    for(auto r = sorted_table.begin(); r != sorted_table.end(); ++r){
        transformed_sequence += c_sequence[(n + *r - 1) % n];
    }
    return transformed_sequence;
}




int main(int argc, char const *argv[])
{
    // string alphabet("ATCG");
    // const int N = (argc > 1) ? atoi(argv[1]) : 1E6;
    // cout << "running sample of " << N << endl;
    // char* sequence = (char*) malloc((N+1) * sizeof(char));
    // for (size_t i = 0; i < N; i++) {
    //     sequence[i] = alphabet[rand() % alphabet.size()];
    // }
    // sequence[N] = ETX;

    string filename = "input.txt"; 
    ifstream inputFile(filename);
    if (!inputFile.is_open()) {
        cerr << "Error opening file " << filename << endl;
        return 1;
    }

    string sequence;
    char c;
    while (inputFile.get(c)) {
        sequence.push_back(c);
    }
    sequence.push_back(ETX);

    
    cout << "running cpu version..." << endl;
    auto start = NOW();
    auto cpu_seq = bwt_cpu(sequence);

    auto cpu_time = chrono::duration_cast<chrono::milliseconds>(NOW() - start);

    cout << "running gpu version..." << endl;
    start = NOW();
    auto gpu_seq = bwt(sequence);
    auto gpu_time = chrono::duration_cast<chrono::milliseconds>(NOW() - start);

    cout << "cpu version: " << cpu_time.count() << "ms" << endl;
    cout << "gpu version: " << gpu_time.count() << "ms" << endl;

    string outputFilename = "gpu_output.txt"; 
    ofstream outputFile(outputFilename);
    if (!outputFile.is_open()) {
        cerr << "Error opening output file " << outputFilename << endl;
        return 1;
    }

    outputFile << gpu_seq << endl;

    outputFile.close();
    cout << "GPU version output written to " << outputFilename << endl;


    if(cpu_seq.compare(gpu_seq) == 0) {
        cout << "outputs match!" << endl;
    } else {
        cout << "uh oh, outputs mismatch, something went wrong!" << endl;
    }

    return 0;
}
