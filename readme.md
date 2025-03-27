# Dining Philosophers Problem

## Overview
This project implements the Dining Philosophers Problem using C++ with multi-threading. It simulates philosophers who alternately think and eat, ensuring that the shared resources (forks) are accessed safely without causing a deadlock.

## Problem Description
In this simulation:
- **Philosophers**: Represented by threads, each philosopher alternates between thinking and eating.
- **Forks**: Shared resources modeled as mutexes. Each philosopher requires two forks (one on the left and one on the right) to eat.
- **Deadlock Avoidance**: To prevent deadlock, the program locks both adjacent forks simultaneously using `std::scoped_lock`.

## Project Structure
- **`dining_philosophers.cpp`**: The main source file containing the implementation of the simulation.
- **`Makefile`**: Build script to compile the project with `g++`.

## How to Compile and Run
1. **Compile the Project**  
   Open a terminal in the project directory and run:
   ```bash
   make
   ```
2. **Run the Executable**  
   Execute the program with the desired number of philosophers:
   ```bash
   ./dining_philosophers <number_of_philosophers>
   ```
   For example, to run with 5 philosophers:
   ```bash
   ./dining_philosophers 5
   ```

## Critical Sections and Their Solutions
- **Fork Access**:  
  - **Critical Section**: When a philosopher picks up forks to eat.  
  - **Solution**: `std::scoped_lock` is used to lock both forks (the left and the right) simultaneously and in always the same order. This prevents deadlock by ensuring that a philosopher never holds one fork while waiting indefinitely for the other.

#Part 2
project is in the submodule
```bash
git submodule update --init 
```