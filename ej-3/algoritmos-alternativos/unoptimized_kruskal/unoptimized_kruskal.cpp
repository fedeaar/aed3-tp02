#include <vector>
#include <iostream>
#include <bits/stdc++.h>
#include <tuple>
using namespace std;

typedef pair<int,int> pos;
vector<tuple<double, bool, int, int>>E;
int N, R, W, U, V;
double s_utp = 0;
double s_fo = 0;

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
        // La cantidad de modems equivale a la cantidad de componentes conexas de nuestro arbol.
        // Al ser bosque generador, si tiene w c.c, tiene n - w aristas
        if (aristas >= N - W) break;

        double c = get<0>(tup);
        bool fo = get<1>(tup);
        int u = get<2>(tup);
        int v = get<3>(tup);
        //si (u,v) es arista segura
        if (dsu.find(u) != dsu.find(v)) {
            // agregar
            dsu.unite(u, v);
            aristas++;
            s_utp += c*(1-fo);
            s_fo += c*fo;
        }
    }
}

int main(int argc, char** argv) {
    int c;
    cin >> c;
    for (int k = 0; k < c; k ++) {
        s_utp = 0;
        s_fo = 0;
        E = {}; //Reiniciamos las variables globales para los siguientes casos
        vector<pos> G;
        cin >> N >> R >> W >> U >> V;
        int x, y;
        for (int i = 0; i < N; i++) {
            cin >> x >> y;
            G.push_back(make_pair(x,y));
        }
        crear_E(G);
        kruskal();
        cout << "Caso #" << k+1 << ": ";
        cout <<  setprecision(3) << fixed << s_utp << " " << s_fo << endl;
    }
}
