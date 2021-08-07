#include <iostream>
#include <vector>

struct Foo
{
    std::vector<int> data;
    Foo(std::vector<int> &&data) : data(data) {}
    /* ------------------------------------------- */
    int sum() const
    {
        int s = 0;
        for (int d : data)
            s += d;
        return s;
    }
    /* ------------------------------------------- */
    void print() const
    {
        for (int d : data)
            std::cout << d << " ";
        std::cout << std::endl;
    }
    /* ------------------------------------------- */

};