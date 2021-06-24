/**
 *  @author Tolga İnkaya
 */

#include "../graph.hpp"

using namespace gp;

void BellmanFord(Graph graph, int src) 
{ 
    int V = graph.size(); 
    int dist[V]; 
    int i, j, k, u, v, weight;
  
    // Step 1: Initialize distances from src to all other vertices 
    // as INFINITE 
    for (i = 0; i < V; i++) 
        dist[i] = INF; 
    dist[src] = 0; 

    for (i = 1; i <= V - 1; i++) { 
        for (j = 0; j < V; j++) {
            for(k = 0; k < V; k++) {
                u = j; 
                v = k; 
                weight = graph(j, k); 
                if (dist[u] != INF && dist[u] + weight < dist[v] && weight > 0) 
                    dist[v] = dist[u] + weight; 
            } 
        } 
    } 
  
    return; 
} 