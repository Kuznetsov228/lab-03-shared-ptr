

public:#include <iostream>
#include <atomic>
#include "ptr.h"

using namespace std;
using std::atomic_uint;




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

    
