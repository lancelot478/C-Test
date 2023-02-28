//
// Created by xindong on 2/1/2023.
//
#include "util.h"
//#include <cassert>
//#include <mutex>

//#include "variant"
//union {
//    int n;
//    float f;
//    double d;
//} x;
//
//
//void test(){
//    x.d = 1.0;
//    x.n = 1;
//
//    variant<int,float,string> v;
//    v = 3.14f;
//    assert(v.index() == 1);
//
//    assert(get<1>(v) = 3.14f);
//    assert(get<float>(v) = 3.14f);
//
//    auto p = get_if<int>(&v);
//    assert(p == nullptr);
//
//    auto visitor = [](auto& x){
//        x = x + x;
//        cout << x << endl;
//    };
//    v = 10;
//    visit(visitor,v);
//    v = "ok";
//    visit(visitor,v);
//}
//class Singleton{
//public:
//    static Singleton* instance();
//private:
//    static Singleton* inst_ptr;
//};
//Singleton* Singleton::inst_ptr = nullptr;
//Singleton* Singleton::instance(){
//    if(inst_ptr == nullptr){
////        lock_guard lock;
//        if(inst_ptr == nullptr){
//            inst_ptr = new Singleton();
//        }
//    }
//    return inst_ptr;
//}

int Pentagonal(int n){
    return n * (3 * n - 1)/2;
}
void union_test(){
//   test();
//    int value;
//    cin >> value;
//    auto ret1 = 1 << value;
//    auto ret = ((1 << value) & value) > 0 ;
//    cout << ret1;
//    cout << ret;
    int n;
    cin >> n;
    Pentagonal(n);
    vector<int> testVec;
    testVec.begin();
    sort(testVec.begin(),testVec.end(),greater<int>());
}