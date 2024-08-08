#include <iostream>
#include <thread>
#include <condition_variable>

static int result = 0;
// static bool finished = false;
static std::mutex m;
static std::condition_variable cv;

void do_work()
{
    std::cout << "worker: Waiting for processing data" << std::endl;
    std::unique_lock<std::mutex> lock(m);
    cv.wait(lock);

    std::cout << "worker: Processing result..." << std::endl;
    result += 6; result *= 23;
    std::this_thread::sleep_for(std::chrono::seconds(3));
    std::cout << "worker: Finished processing result..." << std::endl;
    // finished = true;

    cv.notify_one();
    lock.unlock();
}

int main(int argc, char ** argv) 
{
    using namespace std::literals::chrono_literals;

    std::thread t(do_work);
    std::this_thread::sleep_for(2s);
    std::cout << "main: Will unlock worker and stop..." << std::endl;
    cv.notify_one();

    std::unique_lock<std::mutex> lock(m);
    // cv.wait(lock, [&] { return finished; });
    cv.wait(lock);

    std::cout << "main: Worker got me the pen again, result is ready and value is " << result << std::endl;
    lock.unlock();

    t.join();

    std::cout << "Program will be finished" << std::endl;

    return 0;
}