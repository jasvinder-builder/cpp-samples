#include<condition_variable>
#include <iostream>
#include <mutex>
#include <thread>
#include <vector>

class CircularBuffer {
public:
    CircularBuffer(int buffSize);
    void write(int val);
    int read();
private:
    std::vector<int> buffer_;
    int buffSize_;
    int count_;
    int readIdx_;
    int writeIdx_;
    std::mutex mutex_;
    std::condition_variable notEmpty_;
    std::condition_variable notFull_;
};

CircularBuffer::CircularBuffer(int buffSize):buffSize_(buffSize), buffer_(buffSize), readIdx_(0), writeIdx_(0), count_(0) {}
void CircularBuffer::write(int val) {
    std::unique_lock<std::mutex> lock(mutex_);
    notFull_.wait(lock, [this] {return count_ < buffSize_;});
    buffer_[writeIdx_] = val;
    std::cout << "Wrote " << val << std::endl;
    writeIdx_ = (writeIdx_ + 1) % buffSize_;
    count_++;

    notEmpty_.notify_one(); 
}

int CircularBuffer::read() {
    std::unique_lock<std::mutex> lock(mutex_);
    notEmpty_.wait(lock, [this] {return count_ > 0;});
    int result = buffer_[readIdx_];
    std::cout << "Read " << result << std::endl; 
    readIdx_ = (readIdx_ + 1) % buffSize_;
    count_--;

    notFull_.notify_one();
    return result;
}

int main() {
    CircularBuffer cBuff(3);

    std::thread t1([&cBuff] {    
        for (int i = 0; i < 6; i++) {
            cBuff.write(i); 
    }});

    std::thread t2([&cBuff] {
        for (int i = 0; i < 6; i++) {
            cBuff.read(); 
    }});

    t1.join();
    t2.join();

    return 0;
}