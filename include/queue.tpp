#ifndef QUEUE_TPP
#define QUEUE_TPP

#include <iostream>
#include <stdexcept>

// Конструкторы
template <typename T>
queue<T>::queue() : front(nullptr), rear(nullptr), length(0) {}

template <typename T>
queue<T>::queue(const queue& other) : front(nullptr), rear(nullptr), length(0)
{
    copy_from(other);
}

template <typename T>
queue<T>::queue(queue&& other) noexcept 
    : front(other.front), rear(other.rear), length(other.length)
{
    other.front = nullptr;
    other.rear = nullptr;
    other.length = 0;
}

template <typename T>
queue<T>::queue(const fwd_container<T>& other) : front(nullptr), rear(nullptr), length(0)
{
    copy_from(other);
}

// Деструктор
template <typename T>
queue<T>::~queue()
{
    clear();
}

// Очистка очереди
template <typename T>
void queue<T>::clear()
{
    while (!is_empty())
    {
        pop();
    }
}

// Копирование из другой очереди
template <typename T>
void queue<T>::copy_from(const queue& other)
{
    node<T>* current = other.front;
    while (current)
    {
        push(current->data);
        current = current->next;
    }
}

// Копирование из контейнера
template <typename T>
void queue<T>::copy_from(const fwd_container<T>& other)
{
    fwd_container<T>* nonConstOther = const_cast<fwd_container<T>*>(&other);
    fwd_container<T>* temp = new queue<T>;
    
    while (!nonConstOther->is_empty())
    {
        T value = nonConstOther->get_front();
        this->push(value);
        temp->push(value);
        nonConstOther->pop();
    }
    
    while (!temp->is_empty())
    {
        nonConstOther->push(temp->get_front());
        temp->pop();
    }
    
    delete temp;
}

// Операции присваивания
template <typename T>
queue<T>& queue<T>::operator=(const queue<T>& other)
{
    if (this != &other)
    {
        clear();
        copy_from(other);
    }
    return *this;
}

template <typename T>
queue<T>& queue<T>::operator=(queue<T>&& other) noexcept
{
    if (this != &other)
    {
        clear();
        front = other.front;
        rear = other.rear;
        length = other.length;
        other.front = nullptr;
        other.rear = nullptr;
        other.length = 0;
    }
    return *this;
}

template <typename T>
fwd_container<T>& queue<T>::operator=(const fwd_container<T>& other)
{
    clear();
    copy_from(other);
    return *this;
}

template <typename T>
fwd_container<T>& queue<T>::operator=(fwd_container<T>&& other)
{
    queue<T>* otherQueue = dynamic_cast<queue<T>*>(&other);
    if (otherQueue)
    {
        *this = std::move(*otherQueue);
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
void queue<T>::push(const T& value)
{
    node<T>* new_node = new node<T>(value);
    
    if (is_empty())
    {
        front = rear = new_node;
    }
    else
    {
        rear->next = new_node;
        rear = new_node;
    }
    ++length;
}

template <typename T>
void queue<T>::push(T&& value)
{
    node<T>* new_node = new node<T>(std::move(value));
    
    if (is_empty())
    {
        front = rear = new_node;
    }
    else
    {
        rear->next = new_node;
        rear = new_node;
    }
    ++length;
}

template <typename T>
void queue<T>::pop()
{
    if (is_empty())
    {
        throw EmptyContainerException();
    }
    
    node<T>* temp = front;
    front = front->next;
    
    if (front == nullptr)
    {
        rear = nullptr;
    }
    
    delete temp;
    --length;
}

template <typename T>
T& queue<T>::get_front()
{
    if (is_empty())
    {
        throw EmptyContainerException();
    }
    return front->data;
}

template <typename T>
const T& queue<T>::get_front() const
{
    if (is_empty())
    {
        throw EmptyContainerException();
    }
    return front->data;
}

template <typename T>
bool queue<T>::is_empty() const
{
    return front == nullptr;
}

template <typename T>
size_t queue<T>::size() const
{
    return length;
}

template <typename T>
void queue<T>::print(std::ostream& os) const
{
    node<T>* current = front;
    os << "Queue[";
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