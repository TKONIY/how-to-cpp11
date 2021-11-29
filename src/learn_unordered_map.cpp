#include <unordered_map>

#include "learn_utils.h"

/*
 * explicit unordered_map ( size_type n,
 *                          const hasher& hf = hasher(),
 *                          const key_equal& eql = key_equal(),
 *                          const allocator_type& alloc = allocator_type() );
 */

struct FooHashStruct {
    int operator()(const Foo &f) const {
        return f.sum();
    }
};

struct FooEqualsToStruct {
    bool operator()(const Foo &f1, const Foo &f2) const {
        return FooHashStruct()(f1) == FooHashStruct()(f2);
    }
};

int main() {
    // method 1: define hash() && equals_to(), should be const
    std::unordered_map<Foo,
            int,
            FooHashStruct,
            FooEqualsToStruct>
            m1;
    m1[Foo({1, 2, 3})] = 10;
    m1[Foo({1, 10, 20})] = 3;
    std::cout << "m1[Foo({2, 1, 3})] = " << m1.at(Foo({2, 1, 3})) << std::endl;

    // method 2: define lambda hasher && key_equal
    auto fooHashLambda = [](const Foo &f) {
        return f.sum();
    };

    auto fooEqualsToLambda = [](const Foo &f1, const Foo &f2) {
        return f1.sum() == f2.sum();
    };

    std::unordered_map<Foo,
            int,
            decltype(fooHashLambda),
            decltype(fooEqualsToLambda)>
            m2(100, fooHashLambda, fooEqualsToLambda);
    m2[Foo({1, 2, 3})] = 10;
    m2[Foo({1, 10, 20})] = 3;
    std::cout << "m2[Foo({2, 1, 3})] = " << m2.at(Foo({2, 1, 3})) << std::endl;
}