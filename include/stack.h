#ifndef STACK_H
#define STACK_H

#include "fwd_container.h"
#include "node.h"

template <typename T>
class stack : public fwd_container<T>
{
private:
    node<T>* stack_top;
    size_t length;
    
public:
    using iterator = typename fwd_container<T>::iterator;
    using const_iterator = typename fwd_container<T>::const_iterator;

    // Конструкторы
    stack();
    stack(const stack& other);
    stack(stack&& other) noexcept;
    stack(const fwd_container<T>& other);
    
    // Деструктор
    ~stack();

    fwd_container<T>* clone() const;
    
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

    iterator begin() override;
    iterator end() override;
    const_iterator begin() const override;
    const_iterator end() const override;
    const_iterator cbegin() const override;
    const_iterator cend() const override;

    size_t getSize() const;
    bool empty() const;
    T& top();
    const T& top() const;
    void clear();
    
protected:
    virtual std::ostream& print(std::ostream& os) const override;
    virtual std::istream& read(std::istream& is) override;
    
private:
    class stack_iterator : public fwd_container<T>::iterator_base
    {
    private:
        node<T>* current;
        static constexpr int iterator_kind = 2;

    public:
        int get_iterator_kind() const noexcept override
        {
            return iterator_kind;
        }

        stack_iterator(node<T>* node) : current(node) {}

        T& operator*() override
        {
            if (!current) throw InvalidIteratorException();
            return current->data;
        }

        T* operator->() override
        {
            if (!current) throw InvalidIteratorException();
            return &(current->data);
        }

        stack_iterator& operator++() override
        {
            if (!current) throw InvalidIteratorException();
            current = current->next;
            return *this;
        }

        bool operator==(const typename fwd_container<T>::iterator_base& other) const override
        {
            if (this->get_iterator_kind() != other.get_iterator_kind()) return false;
            const stack_iterator* derived = dynamic_cast<const stack_iterator*>(&other);
            return derived && current == derived->current;
        }

        bool operator!=(const typename fwd_container<T>::iterator_base& other) const override
        {
            return !(*this == other);
        }

        bool operator==(const typename fwd_container<T>::const_iterator_base& other) const override
        {
            if (this->get_iterator_kind() != other.get_iterator_kind()) return false;
            const stack_const_iterator* derived = dynamic_cast<const stack_const_iterator*>(&other);
            return derived && current == derived->get_current();
        }

        bool operator!=(const typename fwd_container<T>::const_iterator_base& other) const override
        {
            return !(*this == other);
        }

        typename fwd_container<T>::const_iterator_base* create_const() const override
        {
            return new stack_const_iterator(current);
        }

        node<T>* get_current() const
        {
            return current;
        }

    protected:
        stack_iterator* clone() const override
        {
            return new stack_iterator(current);
        }

        friend class stack_const_iterator;
    };

    class stack_const_iterator : public fwd_container<T>::const_iterator_base
    {
    private:
        const node<T>* current;
        static constexpr int iterator_kind = 2;

    public:
        int get_iterator_kind() const noexcept override
        {
            return iterator_kind;
        }

        stack_const_iterator(const node<T>* node) : current(node) {}

        const T& operator*() const override
        {
            if (!current) throw InvalidIteratorException();
            return current->data;
        }

        const T* operator->() const override
        {
            if (!current) throw InvalidIteratorException();
            return &(current->data);
        }

        stack_const_iterator& operator++() override
        {
            if (!current) throw InvalidIteratorException();
            current = current->next;
            return *this;
        }

        bool operator==(const typename fwd_container<T>::const_iterator_base& other) const override
        {
            if (this->get_iterator_kind() != other.get_iterator_kind()) return false;
            const stack_const_iterator* derived = static_cast<const stack_const_iterator*>(&other);
            return derived && current == derived->current;
        }

        bool operator!=(const typename fwd_container<T>::const_iterator_base& other) const override
        {
            return !(*this == other);
        }

        bool operator==(const typename fwd_container<T>::iterator_base& other) const override
        {
            if (this->get_iterator_kind() != other.get_iterator_kind()) return false;
            const stack_iterator* derived = static_cast<const stack_iterator*>(&other);
            return derived && current == derived->get_current();
        }

        bool operator!=(const typename fwd_container<T>::iterator_base& other) const override
        {
            return !(*this == other);
        }

        const node<T>* get_current() const
        { 
            return current;
        }

    protected:
        stack_const_iterator* clone() const override
        {
            return new stack_const_iterator(current);
        }

        friend class stack_iterator;
    };
};

// Реализация методов
#include "stack.tpp"

#endif