#include <iostream>
#include <fstream>
#include <utility>
#include <list>
#include <iomanip>
#include <bits/stdc++.h>

using namespace std;

typedef pair<int, int> entry;
typedef list<entry> entrylist;

const pair<entrylist, entrylist> sol(bool **const, const int, int &, int &);
void printsol(ofstream *, int, int, pair<entrylist, entrylist>);

// utils
bool **allocMatrix(const int);
void deallocMatrix(bool **, const int);
void printMatrix(bool **const, const int);

int N, M;

// a structure to represent a unweighted edge in graph
struct Edge
{
    int src, dest;
};
 
// a structure to represent a connected, undirected
// and unweighted graph as a collection of edges.
struct Graph
{
    // V-> Number of vertices, E-> Number of edges
    int V, E;
 
    // graph is represented as an array of edges.
    // Since the graph is undirected, the edge
    // from src to dest is also edge from dest
    // to src. Both are counted as 1 edge here.
    Edge* edge;
};
 
// A structure to represent a subset for union-find
struct subset
{
    int parent;
    int rank;
};
 
// Function prototypes for union-find (These functions are defined
// after kargerMinCut() )
int find(struct subset subsets[], int i);
void Union(struct subset subsets[], int x, int y);
 
// A very basic implementation of Karger's randomized
// algorithm for finding the minimum cut. Please note
// that Karger's algorithm is a Monte Carlo Randomized algo
// and the cut returned by the algorithm may not be
// minimum always
int kargerMinCut(struct Graph* graph)
{
    // Get data of given graph
    int V = graph->V, E = graph->E;
    Edge *edge = graph->edge;
 
    // Allocate memory for creating V subsets.
    struct subset *subsets = new subset[V];
 
    // Create V subsets with single elements
    for (int v = 0; v < V; ++v)
    {
        subsets[v].parent = v;
        subsets[v].rank = 0;
    }
 
    // Initially there are V vertices in
    // contracted graph
    int vertices = V;
 
    // Keep contracting vertices until there are
    // 2 vertices.
    while (vertices > 2)
    {
       // Pick a random edge
       int i = rand() % E;
 
       // Find vertices (or sets) of two corners
       // of current edge
       int subset1 = find(subsets, edge[i].src);
       int subset2 = find(subsets, edge[i].dest);
 
       // If two corners belong to same subset,
       // then no point considering this edge
       if (subset1 == subset2)
         continue;
 
       // Else contract the edge (or combine the
       // corners of edge into one vertex)
       else
       {
          printf("Contracting edge %d-%d\n",
                 edge[i].src, edge[i].dest);
          vertices--;
          Union(subsets, subset1, subset2);
       }
    }
 
    // Now we have two vertices (or subsets) left in
    // the contracted graph, so count the edges between
    // two components and return the count.
    int cutedges = 0;
    for (int i=0; i<E; i++)
    {
        int subset1 = find(subsets, edge[i].src);
        int subset2 = find(subsets, edge[i].dest);
        if (subset1 != subset2) {
            cout << "Final contraction: " << edge[i].src << " - " << edge[i].dest << endl;
            cutedges++;
        }
          
    }
 
    return cutedges;
}
 
// A utility function to find set of an element i
// (uses path compression technique)
int find(struct subset subsets[], int i)
{
    // find root and make root as parent of i
    // (path compression)
    if (subsets[i].parent != i)
      subsets[i].parent =
             find(subsets, subsets[i].parent);
 
    return subsets[i].parent;
}
 
// A function that does union of two sets of x and y
// (uses union by rank)
void Union(struct subset subsets[], int x, int y)
{
    int xroot = find(subsets, x);
    int yroot = find(subsets, y);
 
    // Attach smaller rank tree under root of high
    // rank tree (Union by Rank)
    if (subsets[xroot].rank < subsets[yroot].rank)
        subsets[xroot].parent = yroot;
    else if (subsets[xroot].rank > subsets[yroot].rank)
        subsets[yroot].parent = xroot;
 
    // If ranks are same, then make one as root and
    // increment its rank by one
    else
    {
        subsets[yroot].parent = xroot;
        subsets[xroot].rank++;
    }
}
 
// Creates a graph with V vertices and E edges
struct Graph* createGraph(int V, int E)
{
    Graph* graph = new Graph;
    graph->V = V;
    graph->E = E;
    graph->edge = new Edge[E];
    return graph;
}

int main(int argc, char *argv[])
{
    ifstream in;
    in.open("input.txt");
    ofstream out("output.txt");

    bool **g;
    in >> N >> M;

#ifdef IMG
    // inizio a stampare lo scheletro del grafo
    ofstream dot;
    dot.open("graph.dot");
    dot << "strict graph {\n";
    // beatufiy=true; aggiungere per avere un grafo che gira attorno all'origine
    for (int i = 0; i < N; i++)
        dot << i << ";\n";
#endif

    // inizializzo il grafo
    g = allocMatrix(N);
    struct Graph* graph = createGraph(N, M);
    // defaults
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < i; j++)
        {
            if (i == j)
            {
                g[i][j] = true;
            }
            else
            {
                g[i][j] = false;
                g[j][i] = false;
            }
        }
    }

    for (int i = 0; i < M; i++)
    {
        // NB: il grafo non è orientato
        int u, v;
        in >> u >> v;
        g[u][v] = true;
        g[v][u] = true;
        graph->edge[i].src = u;
        graph->edge[i].dest = v;


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

    // int A = 0, R = 0;
    // const pair<entrylist,entrylist> S = sol(g, N, A, R);
    // printsol(&out, A, R, S);
    vector<int> verticesToCut; // List of vertices to apply the algorithm for
    for (int i = 0; i < N; i++)
    {
        verticesToCut.push_back(i);
    }
    vector<Edge> cutEdges;
    int minCut = kargerMinCut(graph);

    cout << "Minimum cut found by Karger-Stein algorithm: " << minCut << endl;
    cout << "Edges forming the minimum cut: " << endl;
    for (const auto &edge : cutEdges)
    {
        cout << edge.src << " -- " << edge.dest << endl;
    }

    // ------------- FINE SOLUZIONE --------------

#ifdef IMG
    for (entry couple : S.first)
    {
        dot << couple.first << " -- " << couple.second << " [color=green]" << endl;
    }

    for (entry couple : S.second)
    {
        dot << couple.first << " -- " << couple.second << " [style=dashed,color=red]" << endl;
    }

    dot << "}" << endl;
    dot.close();
#endif

    // dealloco la memoria e chiudo gli streams
    // deallocMatrix(g, N);
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
const pair<entrylist, entrylist> sol(bool **const g, const int N, int &A, int &R)
{
    entrylist As, Rs;
    return dummysol(N);
}

const pair<entrylist, entrylist> dummysol(const int N)
{
    entrylist As, Rs;

    // As e Rs a caso
    for (int i = 0; i < N / 2; i++)
        As.push_back(make_pair(i, N - i - 1));
    for (int i = N / 2; i > 0; i--)
        Rs.push_back(make_pair(i, N / 2 + i - 1));

    return make_pair(As, Rs);
};

void printsol(ofstream *out, int A, int R, pair<entrylist, entrylist> S)
{
    // stampo la soluzione
    *out << A << " " << R << endl;

    for (entry couple : S.first)
    {
        *out << "+ " << couple.first << " " << couple.second << endl;
    }

    for (entry couple : S.second)
    {
        *out << "- " << couple.first << " " << couple.second << endl;
    }

    // chiudo la stampa
    *out << "***" << endl;
}

// ----------------------------- UTILS -----------------------------
bool **allocMatrix(const int N)
{
    bool **matrix = new bool *[N];
    for (int i = 0; i < N; i++)
        matrix[i] = new bool[N];
    return matrix;
}

void deallocMatrix(bool **matrix, const int N)
{
    for (int i = 0; i < N; i++)
        delete[] matrix[i];
    delete[] matrix;
}

void printMatrix(bool **const matrix, const int N)
{
    cout << endl
         << setw(4) << "";
    for (int i = 0; i < N; i++)
        cout << setw(3) << i;
    cout << endl
         << setw(3) << ""
         << "╭";
    for (int i = 0; i < N; i++)
        cout << "───";
    cout << "──╮" << endl;

    for (int i = 0; i < N; i++)
    {
        cout << " " << i << " │";
        for (int j = 0; j < N; j++)
            cout << "  " << (matrix[i][j] ? "\x1B[31mx\033[0m" : "-");
        cout << endl;
    }

    cout << setw(3) << ""
         << "╰─" << endl;
}