#include <iostream>
#include <mutex>
#include <queue>
#include <condition_variable>
#include <thread>

constexpr int NUM_MSGS = 5;

struct Message {
    int value;
};

class PC {
public:

void producer() {
    for (int i = 0; i < NUM_MSGS; i++) {
        std::unique_lock<std::mutex> lck(mtx);
        queue.push(Message{i});
        std::cout << "Pushed msg: " << i << std::endl; 
        cv.notify_one();
    }
}

void consumer() {
    for (int i = 0; i < NUM_MSGS; i++) {
        std::unique_lock<std::mutex> lck(mtx);
        cv.wait(lck, [this]{return !queue.empty();});
        int val = queue.front().value;
        queue.pop();
        std::cout << "Popped msg: " << i << std::endl;
        lck.unlock();
    }
}

private:
  std::queue<Message> queue;
  std::mutex mtx;
  std::condition_variable cv;
};

int main() {
    PC pc;
    std::thread t1(&PC::producer, &pc);
    std::thread t2(&PC::consumer, &pc);
    t1.join();
    t2.join();

    return 0;

}


