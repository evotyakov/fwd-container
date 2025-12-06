#ifndef STACK_IMPL_H
#define STACK_IMPL_H

#include <iostream>
#include <stdexcept>

// Конструкторы
template <typename T>
Stack<T>::Stack() : top_(nullptr), size_(0)
{
}

template <typename T>
Stack<T>::Stack(const Stack& other) : top_(nullptr), size_(0)
{
    CopyFrom(other);
}

template <typename T>
Stack<T>::Stack(Stack&& other) noexcept : top_(other.top_), size_(other.size_)
{
    other.top_ = nullptr;
    other.size_ = 0;
}

template <typename T>
Stack<T>::Stack(const Container<T>& other) : top_(nullptr), size_(0)
{
    CopyFrom(other);
}

// Деструктор
template <typename T>
Stack<T>::~Stack()
{
    Clear();
}

// Очистка стека
template <typename T>
void Stack<T>::Clear()
{
    while (!IsEmpty())
    {
        Pop();
    }
}

// Копирование из другого стека
template <typename T>
void Stack<T>::CopyFrom(const Stack& other)
{
    if (other.IsEmpty())
    {
        top_ = nullptr;
        size_ = 0;
        return;
    }
    
    // Создаем массив для временного хранения элементов
    T* temp = new T[other.size_];
    Node<T>* current = other.top_;
    
    // Собираем элементы в обратном порядке
    for (size_t i = other.size_; i > 0; --i)
    {
        temp[i - 1] = current->data;
        current = current->next;
    }
    
    // Заполняем стек
    for (size_t i = 0; i < other.size_; ++i)
    {
        Push(temp[i]);
    }
    
    delete[] temp;
}

// Копирование из контейнера
template <typename T>
void Stack<T>::CopyFrom(const Container<T>& other)
{
    // Временный стек для реверса
    Stack<T> temp;
    Container<T>* tempContainer = &temp;
    
    // Создаем копию контейнера
    Container<T>* otherCopy = dynamic_cast<Container<T>*>(const_cast<Container<T>*>(&other));
    if (!otherCopy)
    {
        throw std::bad_cast();
    }
    
    // Копируем элементы во временный контейнер
    Stack<T> reversed;
    size_t size = other.Size();
    T* elements = new T[size];
    
    // Собираем элементы
    size_t index = 0;
    Container<T>* nonConstOther = const_cast<Container<T>*>(&other);
    while (!nonConstOther->IsEmpty())
    {
        elements[index++] = nonConstOther->GetFront();
        nonConstOther->Pop();
    }
    
    // Восстанавливаем оригинал и заполняем стек
    for (size_t i = size; i > 0; --i)
    {
        this->Push(elements[i - 1]);
        const_cast<Container<T>*>(&other)->Push(elements[i - 1]);
    }
    
    delete[] elements;
}

// Операции присваивания
template <typename T>
Stack<T>& Stack<T>::operator=(const Stack<T>& other)
{
    if (this != &other)
    {
        Clear();
        CopyFrom(other);
    }
    return *this;
}

template <typename T>
Stack<T>& Stack<T>::operator=(Stack<T>&& other) noexcept
{
    if (this != &other)
    {
        Clear();
        top_ = other.top_;
        size_ = other.size_;
        other.top_ = nullptr;
        other.size_ = 0;
    }
    return *this;
}

template <typename T>
Container<T>& Stack<T>::operator=(const Container<T>& other)
{
    Clear();
    CopyFrom(other);
    return *this;
}

template <typename T>
Container<T>& Stack<T>::operator=(Container<T>&& other)
{
    Stack<T>* otherStack = dynamic_cast<Stack<T>*>(&other);
    if (otherStack)
    {
        *this = std::move(*otherStack);
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
void Stack<T>::Push(const T& value)
{
    Node<T>* newNode = new Node<T>(value);
    newNode->next = top_;
    top_ = newNode;
    ++size_;
}

template <typename T>
void Stack<T>::Push(T&& value)
{
    Node<T>* newNode = new Node<T>(std::move(value));
    newNode->next = top_;
    top_ = newNode;
    ++size_;
}

template <typename T>
void Stack<T>::Pop()
{
    if (IsEmpty())
    {
        throw EmptyContainerException();
    }
    
    Node<T>* temp = top_;
    top_ = top_->next;
    delete temp;
    --size_;
}

template <typename T>
T& Stack<T>::GetFront()
{
    if (IsEmpty())
    {
        throw EmptyContainerException();
    }
    return top_->data;
}

template <typename T>
const T& Stack<T>::GetFront() const
{
    if (IsEmpty())
    {
        throw EmptyContainerException();
    }
    return top_->data;
}

template <typename T>
bool Stack<T>::IsEmpty() const
{
    return top_ == nullptr;
}

template <typename T>
size_t Stack<T>::Size() const
{
    return size_;
}

template <typename T>
void Stack<T>::Print(std::ostream& os) const
{
    Node<T>* current = top_;
    os << "Stack[";
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