#include <iostream>
#include <stdexcept>

// Конструкторы
template <typename T>
queue<T>::queue() : front_ptr(nullptr), back_ptr(nullptr), length(0) {}

template <typename T>
queue<T>::queue(const queue& other) : front_ptr(nullptr), back_ptr(nullptr), length(other.length)
{
    if (!other.is_empty()) {
        node<T>* current = other.front_ptr;
        node<T>* prev_new_node = nullptr;
        node<T>* new_front_ptr = nullptr;
        
        try {
            new_front_ptr = new node<T>(current->data);
            prev_new_node = new_front_ptr;
            current = current->next;
            
            while (current != nullptr) {
                node<T>* new_node = new node<T>(current->data);
                prev_new_node->next = new_node;
                prev_new_node = new_node;
                current = current->next;
            }
            
            front_ptr = new_front_ptr;
            back_ptr = prev_new_node;
        }
        catch (const std::bad_alloc&) {
            while (new_front_ptr != nullptr) {
                node<T>* temp = new_front_ptr;
                new_front_ptr = new_front_ptr->next;
                delete temp;
            }
            throw MemoryAllocationException();
        }
    }
}

template <typename T>
queue<T>::queue(queue&& other) noexcept 
    : front_ptr(other.front_ptr), back_ptr(other.back_ptr), length(other.length)
{
    other.front_ptr = nullptr;
    other.back_ptr = nullptr;
    other.length = 0;
}

template <typename T>
queue<T>::queue(const fwd_container<T>& other) : front_ptr(nullptr), back_ptr(nullptr), length(0)
{
    try {
        auto it = other.cbegin();
        auto end = other.cend();
        
        while (it != end) {
            this->push(*it);
            ++it;
        }
    }
    catch (const std::bad_alloc&) {
        throw MemoryAllocationException();
    }
    catch (const ContainerException& e) {
        throw;
    }
    catch (const std::exception&) {
        throw InvalidOperationException();
    }
}

// Операторы присваивания
template <typename T>
queue<T>& queue<T>::operator=(const queue& other)
{
    if (this != &other) {
        clear();
        length = 0;
        
        if (!other.is_empty()) {
            node<T>* current = other.front_ptr;
            node<T>* prev_new_node = nullptr;
            node<T>* new_front_ptr = nullptr;
            
            try {
                new_front_ptr = new node<T>(current->data);
                prev_new_node = new_front_ptr;
                current = current->next;
                
                while (current != nullptr) {
                    node<T>* new_node = new node<T>(current->data);
                    prev_new_node->next = new_node;
                    prev_new_node = new_node;
                    current = current->next;
                }
                
                front_ptr = new_front_ptr;
                back_ptr = prev_new_node;
                length = other.length;
            }
            catch (const std::bad_alloc&) {
                while (new_front_ptr != nullptr) {
                    node<T>* temp = new_front_ptr;
                    new_front_ptr = new_front_ptr->next;
                    delete temp;
                }
                throw MemoryAllocationException();
            }
        }
    }
    return *this;
}

template <typename T>
queue<T>& queue<T>::operator=(queue&& other) noexcept
{
    if (this != &other) {
        clear();
        front_ptr = other.front_ptr;
        back_ptr = other.back_ptr;
        length = other.length;
        
        other.front_ptr = nullptr;
        other.back_ptr = nullptr;
        other.length = 0;
    }
    return *this;
}

template <typename T>
fwd_container<T>& queue<T>::operator=(const fwd_container<T>& other)
{
    if (this == &other) {
        return *this;
    }
    
    if (const queue<T>* other_queue = dynamic_cast<const queue<T>*>(&other)) {
        return *this = *other_queue;
    }
    
    clear();
    length = 0;
    
    try {
        auto it = other.cbegin();
        auto end = other.cend();
        
        while (it != end) {
            this->push(*it);
            ++it;
        }
    }
    catch (const std::bad_alloc&) {
        throw MemoryAllocationException();
    }
    catch (const ContainerException& e) {
        throw;
    }
    catch (const std::exception&) {
        throw InvalidOperationException();
    }
    
    return *this;
}

template <typename T>
fwd_container<T>& queue<T>::operator=(fwd_container<T>&& other)
{
    if (this == &other) {
        return *this;
    }
    
    if (queue<T>* other_queue = dynamic_cast<queue<T>*>(&other)) {
        return *this = std::move(*other_queue);
    }
    
    clear();
    length = 0;
    
    try {
        auto it = other.cbegin();
        auto end = other.cend();
        
        while (it != end) {
            this->push(*it);
            ++it;
        }
        
        while (!other.is_empty()) {
            other.pop();
        }
    }
    catch (const std::bad_alloc&) {
        throw MemoryAllocationException();
    }
    catch (const ContainerException& e) {
        throw;
    }
    catch (const std::exception&) {
        throw InvalidOperationException();
    }
    
    return *this;
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

// Основные методы
template <typename T>
void queue<T>::push(const T& value)
{
    node<T>* new_node = new node<T>(value);
    if (is_empty())
    {
        front_ptr = new_node;
        back_ptr = new_node;
    }
    else
    {
        back_ptr->next = new_node;
        back_ptr = new_node;
    }
    ++length;
}

template <typename T>
void queue<T>::push(T&& value)
{
    node<T>* new_node = new node<T>(std::move(value));
    if (!new_node) throw MemoryAllocationException();
    if (is_empty())
    {
        front_ptr = new_node;
        back_ptr = new_node;
    }
    else
    {
        back_ptr->next = new_node;
        back_ptr = new_node;
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
    
    node<T>* temp = front_ptr;
    front_ptr = front_ptr->next;
    if (front_ptr == nullptr)
    {
        back_ptr = nullptr;
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
    if (!front_ptr) throw InvalidOperationException();
    return front_ptr->data;
}

template <typename T>
const T& queue<T>::get_front() const
{
    if (is_empty())
    {
        throw EmptyContainerException();
    }
    if (!front_ptr) throw InvalidOperationException();
    return front_ptr->data;
}

template <typename T>
bool queue<T>::is_empty() const
{
    return front_ptr == nullptr;
}

template <typename T>
size_t queue<T>::size() const
{
    return length;
}

template <typename T>
fwd_container<T>* queue<T>::clone() const
{
    return new queue<T>(*this);
}

template<typename T>
typename queue<T>::iterator queue<T>::begin()
{
    return iterator(new queue_iterator(front_ptr));
}

template<typename T>
typename queue<T>::iterator queue<T>::end()
{
    return iterator(new queue_iterator(nullptr));
}

template<typename T>
typename queue<T>::const_iterator queue<T>::begin() const
{
    return const_iterator(new queue_const_iterator(front_ptr));
}

template<typename T>
typename queue<T>::const_iterator queue<T>::end() const
{
    return const_iterator(new queue_const_iterator(nullptr));
}

template<typename T>
typename queue<T>::const_iterator queue<T>::cbegin() const
{
    return const_iterator(new queue_const_iterator(front_ptr));
}

template<typename T>
typename queue<T>::const_iterator queue<T>::cend() const
{
    return const_iterator(new queue_const_iterator(nullptr));
}

template<typename T>
size_t queue<T>::getSize() const {
    return length;
}

template<typename T>
bool queue<T>::empty() const {
    return is_empty();
}

template<typename T>
T& queue<T>::front() {
    return get_front();
}

template<typename T>
const T& queue<T>::front() const {
    return get_front();
}

template<typename T>
T& queue<T>::back() {
    if (is_empty())
    {
        throw EmptyContainerException();
    }
    if (!back_ptr) throw InvalidOperationException();
    return back_ptr->data;
}

template<typename T>
const T& queue<T>::back() const {
    if (is_empty())
    {
        throw EmptyContainerException();
    }
    return back_ptr->data;
}

template<typename T>
std::ostream& queue<T>::print(std::ostream& os) const {
    try {
        if (!os.good()) throw std::runtime_error("Output stream is in bad state");
        
        node<T>* current = front_ptr;
        bool first = true;
        
        while (current != nullptr) {
            if (!first) {
                os << " ";
            }
            
            if (!os.good()) throw std::runtime_error("Output stream failed during serialization");
            
            os << current->data;
            current = current->next;
            first = false;
        }
        
        if (!os.good()) throw std::runtime_error("Output stream failed after serialization");
        
        return os;
        
    } catch (const std::exception& e) {
        os.setstate(std::ios::failbit);
        throw std::runtime_error(std::string("Queue serialization failed: ") + e.what());
    }
}

template<typename T>
std::istream& queue<T>::read(std::istream& is) {
    try {
        if (!is.good()) {
            throw std::runtime_error("Input stream is in bad state");
        }
        
        queue<T> backup = *this;
        
        try {
            T value;
            while (is >> value) {
                try {
                    this->push(value);
                } 
                catch (const std::bad_alloc& e) {
                    throw std::runtime_error("Memory allocation failed during input: " + std::string(e.what()));
                } 
                catch (const std::exception& e) {
                    throw std::runtime_error("Push operation failed during input: " + std::string(e.what()));
                }
                
                if (!is.good() && !is.eof()) {
                    throw std::runtime_error("Input stream failed during data reading");
                }
            }

            if (is.eof()) {
                is.clear();
            }

            if (is.fail() && !is.eof()) {
                throw std::runtime_error("Failed to parse input data");
            }
            
            return is;
            
        } 
        catch (...) {
            *this = std::move(backup);
            throw;
        }
        
    } 
    catch (const std::exception& e) 
    {
        is.setstate(std::ios::failbit);
        throw std::runtime_error(std::string("Queue input failed: ") + e.what());
    }
}