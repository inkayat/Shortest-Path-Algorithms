/**
 *  @author Tolga İnkaya
 */

#include "helper.hpp"
#include "hw2.hpp"
#include "test.hpp"

using namespace std;
using namespace gp;
using namespace sol;


int main(int argc, const char * argv[]) {
    
    int source, destination, k_paths;
    string test_file;
    
    int number_of_node=0;
    vector<int> index,c1;
    string line;


    std::ifstream infile(argv[1]);
    test_file = argv[1];
    std::string str;
    std::vector<std::string> tokens;
    std::vector<int> destinations;
    // Number Of Vertices
    getline(infile, str); 
    number_of_node = (int128_t)std::stoi(str);
    getline(infile, str);
    tokens = split(str, ' ');
    destinations.push_back(std::stoi(tokens[0])+1);
    destinations.push_back(std::stoi(tokens[1])+1);
    destinations.push_back(std::stoi(tokens[2])+1);
    destinations.push_back(std::stoi(tokens[3])+1);

    
    while (getline(infile, line))
    {
        istringstream iss(line);
        int a,b,c;
        
        if (!(iss >> a >> b >> c  )) { break; } // error
        
        index.push_back(a+1);
        index.push_back(b+1);
        c1.push_back(c);
       
    }
    
    
    int AdjacencyMatrix[number_of_node+1][number_of_node+1];
    
    for (int i = 0; i < number_of_node+1; i++)
        for (int j = 0; j < number_of_node+1; j++)
        {AdjacencyMatrix[i][j] = 1000000; 
            for (int k=0; k< index.size()/2;k++)
                AdjacencyMatrix[index[2*k]][index[2*k+1]] = c1[k];
        }
    

    vector<vector<int> > adjacencymatrix;
    for ( int i=0;i< sizeof (AdjacencyMatrix)/sizeof (AdjacencyMatrix[0]);i++)
    {  vector<int> temp;
        for (int j=0;j< sizeof (AdjacencyMatrix[0])/sizeof (AdjacencyMatrix[0][0]);j++)
            temp.push_back(AdjacencyMatrix[i][j]);
        adjacencymatrix.push_back(temp);
        temp.clear();  }
     
    
    // object to solve assignment
    Solution assignment = Solution();

    // returning appropriate shortest path 
    int minimumDistance = assignment.Assignment2Solver(destinations, number_of_node, adjacencymatrix, k_paths);

    
    return 0;
}



