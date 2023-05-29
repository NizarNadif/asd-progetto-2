// // Structure to represent an edge
// struct Edge
// {
//     int src, dest;
// };

// // Function to find the parent of a vertex
// int findParent(vector<int> &parent, int i)
// {
//     if (parent[i] == i)
//         return i;
//     return findParent(parent, parent[i]);
// }

// // Function to do union of two subsets
// void unionSets(vector<int> &parent, int x, int y)
// {
//     int xset = findParent(parent, x);
//     int yset = findParent(parent, y);
//     parent[xset] = yset;
//     cout << "Parent of " << x << " is " << y << endl;
// }

// int isNear(int u, int v, vector<int> &vertexIndices, bool **graph, const vector<int> &vertices, vector<int> &parent)
// {
//     int attuale = v;
//     do
//     {
//         if (graph[vertices[u]][vertices[attuale]] && vertexIndices[attuale] != -1)
//         {
//             return attuale;
//             break;
//         }
//         attuale = parent[attuale];
//     } while (attuale != parent[attuale]);
//     if (graph[vertices[u]][vertices[attuale]] && vertexIndices[attuale] != -1)
//     {
//         return attuale;
//     }
//     return -1;
// }

// // Function to find the minimum cut in the graph
// int kargerSteinMinCut(bool **graph, vector<int> &parent, vector<Edge> &cutEdges, int V, const vector<int> &vertices)
// {
//     vector<int> vertexIndices(V); // Array to store the indices of the vertices

//     // Initially, there are V vertices in the contracted graph
//     for (int i = 0; i < V; i++)
//         vertexIndices[i] = i;

//     int numVertices = V;

//     // Keep contracting vertices until there are only 2 vertices left
//     while (numVertices > 2)
//     {
//         // Randomly select a vertex
//         int u;
//         do
//         {

//             u = rand() % V;
//         } while (vertexIndices[u] == -1);
//         cout << "U: " << u << endl;
//         // Random select a neighbor of u in the graph graph
//         int v = 100;
//         int finalParent = 100;
//         for (int i = 0; i < V; i++)
//         {
//             int near = isNear(u, i, vertexIndices, graph, vertices, parent);
//             if (near != -1)
//             {
//                 v = i;
//                 finalParent = near;
//                 break;
//             }
//             // if (graph[vertices[u]][vertices[i]] && vertexIndices[i] != -1) {
//             //     v = i;
//             //     break;
//             // }
//         }
//         cout << "Vicino; " << v << endl;
//         cout << "FinalParent; " << finalParent << endl;

//         // int v = 0;
//         // int count = 0;
//         // while (count != u) {
//         //     if (vertexIndices[v] != -1)
//         //         count++;
//         //     v++;
//         // }
//         // v--;
//         cout << "V: " << v << " U: " << u << endl;
//         sleep(0.5);
//         // If both vertices are still in the graph, contract the edge
//         if (vertexIndices[u] != -1 && vertexIndices[finalParent] != -1)
//         {

//             numVertices--;
//             unionSets(parent, u, finalParent);

//             // Mark v as removed from the graph
//             vertexIndices[finalParent] = -1;

//             // Store the contracted edge
//             cutEdges.push_back({u, v});
//         }
//     }

//     // Count the number of crossing edges
//     int cutCount = 0;
//     for (int i = 0; i < V; i++)
//     {
//         if (vertexIndices[i] != -1)
//         {
//             for (int j = i + 1; j < V; j++)
//             {
//                 if (vertexIndices[j] != -1 && graph[i][j])
//                     cutCount++;
//             }
//         }
//     }

//     return cutCount;
// }

// // Function to find the minimum cut in a graph for a given list of vertices
// int kargerStein(bool **graph, int V, const vector<int> &vertices, vector<Edge> &cutEdges)
// {
//     // Create parent array for union-find operations
//     vector<int> parent(V);
//     for (int i = 0; i < V; i++)
//         parent[i] = i;

//     // Run the Karger-Stein algorithm multiple times to improve the chances of finding the minimum cut
//     int minCut = INT_MAX;
//     int iterations = V * V; // Maximum number of iterations for reliable results

//     for (int i = 0; i < 1; i++)
//     {
//         srand(time(NULL));         // Initialize random seed
//         vector<Edge> currCutEdges; // Store the edges forming the current cut

//         int cutCount = kargerSteinMinCut(graph, parent, currCutEdges, V, vertices);
//         if (cutCount < minCut && cutEdges.size() <= vertices.size())
//         {
//             bool allVerticesFound = true;
//             for (const auto &vertex : vertices)
//             {
//                 int vertexIndex = findParent(parent, vertex);
//                 if (vertexIndex != vertices[0])
//                 {
//                     allVerticesFound = false;
//                     break;
//                 }
//             }

//             if (allVerticesFound)
//             {
//                 minCut = cutCount;
//                 cutEdges = currCutEdges;
//             }
//         }
//     }
//     cout << "Returning: " << minCut << endl;
//     return minCut;
// }
