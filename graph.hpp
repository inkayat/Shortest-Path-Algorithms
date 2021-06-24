/**
 *  This graph implementation uses an adjacency-matrix representation.
 *  @author Tolga İnkaya
 */

#ifndef __GRAPH__H
#define __GRAPH__H

#include <iostream>
#include <vector>
#include <string>
#include "constants.hpp"


typedef int vertex_t;


namespace gp
{
    class Graph
    {
    protected:
        void validate_vertex(vertex_t);
        template <typename weight_t>void validate_weight(weight_t);

    private:
        std::vector<std::vector<vertex_t>> AdjacencyMatrix;
        int numberVertices;

    public:
        Graph(/* args */); 
        Graph(int);
        void add_edge(vertex_t, vertex_t, int);
        void add_node(int);
        void remove_node(int);
        void remove_edge(int, int);
        int size() const;
        int max_size() const;
        void set_capacity(int);
        void copy(Graph&);
        void clear();
        template <typename weight_t>int weight(weight_t, weight_t) const;
        std::vector<std::vector<vertex_t>> getAdjacencyMatrix() const;
        void operator=(const Graph&);
        const int operator()(int, int) const;
        void print();
        ~Graph();
    };
    

    Graph::Graph(/* args */) 
    {
        AdjacencyMatrix = std::vector<std::vector<int>>(MAX_NODE, std::vector<int>(MAX_NODE, -1));
    }


    Graph::Graph(int num_node)
    {
        if (num_node < 0) 
            throw new std::invalid_argument("number of vertices must be nonnegative");
        if (num_node > MAX_NODE)
            throw new std::invalid_argument("too many nodes");

        numberVertices = num_node;
        AdjacencyMatrix = std::vector<std::vector<vertex_t>>(num_node, std::vector<vertex_t>(num_node, -1));
    }
    

    Graph::~Graph()
    {
        //delete[] 
    }


    std::vector<std::vector<vertex_t>> Graph::getAdjacencyMatrix() const
    {
        return AdjacencyMatrix;
    }


    void Graph::add_node(int node)
    {
        /**
            @todo
        */
    }


    void Graph::add_edge(int node1, int node2, int weight)
    {
        /**
        *   @param 1 added node to graph, if it is not int the graph already.
        *   @param 2 argument will also be added with 0 weight
        *   @param 3 argument weight, another words distance between node1 and node2
        */
        validate_vertex(node1);
        validate_vertex(node2);
        validate_weight(weight);

        AdjacencyMatrix[node1][node2] = weight;
        // if node is not already marked, then add it to graph and increment vertices number by 1
        if(node1 >= numberVertices)
        {
            ++numberVertices;
        }
        if(AdjacencyMatrix[node2][node1] == -1)
        {
            AdjacencyMatrix[node2][node1] == 0; // Now, there is a connection but no direct access
        }
    }


    void Graph::remove_edge(int src, int dst)
    {
        AdjacencyMatrix[src][dst] = -1;
    }


    void Graph::validate_vertex(vertex_t v)
    {
        if(v < 0 || v > MAX_NODE)
            throw new std::invalid_argument("vertex should be between 0 and " + std::to_string(MAX_NODE));
    }


    template <typename weight_t>
    void Graph::validate_weight(weight_t w)
    {
        if(w < 0)
            throw new std::invalid_argument("weight must be nonnegative");      
    }
    

    int Graph::size() const
    {
        return numberVertices;
    }


    void Graph::set_capacity(int num)
    {
        numberVertices = num;
    }


    void Graph::copy(Graph &g)
    {
        g.clear();
        g.set_capacity(numberVertices);
        for (size_t i = 0; i < numberVertices; i++)
        {
            for (size_t j = 0; j < numberVertices; j++)
            {
                AdjacencyMatrix[i][j] = g(i, j);
            }
            
        }
        
    }


    void Graph::clear()
    {
        AdjacencyMatrix.clear();
        numberVertices = 0;
    }
    

    void Graph::print()
    {
        for(int i = 0; i<numberVertices; i++)
        {
            for(int j = 0; j<numberVertices; j++)
            {
                if(AdjacencyMatrix[i][j]>0)
                {
                    std::cout << i << " " << j << " " << AdjacencyMatrix[i][j] << std::endl;;
                }
            }
        }
    }


    void Graph::remove_node(int node)
    {
        for(int i=0; i<size(); i++) {
            AdjacencyMatrix[node][i] = -1;
        }
        for(int i=0; i<size(); i++) {
            AdjacencyMatrix[i][node] = -1;
        }
    }


    template <typename weight_t>
    int Graph::weight(weight_t n1, weight_t n2) const
    {
        /*
            find weight between two nodes
            n1 ---> n2
        */
        return AdjacencyMatrix[n1][n2];
    }


    void Graph::operator=(const Graph &graph) 
    {
        numberVertices = graph.size();
        AdjacencyMatrix = std::vector<std::vector<vertex_t>>(numberVertices, std::vector<vertex_t>(numberVertices, -1));
        AdjacencyMatrix = graph.getAdjacencyMatrix();  
    }


    const int Graph::operator()(int x, int y) const
    {
        return AdjacencyMatrix[x][y];
    }


    
} // namespace gp



#endif