/**
 *  Helper functions
 *  @author Tolga İnkaya
 */

#ifndef __HELPER__H
#define __HELPER__h

#include <fstream>
#include <sstream>
#include <string>
#include <string.h>
#include <iostream>
#include <iomanip>
#include <vector>
#include "algorithm.hpp"
#include "graph.hpp"

using namespace gp;


std::vector<std::string> split(const std::string& s, char delimiter)
{
    std::vector<std::string> tokens;
    std::string token;
    std::istringstream tokenStream(s);
    while (std::getline(tokenStream, token, delimiter))
    {
        tokens.push_back(token);
    }
    return tokens;
}


Graph readTextFile(const char *fileName, std::vector<int> *part2)
{
    std::ifstream infile(fileName);
    std::string str;
    std::vector<std::string> tokens;
     
    getline(infile, str); // Number Of Vertices
    int128_t v = (int128_t)std::stoi(str);
    Graph graph(v);
    getline(infile, str);
    tokens = split(str, ' ');
    part2->push_back(std::stoi(tokens[0]));
    part2->push_back(std::stoi(tokens[1]));
    part2->push_back(std::stoi(tokens[2]));
    part2->push_back(std::stoi(tokens[3]));

    while (std::getline(infile, str))
    {
        tokens = split(str, ' ');
        int node1 = std::stoi(tokens[0]);
        int node2 = std::stoi(tokens[1]);
        int weight = std::stoi(tokens[2]); 

        graph.add_edge(node1, node2, weight);  
     
    }

    infile.close();
    return graph;
  
}

#endif