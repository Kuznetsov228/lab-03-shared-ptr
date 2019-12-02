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
        ptr = r.ptr;
        counter = r.counter;
        delete r.ptr;
        delete r.counter;

    }
    ~SharedPtr()
    {
        if (ptr != nullptr)
            delete[]ptr;
    }
    auto operator=(const SharedPtr& r)->SharedPtr&{
        ptr=r.ptr;
        counter=r.counter;
        ++*counter;
    }
    auto operator=(SharedPtr&& r)->SharedPtr&{
        ptr = r.ptr;
        counter = r.counter;
        r.ptr = nullptr;
        r.counter = nullptr;
    }

    // РїСЂРѕРІРµСЂСЏРµС‚, СѓРєР°Р·С‹РІР°РµС‚ Р»Рё СѓРєР°Р·Р°С‚РµР»СЊ РЅР° РѕР±СЉРµРєС‚
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
        if (ptr == nullptr ) return 0;
        else cout<<*ptr<<endl;
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
        std:: swap(ptr, r.ptr);
        std:: swap(counter, r.counter);

    }
    // РІРѕР·РІСЂР°С‰Р°РµС‚ РєРѕР»РёС‡РµСЃС‚РІРѕ РѕР±СЉРµРєС‚РѕРІ SharedPtr, РєРѕС‚РѕСЂС‹Рµ СЃСЃС‹Р»Р°СЋС‚СЃСЏ РЅР° С‚РѕС‚ Р¶Рµ СѓРїСЂР°РІР»СЏРµРјС‹Р№ РѕР±СЉРµРєС‚
    atomic_uint* use_count()  {
        if(ptr!= nullptr)   cout<<*counter<<endl;
        else {
            return 0;
        }
    }
};



