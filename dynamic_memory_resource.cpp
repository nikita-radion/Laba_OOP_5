#include "dynamic_memory_resource.h"
#include <algorithm>  
#include <new>  

void* DynamicMemoryResource::do_allocate(std::size_t bytes, std::size_t alignment) {
    void* ptr = ::operator new(bytes, std::align_val_t{alignment});
    allocated_blocks_[ptr] = bytes;
    return ptr;
}

void DynamicMemoryResource::do_deallocate(void* p, std::size_t bytes, std::size_t alignment) {
    auto it = allocated_blocks_.find(p);
    if (it != allocated_blocks_.end()) {
        ::operator delete(p, bytes, std::align_val_t{alignment});
        allocated_blocks_.erase(it);
    }
}

bool DynamicMemoryResource::do_is_equal(const std::pmr::memory_resource& other) const noexcept {
    return this == &other;  
}

DynamicMemoryResource::~DynamicMemoryResource() {
    for (const auto& [ptr, size] : allocated_blocks_) {
        ::operator delete(ptr, size);
    }
}