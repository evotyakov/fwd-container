#include <iostream>
#include <stdexcept>

// Конструкторы
template <typename T>
stack<T>::stack() : stack_top(nullptr), length(0) {}

template <typename T>
stack<T>::stack(const stack& other) : stack_top(nullptr), length(other.length)
{
    if (!other.is_empty()) {
        node<T>* current = other.stack_top;
        node<T>* prev_new_node = nullptr;
        node<T>* new_top_node = nullptr;
        
        try {
            new_top_node = new node<T>(current->data);
            prev_new_node = new_top_node;
            current = current->next;
            
            while (current != nullptr) {
                node<T>* new_node = new node<T>(current->data);
                prev_new_node->next = new_node;
                prev_new_node = new_node;
                current = current->next;
            }
            
            stack_top = new_top_node;
        }
        catch (const std::bad_alloc&) {
            while (new_top_node != nullptr) {
                node<T>* temp = new_top_node;
                new_top_node = new_top_node->next;
                delete temp;
            }
            throw MemoryAllocationException();
        }
    }
}

template <typename T>
stack<T>::stack(stack&& other) noexcept 
    : stack_top(other.stack_top), length(other.length)
{
    other.stack_top = nullptr;
    other.length = 0;
}

template <typename T>
stack<T>::stack(const fwd_container<T>& other) : stack_top(nullptr), length(0)
{
    try {
        auto it = other.cbegin();
        auto end = other.cend();

        stack<T> temp_stack;
        while (it != end) {
            temp_stack.push(*it);
            ++it;
        }

        while (!temp_stack.is_empty()) {
            this->push(temp_stack.get_front());
            temp_stack.pop();
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
stack<T>& stack<T>::operator=(const stack& other)
{
    if (this != &other) {
        clear();
        length = 0;
        
        if (!other.is_empty()) {
            node<T>* current = other.stack_top;
            node<T>* prev_new_node = nullptr;
            node<T>* new_top_node = nullptr;
            
            try {
                new_top_node = new node<T>(current->data);
                prev_new_node = new_top_node;
                current = current->next;
                
                while (current != nullptr) {
                    node<T>* new_node = new node<T>(current->data);
                    prev_new_node->next = new_node;
                    prev_new_node = new_node;
                    current = current->next;
                }
                
                stack_top = new_top_node;
                length = other.length;
            }
            catch (const std::bad_alloc&) {
                while (new_top_node != nullptr) {
                    node<T>* temp = new_top_node;
                    new_top_node = new_top_node->next;
                    delete temp;
                }
                throw MemoryAllocationException();
            }
        }
    }
    return *this;
}

template <typename T>
stack<T>& stack<T>::operator=(stack&& other) noexcept
{
    if (this != &other) {
        clear();
        stack_top = other.stack_top;
        length = other.length;
        
        other.stack_top = nullptr;
        other.length = 0;
    }
    return *this;
}

template <typename T>
fwd_container<T>& stack<T>::operator=(const fwd_container<T>& other)
{
    if (this == &other) {
        return *this;
    }

    if (const stack<T>* other_stack = dynamic_cast<const stack<T>*>(&other)) {
        return *this = *other_stack;
    }

    clear();
    length = 0;
    
    try {
        auto it = other.cbegin();
        auto end = other.cend();

        stack<T> temp_stack;
        while (it != end) {
            temp_stack.push(*it);
            ++it;
        }

        while (!temp_stack.is_empty()) {
            this->push(temp_stack.get_front());
            temp_stack.pop();
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
fwd_container<T>& stack<T>::operator=(fwd_container<T>&& other)
{
    if (this == &other) {
        return *this;
    }

    if (stack<T>* other_stack = dynamic_cast<stack<T>*>(&other)) {
        return *this = std::move(*other_stack);
    }
    clear();
    length = 0;
    
    try {
        auto it = other.cbegin();
        auto end = other.cend();
        
        stack<T> temp_stack;
        while (it != end) {
            temp_stack.push(*it);
            ++it;
        }
        
        while (!temp_stack.is_empty()) {
            this->push(temp_stack.get_front());
            temp_stack.pop();
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
stack<T>::~stack()
{
    clear();
}

// Очистка стека
template <typename T>
void stack<T>::clear()
{
    while (!is_empty())
    {
        pop();
    }
}

// Основные методы
template <typename T>
void stack<T>::push(const T& value)
{
    node<T>* new_node = new node<T>(value);
    new_node->next = stack_top;
    stack_top = new_node;
    ++length;
}

template <typename T>
void stack<T>::push(T&& value)
{
    node<T>* new_node = new node<T>(std::move(value));
    if (!new_node) throw MemoryAllocationException();
    new_node->next = stack_top;
    stack_top = new_node;
    ++length;
}

template <typename T>
void stack<T>::pop()
{
    if (is_empty())
    {
        throw EmptyContainerException();
    }
    
    node<T>* temp = stack_top;
    stack_top = stack_top->next;
    delete temp;
    --length;
}

template <typename T>
T& stack<T>::get_front()
{
    if (is_empty())
    {
        throw EmptyContainerException();
    }
    if (!stack_top) throw InvalidOperationException();
    return stack_top->data;
}

template <typename T>
const T& stack<T>::get_front() const
{
    if (is_empty())
    {
        throw EmptyContainerException();
    }
    if (!stack_top) throw InvalidOperationException();
    return stack_top->data;
}

template <typename T>
bool stack<T>::is_empty() const
{
    return stack_top == nullptr;
}

template <typename T>
size_t stack<T>::size() const
{
    return length;
}

template <typename T>
fwd_container<T>* stack<T>::clone() const
{
    return new stack<T>(*this);
}

template<typename T>
typename stack<T>::iterator stack<T>::begin()
{
    return iterator(new stack_iterator(stack_top));
}

template<typename T>
typename stack<T>::iterator stack<T>::end()
{
    return iterator(new stack_iterator(nullptr));
}

template<typename T>
typename stack<T>::const_iterator stack<T>::begin() const
{
    return const_iterator(new stack_const_iterator(stack_top));
}

template<typename T>
typename stack<T>::const_iterator stack<T>::end() const
{
    return const_iterator(new stack_const_iterator(nullptr));
}

template<typename T>
typename stack<T>::const_iterator stack<T>::cbegin() const
{
    return const_iterator(new stack_const_iterator(stack_top));
}

template<typename T>
typename stack<T>::const_iterator stack<T>::cend() const
{
    return const_iterator(new stack_const_iterator(nullptr));
}


template<typename T>
size_t stack<T>::getSize() const {
    return length;
}

template<typename T>
bool stack<T>::empty() const {
    return is_empty();
}

template<typename T>
T& stack<T>::top() {
    return get_front();
}

template<typename T>
const T& stack<T>::top() const {
    return get_front();
}

template<typename T>
std::ostream& stack<T>::print(std::ostream& os) const {
    try {
        if (!os.good()) throw std::runtime_error("Output stream is in bad state");
        
        node<T>* current = stack_top;  
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
        throw std::runtime_error(std::string("Stack serialization failed: ") + e.what());
    }
}

template<typename T>
std::istream& stack<T>::read(std::istream& is) {
    try {
        if (!is.good()) {
            throw std::runtime_error("Input stream is in bad state");
        }
        
        stack<T> backup = *this;
        
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
        throw std::runtime_error(std::string("Stack input failed: ") + e.what());
    }
}