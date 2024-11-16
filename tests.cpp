#include <gtest/gtest.h>
#include "dynamic_memory_resource.h"
#include "forward_list.h"
#include <string>

struct TestStruct {
    int x;            
    double y;         
    std::string z;    

    bool operator==(const TestStruct& other) const {
        return x == other.x && y == other.y && z == other.z;
    }
};

TEST(DynamicMemoryResourceTest, AllocateAndDeallocate) {
    DynamicMemoryResource resource;
    
    void* p1 = resource.allocate(64);
    ASSERT_NE(p1, nullptr);  

    void* p2 = resource.allocate(128);
    ASSERT_NE(p2, nullptr); 
    ASSERT_NE(p1, p2);      

    resource.deallocate(p1, 64);
    resource.deallocate(p2, 128);
}

TEST(DynamicForwardListTest, BasicOperations) {
    DynamicMemoryResource resource;
    ForwardList<int> list(&resource);
    
    list.add_first(1);
    list.add_first(2);
    list.add_first(3);

    std::vector<int> expected{3, 2, 1};
    std::vector<int> actual;
    
    for (const auto& value : list) {
        actual.push_back(value);
    }

    ASSERT_EQ(actual, expected); 
}

TEST(DynamicForwardListTest, ComplexType) {
    DynamicMemoryResource resource;
    ForwardList<TestStruct> list(&resource);

    TestStruct s1{1, 1.1, "one"};
    TestStruct s2{2, 2.2, "two"};
    
    list.add_first(s1);
    list.add_first(s2);

    auto it = list.begin();
    ASSERT_EQ(it->x, 2);
    ASSERT_EQ(it->y, 2.2);
    ASSERT_EQ(it->z, "two");
}

TEST(DynamicForwardListTest, ClearAndDestruction) {
    DynamicMemoryResource resource;
    {   
        ForwardList<TestStruct> list(&resource);
        list.add_first({1, 1.1, "test1"});
        list.add_first({2, 2.2, "test2"});
        list.remove_all();  
        ASSERT_EQ(list.begin(), list.end());  
    }   
}

TEST(DynamicIteratorTest, ForwardIteratorRequirements) {
    DynamicMemoryResource resource;
    ForwardList<int> list(&resource);
    
    list.add_first(1);
    list.add_first(2);

    auto it = list.begin();
    ASSERT_EQ(*it, 2);
    
    ++it;
    ASSERT_EQ(*it, 1);
    
    auto it2 = list.begin();
    auto it3 = it2++;
    ASSERT_EQ(*it3, 2);  
    ASSERT_EQ(*it2, 1);  
}

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv); 
    return RUN_ALL_TESTS();  
}