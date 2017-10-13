/**
 * @file   Matrix.h
 * @author FirstName LastName <email@domain.org>
 * Time-stamp: <Mon 2015-03-09 15:45 svarrette>
 *
 * @brief Assignement Matrix STL
 *
 */
/*****************************************************************************/
#ifndef __MATRIX_H
#define __MATRIX_H

#include <assert.h>

#include <iostream>
#include <iomanip>
#include <algorithm>
#include <functional>
#include <numeric> //iota
#include <vector>
#include <exception>
#include <stdexcept>
#include <type_traits>


// [Eigen](http://eigen.tuxfamily.org/) Matrix and Array classes, basic linear algebra
// #include <Eigen/Core>

// [Boost uBlas](http://www.boost.org/doc/libs/1_57_0/libs/numeric/ublas/doc)
// #include <boost/numeric/ublas/matrix.hpp>
// #include <boost/numeric/ublas/matrix_proxy.hpp>
// #include <boost/numeric/ublas/io.hpp>
// #include <boost/numeric/ublas/lu.hpp>

// namespace ublas = boost::numeric::ublas;

namespace Util {
    // =======================================
    /**
     * MatrixRunTimeError. Illustrate the definition of derived class from standard
     * exceptions. For reminder, the standard exeption derives from the excepiton class
     * present in the <exception> header and declared as follows (see [Stroustrup ch14 p.385]):
     * \code
     class exception {
     public:
     exception() throw();
     exception(const exception &) throw();
     exception & operator=(const exception &) throw();
     virtual ~exception() throw();

     virtual const char* what() const throw();
     private:
     ...
     };
     \endcode
     * The hierachy of standard exception are as follows:
     * \verbatim
     .                 +------------------> exception <----------------+
     .                 |                    ^ ^ ^ ^ ^                  |
     .                 logic_error          | | | | |            runtime_error
     .                  ^ ^ ^ ^             | | | | |                ^ ^ ^
     .                  | | | |             | | | | |                | | |
     . length_error ----+ | | | bad_alloc --+ | | | +-- bad_cast     | | +-- range_error
     . domain_error ------+ | |bad_exception -+ | +-- bad_typeid     | +-- overflow_error
     . out_of_range --------+ |         ios_base::failure            +-- underflow_error
     . invalid_argument ------+

     \endverbatim
    */



}; // end namespace Util

// ========================================================
/**
 * Matrix. Simple dense (m x n)-dimensional matrix of elements of type T, store in a rowmajor fashion.
 * \verbatim
 .                 n
 .  <---------------------------->
 ^  +-                          -+
 |  | a_{0,0} .......  a_{0,n-1} |
 |  | a_{1,0} .......  a_{1,n-1} |
 m  |         .                  |
 |  |            .               |
 |  | a_{m-1,0}      a_{m-1,n-1} |
 v  +-                          -+
 * \endverbatim
 */
template <class T>
class Matrix {
    /* Some friend operators (implemented as non-member functions) */
    template <class U> friend
    std::ostream& operator<<(std::ostream& os, const Matrix<U> & M);
    // /!\ inefficient prototypes for the following operators
    template <class U> friend                        /* Addition */
    Matrix<U> operator+(const Matrix<U> & M1, const Matrix<U> & M2);
    template <class U> friend                    /* Soustraction */
    Matrix<U> operator-(const Matrix<U> & M1, const Matrix<U> & M2);
    template <class U> friend                  /* Multiplication */
    Matrix<U> operator*(const Matrix<U> & M1, const Matrix<U> & M2);
    template <class U> friend                       /* Transpose */
    Matrix<U> operator~(const Matrix<U> & M);
    // --------------------------------------------
public:
    const size_t rows;            /**< number of columns */
    const size_t cols;            /**< number of rows    */
protected:
    std::vector<T> _container;    /**< The actual container */
    // --------------------------------------------

public:
    // Constructors / Destructors
    Matrix(const size_t m = 2, const size_t n = 2);
    Matrix(const Matrix<T> & M) :
        rows(M.rows), cols(M.cols), _container(M._container) {
            
        }
    Matrix(const std::vector<T> & v, const size_t m, const size_t n):
        rows(m), cols(n), _container(v) { assert (m*n == v.size()); }
    // template <int R, int C>
    // Matrix(const Eigen::Matrix <T,R,C>& M);
    virtual ~Matrix() {}

    // Assignment (eventually with elements assigned the same constant)
    Matrix<T> & operator=(const Matrix<T> & M);
    template <int R, int C>
    // Matrix<T> & operator=(const Eigen::Matrix <T,R,C> & M);
    Matrix<T> & operator=(const T & val);

    // comparison
    bool operator==(const Matrix<T>& M) const;
    // bool operator==(const ublas::matrix <T> & M) const;
    template <int R, int C>
    // bool operator==(const Eigen::Matrix <T,R,C> & M) const;
    bool operator!() const { return iszero(); }

    // Accessor
    // get M(i,j)
    const T & operator() (const size_t i, const size_t j) const;
    T &       operator() (const size_t i, const size_t j);
    const T & operator[] (const size_t i) const { return _container[i]; }
    T &       operator[] (const size_t i)       { return _container[i]; }
    const T * data() const { return _container.data(); }
    T * data()             { return _container.data(); }
    std::vector<T> row(const size_t i) const;
    //typename std::vector<T> col(const size_t j) const;

    // Iterators
    typename std::vector<T>::iterator       begin()       { return _container.begin(); }
    typename std::vector<T>::const_iterator begin() const{ return _container.begin();}
    typename std::vector<T>::iterator       begin(const size_t i);
    typename std::vector<T>::const_iterator begin(const size_t i) const;
    typename std::vector<T>::iterator       end()       { return _container.end(); }
    typename std::vector<T>::const_iterator end() const { return _container.end(); }
    typename std::vector<T>::iterator       end(const size_t i);
    typename std::vector<T>::const_iterator end(const size_t i) const;

    /**
     * @return number of T elements in this matrix
     */
    size_t size() const { return rows * cols; }
    /**
     * Check if the matrix is null (i.e. composed by only O elements)
     */
    bool iszero() const;
    // ==== Generator / fill functions ===
    /**
     * Assignement of the elements to incremented values (using std::iota)
     */
    void generate();
    /**
     * Assignement of the elements to a value val (using std::fill)
     */
    void generate(const T & val);
    /**
     * Assignement of the elements to random values (using std::generate)
     * @param gen Functor to the random generator to be used
     */
    template<class RandomGenerator> void generate(RandomGenerator gen);
    /**
     * Transpose the matrix
     */
    Matrix<T> transpose() const;
    // ==== Printing functions ====
    /**
     * Print the j-th column  to the output stream s_out
     */
    std::ostream & printColumn(const size_t j = 0,
                               std::ostream &s_out = std::cout) const;
    /**
     * Print the i-th row  to the output stream s_out
     */
    std::ostream & printRow(const size_t i=0, std::ostream &s_out = std::cout) const;
    /**
     * Print the content of the Matrix to the output stream s_out
     */
    virtual std::ostream & print(std::ostream & s_out = std::cout) const;
};      // ============ end class Matrix ===================


#endif  // _MATRIX_H
