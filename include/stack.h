#ifndef STACK_H
#define STACK_H

#include "container.h"
#include "node.h"

template <typename T>
class stack : public fwd_container<T>
{
private:
    node<T>* top;
    size_t length;
    
public:
    // Конструкторы
    stack();
    stack(const stack& other);
    stack(stack&& other) noexcept;
    
    // Деструктор
    ~stack();
    
    // Копирование из другого контейнера
    stack(const fwd_container<T>& other);
    
    // Присваивание
    stack<T>& operator=(const stack<T>& other);
    stack<T>& operator=(stack<T>&& other) noexcept;
    fwd_container<T>& operator=(const fwd_container<T>& other) override;
    fwd_container<T>& operator=(fwd_container<T>&& other) override;
    
    // Методы
    void push(const T& value) override;
    void push(T&& value) override;
    void pop() override;
    T& get_front() override;
    const T& get_front() const override;
    bool is_empty() const override;
    size_t size() const override;
    
protected:
    void print(std::ostream& os) const override;
    
private:
    void clear();
    void copy_from(const stack& other);
    void copy_from(const fwd_container<T>& other);
};

// Реализация методов
#include "stack.tpp"

#endif