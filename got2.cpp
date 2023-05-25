#include <iostream>
#include <fstream>
#include <utility>
#include <list>
#include <iomanip>

using namespace std;

typedef pair<int,int> entry;
typedef list<entry> entrylist;

const pair<entrylist,entrylist> sol(bool **const, const int);

// utils
bool **allocMatrix(const int);
void deallocMatrix(bool **, const int);
void printMatrix(bool **const, const int);

// A = create, R = distrutte
int A = 0, R = 0;

int main (int argc, char *argv[]) {
    ifstream in;
    in.open("input.txt");
    ofstream out("output.txt");
    
    int N, M;
    bool **g;
    in >> N >> M;

    #ifdef IMG
    // inizio a stampare lo scheletro del grafo
    ofstream dot;
    dot.open("graph.dot");
    dot << "strict graph {\n";
    // beatufiy=true; aggiungere per avere un grafo che gira attorno all'origine
    for (int i=0; i<N; i++)
        dot << i << ";\n";
    #endif

    // inizializzo il grafo
    g = allocMatrix(N);

    // defaults
    for (int i=0; i<N; i++) {
        for (int j=0; j<i; j++) {
            if (i == j) {
                g[i][j] = true;
            } else {
                g[i][j] = false;
                g[j][i] = false;
            }
        }
    }

    for (int i=1; i<M; i++) {
        // NB: il grafo non è orientato
        int u, v;
        in >> u >> v;
        g[u][v] = true;
        g[v][u] = true;

        #ifdef IMG
        dot << u << " -- " << v << ";\n";
        #endif
    }

    // debug
    #ifdef DEBUG
    cout << setw(10) << setw(20) << "GRAFO INIZIALE" << endl;
    printMatrix(g, N);
    #endif

    // ---------------- SOLUZIONE ----------------
    const pair<entrylist,entrylist> S = sol(g, N);
    // ------------- FINE SOLUZIONE --------------

    // stampo la soluzione
    out << A << " " << R << endl;

    for (entry couple : S.first) {
        out << "+ " << couple.first << " " << couple.second << endl;
    }

    for (entry couple : S.second) {
        out << "- " << couple.first << " " << couple.second << endl;
    }
    
    // chiudo la stampa
    out << "***" << endl;

    #ifdef IMG
    for (entry couple : S.first) {
        dot << couple.first << " -- " << couple.second << " [color=green]" << endl;
    }

    for (entry couple : S.second) {
        dot << couple.first << " -- " << couple.second << " [style=dashed,color=red]" << endl;
    }

    dot << "}" << endl;
    dot.close();
    #endif

    // dealloco la memoria e chiudo gli streams
    deallocMatrix(g, N);
    in.close();
    out.close();
    return 0;
}

// ----------------------------- SOLUZIONE -----------------------------
const pair<entrylist, entrylist> dummysol(const int);
/**
 * @brief 
 * 
 * @param g grafo rappresentato mediante una matrice di booleani
 * @param N numero di nodi appartenenti al grafo
 * @return una coppia di liste (As e Rs), ognuna di esse contiene
 *  delle coppie di interi che rappresentano un arco aggiunto/eliminato
 */
const pair<entrylist,entrylist> sol(bool **const g, const int N) {
    entrylist As, Rs;
    return dummysol(N);
}

const pair<entrylist, entrylist> dummysol(const int N) {
    entrylist As, Rs;

    // As e Rs a caso
    for (int i=0; i<N/2; i++)
        As.push_back(make_pair(i, N-i-1));
    for (int i=N/2; i>0; i--)
        Rs.push_back(make_pair(i, N/2+i-1));

    return make_pair(As, Rs);
};


// ----------------------------- UTILS -----------------------------
bool **allocMatrix(const int N) {
    bool **matrix = new bool*[N];
    for (int i = 0; i<N; i++)
        matrix[i] = new bool[N];
    return matrix;
}

void deallocMatrix(bool **matrix, const int N) {
    for (int i = 0; i<N; i++)
        delete[] matrix[i];
    delete[] matrix;
}

void printMatrix (bool **const matrix, const int N) {
    cout << endl << setw(4) << "";
    for (int i=0; i<N; i++)
        cout << setw(3) << i;
    cout << endl << setw(3) << "" << "╭";
    for (int i=0; i<N; i++)
        cout << "───";
    cout << "──╮" << endl;

    for (int i=0; i<N; i++) {
        cout << " " << i << " │";
        for (int j=0; j<N; j++)
            cout << "  " << (matrix[i][j] ? "\x1B[31mx\033[0m" : "-");
        cout << endl;
    }

    cout << setw(3) << "" << "╰─" << endl;
}