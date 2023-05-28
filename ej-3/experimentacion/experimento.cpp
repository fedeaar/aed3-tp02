#include <chrono>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <bits/stdc++.h>
#include <tuple>

#include "./algoritmos/modems.h"

using namespace std;


#if   SRC == 1
    #define PATH "./out/runtime_denso.csv"
#elif SRC == 2
    #define PATH "./out/runtime_dsu.csv"
#elif SRC == 3
    #define PATH "./out/runtime_dsu_ingenuo.csv"
#else
    #define PATH "./out/runtime.csv"
#endif


//
// VARIABLES
//

#define REPEAT 10
#define START 1000
#define STOP 10000
#define STEP 1000


//
// MEDICION
//

vector<int> read_input(int size) {
    vector<int> input(size); string file_name = "./in/input_" + to_string(size);
    cout << file_name << endl;
    ifstream read_file(file_name);
    for (int i=0; i<size; i++) read_file >> input[i];
    read_file.close();
    return input;
}

double measure(vector<pair<int, int>>& G, int n, int r, int w, int u, int v) {
    auto start = chrono::high_resolution_clock::now();
    modems(G, n, r, w, u, v);
    auto stop = chrono::high_resolution_clock::now();
    chrono::duration<double> diff = stop - start;
    return diff.count();
}


//
// MAIN
//

int main(int argc, char** argv) {
    int repeat = REPEAT;
    ofstream output_file; output_file.open(PATH);
    output_file << "n,time\n";

    for (int n = START; n <= STOP; n += STEP) {
        vector<int> input = read_input(n);
        vector<pair<int,int>> G;
        for (int i = 0; i < n-1; i+= 2) {
            G.push_back(make_pair(input[i], input[i + 1]));
        }
        double counter = 0;
        for (int ignore=0; ignore<repeat; ignore++) {
            counter += measure(G, n, 1, n/2, 5, 5);
        }
        double avg = counter / repeat;
        output_file << n << "," << avg << endl;
        cout << n << ": " << avg << endl;
    }

    output_file.close();
    return 0;
}
