//
// Created by xindong on 1/28/2023.
//
#include "util.h"

//recursion template
template <int n>
struct factorial{
    static const int value =
    n * factorial<n-1>:: value;
};
template<>
struct factorial<0>{
    static const int value = 0;
};

//If template
template <bool cond,typename Then,typename Else>
struct If;
template <typename Then,typename Else>
struct If<true,Then,Else>{
    typedef Then type;
};
template <typename Then,typename Else>
struct If<false,Then,Else>{
    typedef Else type;
};

//loop template
template<bool condition,typename Body>
struct WhileLoop;

template<typename Body>
struct WhileLoop<true,Body>{
    typedef typename WhileLoop<Body::cond_value,typename Body::next_type>::type type;
};
template<typename Body>
struct WhileLoop<false,Body>{ typedef typename Body::res_type type; };
template<typename Body>
struct While{
    typedef typename WhileLoop<Body::cond_value,Body>::type type;
};

template<class T,T v>
struct custom_integral_constant{
    static const T value = v;
    typedef T value_type;
    typedef custom_integral_constant type;
};

template<int result,int n>
struct SumLoop{
    static const int res_value = result;
    static const bool cond_value = n != 0;
    typedef custom_integral_constant<int,res_value> res_type;
    typedef SumLoop<result+n,n-1> next_type;
};

template<int n>
struct Sum{
    typedef SumLoop<0,n> type;
};

template <template <typename, typename>class OutContainer = vector,
typename F, class R>
auto fmap(F&& f, R&& inputs)
{
    typedef decay_t<decltype(f(*inputs.begin()))> result_type;
    OutContainer<result_type,allocator<result_type>> result;
    for (auto&& item : inputs) {
        result.push_back(f(item));
    }
    return result;
}
void test(){
    auto x = While<Sum<10>::type>::type::value;

    using remover_string = remove_const<const string>::type;
    // char* const is a const pointer, while const char* is a pointer to const char.
    using remover_const_char = remove_const<char* const>::type;
    // _t is a syntax sugar to "::type"
    using remover_const_string = remove_const_t<const string>;

    vector<int> v{1,2,3,4,5};

    auto add  = [](int x){
        return  x + 1;
    };
    auto result = fmap(add, v);

    print_vec(result);
}
// substitution failure is not  an error
struct Test{
    typedef int foo;
};
template<typename T>
void f(typename T::foo){
    puts("3");
}
template<typename T>
void f(T){
    puts("4");
}
//SFINAE substitution failure is not a error;
//struct X {
//    typedef int type;
//};
//
//struct Y {
//    typedef int type2;
//};
//
//template <typename T> void foo(typename T::type);    // Foo0
//template <typename T> void foo(typename T::type2);   // Foo1
//template <typename T> void foo(T);                   // Foo2
//
//void callFoo() {
//    foo<X>(5);    // Foo0: Succeed, Foo1: Failed,  Foo2: Failed
//    foo<Y>(10);   // Foo0: Failed,  Foo1: Succeed, Foo2: Failed
//    foo<int>(15); // Foo0: Failed,  Foo1: Failed,  Foo2: Succeed
//}
//template <typename T>
//struct has_reserve {
//    struct good {char dummy;};
//    struct bad {char dummy[2];};
//    template<class U,void (U::*)(size_t)>
//            struct SFINAE{};
//    template<class U>
//            static good reserve(SFINAE<U,&U::reserver>*);
//
//    template<class U>
//            static bad reserve(...);
//            static const bool value = sizeof(reserve<T>(nullptr)) == sizeof(good);
//    };

//template<typename C,typename T>
//enable_if_t<has_reserve<C>::value,void>
//append(C& container,T* ptr,size_t size){
//    container.reserve(container.size()+ size);
//    for(size_t i = 0;i <size;++i){
//        container.push_back(ptr[i]);
//    }
//}
//
//template<typename C,typename T>
//enable_if_t<!has_reserve<C>::value,void>
//append(C& container,T* ptr,size_t size){
//    for(size_t i = 0;i <size;++i){
//        container.push_back(ptr[i]);
//    }
//}

// use "declval" and "void_t" to check the validation
template<typename T,typename = void_t<>>
struct has_reserve : false_type {};
template<typename T>
struct has_reserve<T,void_t<decltype(declval<T&>().reserve(1U))>> : true_type {};

//tag dispatch : true_type,false_type
template<typename C,typename T>
auto _append(C& container,T* ptr,size_t size,true_type){
    container.reserve(container.size()+ size);
    for(size_t i = 0;i <size;++i){
        container.push_back(ptr[i]);
    }
}
template<typename C,typename T>
auto _append(C& container,T* ptr,size_t size,false_type){
    for(size_t i = 0;i <size;++i){
        container.push_back(ptr[i]);
    }
}
template<typename C,typename T>
auto append(C& container,T* ptr,size_t size){
    _append(container,ptr,size,
            integral_constant<bool,has_reserve<C>::value>{});
            //has_reserve<C>{}
            // because has_reserve inherit from true_type,so above is also right
}
//template match for define a type
template<typename T,typename U>
struct struct_is_same : public true_type {};
template<typename T>
struct struct_is_same<T,T> : public false_type {};

struct inlineConstTest{
        //"const" default is not inline,so must has "one definition rule"
//        static const int num = 1;
        //constexpr default is inline and define
       static constexpr int num = 1;
    };
// "one definition rule" for class static constant value;
//const int inlineConstTest::num;

//template  variables
template<class T>
        inline constexpr bool is_trivially_destructible_v = is_trivially_destructible<T>::value;

// operator value_type() implicit conversion
bool b =  integral_constant<bool, true>();


template <typename T, typename U>
struct convertible
{
private:
    static std::true_type Check(T);
    static std::false_type Check(...);
public:
    bool value = std::is_same<decltype(Check(declval<U>())), std::true_type>::value;
};
//template for check is pair<T,U>
template<typename T>
struct is_pair : false_type {};
template<typename T,typename U>
struct is_pair<pair<T,U>> : true_type {};
template<typename T>
inline constexpr bool is_pair_v = is_pair<T>::value;
//check has out put function
template<typename T>
struct has_output_function{
    template<class U>
            static auto output(U* ptr) ->
            decltype(declval<ostream&>() << *ptr,std::true_type());
    template<class U>
            static false_type output(...);
    static constexpr bool value = decltype(output<T>(nullptr))::value;
};
template <typename T>
inline constexpr bool has_output_function_v = has_output_function<T>::value;


template <typename T,typename U>
ostream& operator<<(ostream& os,const pair<T,U>& pr);
//Cont define a key_type and has value type as std::pair
template <typename T,typename Cont>
auto output_element(ostream& os,const T& element,const Cont&,const true_type)->
decltype(declval<typename Cont::key_type>(),os);
//Output function for other Cont
template <typename T,typename Cont>
auto output_element(ostream& os,const T& element,const Cont&,...) -> decltype(os);

//template <typename T,typename = enable_if_t<!has_output_function_v<T>>>
//auto operator<<

struct Counter {
    void increase() {
        // Implements
    }
};
template <typename T>
void inc_counter(T& intTypeCounter, std::decay_t<decltype(++intTypeCounter)>* = nullptr) {
    ++intTypeCounter;
}
template <typename T>
void inc_counter(T& counterObj, std::decay_t<decltype(counterObj.increase())>* = nullptr) {
    counterObj.increase();
}
void doSomething() {
    Counter cntObj;
    uint32_t cntUI32;
    // blah blah blah
    inc_counter(cntObj);
    inc_counter(cntUI32);
}

void template_module_test(){
    doSomething();
}
