/**
 *  Shortest path algorithm using dynamic programming
 *  @author Tolga İnkaya
 */

#include "../graph.hpp"
#include <vector>
#include <iostream>


void floydWarshall(gp::Graph graph)  
{  
    int v = graph.size();
    int dp[v][v], i, j, k;  
  
    for (i = 0; i < v; i++)  
        for (j = 0; j < v; j++)  
            std::cout << graph(i, j) << std::endl;

    for (i = 0; i < v; i++)  
        for (j = 0; j < v; j++)  
            dp[i][j] = graph(i,j);
  

    for (k = 0; k < v; k++)  
    {  
        for (i = 0; i < v; i++)  
        {  
            for (j = 0; j < v; j++)  
            {  
                if (graph(k,j) > 0 && graph(i, k) > 0 && dp[i][k] + dp[k][j] < dp[i][j])  
                    dp[i][j] = dp[i][k] + dp[k][j];  
            }  
        }  
    }  
  
}  