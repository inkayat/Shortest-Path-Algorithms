/**
 *  Traveling Salesman
 *  @author Tolga İnkaya
 */

#ifndef __TSP__H
#define __TSP__H

#include "../graph.hpp"
#include <vector>
#include <algorithm>

using namespace gp;

template<typename T>
T __min(T a, T b)
{
    if(a<b) return a;
    return b;
}

int travllingSalesmanProblem(Graph graph, int s) 
{ 
    int V = graph.size();
    std::vector<int> vertex; 
    for (int i = 0; i < V; i++) 
        if (i != s) 
            vertex.push_back(i); 
  
    // store minimum weight Hamiltonian Cycle. 
    int min_path = INF; 
    do { 
  
        // store current Path weight(cost) 
        int current_pathweight = 0; 
          
        // compute current path weight 
        int k = s; 
        for (int i = 0; i < vertex.size(); i++) {
            if(graph(k, vertex[i]) > 0)
            {
                current_pathweight += graph(k, vertex[i]); 
                k = vertex[i]; 
            }
            else
            {
                current_pathweight = INF; 
                k = vertex[i]; 
            }
            
        }
        if(graph(k,s) > 0)
        {
            current_pathweight += graph(k, s); 
        }
        else
        {
            current_pathweight = INF; 
        }
        
        // update minimum 

        min_path = __min(min_path, current_pathweight); 

    } while (std::next_permutation(vertex.begin(), vertex.end())); 
  
    return min_path; 
} 

#endif