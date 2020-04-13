//
// Created by devi on 1/9/20.
//
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/kruskal_min_spanning_tree.hpp>
#include <boost/property_map/transform_value_property_map.hpp>
#include <boost/graph/graphviz.hpp>
#include <iostream>
#include <fstream>
#include "Node.h"
#include <boost/graph/astar_search.hpp>
#include <boost/graph/random.hpp>
#include <boost/random.hpp>

namespace boost {
    enum vertex_Node_t { vertex_Node = 0 };
    BOOST_INSTALL_PROPERTY(vertex, Node);
}

int main() {
    typedef boost::adjacency_list< boost::vecS, boost::vecS, boost::undirectedS,
            boost::property<boost::vertex_Node_t, std::shared_ptr<Node> > > Graph;


    typedef boost::graph_traits <Graph>::edge_descriptor Edge;
    typedef boost::graph_traits <Graph>::vertex_descriptor Vertex;
    typedef std::pair<int, int> E;


    std::shared_ptr<Node> object_one = std::make_shared<Node>(123, "obj1");
    std::shared_ptr<Node> object_two = std::make_shared<Node>(456, "obj2");
    std::shared_ptr<Node> object_three = std::make_shared<Node>(789, "obj3");

    std::shared_ptr<Node> object_four = std::make_shared<Node>(101, "obj4");
    std::shared_ptr<Node> object_five = std::make_shared<Node>(121, "obj5");
    std::shared_ptr<Node> object_six = std::make_shared<Node>(145, "obj6");

    const int num_nodes = 5;
    E edge_array[] = { E(0, 2), E(1, 3), E(1, 4), E(2, 1), E(2, 3),
                       E(3, 4), E(4, 0), E(4, 1)
    };
    int weights[] = { 1, 1, 2, 7, 3, 1, 1, 1 };
    std::size_t num_edges = sizeof(edge_array) / sizeof(E);

    Graph g;

    Vertex vertex_one = boost::add_vertex(object_one, g);
    Vertex vertex_two = boost::add_vertex(object_two, g);
    Vertex vertex_three = boost::add_vertex(object_three, g);
    Vertex vertex_four = boost::add_vertex(object_four, g);
    Vertex vertex_five = boost::add_vertex(object_five, g);
    Vertex vertex_six = boost::add_vertex(object_six, g);

    boost::add_edge(vertex_one, vertex_two, g);
    boost::add_edge(vertex_one, vertex_three, g);
    boost::add_edge(vertex_two, vertex_six, g);
    boost::add_edge(vertex_three, vertex_five, g);
    boost::add_edge(vertex_five, vertex_two, g);
    boost::add_edge(vertex_six, vertex_one, g);
/*
    boost::property_map<Graph, boost::edge_weight_t >::type weight = get(boost::edge_weight, g);
    std::vector < Edge > spanning_tree;

    boost::kruskal_minimum_spanning_tree(g, std::back_inserter(spanning_tree));

    std::cout << "Print the edges in the MST:" << std::endl;

    for (std::vector < Edge >::iterator ei = spanning_tree.begin();
         ei != spanning_tree.end(); ++ei)
    {
        std::cout << source(*ei, g)
                  << " <--> "
                  << target(*ei, g)
                  << " with weight of "
                  << weight[*ei]
                  << std::endl;
    }*/

    {
        boost::dynamic_properties dp;
        boost::property_map<Graph , boost::vertex_Node_t>::type custom = get(boost::vertex_Node, g);
        dp.property("node_id", boost::make_transform_value_property_map(std::mem_fn(&Node::get_id), custom));
        dp.property("label", boost::make_transform_value_property_map(std::mem_fn(&Node::get_name), custom));
        boost::write_graphviz_dp(std::cout, g, dp);
    }

    std::vector < Edge > spanning_tree;
    boost::kruskal_minimum_spanning_tree(g, std::back_inserter(spanning_tree));
    std::cout << "Print the edges in the MST:" << std::endl;

    for (std::vector < Edge >::iterator ei = spanning_tree.begin();
         ei != spanning_tree.end(); ++ei)
    {
        std::cout << source(*ei, g)
                  << " <--> "
                  << target(*ei, g)
                  << std::endl;
    }

    return 0;
}