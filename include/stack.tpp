#ifndef STACK_IMPL_H
#define STACK_IMPL_H

#include <iostream>
#include <stdexcept>

// Конструкторы
template <typename T>
stack<T>::stack() : top(nullptr), length(0) {}

template <typename T>
stack<T>::stack(const stack& other) : top(nullptr), length(0)
{
    copy_from(other);
}

template <typename T>
stack<T>::stack(stack&& other) noexcept : top(other.top), length(other.length)
{
    other.top = nullptr;
    other.length = 0;
}

template <typename T>
stack<T>::stack(const fwd_container<T>& other) : top(nullptr), length(0)
{
    copy_from(other);
}

// Деструктор
template <typename T>
stack<T>::~stack()
{
    clear();
}

// Очистка стека
template <typename T>
void stack<T>::clear()
{
    while (!is_empty())
    {
        pop();
    }
}

// Копирование из другого стека
template <typename T>
void stack<T>::copy_from(const stack& other)
{
    if (other.is_empty())
    {
        top = nullptr;
        length = 0;
        return;
    }
    
    T* temp = new T[other.length];
    node<T>* current = other.top;
    
    for (size_t i = other.length; i > 0; --i)
    {
        temp[i - 1] = current->data;
        current = current->next;
    }
    
    for (size_t i = 0; i < other.length; ++i)
    {
        push(temp[i]);
    }
    
    delete[] temp;
}

// Копирование из контейнера
template <typename T>
void stack<T>::copy_from(const fwd_container<T>& other)
{
    stack<T> temp;
    fwd_container<T>* tempContainer = &temp;
    
    fwd_container<T>* otherCopy = dynamic_cast<fwd_container<T>*>(const_cast<fwd_container<T>*>(&other));
    if (!otherCopy)
    {
        throw std::bad_cast();
    }

    stack<T> reversed;
    size_t length = other.size();
    T* elements = new T[length];
    
    size_t index = 0;
    fwd_container<T>* nonConstOther = const_cast<fwd_container<T>*>(&other);
    while (!nonConstOther->is_empty())
    {
        elements[index++] = nonConstOther->get_front();
        nonConstOther->pop();
    }
    
    for (size_t i = length; i > 0; --i)
    {
        this->push(elements[i - 1]);
        const_cast<fwd_container<T>*>(&other)->push(elements[i - 1]);
    }
    
    delete[] elements;
}

// Операции присваивания
template <typename T>
stack<T>& stack<T>::operator=(const stack<T>& other)
{
    if (this != &other)
    {
        clear();
        copy_from(other);
    }
    return *this;
}

template <typename T>
stack<T>& stack<T>::operator=(stack<T>&& other) noexcept
{
    if (this != &other)
    {
        clear();
        top = other.top;
        length = other.length;
        other.top = nullptr;
        other.length = 0;
    }
    return *this;
}

template <typename T>
fwd_container<T>& stack<T>::operator=(const fwd_container<T>& other)
{
    clear();
    copy_from(other);
    return *this;
}

template <typename T>
fwd_container<T>& stack<T>::operator=(fwd_container<T>&& other)
{
    stack<T>* otherStack = dynamic_cast<stack<T>*>(&other);
    if (otherStack)
    {
        *this = std::move(*otherStack);
    }
    else
    {
        clear();
        copy_from(other);
    }
    return *this;
}

// Основные методы
template <typename T>
void stack<T>::push(const T& value)
{
    node<T>* new_node = new node<T>(value);
    new_node->next = top;
    top = new_node;
    ++length;
}

template <typename T>
void stack<T>::push(T&& value)
{
    node<T>* new_node = new node<T>(std::move(value));
    new_node->next = top;
    top = new_node;
    ++length;
}

template <typename T>
void stack<T>::pop()
{
    if (is_empty())
    {
        throw EmptyContainerException();
    }
    
    node<T>* temp = top;
    top = top->next;
    delete temp;
    --length;
}

template <typename T>
T& stack<T>::get_front()
{
    if (is_empty())
    {
        throw EmptyContainerException();
    }
    return top->data;
}

template <typename T>
const T& stack<T>::get_front() const
{
    if (is_empty())
    {
        throw EmptyContainerException();
    }
    return top->data;
}

template <typename T>
bool stack<T>::is_empty() const
{
    return top == nullptr;
}

template <typename T>
size_t stack<T>::size() const
{
    return length;
}

template <typename T>
void stack<T>::print(std::ostream& os) const
{
    node<T>* current = top;
    os << "stack[";
    while (current)
    {
        os << current->data;
        if (current->next)
        {
            os << ", ";
        }
        current = current->next;
    }
    os << "]";
}

#endif