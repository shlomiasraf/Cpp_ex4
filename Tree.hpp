#ifndef TREE_HPP
#define TREE_HPP

#include "Node.hpp"
#include <stack>
#include <queue>
#include <iterator>

template <typename T, size_t k = 2>
class Tree {
private:
    Node<T>* root;
public:
    Tree();
    void add_root(Node<T>& root);
    void add_sub_node(Node<T>& root_node, Node<T>& child);
    Node<T>* findNode(Node<T>*, T);
    class Iterator;

    Iterator begin_pre_order();
    Iterator end_pre_order();
    Iterator begin_post_order();
    Iterator end_post_order();
    Iterator begin_in_order();
    Iterator end_in_order();
    Iterator begin_bfs_scan();
    Iterator end_bfs_scan();
    Iterator begin_dfs_scan();
    Iterator end_dfs_scan();

    Iterator begin();  // For range-based for loop
    Iterator end();    // For range-based for loop

    class Iterator
    {
        private:
            Node<T>* current;
            std::queue<Node<T>*> queue;

            void pre_order_traversal(Node<T>* node);
            void post_order_traversal(Node<T>* node);
            void in_order_traversal(Node<T>* node);
            void bfs_traversal(Node<T>* node);
            void dfs_traversal(Node<T>* node);

        public:
            Iterator(Node<T>* root = nullptr, const std::string& traversal_type = "pre_order");
            Node<T>& operator*();
            Node<T>* operator->();
            Iterator& operator++();
            Iterator operator++(int);
            bool operator==(const Iterator& other) const;
            bool operator!=(const Iterator& other) const;
    };
};

#include "Tree.tpp"

#endif // TREE_HPP
