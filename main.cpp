#include <iostream>
#include "util.h"
#include <chrono>
#include <complex>
#include <thread>
#include <random>
#include "template_module.h"
#include "optional_test.h"
#include "union_test.h"
#include "dfs797.h"
#include "forwardTest.h"

class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int length = prices.size();

        int leftMin = prices[0];
        int rightMax = prices[length - 1];
        int maxProfit = 0;
        vector<int> leftProfit(0, length);
        vector<int> rightProfit(0, length);
        for (int i = 1; i < length; i++) {
            leftProfit[i] = max(leftProfit[i - 1], prices[i] - leftMin);
            leftMin = min(prices[i], leftMin);

            int r = length - 1 -i;
            rightProfit[i] = max(rightProfit[r + 1],  rightMax - prices[r]);
            rightMax = min(prices[r], rightMax);
        }

        for (int i = 0; i < length; i++) {
            maxProfit = max(maxProfit, leftProfit[i] + rightProfit[i+1]);
        }
        return maxProfit;
    }
};


template<typename T>
void print(const T& value){
    cout << value << endl;
}
template<typename T>
constexpr auto sum(T x){
    return x;
}
template<typename T1,typename T2,typename... TArgs>
constexpr auto sum(T1 x1,T2 x2, TArgs... args){
    return sum(x1+x2,args...);
}

template<typename F>
auto compose(F f)
{
    return [f](auto&&... x){
        return f(
                forward<decltype(x)>(x)...);
    };
}
//template<typename F,typename... Args>
//auto compose(F f,Args... args){
//    return [f,args...](auto&&... x){
//        return f(
//                forward<decltype(x)>(x)...);
//    };
//}
//template<typename F,typename... TAgs>


template<typename T>
void print(T & t){
    std::cout << "左值" << std::endl;
}

template<typename T>
void print(T && t){
    std::cout << "右值" << std::endl;
}

template<typename T>
void testForward(T && v){
    print(v);
    print(std::forward<T>(v));
    print(std::move(v));
}


int main()
{
    auto printBlank = [](const auto& value){
        cout<< value<<' ';
    };
    auto printLine = [](const auto& value){
        cout<< value<<endl;
    };
    auto printVec = [&](const auto& value){
        for_each(value.cbegin(), value.cend(),printBlank);
        printLine("next");
    };
//    auto result = dfsTest();
//    for_each(result.cbegin(), result.cend(), printVec);
    forwardTest forwardTest1 = {"test2"};
    forwardTest forwardTest {forwardTest1};
}




