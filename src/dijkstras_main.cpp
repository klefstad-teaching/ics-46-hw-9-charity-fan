#include "dijkstras.h"

int main() {
    Graph G = Graph();
    file_to_graph("src/small.txt", G);
    vector<int> previous(G.numVertices, UNDEFINED);
    vector<int> distances = dijkstra_shortest_path(G, 0, previous);

    vector<int> path0 = extract_shortest_path(distances, previous, 0);
    vector<int> path1 = extract_shortest_path(distances, previous, 1);
    vector<int> path2 = extract_shortest_path(distances, previous, 2);
    vector<int> path3 = extract_shortest_path(distances, previous, 3);

    print_path(path0, distances[0]);
    print_path(path1, distances[1]);
    print_path(path2, distances[2]);
    print_path(path3, distances[3]);

    return 0;
}

// g++ -std=c++20 src/dijkstras.cpp src/dijkstras_main.cpp -o d_main
