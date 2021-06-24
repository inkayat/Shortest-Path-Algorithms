/**
 *  Class implementation for assignment solution
 *  @author Tolga İnkaya
 */

#ifndef __SOLUTION__H
#define __SOLUTION__H

#include "algorithm.hpp"
#include <algorithm>
#include <unordered_map>
#include "graph.hpp"

using namespace gp;


struct double_pair { 
    int index1, index2, cost1, cost2;
};

  
bool compareCost(double_pair p1, double_pair p2) 
{ 
    return (p1.cost1+p1.cost2 <= p2.cost1+p2.cost2); 
} 



namespace sol {
        class Solution
        {
                
                private:
                        int jh, jd, lh, ld;
                        bool isJH, isJD, isLH, isLD;
                        bool isValid;
                        int jVisited;
                        int lVisited;
                        int timeJ;
                        int timeL;
                        int algoType;
                        int conflict;
                        void init(int, int, int, int);
                        std::vector<int> searchPath(Graph, int, int);
                        std::unordered_map<int, int>minutesJ;
                        std::unordered_map<int, int>minutesL;
                        int checkConflict(std::vector<int>, std::vector<int>, int, int, std::vector<std::vector<int>>, int, int);

                public:
                        Solution(int t=0);    
                        int Assignment2Solver(std::vector<int>, int , std::vector< std::vector<int> >, int);
                        void printPath(std::vector<int>, std::unordered_map<int, int>);
                        int calculateMinutes(Graph, std::vector<int>, int, int=0);
                        


        };


Solution::Solution(int t)
{

        /**
         * if t == 0 which is default value, class uses Dijkstra Algorithm to find soluti0n
         * if t == 1, class uses Recursion
         * if t == 2, class uses TSP 
         * if t == 3, class uses Floyd Warshall Algorithm
         * if t == 4, class uses Bellman Ford Algorithm
         * if t == 5, class uses A* Algorithm
        */
        algoType = t;
}


void Solution::init(int a, int b, int c, int d) 
{
        jh = a;
        jd = b;
        lh = c;
        ld = d;
        isJH = true;
        isJD = false;
        isLH = true;
        isLD = false;
        isValid = false;
        jVisited = 0;
        lVisited = 0;
        timeJ = 0;
        timeL = 0;
}


int Solution::Assignment2Solver(std::vector<int>destinations, int number_of_node, vector< vector<int> > adjacencymatrix, int k_paths) 
{

        vector< vector<int> > ShortestPathJ;
        vector< vector<int> > ShortestPathL;
        vector< vector<int> > ShortestPathJ2;
        vector< vector<int> > ShortestPathL2;
        vector<int> TotalCostJ;
        vector<int> TotalCostL;
        vector<int> TotalCostL2;
        vector<int> TotalCostJ2;
        int distancesHomeToDest = 0x3f3f3f3f;
        int distancesDesToHome = 0x3f3f3f3f;

       

        //home to destination paths
        YensKpath(number_of_node, adjacencymatrix, destinations[0], destinations[1], MAX_ROUTE, &ShortestPathJ, &TotalCostJ);
        YensKpath(number_of_node, adjacencymatrix, destinations[2], destinations[3], MAX_ROUTE, &ShortestPathL, &TotalCostL);
        
        vector<double_pair>BestPaths;

        for(int i = 0; i<ShortestPathJ.size(); i++)  {
                for(int j=0; j<ShortestPathL.size(); j++) {
                        double_pair a;
                        a.index1=i;
                        a.cost1=TotalCostJ[i];
                        a.index2=j;
                        a.cost2 = TotalCostL[j];
                        BestPaths.push_back(a);
                }
        }

        sort(BestPaths.begin(), BestPaths.end(), compareCost);
        bool noSolution = true;
        std::vector<int>homeToDestPathsJ;
        std::vector<int>homeToDestPathsL;
        std::vector<int>destToHomePathsJ;
        std::vector<int>destToHomePathsL;
        int homeToDestCostJ;
        int homeToDestCostL;
        int destToHomeCostJ;
        int destToHomeCostL;



        for(int i = 0; i<BestPaths.size(); i++)
        {
                int pp = checkConflict(ShortestPathJ[BestPaths[i].index1],ShortestPathL[BestPaths[i].index2], 0, 0, adjacencymatrix , i, 1);
                if(pp!=-1) {
                        noSolution = false;
                        homeToDestPathsJ = ShortestPathJ[BestPaths[pp].index1];
                        homeToDestPathsL = ShortestPathL[BestPaths[pp].index2];
                        homeToDestCostJ = TotalCostJ[BestPaths[pp].index1];
                        homeToDestCostL = TotalCostL[BestPaths[pp].index2];
                        break;
                }
        }

        if(noSolution) {
                std::cout << "No solution!" << std::endl;
                return -1;
        }

        ShortestPathJ.clear();
        ShortestPathL.clear();

        YensKpath(number_of_node, adjacencymatrix, destinations[1], destinations[0], MAX_ROUTE, &ShortestPathJ, &TotalCostJ);
        YensKpath(number_of_node, adjacencymatrix, destinations[3], destinations[2], MAX_ROUTE, &ShortestPathL, &TotalCostL);

        BestPaths.clear();

        for(int i = 0; i<ShortestPathJ.size(); i++)  {
                for(int j=0; j<ShortestPathL.size(); j++) {
                        double_pair a;
                        a.index1=i;
                        a.cost1=TotalCostJ[i];
                        a.index2=j;
                        a.cost2 = TotalCostL[j];
                        BestPaths.push_back(a);
                }
        }

        sort(BestPaths.begin(), BestPaths.end(), compareCost);
        noSolution = true;
        for(int i = 0; i<BestPaths.size(); i++)
        {
                int pp = checkConflict(ShortestPathJ[BestPaths[i].index1], ShortestPathL[BestPaths[i].index2], homeToDestCostJ, homeToDestCostL, adjacencymatrix, i, 2);
                if(pp !=-1) {
                        noSolution = false;
                        destToHomePathsJ = ShortestPathJ[BestPaths[pp].index1];
                        destToHomePathsL = ShortestPathL[BestPaths[pp].index2];
                        destToHomeCostJ = TotalCostJ[BestPaths[pp].index1];
                        destToHomeCostL = TotalCostL[BestPaths[pp].index2];
                        break;
                }
        }
        
        if(noSolution) {
                std::cout << "No solution!" << std::endl;
                return -1;
        }


        int t_time = 0;
        std::cout << "Joseph's Path, duration: " << homeToDestCostJ+destToHomeCostJ+30 << std::endl;
        std::cout << "Node: " << homeToDestPathsJ[0]-1 << " Time: " << 0 << std::endl;
        for(int i = 1; i<homeToDestPathsJ.size(); i++) {
                int distance =  adjacencymatrix[homeToDestPathsJ[i-1]][homeToDestPathsJ[i]];
                std::cout << "Node: " << homeToDestPathsJ[i]-1 << " Time: " << t_time+distance << std::endl;
                t_time+=distance;
        }

        std::cout << "-- return --" << std::endl;
        t_time+=30;

        std::cout << "Node: " << destToHomePathsJ[0]-1 << " Time: " << t_time << std::endl;
        for(int i = 1; i<destToHomePathsJ.size(); i++) {
                int distance =  adjacencymatrix[destToHomePathsJ[i-1]][destToHomePathsJ[i]];
                std::cout << "Node: " << destToHomePathsJ[i]-1 << " Time: " << t_time+distance << std::endl;
                t_time+=distance;
        }

        std::cout << std::endl;

        t_time = 0;
        std::cout << "Lucy's Path, duration: " << homeToDestCostL+destToHomeCostL+30 << std::endl;
        std::cout << "Node: " << homeToDestPathsL[0]-1 << " Time: " << 0 << std::endl;
        for(int i = 1; i<homeToDestPathsL.size(); i++) {
                int distance =  adjacencymatrix[homeToDestPathsL[i-1]][homeToDestPathsL[i]];
                std::cout << "Node: " << homeToDestPathsL[i]-1 << " Time: " << t_time+distance << std::endl;
                t_time+=distance;
        }

        std::cout << "-- return --" << std::endl;
        t_time+=30;

        std::cout << "Node: " << destToHomePathsL[0]-1 << " Time: " << t_time << std::endl;
        for(int i = 1; i<destToHomePathsL.size(); i++) {
                int distance =  adjacencymatrix[destToHomePathsL[i-1]][destToHomePathsL[i]];
                std::cout << "Node: " << destToHomePathsL[i]-1 << " Time: " << t_time+distance << std::endl;
                t_time+=distance;
        }


        return (homeToDestCostL+destToHomeCostL+30+homeToDestCostJ+destToHomeCostJ+30);

}


std::vector<int> Solution::searchPath(Graph graph, int a, int b) 
{
        Dijkstra pathfinder;

        switch (algoType)
        {
        case 0:  
                pathfinder.shortestPath(graph, a, b);
                return pathfinder.spFromTo(a, b);
        
        default:
                break;
        }

}


void Solution::printPath(std::vector<int>path, std::unordered_map<int, int>ttime) {
        while(!path.empty())
        {
                int node = path.back();
                path.pop_back();
                std::cout << node << "(" <<ttime[node] << ")" <<" >> ";   
        }
        std::cout << std::endl;
        /*
        for(auto p : path)
                std::cout << p << " >> ";
        std::cout << std::endl;
        */
}


// This function checks whatever or not any encounter at the same point at the same time
int Solution::checkConflict(std::vector<int>J, std::vector<int>L, int initial_timeJ, int initial_timeL, std::vector<std::vector<int>>a, int ret, int _case) {
        /*
        Return type <pair<int, int>>
        Return node which not causes confliction 
        
        If there is no confliction Return pair index
        */

       int time_j = 0;
       int time_l = 0;
       int i = 0;
       int j = 0;

       time_j=initial_timeJ+30;
       i = 1;


       if(initial_timeJ<=initial_timeL && _case==2)
       {
               time_j+=a[J[i-1]][J[i]];
               while(initial_timeL<=time_j && time_j<=initial_timeL+30)
              {
                      if(J[i]==L[0]) {
                              return -1;
                      }
                      i+=1;
                      time_j+=a[J[i-1]][J[i]];
              }
       }

       i = 1;
       time_l = initial_timeL+30;
       if(initial_timeJ>initial_timeL && _case==2)
       {

               time_l+=a[L[i-1]][L[i]];
               while(time_l<=initial_timeJ+30)
              {
                      if(L[i]==J[0]) {
                              return -1;
                      }
                      time_l+=a[L[i-1]][L[i]];
                      i+=1;
              }               
       }

       time_j = 0;
       time_l = 0;

       for(int i = 1; i<J.size(); i++) {
               time_j+=a[J[i-1]][J[i]];
               time_l = 0;
               for(int j=1; j<L.size(); j++) {
                       time_l+=a[L[j-1]][L[j]];

                       if(i==J.size()-1 && time_j+30 >= time_l && J[i]==L[j] && _case == 1)
                       {
                               return -1;
                       }

                       if(j==L.size() && time_l+30>=time_j && J[i]==L[j] && _case ==1)
                       {
                               return -1;
                       }
                       
                       if((L[j]==J[i] && initial_timeJ+time_j == initial_timeL+time_l))
                       {
                               return -1; 
                       }
                }      
        }
        return ret;
}


// This function is not used for hw
int Solution::calculateMinutes(Graph g, std::vector<int>vec, int mode, int waitingTime) {
        int src = vec.back();
        int time = 0;
        time+=waitingTime;
        if(mode == 0)
        {
                minutesJ.clear();
                while(!vec.empty())
                {
                        int node = vec.back();
                
                        if(g(src, node) == -1) {
                                time+=0;
                        }
                        else {
                                time+=g(src, node);
                        }
                        src = vec.back();
                        vec.pop_back();
                        minutesJ[node] = time+timeJ;  
                }
                timeJ+=time;
        }
        else
        {
                minutesL.clear();
                while(!vec.empty())
                {
                        int node = vec.back();
                
                        if(g(src, node) == -1) {
                                time+=0;
                        }
                        else {
                                time+=g(src, node);
                        }
                
                        src = vec.back();
                        vec.pop_back();
                        minutesL[node] = time+timeL;  
                }
                timeL+=time;                
        }
           
        return time;
}




}

#endif