# Traveling Salesman Problem (TSP) - Research & Implementation

## Overview
This project explores and implements solutions for the Traveling Salesman Problem (TSP), a fundamental problem in combinatorial optimization and graph theory. The project includes a C++ implementation, a Python script for visualization, test data, and a research paper detailing the methodology, performance analysis, and findings.

## Repository Contents

### 1. **Research Paper** ([TestingandAnalysis.pdf](https://github.com/muhammadrasheed03/Projects/blob/main/Traveling%20Salesman/TestingandAnalysis.pdf))
   - Provides a detailed analysis of different approaches to solving TSP.
   - Discusses the implemented algorithm, test cases, and performance evaluations.
   - Includes theoretical background and experimental results.

### 2. **Source Code** ([tsm.cpp](https://github.com/muhammadrasheed03/Projects/blob/main/Traveling%20Salesman/tsm.cpp))
   - Implements an algorithm to solve TSP efficiently.
   - Utilizes heuristic and/or exact methods for finding optimal or near-optimal routes.
   - Reads input data from a file and computes the shortest possible tour.

### 3. **Plotting Script** ([plotting.py](https://github.com/muhammadrasheed03/Projects/blob/main/Traveling%20Salesman/plotting.py))
   - Uses Matplotlib to visualize the computed tour.
   - Plots the path taken by the traveling salesman based on test data.

### 4. **Test Coordinates** ([testcoordinates.txt](https://github.com/muhammadrasheed03/Projects/blob/main/Traveling%20Salesman/testcoordinates.txt))
   - Contains sample coordinates for testing the algorithm.
   - Serves as input data for `tsm.cpp` to evaluate performance.

### 5. **CMake Build Configuration** ([CMakeLists.txt](https://github.com/muhammadrasheed03/Projects/blob/main/Traveling%20Salesman/CMakeLists.txt))
   - Defines the CMake configuration to compile and build the project.
   - Ensures compatibility with various environments.

## Technologies Used
- **C++** (Algorithm implementation)
- **Python (Matplotlib, NumPy)** (Data visualization and analysis)
- **CMake** (Build configuration)
- **LaTeX or Word Processing** (For research paper preparation)

## How to Run the Project
### Running the TSP Solver (C++)
1. Compile the C++ program using CMake:
   ```sh
   mkdir build && cd build
   cmake ..
   make
   ```
2. Run the program with test coordinates:
   ```sh
   ./tsm ../testcoordinates.txt
   ```

### Plotting the Results (Python)
Run the Python script to visualize the output:
   ```sh
   python3 plotting.py
   ```

## Research Findings
- The research paper provides insights into the effectiveness of different TSP-solving techniques.
- Performance metrics and comparisons between algorithms are discussed in detail.

## Author
**Muhammad Rasheed**
**Sanchit Singhal**
**Yash Jain**

For questions or contributions, feel free to open an issue or submit a pull request!

