template <typename T, size_t k>
Tree<T, k>::Tree() : root(nullptr) {}

template <typename T, size_t k>
void Tree<T, k>::add_root(Node<T>& root)
{
    this->root = new Node<T>(root.get_value());
}

template <typename T, size_t k>
void Tree<T, k>::add_sub_node(Node<T>& root_node, Node<T>& child)
{
    Node<T>* nodeInTree = findNode(root, root_node.get_value());
    if (nodeInTree)
    {
        nodeInTree->addChild(new Node<T>(child.get_value()));
    }
}

template <typename T, size_t k>
Node<T>* Tree<T, k>::findNode(Node<T>* root, T value)
{
    if (!root)
    {
        return nullptr;
    }
    if (root->get_value() == value)
    {
        return root;
    }
    for (auto child : root->getChildren())
    {
        Node<T>* theNode = findNode(child, value);
        if (theNode)
        {
            return theNode;
        }
    }
    return nullptr;
}

template <typename T, size_t k>
Tree<T, k>::Iterator::Iterator(Node<T>* root, const std::string& traversal_type) : current(nullptr)
{
    if (traversal_type == "pre_order")
    {
        pre_order_traversal(root);
    }
    else if (traversal_type == "post_order")
    {
        post_order_traversal(root);
    }
    else if (traversal_type == "in_order")
    {
        in_order_traversal(root);
    }
    else if (traversal_type == "bfs")
    {
        bfs_traversal(root);
    }
    else if (traversal_type == "dfs")
    {
        dfs_traversal(root);
    }
    if (!queue.empty())
    {
        current = queue.front();
        queue.pop();
    }
}

template <typename T, size_t k>
Node<T>& Tree<T, k>::Iterator::operator*() {
    return *current;
}

template <typename T, size_t k>
Node<T>* Tree<T, k>::Iterator::operator->() {
    return current;
}

template <typename T, size_t k>
typename Tree<T, k>::Iterator& Tree<T, k>::Iterator::operator++() {
    if (!queue.empty())
    {
        current = queue.front();
        queue.pop();
    }
    else
    {
        current = nullptr;
    }
    return *this;
}

template <typename T, size_t k>
typename Tree<T, k>::Iterator Tree<T, k>::Iterator::operator++(int) {
    Iterator tmp = *this;
    ++(*this);
    return tmp;
}

template <typename T, size_t k>
bool Tree<T, k>::Iterator::operator==(const Iterator& other) const {
    return current == other.current;
}

template <typename T, size_t k>
bool Tree<T, k>::Iterator::operator!=(const Iterator& other) const {
    return current != other.current;
}

template <typename T, size_t k>
void Tree<T, k>::Iterator::pre_order_traversal(Node<T>* node) {
    if (node)
    {
        queue.push(node);
        for (auto it = node->getChildren().begin(); it != node->getChildren().end(); ++it)
        {
            pre_order_traversal(*it);
        }
    }
}

template <typename T, size_t k>
void Tree<T, k>::Iterator::post_order_traversal(Node<T>* node) {
    if (node) {
        for (auto child : node->getChildren())
        {
            post_order_traversal(child);
        }
        queue.push(node);
    }
}

template <typename T, size_t k>
void Tree<T, k>::Iterator::in_order_traversal(Node<T>* node) {
    if (node) {
        auto& children = node->getChildren();
        if (!children.empty()) {
            in_order_traversal(children[0]);
        }
        queue.push(node);
        for (size_t i = 1; i < children.size(); ++i) {
            in_order_traversal(children[i]);
        }
    }
}

template <typename T, size_t k>
void Tree<T, k>::Iterator::bfs_traversal(Node<T>* node)
{
    std::queue<Node<T>*> tempQueue;
    if (node)
    {
        queue.push(node);
        while (!queue.empty())
        {
            Node<T>* current = queue.front();
            queue.pop();
            tempQueue.push(current);
            for (auto child : current->getChildren())
            {
                queue.push(child);
            }
        }
    }
    queue = tempQueue;
}
template <typename T, size_t k>
void Tree<T, k>::Iterator::dfs_traversal(Node<T>* node)
{
    if (node == nullptr)
    {
        return;
    }
    queue.push(node);
    for (auto child : node->getChildren())
    {
        dfs_traversal(child);
    }
}
template <typename T, size_t k>
typename Tree<T, k>::Iterator Tree<T, k>::begin_pre_order() {
    return Iterator(root, "pre_order");
}

template <typename T, size_t k>
typename Tree<T, k>::Iterator Tree<T, k>::end_pre_order() {
    return Iterator(nullptr);
}

template <typename T, size_t k>
typename Tree<T, k>::Iterator Tree<T, k>::begin_post_order() {
    return Iterator(root, "post_order");
}

template <typename T, size_t k>
typename Tree<T, k>::Iterator Tree<T, k>::end_post_order() {
    return Iterator(nullptr);
}

template <typename T, size_t k>
typename Tree<T, k>::Iterator Tree<T, k>::begin_in_order() {
    return Iterator(root, "in_order");
}

template <typename T, size_t k>
typename Tree<T, k>::Iterator Tree<T, k>::end_in_order() {
    return Iterator(nullptr);
}

template <typename T, size_t k>
typename Tree<T, k>::Iterator Tree<T, k>::begin_bfs_scan() {
    return Iterator(root, "bfs");
}

template <typename T, size_t k>
typename Tree<T, k>::Iterator Tree<T, k>::end_bfs_scan() {
    return Iterator(nullptr);
}

template <typename T, size_t k>
typename Tree<T, k>::Iterator Tree<T, k>::begin_dfs_scan() {
    return Iterator(root, "dfs");
}

template <typename T, size_t k>
typename Tree<T, k>::Iterator Tree<T, k>::end_dfs_scan() {
    return Iterator(nullptr);
}

template <typename T, size_t k>
typename Tree<T, k>::Iterator Tree<T, k>::begin() {
    return begin_bfs_scan();
}

template <typename T, size_t k>
typename Tree<T, k>::Iterator Tree<T, k>::end() {
    return end_bfs_scan();
}
