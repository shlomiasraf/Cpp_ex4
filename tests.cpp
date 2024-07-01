#include "doctest.h"
#include <iostream>
#include <string>
#include "Node.hpp"
#include "Tree.hpp"
#include <iostream>
#include <iomanip>
#include <sstream>

using namespace std;


std::string toString(double value)
{
    std::ostringstream out;
    out << std::fixed << std::setprecision(1) << value;
    return out.str();
}
TEST_CASE("Test everything")
{
    Node<double> root_node(1.1);

    Tree<double> tree; // Binary tree that contains doubles.
    tree.add_root(root_node);
    Node<double> n1(1.2);
    Node<double> n2(1.3);
    Node<double> n3(1.4);
    Node<double> n4(1.5);
    Node<double> n5(1.6);

    tree.add_sub_node(root_node, n1);
    tree.add_sub_node(root_node, n2);
    tree.add_sub_node(n1, n3);
    tree.add_sub_node(n1, n4);
    tree.add_sub_node(n2, n5);

    std::string preOrder;
    for (auto node = tree.begin_pre_order(); node != tree.end_pre_order(); ++node)
    {
        preOrder +=  toString(node->getValue());
        preOrder += " ";
    }
    CHECK(preOrder == "1.1 1.2 1.4 1.5 1.3 1.6 ");
    std::string postOrder;
    for(auto node = tree.begin_post_order(); node != tree.end_post_order(); ++node)
    {
        postOrder +=  toString(node->getValue());
        postOrder += " ";
    }
    CHECK(postOrder == "1.4 1.5 1.2 1.6 1.3 1.1 ");
    std::string inOrder;
    for (auto node = tree.begin_in_order(); node != tree.end_in_order(); ++node)
    {
        inOrder +=  toString(node->getValue());
        inOrder += " ";
    }
    CHECK(inOrder == "1.4 1.2 1.5 1.1 1.6 1.3 ");
    std::string bfsScan;
    for (auto node = tree.begin_bfs_scan(); node != tree.end_bfs_scan(); ++node)
    {
        bfsScan +=  toString(node->getValue());
        bfsScan += " ";
    }
    CHECK(bfsScan == "1.1 1.2 1.3 1.4 1.5 1.6 ");
    std::string dfsScan;
    for (auto node = tree.begin_dfs_scan(); node != tree.end_dfs_scan(); ++node)
    {
        dfsScan +=  toString(node->getValue());
        dfsScan += " ";
    }
    CHECK(dfsScan == "1.1 1.2 1.4 1.5 1.3 1.6 ");
    std::string heap;
    Node<double> root_node2(1.7);

    Tree<double> tree2; // Binary tree that contains doubles.
    tree2.add_root(root_node2);
    Node<double> t1(1.2);
    Node<double> t2(1.3);
    Node<double> t3(1.4);
    Node<double> t4(1.5);
    Node<double> t5(1.6);

    tree2.add_sub_node(root_node2, t1);
    tree2.add_sub_node(root_node2, t2);
    tree2.add_sub_node(t1, t3);
    tree2.add_sub_node(t1, t4);
    tree2.add_sub_node(t2, t5);
    for (auto it = tree2.begin_heap(); it != tree2.end_heap(); ++it)
    {
        heap +=  toString(it->getValue());
        heap += " ";
    }
    CHECK(heap == "1.2 1.3 1.4 1.5 1.6 1.7 ");
}
