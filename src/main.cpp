/**
 * @file   main.cpp
 * @author Sebastien Varrette <Sebastien.Varrette@uni.lu>
 * Time-stamp: <Mon 2015-03-09 15:46 svarrette>
 *
 * @brief  Main entry
 */

#include <string>
#include <iostream>
#include <sstream>
#include <getopt.h>
#include <stdlib.h>
#include <algorithm>
#include <map>  // hash table

#include <boost/timer/timer.hpp>
#include <boost/assign/std/vector.hpp> // for 'operator+=()'
#include "boost/program_options.hpp"
namespace po = boost::program_options;

#include "Matrix.h"
#include "MatrixRuntimeExceptions.h"
//#include "Tools.h"



// [Eigen](http://eigen.tuxfamily.org/) Matrix and Array classes, basic linear algebra
// #include <Eigen/Core>
// #include <Eigen/LU>
// [Boost uBlas](http://www.boost.org/doc/libs/1_57_0/libs/numeric/ublas/doc)
// #include <boost/numeric/ublas/matrix.hpp>
// #include <boost/numeric/ublas/io.hpp>

using namespace std;
// using namespace boost::assign; // bring 'operator+=()' into scope

typedef int type_t; // type to use in matrix elements


/**
 * Entry point where the program begins its execution.
 * @param argc number of arguments of the command line
 * @param argv multi-array containing the command line arguments
 *             (argv[0] is the name of the program, argv[argc]=NULL)
 * @return status of the execution (0: correct execution)
 */
int main(int argc, char * argv[]){
    try {
        po::options_description desc("Available options");
        // supported options
        desc.add_options()
            ("help,h", "Display this help message")
            ("verbose,v", "Verbosity level")
            ("repeat",    po::value<int>()->default_value(1), "Repeat each test <arg> times")
            ("rows,m",    po::value<size_t>()->default_value(3),   "Number of rows")
            ("cols,n",    po::value<size_t>()->default_value(4),   "Number of columns")
            ("random,r",  "Initialize the matrix with random values")
            ("min",       po::value<type_t>()->default_value(-5), "Minimal value for the random values")
            ("max",       po::value<type_t>()->default_value(5),  "Maximal value for the random values")
            ;

        po::variables_map vm;
        po::store(po::parse_command_line(argc, argv, desc), vm);
        po::notify(vm); //assign the variables (if they were specified)

        if (vm.count("help")) {
            std::cout << "Assignment Matrix / STL" << std::endl;
            std::cout << "\t<Lastname> <Firstname> <StudentID" << std::endl;
            std::cout << desc << std::endl;
            return 1;
        }

        if (vm.count("rows") || vm.count("cols"))
        {
            size_t m = vm["rows"].as<size_t>();
            size_t n = vm["cols"].as<size_t>();

            if (m == 0 || n == 0)
            {
                throw ZeroMatrixDimensionException();
            }

            std::cout << "Rows = " << m << " Cols = " << n << std::endl;
        }
    }
    catch(std::exception & e) {
        std::cout << e.what() << "\n";
        return 1;
    }
    return 0;
}
