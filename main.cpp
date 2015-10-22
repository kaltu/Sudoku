#include <cstdlib>
#include <ctime>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
using namespace std ;

#include "Manager.hpp"

void play( Manager &manager ) ;
void manage( Manager &manager ) ;
void start( Manager &manager ) ;

void play( Manager &manager ) {

} // player interface

void manage( Manager &manager ) {
    cout << "1.show sudokus" << endl
         << "2.add new sudoku" << endl
         << "3.delete sudoku" << endl
         << "0.exit managing mode" << endl
         << ">>> " ;
    short opt ;
    cin >> opt ;
    if ( opt == 1 )
        manager.print_sudokus() ;
    else if ( opt == 2 )
        manager.create_sudoku() ;
    else if ( opt == 3 )
        manager.delete_sudoku() ;
    else if ( opt == 0 )
        return start( manager ) ;
    return manage( manager ) ;
} // manager interface

void start( Manager &manager ) {
    cout << "1.manage" << endl
         << "2.play" << endl
         << "0.exit" << endl
         << ">>> " ;
    short opt ;
    cin >> opt ;
    if ( opt == 1 )
        return play( manager ) ;
    else if ( opt == 2 )
        return manage( manager ) ;
    else if ( opt != 0 )
        return start(manager) ;
} // starter

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

    //start() ;
    return 0 ;
} // main
