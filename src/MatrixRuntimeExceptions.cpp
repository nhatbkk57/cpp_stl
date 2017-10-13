#include "MatrixRuntimeExceptions.h"

const char* ZeroMatrixDimensionException::msg = "ZeroMatrixDimensionException: The matrix cannot have zero rows or colums.";

ZeroMatrixDimensionException::ZeroMatrixDimensionException() throw() : std::runtime_error(msg) {}

const char* ZeroMatrixDimensionException::what( ) const throw()
{
    return msg;
}