#ifndef QUEUE_H
#define QUEUE_H

#include "container.h"
#include "node.h"

template <typename T>
class Queue : public Container<T>
{
private:
    Node<T>* front_;
    Node<T>* rear_;
    size_t size_;
    
public:
    // Конструкторы
    Queue();
    Queue(const Queue& other);
    Queue(Queue&& other) noexcept;
    
    // Деструктор
    ~Queue();
    
    // Копирование из другого контейнера
    Queue(const Container<T>& other);
    
    // Присваивание
    Queue<T>& operator=(const Queue<T>& other);
    Queue<T>& operator=(Queue<T>&& other) noexcept;
    Container<T>& operator=(const Container<T>& other) override;
    Container<T>& operator=(Container<T>&& other) override;
    
    // Методы
    void Push(const T& value) override;
    void Push(T&& value) override;
    void Pop() override;
    T& GetFront() override;
    const T& GetFront() const override;
    bool IsEmpty() const override;
    size_t Size() const override;
    
protected:
    void Print(std::ostream& os) const override;
    
private:
    void Clear();
    void CopyFrom(const Queue& other);
    void CopyFrom(const Container<T>& other);
};

#include "queue_impl.h"

#endif