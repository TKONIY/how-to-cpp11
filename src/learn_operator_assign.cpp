#include <utility>
#include <iostream>

class Object {
private:
    int *_buffer;
public:
    /* -----------------------utils---------------------------------------- */
    void printPtr() { std::cout << _buffer << std::endl; }

    template<typename Index>
    auto elementAt(Index i) -> decltype(_buffer[i]) { return _buffer[i]; }

    Object();

    ~Object();
    /* -----------------------utils---------------------------------------- */


    // noexcept swap() friend
    friend void swap(Object &, Object &) noexcept;

    // Move constructor, to implement move assignment
    Object(Object &&) noexcept;

    // Copy constructor, to implement copy assignment
    Object(const Object &);     // may throw exception but safe.

    // Operator=() support copy and move
    Object &operator=(Object);
};


/* -----------------------utils-------------------------------------------- */

Object::Object() : _buffer(new int[1024]) {}

Object::~Object() { std::cout << "delete[]: " << _buffer << std::endl, delete[]_buffer; }

/* -----------------------utils-------------------------------------------- */



inline void swap(Object &obj1, Object &obj2) noexcept {
    using namespace std;
    swap(obj1._buffer, obj2._buffer);
    cout << "Object's swap is called." << endl;
}

Object::Object(Object &&obj) noexcept
        : _buffer{obj._buffer} {
    obj._buffer = nullptr;
}

Object::Object(const Object &obj) : Object() {
    for (int i = 0; i < 1024; ++i) {
        _buffer[i] = obj._buffer[i];
    }
}

/**
 * @note rules about operator=
 * 1. swap() and corresponding move or copy constructor are required.
 * 2. Declare parameter as value.
 *      Here are techniques called copy-and-swap and move-or-swap. The key is
 *      using move constructor and copy constructor to avoid dangerous situations.
 *      1. obj is a new object. We don't need to check "&obj == this".
 *      2. When using move, it won't throw exception. Both swap() and move constructor
 *         don't throw exception. Also, data in this will be destructed.
 *      3. When using copy, it is exception-safe. Exception will only throw in copy
 *         constructor. We may get an incomplete obj but the origin object is complete.
 */
Object &Object::operator=(Object obj) { // item 2
    swap(*this, obj);
    return *this;
}

int main() {

    {
        std::cout << "-- Move example --" << std::endl;
        Object movedFrom;
        Object movedTo;

        std::cout << "Before operator=: " << std::endl;
        std::cout << "movedFrom.ptr: ", movedFrom.printPtr();
        std::cout << "movedTo.ptr: ", movedTo.printPtr();
        movedTo = std::move(movedFrom);
        std::cout << "After operator=: " << std::endl;
        std::cout << "movedFrom.ptr: ", movedFrom.printPtr();
        std::cout << "movedTo.ptr: ", movedTo.printPtr();

    }

    std::cout << std::endl;

    {
        std::cout << "-- Copy example --" << std::endl;
        Object copyFrom;
        Object copyTo;
        copyFrom.elementAt(16) = 256;
        copyTo.elementAt(16) = 1024;

        std::cout << "Before operator=: " << std::endl;
        std::cout << "copyFrom.ptr: ", copyFrom.printPtr();
        std::cout << "copyTo.ptr: ", copyTo.printPtr();
        std::cout << "copyFrom[16]: " << copyFrom.elementAt(16) << std::endl;
        std::cout << "copyTo[16]: " << copyTo.elementAt(16) << std::endl;
        copyTo = copyFrom;
        std::cout << "After operator=: " << std::endl;
        std::cout << "copyFrom.ptr: ", copyFrom.printPtr();
        std::cout << "copyTo.ptr: ", copyTo.printPtr();
        std::cout << "copyFrom[16]: " << copyFrom.elementAt(16) << std::endl;
        std::cout << "copyTo[16]: " << copyTo.elementAt(16) << std::endl;
    }

}

/**
 * https://stackoverflow.com/questions/77639/when-is-it-right-for-a-constructor-to-throw-an-exception/77705
 */


