/**
 * Yen's algorithm computes single-source K-shortest loopless paths for a graph with non-negative edge cost.
 * The algorithm was published by Jin Y.  Yen in 1971 and employs any shortest path algorithm to 
 * find the best path, then proceeds to find K − 1 deviations of the best path.(Wikipedia)
 *  @author Tolga İnkaya
 */

#ifndef YensKpath_h
#define YensKpath_h

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include "dijkstra.hpp"

using namespace std;


class Path_info{
public:
    int path_no;
    vector<int> path_nodes;
    int path_cost;
};


void YensKpath(int number_of_node, vector< vector<int> > adjacencymatrix, int source, 
                int destination, int k_paths, vector < vector<int> > * ShortestPaths1,  vector<int>  * TotalCosts1) {
    
 
    Dijkstra *dijkstra = new Dijkstra();
    std::vector<int> path;
    int cost;
    
    dijkstra->pathFinder(number_of_node, adjacencymatrix, source, destination, &path, &cost);
    
  
    
    vector< vector<int> > temp_adjacencymatrix;
    vector< vector<int> > ShortestPaths;
    vector<int> TotalCosts;
    
    vector<Path_info> P;
    vector<Path_info> X;
    
    int path_number = 1;
    vector<int> S;
    
    Path_info path1;
    
    
    if (path.empty())
        cout << "There is no path between source node and destination node." << endl;
    else {
        {
            path1.path_no = path_number;
            path1.path_nodes = path;
            path1.path_cost = cost;
            
        }
        
        X.push_back(path1);
        P.push_back(path1);
        
        S.push_back(path[0]);
        
        ShortestPaths.push_back(path);
        TotalCosts.push_back(cost);
        
        
        int k=0;
        int current_P = path_number;
        
        while (k<(k_paths-1) && X.size() !=0){
            for (int i=0; i< X.size(); i++)
            {   if (X[i].path_no == current_P)
            {
                
                X.erase(X.begin()+i);
                break;
            }
            }
            
            
            vector<int> P_;
            int w, w_index_in_path=0;
            P_.clear();
            P_ = P[current_P-1].path_nodes;
            w = S[current_P-1];
            
            
            for (int i=0; i<P_.size();i++)
            {if (w == P_[i])
                w_index_in_path = i;}
            
            
            int index_dev_vertex=0;
            int v;
            
            for (index_dev_vertex = w_index_in_path; index_dev_vertex <(P_.size()-1); index_dev_vertex++)
            {            
            for (int i=0; i< number_of_node+1; i++)
               {vector<int> temp;
                    for (int j=0; j< number_of_node+1; j++)
                        temp.push_back(adjacencymatrix[i][j]);
                temp_adjacencymatrix.push_back(temp);
                temp.clear();}
            
                for (int i=0; i<=(index_dev_vertex-1); i++ )
                { v = P_[i];
                    for (int j=0; j<number_of_node+1;j++ ) 
                    {
                        temp_adjacencymatrix[v][j] = 1000000;
                        temp_adjacencymatrix[j][v] = 1000000;
                    }
                }
                
                vector< vector<int> > SP_sameSubPath;
                vector<int> temp,temp1;
                
                SP_sameSubPath.clear();
                SP_sameSubPath.push_back(P_);
                
                for (int i =0; i<=(ShortestPaths.size()-1);i++)
                    if (ShortestPaths[i].size() > index_dev_vertex+1)
                        for (int j = 0; j<=index_dev_vertex; j++)
                            for (int m=0; m<=index_dev_vertex; m++)
                                if ( P_[j] == ShortestPaths[i][m])
                                    SP_sameSubPath.push_back(ShortestPaths[i]);


                int v_ , next;
                v_ = P_[index_dev_vertex];
                for (int j=0; j< SP_sameSubPath.size(); j++)
                {
                    next = SP_sameSubPath[j][index_dev_vertex+1];      
                    temp_adjacencymatrix[v_][next] = 1000000;
                }
             
                
                vector <int> sub_P;
                for (int i=0; i <= index_dev_vertex; i++)
                    sub_P.push_back(P_[i]);
                
                
                int cost_sub_P = 0;
                for (int i=0; i< (sub_P.size()-1); i++)
                    cost_sub_P = cost_sub_P + adjacencymatrix[sub_P[i]][sub_P[i+1]];
                
                
                vector<int> dev_p;
                int c;
                dijkstra->pathFinder(number_of_node,temp_adjacencymatrix, P_[index_dev_vertex], destination, &dev_p, &c);
                
                if (!dev_p.empty())
                {  
                    path_number = path_number + 1; 
                    Path_info temp;
                    temp.path_no = path_number;
                    
                    for (int i=0; i<(sub_P.size()-1); i++ )
                        temp.path_nodes.push_back(sub_P[i]);
                    
                    for (int i=0; i<dev_p.size(); i++)
                        temp.path_nodes.push_back(dev_p[i]);
                    
                    temp.path_cost = cost_sub_P + c;
                    
                    P.push_back(temp);
                    S.push_back(P_[index_dev_vertex]);
                    X.push_back(temp);    
                }

                else
                    cout << "" ;
                
            }
            
          
            if (X.size() > 0)
                
            { int shortestXCost, shortestX;
                vector<int> shortestXpath;
                
                shortestXCost = X[0].path_cost;
                shortestX = X[0].path_no;
                
                for (int i=1; i<X.size(); i++)
                { if (X[i].path_cost < shortestXCost)
                    
                { shortestX = X[i].path_no; 
                    shortestXCost = X[i].path_cost; 
                }
                }
                
                current_P = shortestX;
                k = k + 1;
           
                ShortestPaths.push_back(P[current_P-1].path_nodes);
                TotalCosts.push_back(P[current_P-1].path_cost);
                
            }
            else
                cout << "";
            
        }
    }
    

    
    *ShortestPaths1 = ShortestPaths;
    *TotalCosts1  = TotalCosts;    
    
}




#endif 






