#ifndef __MATRIX_HPP__  // header guard to prevent multiple inclusion
#define __MATRIX_HPP__  // define the header guard

#include <cstdint>      // include for size_t type
#include <vector>       // include for vector container
#include <iostream>     // include for input/output streams
#include <iomanip>      // include for output formatting
#include <stdexcept>    // include for exception handling
#include <string>       // include for string operations

template <typename T>   // template class for matrix type
class Matrix {         // matrix class definition
private:               // private members
    std::vector<std::vector<T>> data;  // 2d vector to store matrix data
    std::size_t size;                  // size of the square matrix

public:                // public members
    // constructors
    Matrix(std::size_t N);            // constructor with size parameter
    Matrix(std::vector<std::vector<T>> nums);  // constructor with data
    
    // getters
    std::size_t get_size() const;     // get matrix size
    T get_value(std::size_t i, std::size_t j) const;  // get element at i,j
    
    // setters
    void set_value(std::size_t i, std::size_t j, T value);  // set element at i,j
    
    // matrix operations
    Matrix<T> operator+(const Matrix<T>& rhs) const;  // matrix addition
    Matrix<T> operator*(const Matrix<T>& rhs) const;  // matrix multiplication
    
    // diagonal operations
    T sum_diagonal_major() const;     // sum of main diagonal
    T sum_diagonal_minor() const;     // sum of secondary diagonal
    
    // row/column operations
    void swap_rows(std::size_t r1, std::size_t r2);  // swap two rows
    void swap_cols(std::size_t c1, std::size_t c2);  // swap two columns
    
    // i/o operations
    template <typename U>             // friend template for input
    friend std::istream& operator>>(std::istream& is, Matrix<U>& matrix);
    
    template <typename U>             // friend template for output
    friend std::ostream& operator<<(std::ostream& os, const Matrix<U>& matrix);
};

// non-member operator declarations
template <typename T>
std::istream& operator>>(std::istream& is, Matrix<T>& matrix);

template <typename T>
std::ostream& operator<<(std::ostream& os, const Matrix<T>& matrix);

// explicit template declarations
extern template class Matrix<int>;     // declare int instantiation
extern template class Matrix<double>;  // declare double instantiation

#endif // __MATRIX_HPP__  // end of header guard