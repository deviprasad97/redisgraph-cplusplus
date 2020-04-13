//
// Created by devi on 1/9/20.
//

#include <boost/graph/graphviz.hpp>
#include <boost/property_map/transform_value_property_map.hpp>
#include <iostream>

class my_custom_class {
public:
    my_custom_class(const std::string &my_string, int my_int) : my_string(my_string), my_int(my_int) {}
    virtual ~my_custom_class() {}

    std::string get_my_string() const { return my_string; }
    int get_int() const { return my_int; }

    bool operator==(const my_custom_class &rhs) const { return my_string == rhs.my_string && my_int == rhs.my_int; }
    bool operator!=(const my_custom_class &rhs) const { return !(rhs == *this); }

private:
    std::string my_string;
    int my_int;
};

namespace boost {
    enum vertex_my_custom_class_t { vertex_my_custom_class = 123 };
    BOOST_INSTALL_PROPERTY(vertex, my_custom_class);
}

int main1() {
    typedef boost::adjacency_list<boost::vecS, boost::setS, boost::directedS,
            boost::property<boost::vertex_my_custom_class_t, std::shared_ptr<my_custom_class> > >
            graph_t;

    typedef boost::graph_traits<graph_t>::vertex_descriptor vertex_t;

    std::shared_ptr<my_custom_class> object_one = std::make_shared<my_custom_class>("Lorem", 123);
    std::shared_ptr<my_custom_class> object_two = std::make_shared<my_custom_class>("ipsum", 456);
    std::shared_ptr<my_custom_class> object_three = std::make_shared<my_custom_class>("Lorem", 123);

    std::cout << "object one: " << object_one->get_int() << "; " << object_one->get_my_string() << std::endl;
    std::cout << "object two: " << object_two->get_int() << "; " << object_two->get_my_string() << std::endl;
    std::cout << "object three: " << object_three->get_int() << "; " << object_three->get_my_string() << std::endl;

    std::cout << std::endl;

    std::cout << "object one == object two: " << (*object_one == *object_two) << std::endl;
    std::cout << "object one == object three: " << (*object_one == *object_three) << std::endl;

    std::cout << std::endl;

    graph_t graph;

    vertex_t vertex_one = boost::add_vertex(object_one, graph);
    vertex_t vertex_two = boost::add_vertex(object_two, graph);
    vertex_t vertex_three = boost::add_vertex(object_three, graph);

    boost::add_edge(vertex_one, vertex_two, graph);
    boost::add_edge(vertex_one, vertex_three, graph);

    {
        boost::dynamic_properties dp;
        boost::property_map<graph_t, boost::vertex_my_custom_class_t>::type custom = get(boost::vertex_my_custom_class, graph);
        dp.property("node_id", boost::make_transform_value_property_map(std::mem_fn(&my_custom_class::get_int), custom));
        dp.property("label", boost::make_transform_value_property_map(std::mem_fn(&my_custom_class::get_my_string), custom));
        boost::write_graphviz_dp(std::cout, graph, dp);
    }

    return 0;
}