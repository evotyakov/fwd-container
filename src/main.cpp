#include <iostream>
#include "stack.h"
#include "queue.h"

int main()
{
    try
    {
        // Тестирование стека
        std::cout << "Testing Stack" << std::endl;
        Stack<int> stack1;
        
        stack1.Push(1);
        stack1.Push(2);
        stack1.Push(3);
        
        std::cout << "Stack1: " << stack1 << std::endl;
        std::cout << "Size: " << stack1.Size() << std::endl;
        std::cout << "Front: " << stack1.GetFront() << std::endl;
        
        stack1.Pop();
        std::cout << "After pop: " << stack1 << std::endl;
        
        // Тестирование копирования
        Stack<int> stack2 = stack1;
        std::cout << "Stack2 (copy): " << stack2 << std::endl;
        
        // Тестирование перемещения
        Stack<int> stack3 = std::move(stack2);
        std::cout << "Stack3 (move): " << stack3 << std::endl;
        std::cout << "Stack2 after move (should be empty): " 
                  << (stack2.IsEmpty() ? "empty" : "not empty") << std::endl;
        
        // Тестирование очереди
        std::cout << "\nTesting Queue" << std::endl;
        Queue<int> queue1;
        
        queue1.Push(1);
        queue1.Push(2);
        queue1.Push(3);
        
        std::cout << "Queue1: " << queue1 << std::endl;
        std::cout << "Size: " << queue1.Size() << std::endl;
        std::cout << "Front: " << queue1.GetFront() << std::endl;
        
        queue1.Pop();
        std::cout << "After pop: " << queue1 << std::endl;
        
        // Тестирование оператора ввода
        std::cout << "\nTesting input operator" << std::endl;
        Stack<int> stackInput;
        std::cout << "Enter 3 integers for stack: ";
        std::cin >> stackInput >> stackInput >> stackInput;
        std::cout << "Input stack: " << stackInput << std::endl;
        
        // Полиморфное использование
        std::cout << "\nPolymorphic usage" << std::endl;
        Container<int>* container1 = new Stack<int>();
        Container<int>* container2 = new Queue<int>();
        
        container1->Push(10);
        container1->Push(20);
        container2->Push(30);
        container2->Push(40);
        
        std::cout << "Container1 (Stack): " << *container1 << std::endl;
        std::cout << "Container2 (Queue): " << *container2 << std::endl;
        
        // Присваивание между разными типами контейнеров
        *container1 = *container2;
        std::cout << "After assignment (Stack = Queue): " << *container1 << std::endl;
        
        delete container1;
        delete container2;
        
        std::cout << "\nTesting exceptions" << std::endl;
        Stack<int> emptyStack;
        try
        {
            emptyStack.Pop();
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