// Design pattern: observer

#include <memory>
#include <iostream>
#include <vector>
#include <mutex>
#include <thread>

class Observer;
class Observerable;

class Observer : public std::enable_shared_from_this<Observer>
{
private:
    std::shared_ptr<Observerable> _obj;

public:
    void update();
    void observe(const std::shared_ptr<Observerable> &obj);
};

class Observerable
{
private:
    std::vector<std::weak_ptr<Observer>> observers;
    std::mutex _mutex;

public:
    void register_(std::weak_ptr<Observer> observer);
    void notifyObservers();
};

/* class Observer; */
/*------------------------------------------------*/
void Observer::update()
{
    std::cout << "Observer::update" << std::endl;
}
/*------------------------------------------------*/
void Observer::observe(const std::shared_ptr<Observerable> &obj)
{
    obj->register_(shared_from_this());
}
/*------------------------------------------------*/


/* class Observerable; */
/*------------------------------------------------*/
void Observerable::register_(std::weak_ptr<Observer> observer)
{
    observers.push_back(observer);
}

/*------------------------------------------------*/
void Observerable::notifyObservers()
{
    std::lock_guard<std::mutex> lock(_mutex);

    auto it = observers.begin();
    while (it != observers.end())
    {
        auto sptr = it->lock();
        if (sptr)
        {
            sptr->update();
            ++it;
        }
        else
        {
            it = observers.erase(it);
        }
    }
}
/*------------------------------------------------*/


int main()
{
    auto obj = std::make_shared<Observerable>();
    std::vector<std::thread> threads;
    for (int i = 0; i < 10; ++i)
    {
        threads.push_back(
            std::thread([&]()
                        {
                            auto obs = std::make_shared<Observer>();
                            obs->observe(obj);
                            std::this_thread::sleep_for(std::chrono::seconds(2));
                        }));
    }
    obj->notifyObservers();
    for (auto &thread : threads)
    {
        thread.join();
    }
}