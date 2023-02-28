//
// Created by xindong on 2/1/2023.
//
#include "util.h"
#include <optional>
#include <cassert>

void optional_test(){
    optional<int> op1 = 42;
    if(op1.has_value()){
        cout<< op1.value()  << endl;
    }
    optional<int> op2;
    cout<< op2.value_or(99)  << endl;

    optional<string> op3 {"test"};
    assert(op3);
    assert(!op3->empty() && *op3 == "test");

    op3.reset();
    assert(!op3);

    auto make_op1 = make_optional<int>();
    auto make_op2= make_optional<string>();

    assert(make_op1 && make_op2);
    assert(make_op1 == 0);
    assert(make_op2->empty());

    optional<bool> op_bool = true;
    if(op_bool and op_bool.value()){
        cout << "right" << endl;
    }
}