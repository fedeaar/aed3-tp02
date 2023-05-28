#include "../modems.h"


//
// GLOBAL
//

typedef pair<int,int> pos;
vector<tuple<double, bool, int, int>>E;
int N, R, W, U, V;
double s_utp = 0;
double s_fo = 0;


//
// AUX
//

double distancia(pos z, pos w) {
    int x = z.first - w.first;
    int y = z.second - w.second;
    double dist = pow(x, 2) + pow(y, 2);
    return sqrt(dist);
}


//
// KRUSKAL (dsu)
//

struct DSU {

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


//
// MODEMS (dsu)
//

pair<double, double> modems(vector<pos> G, int n, int r, int w, int u, int v) {
    N = n, R = r, W = w, U = u, V = v;
    s_utp = 0;
    s_fo = 0;
    E = {};

    crear_E(G);
    kruskal();
    return {s_utp, s_fo};
}
