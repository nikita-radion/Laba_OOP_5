#pragma once
#include <memory_resource>  
#include <map>  
#include <cstddef>  

class DynamicMemoryResource : public std::pmr::memory_resource {
private:

    std::map<void*, std::size_t> allocated_blocks_;

protected:

    void* do_allocate(std::size_t bytes, std::size_t alignment) override;  
    void do_deallocate(void* p, std::size_t bytes, std::size_t alignment) override;  
    bool do_is_equal(const std::pmr::memory_resource& other) const noexcept override;  

public:
    DynamicMemoryResource() = default;  
    ~DynamicMemoryResource();  

    DynamicMemoryResource(const DynamicMemoryResource&) = delete;
    DynamicMemoryResource& operator=(const DynamicMemoryResource&) = delete;
};