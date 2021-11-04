#include <utility>
#include <iostream>

/**
 * @note rules for a swap() function
 * 1. Defined as a friend function.
 *      In order to use private members.
 * 2. Defined as inline.
 * 3. Can't throw exception.
 *      If exception is thrown, both objects are incomplete.
 * 4. Using namespace std before usage.
 *      If the object has swap() friend, compiler will match
 *      it. Otherwise std::swap() is called.
 */
class Object {
private:
    int *_buffer;

    friend                                  // item 1
    void swap(Object &, Object &) noexcept;

public:
    Object() : _buffer(new int[1024]) {}

    ~Object() { delete[]_buffer; }
};

inline                                      // item 2
void swap(Object &obj1, Object &obj2)
noexcept {                                  // item 3
    using namespace std;
    swap(obj1._buffer, obj2._buffer);
    cout << "Object's swap is called." << endl;
}

int main() {
    Object obj1, obj2;
    using namespace std;                    // item 4
    swap(obj1, obj2);
}