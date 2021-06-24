/**
 *  Kth shortest path
 *  @author Tolga İnkaya
 */

#ifndef __KSP__H
#define __KSP__H

#include <vector>
#include <map>
#include <algorithm>
#include "dijkstra.hpp"
using namespace gp;


std::vector<std::pair<int, int>> calculateDistances(Graph g, std::vector<std::vector<int>>vec)
{
    std::vector<std::pair<int, int>>ret;
    for(int i=0; i<vec.size();i++) {
        int distances = 0;
        for(int j=0; j<vec[i].size()-1; j++) {
            distances+=g(vec[i][j], vec[i][j+1]);
        }
        std::pair<int,int> pp;
        pp.first = distances;
        pp.second = i;
        ret.push_back(pp);
    }
    return ret;
}


bool isShared(std::vector<int>rootpath, std::vector<int>p, int x)
{
    for(int i=0; i<x; i++) {
        if(rootpath[i]!=p[p.size()-1-i])
            return false;
        return true;
    }
}


std::vector<std::vector<int>> kShortestPath(Graph graph, int src, int dest, int K)
{
    // Determine the shortest path from the source to the destination.
    std::vector<std::vector<int>>A;
    // Initialize the set to store the potential kth shortest path.
    std::vector<std::vector<int>>B;
    // Select singla path shortest algorithm 
    Dijkstra  shortestPathAlgo;
    shortestPathAlgo.shortestPath(graph, src, dest);
    A.push_back(shortestPathAlgo.spFromTo(src, dest));

    for(int k=1; k<K; k++)
    {
        // The spur node ranges from the first node to the next to last node in the previous k-shortest path.
        for(int i=0; i<A[k-1].size()-2; i++)
        {
            std::vector<std::vector<int>>vertex_removed;
            int size = A[k-1].size();
            int spurNode = A[k-1][size-1-i];
            // The sequence of nodes from the source to the spur node of the previous k-shortest path.
            std::vector<int>rootPath;
            for(int j=0; j<=i; j++) {
                rootPath.push_back(A[k-1][size-1-j]);
            }

            for(auto v:A)
            {
                if(isShared(rootPath, v, i)) {
                    graph.remove_edge(size-1-i, size-2-i);
                }
            }

            int vertex_t = 0;
            for(int r=0; r<rootPath.size(); r++) {
                if(rootPath[r]!=spurNode) {
                    int root = rootPath[r];
                    std::cout << root << std::endl;
                    for(int ii=0; i<graph.size(); ii++) { 
                        if(graph(root, ii)!=-1) {
                            vertex_removed[vertex_t].push_back(root);
                            vertex_removed[vertex_t].push_back(ii);
                            vertex_removed[vertex_t].push_back(graph(root, ii));
                            vertex_t++;
                        }
                    }
                    for(int ii=0; i<graph.size(); i++) {
                        if(ii!=root) {
                            vertex_removed[vertex_t].push_back(ii);
                            vertex_removed[vertex_t].push_back(root);
                            vertex_removed[vertex_t].push_back(graph(ii, root)); 
                            vertex_t++;                          
                        }
                    }
                    graph.remove_node(root);
                }

            }
            // Calculate the spur path from the spur node to the sink.
            shortestPathAlgo.shortestPath(graph, spurNode, dest);
            std::vector<int>spurPath = shortestPathAlgo.spFromTo(spurNode, dest);
            std::vector<int>totalPath;
            for(int ss = 0; ss<rootPath.size(); ss++) {
                totalPath.push_back(rootPath[ss]);
            }
            for(int ss=0;ss<spurPath.size(); ss++) {
                totalPath.push_back(spurPath[spurPath.size()-1-ss]);
            }

            bool check;
            for(int ss=0; ss<B.size(); ss++) {
                check = false;
                if(B[ss].size()==totalPath.size()) {
                    for(int kk=0; kk<B[ss].size(); kk++) {
                        if(B[ss][kk]!=totalPath[kk]) {
                            check = true;
                        }
                    }
                }
                
            }

            // Add the potential k-shortest path to the heap.
            if(check)
            {
                B.push_back(totalPath);
            }

            // Add back the edges and nodes that were removed from the graph.
            for(int ss=0; ss<vertex_removed.size(); ss++)
            {
                graph.add_edge(vertex_removed[ss][0],vertex_removed[ss][1],vertex_removed[ss][2]);
            }

        }
            if(B.size()==0)
            {
                // This handles the case of there being no spur paths, or no spur paths left.
                // This could happen if the spur paths have already been exhausted (added to A), 
                // or there are no spur paths at all - such as when both the source and sink vertices 
                // lie along a "dead end".
                break;
            }

            std::vector<std::pair<int, int>>temp = calculateDistances(graph, B);
            std::sort(temp.begin(), temp.end());
            A.push_back(B[temp[0].second]);
            B.erase (B.begin()+temp[0].second);
    }

    return A;
}


#endif