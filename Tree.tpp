#ifndef TREE_TPP
#define TREE_TPP

#include <memory>
#include <vector>
#include <stdexcept>
#include <queue>
#include <sstream>
#include <iostream>
#include <algorithm>
#include "Node.hpp"
#include "Tree.hpp"

template <typename T, size_t k>
Tree<T, k>::Tree() : root(nullptr) {}

template <typename T, size_t k>
void Tree<T, k>::add_root(Node<T>& root) {
    this->root = new Node<T>(root.getValue());
}
template <typename T, size_t k>
Tree<T, k>::~Tree() {
    deleteSubTree(root);
}
template <typename T, size_t k>

void Tree<T, k>::deleteSubTree(Node<T>* node) 
{
    if (node) 
    {
        for (auto child : node->getChildren())
        {
            deleteSubTree(child);
        }
        delete node;
    }
}

template <typename T, size_t k>
void Tree<T, k>::add_sub_node(Node<T>& root_node, Node<T>& child) {
    Node<T>* nodeInTree = findNode(this->root, root_node.getValue());
    if (nodeInTree) {
        nodeInTree->addChild(new Node<T>(child.getValue()));
    }
}

template <typename T, size_t k>
Node<T>* Tree<T, k>::findNode(Node<T>* root, T value) {
    if (!root) {
        return nullptr;
    }
    if (root->getValue() == value) {
        return root;
    }
    for (auto child : root->getChildren()) {
        Node<T>* theNode = findNode(child, value);
        if (theNode) {
            return theNode;
        }
    }
    return nullptr;
}

template <typename T, size_t k>
Node<T>* Tree<T, k>::getRoot() {
    return root;
}

template <typename T, size_t k>
Tree<T, k>::Iterator::Iterator(Node<T>* root, const std::string& traversal_type) : current(nullptr), index(0) {
    if (traversal_type == "pre_order") {
        pre_order_traversal(root);
    } else if (traversal_type == "post_order") {
        post_order_traversal(root);
    } else if (traversal_type == "in_order") {
        in_order_traversal(root);
    } else if (traversal_type == "bfs") {
        bfs_traversal(root);
    } else if (traversal_type == "dfs") {
        dfs_traversal(root);
    } else if (traversal_type == "myHeap")
    {
        buildHeap(root);
        heapify();
    }
    if (!queue.empty()) {
        current = queue.front();
        queue.pop();
    }
    if (!heapNodes.empty()) {
        current = heapNodes[index];
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
    if (!heapNodes.empty() && index < heapNodes.size() - 1) {
        ++index;
        current = heapNodes[index];
    } else if (!queue.empty()) {
        current = queue.front();
        queue.pop();
    } else {
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
    if (node)
    {
        for (auto child : node->getChildren())
        {
            post_order_traversal(child);
        }
        queue.push(node);
    }
}

template <typename T, size_t k>
void Tree<T, k>::Iterator::in_order_traversal(Node<T>* node) {
    if (node)
    {
        auto& children = node->getChildren();
        if (!children.empty())
        {
            in_order_traversal(children[0]);
        }
        queue.push(node);
        for (size_t i = 1; i < children.size(); ++i)
        {
            in_order_traversal(children[i]);
        }
    }
}

template <typename T, size_t k>
void Tree<T, k>::Iterator::bfs_traversal(Node<T>* node) {
    std::queue<Node<T>*> tempQueue;
    if (node) {
        queue.push(node);
        while (!queue.empty()) {
            Node<T>* current = queue.front();
            queue.pop();
            tempQueue.push(current);
            for (auto child : current->getChildren()) {
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
void Tree<T, k>::Iterator::buildHeap(Node<T>* node)
{
    if (!node)
    {
        return;
    }
    std::queue<Node<T>*> tempQueue;
    tempQueue.push(node);
    while (!tempQueue.empty())
    {
        Node<T>* current = tempQueue.front();
        tempQueue.pop();
        heapNodes.push_back(current);

        for (auto child : current->getChildren())
        {
            tempQueue.push(child);
        }
    }
}


template <typename T, size_t k>
void Tree<T, k>::Iterator::heapify()
{
    std::make_heap(heapNodes.begin(), heapNodes.end(), [](Node<T>* a, Node<T>* b) {
        return a->getValue() < b->getValue();
    });

    std::sort_heap(heapNodes.begin(), heapNodes.end(), [](Node<T>* a, Node<T>* b) {
        return a->getValue() < b->getValue();
    });
}

template <typename T, size_t k>
void Tree<T, k>::myHeap()
{
    heapify(root);
}

template <typename T, size_t k>
typename Tree<T, k>::Iterator Tree<T, k>::begin_pre_order()
{
    return Iterator(root, "pre_order");
}

template <typename T, size_t k>
typename Tree<T, k>::Iterator Tree<T, k>::end_pre_order()
{
    return Iterator(nullptr);
}

template <typename T, size_t k>
typename Tree<T, k>::Iterator Tree<T, k>::begin_post_order()
{
    return Iterator(root, "post_order");
}

template <typename T, size_t k>
typename Tree<T, k>::Iterator Tree<T, k>::end_post_order()
{
    return Iterator(nullptr);
}

template <typename T, size_t k>
typename Tree<T, k>::Iterator Tree<T, k>::begin_in_order()
{
    return Iterator(root, "in_order");
}

template <typename T, size_t k>
typename Tree<T, k>::Iterator Tree<T, k>::end_in_order()
{
    return Iterator(nullptr);
}

template <typename T, size_t k>
typename Tree<T, k>::Iterator Tree<T, k>::begin_bfs_scan()
{
    return Iterator(root, "bfs");
}

template <typename T, size_t k>
typename Tree<T, k>::Iterator Tree<T, k>::end_bfs_scan()
{
    return Iterator(nullptr);
}

template <typename T, size_t k>
typename Tree<T, k>::Iterator Tree<T, k>::begin_dfs_scan()
{
    return Iterator(root, "dfs");
}

template <typename T, size_t k>
typename Tree<T, k>::Iterator Tree<T, k>::end_dfs_scan()
{
    return Iterator(nullptr);
}

template <typename T, size_t k>
typename Tree<T, k>::Iterator Tree<T, k>::begin_heap()
{
    return Iterator(root, "myHeap");
}

template <typename T, size_t k>
typename Tree<T, k>::Iterator Tree<T, k>::end_heap() {
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

template <typename T, size_t k>
std::ostream& operator<<(std::ostream& os, Tree<T, k>& tree) {
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML Tree Example");
    // Load the font
    sf::Font font;
    if (!font.loadFromFile("./Lato-BlackItalic.ttf")) {
        std::cerr << "Failed to load font!" << std::endl;
        // Exit if the font is not loaded
    } else {
        window.clear(sf::Color::White);
        tree.drawTree(window, tree.getRoot(), 400, 50, 200, font);
        window.display();
        while (window.isOpen()) {
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    window.close();
                }
            }
        }
    }
    return os;
}

template <typename T, size_t k>
void Tree<T, k>::drawTree(sf::RenderWindow& window, Node<T>* node, int x, int y, int horizontal_gap, sf::Font& font) 
{
    if (!node) 
    {
        return;
    }
    // Drawing circle and lines...
    sf::Color circleColor = sf::Color::Blue; // Red color for circles
    sf::Color outlineColor = sf::Color::Black; // Black color for circle outline
    sf::Color textColor = sf::Color::Black; // Black color for text

    // Draw circle
    sf::CircleShape circle(30); // Circle radius
    circle.setFillColor(circleColor);
    circle.setOutlineThickness(2);
    circle.setOutlineColor(outlineColor);
    circle.setPosition(x, y);
    window.draw(circle);

    // Convert value to string with fixed precision
    T value = node->getValue();
    std::ostringstream oss;
    oss.precision(1);
    oss << std::fixed << value;
    std::string text = oss.str();

    // Draw text
    sf::Text textObject(text, font, 20);
    textObject.setFillColor(textColor);
    sf::FloatRect textBounds = textObject.getLocalBounds();
    textObject.setOrigin(textBounds.left + textBounds.width / 2.0f, textBounds.top + textBounds.height / 2.0f);
    textObject.setPosition(x + circle.getRadius(), y + circle.getRadius());
    window.draw(textObject);

    // Draw lines to children
    auto children = node->getChildren();
    int num_children = children.size();
    if (num_children > 0) {
        for (int i = 0; i < num_children; ++i) {
            int child_x = x - horizontal_gap / 2 + i * horizontal_gap;
            int child_y = y + 100;

            sf::Vertex line[] = {
                sf::Vertex(sf::Vector2f(x + circle.getRadius(), y + 2 * circle.getRadius())),
                sf::Vertex(sf::Vector2f(child_x + circle.getRadius(), child_y))
            };
            line[0].color = sf::Color::Black;
            line[1].color = sf::Color::Black;
            window.draw(line, 2, sf::Lines);

            drawTree(window, children[i], child_x, child_y, horizontal_gap / 2, font);
        }
    }
}
#endif // TREE_TPP
