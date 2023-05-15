#include <vector>
#include <iostream>
#include <iomanip>
#include <limits>

using namespace std;

typedef long long ll;
struct node {
    int ref;
    int v_ref; 
};


//
// GLOBAL
//

int INF = numeric_limits<int>::max();
int n, m;
vector<vector<node>> G; // grafo
vector<int> R, S; int t = 0; // recorridos y start
vector<int> C, C_sum; int c = 0; int k = 0; // componentes y tamaño de cada una


//
// AUX
//

ll choose(int n, int k) {
    if (n < k) return 0;
    ll k_f = 1, n_f = 1;
    for (int  i = 2; i <= k; ++i) k_f *= i;
    for (int i = n; i > n-k; --i) n_f *= i;
    return n_f / k_f;
}


//
// SOLUCION
//

int puentes_aux(int v, int p) {
    R[v] = 1; t += 1; S[v] = t;
    int w, x, min = INF;
    for (int i = 0; i < G[v].size(); ++i) {
        w = G[v][i].ref;
        if (w == p || w == -1) continue; // es padre o la removimos
        if (R[w] == 1) {
            if (S[w] < S[v]) { // es back-edge
                x = S[w];
            } else { // es forward-edge
                continue;
            }
        } else {
            x = puentes_aux(w, v);
        }
        if (S[v] < x) { // en este caso la arista es puente
            G[v][i].ref = -1; // la 'removemos'
            G[w][G[v][i].v_ref].ref = -1;
        }
        if (x < min) {
            min = x;
        }
    }
    return min;
}
void rm_puentes() {
    for (int v = 0; v < n; ++v) {
        if (R[v] == 0) puentes_aux(v, -1);
    }   
}

void componente_aux(int v) {
    R[v] = 1; C[v] = c; k += 1;
    for (auto w : G[v]) {
        if (R[w.ref] == 1 || w.ref == -1) continue;
        componente_aux(w.ref);
    }
}
void componentes() {
    fill(R.begin(), R.end(), 0);
    for (int v = 0; v < n; ++v) {
        if (R[v] == 0) {
            componente_aux(v);
            C_sum.push_back(k);
            k = 0; c += 1;
        }
    }   
}

double solve() {
    rm_puentes();
    componentes();
    ll ganar = 0, total = choose(n, 2);
    for (auto c: C_sum) ganar += choose(c, 2);
    return 1 - (double) ganar / total;
}


//
// MAIN
//

int main(int argc, char** argv) {
    cin >> n >> m;
    G.resize(n, vector<node>());
    int v, w;
    for (int i = 0; i < m; ++i) {
        cin >> v >> w;
        v--; w--;
        G[v].emplace_back((node) {w, G[w].size()});
        G[w].emplace_back((node) {v, G[v].size()-1});
    }
    R.resize(n, 0);
    S.resize(n, 0);
    C.resize(n, -1);
    double res = solve();
    cout << setprecision(5) << res << endl;
    return 0;
}
