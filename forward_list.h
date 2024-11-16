#pragma once  
#include <memory_resource>  
#include <memory>  
#include "forward_list_iterator.h"  

template<typename T>  
class ForwardList {
private:

    using NodeAllocator = std::pmr::polymorphic_allocator<ListNode<T>>;
    using AllocTraits = std::allocator_traits<NodeAllocator>;
    ListNode<T>* first_;  
    NodeAllocator allocator_;  

public:

    using iterator = ForwardListIterator<T>;  
    
    explicit ForwardList(std::pmr::memory_resource* resource = std::pmr::get_default_resource())
        : first_(nullptr), allocator_(resource) {}
    
    ~ForwardList() {
        while (first_) {
            remove_first();
        }
    }

    void add_first(const T& item) {
        ListNode<T>* new_node = allocator_.allocate(1);  
        try {
            AllocTraits::construct(allocator_, new_node);  
            new_node->value = item;  
            new_node->next_ptr = first_;  
            first_ = new_node;  
        } catch (...) {
            allocator_.deallocate(new_node, 1);  
            throw;  
        }
    }

    void remove_first() {
        if (first_) {  
            ListNode<T>* temp = first_;  
            first_ = first_->next_ptr;  
            AllocTraits::destroy(allocator_, temp);  
            allocator_.deallocate(temp, 1);  
        }
    }

    void remove_all() {
        while (first_) {  
            remove_first();  
        }
    }

    iterator begin() { return iterator(first_); }  
    iterator end() { return iterator(nullptr); }  
    iterator begin() const { return iterator(first_); }  
    iterator end() const { return iterator(nullptr); }  
};