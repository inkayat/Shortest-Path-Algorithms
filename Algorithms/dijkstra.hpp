/**
 *  single-source shortest paths, API includes following methods
 * 
 *  protected methods  
 *          relax(Graph, int, int) -> this is helper function to calculare min distance to finding shortest path
 *          minimum_distance(bool[], int[])
 *  public methods
 *          shortestPath(Graph, int, int) -> this methods find shortest paths from source to other all vertices.
 *          pathFinder() -> findinf all paths
 *          printSD()   -> print path source to destination
 *          printSP()   -> print shortest paths
 *          
 *  @author Tolga İnkaya
 */


#ifndef __DIJKSTRA__H
#define __DIJKSTRA__H

#include "../graph.hpp" 
#include <algorithm>
using namespace gp;
using namespace std;

class Dijkstra
{
    protected:
        void Init(Graph);
        void relax(Graph, int, int);
        int minimum_distance(bool[], int[]);

    private:
        int v;
        bool *visited; 
        int *distances;
        std::vector<int128_t> paths;
        
    public:
        Dijkstra();
        void shortestPath(Graph, int, int);
        void pathFinder(int, std::vector< std::vector<int> >, int, int, std::vector<int> *, int *);
        void printSD();
        void printSP(int);
        template <typename position>std::vector<position> spFromTo(position, position);
        ~Dijkstra();
};


Dijkstra::Dijkstra()
{
    v = 0;
    paths.reserve(MAX_NODE);
}


void Dijkstra::Init(Graph graph)
{
    v = graph.size();
    visited = new bool[v];
    distances = new int[v];
}


int Dijkstra::minimum_distance(bool visited[], int distances[])
{
    int min = INF;
    int index;

    for(int i = 0; i<v; i++)
    {
        if(distances[i] < min && !visited[i])
        {
            min = distances[i];
            index = i;
        }   
    }
    return index;
}


void Dijkstra::relax(Graph graph, int source, int dest)
{
    if(graph(source, dest) > 0 && !visited[dest] && distances[source] != INF && 
       distances[dest] > graph(source, dest) + distances[source])
       {
            distances[dest] = graph(source, dest) + distances[source];
            paths[dest] = source;
       }
}


void::Dijkstra::shortestPath(Graph graph, int source=0, int dest=-1)
{
    int i, j;
    Init(graph);

    for(i = 0; i < v; i++)
    {
        visited[i] = false;
        distances[i] = INF;
        paths[i] = source;
    }

    distances[source] = 0;

    for(i = 0; i < v; i++)
    {
        int idx = minimum_distance(visited, distances);
        visited[idx] = true;

        for(j = 0; j < v; j++) 
        {
            relax(graph, idx, j);
        }

    }
}


void Dijkstra::pathFinder(int number_of_node, std::vector< vector<int> > AdjMatrix, int source, 
              int destination, std::vector<int> *shortestPath, int *totalCost) {
    
    
    std::vector< std::vector<int> > _AdjacencyMatrix;
    for (int i=0; i< number_of_node+1; i++)
    {    
        std::vector<int> temp;
        for (int j=0; j< number_of_node+1; j++)
            temp.push_back(AdjMatrix[i][j]);

        _AdjacencyMatrix.push_back(temp);
    }
    
    
    std::vector<int> furthestPrevHop;
    furthestPrevHop.push_back(0);
    std::vector<int> furthestNextHop;
    furthestNextHop.push_back(0);
    
    for (int i=1; i<number_of_node+1; i++)
    {
        furthestPrevHop.push_back(i);
        furthestNextHop.push_back(i);
    }

    
    std::vector<bool> visited;
    visited.push_back(0);
    
    std::vector<int> distance;
   
    distance.push_back(0);
    
    std::vector<int> parent;
    parent.push_back(0);
    
    for (int i=1; i<number_of_node+1; i++)
    {
        visited.push_back(false);
        distance.push_back(1000000);
 
        parent.push_back(0);
        
    }
  
    std::vector<int> temp;
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
        
        std::vector<int>::const_iterator it = min_element(temp.begin(), temp.end());
        t = *it;
        u = int (min_element(temp.begin(), temp.end()) - temp.begin());
        visited[u] = true;
        
        for (int v=1; v<number_of_node+1; v++)
        { 
        if (_AdjacencyMatrix[u][v] + distance[u] < distance[v])
           {   
            distance[v] = distance[u] + _AdjacencyMatrix[u][v];
            parent[v] = u;
           }     
        }
        temp.erase (temp.begin()+1,temp.end());
    }

    std::vector<int> shortestPath1;
    shortestPath1.push_back(1000000);
    int p;
    if (parent[destination] != 0)
    {
        t = destination;
        shortestPath1.push_back(destination);
        while (t != source)
        {
            p = parent[t];
            std::vector<int>::iterator it = shortestPath1.begin()+1;
            
            shortestPath1.insert(it, p);
            
            if (_AdjacencyMatrix[t][furthestPrevHop[t]] < _AdjacencyMatrix[t][p])
                furthestPrevHop[t] = p;
            
            if (_AdjacencyMatrix[p][furthestNextHop[p]] < _AdjacencyMatrix[p][t])
                furthestNextHop[p] = t;
            t = p;
        }
    }
    
    shortestPath1.erase(shortestPath1.begin());
    *shortestPath = shortestPath1;
    *totalCost = distance[destination];
    
 
}



void Dijkstra::printSD()
{
    std::cout << "Vertex \tDistance from Source" << std::endl;
    for (int i = 0; i < v; i++) 
        std::cout << i << " \t\t " << distances[i] << std::endl;

}


void Dijkstra::printSP(int startnode)
{
    int i, j;
	//print the path and distance of each node
	for(i=0;i<v;i++)
		if(i!=startnode) {
			printf("\nDistance of node%d=%d",i,distances[i]);
			printf("\nPath=%d",i);

			j=i;
			do
            {
				j=paths[j];
				printf("<-%d",j);
			}while(j!=startnode);
	}
}


template <typename position>
std::vector<position> Dijkstra::spFromTo(position source, position dest)
{
    std::vector<position> vec;
    vec.push_back(dest);
    do
    {
        dest = paths[dest];
        vec.push_back(dest);
    } while (dest != source);

    return vec;
}


Dijkstra::~Dijkstra()
{
    delete distances;
    delete visited;
}



#endif