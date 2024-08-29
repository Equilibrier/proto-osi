#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>
#include <atomic>

std::atomic_int consumer_count;
std::mutex cval_lock;

using namespace std::literals::chrono_literals;

void thread1_consumer() 
{
    
    std::cout << "Thread1 started !..." << std::endl;

    for (int cur_value = 1; cur_value <= 100; cur_value ++) {
        // std::cout << "thrd1 " << cur_value << std::endl;
        {
            // std::cout << "thread1: acquiring lock..." << std::endl;
            std::lock_guard lock(cval_lock);
            // std::cout << "thread1: lock acquired..." << std::endl;
            if (!(cur_value % 2)) std::cout << "thread1 consumed " << cur_value << std::endl;
        
            consumer_count ++;
            // std::cout << "thread1: consumer_count(" << consumer_count << "); cur_value(" << cur_value << ")" << std::endl;
        }

        while (consumer_count < cur_value * 3) std::this_thread::sleep_for(10ms);
    }
    std::cout << "thrd1 finishing" << std::endl;
}

void thread2_consumer() 
{
    using namespace std::literals::chrono_literals;
    std::this_thread::sleep_for(2s);

    std::cout << "Thread2 started !..." << std::endl;

    for (int cur_value = 1; cur_value <= 100; cur_value ++) {
        // std::cout << "thrd2 " << cur_value << std::endl;

        {
            // std::cout << "thread2: acquiring lock..." << std::endl;
            std::lock_guard lock(cval_lock);
            // std::cout << "thread2: lock acquired..." << std::endl;
            if (cur_value % 2) std::cout << "thread2 consumed " << cur_value << std::endl;

            consumer_count ++;
            // std::cout << "thread2: consumer_count(" << consumer_count << "); cur_value(" << cur_value << ")" << std::endl;
        }

        while (consumer_count < cur_value * 3) std::this_thread::sleep_for(10ms);
    }
    std::cout << "thrd2 finishing" << std::endl;
}

void thread3_consumer() 
{
    using namespace std::literals::chrono_literals;
    std::this_thread::sleep_for(2s);

    std::cout << "Thread3 started !..." << std::endl;

    for (int cur_value = 1; cur_value <= 100; cur_value ++) {
        // std::cout << "thrd3 " << cur_value << std::endl;

        {
            // std::cout << "thread3: acquiring lock..." << std::endl;
            std::lock_guard lock(cval_lock);
            // std::cout << "thread3: lock acquired..." << std::endl;
            if (!(cur_value % 10)) std::cout << "thread3 consumed " << cur_value << std::endl;

            consumer_count ++;
            // std::cout << "thread3: consumer_count(" << consumer_count << "); cur_value(" << cur_value << ")" << std::endl;
        }

        while (consumer_count < cur_value *3) std::this_thread::sleep_for(10ms);
    }
    std::cout << "thrd3 finishing" << std::endl;
}

int main(int argc, char ** argv) 
{
    // iterez prin numerele 1, 100, si 3 thread-uri sa consume separat numerele: primul nr pare, al doilea nr impare, al treilea nr divizibile cu 10

    // cur_value - 1:100; consumer_count 1:300;

    consumer_count = 0;

    std::cout << "Starting (3 count) threads..." << std::endl;

    std::thread thrd1(thread1_consumer);
    std::thread thrd2(thread2_consumer);
    std::thread thrd3(thread3_consumer);

    //std::cin.get();

    thrd1.join();
    thrd2.join();
    thrd3.join();

    return 0;
}