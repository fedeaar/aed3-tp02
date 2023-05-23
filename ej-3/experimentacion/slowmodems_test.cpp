#include <chrono>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <bits/stdc++.h>
#include <tuple>
using namespace std;

typedef pair<int,int> pos;
vector<tuple<double, bool, int, int>>E;
int N, R, W, U, V;
double s_utp = 0;
double s_fo = 0;

vector<int> read_input(int size) {
    vector<int> input(size); string file_name = "inputs/input_" + to_string(size);
    ifstream read_file(file_name);
    for (int i=0; i<size; i++) read_file >> input[i];
    read_file.close();
    return input;
}

double distancia(pos z, pos w) {
    int x = z.first - w.first;
    int y = z.second - w.second;
    double dist = pow(x, 2) + pow(y, 2);
    return sqrt(dist);
}

void crear_E(vector<pos>& G) {
    for (int i = 0; i < N; i++) {
        for (int j = i + 1; j < N; j++) {
            double dist = distancia(G[i], G[j]);
            double costo;
            bool esFO;
            if (dist <= R) {
                costo = dist * U;
                esFO = false;
            }
            else {
                costo = dist * V;
                esFO = true;
            }
            E.push_back(make_tuple(costo, esFO, i, j));
        }
    }
}

struct DSU{

    DSU(int n){
        hijos.resize(n, {});
        padre = vector<int>(n);
        for(int v = 0; v < n; v++) padre[v] = v;
    }

    int find(int v){
        return padre[v];
    }

    void unite(int u, int v){
        u = find(u), v = find(v);
        padre[v] = u;
        hijos[u].push_back(v);
        for (int i = 0; i < hijos[v].size(); i++) {
            hijos[u].push_back(hijos[v][i]);
        }
        hijos[v] = {};
    }

    vector<int> padre;
    vector<vector<int>> hijos;

};


void kruskal() {
    sort(E.begin(), E.end());
    int aristas = 0;
    DSU dsu(N);
    for (auto tup: E) {
        if (aristas >= N - W) break;

        double c = get<0>(tup);
        bool fo = get<1>(tup);
        int u = get<2>(tup);
        int v = get<3>(tup);
        if (dsu.find(u) != dsu.find(v)) {
            dsu.unite(u, v);
            aristas++;
            s_utp += c*(1-fo);
            s_fo += c*fo;
        }
    }
}

double measure(vector<pos>& G, int n) {
    auto start = chrono::high_resolution_clock::now();

    s_utp = 0;
    s_fo = 0;
    E = {};

    crear_E(G);
    kruskal();

    auto stop = chrono::high_resolution_clock::now();
    chrono::duration<double> diff = stop - start;
    return diff.count();
}

int main() {
    int repeat = 6;
    ofstream output_file; output_file.open("runtime_DSU_suboptimo.csv");
    output_file << "n,time\n";

    int limit = 10000;
    for (int n=1000; n<=limit; n+=1000) {
        vector<int> input = read_input(n);
        vector<pos> G;
        for (int i = 0; i < n-1; i+= 2) {
            G.push_back(make_pair(input[i], input[i + 1]));
        }
        N = n/2; R = 1; W = n/8; U = 5; V = 5;
        double counter = 0;
        for (int ignore=0; ignore<repeat; ignore++) counter += measure(G, n);

        output_file << n << "," << counter / repeat << endl;
        cout << n << "," << counter / repeat << endl;
    }

    output_file.close();
    return 0;
}
