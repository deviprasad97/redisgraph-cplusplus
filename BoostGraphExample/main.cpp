//
// Created by devi on 1/9/20.
//
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/astar_search.hpp>
#include <boost/graph/kruskal_min_spanning_tree.hpp>
#include <boost/property_map/transform_value_property_map.hpp>
#include <boost/graph/graphviz.hpp>
#include <iostream>
#include <fstream>
#include "Node.h"
#include <boost/graph/astar_search.hpp>
#include <boost/graph/random.hpp>
#include <boost/random.hpp>
#include <sys/time.h>
#include <math.h>


namespace boost {
    enum vertex_Node_t { vertex_Node = 0 };
    BOOST_INSTALL_PROPERTY(vertex, Node);
}
struct VertexProps { };
struct EdgeProps { float weight; };
typedef float cost;
// euclidean distance heuristic
template <class Graph, class CostType, class LocMap>
class distance_heuristic : public boost::astar_heuristic<Graph, CostType>
{
public:
    typedef typename boost::graph_traits<Graph>::vertex_descriptor Vertex;
    distance_heuristic(LocMap l, Vertex goal)
            :m_location(l), m_goal(goal) {}
    CostType operator()(Vertex u)
    {
        CostType dx = m_location[m_goal].weight - m_location[u].weight;
        return dx;
    }
private:
    LocMap m_location;
    Vertex m_goal;
};


struct found_goal {}; // exception for termination

// visitor that terminates when we find the goal
template <class Vertex>
class astar_goal_visitor : public boost::default_astar_visitor
{
public:
    astar_goal_visitor(Vertex goal) : m_goal(goal) {}
    template <class Graph>
    void examine_vertex(Vertex u, Graph& g) {
        if(u == m_goal)
            throw found_goal();
    }
private:
    Vertex m_goal;
};
enum vertex_properties_t { vertex_properties };
enum edge_properties_t { edge_properties };
namespace boost {
    BOOST_INSTALL_PROPERTY(vertex, properties);
    BOOST_INSTALL_PROPERTY(edge, properties);
}
int main() {
        typedef boost::adjacency_list< boost::listS, boost::vecS, boost::undirectedS,
        boost::property<vertex_properties_t, std::shared_ptr<Node>>,
        boost::property<boost::edge_weight_t, cost>> Graph;
        typedef boost::property_map<Graph, boost::edge_weight_t>::type WeightMap;
        //typedef boost::property<boost::edge_weight_t, std::shared_ptr<Node>> EdgeWeightProperty;

        typedef boost::graph_traits <Graph>::edge_descriptor Edge;
        typedef boost::graph_traits <Graph>::vertex_descriptor Vertex;
        typedef std::pair<Vertex, Vertex > E;

        typedef Graph::vertex_descriptor vertex;
        typedef Graph::edge_descriptor edge_descriptor;
        typedef Graph::vertex_iterator vertex_iterator;

        const int num_nodes = 6;

        // Create Shared pointer for Node Class
        std::shared_ptr<Node> object_one = std::make_shared<Node>(123, "obj1");
        std::shared_ptr<Node> object_two = std::make_shared<Node>(456, "obj2");
        std::shared_ptr<Node> object_three = std::make_shared<Node>(789, "obj3");
        std::shared_ptr<Node> object_four = std::make_shared<Node>(101, "obj4");
        std::shared_ptr<Node> object_five = std::make_shared<Node>(121, "obj5");
        std::shared_ptr<Node> object_six = std::make_shared<Node>(145, "obj6");

        // Saving all the objects to an array
        std::shared_ptr<Node> objs [] = {object_one, object_two, object_three,
                                         object_four, object_five, object_six};


        // Lets create a graph with n nodes
        Graph g(num_nodes);

        // Create BOOST::VERTEX from the shared objects for the graph g
        Vertex vertex_one = boost::add_vertex(object_one, g);
        Vertex vertex_two = boost::add_vertex(object_two, g);
        Vertex vertex_three = boost::add_vertex(object_three, g);
        Vertex vertex_four = boost::add_vertex(object_four, g);
        Vertex vertex_five = boost::add_vertex(object_five, g);
        Vertex vertex_six = boost::add_vertex(object_six, g);


        // Weights to add to the edge
        int weights[] = { 1, 1, 2, 7, 3, 1, 1, 1 };

        EdgeProps edge_weights[] = {
                {1}, {1}, {2}, {7}, {3}, {1}
        };

        // weight_map weights for the edge.
        //WeightMap weightmap = get(&EdgeProps::weight, g);

        //auto weight_map = get(boost::edge_weight_t, g);

        // Edge array with all the pairs to be joined with a path
        E edge_array[] = {
                E(vertex_one, vertex_two), E(vertex_one, vertex_three), E(vertex_two, vertex_six),
                E(vertex_three, vertex_five), E(vertex_five, vertex_two), E(vertex_six, vertex_one)
        };


        // Get the num_edges
        std::size_t num_edges = sizeof(edge_array) / sizeof(E);

        // Now lets add edges and change their weights
        WeightMap weightmap = get(boost::edge_weight, g);
        for(std::size_t j = 0; j < num_edges; ++j) {
            edge_descriptor e; bool inserted;
            boost::tie(e, inserted) = add_edge(edge_array[j].first,
                                               edge_array[j].second, g);
            weightmap[e] = weights[j];
        }

//        // Now lets add edges and change their weights
//        for(std::size_t j = 0; j < num_edges; ++j) {
//            add_edge(edge_array[j].first,
//                     edge_array[j].second, g);
//            weight_map[j] = weights[j];
//        }

        // get the updated edges weights
//        weight_map = get(&EdgeProps::weight, g);
//
//        // traverse through them and get print the weights
//        for(std::size_t j = 0; j < num_edges; ++j) {
//            std::cout<<weight_map[j];
//        }


        // pick random start/goal
        boost::mt19937 gen(time(0));
        vertex start = random_vertex(g, gen);
        vertex goal = random_vertex(g, gen);

        // Printing the start and goal vertex's name
        std::cout << "Start vertex: " << objs[start]->get_name() << std::endl;
        std::cout << "Goal vertex: " << objs[goal]->get_name() << std::endl;

        std::vector<Graph::vertex_descriptor> p(num_vertices(g));
        std::vector<std::shared_ptr<Node>> d(num_vertices(g));
        try {
            // call astar named parameter interface
            astar_search_tree
                    (
                         g, start,
                         distance_heuristic<Graph, cost ,  EdgeProps*>
                                 (edge_weights, goal),
                         boost::predecessor_map(&p[0]).distance_map(&d[0]).
                                 visitor(astar_goal_visitor<vertex>(goal))
                     );


        } catch(found_goal fg) { // found a path to the goal
            std::list<vertex> shortest_path;
            for(vertex v = goal;; v = p[v]) {
                shortest_path.push_front(v);
                if(p[v] == v)
                    break;
            }
            std::cout << "Shortest path from " << objs[start]->get_name() << " to "
                 << objs[goal]->get_name() << ": ";
            std::list<vertex>::iterator spi = shortest_path.begin();
            std::cout << objs[start]->get_name();
            for(++spi; spi != shortest_path.end(); ++spi)
                std::cout << " -> " << objs[*spi]->get_name();
            std::cout << std::endl << "Total travel time: " << d[goal]->get_name() << std::endl;
            return 0;
        }

        std::cout << "Didn't find a path from " << objs[start]->get_name() << "to"
             << objs[goal]->get_name() << "!" << std::endl;
        return 0;
}