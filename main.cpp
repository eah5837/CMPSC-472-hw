#include <iostream>
#include <thread>
#include <mutex>
#include <vector>
#include <future>
#include <unistd.h>

// Key Feature 1: Multi-Process and Thread Manager
void worker_process() {
    std::cout << "Worker process ID: " << getpid() << std::endl;
}

void worker_thread() {
    std::cout << "Worker thread ID: " << std::this_thread::get_id() << std::endl;
}

// Key Feature 2: Inter-Process Communication (IPC) Mechanisms
std::mutex mtx;
void producer_consumer() {
    std::vector<int> shared_data;
    // Producer
    std::thread producer([&shared_data]() {
        for (int i = 0; i < 5; ++i) {
            std::lock_guard<std::mutex> lock(mtx);
            shared_data.push_back(i);
            std::cout << "Produced " << i << std::endl;
        }
    });
    // Consumer
    std::thread consumer([&shared_data]() {
        for (int i = 0; i < 5; ++i) {
            std::lock_guard<std::mutex> lock(mtx);
            std::cout << "Consumed " << shared_data.back() << std::endl;
            shared_data.pop_back();
        }
    });
    producer.join();
    consumer.join();
}

// Key Feature 3: Parallel Text File Processing (Dummy Example)
int process_data(int data) {
    // Placeholder for data processing logic
    return data * data;
}

void parallel_processing() {
    std::vector<int> data_to_process = {1, 2, 3, 4, 5};
    std::vector<std::future<int>> results;

    for (int data : data_to_process) {
        results.emplace_back(std::async(std::launch::async, process_data, data));
    }

    for (auto& result : results) {
        std::cout << result.get() << std::endl;
    }
}

// Key Feature 4: Simple User Interface (CLI)
void main_menu() {
    while (true) {
        std::cout << "\nMain Menu:\n"
                     "1. Manage Processes/Threads\n"
                     "2. IPC Operations\n"
                     "3. File Processing\n"
                     "4. Exit\n"
                     "Enter your choice: ";

        int choice;
        std::cin >> choice;

        switch (choice) {
            case 1:
                std::cout << "Process/Thread Management Selected" << std::endl;
                std::cout << "Process ID: " << getpid() << std::endl;
                std::cout << "Thread ID: " << std::this_thread::get_id() << std::endl;
                break;
            case 2:
                std::cout << "IPC Operations Selected" << std::endl;
                producer_consumer();
                break;
            case 3:
                std::cout << "File Processing Selected" << std::endl;
                parallel_processing();
                break;
            case 4:
                std::cout << "Exiting..." << std::endl;
                return;
            default:
                std::cout << "Invalid choice, please try again." << std::endl;
        }
    }
}

int main() {
    main_menu();
    return 0;
}
