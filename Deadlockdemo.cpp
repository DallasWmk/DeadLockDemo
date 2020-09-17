/**
 * Two philosophers, thinking and eating spaghetti
 */
#include <thread>
#include <mutex>

int spaghetti_count = 5000; //counting spaghetti for simplicity purpose

void philosopher(std::mutex &first_fork, std::mutex &second_fork) {
    while (spaghetti_count > 0) {
        //first_fork.lock();
        //second_fork.lock();
        std::scoped_lock lock(first_fork, second_fork);
        if (spaghetti_count) {
            spaghetti_count--;
        }
        second_fork.unlock();
        first_fork.unlock();
    }
}

int main() {
    std::mutex fork_a, fork_b;
    std::thread P1(philosopher, std::ref(fork_a), std::ref(fork_b));
    std::thread P2(philosopher, std::ref(fork_b), std::ref(fork_a));
    P1.join();
    P2.join();
    printf("The philosophers are done eating.\n");
}
