#ifndef QUEUE_IMPL_H
#define QUEUE_IMPL_H

#include <iostream>
#include <stdexcept>

// Конструкторы
template <typename T>
Queue<T>::Queue() : front_(nullptr), rear_(nullptr), size_(0)
{
}

template <typename T>
Queue<T>::Queue(const Queue& other) : front_(nullptr), rear_(nullptr), size_(0)
{
    CopyFrom(other);
}

template <typename T>
Queue<T>::Queue(Queue&& other) noexcept 
    : front_(other.front_), rear_(other.rear_), size_(other.size_)
{
    other.front_ = nullptr;
    other.rear_ = nullptr;
    other.size_ = 0;
}

template <typename T>
Queue<T>::Queue(const Container<T>& other) : front_(nullptr), rear_(nullptr), size_(0)
{
    CopyFrom(other);
}

// Деструктор
template <typename T>
Queue<T>::~Queue()
{
    Clear();
}

// Очистка очереди
template <typename T>
void Queue<T>::Clear()
{
    while (!IsEmpty())
    {
        Pop();
    }
}

// Копирование из другой очереди
template <typename T>
void Queue<T>::CopyFrom(const Queue& other)
{
    Node<T>* current = other.front_;
    while (current)
    {
        Push(current->data);
        current = current->next;
    }
}

// Копирование из контейнера
template <typename T>
void Queue<T>::CopyFrom(const Container<T>& other)
{
    Container<T>* nonConstOther = const_cast<Container<T>*>(&other);
    Container<T>* temp = new Queue<T>;
    
    // Копируем элементы
    while (!nonConstOther->IsEmpty())
    {
        T value = nonConstOther->GetFront();
        this->Push(value);
        temp->Push(value);
        nonConstOther->Pop();
    }
    
    // Восстанавливаем оригинал
    while (!temp->IsEmpty())
    {
        nonConstOther->Push(temp->GetFront());
        temp->Pop();
    }
    
    delete temp;
}

// Операции присваивания
template <typename T>
Queue<T>& Queue<T>::operator=(const Queue<T>& other)
{
    if (this != &other)
    {
        Clear();
        CopyFrom(other);
    }
    return *this;
}

template <typename T>
Queue<T>& Queue<T>::operator=(Queue<T>&& other) noexcept
{
    if (this != &other)
    {
        Clear();
        front_ = other.front_;
        rear_ = other.rear_;
        size_ = other.size_;
        other.front_ = nullptr;
        other.rear_ = nullptr;
        other.size_ = 0;
    }
    return *this;
}

template <typename T>
Container<T>& Queue<T>::operator=(const Container<T>& other)
{
    Clear();
    CopyFrom(other);
    return *this;
}

template <typename T>
Container<T>& Queue<T>::operator=(Container<T>&& other)
{
    Queue<T>* otherQueue = dynamic_cast<Queue<T>*>(&other);
    if (otherQueue)
    {
        *this = std::move(*otherQueue);
    }
    else
    {
        Clear();
        CopyFrom(other);
    }
    return *this;
}

// Основные методы
template <typename T>
void Queue<T>::Push(const T& value)
{
    Node<T>* newNode = new Node<T>(value);
    
    if (IsEmpty())
    {
        front_ = rear_ = newNode;
    }
    else
    {
        rear_->next = newNode;
        rear_ = newNode;
    }
    ++size_;
}

template <typename T>
void Queue<T>::Push(T&& value)
{
    Node<T>* newNode = new Node<T>(std::move(value));
    
    if (IsEmpty())
    {
        front_ = rear_ = newNode;
    }
    else
    {
        rear_->next = newNode;
        rear_ = newNode;
    }
    ++size_;
}

template <typename T>
void Queue<T>::Pop()
{
    if (IsEmpty())
    {
        throw EmptyContainerException();
    }
    
    Node<T>* temp = front_;
    front_ = front_->next;
    
    if (front_ == nullptr)
    {
        rear_ = nullptr;
    }
    
    delete temp;
    --size_;
}

template <typename T>
T& Queue<T>::GetFront()
{
    if (IsEmpty())
    {
        throw EmptyContainerException();
    }
    return front_->data;
}

template <typename T>
const T& Queue<T>::GetFront() const
{
    if (IsEmpty())
    {
        throw EmptyContainerException();
    }
    return front_->data;
}

template <typename T>
bool Queue<T>::IsEmpty() const
{
    return front_ == nullptr;
}

template <typename T>
size_t Queue<T>::Size() const
{
    return size_;
}

template <typename T>
void Queue<T>::Print(std::ostream& os) const
{
    Node<T>* current = front_;
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