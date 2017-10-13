#include <stdexcept>

class ZeroMatrixDimensionException : public std::runtime_error
{
    public:
        ZeroMatrixDimensionException() throw();
        // ZeroMatrixDimensionException(const ZeroMatrixDimensionException &) throw();
        // ZeroMatrixDimensionException & operator=(const ZeroMatrixDimensionException &) throw();
        // virtual ~ZeroMatrixDimensionException() throw();

        virtual const char* what() const throw();

    private:

        static const char* msg;
};