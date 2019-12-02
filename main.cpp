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



int main()
{
    int a=4;

    SharedPtr<int> p1(&a);
    SharedPtr<int> p2(p1);
    SharedPtr<int> p3(new int(5));
    SharedPtr<int> p4;

    cout<<"p1 and p3 count"<<endl;
    p1.use_count();
    p3.use_count();
    cout<<"p1, p2, p3:"<<endl;
    cout<<"p1:";
    p1.get();
    cout<<"p2:";
    p2.get();
    cout<<"p3:";
    p3.get();



    cout<<"swap:"<<endl;
    p3.swap(p1);
    cout<<"p1, p2, p3:"<<endl;
    cout<<"p1:";
    p1.get();
    cout<<"p2:";
    p2.get();
    cout<<"p2:";
    p3.get();
    cout<<"p1 and p3 count"<<endl;
    p1.use_count();
    p3.use_count();

    cout<<"p1.reset() and p3.reset(T* ptr):"<<endl;
    p1.reset();
    p3.reset(new int(10));
    cout<<"p1:"<<endl;
    p1.get();
    cout<<"p3:";
    p3.get();

    cout<<"p4=p2:"<<endl;
    p4=p2;
    cout<<"p4:";
    p4.get();
    cout<<"p2:";
    p2.get();




    return 0;
}