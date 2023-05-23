#include <iostream>
#include <vector>
#include <bits/stdc++.h>
#include <tuple>
#include <limits>


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

int main(int argc, char** argv) {
    int c;
    cin >> c;
    for (int k = 0; k < c; k ++) {
        cin >> N >> R >> W >> U >> V;
        distancias_min = {};
        esRepresentante = {};
        s_utp = 0;
        s_fo = 0;
        vector<pos> G;
        ADJ = {};
        esRepresentante.resize(N, true);
        int x, y;
        for (int i = 0; i < N; i++) {
            cin >> x >> y;
            G.push_back(make_pair(x,y));
        }
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
        cout << "Caso #" << k+1 << ": ";
        cout <<  setprecision(3) << fixed << s_utp << " " << s_fo << endl;
    }
}