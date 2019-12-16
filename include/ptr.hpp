//
// Created by pca18 on 02.12.19.
//


#include <iostream>
#include <atomic>

using namespace std;
using std::atomic_uint;

template <typename T>
class SharedPtr{
private:
    T *ptr;
    atomic_uint* counter;

public:

    SharedPtr()
    {
        ptr = nullptr;
        counter  = nullptr;
    }
    SharedPtr(T* ptr)
    {
        this->ptr = ptr;
        this->counter= new atomic_uint(1);;

    }
    SharedPtr(const SharedPtr& r)
    {
        ptr=r.ptr;
        counter=r.counter;

        ++*counter;

    }
    SharedPtr(SharedPtr&& r){
        this->swap(r);

    }
    ~SharedPtr()
    {
        this->reset();
    }
    auto operator=(const SharedPtr& r)->SharedPtr&{
        r.swap(*this);
        return *this;
    }
    auto operator=(SharedPtr&& r)->SharedPtr&{
        std::move(r).swap(*this);
        return *this;
    }

    
    operator bool() const{
        return ptr!= nullptr;
    }
    auto operator*() const->T&
    {
        return *ptr;
    }
    auto operator->() const->T*
    {
        return this->ptr;
    }



    auto get()->T*{
        return this->ptr;
    
    }
    void reset(){
        ptr= nullptr;
        counter= nullptr;
        delete ptr;
        delete counter;

    }
    void reset(T* ptr){
        if(counter != nullptr) counter= nullptr;
        this->ptr=ptr;
        counter=new atomic_uint(1);

    }
    void swap(SharedPtr& r){
        std::swap(ptr, r.ptr);
        std::swap(counter, r.counter);

    }
    
    atomic_uint* use_count()  {
        return this->counter;
        
            
        
    }
};


