#include <cstdlib>

template<typename T, int N>
class SafeArray {
public:
    SafeArray() = default;

    // match non-const lvalue
    T &operator[](std::size_t i) &;

    // match rvalue
    T operator[](std::size_t i) &&;

    // match const lvalue
    const T &operator[](std::size_t i) const &;


private:
    T array[N]{};
};

template<typename T, int N>
T &SafeArray<T, N>::operator[](std::size_t i) &{
    return array[i];
}

template<typename T, int N>
T SafeArray<T, N>::operator[](std::size_t i) &&{
    return array[i];
}

template<typename T, int N>
const T &SafeArray<T, N>::operator[](std::size_t i) const &{
    return array[i];
}

int main() {
    const SafeArray<int, 10> constSafeArray;
    SafeArray<int, 10> nonConstSafeArray;

    // [ERROR] get ref of temporary object;
    // auto &val = SafeArray<int, 10>()[1];

    // [CORRECT] get value of temporary object;
    auto val = SafeArray<int, 10>()[1];


    // [ERROR] modified const object;
    // constSafeArray[1] = 0;

    // [CORRECT] read const object;
    const auto &cref = constSafeArray[1];

    // [CORRECT] write non-const object;
    nonConstSafeArray[1] = 0;

}