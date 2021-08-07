#include <map>
#include <vector>
#include <iostream>

#include "learn_utils.h"

struct FooCompLessStruct
{
    bool operator()(const Foo &f1, const Foo &f2) const
    {
        return f1.sum() < f2.sum();
    }
};

int main()
{
    // method 1: define struct comp, should be const; ----------------
    std::map<Foo, int, FooCompLessStruct> m1;
    m1[Foo({1, 2, 3})] = 1;
    m1[Foo({2, 3, 4})] = 2;
    for (const auto &pair : m1)
    {
        std::cout << "key: ";
        pair.first.print();
        std::cout << "value: " << pair.second << std::endl;
    }

    // method 2: define lambda comp; ---------------------------------
    auto FooCompLessLabmda = [](const Foo &f1, const Foo &f2)
    {
        return f1.sum() < f2.sum();
    };

    std::map<Foo, int, decltype(FooCompLessLabmda)> m2(FooCompLessLabmda);
    m2[Foo({3, 4, 5})] = 2;
    m2[Foo({1, 2, 3})] = 10;
    for (const auto &pair : m2)
    {
        std::cout << "key: ";
        pair.first.print();
        std::cout << "value: " << pair.second << std::endl;
    }
}