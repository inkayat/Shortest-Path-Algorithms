/**
 *  This is higly efficient search but it doesn't 
 *  guarantee to finding shortest path
 *  @author Tolga İnkaya
 */

#ifndef __RANDOM__H
#define __RANDOM__H

#include "../graph.hpp"
#include <time.h>

using namespace gp;

class RandomWalk
{
    protected:
        int randomize(Graph, int, int, bool);

    private:
        int a_value = 0;

    public:
        int walk(Graph, int, int, bool=false);
};


int RandomWalk::randomize(Graph g, int s, int d, bool optimistic)
{
    int ss = s, dd = d;
    std::vector<int> list;
    int ept = 0;
    int result = 0;
    srand(time(NULL));

    while(ss != dd)
    {
        for(int i = 0; i < g.size(); i++)
        {
            if(g(ss, i)>0)
            {
                list.push_back(i);
            }
        }
        if(list.size() == 0)
        {
            ss = ept;
        }
        else 
        {
            int rnd = rand()%list.size();
            list.clear();
            result += g(ss, list[rnd]);
            ept = ss;
            ss = list[rnd];
        }
 
    }
    

    while(s != d && optimistic)
    {
        for(int i = 0; i < g.size(); i++)
        {
            if(g(s, i) > 0 && g(s, g.size()-i-1) > 0)
            {
                if(i == d)
                {
                    a_value += g(s, i);
                    s = i;
                }
                else if(g.size()-i-1 == d)
                {
                    a_value += g(s, g.size()-i-1);
                    s = g.size()-i-1;    
                }
                else if(g(s, i) < g(s, g.size()-i-1))
                {
                    a_value += g(s, i);
                    s = i;
                }
                else
                {
                    a_value += g(s, g.size()-i-1);
                    s = g.size()-i-1;
                    
                }
                break;
            }
            else if(g(s, i)>0)
            {
                a_value += g(s, i);
                s = i;
                break;
            }
            else if(g(s, g.size()-i-1) > 0)
            {
                a_value += g(s, g.size()-i-1);
                s = g.size()-i-1;
                break;
            }
            
        }
    }
    if(a_value != 0 && a_value < result)
    {
        return a_value;
    }
    return result;
}



int RandomWalk::walk(Graph graph, int source, int des, bool optimistic)
{
    return randomize(graph, source, des, optimistic);
}



#endif