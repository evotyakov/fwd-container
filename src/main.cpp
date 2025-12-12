#include <iostream>
#include "C:\Computer Science\cpp\fwd-container\include\stack.h"
#include "C:\Computer Science\cpp\fwd-container\include\queue.h"

int main()
{
    try
    {
        // Тестирование стека
        std::cout << "Testing Stack" << std::endl;
        stack<int> stack1;
        
        stack1.push(1);
        stack1.push(2);
        stack1.push(3);
        
        std::cout << "Stack1: " << stack1 << std::endl;
        std::cout << "Size: " << stack1.size() << std::endl;
        std::cout << "Front: " << stack1.get_front() << std::endl;
        
        stack1.pop();
        std::cout << "After pop: " << stack1 << std::endl;
        
        // Тестирование копирования
        stack<int> stack2 = stack1;
        std::cout << "Stack2 (copy): " << stack2 << std::endl;
        
        // Тестирование перемещения
        stack<int> stack3 = std::move(stack2);
        std::cout << "Stack3 (move): " << stack3 << std::endl;
        std::cout << "Stack2 after move (should be empty): " 
                  << (stack2.is_empty() ? "empty" : "not empty") << std::endl;
        
        // Тестирование очереди
        std::cout << "\nTesting Queue" << std::endl;
        queue<int> queue1;
        
        queue1.push(1);
        queue1.push(2);
        queue1.push(3);
        
        std::cout << "Queue1: " << queue1 << std::endl;
        std::cout << "Size: " << queue1.size() << std::endl;
        std::cout << "Front: " << queue1.get_front() << std::endl;
        
        queue1.pop();
        std::cout << "After pop: " << queue1 << std::endl;
        
        // Тестирование оператора ввода
        std::cout << "\nTesting input operator" << std::endl;
        stack<int> stackInput;
        std::cout << "Enter 3 integers for stack: ";
        std::cin >> stackInput >> stackInput >> stackInput;
        std::cout << "Input stack: " << stackInput << std::endl;
        
        // Полиморфное использование
        std::cout << "\nPolymorphic usage" << std::endl;
        fwd_container<int>* container1 = new stack<int>();
        fwd_container<int>* container2 = new queue<int>();
        
        container1->push(10);
        container1->push(20);
        container2->push(30);
        container2->push(40);
        
        std::cout << "Container1 (Stack): " << *container1 << std::endl;
        std::cout << "Container2 (Queue): " << *container2 << std::endl;
        
        // Присваивание между разными типами контейнеров
        *container1 = *container2;
        std::cout << "After assignment (Stack = Queue): " << *container1 << std::endl;
        
        delete container1;
        delete container2;
        
        std::cout << "\nTesting exceptions" << std::endl;
        stack<int> emptyStack;
        try
        {
            emptyStack.pop();
        }
        catch (const ContainerException& e)
        {
            std::cout << "Exception caught: " << e.what() << std::endl;
        }
        
    }
    catch (const std::exception& e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}