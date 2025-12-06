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
class Container
{
public:
    virtual ~Container() = default;
    
    // Основные методы
    virtual void Push(const T& value) = 0;
    virtual void Push(T&& value) = 0;
    virtual void Pop() = 0;
    virtual T& GetFront() = 0;
    virtual const T& GetFront() const = 0;
    virtual bool IsEmpty() const = 0;
    virtual size_t Size() const = 0;
    
    // Присваивание
    virtual Container<T>& operator=(const Container<T>& other) = 0;
    virtual Container<T>& operator=(Container<T>&& other) = 0;
    
    // Ввод/вывод
    friend std::ostream& operator<<(std::ostream& os, const Container<T>& container)
    {
        container.Print(os);
        return os;
    }
    
    friend std::istream& operator>>(std::istream& is, Container<T>& container)
    {
        T value;
        if (is >> value)
        {
            container.Push(value);
        }
        return is;
    }

protected:
    virtual void Print(std::ostream& os) const = 0;
};

#endif