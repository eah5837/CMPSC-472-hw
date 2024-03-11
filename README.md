# Operating System Simulation

This project is a comprehensive simulation of an operating system, including multi-process and thread management, inter-process communication (IPC) mechanisms, parallel text file processing, and a simple user interface.

## Key Features

- **Multi-Process and Thread Manager:** Provides functionalities to create, manage, and monitor processes and threads.
- **Inter-Process Communication (IPC) Mechanisms:** Implements IPC using shared memory and message passing between processes and threads.
- **Parallel Text File Processing:** Efficiently processes large text files by parallelizing character conversion and counting.
- **Simple User Interface:** Offers a command-line interface (CLI) for users to interact with the simulation.

## Getting Started

### Prerequisites

- C++ compiler (e.g., g++)
- Git

### Installation

1. Clone the repository:

    ```bash
    git clone https://github.com/your_username/operating-system-simulation.git
    ```

2. Navigate to the project directory:

    ```bash
    cd operating-system-simulation
    ```

3. Compile the source code:

    ```bash
    g++ -o simulation main.cpp -std=c++11 -pthread
    ```

4. Run the simulation:

    ```bash
    ./simulation
    ```

## Usage

- Upon running the simulation, you will be presented with a main menu where you can choose various options:
  - Manage Processes/Threads
  - IPC Operations
  - File Processing
  - Exit

## Contributing

Contributions are welcome! Feel free to open issues or pull requests for any improvements or additional features you'd like to see.

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.
