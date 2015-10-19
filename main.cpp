#include <cstdlib>
#include <ctime>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
using namespace std ;

#include "Manager.hpp"

int main( int argc, char** argv ) {
    srand(time(NULL)) ;
    Manager manager ;
    manager.print_sudokus() ;
    manager.set_hardness();
    /*
    Sudoku sudoku(9) ;
    sudoku.print_sudoku() ;
    cout << "build in " << sudoku.times() << " times." << endl ;
    cout << "self check: " << ( sudoku.self_check() ? "success" : "failed" ) << endl ;
    cout << "string: " << endl << sudoku.str() << endl ;
    cout << "HASH: " << sudoku.hash() << endl ;
    sudoku.save() ;
    //cout << "self check: " << ( sudoku.self_check() ? "success" : "failed" ) << "\n" ;
    //sudoku.copy2() ;
    //sudoku.print_copy() ;
    */
    return 0 ;
} // main
