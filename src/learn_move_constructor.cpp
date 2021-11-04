#include <utility>
#include <iostream>

class Object {
private:
    int *_buffer;

public:
    Object();

    ~Object();

    Object(Object &&) noexcept;
};

Object::Object() {
    _buffer = new int[1024];
}

Object::~Object() {
    std::cout << "Object is deleted: " << _buffer << std::endl;
    delete[]_buffer;
}

/**
 * @note rules for move constructor
 * 1. Source object is safe to delete.
 *      After moved, source object will execute it's destructor.
 * 2. Can't throw exception.
 *      If exception is thrown, both source and destination objects are incomplete.
 */
Object::Object(Object &&srcObj) noexcept    // item 2
        : _buffer{srcObj._buffer} {
    srcObj._buffer = nullptr;               // item 1
}

int main() {
    Object obj1;
    std::cout << "before move" << std::endl;
    Object obj2(std::move(obj1));
    std::cout << "after move" << std::endl;

    /**
     * @note moved-from objects are still destructed
     * C++ only provides move as a semantic concept. It doesn't
     * guarantee any action. moved-from objects are still object.
     * They will follow the RAII rule to destructed. That's why
     * we have item 1.
     */
}



