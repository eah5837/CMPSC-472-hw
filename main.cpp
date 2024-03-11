#include <iostream>
#include <thread>
#include <vector>
#include <future>
#include <map>
#include <mutex>
#include <condition_variable>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <cctype>

// Simple Logger for Thread Management
std::mutex cout_mutex;
void log(const std::string& message) {
    std::lock_guard<std::mutex> guard(cout_mutex);
    std::cout << message << std::endl;
}

// Thread function for demonstration
void threadFunction(int id) {
    log("Thread " + std::to_string(id) + " executing.");
    std::this_thread::sleep_for(std::chrono::seconds(1));
}

// Inter-Thread Communication Demonstration
std::mutex mtx;
std::condition_variable cv;
bool ready = false;
int shared_value = 0;

void threadWriter() {
    std::unique_lock<std::mutex> lock(mtx);
    shared_value = 2024;  // Example value
    ready = true;
    log("Writer thread has written value.");
    cv.notify_one();
}

void threadReader() {
    std::unique_lock<std::mutex> lock(mtx);
    cv.wait(lock, [] { return ready; });
    log("Reader thread reads value: " + std::to_string(shared_value));
}

// Parallel Text File Processing
std::map<char, int> processSegment(const std::string& segment) {
    std::map<char, int> segmentCount;
    for (char ch : segment) {
        ch = std::toupper(ch);
        segmentCount[ch]++;
    }
    return segmentCount;
}

std::map<char, int> parallelTextProcessing(const std::string& text) {
    size_t length = text.length();
    size_t perThread = length / 4; // Assume 4 threads for simplicity

    std::vector<std::future<std::map<char, int>>> futures;
    for (int i = 0; i < 4; ++i) {
        std::string segment = text.substr(i * perThread, perThread);
        futures.push_back(std::async(std::launch::async, processSegment, segment));
    }

    std::map<char, int> result;
    for (auto& f : futures) {
        auto segmentCount = f.get();
        for (auto& pair : segmentCount) {
            result[pair.first] += pair.second;
        }
    }
    return result;
}

// Main Menu for Demo
void mainMenu() {
    while (true) {
        log("\nMain Menu:\n"
            "1. Thread Management Demo\n"
            "2. Inter-Thread Communication Demo\n"
            "3. Parallel Text File Processing\n"
            "4. Exit");
        log("Enter your choice: ");

        int choice;
        std::cin >> choice;

        if (choice == 1) {
            std::thread t1(threadFunction, 1);
            std::thread t2(threadFunction, 2);
            t1.join();
            t2.join();
        } else if (choice == 2) {
            std::thread writer(threadWriter);
            std::thread reader(threadReader);
            writer.join();
            reader.join();
        } else if (choice == 3) {
            std::string text = "This is a simple example of text to process in parallel.";
            auto result = parallelTextProcessing(text);
            for (const auto& pair : result) {
                log(std::string(1, pair.first) + ": " + std::to_string(pair.second));
            }
        } else if (choice == 4) {
            log("Exiting...");
            break;
        } else {
            log("Invalid choice, please try again.");
        }
    }
}

int main() {
    mainMenu();
    return 0;
}
