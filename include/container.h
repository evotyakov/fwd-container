#ifndef CONTAINER_H
#define CONTAINER_H

#include <iostream>
#include <exception>

// Базовый класс исключений
class ContainerException : public std::exception
{
public:
    const char* what() const noexcept override = 0;
};

// Конкретный класс исключений
class EmptyContainerException : public ContainerException
{
public:
    const char* what() const noexcept override
    {
        return "Container is empty";
    }
};

template <typename T>
class fwd_container
{
public:
    virtual ~fwd_container() = default;

    virtual void push(const T& value) = 0;
    virtual void push(T&& value) = 0;
    virtual void pop() = 0;
    virtual T& get_front() = 0;
    virtual const T& get_front() const = 0;
    virtual bool is_empty() const = 0;
    virtual size_t size() const = 0;

    virtual fwd_container<T>& operator=(const fwd_container<T>& other) = 0;
    virtual fwd_container<T>& operator=(fwd_container<T>&& other) = 0;

    friend std::ostream& operator<<(std::ostream& os, const fwd_container<T>& container)
    {
        container.print(os);
        return os;
    }
    
    friend std::istream& operator>>(std::istream& is, fwd_container<T>& container)
    {
        T value;
        if (is >> value)
        {
            container.push(value);
        }
        return is;
    }

protected:
    virtual void print(std::ostream& os) const = 0;
};

#endif