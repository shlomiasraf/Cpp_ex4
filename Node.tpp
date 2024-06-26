template<typename T>
Node<T>::Node(T value) : value(value) {}

template<typename T>
T Node<T>::get_value() const
{
    return value;
}

template<typename T>
void Node<T>::addChild(Node<T>* child)
{
    this->children.push_back(new Node<T>(child->get_value()));
}

template<typename T>
const std::vector<Node<T>*>& Node<T>::getChildren() const
{
    return this->children;
}
