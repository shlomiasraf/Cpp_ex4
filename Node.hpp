#ifndef NODE_HPP
#define NODE_HPP

#include <vector>
#include <stdexcept>

template <typename T>
class Node
{
private:
    T value;
    std::vector<Node<T>*> children;

public:
    Node(T val);
    T getValue() const;
    void addChild(Node<T>* child);
    const std::vector<Node<T>*>& getChildren() const;
};

#include "Node.tpp"

#endif // NODE_HPP
