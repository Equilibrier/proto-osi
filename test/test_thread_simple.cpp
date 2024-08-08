#include <iostream>
#include <thread>

static bool stop_it = false;

void do_some_work() 
{
    using namespace std::literals::chrono_literals;

    while (!stop_it) {
        std::cout << "tick" << std::endl;
        std::this_thread::sleep_for(1s);
    }
}

int main(int argc, char** argv)
{
    //std::thread t(do_some_work);
    auto t = std::thread(do_some_work);

    std::cin.get();
    stop_it = true;
    t.join();
    std::cout << "thread finished...";
    std::cin.get();

    return 0;
}