#ifndef QUEUE_H
#define QUEUE_H

#include "fwd_container.h"
#include "node.h"

template <typename T>
class queue : public fwd_container<T>
{
private:
    node<T>* front_ptr;
    node<T>* back_ptr;
    size_t length;
    
public:
    using iterator = typename fwd_container<T>::iterator;
    using const_iterator = typename fwd_container<T>::const_iterator;

    // Конструкторы
    queue();
    queue(const queue& other);
    queue(queue&& other) noexcept;
    queue(const fwd_container<T>& other);
    
    // Деструктор
    ~queue();
    
    fwd_container<T>* clone() const;
    
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

    iterator begin() override;
    iterator end() override;
    const_iterator begin() const override;
    const_iterator end() const override;
    const_iterator cbegin() const override;
    const_iterator cend() const override;

    size_t getSize() const;
    bool empty() const;
    T& front();
    const T& front() const;
    T& back();
    const T& back() const;
    void clear();
    
protected:
    virtual std::ostream& print(std::ostream& os) const override;
    virtual std::istream& read(std::istream& is) override;
    
private:
    void copy_from(const queue& other);
    void copy_from(const fwd_container<T>& other);

    class queue_iterator : public fwd_container<T>::iterator_base
    {
    private:
        node<T>* current;
        static constexpr int iterator_kind = 3;

    public:
        int get_iterator_kind() const noexcept override
        {
            return iterator_kind;
        }

        queue_iterator(node<T>* node) : current(node) {}

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

        queue_iterator& operator++() override
        {
            if (!current) throw InvalidIteratorException();
            current = current->next;
            return *this;
        }

        bool operator==(const typename fwd_container<T>::iterator_base& other) const override
        {
            if (this->get_iterator_kind() != other.get_iterator_kind()) return false;
            const queue_iterator* derived = dynamic_cast<const queue_iterator*>(&other);
            return derived && current == derived->current;
        }

        bool operator!=(const typename fwd_container<T>::iterator_base& other) const override
        {
            return !(*this == other);
        }

        bool operator==(const typename fwd_container<T>::const_iterator_base& other) const override
        {
            if (this->get_iterator_kind() != other.get_iterator_kind()) return false;
            const queue_const_iterator* derived = dynamic_cast<const queue_const_iterator*>(&other);
            return derived && current == derived->get_current();
        }

        bool operator!=(const typename fwd_container<T>::const_iterator_base& other) const override
        {
            return !(*this == other);
        }

        typename fwd_container<T>::const_iterator_base* create_const() const override
        {
            return new queue_const_iterator(current);
        }

        node<T>* get_current() const
        {
            return current;
        }

    protected:
        queue_iterator* clone() const override
        {
            return new queue_iterator(current);
        }

        friend class queue_const_iterator;
    };

    class queue_const_iterator : public fwd_container<T>::const_iterator_base
    {
    private:
        const node<T>* current;
        static constexpr int iterator_kind = 3;

    public:
        int get_iterator_kind() const noexcept override
        {
            return iterator_kind;
        }

        queue_const_iterator(const node<T>* node) : current(node) {}

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

        queue_const_iterator& operator++() override
        {
            if (!current) throw InvalidIteratorException();
            current = current->next;
            return *this;
        }

        bool operator==(const typename fwd_container<T>::const_iterator_base& other) const override
        {
            if (this->get_iterator_kind() != other.get_iterator_kind()) return false;
            const queue_const_iterator* derived = dynamic_cast<const queue_const_iterator*>(&other);
            return derived && current == derived->current;
        }

        bool operator!=(const typename fwd_container<T>::const_iterator_base& other) const override
        {
            return !(*this == other);
        }

        bool operator==(const typename fwd_container<T>::iterator_base& other) const override
        {
            if (this->get_iterator_kind() != other.get_iterator_kind()) return false;
            const queue_iterator* derived = dynamic_cast<const queue_iterator*>(&other);
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
        queue_const_iterator* clone() const override
        {
            return new queue_const_iterator(current);
        }

        friend class queue_iterator;
    };
};

#include "queue.tpp"

#endif