#include <iostream>

template<typename T, int N>
constexpr int arraySize(T (&)[N]) noexcept {
    return N;
}

int main() {
    const char arr[] = {"adidas"};
    std::cout << "array's length = " << arraySize(arr) << std::endl;
}