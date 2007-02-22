
#include <OpenThreads/Thread>
#include <iostream>

class MyThread : public OpenThreads::Thread
{
public:
    void run()
    {
        std::cout << "Running thread" << std::endl;
    }
};

int main()
{
    MyThread t;
    t.start();
    t.join();
}
