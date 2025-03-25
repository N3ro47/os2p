#include <iostream>
#include <vector>
#include <mutex>
#include <thread>
#include <chrono>
#include <random>
#include <cstdlib>
#include <immintrin.h>

void philosopher(int id, int N, std::vector<std::mutex>& forks, std::mutex& print_mutex) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(1, 200);

    // Each philosopher performs 10 cycles of thinking and eating hardcode 10 cycles for eating
    for (int iter = 0; iter < 10; ++iter) {
        // Thinking phase
        {
            std::lock_guard<std::mutex> lock(print_mutex);
            std::cout << "Philosopher " << id << " is thinking" << std::endl;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(dist(gen)));

        // Eating phase
        {
            // Lock both forks simultaneously to avoid deadlock
            std::scoped_lock lock(forks[id], forks[(id + 1) % N]);
            {
                std::lock_guard<std::mutex> lock(print_mutex);
                std::cout << "Philosopher " << id << " is eating" << std::endl;
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(dist(gen)));
        } // Forks are released here
    }
}

int main(int argc, char* argv[]) {
    // Validate command-line argument
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <number_of_philosophers>" << std::endl;
        return 1;
    }

    int N = std::stoi(argv[1]);
    if (N < 2) {
        std::cerr << "Number of philosophers must be at least 2" << std::endl;
        return 1;
    }

    // Initialize resources
    std::vector<std::mutex> forks(N);
    std::mutex print_mutex;
    std::vector<std::thread> philosophers;

    // Create philosopher threads
    for (int i = 0; i < N; ++i) {
        philosophers.emplace_back(philosopher, i, N, std::ref(forks), std::ref(print_mutex));
    }

    // Wait for all philosophers to complete
    for (auto& t : philosophers) {
        t.join();
    }

    return 0;
}