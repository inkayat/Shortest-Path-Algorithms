/*

#ifndef Dijkstra_h
#define Dijkstra_h


#include <iostream>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <vector>
#include <algorithm>

using namespace std;

void pathFinder(int number_of_node, vector< vector<int> > AdjMatrix, int source, 
              int destination, vector<int> *shortestPath, int *totalCost) {
    
    
    vector< vector<int> > AdjacencyMatrix;
    for (int i=0; i< number_of_node+1; i++)
    {    
        vector<int> temp;
        for (int j=0; j< number_of_node+1; j++)
            temp.push_back(AdjMatrix[i][j]);

        AdjacencyMatrix.push_back(temp);
    }
    
    
    vector<int> furthestPrevHop;
    furthestPrevHop.push_back(0);
    vector<int> furthestNextHop;
    furthestNextHop.push_back(0);
    
    for (int i=1; i<number_of_node+1; i++)
    {
        furthestPrevHop.push_back(i);
        furthestNextHop.push_back(i);
    }

    
    vector<bool> visited;
    visited.push_back(0);
    
    vector<int> distance;
    //distance variable contains the current total weight 
    //of the smallest weight path from the start to the vertex in question 
    distance.push_back(0);
    
    vector<int> parent;
    parent.push_back(0);
    
    for (int i=1; i<number_of_node+1; i++)
    {
        visited.push_back(false);
        distance.push_back(1000000);
        // Theoritically elements of distance is initially set as infinity. 
        // But, in practice, we set it to a number that is larger than any 
        // real distance we will have in the problem that we are trying to solve.
        parent.push_back(0);
        
    }
  
    vector<int> temp;
    temp.push_back(1000000);
    int t;
    int u;
    distance[source] = 0;

    for (int i=1; i<=(number_of_node-1);i++)
    {
        for (int h=1; h<=number_of_node; h++) 
        {
            if (!visited[h])
                temp.push_back(distance[h]);
            else
                temp.push_back(1000000);
        }
        
        vector<int>::const_iterator it = min_element(temp.begin(), temp.end());
        t = *it;
        u = int (min_element(temp.begin(), temp.end()) - temp.begin());
        visited[u] = true;
        
        for (int v=1; v<number_of_node+1; v++)
        { 
        if (AdjacencyMatrix[u][v] + distance[u] < distance[v])
           {   
            distance[v] = distance[u] + AdjacencyMatrix[u][v];
            parent[v] = u;
           }     
        }
        temp.erase (temp.begin()+1,temp.end());
    }

    vector<int> shortestPath1;
    shortestPath1.push_back(1000000);
    int p;
    if (parent[destination] != 0)
    {
        t = destination;
        shortestPath1.push_back(destination);
        while (t != source)
        {
            p = parent[t];
            vector<int>::iterator it = shortestPath1.begin()+1;
            
            shortestPath1.insert(it, p);
            
            if (AdjacencyMatrix[t][furthestPrevHop[t]] < AdjacencyMatrix[t][p])
                furthestPrevHop[t] = p;
            
            if (AdjacencyMatrix[p][furthestNextHop[p]] < AdjacencyMatrix[p][t])
                furthestNextHop[p] = t;
            t = p;
        }
    }
    
    shortestPath1.erase(shortestPath1.begin());
    *shortestPath = shortestPath1;
    *totalCost = distance[destination];
    
   
    
}


#endif /* Dijkstra_h */



