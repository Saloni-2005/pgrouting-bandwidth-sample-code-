#include <boost/config.hpp>
#include <iostream>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/bandwidth.hpp>

int main()
{
    using namespace boost;
    using namespace std;
    
    // Define the graph type
    typedef adjacency_list<vecS, vecS, undirectedS,
        property<vertex_index_t, int>> Graph;
    
    // Define graph edges based on the provided image
    // Note: Converting from 1-indexed (in image) to 0-indexed (for code)
    typedef std::pair<std::size_t, std::size_t> Pair;
    Pair edges[] = {
        // Horizontal connections
        Pair(0, 1),  // 1-2
        Pair(1, 2),  // 2-3
        Pair(3, 4),  // 4-5
        Pair(4, 5),  // 5-6
        Pair(7, 8),  // 8-9
        Pair(8, 9),  // 9-10
        
        // Vertical connections
        Pair(0, 3),  // 1-4
        Pair(1, 4),  // 2-5
        Pair(2, 5),  // 3-6
        Pair(3, 6),  // 4-7
        Pair(4, 7),  // 5-8
        Pair(5, 8)   // 6-9
    };
    
    Graph G(10);
    for (const auto& edge : edges)
        add_edge(edge.first, edge.second, G);
    
    // Calculate and output the graph bandwidth
    cout << "Graph bandwidth: " << bandwidth(G) << endl;
    
    return 0;
}
