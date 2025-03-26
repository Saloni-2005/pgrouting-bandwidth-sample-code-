#include <boost/config.hpp>
#include <vector>
#include <iostream>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/properties.hpp>
#include <boost/graph/bandwidth.hpp>

int main(int, char*[])
{
    using namespace boost;
    using namespace std;
    
    // Define the graph type
    typedef adjacency_list<vecS, vecS, undirectedS,
        property<vertex_index_t, int>> Graph;
    
    typedef graph_traits<Graph>::vertex_descriptor Vertex;
    typedef graph_traits<Graph>::vertices_size_type size_type;
    
    // Define graph edges
    typedef std::pair<std::size_t, std::size_t> Pair;
    Pair edges[14] = {
        Pair(0, 3), // a-d
        Pair(0, 5), // a-f
        Pair(1, 2), // b-c
        Pair(1, 4), // b-e
        Pair(1, 6), // b-g
        Pair(1, 9), // b-j
        Pair(2, 3), // c-d
        Pair(2, 4), // c-e
        Pair(3, 5), // d-f
        Pair(3, 8), // d-i
        Pair(4, 6), // e-g
        Pair(5, 6), // f-g
        Pair(5, 7), // f-h
        Pair(6, 7)  // g-h
    };
    
    // Create graph with 10 vertices
    Graph G(10);
    for (int i = 0; i < 14; ++i)
        add_edge(edges[i].first, edges[i].second, G);
    
    // Get vertex index map
    property_map<Graph, vertex_index_t>::type index_map = get(vertex_index, G);
    
    // Calculate and output the total graph bandwidth
    cout << "Graph bandwidth: " << bandwidth(G) << endl;
    
    // Calculate and output individual vertex bandwidths
    graph_traits<Graph>::vertex_iterator vi, vi_end;
    for (tie(vi, vi_end) = vertices(G); vi != vi_end; ++vi) {
        cout << "Bandwidth of vertex " << *vi << ": " 
             << ith_bandwidth(*vi, G) << endl;
    }
    
    // Calculate and output edge sum (profile)
    cout << "Edge sum (profile): " << edgesum(G, index_map) << endl;
    
    // Create a custom vertex ordering to demonstrate bandwidth with different ordering
    std::vector<size_type> perm(num_vertices(G));
    // Reverse the default ordering as an example
    for (size_type i = 0; i < num_vertices(G); ++i)
        perm[i] = num_vertices(G) - i - 1;
    
    // Calculate bandwidth with custom ordering
    cout << "Bandwidth with custom ordering: " 
         << bandwidth(G, make_iterator_property_map(&perm[0], index_map, perm[0])) 
         << endl;
    
    // Calculate edge sum with custom ordering
    cout << "Edge sum with custom ordering: " 
         << edgesum(G, make_iterator_property_map(&perm[0], index_map, perm[0])) 
         << endl;
    
    return 0;
}