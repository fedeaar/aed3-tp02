#include <vector>
#include <iostream>
#include <bits/stdc++.h>
#include <tuple>
using namespace std;

typedef pair<int,int> pos;
vector<tuple<double, bool, int, int>>E;
int n, r, w, u, v;
double s_utp = 0;
double s_fo = 0;

double distancia(pos z, pos w) {
    int x = z.first - w.first;
    int y = z.second - w.second;
    double dist = pow(x, 2) + pow(y, 2);
    return sqrt(dist);
}

void crear_E(vector<pos>& G) {
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            double dist = distancia(G[i], G[j]);
            double costo;
            bool esFO;
            if (dist <= r) {
                costo = dist * u;
                esFO = false;
            }
            else {
                costo = dist * v;
                esFO = true;
            }
            E.push_back(make_tuple(costo, esFO, i, j));
        }
    }
}

struct DSU{

    DSU(int n){
        padre = rank = vector<int>(n);
        for(int v = 0; v < n; v++) padre[v] = v;
    }

    int find(int v){
        if(v == padre[v]) return v;
        return padre[v] = find(padre[v]);
    }

    void unite(int u, int v){
        u = find(u), v = find(v);
        if(u == v) return;
        if(rank[u] < rank[v]) swap(u,v);
        padre[v] = padre[u];
        rank[u] = max(rank[u],rank[v]+1);
    }

    vector<int> padre;
    vector<int> rank;
};

void kruskal() {
    sort(E.begin(), E.end());
    int aristas = 0;
    DSU dsu(n);
    for (auto tup: E) {
        // La cantidad de modems equivale a la cantidad de componentes conexas de nuestro arbol.
        // Al ser bosque generador, si tiene w c.c, tiene n - w aristas
        if (aristas >= n - w) break;

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
        cin >> n >> r >> w >> u >> v;
        vector<pos> G;
        int x, y;
        for (int i = 0; i < n; i++) {
            cin >> x >> y;
            G.push_back(make_pair(x,y));
        }
        crear_E(G);
        kruskal();
        cout << "Caso #" << k+1 << ": ";
        cout <<  setprecision(3) << s_utp << " " << s_fo << endl;
        E = {}; //Reiniciamos las variables globales para los siguientes casos
        s_fo = 0;
        s_utp = 0;
    }
}