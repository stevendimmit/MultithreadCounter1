#include <iostream>
#include <thread>
#include <mutex>

std::mutex mtx;   // mutex to help prevent race conditions      
int counted = 0;  // global counter variable       

void countUp() {
    std::lock_guard<std::mutex> lock(mtx);
    for (int i = 1; i <= 20; ++i) {
        counted = i;  
        std::cout << "Counting up: " << counted << std::endl;
    }
    //std::cout << "Count Up Finished" << std::endl;
}

void countDown() {
    // wait until counted reaches 20 
    while (true) {
        if (counted == 20) {
            break;  
        }
    }
    std::lock_guard<std::mutex> lock(mtx);
    for (int i = 20; i >= 0; --i) {
        counted = i;  
        std::cout << "Counting down: " << counted << std::endl;
    }
}

int main() {
    // start the threads
    std::thread t1(countUp);
    std::thread t2(countDown);

    // join the threads 
    t1.join();
    t2.join();

    std::cout << "Both threads have completed their work." << std::endl;

    return 0;
}