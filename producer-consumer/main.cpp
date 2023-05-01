#include <iostream>
#include <mutex>
#include <queue>
#include <condition_variable>
#include <thread>

struct Message {
    int value;
};

class PC {
public:

void producer() {
    for (int i = 0; i < 10; i++) {
        {
            std::unique_lock<std::mutex> lck(mtx);
            queue.push(Message{i});
            cv.notify_one();
        }
        std::cout << "Pushed msg: " << i << std::endl; 
    }
}

void consumer() {
    for (int i = 0; i < 10; i++) {
        std::unique_lock<std::mutex> lck(mtx);
        cv.wait(lck, [this]{return !queue.empty();});
        int val = queue.front().value;
        queue.pop();
        lck.unlock();
        std::cout << "Popped msg: " << i << std::endl;
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


