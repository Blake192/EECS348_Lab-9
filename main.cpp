/***********************************************************************
 * EEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEE       CCCCCCCCCCCCC   SSSSSSSSSSSSSSS       333333333333333          444444444       888888888  
 * E::::::::::::::::::::EE::::::::::::::::::::E    CCC::::::::::::C SS:::::::::::::::S     3:::::::::::::::33       4::::::::4     88:::::::::88  
 * E::::::::::::::::::::EE::::::::::::::::::::E  CC:::::::::::::::CS:::::SSSSSS::::::S     3::::::33333::::::3     4:::::::::4   88:::::::::::::88  
 * EE::::::EEEEEEEEE::::EEE::::::EEEEEEEEE::::E C:::::CCCCCCCC::::CS:::::S     SSSSSSS     3333333     3:::::3    4::::44::::4  8::::::88888::::::8  
 *   E:::::E       EEEEEE  E:::::E       EEEEEEC:::::C       CCCCCCS:::::S                             3:::::3   4::::4 4::::4  8:::::8     8:::::8  
 *   E:::::E               E:::::E            C:::::C              S:::::S                             3:::::3  4::::4  4::::4  8:::::8     8:::::8  
 *   E::::::EEEEEEEEEE     E::::::EEEEEEEEEE  C:::::C               S::::SSSS                  33333333:::::3  4::::4   4::::4   8:::::88888:::::8  
 *   E:::::::::::::::E     E:::::::::::::::E  C:::::C                SS::::::SSSSS             3:::::::::::3  4::::444444::::444  8:::::::::::::8  
 *   E:::::::::::::::E     E:::::::::::::::E  C:::::C                  SSS::::::::SS           33333333:::::3 4::::::::::::::::4 8:::::88888:::::8  
 *   E::::::EEEEEEEEEE     E::::::EEEEEEEEEE  C:::::C                     SSSSSS::::S                  3:::::34444444444:::::4448:::::8     8:::::8  
 *   E:::::E               E:::::E            C:::::C                          S:::::S                 3:::::3          4::::4  8:::::8     8:::::8  
 *   E:::::E       EEEEEE  E:::::E       EEEEEEC:::::C       CCCCCC            S:::::S                 3:::::3          4::::4  8:::::8     8:::::8  
 * EE::::::EEEEEEEE:::::EEE::::::EEEEEEEE:::::E C:::::CCCCCCCC::::CSSSSSSS     S:::::S     3333333     3:::::3          4::::4  8::::::88888::::::8  
 * E::::::::::::::::::::EE::::::::::::::::::::E  CC:::::::::::::::CS::::::SSSSSS:::::S     3::::::33333::::::3        44::::::44 88:::::::::::::88  
 * E::::::::::::::::::::EE::::::::::::::::::::E    CCC::::::::::::CS:::::::::::::::SS      3:::::::::::::::33         4::::::::4   88:::::::::88  
 * EEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEE       CCCCCCCCCCCCC SSSSSSSSSSSSSSS         333333333333333           4444444444     888888888  
 *   
 * EECS 348 LAB 9
 * DESCRIPTION: IMPLEMENT MATRIX OPERATIONS IN C++ WITH TEMPLATE FUNCTIONS
 * INPUTS: Reads matrix size and two matrices from user specified file.  
 * OUTPUTS: Shows operations and output
 * ALL COLLABS: Blake Pennel, template files from github, ChatGPT o3-mini-high/Claud 3.7 sonnett with Cursor IDE integration (help with creation based on template files)
 * AUTHORS: Blake Pennel 
 * CREATION DATE: 04/08/2025 
 ***********************************************************************/  
#include "matrix.hpp"               // include matrix header
#include <iostream>                 // include for console i/o
#include <fstream>                  // include for file i/o
#include <stdexcept>                // include for exceptions
#include <string>                   // include for strings
#include <sstream>                  // include for string streams
#include <limits>                   // include for numeric limits

// function to safely read two indices from user
template <typename T>
bool read_two_indices(std::size_t& idx1, std::size_t& idx2, std::size_t max_idx, const std::string& prompt) {  // read two indices safely
    std::cout << prompt;            // display prompt
    std::string input;              // store user input
    if (!std::getline(std::cin, input) || input.empty()) {  // read full line of input
        std::cout << "Invalid input. Please try again.\n";  // error message
        return false;               // return failure
    }
    
    std::istringstream iss(input);  // create string stream from input
    if (!(iss >> idx1 >> idx2)) {   // try to read two indices
        std::cout << "Invalid input. Please enter two numbers between 0 and " << max_idx << ".\n";  // error message
        return false;               // return failure
    }
    
    // check if any extra input remains
    std::string extra;              // store extra input
    if (iss >> extra) {             // try to read more
        std::cout << "Too many values entered. Please enter exactly two numbers.\n";  // error message
        return false;               // return failure
    }
    
    // check bounds
    if (idx1 > max_idx || idx2 > max_idx) {  // check if indices are in range
        std::cout << "Index out of range. Please enter numbers between 0 and " << max_idx << ".\n";  // error message
        return false;               // return failure
    }
    
    return true;                    // return success
}

// function to safely read a value update (row, column, value)
template <typename T>
bool read_value_update(std::size_t& row, std::size_t& col, T& value, std::size_t max_idx) {  // read value update safely
    std::cout << "Enter row, column, and new value (0-" << max_idx << "): ";  // prompt for input
    
    std::string input;              // store user input
    if (!std::getline(std::cin, input) || input.empty()) {  // read full line of input
        std::cout << "Invalid input. Please try again.\n";  // error message
        return false;               // return failure
    }
    
    std::istringstream iss(input);  // create string stream from input
    if (!(iss >> row >> col >> value)) {  // try to read row, column, and value
        std::cout << "Invalid input. Please enter row, column, and value.\n";  // error message
        return false;               // return failure
    }
    
    // check if any extra input remains
    std::string extra;              // store extra input
    if (iss >> extra) {             // try to read more
        std::cout << "Too many values entered. Please enter exactly three values.\n";  // error message
        return false;               // return failure
    }
    
    // check bounds
    if (row > max_idx || col > max_idx) {  // check if indices are in range
        std::cout << "Index out of range. Please enter row and column between 0 and " << max_idx << ".\n";  // error message
        return false;               // return failure
    }
    
    return true;                    // return success
}

// safely read menu choice
bool read_menu_choice(int& choice, int min_choice, int max_choice) {  // read menu choice safely
    std::string input;              // store user input
    if (!std::getline(std::cin, input) || input.empty()) {  // read full line of input
        std::cout << "Invalid input. Please try again.\n";  // error message
        return false;               // return failure
    }
    
    std::istringstream iss(input);  // create string stream from input
    if (!(iss >> choice)) {         // try to read choice
        std::cout << "Invalid input. Please enter a number.\n";  // error message
        return false;               // return failure
    }
    
    // check if any extra input remains
    std::string extra;              // store extra input
    if (iss >> extra) {             // try to read more
        std::cout << "Too many values entered. Please enter exactly one number.\n";  // error message
        return false;               // return failure
    }
    
    // check bounds
    if (choice < min_choice || choice > max_choice) {  // check if choice is in range
        std::cout << "Invalid choice. Please enter a number between " << min_choice << " and " << max_choice << ".\n";  // error message
        return false;               // return failure
    }
    
    return true;                    // return success
}

// process matrix operations for type T
template <typename T>
void process_matrix_operations(const std::string& filename) {  // process matrix operations
    std::ifstream inFile(filename);                           // open input file
    if (!inFile) {                                            // check if file opened
        throw std::runtime_error("Could not open file: " + filename);  // throw if failed
    }

    // read matrix size and type
    std::size_t N;                                            // store matrix size
    int type;                                                 // store matrix type
    if (!(inFile >> N >> type)) {                            // read size and type
        throw std::runtime_error("Invalid input format: expected matrix size and type");  // throw if invalid
    }

    if (N == 0) {                                            // check size
        throw std::invalid_argument("Matrix size cannot be zero");  // throw if zero
    }

    // create matrices
    Matrix<T> matrix1(N);                                    // create first matrix
    Matrix<T> matrix2(N);                                    // create second matrix

    // read matrices
    try {                                                    // try to read matrices
        inFile >> matrix1 >> matrix2;                        // read from file
    } catch (const std::exception& e) {                      // catch errors
        throw std::runtime_error("Error reading matrices: " + std::string(e.what()));  // throw with message
    }

    inFile.close();                                         // close file

    std::cout << "\nMatrix 1:\n" << matrix1;               // print first matrix
    std::cout << "\nMatrix 2:\n" << matrix2;               // print second matrix

    int choice = 0;                                        // store menu choice
    do {                                                   // start menu loop
        std::cout << "\nMenu:\n"                          // print menu
                  << "1. Display Matrix 1\n"              // option 1
                  << "2. Display Matrix 2\n"              // option 2
                  << "3. Add Matrices (Matrix1 + Matrix2)\n"  // option 3
                  << "4. Multiply Matrices (Matrix1 * Matrix2)\n"  // option 4
                  << "5. Display Sum of Diagonals of Matrix 1\n"  // option 5
                  << "6. Swap Rows in Matrix 1\n"         // option 6
                  << "7. Swap Columns in Matrix 1\n"      // option 7
                  << "8. Update an Element in Matrix 1\n" // option 8
                  << "9. Exit\n"                          // option 9
                  << "Enter your choice: ";               // prompt for choice

        if (!read_menu_choice(choice, 1, 9)) {            // read and validate menu choice
            continue;                                     // if invalid, try again
        }

        try {                                             // try to process choice
            switch (choice) {                             // switch on choice
                case 1:                                   // display matrix 1
                    std::cout << "\nMatrix 1:\n" << matrix1;  // print matrix 1
                    break;                                // exit switch
                case 2:                                   // display matrix 2
                    std::cout << "\nMatrix 2:\n" << matrix2;  // print matrix 2
                    break;                                // exit switch
                case 3: {                                 // add matrices
                    Matrix<T> sum = matrix1 + matrix2;    // add matrices
                    std::cout << "\nResult of Matrix1 + Matrix2:\n" << sum;  // print result
                    break;                                // exit switch
                }
                case 4: {                                 // multiply matrices
                    Matrix<T> product = matrix1 * matrix2;  // multiply matrices
                    std::cout << "\nResult of Matrix1 * Matrix2:\n" << product;  // print result
                    break;                                // exit switch
                }
                case 5:                                   // display diagonals
                    std::cout << "\nSum of Major Diagonal (Matrix1): " << matrix1.sum_diagonal_major() << '\n'  // print major
                              << "Sum of Minor Diagonal (Matrix1): " << matrix1.sum_diagonal_minor() << '\n';  // print minor
                    break;                                // exit switch
                case 6: {                                 // swap rows
                    std::size_t r1, r2;                   // store row indices
                    if (!read_two_indices<T>(r1, r2, N-1, "Enter two row indices to swap (0-" + std::to_string(N-1) + "): ")) {  // read and validate
                        continue;                         // if invalid, try again
                    }
                    matrix1.swap_rows(r1, r2);            // swap rows
                    std::cout << "\nMatrix 1 after swapping rows " << r1 << " and " << r2 << ":\n" << matrix1;  // print result
                    break;                                // exit switch
                }
                case 7: {                                 // swap columns
                    std::size_t c1, c2;                   // store column indices
                    if (!read_two_indices<T>(c1, c2, N-1, "Enter two column indices to swap (0-" + std::to_string(N-1) + "): ")) {  // read and validate
                        continue;                         // if invalid, try again
                    }
                    matrix1.swap_cols(c1, c2);            // swap columns
                    std::cout << "\nMatrix 1 after swapping columns " << c1 << " and " << c2 << ":\n" << matrix1;  // print result
                    break;                                // exit switch
                }
                case 8: {                                 // update element
                    std::size_t row, col;                 // store indices
                    T value;                              // store new value
                    if (!read_value_update<T>(row, col, value, N-1)) {  // read and validate
                        continue;                         // if invalid, try again
                    }
                    matrix1.set_value(row, col, value);   // update element
                    std::cout << "\nMatrix 1 after updating element at (" << row << ", " << col << "):\n" << matrix1;  // print result
                    break;                                // exit switch
                }
                case 9:                                   // exit
                    std::cout << "Exiting program.\n";    // print exit message
                    break;                                // exit switch
                default:                                  // invalid choice
                    std::cout << "Invalid choice. Please try again.\n";  // print error
            }
        } catch (const std::exception& e) {               // catch errors
            std::cerr << "Error: " << e.what() << '\n';  // print error message
        }
    } while (choice != 9);                               // loop until exit
}

// main function
int main() {                                             // program entry point
    try {                                                // try to run program
        std::string filename;                            // store filename
        std::cout << "Enter the input file name: ";      // prompt for filename
        
        // read filename
        if (!std::getline(std::cin, filename) || filename.empty()) {  // read full line of input
            throw std::runtime_error("Invalid input for filename");  // throw if invalid
        }

        // read the first line to determine matrix type
        std::ifstream inFile(filename);                  // open file
        if (!inFile) {                                   // check if opened
            throw std::runtime_error("Could not open file: " + filename);  // throw if failed
        }

        std::size_t N;                                   // store matrix size
        int type;                                        // store matrix type
        if (!(inFile >> N >> type)) {                   // read size and type
            throw std::runtime_error("Invalid input format: expected matrix size and type");  // throw if invalid
        }
        inFile.close();                                 // close file

        // process based on type
        if (type == 0) {                                // if integer type
            process_matrix_operations<int>(filename);    // process as int
        } else if (type == 1) {                         // if double type
            process_matrix_operations<double>(filename); // process as double
        } else {                                        // invalid type
            throw std::invalid_argument("Invalid matrix type. Must be 0 (int) or 1 (double)");  // throw if invalid
        }
    } catch (const std::exception& e) {                 // catch errors
        std::cerr << "Error: " << e.what() << '\n';    // print error message
        return 1;                                       // return error code
    }

    return 0;                                          // return success
} 
