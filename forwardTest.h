//
// Created by xindong on 2/27/2023.
//

#ifndef C__20TEST_FORWARDTEST_H
#define C__20TEST_FORWARDTEST_H
#include <cstdio>
#include <string>

class forwardTest {
private:
    std::string value1;
    std::string value2;
public:
    template<typename S1,typename S2 = std::string,
            typename = std::enable_if_t<std::is_convertible_v<S1,std::string>>>
    forwardTest(S1&& n,S2&& p = "test"):value1(std::forward<S1>(n)),value2(std::forward<S2>(p)){};
};


#endif //C__20TEST_FORWARDTEST_H
