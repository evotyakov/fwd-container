#ifndef QUEUE_H
#define QUEUE_H

#include "container.h"
#include "node.h"

template <typename T>
class queue : public fwd_container<T>
{
private:
    node<T>* front;
    node<T>* rear;
    size_t length;
    
public:
    // Конструкторы
    queue();
    queue(const queue& other);
    queue(queue&& other) noexcept;
    
    // Деструктор
    ~queue();
    
    // Копирование из другого контейнера
    queue(const fwd_container<T>& other);
    
    // Присваивание
    queue<T>& operator=(const queue<T>& other);
    queue<T>& operator=(queue<T>&& other) noexcept;
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
    void copy_from(const queue& other);
    void copy_from(const fwd_container<T>& other);
};

#include "queue.tpp"

#endif