#include <bits/stdc++.h>

using namespace std;

typedef pair<int, int> entry;
typedef list<entry> entrylist;

struct ccomp
{
    vector<int> nodi;
    int n_edges;
};

const pair<entrylist, entrylist> sol(const int);
void printsol(ofstream *, pair<entrylist, entrylist>);

bool **g;

// utils
bool **allocMatrix(const int);
void deallocMatrix(bool **, const int);
void printMatrix(bool **const, const int);
// utils per i grafi

vector<ccomp> cc(bool **const, const int, int &);
vector<int> getCC(const int *, const int, const int);
int getEdges(bool **const, const vector<int>, const int);

const double CUT_OFF = 0.7;

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
    vector<int> vertici;

    // graph is represented as an array of edges.
    // Since the graph is undirected, the edge
    // from src to dest is also edge from dest
    // to src. Both are counted as 1 edge here.
    vector<Edge> edge;
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
int kargerMinCut(struct Graph *graph, int &minSoFar, vector<Edge> &bestEdges)
{

    // Get data of given graph
    int V = graph->V;
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

        int random = rand() % V;
        int verticeRandom = graph->vertici[random];
        // Pick a random edge
        // int i = rand() % E;
        int j = rand() % V;
        while (g[verticeRandom][graph->vertici[j]] == false)
        {
            j++;
            j = j % V;
        }
        // Find vertices (or sets) of two corners
        // of current edge
        int subset1 = find(subsets, random);
        int subset2 = find(subsets, j);

        // If two corners belong to same subset,
        // then no point considering this edge
        if (subset1 == subset2)
            continue;

        // Else contract the edge (or combine the
        // corners of edge into one vertex)
        else
        {
            // printf("Contracting edge %d-%d\n",
            //        edge[i].src, edge[i].dest);
            vertices--;
            Union(subsets, subset1, subset2);
        }
    }

    // Now we have two vertices (or subsets) left in
    // the contracted graph, so count the edges between
    // two components and return the count.
    int cutedges = 0;
    vector<Edge> currentEdge;

    // Cycle on the vertexes to check if there is an edge between the two vertexes
    for (int k = 0; k < V; k++)
    {
        for (int l = k + 1; l < V; l++)
        {
            if (g[graph->vertici[k]][graph->vertici[l]] == true)
            {
                int subset1 = find(subsets, k);
                int subset2 = find(subsets, l);
                if (subset1 != subset2)
                {
                    struct Edge *e = new Edge();
                    e->src = graph->vertici[k];
                    e->dest = graph->vertici[l];
                    currentEdge.push_back(*e);
                    cutedges++;
                }
            }
        }
    }
    if (cutedges < minSoFar)
    {
        minSoFar = cutedges;
        bestEdges = currentEdge;
    }
    // free(currentEdge);
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
struct Graph *createGraph(int V, int E)
{
    Graph *graph = new Graph;
    graph->V = V;
    graph->E = E;
    return graph;
}

int main(int argc, char *argv[])
{
    ifstream in;
    in.open("input.txt");
    ofstream out("output.txt");

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
    struct Graph *graph = createGraph(N, M);
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

    const pair<entrylist, entrylist> S = sol(N);
    // ------------- FINE SOLUZIONE --------------

    printsol(&out, S);

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
const pair<entrylist, entrylist> sol(const int N)
{
    bool finish = false;

    entrylist As, Rs;

    while (!finish)
    {
        finish = true;
        int n_componenti;
        cout << "CCS" << endl;
        vector<ccomp> ccs = cc(g, N, n_componenti);
        #ifdef DEBUG
                cout << "le componenti connesse sono " << n_componenti << endl;
        #endif

        for (ccomp ccsingola : ccs)
        {
            vector<int> cc = ccsingola.nodi;
            // Qui avremo il numero di archi della CC
            int nEdges = ccsingola.n_edges;
            int edgeMax = cc.size() * (cc.size() - 1) / 2;
            if (edgeMax * CUT_OFF <= nEdges)
            {
                // HERE I ADD ALL THE EDGES
                for (int i = 0; i < cc.size(); i++)
                {
                    for (int j = i + 1; j < cc.size(); j++)
                    {
                        if (g[cc[i]][cc[j]] == false)
                        {
                            As.push_back(make_pair(cc[i], cc[j]));
                        }
                    }
                }
            }
            else
            {
                // If one time I broke the graph I have to repeat the process
                finish = false;
                struct Graph *graph = createGraph(cc.size(), cc.size() * (cc.size() - 1));
                graph->vertici = cc;
                int minSoFar = INT_MAX;
                vector<Edge> minEdge;
                for (int i = 0; i < cc.size() * cc.size(); i++)
                {
                    kargerMinCut(graph, minSoFar, minEdge);
                }
                // Print the midEdges
                cout << "Min cut found by Karger's randomized algo is "
                     << minSoFar << endl;
                for (int i = 0; i < minSoFar; i++)
                {
                    // I delete the edges found
                    cout << minEdge[i].src << " - " << minEdge[i].dest << endl;

                    Rs.push_back(make_pair(cc[minEdge[i].src], cc[minEdge[i].dest]));
                    g[minEdge[i].src][minEdge[i].dest] = false;
                    g[minEdge[i].dest][minEdge[i].src] = false;
                    
                }
            }
        }
    }

    return make_pair(As, Rs);
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

void printsol(ofstream *out, pair<entrylist, entrylist> S)
{

    // stampo la soluzione
    *out << S.first.size() << " " << S.second.size() << endl;

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

int ccdfs(bool **const, const int, const int, const int, int *);

// graph utilts
vector<ccomp> cc(bool **const g, const int N, int &n_componenti)
{

    // creo lo stack e lo riempio con tutti i nodi
    stack<int> s;
    for (int i = 0; i < N; i++)
        s.push(i);

    // definisco l'array IDs
    int *id = new int[N];
    n_componenti = 0;

    vector<int> edges;
    for (int i = 0; i < N; i++)
        id[i] = 0;

    // finché lo stack non è vuoto
    while (!s.empty())
    {
        // prendo il primo nodo
        int u = s.top();
        s.pop();

        if (id[u] == 0)
        {
            n_componenti++;
            edges.push_back(ccdfs(g, N, n_componenti, u, id) / 2);
        }
    }
    // vettore delle componenti connesse
    vector<ccomp> ccs;
    for (int i = 0; i < n_componenti; i++)
    {
        ccomp c;
        c.n_edges = edges[i];
        ccs.push_back(c);
    }

    // riempio le cc
    for (int i = 0; i < N; i++)
        ccs[id[i] - 1].nodi.push_back(i);
    return ccs;
}

int ccdfs(bool **const g, const int N, const int conta, const int node, int *id)
{
    int edges = 0;
    id[node] = conta;
    for (int i = 0; i < N; i++)
    {
        if (g[node][i])
        {
            if (id[i] == 0)
            {
                edges += 1 + ccdfs(g, N, conta, i, id);
            }
            else if (conta == id[i])
                edges++;
        }
    }
    return edges;
}

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