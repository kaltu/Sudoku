#include <cstdlib>
#include <ctime>
#include <iostream>
#include <vector>
using namespace std ;

#include "Sudoku.hpp"

int main( int argc, char** argv ) {
    srand(time(NULL)) ;
    Sudoku sudoku(9) ;
    sudoku.print_sudoku() ;
    cout << "build in " << sudoku.times() << " times." << endl ;
    cout << "self check: " << ( sudoku.self_check() ? "success" : "failed" ) << "\n" ;
    sudoku.copy2() ;
    sudoku.print_copy() ;
    return 0 ;
} // main
