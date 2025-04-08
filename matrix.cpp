#include "matrix.hpp"    // include the header file
#include <iostream>      // include for console output
#include <iomanip>       // include for output formatting
#include <stdexcept>     // include for exceptions
#include <string>        // include for string operations
#include <sstream>       // include for string streams
#include <fstream>       // include for file i/o
#include <limits>        // include for numeric limits

// constructor with size parameter
template <typename T>
Matrix<T>::Matrix(std::size_t N) : size(N) {  // initialize size
    if (N == 0) {                             // check for zero size
        throw std::invalid_argument("Matrix size cannot be zero");  // throw if invalid
    }
    if (N > 100) {                            // check for maximum size
        throw std::invalid_argument("Matrix size cannot exceed 100");  // throw if too large
    }
    data = std::vector<std::vector<T>>(N, std::vector<T>(N, T()));  // create nxn matrix
}

// constructor with data
template <typename T>
Matrix<T>::Matrix(std::vector<std::vector<T>> nums) : data(nums), size(nums.size()) {  // initialize with data
    if (size == 0) {                                                                  // check for empty matrix
        throw std::invalid_argument("Matrix cannot be empty");                         // throw if empty
    }
    if (size > 100) {                                                                 // check for maximum size
        throw std::invalid_argument("Matrix size cannot exceed 100");                  // throw if too large
    }
    for (const auto& row : nums) {                                                    // check each row
        if (row.size() != size) {                                                     // check if square
            throw std::invalid_argument("Matrix must be square");                      // throw if not square
        }
    }
}

// matrix addition operator
template <typename T>
Matrix<T> Matrix<T>::operator+(const Matrix<T>& rhs) const {  // add two matrices
    if (size != rhs.size) {                                  // check size match
        throw std::invalid_argument("Matrix dimensions must match for addition");  // throw if sizes differ
    }
    
    Matrix<T> result(size);                                  // create result matrix
    for (std::size_t i = 0; i < size; ++i) {                // loop through rows
        for (std::size_t j = 0; j < size; ++j) {            // loop through columns
            // check for overflow/underflow
            if (std::numeric_limits<T>::is_integer) {        // if integer type
                if (data[i][j] > 0 && rhs.data[i][j] > 0) {  // both positive
                    if (std::numeric_limits<T>::max() - data[i][j] < rhs.data[i][j]) {  // check overflow
                        throw std::overflow_error("Integer overflow in matrix addition");
                    }
                } else if (data[i][j] < 0 && rhs.data[i][j] < 0) {  // both negative
                    if (std::numeric_limits<T>::min() - data[i][j] > rhs.data[i][j]) {  // check underflow
                        throw std::underflow_error("Integer underflow in matrix addition");
                    }
                }
            }
            result.data[i][j] = data[i][j] + rhs.data[i][j];  // add elements
        }
    }
    return result;                                           // return result
}

// matrix multiplication operator
template <typename T>
Matrix<T> Matrix<T>::operator*(const Matrix<T>& rhs) const {  // multiply two matrices
    if (size != rhs.size) {                                  // check size match
        throw std::invalid_argument("Matrix dimensions must match for multiplication");  // throw if sizes differ
    }
    
    Matrix<T> result(size);                                  // create result matrix
    for (std::size_t i = 0; i < size; ++i) {                // loop through rows
        for (std::size_t j = 0; j < size; ++j) {            // loop through columns
            T sum = T();                                     // initialize sum
            for (std::size_t k = 0; k < size; ++k) {        // loop for dot product
                // check for overflow/underflow
                if (std::numeric_limits<T>::is_integer) {    // if integer type
                    if (data[i][k] > 0 && rhs.data[k][j] > 0) {  // both positive
                        if (std::numeric_limits<T>::max() / data[i][k] < rhs.data[k][j]) {  // check overflow
                            throw std::overflow_error("Integer overflow in matrix multiplication");
                        }
                    } else if (data[i][k] < 0 && rhs.data[k][j] < 0) {  // both negative
                        if (std::numeric_limits<T>::max() / data[i][k] > rhs.data[k][j]) {  // check overflow
                            throw std::overflow_error("Integer overflow in matrix multiplication");
                        }
                    } else if (data[i][k] < 0 || rhs.data[k][j] < 0) {  // one negative
                        if (std::numeric_limits<T>::min() / data[i][k] < rhs.data[k][j]) {  // check underflow
                            throw std::underflow_error("Integer underflow in matrix multiplication");
                        }
                    }
                }
                T product = data[i][k] * rhs.data[k][j];     // multiply elements
                // check for overflow/underflow in addition
                if (std::numeric_limits<T>::is_integer) {    // if integer type
                    if (sum > 0 && product > 0) {            // both positive
                        if (std::numeric_limits<T>::max() - sum < product) {  // check overflow
                            throw std::overflow_error("Integer overflow in matrix multiplication");
                        }
                    } else if (sum < 0 && product < 0) {     // both negative
                        if (std::numeric_limits<T>::min() - sum > product) {  // check underflow
                            throw std::underflow_error("Integer underflow in matrix multiplication");
                        }
                    }
                }
                sum += product;                              // add to sum
            }
            result.data[i][j] = sum;                         // store result
        }
    }
    return result;                                           // return result
}

// set element value
template <typename T>
void Matrix<T>::set_value(std::size_t i, std::size_t j, T value) {  // set element at i,j
    if (i >= size || j >= size) {                                  // check bounds
        throw std::out_of_range("Matrix index out of bounds");      // throw if out of bounds
    }
    data[i][j] = value;                                            // set value
}

// get element value
template <typename T>
T Matrix<T>::get_value(std::size_t i, std::size_t j) const {  // get element at i,j
    if (i >= size || j >= size) {                            // check bounds
        throw std::out_of_range("Matrix index out of bounds");  // throw if out of bounds
    }
    return data[i][j];                                        // return value
}

// get matrix size
template <typename T>
std::size_t Matrix<T>::get_size() const {  // get size of matrix
    return size;                           // return size
}

// sum of main diagonal
template <typename T>
T Matrix<T>::sum_diagonal_major() const {  // calculate main diagonal sum
    T sum = T();                           // initialize sum
    for (std::size_t i = 0; i < size; ++i) {  // loop through diagonal
        // check for overflow/underflow
        if (std::numeric_limits<T>::is_integer) {  // if integer type
            if (sum > 0 && data[i][i] > 0) {       // both positive
                if (std::numeric_limits<T>::max() - sum < data[i][i]) {  // check overflow
                    throw std::overflow_error("Integer overflow in diagonal sum");
                }
            } else if (sum < 0 && data[i][i] < 0) {  // both negative
                if (std::numeric_limits<T>::min() - sum > data[i][i]) {  // check underflow
                    throw std::underflow_error("Integer underflow in diagonal sum");
                }
            }
        }
        sum += data[i][i];                  // add element
    }
    return sum;                             // return sum
}

// sum of secondary diagonal
template <typename T>
T Matrix<T>::sum_diagonal_minor() const {  // calculate secondary diagonal sum
    T sum = T();                           // initialize sum
    for (std::size_t i = 0; i < size; ++i) {  // loop through diagonal
        // check for overflow/underflow
        if (std::numeric_limits<T>::is_integer) {  // if integer type
            if (sum > 0 && data[i][size - 1 - i] > 0) {  // both positive
                if (std::numeric_limits<T>::max() - sum < data[i][size - 1 - i]) {  // check overflow
                    throw std::overflow_error("Integer overflow in diagonal sum");
                }
            } else if (sum < 0 && data[i][size - 1 - i] < 0) {  // both negative
                if (std::numeric_limits<T>::min() - sum > data[i][size - 1 - i]) {  // check underflow
                    throw std::underflow_error("Integer underflow in diagonal sum");
                }
            }
        }
        sum += data[i][size - 1 - i];       // add element
    }
    return sum;                             // return sum
}

// swap two rows
template <typename T>
void Matrix<T>::swap_rows(std::size_t r1, std::size_t r2) {  // swap rows r1 and r2
    if (r1 >= size || r2 >= size) {                         // check bounds
        throw std::out_of_range("Row index out of bounds");  // throw if out of bounds
    }
    if (r1 == r2) {                                         // check if same row
        return;                                             // no need to swap
    }
    std::swap(data[r1], data[r2]);                          // swap rows
}

// swap two columns
template <typename T>
void Matrix<T>::swap_cols(std::size_t c1, std::size_t c2) {  // swap columns c1 and c2
    if (c1 >= size || c2 >= size) {                         // check bounds
        throw std::out_of_range("Column index out of bounds");  // throw if out of bounds
    }
    if (c1 == c2) {                                         // check if same column
        return;                                             // no need to swap
    }
    for (std::size_t i = 0; i < size; ++i) {               // loop through rows
        std::swap(data[i][c1], data[i][c2]);               // swap elements
    }
}

// input operator
template <typename T>
std::istream& operator>>(std::istream& is, Matrix<T>& matrix) {  // read matrix from stream
    for (std::size_t i = 0; i < matrix.size; ++i) {            // loop through rows
        for (std::size_t j = 0; j < matrix.size; ++j) {        // loop through columns
            T value;                                           // store value
            if (!(is >> value)) {                             // read value
                throw std::runtime_error("Invalid matrix element at row " + std::to_string(i) + 
                                       ", column " + std::to_string(j));  // throw with location
            }
            // check for overflow/underflow
            if (std::numeric_limits<T>::is_integer) {          // if integer type
                if (value > std::numeric_limits<T>::max()) {   // check overflow
                    throw std::overflow_error("Integer overflow at row " + std::to_string(i) + 
                                           ", column " + std::to_string(j));
                }
                if (value < std::numeric_limits<T>::min()) {   // check underflow
                    throw std::underflow_error("Integer underflow at row " + std::to_string(i) + 
                                            ", column " + std::to_string(j));
                }
            }
            matrix.set_value(i, j, value);                     // set value
        }
    }
    return is;                                                 // return stream
}

// output operator
template <typename T>
std::ostream& operator<<(std::ostream& os, const Matrix<T>& matrix) {  // write matrix to stream
    int max_width = 0;                                                // store max width
    for (const auto& row : matrix.data) {                             // loop through rows
        for (const auto& val : row) {                                 // loop through columns
            std::ostringstream oss;                                   // create string stream
            oss << val;                                              // write value
            int width = static_cast<int>(oss.str().length());        // get width
            if (width > max_width) {                                 // check if max
                max_width = width;                                   // update max width
            }
        }
    }
    
    for (const auto& row : matrix.data) {                            // loop through rows
        for (const auto& val : row) {                                // loop through columns
            os << std::setw(max_width + 1) << val;                   // write value with padding
        }
        os << '\n';                                                  // new line
    }
    return os;                                                       // return stream
}

// explicit template instantiations
template class Matrix<int>;     // instantiate for int
template class Matrix<double>;  // instantiate for double

// explicit instantiations for input/output operators
template std::istream& operator>><int>(std::istream&, Matrix<int>&);
template std::istream& operator>><double>(std::istream&, Matrix<double>&);
template std::ostream& operator<<<int>(std::ostream&, const Matrix<int>&);
template std::ostream& operator<<<double>(std::ostream&, const Matrix<double>&);
