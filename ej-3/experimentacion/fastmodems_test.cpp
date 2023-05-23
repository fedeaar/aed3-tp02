#include <chrono>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <bits/stdc++.h>
#include <tuple>
using namespace std;

typedef pair<int,int> pos;
typedef tuple<double, int, int, bool> eje_pesado;

vector<vector<pair<double,bool>>> ADJ; // matriz de adyacencia pesada, indica también si es utp o fo.
int N, R, W, U, V;
double s_utp = 0;
double s_fo = 0;
double INF = numeric_limits<double>::max();
vector<double> distancias_min; // mínimas distancias a otros conjuntos disjuntos
vector<bool> esRepresentante; // refleja si el nodo actual es el representante de un conjunto

vector<int> read_input(int size) {
    vector<int> input(size); string file_name = "inputs/input_" + to_string(size);
    cout << file_name << endl;
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

void crear_ADJ(vector<pos>& G) {
    for (int i = 0; i < N; i++) {
        for (int j = i + 1; j < N; j++) { //empezamos de i + 1 porque marcamos en [i][j] y [j][i]
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
            ADJ[i][j] = make_pair(costo, esFO);
            ADJ[j][i] = make_pair(costo, esFO);
        }
    }
}

eje_pesado eje_minimo() {
    int representante = 0;
    while (!esRepresentante[representante]) representante++;
    for (int i = representante+1; i < N; i++) {
        if (esRepresentante[i] && distancias_min[i] < distancias_min[representante]) {
            representante = i; //Encuentra el nodo representante con menor peso a otro bosque
        }
    }
    int objetivo = 0;
    bool esFO;
    for (int j = 0; j < N; j++) {
        if (!esRepresentante[j]) continue;
        if (ADJ[representante][j].first == distancias_min[representante]) {
            objetivo = j;
            esFO = ADJ[representante][j].second;
            break; // encuentra el nodo correspondiente a ese representante
        }
    }
    return eje_pesado(distancias_min[representante], representante, objetivo, esFO);
}

void remover(eje_pesado e) {
    int u = get<1>(e);
    int v = get<2>(e);
    esRepresentante[v] = false;
    distancias_min[u] = INF;
    for (int i = 0; i < N; i++) {
        if (esRepresentante[i] && i != u) {
            //Como v es parte del conjunto de u, actualiza todos los demás enlaces a ver si v tiene uno mejor
            double nuevoCosto = min(ADJ[u][i].first, ADJ[v][i].first);
            ADJ[i][u].first = nuevoCosto;
            ADJ[u][i].first = nuevoCosto;
            if (ADJ[u][i].first > ADJ[v][i].first || (ADJ[u][i].first == ADJ[v][i].first && !ADJ[v][i].second)) {
                //Actualizamos si es utp o fo, dando prioridad a utp
                ADJ[u][i].second = ADJ[v][i].second;
                ADJ[i][u].second = ADJ[v][i].second;
            }
            distancias_min[u] = min(distancias_min[u], nuevoCosto);
        }
    }
}


void kruskal() {
    int aristas = 0;
    // La cantidad de modems equivale a la cantidad de componentes conexas de nuestro arbol.
    // Al ser bosque generador, si tiene w c.c, tiene n - w aristas
    while (aristas < N - W) {

        eje_pesado e = eje_minimo();
        bool esFO = get<3>(e);
        double costo = get<0>(e);
        s_fo += esFO*costo;
        s_utp += (1-esFO)*costo;
        remover(e);
        aristas++;
    }
}

double measure(vector<pos>& G, int n) {
    auto start = chrono::high_resolution_clock::now();

    distancias_min = {};
    esRepresentante = {};
    s_utp = 0;
    s_fo = 0;
    ADJ = {};
    esRepresentante.resize(N, true);

    vector<pair<double, bool>> VEC(N, make_pair(INF, false));
    ADJ.resize(N, VEC);
    crear_ADJ(G);
    distancias_min.resize(N, INF);
    for (int i = 0; i < N; i++) {
        for (int j = i+1; j < N; j++) {
            distancias_min[i] = min(distancias_min[i], ADJ[i][j].first);
        }
    }
    kruskal();

    auto stop = chrono::high_resolution_clock::now();
    chrono::duration<double> diff = stop - start;
    return diff.count();
}

int main() {
    int repeat = 6;
    ofstream output_file; output_file.open("runtime.csv");
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
        cout << n << counter / repeat << endl;
    }

    output_file.close();
    return 0;
}


