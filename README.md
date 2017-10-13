-*- mode: markdown; mode: visual-line; fill-column: 80 -*-
`README.md`

Copyright (c) 2015 [Sebastien Varrette](mailto:<Sebastien.Varrette@uni.lu>)

        Time-stamp: <Lun 2015-03-09 15:50 svarrette>

-------------------

# C++ Matrix / STL -- Example of sources organization

Template for the source files can be found in `src/`. 

Building these sources is based on [CMake](http://www.cmake.org/) within the `build/` directory

      $> cd build
	  $> cmake ../src
	  $> make

The main application supports the following command-line options: 

```
$> ./matrix_stl -h
Assignment Matrix / STL
	<Lastname> <Firstname> <StudentID
Available options:
  -h [ --help ]          Display this help message
  -v [ --verbose ]       Verbosity level
  --repeat arg (=1)      Repeat each test <arg> times
  -m [ --rows ] arg (=3) Number of rows
  -n [ --cols ] arg (=4) Number of columns
  -r [ --random ]        Initialize the matrix with random values
  --min arg (=-5)        Minimal value for the random values
  --max arg (=5)         Maximal value for the random values
```
