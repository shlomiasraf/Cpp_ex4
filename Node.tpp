#include "Node.hpp"
template<typename T>
Node<T>::Node(T value) : value(value) {}

template<typename T>
T Node<T>::getValue() const
{
    return value;
}

template<typename T>
void Node<T>::addChild(Node<T>* child)
{
    this->children.push_back(child);
}

template<typename T>
const std::vector<Node<T>*>& Node<T>::getChildren() const
{
    return this->children;
}


