#pragma once  
#include <iterator>  

template<typename T>
struct ListNode {
    T value;  
    ListNode* next_ptr;  
};

template<typename T>
class ForwardListIterator {
public:

    using iterator_category = std::forward_iterator_tag;  
    using value_type = T; 
    using difference_type = std::ptrdiff_t;  
    using pointer = T*;  
    using reference = T&;  

private:

    ListNode<T>* current_ptr_;  

public:

    explicit ForwardListIterator(ListNode<T>* node) : current_ptr_(node) {}

    reference operator*() const { return current_ptr_->value; }  
    pointer operator->() const { return &(current_ptr_->value); }  

    ForwardListIterator& operator++() {  
        current_ptr_ = current_ptr_->next_ptr;
        return *this;
    }

    ForwardListIterator operator++(int) {  
        ForwardListIterator copy(*this);
        current_ptr_ = current_ptr_->next_ptr;
        return copy;
    }

    bool operator==(const ForwardListIterator& other) const {
        return current_ptr_ == other.current_ptr_;
    }

    bool operator!=(const ForwardListIterator& other) const {
        return current_ptr_ != other.current_ptr_;
    }
};