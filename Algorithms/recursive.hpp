/**
 *  Brute force approach using recursion
 *  @author Tolga İnkaya
 */

#ifndef __RECURSIVE__H
#define __RECURSIVE__H

#include <vector>
#include "../graph.hpp" 

using namespace gp;


class Recursive
{
    protected:
        template<typename T>T find_min(std::vector<T>);
        void recur(Graph, int, int, int, std::vector<bool>);

    private:
        int __min_t = INF;
    
    public:
        void shortestPath(Graph, int, int);
        int show();

};


template<typename T>
T Recursive::find_min(std::vector<T> vec)
{
    int128_t min = INF;
    for(auto v : vec)
    {
        if(v < min)
        {
            min = v;
        }
    }
    return min;
}

int Recursive::show()
{
    std::cout << __min_t << std::endl;
    return __min_t ;
}


void::Recursive::recur(Graph graph, int target, int current, int weight, std::vector<bool> visited)
{
    if(current == target)
    {
        if(weight < __min_t)
        {
            __min_t = weight;
        }
        return;
    }

    visited[current] = true;
    for(int i = 0; i<graph.size(); i++)
    {
        if(graph(current, i) > 0 && !visited[i])
        {
            recur(graph, target, i, weight + graph(current, i), visited);
        }
    }
}


void Recursive::shortestPath(Graph graph, int target, int current)
{
    std::vector<bool>visited = std::vector<bool>(graph.size(), false);  
    recur(graph, target, current, 0, visited);
}



#endif






