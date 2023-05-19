#include <vector>
#include <iostream>
#include <stack>
#include <bits/stdc++.h>


using namespace std;
vector<vector<int>> D; // digrafo
vector<vector<int>> D_trans; // digrafo transpuesto
vector<int> Pila; // pila para kosaraju
vector<bool> marcados; // representa si el dfs marcó a este nodo
int minimo_cfc; // mínimo de la c.f.c actual
vector<pair<int, vector<int>>> F; // grafo de c.f.c
vector<int> indice_en_F; // posición en F a la que corresponde
int identificador_cfc = 0;
vector<int> solucion;
int n, m;

void DFS_stacker(int v) {
    //Apila los nodos recorridos en orden inverso
    marcados[v] = true;
    for (int w : D[v]) {
        if (marcados[w]) continue;
        else {
            DFS_stacker(w);
        }
    }
    Pila.push_back(v);
}
void DFS_trans(int v) {
    marcados[v] = true;
    minimo_cfc = min(v, minimo_cfc);
    indice_en_F[v] = identificador_cfc;
    for (int w : D_trans[v]) {
        if (marcados[w]) {
            //Si pertenecen a c.f.c distintas, hay arista de w a v porque D está transpuesto
            if (indice_en_F[v] != indice_en_F[w]) {
                F[indice_en_F[w]].second.push_back(identificador_cfc);
            }
        }
        else {
            DFS_trans(w);
        }
    }
}

void DFS_F(int v) {
    marcados[v] = true;
    for (int w : F[v].second) {
        if (marcados[w]) continue;
        else {
            DFS_F(w);
        }
    }
}

void bucket_sort(vector<pair<int,int>>& indices_d_in) {
    //Ordena en base al d_in de cada nodo de F
    vector<vector<pair<int,int>>> buckets(indices_d_in.size());
    for (int i = 0; i < indices_d_in.size(); i++) {
        buckets[indices_d_in[i].second].push_back(indices_d_in[i]);
    }
    int indice_actual = 0;
    for (int i = 0; i < buckets.size(); i++) {
        for (pair<int,int> p : buckets[i]) {
            indices_d_in[indice_actual] = p;
            indice_actual++;
        }
    }
}

void kosaraju() {
    for (int i = 0; i < n; i++) {
        if (!marcados[i]) {
            DFS_stacker(i);
        }
    }
    vector<bool> marcados_limpio(n, false);
    marcados = marcados_limpio;
    for (int i = Pila.size()-1; i >= 0; i--) {
        if (!marcados[Pila[i]]) {
            //Recorre la pila desde el tope, haciendo DFS y juntando la c.f.c en un nodo de F.
            minimo_cfc = Pila[i];
            DFS_trans(Pila[i]);
            F.emplace_back((pair<int, vector<int>>){minimo_cfc, vector<int>()});
            identificador_cfc++;
        }
    }
}

void encontrar_indices() {
    vector<pair<int,int>> indices_d_in(F.size(), make_pair(0,0)); // indices de F ordenados por grado de entrada
    for (int i = 0; i < F.size(); i++) {
        indices_d_in[i].first = i;
        for (int w : F[i].second) indices_d_in[w].second++;
    }
    sort(indices_d_in.begin(), indices_d_in.end());
    //bucket_sort(indices_d_in);
    vector<bool> marcados_limpio(F.size(), false);
    marcados = marcados_limpio;
    // Recorre los nodos de F en orden de d_in
    for (int i = 0; i < indices_d_in.size(); i++) {
        if (marcados[indices_d_in[i].first]) continue;
        else {
            solucion.push_back(F[indices_d_in[i].first].first);
            DFS_F(indices_d_in[i].first);
        }
    }
    sort(solucion.begin(), solucion.end());
}

int main(int argc, char** argv) {
    cin >> n >> m;
    D.resize(n, vector<int>());
    D_trans.resize(n, vector<int>());
    int v, w;
    for (int i = 0; i < m; ++i) {
        cin >> v >> w;
        v--; w--; //Restamos para poder trabajar desde 0 a n-1
        D[v].push_back(w);
        D_trans[w].push_back(v);
    }
    marcados.resize(n, false);
    indice_en_F.resize(n, -1);
    kosaraju();
    encontrar_indices();

    cout << solucion.size() << endl;
    for (int s : solucion) {
        cout << s+1 << " "; // Volvemos a sumar lo restado
    }
    cout << endl;
    return 0;
}
