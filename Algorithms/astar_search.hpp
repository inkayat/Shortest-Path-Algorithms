/**
 *  A* Search Algorithm. Heuristacly searches shortest path.
 *  @author Tolga İnkaya
 */

#include "../graph.hpp"
#include <vector>
#include <unordered_map>
#include <list>
#include <math.h>
#include <queue>
#include <utility>

using namespace gp;


template<typename T, typename priority_t>
struct PriorityQueue {
  typedef std::pair<priority_t, T> PQElement;
  std::priority_queue<PQElement, std::vector<PQElement>,
                 std::greater<PQElement>> elements;

  inline bool empty() const {
     return elements.empty();
  }

  inline void put(T item, priority_t priority) {
    elements.emplace(priority, item);
  }

  T get() {
    T best_item = elements.top().second;
    elements.pop();
    return best_item;
  }
};


class A_Star
{   
    protected:
        void construct(Graph);
        inline int heuristic(int, int); 


    private:
        std::unordered_map<int, int>came_from;
        std::unordered_map<int, int>cost_so_far;
        PriorityQueue<int, int> frontier;
        std::list<int>closed_set;
        std::vector<int, int>neighbors;
        

    public:
        void shortestPath(Graph, int, int);

};

inline int A_Star::heuristic(int src, int dest)
{
    return pow(dest-src, 2) + sqrt(dest*dest - src*src);
}

void A_Star::construct(Graph graph)
{
    for(int i=0; i<graph.size(); i++)
    {
        for(int j=0; j<graph.size(); j++)
        {
            neighbors[i].push_back(graph(i, j));
        }
    }
}


void A_Star::shortestPath(Graph graph, int src, int dest)
{
    construct(graph);

    came_from[src] = src;
    cost_so_far[src] = 0;

    while(!frontier.empty()) {
        int current = frontier.get();
    

        if (current == dest)
            break;

        for (int next : neighbors[current]) {
            int new_cost = cost_so_far[current] + graph(current, next);
            if (cost_so_far.find(next) == cost_so_far.end()
                || new_cost < cost_so_far[next]) {
                cost_so_far[next] = new_cost;
                int priority = new_cost + heuristic(next, dest);
                frontier.put(next, priority);
                came_from[next] = current;
            }
        }
    }
    
}
