#ifndef NODE_H
#define NODE_H

template <typename T>
class Node
{
public:
    T data;
    Node* next;
    
    Node(const T& value) : data(value), next(nullptr)
    {
    }
    
    Node(T&& value) : data(std::move(value)), next(nullptr)
    {
    }
    
    Node(const Node&) = delete;
    Node& operator=(const Node&) = delete;
    
    Node(Node&& other) noexcept : data(std::move(other.data)), next(other.next)
    {
        other.next = nullptr;
    }
    
    Node& operator=(Node&& other) noexcept
    {
        if (this != &other)
        {
            data = std::move(other.data);
            next = other.next;
            other.next = nullptr;
        }
        return *this;
    }
    
    ~Node() = default;
};

#endif