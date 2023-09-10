# Tabular Data Manipulation with C++ 

## Overview
Welcome to the world of advanced tabular data manipulation with this powerful C++ program. This remarkable code allows you to read, process, and analyze tabular data with ease and efficiency. Whether you're a data scientist, programmer, or simply curious, this code is designed to impress and empower you.

## Table of Contents

- [Features](#features)
- [Prerequisites](#prerequisites)
- [Getting Started](#getting-started)
- [Command Reference](#command-reference)
- [Exception Handling](#exception-handling)
- [Memory Management](#memory-management)
- [Usage Examples](#usage-examples)
- [Contributing](#contributing)
- [License](#license)

## Features

This sophisticated C++ program boasts an impressive array of features:

1. **Robust Data Handling**: Seamlessly read and store tabular data from CSV files.

2. **Exception Handling**: Exceptional error handling with custom exceptions (`RecordNotFoundException` and `WrongDataTypeException`) to ensure your data remains safe and your code remains robust.

3. **Data Sorting**: Quickly sort your data based on the contents of the first column, facilitating easy data retrieval.

4. **Data Searching**: Efficiently search for records within your dataset using a variety of search criteria.

5. **Data Analysis**: Find minimum values within numeric columns, with built-in support for different data types.

6. **Data Extraction**: Extract specific rows, columns, or subsets of your data, offering flexibility in data manipulation.

7. **Command-Driven Interface**: A user-friendly, command-line interface enables you to interact with your data effortlessly.

## Prerequisites
Before diving into the world of advanced data manipulation, ensure you have the following prerequisites:

- A C++ compiler (C++11 or later)
- A CSV file containing the data you wish to analyze

## Getting Started

1. **Compile the Code**:  Compile the provided C++ code using your preferred C++ compiler. For example:
 ```shell
   g++ -std=c++11 main.cpp -o data_manipulator
 ```

2. **Run the Program**: Execute the compiled binary:

 ```shell
  ./data_manipulator
 ```

3. **Provide Input**: Follow the on-screen prompts to input the number of rows, number of columns, the CSV file name, and the data types for each column.

4. **Interact with Data**: Once the program is running, you can interact with your data by entering various commands. Choose from options like finding records, displaying data, analyzing data, and extracting subsets.

5. **Exit the Program**: To exit the program, simply enter the appropriate command or close the terminal.

## Command Reference

Here's a quick reference for the commands you can use within the program:

- F: Find a specific value in the first column of the data and display the corresponding record.

- V: Search for a value across the entire dataset and display the row and column where it's found.

- D: Display the entire dataset in a tabular format.

- I: Find the minimum value within a specified column (numeric columns only).

- C: Extract a subset of columns from the dataset.

- R: Extract a subset of rows from the dataset.

- S: Extract a subset of rows and columns from the dataset.

## Usage Example

Let's explore a simple usage example of the `tableClass` to demonstrate some of its core features.

### 1. Initialization and Data Loading

First, we'll initialize a `tableClass` object, load data from a CSV file, and display the initial state of the table.

```cpp
#include <iostream>
#include "tableClass.h"

int main() {
    // Initialize a tableClass object with 3 rows and 4 columns
    tableClass myTable(3, 4);

    // Define data types for each column
    string dataTypes[] = { "int", "float", "string", "int" };
    myTable.setData(dataTypes);

    // Read data from a CSV file
    myTable.readCSV("sample_data.csv");

    // Display the initial table
    std::cout << "Initial Table:\n";
    myTable.display();

    return 0;
}
```
### 2. Data Manipulation
Next, we'll demonstrate some data manipulation operations like sorting and finding minimum values in columns.
```cpp
#include <iostream>
#include "tableClass.h"

int main() {
    // ... (Previous code for initialization and data loading)

    // Sort the table based on the first column
    myTable.sortTable();

    // Display the sorted table
    std::cout << "\nSorted Table:\n";
    myTable.display();

    // Find the minimum value in the third column
    double minValue = myTable.findMin(2);
    std::cout << "\nMinimum value in the third column: " << minValue << std::endl;

    return 0;
}
```

### 3. Record and Value Searches
Now, let's perform searches for specific records and values in the table.
```cpp
#include <iostream>
#include "tableClass.h"

int main() {
    // ... (Previous code for initialization and data loading)

    // Search for a specific record based on a value in the first column
    std::string searchValue = "John";
    try {
        std::string foundRecord = myTable.searchRecord(searchValue);
        std::cout << "\nRecord found for '" << searchValue << "':\n" << foundRecord << std::endl;
    } catch (const RecordNotFoundException& e) {
        std::cerr << "\n" << e.getMessage() << std::endl;
    }

    // Search for a specific value in the entire table
    std::string findValue = "42";
    std::cout << "\nSearching for value '" << findValue << "' in the entire table:\n";
    myTable.searchValue(findValue);

    return 0;
}
```

## Exception Handling
This program employs robust exception handling to ensure data integrity and program stability. Should any errors occur during data processing, the program will gracefully handle them and provide informative error messages.

## Memory Management
The program makes use of dynamic memory allocation for data storage. While it diligently manages memory, be aware that the program does not exit cleanly in the provided code. Remember to free resources manually by deleting objects before program termination.

## Enjoy Data Manipulation!
With this impressive C++ program, you're now equipped to conquer the world of tabular data manipulation. Feel free to explore, analyze, and extract valuable insights from your datasets with ease and precision.

Happy coding, and may your data analysis endeavors be nothing short of extraordinary!
