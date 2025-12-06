#ifndef STACK_H
#define STACK_H

#include "container.h"
#include "node.h"

template <typename T>
class Stack : public Container<T>
{
private:
    Node<T>* top_;
    size_t size_;
    
public:
    // Конструкторы
    Stack();
    Stack(const Stack& other);
    Stack(Stack&& other) noexcept;
    
    // Деструктор
    ~Stack();
    
    // Копирование из другого контейнера
    Stack(const Container<T>& other);
    
    // Присваивание
    Stack<T>& operator=(const Stack<T>& other);
    Stack<T>& operator=(Stack<T>&& other) noexcept;
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
    void CopyFrom(const Stack& other);
    void CopyFrom(const Container<T>& other);
};

// Реализация методов
#include "stack_impl.h"

#endif