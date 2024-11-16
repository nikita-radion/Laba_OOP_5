#include <iostream>
#include "dynamic_memory_resource.h"
#include "forward_list.h"

struct Person {
    std::string name;
    int age;
    float height;
    
    void print() const {
        std::cout << "Name: " << name 
                  << ", Age: " << age 
                  << ", Height: " << height << "m\n";
    }
};

void print_numbers(const ForwardList<int>& list) {
    std::cout << "Numbers: ";
    for (const auto& num : list) {
        std::cout << num << " ";
    }
    std::cout << "\n";
}

int main() {
    try {
        DynamicMemoryResource mem_resource;
        
        ForwardList<int> numbers(&mem_resource);
        
        numbers.add_first(13);
        numbers.add_first(8);
        numbers.add_first(5);
        numbers.add_first(3);
        numbers.add_first(2);
        numbers.add_first(1);
        
        std::cout << "=== Testing with Fibonacci numbers ===\n";
        print_numbers(numbers);
        
        numbers.remove_first();
        std::cout << "After removing first element:\n";
        print_numbers(numbers);
        
        std::cout << "\n=== Testing with Person objects ===\n";
        ForwardList<Person> people(&mem_resource);
        
        people.add_first({"Alice", 25, 1.65f});
        people.add_first({"Bob", 30, 1.80f});
        people.add_first({"Charlie", 35, 1.75f});
        
        std::cout << "People list:\n";
        for (const auto& person : people) {
            person.print();
        }
        
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}