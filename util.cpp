//
// Created by xindong on 1/28/2023.
//
template<typename T>
void print_vec(const T& vec){
    for_each(begin(vec),end(vec),[](auto x){
        printf("%d\n",x);
    });
}


