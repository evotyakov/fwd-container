#ifndef NODE_H
#define NODE_H

// Узел
template <typename T>
class node
{
public:
    T data;
    node* next;
    
    node(const T& value) : data(value), next(nullptr) {}
    
    node(T&& value) : data(std::move(value)), next(nullptr) {}
    
    node(const node&) = delete;
    node& operator=(const node&) = delete;
    
    node(node&& other) noexcept : data(std::move(other.data)), next(other.next)
    {
        other.next = nullptr;
    }
    
    node& operator=(node&& other) noexcept
    {
        if (this != &other)
        {
            data = std::move(other.data);
            next = other.next;
            other.next = nullptr;
        }
        return *this;
    }
    
    ~node() = default;
};

#endif